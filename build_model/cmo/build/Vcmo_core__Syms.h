// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table internal header
//
// Internal details; most calling programs do not need this header,
// unless using verilator public meta comments.

#ifndef VERILATED_VCMO_CORE__SYMS_H_
#define VERILATED_VCMO_CORE__SYMS_H_  // guard

#include "verilated.h"

// INCLUDE MODEL CLASS

#include "Vcmo_core.h"

// INCLUDE MODULE CLASSES
#include "Vcmo_core___024root.h"

// SYMS CLASS (contains all model state)
class alignas(VL_CACHE_LINE_BYTES) Vcmo_core__Syms final : public VerilatedSyms {
  public:
    // INTERNAL STATE
    Vcmo_core* const __Vm_modelp;
    VlDeleter __Vm_deleter;
    bool __Vm_didInit = false;

    // MODULE INSTANCE STATE
    Vcmo_core___024root            TOP;

    // CONSTRUCTORS
    Vcmo_core__Syms(VerilatedContext* contextp, const char* namep, Vcmo_core* modelp);
    ~Vcmo_core__Syms();

    // METHODS
    const char* name() const { return TOP.vlNamep; }
};

#endif  // guard
