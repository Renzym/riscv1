// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtb_riscv.h for the primary calling header

#include "Vtb_riscv__pch.h"

void Vtb_riscv___024root___timing_ready(Vtb_riscv___024root* vlSelf);

VL_ATTR_COLD void Vtb_riscv___024root___eval_static(Vtb_riscv___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_riscv___024root___eval_static\n"); );
    Vtb_riscv__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__Vtrigprevexpr___TOP__tb_riscv__DOT__Clk__0 
        = vlSelfRef.tb_riscv__DOT__Clk;
    Vtb_riscv___024root___timing_ready(vlSelf);
    do {
        vlSelfRef.__VactTriggeredAcc[vlSelfRef.__Vi] 
            = vlSelfRef.__VactTriggered[vlSelfRef.__Vi];
        vlSelfRef.__Vi = ((IData)(1U) + vlSelfRef.__Vi);
    } while ((0U >= vlSelfRef.__Vi));
}

VL_ATTR_COLD void Vtb_riscv___024root___eval_initial__TOP(Vtb_riscv___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_riscv___024root___eval_initial__TOP\n"); );
    Vtb_riscv__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs[0U] = 0U;
    VL_READMEM_N(true, 32, 512, 0, "Program.hex"s,  &(vlSelfRef.tb_riscv__DOT__dut__DOT__ProgMemInst__DOT__RamArray)
                 , 0U, 0x000000ffU);
    VL_READMEM_N(true, 32, 512, 0, "Data.hex"s,  &(vlSelfRef.tb_riscv__DOT__dut__DOT__DataMemInst__DOT__RamArray)
                 , 0U, 0x000000ffU);
}

VL_ATTR_COLD void Vtb_riscv___024root___eval_final(Vtb_riscv___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_riscv___024root___eval_final\n"); );
    Vtb_riscv__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtb_riscv___024root___dump_triggers__stl(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG
VL_ATTR_COLD bool Vtb_riscv___024root___eval_phase__stl(Vtb_riscv___024root* vlSelf);

VL_ATTR_COLD void Vtb_riscv___024root___eval_settle(Vtb_riscv___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_riscv___024root___eval_settle\n"); );
    Vtb_riscv__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ __VstlIterCount;
    // Body
    __VstlIterCount = 0U;
    vlSelfRef.__VstlFirstIteration = 1U;
    do {
        if (VL_UNLIKELY(((0x00000064U < __VstlIterCount)))) {
#ifdef VL_DEBUG
            Vtb_riscv___024root___dump_triggers__stl(vlSelfRef.__VstlTriggered, "stl"s);
#endif
            VL_FATAL_MT("tb_riscv.sv", 4, "", "DIDNOTCONVERGE: Settle region did not converge after '--converge-limit' of 100 tries");
        }
        __VstlIterCount = ((IData)(1U) + __VstlIterCount);
        vlSelfRef.__VstlPhaseResult = Vtb_riscv___024root___eval_phase__stl(vlSelf);
        vlSelfRef.__VstlFirstIteration = 0U;
    } while (vlSelfRef.__VstlPhaseResult);
}

VL_ATTR_COLD void Vtb_riscv___024root___eval_triggers_vec__stl(Vtb_riscv___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_riscv___024root___eval_triggers_vec__stl\n"); );
    Vtb_riscv__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VstlTriggered[0U] = ((0xfffffffffffffffeULL 
                                      & vlSelfRef.__VstlTriggered[0U]) 
                                     | (IData)((IData)(vlSelfRef.__VstlFirstIteration)));
}

VL_ATTR_COLD bool Vtb_riscv___024root___trigger_anySet__stl(const VlUnpacked<QData/*63:0*/, 1> &in);

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtb_riscv___024root___dump_triggers__stl(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_riscv___024root___dump_triggers__stl\n"); );
    // Body
    if ((1U & (~ (IData)(Vtb_riscv___024root___trigger_anySet__stl(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: Internal 'stl' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD bool Vtb_riscv___024root___trigger_anySet__stl(const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_riscv___024root___trigger_anySet__stl\n"); );
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

VL_ATTR_COLD void Vtb_riscv___024root___stl_sequent__TOP__0(Vtb_riscv___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_riscv___024root___stl_sequent__TOP__0\n"); );
    Vtb_riscv__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ tb_riscv__DOT__dut__DOT__Instr;
    tb_riscv__DOT__dut__DOT__Instr = 0;
    CData/*0:0*/ tb_riscv__DOT__dut__DOT__JalPcSel;
    tb_riscv__DOT__dut__DOT__JalPcSel = 0;
    CData/*0:0*/ tb_riscv__DOT__dut__DOT__BrPcSel;
    tb_riscv__DOT__dut__DOT__BrPcSel = 0;
    IData/*31:0*/ tb_riscv__DOT__dut__DOT__RegSrc2;
    tb_riscv__DOT__dut__DOT__RegSrc2 = 0;
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
    IData/*31:0*/ tb_riscv__DOT__dut__DOT__DmemDout;
    tb_riscv__DOT__dut__DOT__DmemDout = 0;
    CData/*1:0*/ tb_riscv__DOT__dut__DOT__RegWb;
    tb_riscv__DOT__dut__DOT__RegWb = 0;
    CData/*0:0*/ tb_riscv__DOT__dut__DOT__DmemWr;
    tb_riscv__DOT__dut__DOT__DmemWr = 0;
    CData/*0:0*/ tb_riscv__DOT__dut__DOT__RegWrEn;
    tb_riscv__DOT__dut__DOT__RegWrEn = 0;
    CData/*3:0*/ tb_riscv__DOT__dut__DOT__StoreWrEnMask;
    tb_riscv__DOT__dut__DOT__StoreWrEnMask = 0;
    CData/*0:0*/ tb_riscv__DOT__dut__DOT____VdfgExtracted_h728d4a5a__0;
    tb_riscv__DOT__dut__DOT____VdfgExtracted_h728d4a5a__0 = 0;
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
    IData/*31:0*/ __Vfunc_GetImmediate__3__Vfuncout;
    __Vfunc_GetImmediate__3__Vfuncout = 0;
    IData/*31:0*/ __Vfunc_GetImmediate__3__RawInstr;
    __Vfunc_GetImmediate__3__RawInstr = 0;
    IData/*31:0*/ __Vfunc_GetImmediate__3__Instr;
    __Vfunc_GetImmediate__3__Instr = 0;
    // Body
    tb_riscv__DOT__dut__DOT__Instr = vlSelfRef.tb_riscv__DOT__dut__DOT__ProgMemInst__DOT__RamArray
        [(0x000001ffU & vlSelfRef.tb_riscv__DOT__dut__DOT__Pc)];
    tb_riscv__DOT__dut__DOT__DmemWr = (0x23U == ([&]() {
                vlSelfRef.__Vfunc_GetOpcode__39__RawInstr 
                    = tb_riscv__DOT__dut__DOT__Instr;
                vlSelfRef.__Vfunc_GetOpcode__39__Vfuncout 
                    = (0x0000007fU & vlSelfRef.__Vfunc_GetOpcode__39__RawInstr);
            }(), (IData)(vlSelfRef.__Vfunc_GetOpcode__39__Vfuncout)));
    tb_riscv__DOT__dut__DOT__JalPcSel = (0x67U == ([&]() {
                vlSelfRef.__Vfunc_GetOpcode__50__RawInstr 
                    = tb_riscv__DOT__dut__DOT__Instr;
                vlSelfRef.__Vfunc_GetOpcode__50__Vfuncout 
                    = (0x0000007fU & vlSelfRef.__Vfunc_GetOpcode__50__RawInstr);
            }(), (IData)(vlSelfRef.__Vfunc_GetOpcode__50__Vfuncout)));
    tb_riscv__DOT__dut__DOT__RegWrEn = (1U & (~ ((0x23U 
                                                  == 
                                                  ([&]() {
                            vlSelfRef.__Vfunc_GetOpcode__40__RawInstr 
                                = tb_riscv__DOT__dut__DOT__Instr;
                            vlSelfRef.__Vfunc_GetOpcode__40__Vfuncout 
                                = (0x0000007fU & vlSelfRef.__Vfunc_GetOpcode__40__RawInstr);
                        }(), (IData)(vlSelfRef.__Vfunc_GetOpcode__40__Vfuncout))) 
                                                 | (0x63U 
                                                    == 
                                                    ([&]() {
                            vlSelfRef.__Vfunc_GetOpcode__41__RawInstr 
                                = tb_riscv__DOT__dut__DOT__Instr;
                            vlSelfRef.__Vfunc_GetOpcode__41__Vfuncout 
                                = (0x0000007fU & vlSelfRef.__Vfunc_GetOpcode__41__RawInstr);
                        }(), (IData)(vlSelfRef.__Vfunc_GetOpcode__41__Vfuncout))))));
    tb_riscv__DOT__dut__DOT__RegWb = ((((0x33U == ([&]() {
                            vlSelfRef.__Vfunc_GetOpcode__42__RawInstr 
                                = tb_riscv__DOT__dut__DOT__Instr;
                            vlSelfRef.__Vfunc_GetOpcode__42__Vfuncout 
                                = (0x0000007fU & vlSelfRef.__Vfunc_GetOpcode__42__RawInstr);
                        }(), (IData)(vlSelfRef.__Vfunc_GetOpcode__42__Vfuncout))) 
                                        | (0x13U == 
                                           ([&]() {
                            vlSelfRef.__Vfunc_GetOpcode__43__RawInstr 
                                = tb_riscv__DOT__dut__DOT__Instr;
                            vlSelfRef.__Vfunc_GetOpcode__43__Vfuncout 
                                = (0x0000007fU & vlSelfRef.__Vfunc_GetOpcode__43__RawInstr);
                        }(), (IData)(vlSelfRef.__Vfunc_GetOpcode__43__Vfuncout)))) 
                                       | (0x17U == 
                                          ([&]() {
                        vlSelfRef.__Vfunc_GetOpcode__44__RawInstr 
                            = tb_riscv__DOT__dut__DOT__Instr;
                        vlSelfRef.__Vfunc_GetOpcode__44__Vfuncout 
                            = (0x0000007fU & vlSelfRef.__Vfunc_GetOpcode__44__RawInstr);
                    }(), (IData)(vlSelfRef.__Vfunc_GetOpcode__44__Vfuncout))))
                                       ? 0U : ((3U 
                                                == 
                                                ([&]() {
                        vlSelfRef.__Vfunc_GetOpcode__45__RawInstr 
                            = tb_riscv__DOT__dut__DOT__Instr;
                        vlSelfRef.__Vfunc_GetOpcode__45__Vfuncout 
                            = (0x0000007fU & vlSelfRef.__Vfunc_GetOpcode__45__RawInstr);
                    }(), (IData)(vlSelfRef.__Vfunc_GetOpcode__45__Vfuncout)))
                                                ? 1U
                                                : (
                                                   (0x37U 
                                                    == 
                                                    ([&]() {
                            vlSelfRef.__Vfunc_GetOpcode__46__RawInstr 
                                = tb_riscv__DOT__dut__DOT__Instr;
                            vlSelfRef.__Vfunc_GetOpcode__46__Vfuncout 
                                = (0x0000007fU & vlSelfRef.__Vfunc_GetOpcode__46__RawInstr);
                        }(), (IData)(vlSelfRef.__Vfunc_GetOpcode__46__Vfuncout)))
                                                    ? 3U
                                                    : 2U)));
    tb_riscv__DOT__dut__DOT__AluInst__DOT__Subtract 
        = (((0x33U == ([&]() {
                        vlSelfRef.__Vfunc_GetOpcode__51__RawInstr 
                            = tb_riscv__DOT__dut__DOT__Instr;
                        vlSelfRef.__Vfunc_GetOpcode__51__Vfuncout 
                            = (0x0000007fU & vlSelfRef.__Vfunc_GetOpcode__51__RawInstr);
                    }(), (IData)(vlSelfRef.__Vfunc_GetOpcode__51__Vfuncout))) 
            & (((IData)((0x40000000U == (0xfe007000U 
                                         & tb_riscv__DOT__dut__DOT__Instr))) 
                | (2U == (7U & (tb_riscv__DOT__dut__DOT__Instr 
                                >> 0x0000000cU)))) 
               | (3U == (7U & (tb_riscv__DOT__dut__DOT__Instr 
                               >> 0x0000000cU))))) 
           | ((0x63U == ([&]() {
                        vlSelfRef.__Vfunc_GetOpcode__52__RawInstr 
                            = tb_riscv__DOT__dut__DOT__Instr;
                        vlSelfRef.__Vfunc_GetOpcode__52__Vfuncout 
                            = (0x0000007fU & vlSelfRef.__Vfunc_GetOpcode__52__RawInstr);
                    }(), (IData)(vlSelfRef.__Vfunc_GetOpcode__52__Vfuncout))) 
              & ((0U == (7U & (tb_riscv__DOT__dut__DOT__Instr 
                               >> 0x0000000cU))) | 
                 (1U == (7U & (tb_riscv__DOT__dut__DOT__Instr 
                               >> 0x0000000cU))))));
    tb_riscv__DOT__dut__DOT__AuipcSel = (0x17U == ([&]() {
                vlSelfRef.__Vfunc_GetOpcode__47__RawInstr 
                    = tb_riscv__DOT__dut__DOT__Instr;
                vlSelfRef.__Vfunc_GetOpcode__47__Vfuncout 
                    = (0x0000007fU & vlSelfRef.__Vfunc_GetOpcode__47__RawInstr);
            }(), (IData)(vlSelfRef.__Vfunc_GetOpcode__47__Vfuncout)));
    tb_riscv__DOT__dut__DOT__Op2Sel = (1U & (~ ((0x33U 
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
    tb_riscv__DOT__dut__DOT__RegSrc2 = vlSelfRef.tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs
        [(0x0000001fU & (tb_riscv__DOT__dut__DOT__Instr 
                         >> 0x00000014U))];
    __Vfunc_GetImmediate__3__RawInstr = tb_riscv__DOT__dut__DOT__Instr;
    __Vfunc_GetImmediate__3__Instr = __Vfunc_GetImmediate__3__RawInstr;
    __Vfunc_GetImmediate__3__Vfuncout = ((0x00000040U 
                                          & ([&]() {
                    vlSelfRef.__Vfunc_GetOpcode__4__RawInstr 
                        = __Vfunc_GetImmediate__3__RawInstr;
                    vlSelfRef.__Vfunc_GetOpcode__4__Vfuncout 
                        = (0x0000007fU & vlSelfRef.__Vfunc_GetOpcode__4__RawInstr);
                }(), (IData)(vlSelfRef.__Vfunc_GetOpcode__4__Vfuncout)))
                                          ? ((0x00000020U 
                                              & ([&]() {
                        vlSelfRef.__Vfunc_GetOpcode__5__RawInstr 
                            = __Vfunc_GetImmediate__3__RawInstr;
                        vlSelfRef.__Vfunc_GetOpcode__5__Vfuncout 
                            = (0x0000007fU & vlSelfRef.__Vfunc_GetOpcode__5__RawInstr);
                    }(), (IData)(vlSelfRef.__Vfunc_GetOpcode__5__Vfuncout)))
                                              ? ((0x00000010U 
                                                  & ([&]() {
                            vlSelfRef.__Vfunc_GetOpcode__6__RawInstr 
                                = __Vfunc_GetImmediate__3__RawInstr;
                            vlSelfRef.__Vfunc_GetOpcode__6__Vfuncout 
                                = (0x0000007fU & vlSelfRef.__Vfunc_GetOpcode__6__RawInstr);
                        }(), (IData)(vlSelfRef.__Vfunc_GetOpcode__6__Vfuncout)))
                                                  ? 0U
                                                  : 
                                                 ((8U 
                                                   & ([&]() {
                                vlSelfRef.__Vfunc_GetOpcode__7__RawInstr 
                                    = __Vfunc_GetImmediate__3__RawInstr;
                                vlSelfRef.__Vfunc_GetOpcode__7__Vfuncout 
                                    = (0x0000007fU 
                                       & vlSelfRef.__Vfunc_GetOpcode__7__RawInstr);
                            }(), (IData)(vlSelfRef.__Vfunc_GetOpcode__7__Vfuncout)))
                                                   ? 
                                                  ((4U 
                                                    & ([&]() {
                                    vlSelfRef.__Vfunc_GetOpcode__8__RawInstr 
                                        = __Vfunc_GetImmediate__3__RawInstr;
                                    vlSelfRef.__Vfunc_GetOpcode__8__Vfuncout 
                                        = (0x0000007fU 
                                           & vlSelfRef.__Vfunc_GetOpcode__8__RawInstr);
                                }(), (IData)(vlSelfRef.__Vfunc_GetOpcode__8__Vfuncout)))
                                                    ? 
                                                   ((2U 
                                                     & ([&]() {
                                        vlSelfRef.__Vfunc_GetOpcode__9__RawInstr 
                                            = __Vfunc_GetImmediate__3__RawInstr;
                                        vlSelfRef.__Vfunc_GetOpcode__9__Vfuncout 
                                            = (0x0000007fU 
                                               & vlSelfRef.__Vfunc_GetOpcode__9__RawInstr);
                                    }(), (IData)(vlSelfRef.__Vfunc_GetOpcode__9__Vfuncout)))
                                                     ? 
                                                    ((1U 
                                                      & ([&]() {
                                            vlSelfRef.__Vfunc_GetOpcode__10__RawInstr 
                                                = __Vfunc_GetImmediate__3__RawInstr;
                                            vlSelfRef.__Vfunc_GetOpcode__10__Vfuncout 
                                                = (0x0000007fU 
                                                   & vlSelfRef.__Vfunc_GetOpcode__10__RawInstr);
                                        }(), (IData)(vlSelfRef.__Vfunc_GetOpcode__10__Vfuncout)))
                                                      ? 
                                                     ((((0x00000ffeU 
                                                         & ((- (IData)(
                                                                       (__Vfunc_GetImmediate__3__Instr 
                                                                        >> 0x0000001fU))) 
                                                            << 1U)) 
                                                        | (__Vfunc_GetImmediate__3__Instr 
                                                           >> 0x0000001fU)) 
                                                       << 0x00000014U) 
                                                      | ((((0x000001feU 
                                                            & (__Vfunc_GetImmediate__3__Instr 
                                                               >> 0x0000000bU)) 
                                                           | (1U 
                                                              & (__Vfunc_GetImmediate__3__Instr 
                                                                 >> 0x00000014U))) 
                                                          << 0x0000000bU) 
                                                         | (0x000007feU 
                                                            & (__Vfunc_GetImmediate__3__Instr 
                                                               >> 0x00000014U))))
                                                      : 0U)
                                                     : 0U)
                                                    : 0U)
                                                   : 
                                                  ((4U 
                                                    & ([&]() {
                                    vlSelfRef.__Vfunc_GetOpcode__11__RawInstr 
                                        = __Vfunc_GetImmediate__3__RawInstr;
                                    vlSelfRef.__Vfunc_GetOpcode__11__Vfuncout 
                                        = (0x0000007fU 
                                           & vlSelfRef.__Vfunc_GetOpcode__11__RawInstr);
                                }(), (IData)(vlSelfRef.__Vfunc_GetOpcode__11__Vfuncout)))
                                                    ? 
                                                   ((2U 
                                                     & ([&]() {
                                        vlSelfRef.__Vfunc_GetOpcode__12__RawInstr 
                                            = __Vfunc_GetImmediate__3__RawInstr;
                                        vlSelfRef.__Vfunc_GetOpcode__12__Vfuncout 
                                            = (0x0000007fU 
                                               & vlSelfRef.__Vfunc_GetOpcode__12__RawInstr);
                                    }(), (IData)(vlSelfRef.__Vfunc_GetOpcode__12__Vfuncout)))
                                                     ? 
                                                    ((1U 
                                                      & ([&]() {
                                            vlSelfRef.__Vfunc_GetOpcode__13__RawInstr 
                                                = __Vfunc_GetImmediate__3__RawInstr;
                                            vlSelfRef.__Vfunc_GetOpcode__13__Vfuncout 
                                                = (0x0000007fU 
                                                   & vlSelfRef.__Vfunc_GetOpcode__13__RawInstr);
                                        }(), (IData)(vlSelfRef.__Vfunc_GetOpcode__13__Vfuncout)))
                                                      ? 
                                                     (((- (IData)(
                                                                  (__Vfunc_GetImmediate__3__Instr 
                                                                   >> 0x0000001fU))) 
                                                       << 0x0000000cU) 
                                                      | (__Vfunc_GetImmediate__3__Instr 
                                                         >> 0x00000014U))
                                                      : 0U)
                                                     : 0U)
                                                    : 
                                                   ((2U 
                                                     & ([&]() {
                                        vlSelfRef.__Vfunc_GetOpcode__14__RawInstr 
                                            = __Vfunc_GetImmediate__3__RawInstr;
                                        vlSelfRef.__Vfunc_GetOpcode__14__Vfuncout 
                                            = (0x0000007fU 
                                               & vlSelfRef.__Vfunc_GetOpcode__14__RawInstr);
                                    }(), (IData)(vlSelfRef.__Vfunc_GetOpcode__14__Vfuncout)))
                                                     ? 
                                                    ((1U 
                                                      & ([&]() {
                                            vlSelfRef.__Vfunc_GetOpcode__15__RawInstr 
                                                = __Vfunc_GetImmediate__3__RawInstr;
                                            vlSelfRef.__Vfunc_GetOpcode__15__Vfuncout 
                                                = (0x0000007fU 
                                                   & vlSelfRef.__Vfunc_GetOpcode__15__RawInstr);
                                        }(), (IData)(vlSelfRef.__Vfunc_GetOpcode__15__Vfuncout)))
                                                      ? 
                                                     (((- (IData)(
                                                                  (__Vfunc_GetImmediate__3__Instr 
                                                                   >> 0x0000001fU))) 
                                                       << 0x0000000dU) 
                                                      | ((((2U 
                                                            & (__Vfunc_GetImmediate__3__Instr 
                                                               >> 0x0000001eU)) 
                                                           | (1U 
                                                              & (__Vfunc_GetImmediate__3__Instr 
                                                                 >> 7U))) 
                                                          << 0x0000000bU) 
                                                         | ((0x000007e0U 
                                                             & (__Vfunc_GetImmediate__3__Instr 
                                                                >> 0x00000014U)) 
                                                            | (0x0000001eU 
                                                               & (__Vfunc_GetImmediate__3__Instr 
                                                                  >> 7U)))))
                                                      : 0U)
                                                     : 0U))))
                                              : 0U)
                                          : ((0x00000020U 
                                              & ([&]() {
                        vlSelfRef.__Vfunc_GetOpcode__16__RawInstr 
                            = __Vfunc_GetImmediate__3__RawInstr;
                        vlSelfRef.__Vfunc_GetOpcode__16__Vfuncout 
                            = (0x0000007fU & vlSelfRef.__Vfunc_GetOpcode__16__RawInstr);
                    }(), (IData)(vlSelfRef.__Vfunc_GetOpcode__16__Vfuncout)))
                                              ? ((0x00000010U 
                                                  & ([&]() {
                            vlSelfRef.__Vfunc_GetOpcode__17__RawInstr 
                                = __Vfunc_GetImmediate__3__RawInstr;
                            vlSelfRef.__Vfunc_GetOpcode__17__Vfuncout 
                                = (0x0000007fU & vlSelfRef.__Vfunc_GetOpcode__17__RawInstr);
                        }(), (IData)(vlSelfRef.__Vfunc_GetOpcode__17__Vfuncout)))
                                                  ? 
                                                 ((8U 
                                                   & ([&]() {
                                vlSelfRef.__Vfunc_GetOpcode__18__RawInstr 
                                    = __Vfunc_GetImmediate__3__RawInstr;
                                vlSelfRef.__Vfunc_GetOpcode__18__Vfuncout 
                                    = (0x0000007fU 
                                       & vlSelfRef.__Vfunc_GetOpcode__18__RawInstr);
                            }(), (IData)(vlSelfRef.__Vfunc_GetOpcode__18__Vfuncout)))
                                                   ? 0U
                                                   : 
                                                  ((4U 
                                                    & ([&]() {
                                    vlSelfRef.__Vfunc_GetOpcode__19__RawInstr 
                                        = __Vfunc_GetImmediate__3__RawInstr;
                                    vlSelfRef.__Vfunc_GetOpcode__19__Vfuncout 
                                        = (0x0000007fU 
                                           & vlSelfRef.__Vfunc_GetOpcode__19__RawInstr);
                                }(), (IData)(vlSelfRef.__Vfunc_GetOpcode__19__Vfuncout)))
                                                    ? 
                                                   ((2U 
                                                     & ([&]() {
                                        vlSelfRef.__Vfunc_GetOpcode__20__RawInstr 
                                            = __Vfunc_GetImmediate__3__RawInstr;
                                        vlSelfRef.__Vfunc_GetOpcode__20__Vfuncout 
                                            = (0x0000007fU 
                                               & vlSelfRef.__Vfunc_GetOpcode__20__RawInstr);
                                    }(), (IData)(vlSelfRef.__Vfunc_GetOpcode__20__Vfuncout)))
                                                     ? 
                                                    ((1U 
                                                      & ([&]() {
                                            vlSelfRef.__Vfunc_GetOpcode__21__RawInstr 
                                                = __Vfunc_GetImmediate__3__RawInstr;
                                            vlSelfRef.__Vfunc_GetOpcode__21__Vfuncout 
                                                = (0x0000007fU 
                                                   & vlSelfRef.__Vfunc_GetOpcode__21__RawInstr);
                                        }(), (IData)(vlSelfRef.__Vfunc_GetOpcode__21__Vfuncout)))
                                                      ? 
                                                     (0xfffff000U 
                                                      & __Vfunc_GetImmediate__3__Instr)
                                                      : 0U)
                                                     : 0U)
                                                    : 0U))
                                                  : 
                                                 ((8U 
                                                   & ([&]() {
                                vlSelfRef.__Vfunc_GetOpcode__22__RawInstr 
                                    = __Vfunc_GetImmediate__3__RawInstr;
                                vlSelfRef.__Vfunc_GetOpcode__22__Vfuncout 
                                    = (0x0000007fU 
                                       & vlSelfRef.__Vfunc_GetOpcode__22__RawInstr);
                            }(), (IData)(vlSelfRef.__Vfunc_GetOpcode__22__Vfuncout)))
                                                   ? 0U
                                                   : 
                                                  ((4U 
                                                    & ([&]() {
                                    vlSelfRef.__Vfunc_GetOpcode__23__RawInstr 
                                        = __Vfunc_GetImmediate__3__RawInstr;
                                    vlSelfRef.__Vfunc_GetOpcode__23__Vfuncout 
                                        = (0x0000007fU 
                                           & vlSelfRef.__Vfunc_GetOpcode__23__RawInstr);
                                }(), (IData)(vlSelfRef.__Vfunc_GetOpcode__23__Vfuncout)))
                                                    ? 0U
                                                    : 
                                                   ((2U 
                                                     & ([&]() {
                                        vlSelfRef.__Vfunc_GetOpcode__24__RawInstr 
                                            = __Vfunc_GetImmediate__3__RawInstr;
                                        vlSelfRef.__Vfunc_GetOpcode__24__Vfuncout 
                                            = (0x0000007fU 
                                               & vlSelfRef.__Vfunc_GetOpcode__24__RawInstr);
                                    }(), (IData)(vlSelfRef.__Vfunc_GetOpcode__24__Vfuncout)))
                                                     ? 
                                                    ((1U 
                                                      & ([&]() {
                                            vlSelfRef.__Vfunc_GetOpcode__25__RawInstr 
                                                = __Vfunc_GetImmediate__3__RawInstr;
                                            vlSelfRef.__Vfunc_GetOpcode__25__Vfuncout 
                                                = (0x0000007fU 
                                                   & vlSelfRef.__Vfunc_GetOpcode__25__RawInstr);
                                        }(), (IData)(vlSelfRef.__Vfunc_GetOpcode__25__Vfuncout)))
                                                      ? 
                                                     (((- (IData)(
                                                                  (__Vfunc_GetImmediate__3__Instr 
                                                                   >> 0x0000001fU))) 
                                                       << 0x0000000cU) 
                                                      | ((0x00000fe0U 
                                                          & (__Vfunc_GetImmediate__3__Instr 
                                                             >> 0x00000014U)) 
                                                         | (0x0000001fU 
                                                            & (__Vfunc_GetImmediate__3__Instr 
                                                               >> 7U))))
                                                      : 0U)
                                                     : 0U))))
                                              : ((0x00000010U 
                                                  & ([&]() {
                            vlSelfRef.__Vfunc_GetOpcode__26__RawInstr 
                                = __Vfunc_GetImmediate__3__RawInstr;
                            vlSelfRef.__Vfunc_GetOpcode__26__Vfuncout 
                                = (0x0000007fU & vlSelfRef.__Vfunc_GetOpcode__26__RawInstr);
                        }(), (IData)(vlSelfRef.__Vfunc_GetOpcode__26__Vfuncout)))
                                                  ? 
                                                 ((8U 
                                                   & ([&]() {
                                vlSelfRef.__Vfunc_GetOpcode__27__RawInstr 
                                    = __Vfunc_GetImmediate__3__RawInstr;
                                vlSelfRef.__Vfunc_GetOpcode__27__Vfuncout 
                                    = (0x0000007fU 
                                       & vlSelfRef.__Vfunc_GetOpcode__27__RawInstr);
                            }(), (IData)(vlSelfRef.__Vfunc_GetOpcode__27__Vfuncout)))
                                                   ? 0U
                                                   : 
                                                  ((4U 
                                                    & ([&]() {
                                    vlSelfRef.__Vfunc_GetOpcode__28__RawInstr 
                                        = __Vfunc_GetImmediate__3__RawInstr;
                                    vlSelfRef.__Vfunc_GetOpcode__28__Vfuncout 
                                        = (0x0000007fU 
                                           & vlSelfRef.__Vfunc_GetOpcode__28__RawInstr);
                                }(), (IData)(vlSelfRef.__Vfunc_GetOpcode__28__Vfuncout)))
                                                    ? 
                                                   ((2U 
                                                     & ([&]() {
                                        vlSelfRef.__Vfunc_GetOpcode__29__RawInstr 
                                            = __Vfunc_GetImmediate__3__RawInstr;
                                        vlSelfRef.__Vfunc_GetOpcode__29__Vfuncout 
                                            = (0x0000007fU 
                                               & vlSelfRef.__Vfunc_GetOpcode__29__RawInstr);
                                    }(), (IData)(vlSelfRef.__Vfunc_GetOpcode__29__Vfuncout)))
                                                     ? 
                                                    ((1U 
                                                      & ([&]() {
                                            vlSelfRef.__Vfunc_GetOpcode__30__RawInstr 
                                                = __Vfunc_GetImmediate__3__RawInstr;
                                            vlSelfRef.__Vfunc_GetOpcode__30__Vfuncout 
                                                = (0x0000007fU 
                                                   & vlSelfRef.__Vfunc_GetOpcode__30__RawInstr);
                                        }(), (IData)(vlSelfRef.__Vfunc_GetOpcode__30__Vfuncout)))
                                                      ? 
                                                     (0xfffff000U 
                                                      & __Vfunc_GetImmediate__3__Instr)
                                                      : 0U)
                                                     : 0U)
                                                    : 
                                                   ((2U 
                                                     & ([&]() {
                                        vlSelfRef.__Vfunc_GetOpcode__31__RawInstr 
                                            = __Vfunc_GetImmediate__3__RawInstr;
                                        vlSelfRef.__Vfunc_GetOpcode__31__Vfuncout 
                                            = (0x0000007fU 
                                               & vlSelfRef.__Vfunc_GetOpcode__31__RawInstr);
                                    }(), (IData)(vlSelfRef.__Vfunc_GetOpcode__31__Vfuncout)))
                                                     ? 
                                                    ((1U 
                                                      & ([&]() {
                                            vlSelfRef.__Vfunc_GetOpcode__32__RawInstr 
                                                = __Vfunc_GetImmediate__3__RawInstr;
                                            vlSelfRef.__Vfunc_GetOpcode__32__Vfuncout 
                                                = (0x0000007fU 
                                                   & vlSelfRef.__Vfunc_GetOpcode__32__RawInstr);
                                        }(), (IData)(vlSelfRef.__Vfunc_GetOpcode__32__Vfuncout)))
                                                      ? 
                                                     (((- (IData)(
                                                                  (__Vfunc_GetImmediate__3__Instr 
                                                                   >> 0x0000001fU))) 
                                                       << 0x0000000cU) 
                                                      | (__Vfunc_GetImmediate__3__Instr 
                                                         >> 0x00000014U))
                                                      : 0U)
                                                     : 0U)))
                                                  : 
                                                 ((8U 
                                                   & ([&]() {
                                vlSelfRef.__Vfunc_GetOpcode__33__RawInstr 
                                    = __Vfunc_GetImmediate__3__RawInstr;
                                vlSelfRef.__Vfunc_GetOpcode__33__Vfuncout 
                                    = (0x0000007fU 
                                       & vlSelfRef.__Vfunc_GetOpcode__33__RawInstr);
                            }(), (IData)(vlSelfRef.__Vfunc_GetOpcode__33__Vfuncout)))
                                                   ? 0U
                                                   : 
                                                  ((4U 
                                                    & ([&]() {
                                    vlSelfRef.__Vfunc_GetOpcode__34__RawInstr 
                                        = __Vfunc_GetImmediate__3__RawInstr;
                                    vlSelfRef.__Vfunc_GetOpcode__34__Vfuncout 
                                        = (0x0000007fU 
                                           & vlSelfRef.__Vfunc_GetOpcode__34__RawInstr);
                                }(), (IData)(vlSelfRef.__Vfunc_GetOpcode__34__Vfuncout)))
                                                    ? 0U
                                                    : 
                                                   ((2U 
                                                     & ([&]() {
                                        vlSelfRef.__Vfunc_GetOpcode__35__RawInstr 
                                            = __Vfunc_GetImmediate__3__RawInstr;
                                        vlSelfRef.__Vfunc_GetOpcode__35__Vfuncout 
                                            = (0x0000007fU 
                                               & vlSelfRef.__Vfunc_GetOpcode__35__RawInstr);
                                    }(), (IData)(vlSelfRef.__Vfunc_GetOpcode__35__Vfuncout)))
                                                     ? 
                                                    ((1U 
                                                      & ([&]() {
                                            vlSelfRef.__Vfunc_GetOpcode__36__RawInstr 
                                                = __Vfunc_GetImmediate__3__RawInstr;
                                            vlSelfRef.__Vfunc_GetOpcode__36__Vfuncout 
                                                = (0x0000007fU 
                                                   & vlSelfRef.__Vfunc_GetOpcode__36__RawInstr);
                                        }(), (IData)(vlSelfRef.__Vfunc_GetOpcode__36__Vfuncout)))
                                                      ? 
                                                     (((- (IData)(
                                                                  (__Vfunc_GetImmediate__3__Instr 
                                                                   >> 0x0000001fU))) 
                                                       << 0x0000000cU) 
                                                      | (__Vfunc_GetImmediate__3__Instr 
                                                         >> 0x00000014U))
                                                      : 0U)
                                                     : 0U))))));
    tb_riscv__DOT__dut__DOT__ImmExt = __Vfunc_GetImmediate__3__Vfuncout;
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
                VL_WRITEF_NX("[%0t] %%Error: Riscv.sv:184: Assertion failed in %Ntb_riscv.dut: unique case, but multiple matches found for '32'h%x'\n",0,
                             64,VL_TIME_UNITED_Q(1000),
                             -9,vlSymsp->name(),32,
                             (IData)(tb_riscv__DOT__dut__DOT__RegWb));
                VL_STOP_MT("Riscv.sv", 184, "");
            }
        }
    }
    tb_riscv__DOT__dut__DOT__AluOp1 = ((IData)(tb_riscv__DOT__dut__DOT__AuipcSel)
                                        ? vlSelfRef.tb_riscv__DOT__dut__DOT__Pc
                                        : vlSelfRef.tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs
                                       [(0x0000001fU 
                                         & (tb_riscv__DOT__dut__DOT__Instr 
                                            >> 0x0000000fU))]);
    vlSelfRef.tb_riscv__DOT__dut__DOT__DmemWrData = tb_riscv__DOT__dut__DOT__RegSrc2;
    if ((0x23U == ([&]() {
                    vlSelfRef.__Vfunc_GetOpcode__0__RawInstr 
                        = tb_riscv__DOT__dut__DOT__Instr;
                    vlSelfRef.__Vfunc_GetOpcode__0__Vfuncout 
                        = (0x0000007fU & vlSelfRef.__Vfunc_GetOpcode__0__RawInstr);
                }(), (IData)(vlSelfRef.__Vfunc_GetOpcode__0__Vfuncout)))) {
        if ((0U == (7U & (tb_riscv__DOT__dut__DOT__Instr 
                          >> 0x0000000cU)))) {
            vlSelfRef.tb_riscv__DOT__dut__DOT__DmemWrData 
                = ((tb_riscv__DOT__dut__DOT__RegSrc2 
                    << 0x00000018U) | ((0x00ff0000U 
                                        & (tb_riscv__DOT__dut__DOT__RegSrc2 
                                           << 0x00000010U)) 
                                       | ((0x0000ff00U 
                                           & (tb_riscv__DOT__dut__DOT__RegSrc2 
                                              << 8U)) 
                                          | (0x000000ffU 
                                             & tb_riscv__DOT__dut__DOT__RegSrc2))));
        } else if ((1U == (7U & (tb_riscv__DOT__dut__DOT__Instr 
                                 >> 0x0000000cU)))) {
            vlSelfRef.tb_riscv__DOT__dut__DOT__DmemWrData 
                = ((tb_riscv__DOT__dut__DOT__RegSrc2 
                    << 0x00000010U) | (0x0000ffffU 
                                       & tb_riscv__DOT__dut__DOT__RegSrc2));
        }
        if (VL_UNLIKELY(((1U & (~ VL_ONEHOT_I((((1U 
                                                 == 
                                                 (7U 
                                                  & (tb_riscv__DOT__dut__DOT__Instr 
                                                     >> 0x0000000cU))) 
                                                << 1U) 
                                               | (0U 
                                                  == 
                                                  (7U 
                                                   & (tb_riscv__DOT__dut__DOT__Instr 
                                                      >> 0x0000000cU)))))))))) {
            if ((0U != (((1U == (7U & (tb_riscv__DOT__dut__DOT__Instr 
                                       >> 0x0000000cU))) 
                         << 1U) | (0U == (7U & (tb_riscv__DOT__dut__DOT__Instr 
                                                >> 0x0000000cU)))))) {
                if (VL_UNLIKELY((vlSymsp->_vm_contextp__->assertOn()))) {
                    VL_WRITEF_NX("[%0t] %%Error: Riscv.sv:109: Assertion failed in %Ntb_riscv.dut: unique case, but multiple matches found for '3'h%x'\n",0,
                                 64,VL_TIME_UNITED_Q(1000),
                                 -9,vlSymsp->name(),
                                 3,(7U & (tb_riscv__DOT__dut__DOT__Instr 
                                          >> 0x0000000cU)));
                    VL_STOP_MT("Riscv.sv", 109, "");
                }
            }
        }
    }
    tb_riscv__DOT__dut__DOT__AluOp2 = ((IData)(tb_riscv__DOT__dut__DOT__Op2Sel)
                                        ? tb_riscv__DOT__dut__DOT__ImmExt
                                        : tb_riscv__DOT__dut__DOT__RegSrc2);
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
                    vlSelfRef.__Vfunc_GetOpcode__48__RawInstr 
                        = tb_riscv__DOT__dut__DOT__Instr;
                    vlSelfRef.__Vfunc_GetOpcode__48__Vfuncout 
                        = (0x0000007fU & vlSelfRef.__Vfunc_GetOpcode__48__RawInstr);
                }(), (IData)(vlSelfRef.__Vfunc_GetOpcode__48__Vfuncout))) 
                                        | ((0x63U == 
                                            ([&]() {
                        vlSelfRef.__Vfunc_GetOpcode__49__RawInstr 
                            = tb_riscv__DOT__dut__DOT__Instr;
                        vlSelfRef.__Vfunc_GetOpcode__49__Vfuncout 
                            = (0x0000007fU & vlSelfRef.__Vfunc_GetOpcode__49__RawInstr);
                    }(), (IData)(vlSelfRef.__Vfunc_GetOpcode__49__Vfuncout))) 
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
    vlSelfRef.tb_riscv__DOT__dut__DOT__PcNxt = ((IData)(tb_riscv__DOT__dut__DOT__JalPcSel)
                                                 ? vlSelfRef.tb_riscv__DOT__dut__DOT__AluOut
                                                 : 
                                                (vlSelfRef.tb_riscv__DOT__dut__DOT__Pc 
                                                 + 
                                                 ((IData)(tb_riscv__DOT__dut__DOT__BrPcSel)
                                                   ? tb_riscv__DOT__dut__DOT__ImmExt
                                                   : 4U)));
    tb_riscv__DOT__dut__DOT__StoreWrEnMask = 0U;
    if ((0x23U == ([&]() {
                    vlSelfRef.__Vfunc_GetOpcode__2__RawInstr 
                        = tb_riscv__DOT__dut__DOT__Instr;
                    vlSelfRef.__Vfunc_GetOpcode__2__Vfuncout 
                        = (0x0000007fU & vlSelfRef.__Vfunc_GetOpcode__2__RawInstr);
                }(), (IData)(vlSelfRef.__Vfunc_GetOpcode__2__Vfuncout)))) {
        tb_riscv__DOT__dut__DOT__StoreWrEnMask = ((2U 
                                                   == 
                                                   (7U 
                                                    & (tb_riscv__DOT__dut__DOT__Instr 
                                                       >> 0x0000000cU)))
                                                   ? 0x0fU
                                                   : 
                                                  ((1U 
                                                    == 
                                                    (7U 
                                                     & (tb_riscv__DOT__dut__DOT__Instr 
                                                        >> 0x0000000cU)))
                                                    ? 
                                                   ((2U 
                                                     & vlSelfRef.tb_riscv__DOT__dut__DOT__AluOut)
                                                     ? 0x0cU
                                                     : 3U)
                                                    : 
                                                   ((0U 
                                                     == 
                                                     (7U 
                                                      & (tb_riscv__DOT__dut__DOT__Instr 
                                                         >> 0x0000000cU)))
                                                     ? 
                                                    ((2U 
                                                      & vlSelfRef.tb_riscv__DOT__dut__DOT__AluOut)
                                                      ? 
                                                     ((1U 
                                                       & vlSelfRef.tb_riscv__DOT__dut__DOT__AluOut)
                                                       ? 8U
                                                       : 4U)
                                                      : 
                                                     ((1U 
                                                       & vlSelfRef.tb_riscv__DOT__dut__DOT__AluOut)
                                                       ? 2U
                                                       : 1U))
                                                     : 0U)));
        if (VL_UNLIKELY(((1U & (~ VL_ONEHOT_I((((0U 
                                                 == 
                                                 (7U 
                                                  & (tb_riscv__DOT__dut__DOT__Instr 
                                                     >> 0x0000000cU))) 
                                                << 2U) 
                                               | (((1U 
                                                    == 
                                                    (7U 
                                                     & (tb_riscv__DOT__dut__DOT__Instr 
                                                        >> 0x0000000cU))) 
                                                   << 1U) 
                                                  | (2U 
                                                     == 
                                                     (7U 
                                                      & (tb_riscv__DOT__dut__DOT__Instr 
                                                         >> 0x0000000cU))))))))))) {
            if ((0U != (((0U == (7U & (tb_riscv__DOT__dut__DOT__Instr 
                                       >> 0x0000000cU))) 
                         << 2U) | (((1U == (7U & (tb_riscv__DOT__dut__DOT__Instr 
                                                  >> 0x0000000cU))) 
                                    << 1U) | (2U == 
                                              (7U & 
                                               (tb_riscv__DOT__dut__DOT__Instr 
                                                >> 0x0000000cU))))))) {
                if (VL_UNLIKELY((vlSymsp->_vm_contextp__->assertOn()))) {
                    VL_WRITEF_NX("[%0t] %%Error: Riscv.sv:168: Assertion failed in %Ntb_riscv.dut: unique case, but multiple matches found for '3'h%x'\n",0,
                                 64,VL_TIME_UNITED_Q(1000),
                                 -9,vlSymsp->name(),
                                 3,(7U & (tb_riscv__DOT__dut__DOT__Instr 
                                          >> 0x0000000cU)));
                    VL_STOP_MT("Riscv.sv", 168, "");
                }
            }
        }
    }
    tb_riscv__DOT__dut__DOT____VdfgExtracted_h728d4a5a__0 
        = (0U == ((2U & vlSelfRef.tb_riscv__DOT__dut__DOT__AluOut) 
                  | (1U & (~ (vlSelfRef.tb_riscv__DOT__dut__DOT__AluOut 
                              >> 1U)))));
    tb_riscv__DOT__dut__DOT__DmemDout = vlSelfRef.tb_riscv__DOT__dut__DOT__DataMemInst__DOT__RamArray
        [(0x000001ffU & (vlSelfRef.tb_riscv__DOT__dut__DOT__AluOut 
                         >> 2U))];
    vlSelfRef.tb_riscv__DOT__dut__DOT__DmemWrEn = ((IData)(tb_riscv__DOT__dut__DOT__DmemWr)
                                                    ? (IData)(tb_riscv__DOT__dut__DOT__StoreWrEnMask)
                                                    : 0U);
    if ((3U != ([&]() {
                    vlSelfRef.__Vfunc_GetOpcode__1__RawInstr 
                        = tb_riscv__DOT__dut__DOT__Instr;
                    vlSelfRef.__Vfunc_GetOpcode__1__Vfuncout 
                        = (0x0000007fU & vlSelfRef.__Vfunc_GetOpcode__1__RawInstr);
                }(), (IData)(vlSelfRef.__Vfunc_GetOpcode__1__Vfuncout)))) {
        vlSelfRef.tb_riscv__DOT__dut__DOT__LoadWbData 
            = tb_riscv__DOT__dut__DOT__DmemDout;
    } else if ((0x00004000U & tb_riscv__DOT__dut__DOT__Instr)) {
        if ((0x00002000U & tb_riscv__DOT__dut__DOT__Instr)) {
            vlSelfRef.tb_riscv__DOT__dut__DOT__LoadWbData 
                = tb_riscv__DOT__dut__DOT__DmemDout;
        } else if ((0x00001000U & tb_riscv__DOT__dut__DOT__Instr)) {
            if ((2U & vlSelfRef.tb_riscv__DOT__dut__DOT__AluOut)) {
                if ((2U & vlSelfRef.tb_riscv__DOT__dut__DOT__AluOut)) {
                    vlSelfRef.tb_riscv__DOT__dut__DOT__LoadWbData 
                        = (tb_riscv__DOT__dut__DOT__DmemDout 
                           >> 0x10U);
                }
            } else {
                vlSelfRef.tb_riscv__DOT__dut__DOT__LoadWbData 
                    = (0x0000ffffU & tb_riscv__DOT__dut__DOT__DmemDout);
            }
            if (VL_UNLIKELY(((1U & (~ VL_ONEHOT_I((
                                                   (2U 
                                                    & vlSelfRef.tb_riscv__DOT__dut__DOT__AluOut) 
                                                   | (1U 
                                                      & (~ 
                                                         (vlSelfRef.tb_riscv__DOT__dut__DOT__AluOut 
                                                          >> 1U)))))))))) {
                if (tb_riscv__DOT__dut__DOT____VdfgExtracted_h728d4a5a__0) {
                    if (VL_UNLIKELY((vlSymsp->_vm_contextp__->assertOn()))) {
                        VL_WRITEF_NX("[%0t] %%Error: Riscv.sv:157: Assertion failed in %Ntb_riscv.dut: unique case, but none matched for '1'h%x'\n",0,
                                     64,VL_TIME_UNITED_Q(1000),
                                     -9,vlSymsp->name(),
                                     1,(1U & (vlSelfRef.tb_riscv__DOT__dut__DOT__AluOut 
                                              >> 1U)));
                        VL_STOP_MT("Riscv.sv", 157, "");
                    }
                } else if (VL_UNLIKELY((vlSymsp->_vm_contextp__->assertOn()))) {
                    VL_WRITEF_NX("[%0t] %%Error: Riscv.sv:157: Assertion failed in %Ntb_riscv.dut: unique case, but multiple matches found for '1'h%x'\n",0,
                                 64,VL_TIME_UNITED_Q(1000),
                                 -9,vlSymsp->name(),
                                 1,(1U & (vlSelfRef.tb_riscv__DOT__dut__DOT__AluOut 
                                          >> 1U)));
                    VL_STOP_MT("Riscv.sv", 157, "");
                }
            }
        } else {
            vlSelfRef.tb_riscv__DOT__dut__DOT__LoadWbData 
                = ((2U & vlSelfRef.tb_riscv__DOT__dut__DOT__AluOut)
                    ? ((1U & vlSelfRef.tb_riscv__DOT__dut__DOT__AluOut)
                        ? (tb_riscv__DOT__dut__DOT__DmemDout 
                           >> 0x18U) : (0x000000ffU 
                                        & (tb_riscv__DOT__dut__DOT__DmemDout 
                                           >> 0x10U)))
                    : ((1U & vlSelfRef.tb_riscv__DOT__dut__DOT__AluOut)
                        ? (0x000000ffU & (tb_riscv__DOT__dut__DOT__DmemDout 
                                          >> 8U)) : 
                       (0x000000ffU & tb_riscv__DOT__dut__DOT__DmemDout)));
        }
    } else if ((0x00002000U & tb_riscv__DOT__dut__DOT__Instr)) {
        vlSelfRef.tb_riscv__DOT__dut__DOT__LoadWbData 
            = tb_riscv__DOT__dut__DOT__DmemDout;
    } else if ((0x00001000U & tb_riscv__DOT__dut__DOT__Instr)) {
        if ((2U & vlSelfRef.tb_riscv__DOT__dut__DOT__AluOut)) {
            if ((2U & vlSelfRef.tb_riscv__DOT__dut__DOT__AluOut)) {
                vlSelfRef.tb_riscv__DOT__dut__DOT__LoadWbData 
                    = (((- (IData)((tb_riscv__DOT__dut__DOT__DmemDout 
                                    >> 0x1fU))) << 0x00000010U) 
                       | (tb_riscv__DOT__dut__DOT__DmemDout 
                          >> 0x10U));
            }
        } else {
            vlSelfRef.tb_riscv__DOT__dut__DOT__LoadWbData 
                = (((- (IData)((1U & (tb_riscv__DOT__dut__DOT__DmemDout 
                                      >> 0x0fU)))) 
                    << 0x00000010U) | (0x0000ffffU 
                                       & tb_riscv__DOT__dut__DOT__DmemDout));
        }
        if (VL_UNLIKELY(((1U & (~ VL_ONEHOT_I(((2U 
                                                & vlSelfRef.tb_riscv__DOT__dut__DOT__AluOut) 
                                               | (1U 
                                                  & (~ 
                                                     (vlSelfRef.tb_riscv__DOT__dut__DOT__AluOut 
                                                      >> 1U)))))))))) {
            if (tb_riscv__DOT__dut__DOT____VdfgExtracted_h728d4a5a__0) {
                if (VL_UNLIKELY((vlSymsp->_vm_contextp__->assertOn()))) {
                    VL_WRITEF_NX("[%0t] %%Error: Riscv.sv:147: Assertion failed in %Ntb_riscv.dut: unique case, but none matched for '1'h%x'\n",0,
                                 64,VL_TIME_UNITED_Q(1000),
                                 -9,vlSymsp->name(),
                                 1,(1U & (vlSelfRef.tb_riscv__DOT__dut__DOT__AluOut 
                                          >> 1U)));
                    VL_STOP_MT("Riscv.sv", 147, "");
                }
            } else if (VL_UNLIKELY((vlSymsp->_vm_contextp__->assertOn()))) {
                VL_WRITEF_NX("[%0t] %%Error: Riscv.sv:147: Assertion failed in %Ntb_riscv.dut: unique case, but multiple matches found for '1'h%x'\n",0,
                             64,VL_TIME_UNITED_Q(1000),
                             -9,vlSymsp->name(),1,(1U 
                                                   & (vlSelfRef.tb_riscv__DOT__dut__DOT__AluOut 
                                                      >> 1U)));
                VL_STOP_MT("Riscv.sv", 147, "");
            }
        }
    } else {
        vlSelfRef.tb_riscv__DOT__dut__DOT__LoadWbData 
            = ((2U & vlSelfRef.tb_riscv__DOT__dut__DOT__AluOut)
                ? ((1U & vlSelfRef.tb_riscv__DOT__dut__DOT__AluOut)
                    ? (((- (IData)((tb_riscv__DOT__dut__DOT__DmemDout 
                                    >> 0x1fU))) << 8U) 
                       | (tb_riscv__DOT__dut__DOT__DmemDout 
                          >> 0x18U)) : (((- (IData)(
                                                    (1U 
                                                     & (tb_riscv__DOT__dut__DOT__DmemDout 
                                                        >> 0x17U)))) 
                                         << 8U) | (0x000000ffU 
                                                   & (tb_riscv__DOT__dut__DOT__DmemDout 
                                                      >> 0x10U))))
                : ((1U & vlSelfRef.tb_riscv__DOT__dut__DOT__AluOut)
                    ? (((- (IData)((1U & (tb_riscv__DOT__dut__DOT__DmemDout 
                                          >> 0x0fU)))) 
                        << 8U) | (0x000000ffU & (tb_riscv__DOT__dut__DOT__DmemDout 
                                                 >> 8U)))
                    : (((- (IData)((1U & (tb_riscv__DOT__dut__DOT__DmemDout 
                                          >> 7U)))) 
                        << 8U) | (0x000000ffU & tb_riscv__DOT__dut__DOT__DmemDout))));
    }
    vlSelfRef.tb_riscv__DOT__dut__DOT__RegWrData = 
        ((0U == (IData)(tb_riscv__DOT__dut__DOT__RegWb))
          ? vlSelfRef.tb_riscv__DOT__dut__DOT__AluOut
          : ((1U == (IData)(tb_riscv__DOT__dut__DOT__RegWb))
              ? vlSelfRef.tb_riscv__DOT__dut__DOT__LoadWbData
              : ((2U == (IData)(tb_riscv__DOT__dut__DOT__RegWb))
                  ? ((IData)(4U) + vlSelfRef.tb_riscv__DOT__dut__DOT__Pc)
                  : ((3U == (IData)(tb_riscv__DOT__dut__DOT__RegWb))
                      ? tb_riscv__DOT__dut__DOT__ImmExt
                      : 0U))));
}

VL_ATTR_COLD void Vtb_riscv___024root___eval_stl(Vtb_riscv___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_riscv___024root___eval_stl\n"); );
    Vtb_riscv__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VstlTriggered[0U])) {
        Vtb_riscv___024root___stl_sequent__TOP__0(vlSelf);
    }
}

VL_ATTR_COLD bool Vtb_riscv___024root___eval_phase__stl(Vtb_riscv___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_riscv___024root___eval_phase__stl\n"); );
    Vtb_riscv__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VstlExecute;
    // Body
    Vtb_riscv___024root___eval_triggers_vec__stl(vlSelf);
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vtb_riscv___024root___dump_triggers__stl(vlSelfRef.__VstlTriggered, "stl"s);
    }
#endif
    __VstlExecute = Vtb_riscv___024root___trigger_anySet__stl(vlSelfRef.__VstlTriggered);
    if (__VstlExecute) {
        Vtb_riscv___024root___eval_stl(vlSelf);
    }
    return (__VstlExecute);
}

bool Vtb_riscv___024root___trigger_anySet__act(const VlUnpacked<QData/*63:0*/, 1> &in);

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtb_riscv___024root___dump_triggers__act(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_riscv___024root___dump_triggers__act\n"); );
    // Body
    if ((1U & (~ (IData)(Vtb_riscv___024root___trigger_anySet__act(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: @(posedge tb_riscv.Clk)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 1U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 1 is active: @([true] __VdlySched.awaitingCurrentTime())\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void Vtb_riscv___024root___ctor_var_reset(Vtb_riscv___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_riscv___024root___ctor_var_reset\n"); );
    Vtb_riscv__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    const uint64_t __VscopeHash = VL_MURMUR64_HASH(vlSelf->vlNamep);
    vlSelf->tb_riscv__DOT__Clk = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14294047824207325098ull);
    vlSelf->tb_riscv__DOT__Reset = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2586805124752360917ull);
    vlSelf->tb_riscv__DOT__dut__DOT__Pc = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 14532533661930845590ull);
    vlSelf->tb_riscv__DOT__dut__DOT__PcNxt = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 18402542377065888344ull);
    vlSelf->tb_riscv__DOT__dut__DOT__AluOut = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 1160330940543652066ull);
    vlSelf->tb_riscv__DOT__dut__DOT__RegWrData = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 15574384850797284442ull);
    vlSelf->tb_riscv__DOT__dut__DOT__DmemWrEn = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 16452803853961160188ull);
    vlSelf->tb_riscv__DOT__dut__DOT__LoadWbData = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 14695130222803473604ull);
    vlSelf->tb_riscv__DOT__dut__DOT__DmemWrData = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 2768082759656368954ull);
    for (int __Vi0 = 0; __Vi0 < 512; ++__Vi0) {
        vlSelf->tb_riscv__DOT__dut__DOT__ProgMemInst__DOT__RamArray[__Vi0] = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 9651565974914749815ull);
    }
    VL_SCOPED_RAND_RESET_W(1024, vlSelf->tb_riscv__DOT__dut__DOT__RegfileInst__DOT__Regs, __VscopeHash, 14634163948500924015ull);
    vlSelf->tb_riscv__DOT__dut__DOT__RegfileInst__DOT__WrDecVec = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 10139198617876929348ull);
    for (int __Vi0 = 0; __Vi0 < 512; ++__Vi0) {
        vlSelf->tb_riscv__DOT__dut__DOT__DataMemInst__DOT__RamArray[__Vi0] = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 4928775624350781919ull);
    }
    vlSelf->__Vfunc_GetOpcode__0__Vfuncout = 0;
    vlSelf->__Vfunc_GetOpcode__0__RawInstr = 0;
    vlSelf->__Vfunc_GetOpcode__1__Vfuncout = 0;
    vlSelf->__Vfunc_GetOpcode__1__RawInstr = 0;
    vlSelf->__Vfunc_GetOpcode__2__Vfuncout = 0;
    vlSelf->__Vfunc_GetOpcode__2__RawInstr = 0;
    vlSelf->__Vfunc_GetOpcode__4__Vfuncout = 0;
    vlSelf->__Vfunc_GetOpcode__4__RawInstr = 0;
    vlSelf->__Vfunc_GetOpcode__5__Vfuncout = 0;
    vlSelf->__Vfunc_GetOpcode__5__RawInstr = 0;
    vlSelf->__Vfunc_GetOpcode__6__Vfuncout = 0;
    vlSelf->__Vfunc_GetOpcode__6__RawInstr = 0;
    vlSelf->__Vfunc_GetOpcode__7__Vfuncout = 0;
    vlSelf->__Vfunc_GetOpcode__7__RawInstr = 0;
    vlSelf->__Vfunc_GetOpcode__8__Vfuncout = 0;
    vlSelf->__Vfunc_GetOpcode__8__RawInstr = 0;
    vlSelf->__Vfunc_GetOpcode__9__Vfuncout = 0;
    vlSelf->__Vfunc_GetOpcode__9__RawInstr = 0;
    vlSelf->__Vfunc_GetOpcode__10__Vfuncout = 0;
    vlSelf->__Vfunc_GetOpcode__10__RawInstr = 0;
    vlSelf->__Vfunc_GetOpcode__11__Vfuncout = 0;
    vlSelf->__Vfunc_GetOpcode__11__RawInstr = 0;
    vlSelf->__Vfunc_GetOpcode__12__Vfuncout = 0;
    vlSelf->__Vfunc_GetOpcode__12__RawInstr = 0;
    vlSelf->__Vfunc_GetOpcode__13__Vfuncout = 0;
    vlSelf->__Vfunc_GetOpcode__13__RawInstr = 0;
    vlSelf->__Vfunc_GetOpcode__14__Vfuncout = 0;
    vlSelf->__Vfunc_GetOpcode__14__RawInstr = 0;
    vlSelf->__Vfunc_GetOpcode__15__Vfuncout = 0;
    vlSelf->__Vfunc_GetOpcode__15__RawInstr = 0;
    vlSelf->__Vfunc_GetOpcode__16__Vfuncout = 0;
    vlSelf->__Vfunc_GetOpcode__16__RawInstr = 0;
    vlSelf->__Vfunc_GetOpcode__17__Vfuncout = 0;
    vlSelf->__Vfunc_GetOpcode__17__RawInstr = 0;
    vlSelf->__Vfunc_GetOpcode__18__Vfuncout = 0;
    vlSelf->__Vfunc_GetOpcode__18__RawInstr = 0;
    vlSelf->__Vfunc_GetOpcode__19__Vfuncout = 0;
    vlSelf->__Vfunc_GetOpcode__19__RawInstr = 0;
    vlSelf->__Vfunc_GetOpcode__20__Vfuncout = 0;
    vlSelf->__Vfunc_GetOpcode__20__RawInstr = 0;
    vlSelf->__Vfunc_GetOpcode__21__Vfuncout = 0;
    vlSelf->__Vfunc_GetOpcode__21__RawInstr = 0;
    vlSelf->__Vfunc_GetOpcode__22__Vfuncout = 0;
    vlSelf->__Vfunc_GetOpcode__22__RawInstr = 0;
    vlSelf->__Vfunc_GetOpcode__23__Vfuncout = 0;
    vlSelf->__Vfunc_GetOpcode__23__RawInstr = 0;
    vlSelf->__Vfunc_GetOpcode__24__Vfuncout = 0;
    vlSelf->__Vfunc_GetOpcode__24__RawInstr = 0;
    vlSelf->__Vfunc_GetOpcode__25__Vfuncout = 0;
    vlSelf->__Vfunc_GetOpcode__25__RawInstr = 0;
    vlSelf->__Vfunc_GetOpcode__26__Vfuncout = 0;
    vlSelf->__Vfunc_GetOpcode__26__RawInstr = 0;
    vlSelf->__Vfunc_GetOpcode__27__Vfuncout = 0;
    vlSelf->__Vfunc_GetOpcode__27__RawInstr = 0;
    vlSelf->__Vfunc_GetOpcode__28__Vfuncout = 0;
    vlSelf->__Vfunc_GetOpcode__28__RawInstr = 0;
    vlSelf->__Vfunc_GetOpcode__29__Vfuncout = 0;
    vlSelf->__Vfunc_GetOpcode__29__RawInstr = 0;
    vlSelf->__Vfunc_GetOpcode__30__Vfuncout = 0;
    vlSelf->__Vfunc_GetOpcode__30__RawInstr = 0;
    vlSelf->__Vfunc_GetOpcode__31__Vfuncout = 0;
    vlSelf->__Vfunc_GetOpcode__31__RawInstr = 0;
    vlSelf->__Vfunc_GetOpcode__32__Vfuncout = 0;
    vlSelf->__Vfunc_GetOpcode__32__RawInstr = 0;
    vlSelf->__Vfunc_GetOpcode__33__Vfuncout = 0;
    vlSelf->__Vfunc_GetOpcode__33__RawInstr = 0;
    vlSelf->__Vfunc_GetOpcode__34__Vfuncout = 0;
    vlSelf->__Vfunc_GetOpcode__34__RawInstr = 0;
    vlSelf->__Vfunc_GetOpcode__35__Vfuncout = 0;
    vlSelf->__Vfunc_GetOpcode__35__RawInstr = 0;
    vlSelf->__Vfunc_GetOpcode__36__Vfuncout = 0;
    vlSelf->__Vfunc_GetOpcode__36__RawInstr = 0;
    vlSelf->__Vfunc_GetOpcode__37__Vfuncout = 0;
    vlSelf->__Vfunc_GetOpcode__37__RawInstr = 0;
    vlSelf->__Vfunc_GetOpcode__38__Vfuncout = 0;
    vlSelf->__Vfunc_GetOpcode__38__RawInstr = 0;
    vlSelf->__Vfunc_GetOpcode__39__Vfuncout = 0;
    vlSelf->__Vfunc_GetOpcode__39__RawInstr = 0;
    vlSelf->__Vfunc_GetOpcode__40__Vfuncout = 0;
    vlSelf->__Vfunc_GetOpcode__40__RawInstr = 0;
    vlSelf->__Vfunc_GetOpcode__41__Vfuncout = 0;
    vlSelf->__Vfunc_GetOpcode__41__RawInstr = 0;
    vlSelf->__Vfunc_GetOpcode__42__Vfuncout = 0;
    vlSelf->__Vfunc_GetOpcode__42__RawInstr = 0;
    vlSelf->__Vfunc_GetOpcode__43__Vfuncout = 0;
    vlSelf->__Vfunc_GetOpcode__43__RawInstr = 0;
    vlSelf->__Vfunc_GetOpcode__44__Vfuncout = 0;
    vlSelf->__Vfunc_GetOpcode__44__RawInstr = 0;
    vlSelf->__Vfunc_GetOpcode__45__Vfuncout = 0;
    vlSelf->__Vfunc_GetOpcode__45__RawInstr = 0;
    vlSelf->__Vfunc_GetOpcode__46__Vfuncout = 0;
    vlSelf->__Vfunc_GetOpcode__46__RawInstr = 0;
    vlSelf->__Vfunc_GetOpcode__47__Vfuncout = 0;
    vlSelf->__Vfunc_GetOpcode__47__RawInstr = 0;
    vlSelf->__Vfunc_GetOpcode__48__Vfuncout = 0;
    vlSelf->__Vfunc_GetOpcode__48__RawInstr = 0;
    vlSelf->__Vfunc_GetOpcode__49__Vfuncout = 0;
    vlSelf->__Vfunc_GetOpcode__49__RawInstr = 0;
    vlSelf->__Vfunc_GetOpcode__50__Vfuncout = 0;
    vlSelf->__Vfunc_GetOpcode__50__RawInstr = 0;
    vlSelf->__Vfunc_GetOpcode__51__Vfuncout = 0;
    vlSelf->__Vfunc_GetOpcode__51__RawInstr = 0;
    vlSelf->__Vfunc_GetOpcode__52__Vfuncout = 0;
    vlSelf->__Vfunc_GetOpcode__52__RawInstr = 0;
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VstlTriggered[__Vi0] = 0;
    }
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VactTriggered[__Vi0] = 0;
    }
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VactTriggeredAcc[__Vi0] = 0;
    }
    vlSelf->__Vtrigprevexpr___TOP__tb_riscv__DOT__Clk__0 = 0;
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VnbaTriggered[__Vi0] = 0;
    }
    vlSelf->__Vi = 0;
}
