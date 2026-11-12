// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vcmo_core.h for the primary calling header

#include "Vcmo_core__pch.h"

VL_ATTR_COLD void Vcmo_core___024root___eval_static(Vcmo_core___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcmo_core___024root___eval_static\n"); );
    Vcmo_core__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__Vtrigprevexpr___TOP__clk_i__0 = vlSelfRef.clk_i;
    vlSelfRef.__Vtrigprevexpr___TOP__rst_ni__0 = vlSelfRef.rst_ni;
}

VL_ATTR_COLD void Vcmo_core___024root___eval_initial(Vcmo_core___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcmo_core___024root___eval_initial\n"); );
    Vcmo_core__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

VL_ATTR_COLD void Vcmo_core___024root___eval_final(Vcmo_core___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcmo_core___024root___eval_final\n"); );
    Vcmo_core__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vcmo_core___024root___dump_triggers__stl(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG
VL_ATTR_COLD bool Vcmo_core___024root___eval_phase__stl(Vcmo_core___024root* vlSelf);

VL_ATTR_COLD void Vcmo_core___024root___eval_settle(Vcmo_core___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcmo_core___024root___eval_settle\n"); );
    Vcmo_core__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ __VstlIterCount;
    // Body
    __VstlIterCount = 0U;
    vlSelfRef.__VstlFirstIteration = 1U;
    do {
        if (VL_UNLIKELY(((0x00000064U < __VstlIterCount)))) {
#ifdef VL_DEBUG
            Vcmo_core___024root___dump_triggers__stl(vlSelfRef.__VstlTriggered, "stl"s);
#endif
            VL_FATAL_MT("rtl/cmo_core/cmo_core.sv", 1, "", "DIDNOTCONVERGE: Settle region did not converge after '--converge-limit' of 100 tries");
        }
        __VstlIterCount = ((IData)(1U) + __VstlIterCount);
        vlSelfRef.__VstlPhaseResult = Vcmo_core___024root___eval_phase__stl(vlSelf);
        vlSelfRef.__VstlFirstIteration = 0U;
    } while (vlSelfRef.__VstlPhaseResult);
}

VL_ATTR_COLD void Vcmo_core___024root___eval_triggers_vec__stl(Vcmo_core___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcmo_core___024root___eval_triggers_vec__stl\n"); );
    Vcmo_core__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VstlTriggered[0U] = ((0xfffffffffffffffeULL 
                                      & vlSelfRef.__VstlTriggered[0U]) 
                                     | (IData)((IData)(vlSelfRef.__VstlFirstIteration)));
}

VL_ATTR_COLD bool Vcmo_core___024root___trigger_anySet__stl(const VlUnpacked<QData/*63:0*/, 1> &in);

#ifdef VL_DEBUG
VL_ATTR_COLD void Vcmo_core___024root___dump_triggers__stl(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcmo_core___024root___dump_triggers__stl\n"); );
    // Body
    if ((1U & (~ (IData)(Vcmo_core___024root___trigger_anySet__stl(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: Internal 'stl' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD bool Vcmo_core___024root___trigger_anySet__stl(const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcmo_core___024root___trigger_anySet__stl\n"); );
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

VL_ATTR_COLD void Vcmo_core___024root___stl_sequent__TOP__0(Vcmo_core___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcmo_core___024root___stl_sequent__TOP__0\n"); );
    Vcmo_core__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.req_ready_o = (0U == (IData)(vlSelfRef.cmo_core__DOT__state_q));
    vlSelfRef.cache_req_valid_o = (1U == (IData)(vlSelfRef.cmo_core__DOT__state_q));
    vlSelfRef.cache_req_addr_o = vlSelfRef.cmo_core__DOT__addr_q;
    vlSelfRef.cache_req_op_o = vlSelfRef.cmo_core__DOT__op_q;
    vlSelfRef.cmo_core__DOT__is_prefetch = ((0U == (IData)(vlSelfRef.cmo_core__DOT__op_q)) 
                                            | (1U == (IData)(vlSelfRef.cmo_core__DOT__op_q)));
}

VL_ATTR_COLD void Vcmo_core___024root___eval_stl(Vcmo_core___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcmo_core___024root___eval_stl\n"); );
    Vcmo_core__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VstlTriggered[0U])) {
        vlSelfRef.req_ready_o = (0U == (IData)(vlSelfRef.cmo_core__DOT__state_q));
        vlSelfRef.cache_req_valid_o = (1U == (IData)(vlSelfRef.cmo_core__DOT__state_q));
        vlSelfRef.cache_req_addr_o = vlSelfRef.cmo_core__DOT__addr_q;
        vlSelfRef.cache_req_op_o = vlSelfRef.cmo_core__DOT__op_q;
        vlSelfRef.cmo_core__DOT__is_prefetch = ((0U 
                                                 == (IData)(vlSelfRef.cmo_core__DOT__op_q)) 
                                                | (1U 
                                                   == (IData)(vlSelfRef.cmo_core__DOT__op_q)));
    }
}

VL_ATTR_COLD bool Vcmo_core___024root___eval_phase__stl(Vcmo_core___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcmo_core___024root___eval_phase__stl\n"); );
    Vcmo_core__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VstlExecute;
    // Body
    Vcmo_core___024root___eval_triggers_vec__stl(vlSelf);
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vcmo_core___024root___dump_triggers__stl(vlSelfRef.__VstlTriggered, "stl"s);
    }
#endif
    __VstlExecute = Vcmo_core___024root___trigger_anySet__stl(vlSelfRef.__VstlTriggered);
    if (__VstlExecute) {
        Vcmo_core___024root___eval_stl(vlSelf);
    }
    return (__VstlExecute);
}

bool Vcmo_core___024root___trigger_anySet__act(const VlUnpacked<QData/*63:0*/, 1> &in);

#ifdef VL_DEBUG
VL_ATTR_COLD void Vcmo_core___024root___dump_triggers__act(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcmo_core___024root___dump_triggers__act\n"); );
    // Body
    if ((1U & (~ (IData)(Vcmo_core___024root___trigger_anySet__act(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: @(posedge clk_i)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 1U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 1 is active: @(negedge rst_ni)\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void Vcmo_core___024root___ctor_var_reset(Vcmo_core___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcmo_core___024root___ctor_var_reset\n"); );
    Vcmo_core__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    const uint64_t __VscopeHash = VL_MURMUR64_HASH(vlSelf->vlNamep);
    vlSelf->clk_i = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11908517815223722933ull);
    vlSelf->rst_ni = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3161515032326629241ull);
    vlSelf->req_valid_i = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11921997549316339842ull);
    vlSelf->req_ready_o = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9457934168498264557ull);
    vlSelf->req_addr_i = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 12677377809789801409ull);
    vlSelf->req_op_i = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 17086765513481871067ull);
    vlSelf->cache_req_valid_o = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6694190876036956331ull);
    vlSelf->cache_req_ready_i = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7828862140397720921ull);
    vlSelf->cache_req_addr_o = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 7587024703652629288ull);
    vlSelf->cache_req_op_o = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 6220669494281865198ull);
    vlSelf->cache_rsp_valid_i = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11676528485074667460ull);
    vlSelf->cache_rsp_error_i = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15419139120210904257ull);
    vlSelf->done_o = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13948340918712020156ull);
    vlSelf->error_o = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13586856194824817975ull);
    vlSelf->cmo_core__DOT__state_q = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 1112379000754230936ull);
    vlSelf->cmo_core__DOT__addr_q = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 3310686347160436955ull);
    vlSelf->cmo_core__DOT__op_q = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 13397766108922470101ull);
    vlSelf->cmo_core__DOT__is_prefetch = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 18230290806917358117ull);
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VstlTriggered[__Vi0] = 0;
    }
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VactTriggered[__Vi0] = 0;
    }
    vlSelf->__Vtrigprevexpr___TOP__clk_i__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__rst_ni__0 = 0;
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VnbaTriggered[__Vi0] = 0;
    }
}
