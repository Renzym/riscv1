// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Model implementation (design independent parts)

#include "Vtb_riscv__pch.h"

//============================================================
// Constructors

Vtb_riscv::Vtb_riscv(VerilatedContext* _vcontextp__, const char* _vcname__)
    : VerilatedModel{*_vcontextp__}
    , vlSymsp{new Vtb_riscv__Syms(contextp(), _vcname__, this)}
    , rootp{&(vlSymsp->TOP)}
{
    // Register model with the context
    contextp()->addModel(this);
}

Vtb_riscv::Vtb_riscv(const char* _vcname__)
    : Vtb_riscv(Verilated::threadContextp(), _vcname__)
{
}

//============================================================
// Destructor

Vtb_riscv::~Vtb_riscv() {
    delete vlSymsp;
}

//============================================================
// Evaluation function

#ifdef VL_DEBUG
void Vtb_riscv___024root___eval_debug_assertions(Vtb_riscv___024root* vlSelf);
#endif  // VL_DEBUG
void Vtb_riscv___024root___eval_static(Vtb_riscv___024root* vlSelf);
void Vtb_riscv___024root___eval_initial(Vtb_riscv___024root* vlSelf);
void Vtb_riscv___024root___eval_settle(Vtb_riscv___024root* vlSelf);
void Vtb_riscv___024root___eval(Vtb_riscv___024root* vlSelf);

void Vtb_riscv::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vtb_riscv::eval_step\n"); );
#ifdef VL_DEBUG
    // Debug assertions
    Vtb_riscv___024root___eval_debug_assertions(&(vlSymsp->TOP));
#endif  // VL_DEBUG
    vlSymsp->__Vm_deleter.deleteAll();
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) {
        VL_DEBUG_IF(VL_DBG_MSGF("+ Initial\n"););
        Vtb_riscv___024root___eval_static(&(vlSymsp->TOP));
        Vtb_riscv___024root___eval_initial(&(vlSymsp->TOP));
        Vtb_riscv___024root___eval_settle(&(vlSymsp->TOP));
        vlSymsp->__Vm_didInit = true;
    }
    VL_DEBUG_IF(VL_DBG_MSGF("+ Eval\n"););
    Vtb_riscv___024root___eval(&(vlSymsp->TOP));
    // Evaluate cleanup
    Verilated::endOfEval(vlSymsp->__Vm_evalMsgQp);
}

//============================================================
// Events and timing
bool Vtb_riscv::eventsPending() { return !vlSymsp->TOP.__VdlySched.empty() && !contextp()->gotFinish(); }

uint64_t Vtb_riscv::nextTimeSlot() { return vlSymsp->TOP.__VdlySched.nextTimeSlot(); }

//============================================================
// Utilities

const char* Vtb_riscv::name() const {
    return vlSymsp->name();
}

//============================================================
// Invoke final blocks

void Vtb_riscv___024root___eval_final(Vtb_riscv___024root* vlSelf);

VL_ATTR_COLD void Vtb_riscv::final() {
    Vtb_riscv___024root___eval_final(&(vlSymsp->TOP));
}

//============================================================
// Implementations of abstract methods from VerilatedModel

const char* Vtb_riscv::hierName() const { return vlSymsp->name(); }
const char* Vtb_riscv::modelName() const { return "Vtb_riscv"; }
unsigned Vtb_riscv::threads() const { return 1; }
void Vtb_riscv::prepareClone() const { contextp()->prepareClone(); }
void Vtb_riscv::atClone() const {
    contextp()->threadPoolpOnClone();
}
