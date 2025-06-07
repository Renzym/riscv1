module Riscv (
    input  logic                  Clk,
    input  logic                  Reset
)


    Regfile #(
    .ADDR_WIDTH(5),
    .DATA_WIDTH(32)
    )
    RegfileInst (
    .Clk        ,
    .Reset      ,
    .RdAddr1    ,
    .RdAddr2    ,
    .RdData1    ,
    .RdData2    ,
    .WrAddr     ,
    .WrData     ,
    .WrEn       
    )

endmodule