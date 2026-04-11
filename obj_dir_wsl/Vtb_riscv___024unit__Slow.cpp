// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtb_riscv.h for the primary calling header

#include "Vtb_riscv__pch.h"

void Vtb_riscv___024unit___ctor_var_reset(Vtb_riscv___024unit* vlSelf);

Vtb_riscv___024unit::Vtb_riscv___024unit() = default;
Vtb_riscv___024unit::~Vtb_riscv___024unit() = default;

void Vtb_riscv___024unit::ctor(Vtb_riscv__Syms* symsp, const char* namep) {
    vlSymsp = symsp;
    vlNamep = strdup(Verilated::catName(vlSymsp->name(), namep));
    // Reset structure values
    Vtb_riscv___024unit___ctor_var_reset(this);
}

void Vtb_riscv___024unit::__Vconfigure(bool first) {
    (void)first;  // Prevent unused variable warning
}

void Vtb_riscv___024unit::dtor() {
    VL_DO_DANGLING(std::free(const_cast<char*>(vlNamep)), vlNamep);
}
