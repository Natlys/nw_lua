#ifndef NC_API_H
#define NC_API_H

#include "nc_lua_limit.hxx"
#include "nc_lua_stt.hxx"

// increments 'L->top', checking for stack overflows
#define api_incr_top(L)   {L->top++; api_check(L, L->top <= L->ci->top, "stack overflow");}

// if a call returns too many multiple returns,
// the callee may not have stack space to accommodate all results;
// in this case, this macro increases its stack space ('L->ci->top').
#define adjustresults(L,nres) \
    { if ((nres) <= NC_LUA_MULTRET && L->ci->top < L->top) L->ci->top = L->top; }

// ensure the stack has at least 'n' elements
#define api_checknelems(L,n)	api_check(L, (n) < (L->top - L->ci->func), "not enough elements in the stack")

// To reduce the overhead of returning from C functions, the presence of
// to-be-closed variables in these functions is coded in the CallInfo's
// field 'nresults', in a way that functions with no to-be-closed variables
// with zero, one, or "all" wanted results have no overhead
// functions with other number of wanted results, as well as functions with
// variables to be closed, have an extra check;
#define hastocloseCfunc(n)	((n) < NC_LUA_MULTRET)

#define codeNresults(n)		(-(n) - 3)

#endif  // NC_API_H
