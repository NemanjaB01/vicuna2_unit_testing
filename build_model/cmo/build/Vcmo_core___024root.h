// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vcmo_core.h for the primary calling header

#ifndef VERILATED_VCMO_CORE___024ROOT_H_
#define VERILATED_VCMO_CORE___024ROOT_H_  // guard

#include "verilated.h"


class Vcmo_core__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vcmo_core___024root final {
  public:

    // DESIGN SPECIFIC STATE
    VL_IN8(clk_i,0,0);
    VL_IN8(rst_ni,0,0);
    VL_IN8(req_valid_i,0,0);
    VL_OUT8(req_ready_o,0,0);
    VL_IN8(req_op_i,2,0);
    VL_OUT8(cache_req_valid_o,0,0);
    VL_IN8(cache_req_ready_i,0,0);
    VL_OUT8(cache_req_op_o,2,0);
    VL_IN8(cache_rsp_valid_i,0,0);
    VL_IN8(cache_rsp_error_i,0,0);
    VL_OUT8(done_o,0,0);
    VL_OUT8(error_o,0,0);
    CData/*1:0*/ cmo_core__DOT__state_q;
    CData/*2:0*/ cmo_core__DOT__op_q;
    CData/*0:0*/ cmo_core__DOT__is_prefetch;
    CData/*0:0*/ __VstlFirstIteration;
    CData/*0:0*/ __VstlPhaseResult;
    CData/*0:0*/ __Vtrigprevexpr___TOP__clk_i__0;
    CData/*0:0*/ __Vtrigprevexpr___TOP__rst_ni__0;
    CData/*0:0*/ __VactPhaseResult;
    CData/*0:0*/ __VnbaPhaseResult;
    VL_IN(req_addr_i,31,0);
    VL_OUT(cache_req_addr_o,31,0);
    IData/*31:0*/ cmo_core__DOT__addr_q;
    IData/*31:0*/ __VactIterCount;
    VlUnpacked<QData/*63:0*/, 1> __VstlTriggered;
    VlUnpacked<QData/*63:0*/, 1> __VactTriggered;
    VlUnpacked<QData/*63:0*/, 1> __VnbaTriggered;

    // INTERNAL VARIABLES
    Vcmo_core__Syms* vlSymsp;
    const char* vlNamep;

    // CONSTRUCTORS
    Vcmo_core___024root(Vcmo_core__Syms* symsp, const char* namep);
    ~Vcmo_core___024root();
    VL_UNCOPYABLE(Vcmo_core___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
