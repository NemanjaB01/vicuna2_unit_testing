// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vcmo_core.h for the primary calling header

#include "Vcmo_core__pch.h"

void Vcmo_core___024root___ctor_var_reset(Vcmo_core___024root* vlSelf);

Vcmo_core___024root::Vcmo_core___024root(Vcmo_core__Syms* symsp, const char* namep)
 {
    vlSymsp = symsp;
    vlNamep = strdup(namep);
    // Reset structure values
    Vcmo_core___024root___ctor_var_reset(this);
}

void Vcmo_core___024root::__Vconfigure(bool first) {
    (void)first;  // Prevent unused variable warning
}

Vcmo_core___024root::~Vcmo_core___024root() {
    VL_DO_DANGLING(std::free(const_cast<char*>(vlNamep)), vlNamep);
}
