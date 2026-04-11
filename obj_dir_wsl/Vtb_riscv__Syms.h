// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table internal header
//
// Internal details; most calling programs do not need this header,
// unless using verilator public meta comments.

#ifndef VERILATED_VTB_RISCV__SYMS_H_
#define VERILATED_VTB_RISCV__SYMS_H_  // guard

#include "verilated.h"

// INCLUDE MODEL CLASS

#include "Vtb_riscv.h"

// INCLUDE MODULE CLASSES
#include "Vtb_riscv___024root.h"
#include "Vtb_riscv___024unit.h"

// SYMS CLASS (contains all model state)
class alignas(VL_CACHE_LINE_BYTES) Vtb_riscv__Syms final : public VerilatedSyms {
  public:
    // INTERNAL STATE
    Vtb_riscv* const __Vm_modelp;
    VlDeleter __Vm_deleter;
    bool __Vm_didInit = false;

    // MODULE INSTANCE STATE
    Vtb_riscv___024root            TOP;

    // CONSTRUCTORS
    Vtb_riscv__Syms(VerilatedContext* contextp, const char* namep, Vtb_riscv* modelp);
    ~Vtb_riscv__Syms();

    // METHODS
    const char* name() const { return TOP.vlNamep; }
};

#endif  // guard
