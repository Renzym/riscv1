// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vtb_riscv.h for the primary calling header

#ifndef VERILATED_VTB_RISCV___024ROOT_H_
#define VERILATED_VTB_RISCV___024ROOT_H_  // guard

#include "verilated.h"
#include "verilated_timing.h"


class Vtb_riscv__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vtb_riscv___024root final {
  public:

    // DESIGN SPECIFIC STATE
    // Anonymous structures to workaround compiler member-count bugs
    struct {
        CData/*0:0*/ tb_riscv__DOT__Clk;
        CData/*0:0*/ tb_riscv__DOT__Reset;
        CData/*3:0*/ tb_riscv__DOT__dut__DOT__DmemWrEn;
        CData/*6:0*/ __Vfunc_GetOpcode__0__Vfuncout;
        CData/*6:0*/ __Vfunc_GetOpcode__1__Vfuncout;
        CData/*6:0*/ __Vfunc_GetOpcode__2__Vfuncout;
        CData/*6:0*/ __Vfunc_GetOpcode__4__Vfuncout;
        CData/*6:0*/ __Vfunc_GetOpcode__5__Vfuncout;
        CData/*6:0*/ __Vfunc_GetOpcode__6__Vfuncout;
        CData/*6:0*/ __Vfunc_GetOpcode__7__Vfuncout;
        CData/*6:0*/ __Vfunc_GetOpcode__8__Vfuncout;
        CData/*6:0*/ __Vfunc_GetOpcode__9__Vfuncout;
        CData/*6:0*/ __Vfunc_GetOpcode__10__Vfuncout;
        CData/*6:0*/ __Vfunc_GetOpcode__11__Vfuncout;
        CData/*6:0*/ __Vfunc_GetOpcode__12__Vfuncout;
        CData/*6:0*/ __Vfunc_GetOpcode__13__Vfuncout;
        CData/*6:0*/ __Vfunc_GetOpcode__14__Vfuncout;
        CData/*6:0*/ __Vfunc_GetOpcode__15__Vfuncout;
        CData/*6:0*/ __Vfunc_GetOpcode__16__Vfuncout;
        CData/*6:0*/ __Vfunc_GetOpcode__17__Vfuncout;
        CData/*6:0*/ __Vfunc_GetOpcode__18__Vfuncout;
        CData/*6:0*/ __Vfunc_GetOpcode__19__Vfuncout;
        CData/*6:0*/ __Vfunc_GetOpcode__20__Vfuncout;
        CData/*6:0*/ __Vfunc_GetOpcode__21__Vfuncout;
        CData/*6:0*/ __Vfunc_GetOpcode__22__Vfuncout;
        CData/*6:0*/ __Vfunc_GetOpcode__23__Vfuncout;
        CData/*6:0*/ __Vfunc_GetOpcode__24__Vfuncout;
        CData/*6:0*/ __Vfunc_GetOpcode__25__Vfuncout;
        CData/*6:0*/ __Vfunc_GetOpcode__26__Vfuncout;
        CData/*6:0*/ __Vfunc_GetOpcode__27__Vfuncout;
        CData/*6:0*/ __Vfunc_GetOpcode__28__Vfuncout;
        CData/*6:0*/ __Vfunc_GetOpcode__29__Vfuncout;
        CData/*6:0*/ __Vfunc_GetOpcode__30__Vfuncout;
        CData/*6:0*/ __Vfunc_GetOpcode__31__Vfuncout;
        CData/*6:0*/ __Vfunc_GetOpcode__32__Vfuncout;
        CData/*6:0*/ __Vfunc_GetOpcode__33__Vfuncout;
        CData/*6:0*/ __Vfunc_GetOpcode__34__Vfuncout;
        CData/*6:0*/ __Vfunc_GetOpcode__35__Vfuncout;
        CData/*6:0*/ __Vfunc_GetOpcode__36__Vfuncout;
        CData/*6:0*/ __Vfunc_GetOpcode__37__Vfuncout;
        CData/*6:0*/ __Vfunc_GetOpcode__38__Vfuncout;
        CData/*6:0*/ __Vfunc_GetOpcode__39__Vfuncout;
        CData/*6:0*/ __Vfunc_GetOpcode__40__Vfuncout;
        CData/*6:0*/ __Vfunc_GetOpcode__41__Vfuncout;
        CData/*6:0*/ __Vfunc_GetOpcode__42__Vfuncout;
        CData/*6:0*/ __Vfunc_GetOpcode__43__Vfuncout;
        CData/*6:0*/ __Vfunc_GetOpcode__44__Vfuncout;
        CData/*6:0*/ __Vfunc_GetOpcode__45__Vfuncout;
        CData/*6:0*/ __Vfunc_GetOpcode__46__Vfuncout;
        CData/*6:0*/ __Vfunc_GetOpcode__47__Vfuncout;
        CData/*6:0*/ __Vfunc_GetOpcode__48__Vfuncout;
        CData/*6:0*/ __Vfunc_GetOpcode__49__Vfuncout;
        CData/*6:0*/ __Vfunc_GetOpcode__50__Vfuncout;
        CData/*6:0*/ __Vfunc_GetOpcode__51__Vfuncout;
        CData/*6:0*/ __Vfunc_GetOpcode__52__Vfuncout;
        CData/*0:0*/ __VstlFirstIteration;
        CData/*0:0*/ __VstlPhaseResult;
        CData/*0:0*/ __Vtrigprevexpr___TOP__tb_riscv__DOT__Clk__0;
        CData/*0:0*/ __VactPhaseResult;
        CData/*0:0*/ __VinactPhaseResult;
        CData/*0:0*/ __VnbaPhaseResult;
        IData/*31:0*/ tb_riscv__DOT__dut__DOT__Pc;
        IData/*31:0*/ tb_riscv__DOT__dut__DOT__PcNxt;
        IData/*31:0*/ tb_riscv__DOT__dut__DOT__AluOut;
    };
    struct {
        IData/*31:0*/ tb_riscv__DOT__dut__DOT__RegWrData;
        IData/*31:0*/ tb_riscv__DOT__dut__DOT__LoadWbData;
        IData/*31:0*/ tb_riscv__DOT__dut__DOT__DmemWrData;
        VlWide<32>/*1023:0*/ tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs;
        IData/*31:0*/ tb_riscv__DOT__dut__DOT__RegfileInst__DOT__WrDecVec;
        IData/*31:0*/ __Vfunc_GetOpcode__0__RawInstr;
        IData/*31:0*/ __Vfunc_GetOpcode__1__RawInstr;
        IData/*31:0*/ __Vfunc_GetOpcode__2__RawInstr;
        IData/*31:0*/ __Vfunc_GetOpcode__4__RawInstr;
        IData/*31:0*/ __Vfunc_GetOpcode__5__RawInstr;
        IData/*31:0*/ __Vfunc_GetOpcode__6__RawInstr;
        IData/*31:0*/ __Vfunc_GetOpcode__7__RawInstr;
        IData/*31:0*/ __Vfunc_GetOpcode__8__RawInstr;
        IData/*31:0*/ __Vfunc_GetOpcode__9__RawInstr;
        IData/*31:0*/ __Vfunc_GetOpcode__10__RawInstr;
        IData/*31:0*/ __Vfunc_GetOpcode__11__RawInstr;
        IData/*31:0*/ __Vfunc_GetOpcode__12__RawInstr;
        IData/*31:0*/ __Vfunc_GetOpcode__13__RawInstr;
        IData/*31:0*/ __Vfunc_GetOpcode__14__RawInstr;
        IData/*31:0*/ __Vfunc_GetOpcode__15__RawInstr;
        IData/*31:0*/ __Vfunc_GetOpcode__16__RawInstr;
        IData/*31:0*/ __Vfunc_GetOpcode__17__RawInstr;
        IData/*31:0*/ __Vfunc_GetOpcode__18__RawInstr;
        IData/*31:0*/ __Vfunc_GetOpcode__19__RawInstr;
        IData/*31:0*/ __Vfunc_GetOpcode__20__RawInstr;
        IData/*31:0*/ __Vfunc_GetOpcode__21__RawInstr;
        IData/*31:0*/ __Vfunc_GetOpcode__22__RawInstr;
        IData/*31:0*/ __Vfunc_GetOpcode__23__RawInstr;
        IData/*31:0*/ __Vfunc_GetOpcode__24__RawInstr;
        IData/*31:0*/ __Vfunc_GetOpcode__25__RawInstr;
        IData/*31:0*/ __Vfunc_GetOpcode__26__RawInstr;
        IData/*31:0*/ __Vfunc_GetOpcode__27__RawInstr;
        IData/*31:0*/ __Vfunc_GetOpcode__28__RawInstr;
        IData/*31:0*/ __Vfunc_GetOpcode__29__RawInstr;
        IData/*31:0*/ __Vfunc_GetOpcode__30__RawInstr;
        IData/*31:0*/ __Vfunc_GetOpcode__31__RawInstr;
        IData/*31:0*/ __Vfunc_GetOpcode__32__RawInstr;
        IData/*31:0*/ __Vfunc_GetOpcode__33__RawInstr;
        IData/*31:0*/ __Vfunc_GetOpcode__34__RawInstr;
        IData/*31:0*/ __Vfunc_GetOpcode__35__RawInstr;
        IData/*31:0*/ __Vfunc_GetOpcode__36__RawInstr;
        IData/*31:0*/ __Vfunc_GetOpcode__37__RawInstr;
        IData/*31:0*/ __Vfunc_GetOpcode__38__RawInstr;
        IData/*31:0*/ __Vfunc_GetOpcode__39__RawInstr;
        IData/*31:0*/ __Vfunc_GetOpcode__40__RawInstr;
        IData/*31:0*/ __Vfunc_GetOpcode__41__RawInstr;
        IData/*31:0*/ __Vfunc_GetOpcode__42__RawInstr;
        IData/*31:0*/ __Vfunc_GetOpcode__43__RawInstr;
        IData/*31:0*/ __Vfunc_GetOpcode__44__RawInstr;
        IData/*31:0*/ __Vfunc_GetOpcode__45__RawInstr;
        IData/*31:0*/ __Vfunc_GetOpcode__46__RawInstr;
        IData/*31:0*/ __Vfunc_GetOpcode__47__RawInstr;
        IData/*31:0*/ __Vfunc_GetOpcode__48__RawInstr;
        IData/*31:0*/ __Vfunc_GetOpcode__49__RawInstr;
        IData/*31:0*/ __Vfunc_GetOpcode__50__RawInstr;
        IData/*31:0*/ __Vfunc_GetOpcode__51__RawInstr;
        IData/*31:0*/ __Vfunc_GetOpcode__52__RawInstr;
        IData/*31:0*/ __VactIterCount;
        IData/*31:0*/ __VinactIterCount;
        IData/*31:0*/ __Vi;
        VlUnpacked<IData/*31:0*/, 512> tb_riscv__DOT__dut__DOT__ProgMemInst__DOT__RamArray;
        VlUnpacked<IData/*31:0*/, 512> tb_riscv__DOT__dut__DOT__DataMemInst__DOT__RamArray;
        VlUnpacked<QData/*63:0*/, 1> __VstlTriggered;
        VlUnpacked<QData/*63:0*/, 1> __VactTriggered;
    };
    struct {
        VlUnpacked<QData/*63:0*/, 1> __VactTriggeredAcc;
        VlUnpacked<QData/*63:0*/, 1> __VnbaTriggered;
    };
    VlDelayScheduler __VdlySched;
    VlTriggerScheduler __VtrigSched_h71169501__0;

    // INTERNAL VARIABLES
    Vtb_riscv__Syms* vlSymsp;
    const char* vlNamep;

    // CONSTRUCTORS
    Vtb_riscv___024root(Vtb_riscv__Syms* symsp, const char* namep);
    ~Vtb_riscv___024root();
    VL_UNCOPYABLE(Vtb_riscv___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
