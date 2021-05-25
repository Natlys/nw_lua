#ifndef NC_LUA_DO_H
#define NC_LUA_DO_H

#include "nc_lua_obj.hxx"
#include "nc_lua_stt.hxx"
#include "nc_lua_zbuf.hxx"

// ,acro to check stack size and grow stack if needed.
// parameters 'pre'/'pos' allow the macro to preserve a pointer into the
// stack across reallocations, doing the work only when needed;
// it also allows the running of one GC step when the stack is reallocated
// 'condmovestack' is used in heavy tests to force a stack reallocation at every check
#define luaD_checkstackaux(L,n,pre,pos)  \
	if (L->stack_last - L->top <= (n)) \
	  { pre; luaD_growstack(L, n, 1); pos; } \
        else { condmovestack(L,pre,pos); }

// in general, 'pre'/'pos' are empty (nothing to save)
#define luaD_checkstack(L,n)	luaD_checkstackaux(L,n,(void)0,(void)0)

#define savestack(L,p)		((char *)(p) - (char *)L->stack)
#define restorestack(L,n)	((StkId)((char *)L->stack + (n)))

// macro to check stack size, preserving 'p'
#define checkstackGCp(L,n,p)  \
  luaD_checkstackaux(L, n, \
    ptrdiff_t t__ = savestack(L, p);  /* save 'p' */ \
    luaC_checkGC(L),  /* stack grow uses memory */ \
    p = restorestack(L, t__))  /* 'pos' part: restore 'p' */

// macro to check stack size and GC
#define checkstackGC(L,fsize)  \
	luaD_checkstackaux(L, (fsize), luaC_checkGC(L), (void)0)

// type of protected functions, to be ran by 'runprotected'
typedef void (*Pfunc) (nc_lua_flow_t *L, void *ud);

NC_LUAI_FUNC void luaD_seterrorobj (nc_lua_flow_t *L, int errcode, StkId oldtop);
NC_LUAI_FUNC int luaD_protectedparser (nc_lua_flow_t *L, ZIO *z, const char *name,
                                                  const char *mode);
NC_LUAI_FUNC void luaD_hook (nc_lua_flow_t *L, int event, int line,
                                        int fTransfer, int nTransfer);
NC_LUAI_FUNC void luaD_hookcall (nc_lua_flow_t *L, CallInfo *ci);
NC_LUAI_FUNC void luaD_pretailcall (nc_lua_flow_t *L, CallInfo *ci, StkId func, int n);
NC_LUAI_FUNC CallInfo *luaD_precall (nc_lua_flow_t *L, StkId func, int nResults);
NC_LUAI_FUNC void luaD_call (nc_lua_flow_t *L, StkId func, int nResults);
NC_LUAI_FUNC void luaD_callnoyield (nc_lua_flow_t *L, StkId func, int nResults);
NC_LUAI_FUNC void luaD_tryfuncTM (nc_lua_flow_t *L, StkId func);
NC_LUAI_FUNC int luaD_pcall (nc_lua_flow_t *L, Pfunc func, void *u,
                                        ptrdiff_t oldtop, ptrdiff_t ef);
NC_LUAI_FUNC void luaD_poscall (nc_lua_flow_t *L, CallInfo *ci, int nres);
NC_LUAI_FUNC int luaD_reallocstack (nc_lua_flow_t *L, int newsize, int raiseerror);
NC_LUAI_FUNC int luaD_growstack (nc_lua_flow_t *L, int n, int raiseerror);
NC_LUAI_FUNC void luaD_shrinkstack (nc_lua_flow_t *L);
NC_LUAI_FUNC void luaD_inctop (nc_lua_flow_t *L);

NC_LUAI_FUNC l_noret luaD_throw (nc_lua_flow_t *L, int errcode);
NC_LUAI_FUNC int luaD_rawrunprotected (nc_lua_flow_t *L, Pfunc f, void *ud);

#endif  // NC_LUADO_H
