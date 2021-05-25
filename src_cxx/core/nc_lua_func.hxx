/*
** $Id: lua_func.h $
** Auxiliary functions to manipulate prototypes and closures
** See Copyright Notice in lua_core.h
*/

#ifndef lfunc_h
#define lfunc_h


#include "nc_lua_obj.hxx"


#define sizeCclosure(n)	(cast_int(offsetof(CClosure, upvalue)) + \
                         cast_int(sizeof(TValue)) * (n))

#define sizeLclosure(n)	(cast_int(offsetof(LClosure, upvals)) + \
                         cast_int(sizeof(TValue *)) * (n))


/* test whether thread is in 'twups' list */
#define isintwups(L)	(L->twups != L)


/*
** maximum number of upvalues in a closure (both C and Lua). (Value
** must fit in a VM register.)
*/
#define MAXUPVAL	255


#define upisopen(up)	((up)->v != &(up)->u.value)


#define uplevel(up)	check_exp(upisopen(up), cast(StkId, (up)->v))


/*
** maximum number of misses before giving up the cache of closures
** in prototypes
*/
#define MAXMISS		10


/*
** Special "status" for 'luaF_close'
*/

/* close upvalues without running their closing methods */
#define NOCLOSINGMETH	(-1)

/* close upvalues running all closing methods in protected mode */
#define CLOSEPROTECT	(-2)


NC_LUAI_FUNC Proto *luaF_newproto (nc_lua_flow_t *L);
NC_LUAI_FUNC CClosure *luaF_newCclosure (nc_lua_flow_t *L, int nupvals);
NC_LUAI_FUNC LClosure *luaF_newLclosure (nc_lua_flow_t *L, int nupvals);
NC_LUAI_FUNC void luaF_initupvals (nc_lua_flow_t *L, LClosure *cl);
NC_LUAI_FUNC UpVal *luaF_findupval (nc_lua_flow_t *L, StkId level);
NC_LUAI_FUNC void luaF_newtbcupval (nc_lua_flow_t *L, StkId level);
NC_LUAI_FUNC int luaF_close (nc_lua_flow_t *L, StkId level, int status);
NC_LUAI_FUNC void luaF_unlinkupval (UpVal *uv);
NC_LUAI_FUNC void luaF_freeproto (nc_lua_flow_t *L, Proto *f);
NC_LUAI_FUNC const char *luaF_getlocalname (const Proto *func, int local_number,
                                         int pc);


#endif
