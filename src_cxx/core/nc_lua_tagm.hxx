#ifndef NC_LUA_TAG_METHODS_H
#define NC_LUA_TAG_METHODS_H
#include "nc_lua_obj.hxx"
// warning: if you change the order of this enumeration,
// grep "ORDER TM" and "ORDER OP"
typedef enum {
    TM_INDEX,
    TM_NEWINDEX,
    TM_GC,
    TM_MODE,
    TM_LEN,
    TM_EQ,  // last tag method with fast access
    TM_ADD,
    TM_SUB,
    TM_MUL,
    TM_MOD,
    TM_POW,
    TM_DIV,
    TM_IDIV,
    TM_BAND,
    TM_BOR,
    TM_BXOR,
    TM_SHL,
    TM_SHR,
    TM_UNM,
    TM_BNOT,
    TM_LT,
    TM_LE,
    TM_CONCAT,
    TM_CALL,
    TM_CLOSE,
    TM_N		// number of elements in the enum
} TMS;
// mask with 1 in all fast-access methods;
// a 1 in any of these bits in the flag of a (meta)table means the metatable does not have the
// corresponding metamethod field. (Bit 7 of the flag is used for 'isrealasize');
#define maskflags	(~(~0u << (TM_EQ + 1)))
// test whether there is no tagmethod;
// (because tagmethods use raw accesses, the result may be an "empty" nil);
#define notm(tm)	ttisnil(tm)

#define gfasttm(g,et,e) ((et) == NULL ? NULL : \
  ((et)->flags & (1u<<(e))) ? NULL : luaT_gettm(et, e, (g)->tmname[e]))

#define fasttm(l,et,e)	gfasttm(G(l), et, e)

#define ttypename(x)	luaT_typenames_[(x) + 1]

NC_LUAI_DDEC(const char* const luaT_typenames_[NC_LUA_TOTALTYPES];)

NC_LUAI_FUNC const char* luaT_objtypename (nc_lua_flow_t *L, const TValue *o);

NC_LUAI_FUNC const TValue *luaT_gettm (Table *events, TMS event, TString *ename);
NC_LUAI_FUNC const TValue *luaT_gettmbyobj (nc_lua_flow_t *L, const TValue *o,
                                                       TMS event);
NC_LUAI_FUNC void luaT_init (nc_lua_flow_t *L);

NC_LUAI_FUNC void luaT_callTM (nc_lua_flow_t *L, const TValue *f, const TValue *p1,
                            const TValue *p2, const TValue *p3);
NC_LUAI_FUNC void luaT_callTMres (nc_lua_flow_t *L, const TValue *f,
                            const TValue *p1, const TValue *p2, StkId p3);
NC_LUAI_FUNC void luaT_trybinTM (nc_lua_flow_t *L, const TValue *p1, const TValue *p2,
                              StkId res, TMS event);
NC_LUAI_FUNC void luaT_tryconcatTM (nc_lua_flow_t *L);
NC_LUAI_FUNC void luaT_trybinassocTM (nc_lua_flow_t *L, const TValue *p1,
       const TValue *p2, int inv, StkId res, TMS event);
NC_LUAI_FUNC void luaT_trybiniTM (nc_lua_flow_t *L, const TValue *p1, lua_Integer i2,
                               int inv, StkId res, TMS event);
NC_LUAI_FUNC int luaT_callorderTM (nc_lua_flow_t *L, const TValue *p1,
                                const TValue *p2, TMS event);
NC_LUAI_FUNC int luaT_callorderiTM (nc_lua_flow_t *L, const TValue *p1, int v2,
                                 int inv, int isfloat, TMS event);

NC_LUAI_FUNC void luaT_adjustvarargs (nc_lua_flow_t *L, int nfixparams,
                                   struct CallInfo *ci, const Proto *p);
NC_LUAI_FUNC void luaT_getvarargs (nc_lua_flow_t *L, struct CallInfo *ci,
                                              StkId where, int wanted);

#endif  // NC_LUATAG_METHODS_H
