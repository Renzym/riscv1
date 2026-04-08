// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtb_riscv.h for the primary calling header

#include "Vtb_riscv__pch.h"

VlCoroutine Vtb_riscv___024root___eval_initial__TOP__Vtiming__0(Vtb_riscv___024root* vlSelf);
VlCoroutine Vtb_riscv___024root___eval_initial__TOP__Vtiming__1(Vtb_riscv___024root* vlSelf);

void Vtb_riscv___024root___eval_initial(Vtb_riscv___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_riscv___024root___eval_initial\n"); );
    Vtb_riscv__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[0U] = 0U;
    VL_READMEM_N(true, 32, 512, 0, "Program.hex"s,  &(vlSelfRef.tb_riscv__DOT__dut__DOT__ProgMemInst__DOT__RamArray)
                 , 0U, 0x000000ffU);
    VL_READMEM_N(true, 32, 512, 0, "Data.hex"s,  &(vlSelfRef.tb_riscv__DOT__dut__DOT__DataMemInst__DOT__RamArray)
                 , 0U, 0x000000ffU);
    Vtb_riscv___024root___eval_initial__TOP__Vtiming__0(vlSelf);
    Vtb_riscv___024root___eval_initial__TOP__Vtiming__1(vlSelf);
}

void Vtb_riscv___024root____VbeforeTrig_h71169501__0(Vtb_riscv___024root* vlSelf, const char* __VeventDescription);

VlCoroutine Vtb_riscv___024root___eval_initial__TOP__Vtiming__0(Vtb_riscv___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_riscv___024root___eval_initial__TOP__Vtiming__0\n"); );
    Vtb_riscv__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ tb_riscv__DOT__unnamedblk1_1__DOT____Vrepeat0;
    tb_riscv__DOT__unnamedblk1_1__DOT____Vrepeat0 = 0;
    IData/*31:0*/ tb_riscv__DOT__unnamedblk1_2__DOT____Vrepeat1;
    tb_riscv__DOT__unnamedblk1_2__DOT____Vrepeat1 = 0;
    // Body
    vlSelfRef.tb_riscv__DOT__Clk = 0U;
    vlSelfRef.tb_riscv__DOT__Reset = 1U;
    tb_riscv__DOT__unnamedblk1_1__DOT____Vrepeat0 = 2U;
    while (VL_LTS_III(32, 0U, tb_riscv__DOT__unnamedblk1_1__DOT____Vrepeat0)) {
        Vtb_riscv___024root____VbeforeTrig_h71169501__0(vlSelf, 
                                                        "@(posedge tb_riscv.Clk)");
        co_await vlSelfRef.__VtrigSched_h71169501__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_riscv.Clk)", 
                                                             "tb_riscv.sv", 
                                                             17);
        tb_riscv__DOT__unnamedblk1_1__DOT____Vrepeat0 
            = (tb_riscv__DOT__unnamedblk1_1__DOT____Vrepeat0 
               - (IData)(1U));
    }
    vlSelfRef.tb_riscv__DOT__Reset = 0U;
    tb_riscv__DOT__unnamedblk1_2__DOT____Vrepeat1 = 0x00000019U;
    while (VL_LTS_III(32, 0U, tb_riscv__DOT__unnamedblk1_2__DOT____Vrepeat1)) {
        Vtb_riscv___024root____VbeforeTrig_h71169501__0(vlSelf, 
                                                        "@(posedge tb_riscv.Clk)");
        co_await vlSelfRef.__VtrigSched_h71169501__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_riscv.Clk)", 
                                                             "tb_riscv.sv", 
                                                             21);
        tb_riscv__DOT__unnamedblk1_2__DOT____Vrepeat1 
            = (tb_riscv__DOT__unnamedblk1_2__DOT____Vrepeat1 
               - (IData)(1U));
    }
    if (VL_UNLIKELY(((5U != vlSelfRef.tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[1U])))) {
        VL_WRITEF_NX("[%0t] %%Fatal: tb_riscv.sv:25: Assertion failed in %Ntb_riscv: x1 mismatch. Expected 5, got %0#\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     32,vlSelfRef.tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[1U]);
        VL_STOP_MT("tb_riscv.sv", 25, "", false);
    }
    if (VL_UNLIKELY(((0x0000000aU != vlSelfRef.tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[2U])))) {
        VL_WRITEF_NX("[%0t] %%Fatal: tb_riscv.sv:28: Assertion failed in %Ntb_riscv: x2 mismatch. Expected 10, got %0#\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     32,vlSelfRef.tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[2U]);
        VL_STOP_MT("tb_riscv.sv", 28, "", false);
    }
    if (VL_UNLIKELY(((0x0000000fU != vlSelfRef.tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[3U])))) {
        VL_WRITEF_NX("[%0t] %%Fatal: tb_riscv.sv:31: Assertion failed in %Ntb_riscv: x3 mismatch. Expected 15, got %0#\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     32,vlSelfRef.tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[3U]);
        VL_STOP_MT("tb_riscv.sv", 31, "", false);
    }
    if (VL_UNLIKELY(((0x0000000fU != vlSelfRef.tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[4U])))) {
        VL_WRITEF_NX("[%0t] %%Fatal: tb_riscv.sv:34: Assertion failed in %Ntb_riscv: x4 mismatch. Expected 15, got %0#\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     32,vlSelfRef.tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[4U]);
        VL_STOP_MT("tb_riscv.sv", 34, "", false);
    }
    if (VL_UNLIKELY(((0U != vlSelfRef.tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[5U])))) {
        VL_WRITEF_NX("[%0t] %%Fatal: tb_riscv.sv:37: Assertion failed in %Ntb_riscv: x5 mismatch. Branch/JAL skip failed, got %0#\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     32,vlSelfRef.tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[5U]);
        VL_STOP_MT("tb_riscv.sv", 37, "", false);
    }
    if (VL_UNLIKELY(((0x0000001cU != vlSelfRef.tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[6U])))) {
        VL_WRITEF_NX("[%0t] %%Fatal: tb_riscv.sv:40: Assertion failed in %Ntb_riscv: x6 mismatch. AUIPC expected 28, got %0#\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     32,vlSelfRef.tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[6U]);
        VL_STOP_MT("tb_riscv.sv", 40, "", false);
    }
    if (VL_UNLIKELY(((0x00000024U != vlSelfRef.tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[7U])))) {
        VL_WRITEF_NX("[%0t] %%Fatal: tb_riscv.sv:43: Assertion failed in %Ntb_riscv: x7 mismatch. JAL link expected 36, got %0#\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     32,vlSelfRef.tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[7U]);
        VL_STOP_MT("tb_riscv.sv", 43, "", false);
    }
    if (VL_UNLIKELY(((0x12345000U != vlSelfRef.tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[8U])))) {
        VL_WRITEF_NX("[%0t] %%Fatal: tb_riscv.sv:46: Assertion failed in %Ntb_riscv: x8 mismatch. LUI expected 0x12345000, got 0x%08x\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     32,vlSelfRef.tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[8U]);
        VL_STOP_MT("tb_riscv.sv", 46, "", false);
    }
    if (VL_UNLIKELY(((0x00000030U != vlSelfRef.tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[9U])))) {
        VL_WRITEF_NX("[%0t] %%Fatal: tb_riscv.sv:49: Assertion failed in %Ntb_riscv: x9 mismatch. JALR link expected 48, got %0#\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     32,vlSelfRef.tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[9U]);
        VL_STOP_MT("tb_riscv.sv", 49, "", false);
    }
    VL_WRITEF_NX("PASS: Stage 1 smoke test passed.\n",0);
    VL_FINISH_MT("tb_riscv.sv", 52, "");
    co_return;
}

VlCoroutine Vtb_riscv___024root___eval_initial__TOP__Vtiming__1(Vtb_riscv___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_riscv___024root___eval_initial__TOP__Vtiming__1\n"); );
    Vtb_riscv__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    while (VL_LIKELY(!vlSymsp->_vm_contextp__->gotFinish())) {
        co_await vlSelfRef.__VdlySched.delay(0x0000000000001388ULL, 
                                             nullptr, 
                                             "tb_riscv.sv", 
                                             12);
        vlSelfRef.tb_riscv__DOT__Clk = (1U & (~ (IData)(vlSelfRef.tb_riscv__DOT__Clk)));
    }
    co_return;
}

void Vtb_riscv___024root___eval_triggers_vec__act(Vtb_riscv___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_riscv___024root___eval_triggers_vec__act\n"); );
    Vtb_riscv__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VactTriggered[0U] = (QData)((IData)(
                                                    ((vlSelfRef.__VdlySched.awaitingCurrentTime() 
                                                      << 1U) 
                                                     | ((IData)(vlSelfRef.tb_riscv__DOT__Clk) 
                                                        & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_riscv__DOT__Clk__0))))));
    vlSelfRef.__Vtrigprevexpr___TOP__tb_riscv__DOT__Clk__0 
        = vlSelfRef.tb_riscv__DOT__Clk;
}

bool Vtb_riscv___024root___trigger_anySet__act(const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_riscv___024root___trigger_anySet__act\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        if (in[n]) {
            return (1U);
        }
        n = ((IData)(1U) + n);
    } while ((1U > n));
    return (0U);
}

extern const VlWide<32>/*1023:0*/ Vtb_riscv__ConstPool__CONST_hd6b7ba52_0;

void Vtb_riscv___024root___nba_sequent__TOP__0(Vtb_riscv___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_riscv___024root___nba_sequent__TOP__0\n"); );
    Vtb_riscv__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ tb_riscv__DOT__dut__DOT__Instr;
    tb_riscv__DOT__dut__DOT__Instr = 0;
    CData/*0:0*/ tb_riscv__DOT__dut__DOT__JalPcSel;
    tb_riscv__DOT__dut__DOT__JalPcSel = 0;
    CData/*0:0*/ tb_riscv__DOT__dut__DOT__BrPcSel;
    tb_riscv__DOT__dut__DOT__BrPcSel = 0;
    IData/*31:0*/ tb_riscv__DOT__dut__DOT__ImmExt;
    tb_riscv__DOT__dut__DOT__ImmExt = 0;
    IData/*31:0*/ tb_riscv__DOT__dut__DOT__AluOp1;
    tb_riscv__DOT__dut__DOT__AluOp1 = 0;
    IData/*31:0*/ tb_riscv__DOT__dut__DOT__AluOp2;
    tb_riscv__DOT__dut__DOT__AluOp2 = 0;
    CData/*0:0*/ tb_riscv__DOT__dut__DOT__Op2Sel;
    tb_riscv__DOT__dut__DOT__Op2Sel = 0;
    CData/*0:0*/ tb_riscv__DOT__dut__DOT__AuipcSel;
    tb_riscv__DOT__dut__DOT__AuipcSel = 0;
    CData/*1:0*/ tb_riscv__DOT__dut__DOT__RegWb;
    tb_riscv__DOT__dut__DOT__RegWb = 0;
    CData/*0:0*/ tb_riscv__DOT__dut__DOT__RegWrEn;
    tb_riscv__DOT__dut__DOT__RegWrEn = 0;
    CData/*0:0*/ tb_riscv__DOT__dut__DOT__AluInst__DOT__Subtract;
    tb_riscv__DOT__dut__DOT__AluInst__DOT__Subtract = 0;
    IData/*31:0*/ tb_riscv__DOT__dut__DOT__AluInst__DOT__AddrOut;
    tb_riscv__DOT__dut__DOT__AluInst__DOT__AddrOut = 0;
    IData/*31:0*/ tb_riscv__DOT__dut__DOT__AluInst__DOT__ShiftOut;
    tb_riscv__DOT__dut__DOT__AluInst__DOT__ShiftOut = 0;
    IData/*31:0*/ tb_riscv__DOT__dut__DOT__AluInst__DOT__LogicOut;
    tb_riscv__DOT__dut__DOT__AluInst__DOT__LogicOut = 0;
    CData/*0:0*/ tb_riscv__DOT__dut__DOT__AluInst__DOT__IsLessThan;
    tb_riscv__DOT__dut__DOT__AluInst__DOT__IsLessThan = 0;
    CData/*0:0*/ tb_riscv__DOT__dut__DOT__AluInst__DOT__IsLessThanUnsigned;
    tb_riscv__DOT__dut__DOT__AluInst__DOT__IsLessThanUnsigned = 0;
    IData/*31:0*/ __Vfunc_GetImmediate__0__Vfuncout;
    __Vfunc_GetImmediate__0__Vfuncout = 0;
    IData/*31:0*/ __Vfunc_GetImmediate__0__RawInstr;
    __Vfunc_GetImmediate__0__RawInstr = 0;
    IData/*31:0*/ __Vfunc_GetImmediate__0__Instr;
    __Vfunc_GetImmediate__0__Instr = 0;
    VlWide<32>/*1023:0*/ __Vdly__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs;
    VL_ZERO_W(1024, __Vdly__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs);
    VlWide<32>/*1023:0*/ __VdlyMask__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs;
    VL_ZERO_W(1024, __VdlyMask__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs);
    CData/*7:0*/ __VdlyVal__tb_riscv__DOT__dut__DOT__DataMemInst__DOT__RamArray__v0;
    __VdlyVal__tb_riscv__DOT__dut__DOT__DataMemInst__DOT__RamArray__v0 = 0;
    SData/*8:0*/ __VdlyDim0__tb_riscv__DOT__dut__DOT__DataMemInst__DOT__RamArray__v0;
    __VdlyDim0__tb_riscv__DOT__dut__DOT__DataMemInst__DOT__RamArray__v0 = 0;
    CData/*0:0*/ __VdlySet__tb_riscv__DOT__dut__DOT__DataMemInst__DOT__RamArray__v0;
    __VdlySet__tb_riscv__DOT__dut__DOT__DataMemInst__DOT__RamArray__v0 = 0;
    CData/*7:0*/ __VdlyVal__tb_riscv__DOT__dut__DOT__DataMemInst__DOT__RamArray__v1;
    __VdlyVal__tb_riscv__DOT__dut__DOT__DataMemInst__DOT__RamArray__v1 = 0;
    SData/*8:0*/ __VdlyDim0__tb_riscv__DOT__dut__DOT__DataMemInst__DOT__RamArray__v1;
    __VdlyDim0__tb_riscv__DOT__dut__DOT__DataMemInst__DOT__RamArray__v1 = 0;
    CData/*0:0*/ __VdlySet__tb_riscv__DOT__dut__DOT__DataMemInst__DOT__RamArray__v1;
    __VdlySet__tb_riscv__DOT__dut__DOT__DataMemInst__DOT__RamArray__v1 = 0;
    CData/*7:0*/ __VdlyVal__tb_riscv__DOT__dut__DOT__DataMemInst__DOT__RamArray__v2;
    __VdlyVal__tb_riscv__DOT__dut__DOT__DataMemInst__DOT__RamArray__v2 = 0;
    SData/*8:0*/ __VdlyDim0__tb_riscv__DOT__dut__DOT__DataMemInst__DOT__RamArray__v2;
    __VdlyDim0__tb_riscv__DOT__dut__DOT__DataMemInst__DOT__RamArray__v2 = 0;
    CData/*0:0*/ __VdlySet__tb_riscv__DOT__dut__DOT__DataMemInst__DOT__RamArray__v2;
    __VdlySet__tb_riscv__DOT__dut__DOT__DataMemInst__DOT__RamArray__v2 = 0;
    CData/*7:0*/ __VdlyVal__tb_riscv__DOT__dut__DOT__DataMemInst__DOT__RamArray__v3;
    __VdlyVal__tb_riscv__DOT__dut__DOT__DataMemInst__DOT__RamArray__v3 = 0;
    SData/*8:0*/ __VdlyDim0__tb_riscv__DOT__dut__DOT__DataMemInst__DOT__RamArray__v3;
    __VdlyDim0__tb_riscv__DOT__dut__DOT__DataMemInst__DOT__RamArray__v3 = 0;
    CData/*0:0*/ __VdlySet__tb_riscv__DOT__dut__DOT__DataMemInst__DOT__RamArray__v3;
    __VdlySet__tb_riscv__DOT__dut__DOT__DataMemInst__DOT__RamArray__v3 = 0;
    // Body
    __VdlySet__tb_riscv__DOT__dut__DOT__DataMemInst__DOT__RamArray__v0 = 0U;
    __VdlySet__tb_riscv__DOT__dut__DOT__DataMemInst__DOT__RamArray__v1 = 0U;
    __VdlySet__tb_riscv__DOT__dut__DOT__DataMemInst__DOT__RamArray__v2 = 0U;
    __VdlySet__tb_riscv__DOT__dut__DOT__DataMemInst__DOT__RamArray__v3 = 0U;
    if (vlSelfRef.tb_riscv__DOT__Reset) {
        __Vdly__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[1U] = 0U;
        __VdlyMask__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[1U] = 0xffffffffU;
        __Vdly__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[2U] = 0U;
        __VdlyMask__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[2U] = 0xffffffffU;
        __Vdly__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[3U] = 0U;
        __VdlyMask__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[3U] = 0xffffffffU;
        __Vdly__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[4U] = 0U;
        __VdlyMask__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[4U] = 0xffffffffU;
        __Vdly__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[5U] = 0U;
        __VdlyMask__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[5U] = 0xffffffffU;
        __Vdly__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[6U] = 0U;
        __VdlyMask__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[6U] = 0xffffffffU;
        __Vdly__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[7U] = 0U;
        __VdlyMask__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[7U] = 0xffffffffU;
        __Vdly__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[8U] = 0U;
        __VdlyMask__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[8U] = 0xffffffffU;
        __Vdly__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[9U] = 0U;
        __VdlyMask__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[9U] = 0xffffffffU;
        __Vdly__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[10U] = 0U;
        __VdlyMask__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[10U] = 0xffffffffU;
        __Vdly__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[11U] = 0U;
        __VdlyMask__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[11U] = 0xffffffffU;
        __Vdly__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[12U] = 0U;
        __VdlyMask__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[12U] = 0xffffffffU;
        __Vdly__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[13U] = 0U;
        __VdlyMask__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[13U] = 0xffffffffU;
        __Vdly__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[14U] = 0U;
        __VdlyMask__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[14U] = 0xffffffffU;
        __Vdly__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[15U] = 0U;
        __VdlyMask__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[15U] = 0xffffffffU;
        __Vdly__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[16U] = 0U;
        __VdlyMask__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[16U] = 0xffffffffU;
        __Vdly__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[17U] = 0U;
        __VdlyMask__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[17U] = 0xffffffffU;
        __Vdly__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[18U] = 0U;
        __VdlyMask__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[18U] = 0xffffffffU;
        __Vdly__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[19U] = 0U;
        __VdlyMask__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[19U] = 0xffffffffU;
        __Vdly__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[20U] = 0U;
        __VdlyMask__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[20U] = 0xffffffffU;
        __Vdly__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[21U] = 0U;
        __VdlyMask__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[21U] = 0xffffffffU;
        __Vdly__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[22U] = 0U;
        __VdlyMask__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[22U] = 0xffffffffU;
        __Vdly__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[23U] = 0U;
        __VdlyMask__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[23U] = 0xffffffffU;
        __Vdly__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[24U] = 0U;
        __VdlyMask__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[24U] = 0xffffffffU;
        __Vdly__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[25U] = 0U;
        __VdlyMask__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[25U] = 0xffffffffU;
        __Vdly__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[26U] = 0U;
        __VdlyMask__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[26U] = 0xffffffffU;
        __Vdly__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[27U] = 0U;
        __VdlyMask__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[27U] = 0xffffffffU;
        __Vdly__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[28U] = 0U;
        __VdlyMask__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[28U] = 0xffffffffU;
        __Vdly__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[29U] = 0U;
        __VdlyMask__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[29U] = 0xffffffffU;
        __Vdly__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[30U] = 0U;
        __VdlyMask__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[30U] = 0xffffffffU;
        __Vdly__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[31U] = 0U;
        __VdlyMask__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[31U] = 0xffffffffU;
        vlSelfRef.tb_riscv__DOT__dut__DOT__Pc = 0U;
    } else {
        if ((2U & vlSelfRef.tb_riscv__DOT__dut__DOT__RegfileInst__DOT__WrDecVec)) {
            __Vdly__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[1U] 
                = vlSelfRef.tb_riscv__DOT__dut__DOT__RegWrData;
            __VdlyMask__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[1U] = 0xffffffffU;
        }
        if ((4U & vlSelfRef.tb_riscv__DOT__dut__DOT__RegfileInst__DOT__WrDecVec)) {
            __Vdly__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[2U] 
                = vlSelfRef.tb_riscv__DOT__dut__DOT__RegWrData;
            __VdlyMask__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[2U] = 0xffffffffU;
        }
        if ((8U & vlSelfRef.tb_riscv__DOT__dut__DOT__RegfileInst__DOT__WrDecVec)) {
            __Vdly__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[3U] 
                = vlSelfRef.tb_riscv__DOT__dut__DOT__RegWrData;
            __VdlyMask__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[3U] = 0xffffffffU;
        }
        if ((0x00000010U & vlSelfRef.tb_riscv__DOT__dut__DOT__RegfileInst__DOT__WrDecVec)) {
            __Vdly__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[4U] 
                = vlSelfRef.tb_riscv__DOT__dut__DOT__RegWrData;
            __VdlyMask__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[4U] = 0xffffffffU;
        }
        if ((0x00000020U & vlSelfRef.tb_riscv__DOT__dut__DOT__RegfileInst__DOT__WrDecVec)) {
            __Vdly__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[5U] 
                = vlSelfRef.tb_riscv__DOT__dut__DOT__RegWrData;
            __VdlyMask__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[5U] = 0xffffffffU;
        }
        if ((0x00000040U & vlSelfRef.tb_riscv__DOT__dut__DOT__RegfileInst__DOT__WrDecVec)) {
            __Vdly__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[6U] 
                = vlSelfRef.tb_riscv__DOT__dut__DOT__RegWrData;
            __VdlyMask__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[6U] = 0xffffffffU;
        }
        if ((0x00000080U & vlSelfRef.tb_riscv__DOT__dut__DOT__RegfileInst__DOT__WrDecVec)) {
            __Vdly__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[7U] 
                = vlSelfRef.tb_riscv__DOT__dut__DOT__RegWrData;
            __VdlyMask__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[7U] = 0xffffffffU;
        }
        if ((0x00000100U & vlSelfRef.tb_riscv__DOT__dut__DOT__RegfileInst__DOT__WrDecVec)) {
            __Vdly__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[8U] 
                = vlSelfRef.tb_riscv__DOT__dut__DOT__RegWrData;
            __VdlyMask__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[8U] = 0xffffffffU;
        }
        if ((0x00000200U & vlSelfRef.tb_riscv__DOT__dut__DOT__RegfileInst__DOT__WrDecVec)) {
            __Vdly__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[9U] 
                = vlSelfRef.tb_riscv__DOT__dut__DOT__RegWrData;
            __VdlyMask__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[9U] = 0xffffffffU;
        }
        if ((0x00000400U & vlSelfRef.tb_riscv__DOT__dut__DOT__RegfileInst__DOT__WrDecVec)) {
            __Vdly__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[10U] 
                = vlSelfRef.tb_riscv__DOT__dut__DOT__RegWrData;
            __VdlyMask__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[10U] = 0xffffffffU;
        }
        if ((0x00000800U & vlSelfRef.tb_riscv__DOT__dut__DOT__RegfileInst__DOT__WrDecVec)) {
            __Vdly__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[11U] 
                = vlSelfRef.tb_riscv__DOT__dut__DOT__RegWrData;
            __VdlyMask__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[11U] = 0xffffffffU;
        }
        if ((0x00001000U & vlSelfRef.tb_riscv__DOT__dut__DOT__RegfileInst__DOT__WrDecVec)) {
            __Vdly__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[12U] 
                = vlSelfRef.tb_riscv__DOT__dut__DOT__RegWrData;
            __VdlyMask__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[12U] = 0xffffffffU;
        }
        if ((0x00002000U & vlSelfRef.tb_riscv__DOT__dut__DOT__RegfileInst__DOT__WrDecVec)) {
            __Vdly__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[13U] 
                = vlSelfRef.tb_riscv__DOT__dut__DOT__RegWrData;
            __VdlyMask__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[13U] = 0xffffffffU;
        }
        if ((0x00004000U & vlSelfRef.tb_riscv__DOT__dut__DOT__RegfileInst__DOT__WrDecVec)) {
            __Vdly__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[14U] 
                = vlSelfRef.tb_riscv__DOT__dut__DOT__RegWrData;
            __VdlyMask__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[14U] = 0xffffffffU;
        }
        if ((0x00008000U & vlSelfRef.tb_riscv__DOT__dut__DOT__RegfileInst__DOT__WrDecVec)) {
            __Vdly__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[15U] 
                = vlSelfRef.tb_riscv__DOT__dut__DOT__RegWrData;
            __VdlyMask__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[15U] = 0xffffffffU;
        }
        if ((0x00010000U & vlSelfRef.tb_riscv__DOT__dut__DOT__RegfileInst__DOT__WrDecVec)) {
            __Vdly__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[16U] 
                = vlSelfRef.tb_riscv__DOT__dut__DOT__RegWrData;
            __VdlyMask__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[16U] = 0xffffffffU;
        }
        if ((0x00020000U & vlSelfRef.tb_riscv__DOT__dut__DOT__RegfileInst__DOT__WrDecVec)) {
            __Vdly__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[17U] 
                = vlSelfRef.tb_riscv__DOT__dut__DOT__RegWrData;
            __VdlyMask__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[17U] = 0xffffffffU;
        }
        if ((0x00040000U & vlSelfRef.tb_riscv__DOT__dut__DOT__RegfileInst__DOT__WrDecVec)) {
            __Vdly__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[18U] 
                = vlSelfRef.tb_riscv__DOT__dut__DOT__RegWrData;
            __VdlyMask__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[18U] = 0xffffffffU;
        }
        if ((0x00080000U & vlSelfRef.tb_riscv__DOT__dut__DOT__RegfileInst__DOT__WrDecVec)) {
            __Vdly__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[19U] 
                = vlSelfRef.tb_riscv__DOT__dut__DOT__RegWrData;
            __VdlyMask__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[19U] = 0xffffffffU;
        }
        if ((0x00100000U & vlSelfRef.tb_riscv__DOT__dut__DOT__RegfileInst__DOT__WrDecVec)) {
            __Vdly__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[20U] 
                = vlSelfRef.tb_riscv__DOT__dut__DOT__RegWrData;
            __VdlyMask__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[20U] = 0xffffffffU;
        }
        if ((0x00200000U & vlSelfRef.tb_riscv__DOT__dut__DOT__RegfileInst__DOT__WrDecVec)) {
            __Vdly__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[21U] 
                = vlSelfRef.tb_riscv__DOT__dut__DOT__RegWrData;
            __VdlyMask__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[21U] = 0xffffffffU;
        }
        if ((0x00400000U & vlSelfRef.tb_riscv__DOT__dut__DOT__RegfileInst__DOT__WrDecVec)) {
            __Vdly__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[22U] 
                = vlSelfRef.tb_riscv__DOT__dut__DOT__RegWrData;
            __VdlyMask__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[22U] = 0xffffffffU;
        }
        if ((0x00800000U & vlSelfRef.tb_riscv__DOT__dut__DOT__RegfileInst__DOT__WrDecVec)) {
            __Vdly__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[23U] 
                = vlSelfRef.tb_riscv__DOT__dut__DOT__RegWrData;
            __VdlyMask__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[23U] = 0xffffffffU;
        }
        if ((0x01000000U & vlSelfRef.tb_riscv__DOT__dut__DOT__RegfileInst__DOT__WrDecVec)) {
            __Vdly__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[24U] 
                = vlSelfRef.tb_riscv__DOT__dut__DOT__RegWrData;
            __VdlyMask__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[24U] = 0xffffffffU;
        }
        if ((0x02000000U & vlSelfRef.tb_riscv__DOT__dut__DOT__RegfileInst__DOT__WrDecVec)) {
            __Vdly__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[25U] 
                = vlSelfRef.tb_riscv__DOT__dut__DOT__RegWrData;
            __VdlyMask__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[25U] = 0xffffffffU;
        }
        if ((0x04000000U & vlSelfRef.tb_riscv__DOT__dut__DOT__RegfileInst__DOT__WrDecVec)) {
            __Vdly__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[26U] 
                = vlSelfRef.tb_riscv__DOT__dut__DOT__RegWrData;
            __VdlyMask__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[26U] = 0xffffffffU;
        }
        if ((0x08000000U & vlSelfRef.tb_riscv__DOT__dut__DOT__RegfileInst__DOT__WrDecVec)) {
            __Vdly__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[27U] 
                = vlSelfRef.tb_riscv__DOT__dut__DOT__RegWrData;
            __VdlyMask__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[27U] = 0xffffffffU;
        }
        if ((0x10000000U & vlSelfRef.tb_riscv__DOT__dut__DOT__RegfileInst__DOT__WrDecVec)) {
            __Vdly__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[28U] 
                = vlSelfRef.tb_riscv__DOT__dut__DOT__RegWrData;
            __VdlyMask__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[28U] = 0xffffffffU;
        }
        if ((0x20000000U & vlSelfRef.tb_riscv__DOT__dut__DOT__RegfileInst__DOT__WrDecVec)) {
            __Vdly__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[29U] 
                = vlSelfRef.tb_riscv__DOT__dut__DOT__RegWrData;
            __VdlyMask__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[29U] = 0xffffffffU;
        }
        if ((0x40000000U & vlSelfRef.tb_riscv__DOT__dut__DOT__RegfileInst__DOT__WrDecVec)) {
            __Vdly__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[30U] 
                = vlSelfRef.tb_riscv__DOT__dut__DOT__RegWrData;
            __VdlyMask__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[30U] = 0xffffffffU;
        }
        if ((vlSelfRef.tb_riscv__DOT__dut__DOT__RegfileInst__DOT__WrDecVec 
             >> 0x1fU)) {
            __Vdly__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[31U] 
                = vlSelfRef.tb_riscv__DOT__dut__DOT__RegWrData;
            __VdlyMask__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[31U] = 0xffffffffU;
        }
        vlSelfRef.tb_riscv__DOT__dut__DOT__Pc = vlSelfRef.tb_riscv__DOT__dut__DOT__PcNxt;
    }
    if (vlSelfRef.tb_riscv__DOT__dut__DOT__DmemWr) {
        __VdlyVal__tb_riscv__DOT__dut__DOT__DataMemInst__DOT__RamArray__v0 
            = (0x000000ffU & vlSelfRef.tb_riscv__DOT__dut__DOT__RegSrc2);
        __VdlyDim0__tb_riscv__DOT__dut__DOT__DataMemInst__DOT__RamArray__v0 
            = (0x000001ffU & vlSelfRef.tb_riscv__DOT__dut__DOT__AluOut);
        __VdlySet__tb_riscv__DOT__dut__DOT__DataMemInst__DOT__RamArray__v0 = 1U;
        __VdlyVal__tb_riscv__DOT__dut__DOT__DataMemInst__DOT__RamArray__v1 
            = (0x000000ffU & (vlSelfRef.tb_riscv__DOT__dut__DOT__RegSrc2 
                              >> 8U));
        __VdlyDim0__tb_riscv__DOT__dut__DOT__DataMemInst__DOT__RamArray__v1 
            = (0x000001ffU & vlSelfRef.tb_riscv__DOT__dut__DOT__AluOut);
        __VdlySet__tb_riscv__DOT__dut__DOT__DataMemInst__DOT__RamArray__v1 = 1U;
        __VdlyVal__tb_riscv__DOT__dut__DOT__DataMemInst__DOT__RamArray__v2 
            = (0x000000ffU & (vlSelfRef.tb_riscv__DOT__dut__DOT__RegSrc2 
                              >> 0x10U));
        __VdlyDim0__tb_riscv__DOT__dut__DOT__DataMemInst__DOT__RamArray__v2 
            = (0x000001ffU & vlSelfRef.tb_riscv__DOT__dut__DOT__AluOut);
        __VdlySet__tb_riscv__DOT__dut__DOT__DataMemInst__DOT__RamArray__v2 = 1U;
        __VdlyVal__tb_riscv__DOT__dut__DOT__DataMemInst__DOT__RamArray__v3 
            = (vlSelfRef.tb_riscv__DOT__dut__DOT__RegSrc2 
               >> 0x18U);
        __VdlyDim0__tb_riscv__DOT__dut__DOT__DataMemInst__DOT__RamArray__v3 
            = (0x000001ffU & vlSelfRef.tb_riscv__DOT__dut__DOT__AluOut);
        __VdlySet__tb_riscv__DOT__dut__DOT__DataMemInst__DOT__RamArray__v3 = 1U;
    }
    vlSelfRef.tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[0U] 
        = ((__Vdly__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[0U] 
            & __VdlyMask__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[0U]) 
           | (vlSelfRef.tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[0U] 
              & (~ __VdlyMask__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[0U])));
    vlSelfRef.tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[1U] 
        = ((__Vdly__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[1U] 
            & __VdlyMask__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[1U]) 
           | (vlSelfRef.tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[1U] 
              & (~ __VdlyMask__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[1U])));
    vlSelfRef.tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[2U] 
        = ((__Vdly__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[2U] 
            & __VdlyMask__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[2U]) 
           | (vlSelfRef.tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[2U] 
              & (~ __VdlyMask__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[2U])));
    vlSelfRef.tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[3U] 
        = ((__Vdly__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[3U] 
            & __VdlyMask__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[3U]) 
           | (vlSelfRef.tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[3U] 
              & (~ __VdlyMask__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[3U])));
    vlSelfRef.tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[4U] 
        = ((__Vdly__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[4U] 
            & __VdlyMask__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[4U]) 
           | (vlSelfRef.tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[4U] 
              & (~ __VdlyMask__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[4U])));
    vlSelfRef.tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[5U] 
        = ((__Vdly__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[5U] 
            & __VdlyMask__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[5U]) 
           | (vlSelfRef.tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[5U] 
              & (~ __VdlyMask__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[5U])));
    vlSelfRef.tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[6U] 
        = ((__Vdly__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[6U] 
            & __VdlyMask__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[6U]) 
           | (vlSelfRef.tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[6U] 
              & (~ __VdlyMask__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[6U])));
    vlSelfRef.tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[7U] 
        = ((__Vdly__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[7U] 
            & __VdlyMask__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[7U]) 
           | (vlSelfRef.tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[7U] 
              & (~ __VdlyMask__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[7U])));
    vlSelfRef.tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[8U] 
        = ((__Vdly__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[8U] 
            & __VdlyMask__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[8U]) 
           | (vlSelfRef.tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[8U] 
              & (~ __VdlyMask__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[8U])));
    vlSelfRef.tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[9U] 
        = ((__Vdly__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[9U] 
            & __VdlyMask__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[9U]) 
           | (vlSelfRef.tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[9U] 
              & (~ __VdlyMask__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[9U])));
    vlSelfRef.tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[10U] 
        = ((__Vdly__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[10U] 
            & __VdlyMask__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[10U]) 
           | (vlSelfRef.tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[10U] 
              & (~ __VdlyMask__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[10U])));
    vlSelfRef.tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[11U] 
        = ((__Vdly__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[11U] 
            & __VdlyMask__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[11U]) 
           | (vlSelfRef.tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[11U] 
              & (~ __VdlyMask__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[11U])));
    vlSelfRef.tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[12U] 
        = ((__Vdly__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[12U] 
            & __VdlyMask__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[12U]) 
           | (vlSelfRef.tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[12U] 
              & (~ __VdlyMask__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[12U])));
    vlSelfRef.tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[13U] 
        = ((__Vdly__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[13U] 
            & __VdlyMask__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[13U]) 
           | (vlSelfRef.tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[13U] 
              & (~ __VdlyMask__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[13U])));
    vlSelfRef.tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[14U] 
        = ((__Vdly__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[14U] 
            & __VdlyMask__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[14U]) 
           | (vlSelfRef.tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[14U] 
              & (~ __VdlyMask__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[14U])));
    vlSelfRef.tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[15U] 
        = ((__Vdly__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[15U] 
            & __VdlyMask__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[15U]) 
           | (vlSelfRef.tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[15U] 
              & (~ __VdlyMask__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[15U])));
    vlSelfRef.tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[16U] 
        = ((__Vdly__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[16U] 
            & __VdlyMask__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[16U]) 
           | (vlSelfRef.tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[16U] 
              & (~ __VdlyMask__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[16U])));
    vlSelfRef.tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[17U] 
        = ((__Vdly__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[17U] 
            & __VdlyMask__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[17U]) 
           | (vlSelfRef.tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[17U] 
              & (~ __VdlyMask__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[17U])));
    vlSelfRef.tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[18U] 
        = ((__Vdly__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[18U] 
            & __VdlyMask__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[18U]) 
           | (vlSelfRef.tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[18U] 
              & (~ __VdlyMask__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[18U])));
    vlSelfRef.tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[19U] 
        = ((__Vdly__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[19U] 
            & __VdlyMask__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[19U]) 
           | (vlSelfRef.tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[19U] 
              & (~ __VdlyMask__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[19U])));
    vlSelfRef.tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[20U] 
        = ((__Vdly__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[20U] 
            & __VdlyMask__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[20U]) 
           | (vlSelfRef.tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[20U] 
              & (~ __VdlyMask__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[20U])));
    vlSelfRef.tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[21U] 
        = ((__Vdly__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[21U] 
            & __VdlyMask__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[21U]) 
           | (vlSelfRef.tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[21U] 
              & (~ __VdlyMask__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[21U])));
    vlSelfRef.tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[22U] 
        = ((__Vdly__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[22U] 
            & __VdlyMask__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[22U]) 
           | (vlSelfRef.tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[22U] 
              & (~ __VdlyMask__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[22U])));
    vlSelfRef.tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[23U] 
        = ((__Vdly__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[23U] 
            & __VdlyMask__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[23U]) 
           | (vlSelfRef.tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[23U] 
              & (~ __VdlyMask__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[23U])));
    vlSelfRef.tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[24U] 
        = ((__Vdly__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[24U] 
            & __VdlyMask__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[24U]) 
           | (vlSelfRef.tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[24U] 
              & (~ __VdlyMask__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[24U])));
    vlSelfRef.tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[25U] 
        = ((__Vdly__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[25U] 
            & __VdlyMask__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[25U]) 
           | (vlSelfRef.tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[25U] 
              & (~ __VdlyMask__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[25U])));
    vlSelfRef.tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[26U] 
        = ((__Vdly__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[26U] 
            & __VdlyMask__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[26U]) 
           | (vlSelfRef.tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[26U] 
              & (~ __VdlyMask__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[26U])));
    vlSelfRef.tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[27U] 
        = ((__Vdly__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[27U] 
            & __VdlyMask__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[27U]) 
           | (vlSelfRef.tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[27U] 
              & (~ __VdlyMask__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[27U])));
    vlSelfRef.tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[28U] 
        = ((__Vdly__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[28U] 
            & __VdlyMask__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[28U]) 
           | (vlSelfRef.tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[28U] 
              & (~ __VdlyMask__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[28U])));
    vlSelfRef.tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[29U] 
        = ((__Vdly__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[29U] 
            & __VdlyMask__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[29U]) 
           | (vlSelfRef.tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[29U] 
              & (~ __VdlyMask__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[29U])));
    vlSelfRef.tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[30U] 
        = ((__Vdly__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[30U] 
            & __VdlyMask__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[30U]) 
           | (vlSelfRef.tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[30U] 
              & (~ __VdlyMask__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[30U])));
    vlSelfRef.tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[31U] 
        = ((__Vdly__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[31U] 
            & __VdlyMask__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[31U]) 
           | (vlSelfRef.tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[31U] 
              & (~ __VdlyMask__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[31U])));
    VL_ASSIGN_W(1024, __VdlyMask__tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs, Vtb_riscv__ConstPool__CONST_hd6b7ba52_0);
    if (__VdlySet__tb_riscv__DOT__dut__DOT__DataMemInst__DOT__RamArray__v0) {
        vlSelfRef.tb_riscv__DOT__dut__DOT__DataMemInst__DOT__RamArray[__VdlyDim0__tb_riscv__DOT__dut__DOT__DataMemInst__DOT__RamArray__v0] 
            = ((0xffffff00U & vlSelfRef.tb_riscv__DOT__dut__DOT__DataMemInst__DOT__RamArray
                [__VdlyDim0__tb_riscv__DOT__dut__DOT__DataMemInst__DOT__RamArray__v0]) 
               | (IData)(__VdlyVal__tb_riscv__DOT__dut__DOT__DataMemInst__DOT__RamArray__v0));
    }
    if (__VdlySet__tb_riscv__DOT__dut__DOT__DataMemInst__DOT__RamArray__v1) {
        vlSelfRef.tb_riscv__DOT__dut__DOT__DataMemInst__DOT__RamArray[__VdlyDim0__tb_riscv__DOT__dut__DOT__DataMemInst__DOT__RamArray__v1] 
            = ((0xffff00ffU & vlSelfRef.tb_riscv__DOT__dut__DOT__DataMemInst__DOT__RamArray
                [__VdlyDim0__tb_riscv__DOT__dut__DOT__DataMemInst__DOT__RamArray__v1]) 
               | ((IData)(__VdlyVal__tb_riscv__DOT__dut__DOT__DataMemInst__DOT__RamArray__v1) 
                  << 8U));
    }
    if (__VdlySet__tb_riscv__DOT__dut__DOT__DataMemInst__DOT__RamArray__v2) {
        vlSelfRef.tb_riscv__DOT__dut__DOT__DataMemInst__DOT__RamArray[__VdlyDim0__tb_riscv__DOT__dut__DOT__DataMemInst__DOT__RamArray__v2] 
            = ((0xff00ffffU & vlSelfRef.tb_riscv__DOT__dut__DOT__DataMemInst__DOT__RamArray
                [__VdlyDim0__tb_riscv__DOT__dut__DOT__DataMemInst__DOT__RamArray__v2]) 
               | ((IData)(__VdlyVal__tb_riscv__DOT__dut__DOT__DataMemInst__DOT__RamArray__v2) 
                  << 0x00000010U));
    }
    if (__VdlySet__tb_riscv__DOT__dut__DOT__DataMemInst__DOT__RamArray__v3) {
        vlSelfRef.tb_riscv__DOT__dut__DOT__DataMemInst__DOT__RamArray[__VdlyDim0__tb_riscv__DOT__dut__DOT__DataMemInst__DOT__RamArray__v3] 
            = ((0x00ffffffU & vlSelfRef.tb_riscv__DOT__dut__DOT__DataMemInst__DOT__RamArray
                [__VdlyDim0__tb_riscv__DOT__dut__DOT__DataMemInst__DOT__RamArray__v3]) 
               | ((IData)(__VdlyVal__tb_riscv__DOT__dut__DOT__DataMemInst__DOT__RamArray__v3) 
                  << 0x00000018U));
    }
    tb_riscv__DOT__dut__DOT__Instr = vlSelfRef.tb_riscv__DOT__dut__DOT__ProgMemInst__DOT__RamArray
        [(0x000001ffU & vlSelfRef.tb_riscv__DOT__dut__DOT__Pc)];
    vlSelfRef.tb_riscv__DOT__dut__DOT__DmemWr = (0x23U 
                                                 == 
                                                 ([&]() {
                vlSelfRef.__Vfunc_GetOpcode__36__RawInstr 
                    = tb_riscv__DOT__dut__DOT__Instr;
                vlSelfRef.__Vfunc_GetOpcode__36__Vfuncout 
                    = (0x0000007fU & vlSelfRef.__Vfunc_GetOpcode__36__RawInstr);
            }(), (IData)(vlSelfRef.__Vfunc_GetOpcode__36__Vfuncout)));
    tb_riscv__DOT__dut__DOT__JalPcSel = (0x67U == ([&]() {
                vlSelfRef.__Vfunc_GetOpcode__47__RawInstr 
                    = tb_riscv__DOT__dut__DOT__Instr;
                vlSelfRef.__Vfunc_GetOpcode__47__Vfuncout 
                    = (0x0000007fU & vlSelfRef.__Vfunc_GetOpcode__47__RawInstr);
            }(), (IData)(vlSelfRef.__Vfunc_GetOpcode__47__Vfuncout)));
    tb_riscv__DOT__dut__DOT__RegWrEn = (1U & (~ ((0x23U 
                                                  == 
                                                  ([&]() {
                            vlSelfRef.__Vfunc_GetOpcode__37__RawInstr 
                                = tb_riscv__DOT__dut__DOT__Instr;
                            vlSelfRef.__Vfunc_GetOpcode__37__Vfuncout 
                                = (0x0000007fU & vlSelfRef.__Vfunc_GetOpcode__37__RawInstr);
                        }(), (IData)(vlSelfRef.__Vfunc_GetOpcode__37__Vfuncout))) 
                                                 | (0x63U 
                                                    == 
                                                    ([&]() {
                            vlSelfRef.__Vfunc_GetOpcode__38__RawInstr 
                                = tb_riscv__DOT__dut__DOT__Instr;
                            vlSelfRef.__Vfunc_GetOpcode__38__Vfuncout 
                                = (0x0000007fU & vlSelfRef.__Vfunc_GetOpcode__38__RawInstr);
                        }(), (IData)(vlSelfRef.__Vfunc_GetOpcode__38__Vfuncout))))));
    tb_riscv__DOT__dut__DOT__RegWb = ((((0x33U == ([&]() {
                            vlSelfRef.__Vfunc_GetOpcode__39__RawInstr 
                                = tb_riscv__DOT__dut__DOT__Instr;
                            vlSelfRef.__Vfunc_GetOpcode__39__Vfuncout 
                                = (0x0000007fU & vlSelfRef.__Vfunc_GetOpcode__39__RawInstr);
                        }(), (IData)(vlSelfRef.__Vfunc_GetOpcode__39__Vfuncout))) 
                                        | (0x13U == 
                                           ([&]() {
                            vlSelfRef.__Vfunc_GetOpcode__40__RawInstr 
                                = tb_riscv__DOT__dut__DOT__Instr;
                            vlSelfRef.__Vfunc_GetOpcode__40__Vfuncout 
                                = (0x0000007fU & vlSelfRef.__Vfunc_GetOpcode__40__RawInstr);
                        }(), (IData)(vlSelfRef.__Vfunc_GetOpcode__40__Vfuncout)))) 
                                       | (0x17U == 
                                          ([&]() {
                        vlSelfRef.__Vfunc_GetOpcode__41__RawInstr 
                            = tb_riscv__DOT__dut__DOT__Instr;
                        vlSelfRef.__Vfunc_GetOpcode__41__Vfuncout 
                            = (0x0000007fU & vlSelfRef.__Vfunc_GetOpcode__41__RawInstr);
                    }(), (IData)(vlSelfRef.__Vfunc_GetOpcode__41__Vfuncout))))
                                       ? 0U : ((3U 
                                                == 
                                                ([&]() {
                        vlSelfRef.__Vfunc_GetOpcode__42__RawInstr 
                            = tb_riscv__DOT__dut__DOT__Instr;
                        vlSelfRef.__Vfunc_GetOpcode__42__Vfuncout 
                            = (0x0000007fU & vlSelfRef.__Vfunc_GetOpcode__42__RawInstr);
                    }(), (IData)(vlSelfRef.__Vfunc_GetOpcode__42__Vfuncout)))
                                                ? 1U
                                                : (
                                                   (0x37U 
                                                    == 
                                                    ([&]() {
                            vlSelfRef.__Vfunc_GetOpcode__43__RawInstr 
                                = tb_riscv__DOT__dut__DOT__Instr;
                            vlSelfRef.__Vfunc_GetOpcode__43__Vfuncout 
                                = (0x0000007fU & vlSelfRef.__Vfunc_GetOpcode__43__RawInstr);
                        }(), (IData)(vlSelfRef.__Vfunc_GetOpcode__43__Vfuncout)))
                                                    ? 3U
                                                    : 2U)));
    tb_riscv__DOT__dut__DOT__AluInst__DOT__Subtract 
        = (((0x33U == ([&]() {
                        vlSelfRef.__Vfunc_GetOpcode__48__RawInstr 
                            = tb_riscv__DOT__dut__DOT__Instr;
                        vlSelfRef.__Vfunc_GetOpcode__48__Vfuncout 
                            = (0x0000007fU & vlSelfRef.__Vfunc_GetOpcode__48__RawInstr);
                    }(), (IData)(vlSelfRef.__Vfunc_GetOpcode__48__Vfuncout))) 
            & (((IData)((0x40000000U == (0xfe007000U 
                                         & tb_riscv__DOT__dut__DOT__Instr))) 
                | (2U == (7U & (tb_riscv__DOT__dut__DOT__Instr 
                                >> 0x0000000cU)))) 
               | (3U == (7U & (tb_riscv__DOT__dut__DOT__Instr 
                               >> 0x0000000cU))))) 
           | ((0x63U == ([&]() {
                        vlSelfRef.__Vfunc_GetOpcode__49__RawInstr 
                            = tb_riscv__DOT__dut__DOT__Instr;
                        vlSelfRef.__Vfunc_GetOpcode__49__Vfuncout 
                            = (0x0000007fU & vlSelfRef.__Vfunc_GetOpcode__49__RawInstr);
                    }(), (IData)(vlSelfRef.__Vfunc_GetOpcode__49__Vfuncout))) 
              & ((0U == (7U & (tb_riscv__DOT__dut__DOT__Instr 
                               >> 0x0000000cU))) | 
                 (1U == (7U & (tb_riscv__DOT__dut__DOT__Instr 
                               >> 0x0000000cU))))));
    vlSelfRef.tb_riscv__DOT__dut__DOT__RegSrc2 = vlSelfRef.tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs
        [(0x0000001fU & (tb_riscv__DOT__dut__DOT__Instr 
                         >> 0x00000014U))];
    tb_riscv__DOT__dut__DOT__AuipcSel = (0x17U == ([&]() {
                vlSelfRef.__Vfunc_GetOpcode__44__RawInstr 
                    = tb_riscv__DOT__dut__DOT__Instr;
                vlSelfRef.__Vfunc_GetOpcode__44__Vfuncout 
                    = (0x0000007fU & vlSelfRef.__Vfunc_GetOpcode__44__RawInstr);
            }(), (IData)(vlSelfRef.__Vfunc_GetOpcode__44__Vfuncout)));
    tb_riscv__DOT__dut__DOT__Op2Sel = (1U & (~ ((0x33U 
                                                 == 
                                                 ([&]() {
                            vlSelfRef.__Vfunc_GetOpcode__34__RawInstr 
                                = tb_riscv__DOT__dut__DOT__Instr;
                            vlSelfRef.__Vfunc_GetOpcode__34__Vfuncout 
                                = (0x0000007fU & vlSelfRef.__Vfunc_GetOpcode__34__RawInstr);
                        }(), (IData)(vlSelfRef.__Vfunc_GetOpcode__34__Vfuncout))) 
                                                | (0x63U 
                                                   == 
                                                   ([&]() {
                            vlSelfRef.__Vfunc_GetOpcode__35__RawInstr 
                                = tb_riscv__DOT__dut__DOT__Instr;
                            vlSelfRef.__Vfunc_GetOpcode__35__Vfuncout 
                                = (0x0000007fU & vlSelfRef.__Vfunc_GetOpcode__35__RawInstr);
                        }(), (IData)(vlSelfRef.__Vfunc_GetOpcode__35__Vfuncout))))));
    __Vfunc_GetImmediate__0__RawInstr = tb_riscv__DOT__dut__DOT__Instr;
    __Vfunc_GetImmediate__0__Instr = __Vfunc_GetImmediate__0__RawInstr;
    __Vfunc_GetImmediate__0__Vfuncout = ((0x00000040U 
                                          & ([&]() {
                    vlSelfRef.__Vfunc_GetOpcode__1__RawInstr 
                        = __Vfunc_GetImmediate__0__RawInstr;
                    vlSelfRef.__Vfunc_GetOpcode__1__Vfuncout 
                        = (0x0000007fU & vlSelfRef.__Vfunc_GetOpcode__1__RawInstr);
                }(), (IData)(vlSelfRef.__Vfunc_GetOpcode__1__Vfuncout)))
                                          ? ((0x00000020U 
                                              & ([&]() {
                        vlSelfRef.__Vfunc_GetOpcode__2__RawInstr 
                            = __Vfunc_GetImmediate__0__RawInstr;
                        vlSelfRef.__Vfunc_GetOpcode__2__Vfuncout 
                            = (0x0000007fU & vlSelfRef.__Vfunc_GetOpcode__2__RawInstr);
                    }(), (IData)(vlSelfRef.__Vfunc_GetOpcode__2__Vfuncout)))
                                              ? ((0x00000010U 
                                                  & ([&]() {
                            vlSelfRef.__Vfunc_GetOpcode__3__RawInstr 
                                = __Vfunc_GetImmediate__0__RawInstr;
                            vlSelfRef.__Vfunc_GetOpcode__3__Vfuncout 
                                = (0x0000007fU & vlSelfRef.__Vfunc_GetOpcode__3__RawInstr);
                        }(), (IData)(vlSelfRef.__Vfunc_GetOpcode__3__Vfuncout)))
                                                  ? 0U
                                                  : 
                                                 ((8U 
                                                   & ([&]() {
                                vlSelfRef.__Vfunc_GetOpcode__4__RawInstr 
                                    = __Vfunc_GetImmediate__0__RawInstr;
                                vlSelfRef.__Vfunc_GetOpcode__4__Vfuncout 
                                    = (0x0000007fU 
                                       & vlSelfRef.__Vfunc_GetOpcode__4__RawInstr);
                            }(), (IData)(vlSelfRef.__Vfunc_GetOpcode__4__Vfuncout)))
                                                   ? 
                                                  ((4U 
                                                    & ([&]() {
                                    vlSelfRef.__Vfunc_GetOpcode__5__RawInstr 
                                        = __Vfunc_GetImmediate__0__RawInstr;
                                    vlSelfRef.__Vfunc_GetOpcode__5__Vfuncout 
                                        = (0x0000007fU 
                                           & vlSelfRef.__Vfunc_GetOpcode__5__RawInstr);
                                }(), (IData)(vlSelfRef.__Vfunc_GetOpcode__5__Vfuncout)))
                                                    ? 
                                                   ((2U 
                                                     & ([&]() {
                                        vlSelfRef.__Vfunc_GetOpcode__6__RawInstr 
                                            = __Vfunc_GetImmediate__0__RawInstr;
                                        vlSelfRef.__Vfunc_GetOpcode__6__Vfuncout 
                                            = (0x0000007fU 
                                               & vlSelfRef.__Vfunc_GetOpcode__6__RawInstr);
                                    }(), (IData)(vlSelfRef.__Vfunc_GetOpcode__6__Vfuncout)))
                                                     ? 
                                                    ((1U 
                                                      & ([&]() {
                                            vlSelfRef.__Vfunc_GetOpcode__7__RawInstr 
                                                = __Vfunc_GetImmediate__0__RawInstr;
                                            vlSelfRef.__Vfunc_GetOpcode__7__Vfuncout 
                                                = (0x0000007fU 
                                                   & vlSelfRef.__Vfunc_GetOpcode__7__RawInstr);
                                        }(), (IData)(vlSelfRef.__Vfunc_GetOpcode__7__Vfuncout)))
                                                      ? 
                                                     ((((0x00000ffeU 
                                                         & ((- (IData)(
                                                                       (__Vfunc_GetImmediate__0__Instr 
                                                                        >> 0x0000001fU))) 
                                                            << 1U)) 
                                                        | (__Vfunc_GetImmediate__0__Instr 
                                                           >> 0x0000001fU)) 
                                                       << 0x00000014U) 
                                                      | ((((0x000001feU 
                                                            & (__Vfunc_GetImmediate__0__Instr 
                                                               >> 0x0000000bU)) 
                                                           | (1U 
                                                              & (__Vfunc_GetImmediate__0__Instr 
                                                                 >> 0x00000014U))) 
                                                          << 0x0000000bU) 
                                                         | (0x000007feU 
                                                            & (__Vfunc_GetImmediate__0__Instr 
                                                               >> 0x00000014U))))
                                                      : 0U)
                                                     : 0U)
                                                    : 0U)
                                                   : 
                                                  ((4U 
                                                    & ([&]() {
                                    vlSelfRef.__Vfunc_GetOpcode__8__RawInstr 
                                        = __Vfunc_GetImmediate__0__RawInstr;
                                    vlSelfRef.__Vfunc_GetOpcode__8__Vfuncout 
                                        = (0x0000007fU 
                                           & vlSelfRef.__Vfunc_GetOpcode__8__RawInstr);
                                }(), (IData)(vlSelfRef.__Vfunc_GetOpcode__8__Vfuncout)))
                                                    ? 
                                                   ((2U 
                                                     & ([&]() {
                                        vlSelfRef.__Vfunc_GetOpcode__9__RawInstr 
                                            = __Vfunc_GetImmediate__0__RawInstr;
                                        vlSelfRef.__Vfunc_GetOpcode__9__Vfuncout 
                                            = (0x0000007fU 
                                               & vlSelfRef.__Vfunc_GetOpcode__9__RawInstr);
                                    }(), (IData)(vlSelfRef.__Vfunc_GetOpcode__9__Vfuncout)))
                                                     ? 
                                                    ((1U 
                                                      & ([&]() {
                                            vlSelfRef.__Vfunc_GetOpcode__10__RawInstr 
                                                = __Vfunc_GetImmediate__0__RawInstr;
                                            vlSelfRef.__Vfunc_GetOpcode__10__Vfuncout 
                                                = (0x0000007fU 
                                                   & vlSelfRef.__Vfunc_GetOpcode__10__RawInstr);
                                        }(), (IData)(vlSelfRef.__Vfunc_GetOpcode__10__Vfuncout)))
                                                      ? 
                                                     (((- (IData)(
                                                                  (__Vfunc_GetImmediate__0__Instr 
                                                                   >> 0x0000001fU))) 
                                                       << 0x0000000cU) 
                                                      | (__Vfunc_GetImmediate__0__Instr 
                                                         >> 0x00000014U))
                                                      : 0U)
                                                     : 0U)
                                                    : 
                                                   ((2U 
                                                     & ([&]() {
                                        vlSelfRef.__Vfunc_GetOpcode__11__RawInstr 
                                            = __Vfunc_GetImmediate__0__RawInstr;
                                        vlSelfRef.__Vfunc_GetOpcode__11__Vfuncout 
                                            = (0x0000007fU 
                                               & vlSelfRef.__Vfunc_GetOpcode__11__RawInstr);
                                    }(), (IData)(vlSelfRef.__Vfunc_GetOpcode__11__Vfuncout)))
                                                     ? 
                                                    ((1U 
                                                      & ([&]() {
                                            vlSelfRef.__Vfunc_GetOpcode__12__RawInstr 
                                                = __Vfunc_GetImmediate__0__RawInstr;
                                            vlSelfRef.__Vfunc_GetOpcode__12__Vfuncout 
                                                = (0x0000007fU 
                                                   & vlSelfRef.__Vfunc_GetOpcode__12__RawInstr);
                                        }(), (IData)(vlSelfRef.__Vfunc_GetOpcode__12__Vfuncout)))
                                                      ? 
                                                     (((- (IData)(
                                                                  (__Vfunc_GetImmediate__0__Instr 
                                                                   >> 0x0000001fU))) 
                                                       << 0x0000000dU) 
                                                      | ((((2U 
                                                            & (__Vfunc_GetImmediate__0__Instr 
                                                               >> 0x0000001eU)) 
                                                           | (1U 
                                                              & (__Vfunc_GetImmediate__0__Instr 
                                                                 >> 7U))) 
                                                          << 0x0000000bU) 
                                                         | ((0x000007e0U 
                                                             & (__Vfunc_GetImmediate__0__Instr 
                                                                >> 0x00000014U)) 
                                                            | (0x0000001eU 
                                                               & (__Vfunc_GetImmediate__0__Instr 
                                                                  >> 7U)))))
                                                      : 0U)
                                                     : 0U))))
                                              : 0U)
                                          : ((0x00000020U 
                                              & ([&]() {
                        vlSelfRef.__Vfunc_GetOpcode__13__RawInstr 
                            = __Vfunc_GetImmediate__0__RawInstr;
                        vlSelfRef.__Vfunc_GetOpcode__13__Vfuncout 
                            = (0x0000007fU & vlSelfRef.__Vfunc_GetOpcode__13__RawInstr);
                    }(), (IData)(vlSelfRef.__Vfunc_GetOpcode__13__Vfuncout)))
                                              ? ((0x00000010U 
                                                  & ([&]() {
                            vlSelfRef.__Vfunc_GetOpcode__14__RawInstr 
                                = __Vfunc_GetImmediate__0__RawInstr;
                            vlSelfRef.__Vfunc_GetOpcode__14__Vfuncout 
                                = (0x0000007fU & vlSelfRef.__Vfunc_GetOpcode__14__RawInstr);
                        }(), (IData)(vlSelfRef.__Vfunc_GetOpcode__14__Vfuncout)))
                                                  ? 
                                                 ((8U 
                                                   & ([&]() {
                                vlSelfRef.__Vfunc_GetOpcode__15__RawInstr 
                                    = __Vfunc_GetImmediate__0__RawInstr;
                                vlSelfRef.__Vfunc_GetOpcode__15__Vfuncout 
                                    = (0x0000007fU 
                                       & vlSelfRef.__Vfunc_GetOpcode__15__RawInstr);
                            }(), (IData)(vlSelfRef.__Vfunc_GetOpcode__15__Vfuncout)))
                                                   ? 0U
                                                   : 
                                                  ((4U 
                                                    & ([&]() {
                                    vlSelfRef.__Vfunc_GetOpcode__16__RawInstr 
                                        = __Vfunc_GetImmediate__0__RawInstr;
                                    vlSelfRef.__Vfunc_GetOpcode__16__Vfuncout 
                                        = (0x0000007fU 
                                           & vlSelfRef.__Vfunc_GetOpcode__16__RawInstr);
                                }(), (IData)(vlSelfRef.__Vfunc_GetOpcode__16__Vfuncout)))
                                                    ? 
                                                   ((2U 
                                                     & ([&]() {
                                        vlSelfRef.__Vfunc_GetOpcode__17__RawInstr 
                                            = __Vfunc_GetImmediate__0__RawInstr;
                                        vlSelfRef.__Vfunc_GetOpcode__17__Vfuncout 
                                            = (0x0000007fU 
                                               & vlSelfRef.__Vfunc_GetOpcode__17__RawInstr);
                                    }(), (IData)(vlSelfRef.__Vfunc_GetOpcode__17__Vfuncout)))
                                                     ? 
                                                    ((1U 
                                                      & ([&]() {
                                            vlSelfRef.__Vfunc_GetOpcode__18__RawInstr 
                                                = __Vfunc_GetImmediate__0__RawInstr;
                                            vlSelfRef.__Vfunc_GetOpcode__18__Vfuncout 
                                                = (0x0000007fU 
                                                   & vlSelfRef.__Vfunc_GetOpcode__18__RawInstr);
                                        }(), (IData)(vlSelfRef.__Vfunc_GetOpcode__18__Vfuncout)))
                                                      ? 
                                                     (0xfffff000U 
                                                      & __Vfunc_GetImmediate__0__Instr)
                                                      : 0U)
                                                     : 0U)
                                                    : 0U))
                                                  : 
                                                 ((8U 
                                                   & ([&]() {
                                vlSelfRef.__Vfunc_GetOpcode__19__RawInstr 
                                    = __Vfunc_GetImmediate__0__RawInstr;
                                vlSelfRef.__Vfunc_GetOpcode__19__Vfuncout 
                                    = (0x0000007fU 
                                       & vlSelfRef.__Vfunc_GetOpcode__19__RawInstr);
                            }(), (IData)(vlSelfRef.__Vfunc_GetOpcode__19__Vfuncout)))
                                                   ? 0U
                                                   : 
                                                  ((4U 
                                                    & ([&]() {
                                    vlSelfRef.__Vfunc_GetOpcode__20__RawInstr 
                                        = __Vfunc_GetImmediate__0__RawInstr;
                                    vlSelfRef.__Vfunc_GetOpcode__20__Vfuncout 
                                        = (0x0000007fU 
                                           & vlSelfRef.__Vfunc_GetOpcode__20__RawInstr);
                                }(), (IData)(vlSelfRef.__Vfunc_GetOpcode__20__Vfuncout)))
                                                    ? 0U
                                                    : 
                                                   ((2U 
                                                     & ([&]() {
                                        vlSelfRef.__Vfunc_GetOpcode__21__RawInstr 
                                            = __Vfunc_GetImmediate__0__RawInstr;
                                        vlSelfRef.__Vfunc_GetOpcode__21__Vfuncout 
                                            = (0x0000007fU 
                                               & vlSelfRef.__Vfunc_GetOpcode__21__RawInstr);
                                    }(), (IData)(vlSelfRef.__Vfunc_GetOpcode__21__Vfuncout)))
                                                     ? 
                                                    ((1U 
                                                      & ([&]() {
                                            vlSelfRef.__Vfunc_GetOpcode__22__RawInstr 
                                                = __Vfunc_GetImmediate__0__RawInstr;
                                            vlSelfRef.__Vfunc_GetOpcode__22__Vfuncout 
                                                = (0x0000007fU 
                                                   & vlSelfRef.__Vfunc_GetOpcode__22__RawInstr);
                                        }(), (IData)(vlSelfRef.__Vfunc_GetOpcode__22__Vfuncout)))
                                                      ? 
                                                     (((- (IData)(
                                                                  (__Vfunc_GetImmediate__0__Instr 
                                                                   >> 0x0000001fU))) 
                                                       << 0x0000000cU) 
                                                      | ((0x00000fe0U 
                                                          & (__Vfunc_GetImmediate__0__Instr 
                                                             >> 0x00000014U)) 
                                                         | (0x0000001fU 
                                                            & (__Vfunc_GetImmediate__0__Instr 
                                                               >> 7U))))
                                                      : 0U)
                                                     : 0U))))
                                              : ((0x00000010U 
                                                  & ([&]() {
                            vlSelfRef.__Vfunc_GetOpcode__23__RawInstr 
                                = __Vfunc_GetImmediate__0__RawInstr;
                            vlSelfRef.__Vfunc_GetOpcode__23__Vfuncout 
                                = (0x0000007fU & vlSelfRef.__Vfunc_GetOpcode__23__RawInstr);
                        }(), (IData)(vlSelfRef.__Vfunc_GetOpcode__23__Vfuncout)))
                                                  ? 
                                                 ((8U 
                                                   & ([&]() {
                                vlSelfRef.__Vfunc_GetOpcode__24__RawInstr 
                                    = __Vfunc_GetImmediate__0__RawInstr;
                                vlSelfRef.__Vfunc_GetOpcode__24__Vfuncout 
                                    = (0x0000007fU 
                                       & vlSelfRef.__Vfunc_GetOpcode__24__RawInstr);
                            }(), (IData)(vlSelfRef.__Vfunc_GetOpcode__24__Vfuncout)))
                                                   ? 0U
                                                   : 
                                                  ((4U 
                                                    & ([&]() {
                                    vlSelfRef.__Vfunc_GetOpcode__25__RawInstr 
                                        = __Vfunc_GetImmediate__0__RawInstr;
                                    vlSelfRef.__Vfunc_GetOpcode__25__Vfuncout 
                                        = (0x0000007fU 
                                           & vlSelfRef.__Vfunc_GetOpcode__25__RawInstr);
                                }(), (IData)(vlSelfRef.__Vfunc_GetOpcode__25__Vfuncout)))
                                                    ? 
                                                   ((2U 
                                                     & ([&]() {
                                        vlSelfRef.__Vfunc_GetOpcode__26__RawInstr 
                                            = __Vfunc_GetImmediate__0__RawInstr;
                                        vlSelfRef.__Vfunc_GetOpcode__26__Vfuncout 
                                            = (0x0000007fU 
                                               & vlSelfRef.__Vfunc_GetOpcode__26__RawInstr);
                                    }(), (IData)(vlSelfRef.__Vfunc_GetOpcode__26__Vfuncout)))
                                                     ? 
                                                    ((1U 
                                                      & ([&]() {
                                            vlSelfRef.__Vfunc_GetOpcode__27__RawInstr 
                                                = __Vfunc_GetImmediate__0__RawInstr;
                                            vlSelfRef.__Vfunc_GetOpcode__27__Vfuncout 
                                                = (0x0000007fU 
                                                   & vlSelfRef.__Vfunc_GetOpcode__27__RawInstr);
                                        }(), (IData)(vlSelfRef.__Vfunc_GetOpcode__27__Vfuncout)))
                                                      ? 
                                                     (0xfffff000U 
                                                      & __Vfunc_GetImmediate__0__Instr)
                                                      : 0U)
                                                     : 0U)
                                                    : 
                                                   ((2U 
                                                     & ([&]() {
                                        vlSelfRef.__Vfunc_GetOpcode__28__RawInstr 
                                            = __Vfunc_GetImmediate__0__RawInstr;
                                        vlSelfRef.__Vfunc_GetOpcode__28__Vfuncout 
                                            = (0x0000007fU 
                                               & vlSelfRef.__Vfunc_GetOpcode__28__RawInstr);
                                    }(), (IData)(vlSelfRef.__Vfunc_GetOpcode__28__Vfuncout)))
                                                     ? 
                                                    ((1U 
                                                      & ([&]() {
                                            vlSelfRef.__Vfunc_GetOpcode__29__RawInstr 
                                                = __Vfunc_GetImmediate__0__RawInstr;
                                            vlSelfRef.__Vfunc_GetOpcode__29__Vfuncout 
                                                = (0x0000007fU 
                                                   & vlSelfRef.__Vfunc_GetOpcode__29__RawInstr);
                                        }(), (IData)(vlSelfRef.__Vfunc_GetOpcode__29__Vfuncout)))
                                                      ? 
                                                     (((- (IData)(
                                                                  (__Vfunc_GetImmediate__0__Instr 
                                                                   >> 0x0000001fU))) 
                                                       << 0x0000000cU) 
                                                      | (__Vfunc_GetImmediate__0__Instr 
                                                         >> 0x00000014U))
                                                      : 0U)
                                                     : 0U)))
                                                  : 
                                                 ((8U 
                                                   & ([&]() {
                                vlSelfRef.__Vfunc_GetOpcode__30__RawInstr 
                                    = __Vfunc_GetImmediate__0__RawInstr;
                                vlSelfRef.__Vfunc_GetOpcode__30__Vfuncout 
                                    = (0x0000007fU 
                                       & vlSelfRef.__Vfunc_GetOpcode__30__RawInstr);
                            }(), (IData)(vlSelfRef.__Vfunc_GetOpcode__30__Vfuncout)))
                                                   ? 0U
                                                   : 
                                                  ((4U 
                                                    & ([&]() {
                                    vlSelfRef.__Vfunc_GetOpcode__31__RawInstr 
                                        = __Vfunc_GetImmediate__0__RawInstr;
                                    vlSelfRef.__Vfunc_GetOpcode__31__Vfuncout 
                                        = (0x0000007fU 
                                           & vlSelfRef.__Vfunc_GetOpcode__31__RawInstr);
                                }(), (IData)(vlSelfRef.__Vfunc_GetOpcode__31__Vfuncout)))
                                                    ? 0U
                                                    : 
                                                   ((2U 
                                                     & ([&]() {
                                        vlSelfRef.__Vfunc_GetOpcode__32__RawInstr 
                                            = __Vfunc_GetImmediate__0__RawInstr;
                                        vlSelfRef.__Vfunc_GetOpcode__32__Vfuncout 
                                            = (0x0000007fU 
                                               & vlSelfRef.__Vfunc_GetOpcode__32__RawInstr);
                                    }(), (IData)(vlSelfRef.__Vfunc_GetOpcode__32__Vfuncout)))
                                                     ? 
                                                    ((1U 
                                                      & ([&]() {
                                            vlSelfRef.__Vfunc_GetOpcode__33__RawInstr 
                                                = __Vfunc_GetImmediate__0__RawInstr;
                                            vlSelfRef.__Vfunc_GetOpcode__33__Vfuncout 
                                                = (0x0000007fU 
                                                   & vlSelfRef.__Vfunc_GetOpcode__33__RawInstr);
                                        }(), (IData)(vlSelfRef.__Vfunc_GetOpcode__33__Vfuncout)))
                                                      ? 
                                                     (((- (IData)(
                                                                  (__Vfunc_GetImmediate__0__Instr 
                                                                   >> 0x0000001fU))) 
                                                       << 0x0000000cU) 
                                                      | (__Vfunc_GetImmediate__0__Instr 
                                                         >> 0x00000014U))
                                                      : 0U)
                                                     : 0U))))));
    tb_riscv__DOT__dut__DOT__ImmExt = __Vfunc_GetImmediate__0__Vfuncout;
    vlSelfRef.tb_riscv__DOT__dut__DOT__RegfileInst__DOT__WrDecVec = 0U;
    vlSelfRef.tb_riscv__DOT__dut__DOT__RegfileInst__DOT__WrDecVec 
        = (((~ ((IData)(1U) << (0x0000001fU & (tb_riscv__DOT__dut__DOT__Instr 
                                               >> 7U)))) 
            & vlSelfRef.tb_riscv__DOT__dut__DOT__RegfileInst__DOT__WrDecVec) 
           | (0x00000000ffffffffULL & ((IData)(tb_riscv__DOT__dut__DOT__RegWrEn) 
                                       << (0x0000001fU 
                                           & (tb_riscv__DOT__dut__DOT__Instr 
                                              >> 7U)))));
    if ((1U & (~ VL_ONEHOT_I(((((3U == (IData)(tb_riscv__DOT__dut__DOT__RegWb)) 
                                << 3U) | ((2U == (IData)(tb_riscv__DOT__dut__DOT__RegWb)) 
                                          << 2U)) | 
                              (((1U == (IData)(tb_riscv__DOT__dut__DOT__RegWb)) 
                                << 1U) | (0U == (IData)(tb_riscv__DOT__dut__DOT__RegWb)))))))) {
        if ((0U != ((((3U == (IData)(tb_riscv__DOT__dut__DOT__RegWb)) 
                      << 3U) | ((2U == (IData)(tb_riscv__DOT__dut__DOT__RegWb)) 
                                << 2U)) | (((1U == (IData)(tb_riscv__DOT__dut__DOT__RegWb)) 
                                            << 1U) 
                                           | (0U == (IData)(tb_riscv__DOT__dut__DOT__RegWb)))))) {
            if (VL_UNLIKELY((vlSymsp->_vm_contextp__->assertOn()))) {
                VL_WRITEF_NX("[%0t] %%Error: Riscv.sv:116: Assertion failed in %Ntb_riscv.dut: unique case, but multiple matches found for '32'h%x'\n",0,
                             64,VL_TIME_UNITED_Q(1000),
                             -9,vlSymsp->name(),32,
                             (IData)(tb_riscv__DOT__dut__DOT__RegWb));
                VL_STOP_MT("Riscv.sv", 116, "");
            }
        }
    }
    tb_riscv__DOT__dut__DOT__AluOp1 = ((IData)(tb_riscv__DOT__dut__DOT__AuipcSel)
                                        ? vlSelfRef.tb_riscv__DOT__dut__DOT__Pc
                                        : vlSelfRef.tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs
                                       [(0x0000001fU 
                                         & (tb_riscv__DOT__dut__DOT__Instr 
                                            >> 0x0000000fU))]);
    tb_riscv__DOT__dut__DOT__AluOp2 = ((IData)(tb_riscv__DOT__dut__DOT__Op2Sel)
                                        ? tb_riscv__DOT__dut__DOT__ImmExt
                                        : vlSelfRef.tb_riscv__DOT__dut__DOT__RegSrc2);
    tb_riscv__DOT__dut__DOT__AluInst__DOT__ShiftOut 
        = ((1U == (7U & (tb_riscv__DOT__dut__DOT__Instr 
                         >> 0x0000000cU))) ? (tb_riscv__DOT__dut__DOT__AluOp1 
                                              << (0x0000001fU 
                                                  & tb_riscv__DOT__dut__DOT__AluOp2))
            : ((5U == (7U & (tb_riscv__DOT__dut__DOT__Instr 
                             >> 0x0000000cU))) ? (tb_riscv__DOT__dut__DOT__AluOp1 
                                                  >> 
                                                  (0x0000001fU 
                                                   & tb_riscv__DOT__dut__DOT__AluOp2))
                : 0U));
    tb_riscv__DOT__dut__DOT__AluInst__DOT__AddrOut 
        = (tb_riscv__DOT__dut__DOT__AluOp1 + (((- (IData)((IData)(tb_riscv__DOT__dut__DOT__AluInst__DOT__Subtract))) 
                                               ^ tb_riscv__DOT__dut__DOT__AluOp2) 
                                              + (IData)(tb_riscv__DOT__dut__DOT__AluInst__DOT__Subtract)));
    tb_riscv__DOT__dut__DOT__AluInst__DOT__IsLessThan 
        = VL_LTS_III(32, tb_riscv__DOT__dut__DOT__AluOp1, tb_riscv__DOT__dut__DOT__AluOp2);
    tb_riscv__DOT__dut__DOT__AluInst__DOT__IsLessThanUnsigned 
        = (tb_riscv__DOT__dut__DOT__AluOp1 < tb_riscv__DOT__dut__DOT__AluOp2);
    tb_riscv__DOT__dut__DOT__BrPcSel = ((0x6fU == ([&]() {
                    vlSelfRef.__Vfunc_GetOpcode__45__RawInstr 
                        = tb_riscv__DOT__dut__DOT__Instr;
                    vlSelfRef.__Vfunc_GetOpcode__45__Vfuncout 
                        = (0x0000007fU & vlSelfRef.__Vfunc_GetOpcode__45__RawInstr);
                }(), (IData)(vlSelfRef.__Vfunc_GetOpcode__45__Vfuncout))) 
                                        | ((0x63U == 
                                            ([&]() {
                        vlSelfRef.__Vfunc_GetOpcode__46__RawInstr 
                            = tb_riscv__DOT__dut__DOT__Instr;
                        vlSelfRef.__Vfunc_GetOpcode__46__Vfuncout 
                            = (0x0000007fU & vlSelfRef.__Vfunc_GetOpcode__46__RawInstr);
                    }(), (IData)(vlSelfRef.__Vfunc_GetOpcode__46__Vfuncout))) 
                                           & ((IData)(
                                                      ((0U 
                                                        == 
                                                        (0x00007000U 
                                                         & tb_riscv__DOT__dut__DOT__Instr)) 
                                                       & (0U 
                                                          == tb_riscv__DOT__dut__DOT__AluInst__DOT__AddrOut))) 
                                              | ((IData)(
                                                         ((0x00001000U 
                                                           == 
                                                           (0x00007000U 
                                                            & tb_riscv__DOT__dut__DOT__Instr)) 
                                                          & (0U 
                                                             != tb_riscv__DOT__dut__DOT__AluInst__DOT__AddrOut))) 
                                                 | ((IData)(
                                                            ((0x00004000U 
                                                              == 
                                                              (0x00007000U 
                                                               & tb_riscv__DOT__dut__DOT__Instr)) 
                                                             & (IData)(tb_riscv__DOT__dut__DOT__AluInst__DOT__IsLessThan))) 
                                                    | (((~ (IData)(tb_riscv__DOT__dut__DOT__AluInst__DOT__IsLessThan)) 
                                                        & (0x00005000U 
                                                           == 
                                                           (0x00007000U 
                                                            & tb_riscv__DOT__dut__DOT__Instr))) 
                                                       | ((IData)(
                                                                  ((0x00006000U 
                                                                    == 
                                                                    (0x00007000U 
                                                                     & tb_riscv__DOT__dut__DOT__Instr)) 
                                                                   & (IData)(tb_riscv__DOT__dut__DOT__AluInst__DOT__IsLessThanUnsigned))) 
                                                          | ((~ (IData)(tb_riscv__DOT__dut__DOT__AluInst__DOT__IsLessThanUnsigned)) 
                                                             & (0x00007000U 
                                                                == 
                                                                (0x00007000U 
                                                                 & tb_riscv__DOT__dut__DOT__Instr))))))))));
    if ((0x00004000U & tb_riscv__DOT__dut__DOT__Instr)) {
        if ((0x00002000U & tb_riscv__DOT__dut__DOT__Instr)) {
            tb_riscv__DOT__dut__DOT__AluInst__DOT__LogicOut 
                = ((0x00001000U & tb_riscv__DOT__dut__DOT__Instr)
                    ? (tb_riscv__DOT__dut__DOT__AluOp1 
                       & tb_riscv__DOT__dut__DOT__AluOp2)
                    : (tb_riscv__DOT__dut__DOT__AluOp1 
                       | tb_riscv__DOT__dut__DOT__AluOp2));
            vlSelfRef.tb_riscv__DOT__dut__DOT__AluOut 
                = tb_riscv__DOT__dut__DOT__AluInst__DOT__LogicOut;
        } else if ((0x00001000U & tb_riscv__DOT__dut__DOT__Instr)) {
            tb_riscv__DOT__dut__DOT__AluInst__DOT__LogicOut = 0U;
            vlSelfRef.tb_riscv__DOT__dut__DOT__AluOut 
                = tb_riscv__DOT__dut__DOT__AluInst__DOT__ShiftOut;
        } else {
            tb_riscv__DOT__dut__DOT__AluInst__DOT__LogicOut 
                = (tb_riscv__DOT__dut__DOT__AluOp1 
                   ^ tb_riscv__DOT__dut__DOT__AluOp2);
            vlSelfRef.tb_riscv__DOT__dut__DOT__AluOut 
                = tb_riscv__DOT__dut__DOT__AluInst__DOT__LogicOut;
        }
    } else if ((0x00002000U & tb_riscv__DOT__dut__DOT__Instr)) {
        tb_riscv__DOT__dut__DOT__AluInst__DOT__LogicOut 
            = ((0x00001000U & tb_riscv__DOT__dut__DOT__Instr)
                ? (IData)(tb_riscv__DOT__dut__DOT__AluInst__DOT__IsLessThanUnsigned)
                : (IData)(tb_riscv__DOT__dut__DOT__AluInst__DOT__IsLessThan));
        vlSelfRef.tb_riscv__DOT__dut__DOT__AluOut = tb_riscv__DOT__dut__DOT__AluInst__DOT__LogicOut;
    } else {
        tb_riscv__DOT__dut__DOT__AluInst__DOT__LogicOut = 0U;
        vlSelfRef.tb_riscv__DOT__dut__DOT__AluOut = 
            ((0x00001000U & tb_riscv__DOT__dut__DOT__Instr)
              ? tb_riscv__DOT__dut__DOT__AluInst__DOT__ShiftOut
              : tb_riscv__DOT__dut__DOT__AluInst__DOT__AddrOut);
    }
    vlSelfRef.tb_riscv__DOT__dut__DOT__RegWrData = 
        ((0U == (IData)(tb_riscv__DOT__dut__DOT__RegWb))
          ? vlSelfRef.tb_riscv__DOT__dut__DOT__AluOut
          : ((1U == (IData)(tb_riscv__DOT__dut__DOT__RegWb))
              ? vlSelfRef.tb_riscv__DOT__dut__DOT__DataMemInst__DOT__RamArray
             [(0x000001ffU & vlSelfRef.tb_riscv__DOT__dut__DOT__AluOut)]
              : ((2U == (IData)(tb_riscv__DOT__dut__DOT__RegWb))
                  ? ((IData)(4U) + vlSelfRef.tb_riscv__DOT__dut__DOT__Pc)
                  : ((3U == (IData)(tb_riscv__DOT__dut__DOT__RegWb))
                      ? tb_riscv__DOT__dut__DOT__ImmExt
                      : 0U))));
    vlSelfRef.tb_riscv__DOT__dut__DOT__PcNxt = ((IData)(tb_riscv__DOT__dut__DOT__JalPcSel)
                                                 ? vlSelfRef.tb_riscv__DOT__dut__DOT__AluOut
                                                 : 
                                                (vlSelfRef.tb_riscv__DOT__dut__DOT__Pc 
                                                 + 
                                                 ((IData)(tb_riscv__DOT__dut__DOT__BrPcSel)
                                                   ? tb_riscv__DOT__dut__DOT__ImmExt
                                                   : 4U)));
}

void Vtb_riscv___024root___eval_nba(Vtb_riscv___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_riscv___024root___eval_nba\n"); );
    Vtb_riscv__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VnbaTriggered[0U])) {
        Vtb_riscv___024root___nba_sequent__TOP__0(vlSelf);
    }
}

void Vtb_riscv___024root___timing_ready(Vtb_riscv___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_riscv___024root___timing_ready\n"); );
    Vtb_riscv__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VactTriggered[0U])) {
        vlSelfRef.__VtrigSched_h71169501__0.ready("@(posedge tb_riscv.Clk)");
    }
}

void Vtb_riscv___024root___timing_resume(Vtb_riscv___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_riscv___024root___timing_resume\n"); );
    Vtb_riscv__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VtrigSched_h71169501__0.moveToResumeQueue(
                                                          "@(posedge tb_riscv.Clk)");
    vlSelfRef.__VtrigSched_h71169501__0.resume("@(posedge tb_riscv.Clk)");
    if ((2ULL & vlSelfRef.__VactTriggered[0U])) {
        vlSelfRef.__VdlySched.resume();
    }
}

void Vtb_riscv___024root___trigger_orInto__act_vec_vec(VlUnpacked<QData/*63:0*/, 1> &out, const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_riscv___024root___trigger_orInto__act_vec_vec\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        out[n] = (out[n] | in[n]);
        n = ((IData)(1U) + n);
    } while ((0U >= n));
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtb_riscv___024root___dump_triggers__act(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG

bool Vtb_riscv___024root___eval_phase__act(Vtb_riscv___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_riscv___024root___eval_phase__act\n"); );
    Vtb_riscv__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VactExecute;
    // Body
    Vtb_riscv___024root___eval_triggers_vec__act(vlSelf);
    Vtb_riscv___024root___timing_ready(vlSelf);
    Vtb_riscv___024root___trigger_orInto__act_vec_vec(vlSelfRef.__VactTriggered, vlSelfRef.__VactTriggeredAcc);
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vtb_riscv___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
    }
#endif
    Vtb_riscv___024root___trigger_orInto__act_vec_vec(vlSelfRef.__VnbaTriggered, vlSelfRef.__VactTriggered);
    __VactExecute = Vtb_riscv___024root___trigger_anySet__act(vlSelfRef.__VactTriggered);
    if (__VactExecute) {
        vlSelfRef.__VactTriggeredAcc.fill(0ULL);
        Vtb_riscv___024root___timing_resume(vlSelf);
    }
    return (__VactExecute);
}

bool Vtb_riscv___024root___eval_phase__inact(Vtb_riscv___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_riscv___024root___eval_phase__inact\n"); );
    Vtb_riscv__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VinactExecute;
    // Body
    __VinactExecute = vlSelfRef.__VdlySched.awaitingZeroDelay();
    if (__VinactExecute) {
        VL_FATAL_MT("tb_riscv.sv", 3, "", "ZERODLY: Design Verilated with '--no-sched-zero-delay', but #0 delay executed at runtime");
    }
    return (__VinactExecute);
}

void Vtb_riscv___024root___trigger_clear__act(VlUnpacked<QData/*63:0*/, 1> &out) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_riscv___024root___trigger_clear__act\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        out[n] = 0ULL;
        n = ((IData)(1U) + n);
    } while ((1U > n));
}

bool Vtb_riscv___024root___eval_phase__nba(Vtb_riscv___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_riscv___024root___eval_phase__nba\n"); );
    Vtb_riscv__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VnbaExecute;
    // Body
    __VnbaExecute = Vtb_riscv___024root___trigger_anySet__act(vlSelfRef.__VnbaTriggered);
    if (__VnbaExecute) {
        Vtb_riscv___024root___eval_nba(vlSelf);
        Vtb_riscv___024root___trigger_clear__act(vlSelfRef.__VnbaTriggered);
    }
    return (__VnbaExecute);
}

void Vtb_riscv___024root___eval(Vtb_riscv___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_riscv___024root___eval\n"); );
    Vtb_riscv__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ __VnbaIterCount;
    // Body
    __VnbaIterCount = 0U;
    do {
        if (VL_UNLIKELY(((0x00000064U < __VnbaIterCount)))) {
#ifdef VL_DEBUG
            Vtb_riscv___024root___dump_triggers__act(vlSelfRef.__VnbaTriggered, "nba"s);
#endif
            VL_FATAL_MT("tb_riscv.sv", 3, "", "DIDNOTCONVERGE: NBA region did not converge after '--converge-limit' of 100 tries");
        }
        __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
        vlSelfRef.__VinactIterCount = 0U;
        do {
            if (VL_UNLIKELY(((0x00000064U < vlSelfRef.__VinactIterCount)))) {
                VL_FATAL_MT("tb_riscv.sv", 3, "", "DIDNOTCONVERGE: Inactive region did not converge after '--converge-limit' of 100 tries");
            }
            vlSelfRef.__VinactIterCount = ((IData)(1U) 
                                           + vlSelfRef.__VinactIterCount);
            vlSelfRef.__VactIterCount = 0U;
            do {
                if (VL_UNLIKELY(((0x00000064U < vlSelfRef.__VactIterCount)))) {
#ifdef VL_DEBUG
                    Vtb_riscv___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
#endif
                    VL_FATAL_MT("tb_riscv.sv", 3, "", "DIDNOTCONVERGE: Active region did not converge after '--converge-limit' of 100 tries");
                }
                vlSelfRef.__VactIterCount = ((IData)(1U) 
                                             + vlSelfRef.__VactIterCount);
                vlSelfRef.__VactPhaseResult = Vtb_riscv___024root___eval_phase__act(vlSelf);
            } while (vlSelfRef.__VactPhaseResult);
            vlSelfRef.__VinactPhaseResult = Vtb_riscv___024root___eval_phase__inact(vlSelf);
        } while (vlSelfRef.__VinactPhaseResult);
        vlSelfRef.__VnbaPhaseResult = Vtb_riscv___024root___eval_phase__nba(vlSelf);
    } while (vlSelfRef.__VnbaPhaseResult);
}

void Vtb_riscv___024root____VbeforeTrig_h71169501__0(Vtb_riscv___024root* vlSelf, const char* __VeventDescription) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_riscv___024root____VbeforeTrig_h71169501__0\n"); );
    Vtb_riscv__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    VlUnpacked<QData/*63:0*/, 1> __VTmp;
    // Body
    __VTmp[0U] = (QData)((IData)(((IData)(vlSelfRef.tb_riscv__DOT__Clk) 
                                  & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_riscv__DOT__Clk__0)))));
    vlSelfRef.__Vtrigprevexpr___TOP__tb_riscv__DOT__Clk__0 
        = vlSelfRef.tb_riscv__DOT__Clk;
    if ((1ULL & __VTmp[0U])) {
        vlSelfRef.__VtrigSched_h71169501__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h71169501__0.ready(__VeventDescription);
    }
    vlSelfRef.__VactTriggeredAcc[0U] = (vlSelfRef.__VactTriggeredAcc[0U] 
                                        | __VTmp[0U]);
}

#ifdef VL_DEBUG
void Vtb_riscv___024root___eval_debug_assertions(Vtb_riscv___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_riscv___024root___eval_debug_assertions\n"); );
    Vtb_riscv__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}
#endif  // VL_DEBUG
