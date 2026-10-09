# Run from PowerShell: .\cleanup_sim.ps1 (or add -WhatIf to preview).
[CmdletBinding(SupportsShouldProcess = $true, ConfirmImpact = 'Medium')]
param()

$ErrorActionPreference = 'Stop'
$repoRoot = [IO.Path]::GetFullPath($PSScriptRoot)
$repoPrefix = $repoRoot.TrimEnd([IO.Path]::DirectorySeparatorChar) + [IO.Path]::DirectorySeparatorChar

if (!(Test-Path -LiteralPath (Join-Path $repoRoot 'rtl/Riscv.sv') -PathType Leaf)) {
    throw 'Run the cleanup script from its original location in the RISC-V repository.'
}

# Only known simulator outputs are eligible. Software builds are handled by
# make -C sw clean; source files and the root hex images are never targets.
$targets = @('obj_dir', 'obj_dir_wsl', 'sim/proj', 'sim/proj_tb', 'sim/proj_checks', '.Xil')
$rootLogs = Get-ChildItem -LiteralPath $repoRoot -File -Force | Where-Object {
    $_.Name -eq 'vivado.log' -or $_.Name -eq 'vivado.jou' -or $_.Name -like 'vivado_*.backup.*'
}
$targets += @($rootLogs | ForEach-Object { $_.Name })

foreach ($relativePath in $targets) {
    $targetPath = [IO.Path]::GetFullPath((Join-Path $repoRoot $relativePath))
    if (!$targetPath.StartsWith($repoPrefix, [StringComparison]::OrdinalIgnoreCase)) {
        throw "Cleanup target is outside the repository: $targetPath"
    }
    if (!(Test-Path -LiteralPath $targetPath)) { continue }

    # Reject symlinks/junctions in the path so cleanup cannot cross into an
    # external directory even when a generated-output folder has been replaced.
    $ancestor = $targetPath
    while ($ancestor -ne $repoRoot) {
        $item = Get-Item -LiteralPath $ancestor -Force
        if ($item.Attributes -band [IO.FileAttributes]::ReparsePoint) {
            throw "Refusing to clean a symbolic link or junction: $ancestor"
        }
        $ancestor = [IO.Path]::GetDirectoryName($ancestor)
    }

    if ($PSCmdlet.ShouldProcess($targetPath, 'Remove simulator output')) {
        try {
            # Inspect directories without following reparse points, before
            # allowing recursive deletion of any contents.
            $pending = [Collections.Generic.Stack[string]]::new()
            if (Test-Path -LiteralPath $targetPath -PathType Container) { $pending.Push($targetPath) }
            while ($pending.Count -gt 0) {
                foreach ($child in Get-ChildItem -LiteralPath $pending.Pop() -Force) {
                    if ($child.Attributes -band [IO.FileAttributes]::ReparsePoint) {
                        throw "Refusing to clean a symbolic link or junction: $($child.FullName)"
                    }
                    if ($child.PSIsContainer) { $pending.Push($child.FullName) }
                }
            }
            Remove-Item -LiteralPath $targetPath -Recurse -Force
            Write-Output "Removed $relativePath"
        } catch {
            throw "Could not remove ${relativePath}. Close Vivado, xsim and other tools using it, then retry. $($_.Exception.Message)"
        }
    }
}
