// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vtb_riscv.h for the primary calling header

#ifndef VERILATED_VTB_RISCV___024UNIT_H_
#define VERILATED_VTB_RISCV___024UNIT_H_  // guard

#include "verilated.h"
#include "verilated_timing.h"


class Vtb_riscv__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vtb_riscv___024unit final {
  public:

    // INTERNAL VARIABLES
    Vtb_riscv__Syms* vlSymsp;
    const char* vlNamep;

    // CONSTRUCTORS
    Vtb_riscv___024unit();
    ~Vtb_riscv___024unit();
    void ctor(Vtb_riscv__Syms* symsp, const char* namep);
    void dtor();
    VL_UNCOPYABLE(Vtb_riscv___024unit);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
