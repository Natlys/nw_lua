#ifndef NC_LUA_DEBUG_H
#    define NC_LUA_DEBUG_H
#    include "nc_lua_stt.hxx"
#    if (defined NC_API)

#        define pcRel(pc, p) (cast_int((pc) - (p)->code) - 1)
// active lua function (given call info) //
#        define ci_func(ci)  (clLvalue(s2v((ci)->func)))
#        define resethookcount(L) (L->hookcount = L->basehookcount)
// mark for entries in 'lineinfo' array that has absolute information in 'abslineinfo' array
#        define ABSLINEINFO (-0x80)

NC_LUAI_FUNC int luaG_getfuncline (const Proto *f, int pc);
NC_LUAI_FUNC const char *luaG_findlocal (nc_lua_flow_t *L, CallInfo *ci, int n, StkId *pos);
NC_LUAI_FUNC l_noret luaG_typeerror (nc_lua_flow_t *L, const TValue *o, const char *opname);
NC_LUAI_FUNC l_noret luaG_forerror (nc_lua_flow_t *L, const TValue *o, const char *what);
NC_LUAI_FUNC l_noret luaG_concaterror (nc_lua_flow_t *L, const TValue *p1, const TValue *p2);
NC_LUAI_FUNC l_noret luaG_opinterror (nc_lua_flow_t *L, const TValue *p1, const TValue *p2, const char *msg);
NC_LUAI_FUNC l_noret luaG_tointerror (nc_lua_flow_t *L, const TValue *p1, const TValue *p2);
NC_LUAI_FUNC l_noret luaG_ordererror (nc_lua_flow_t *L, const TValue *p1, const TValue *p2);
NC_LUAI_FUNC l_noret luaG_runerror (nc_lua_flow_t *L, const char *fmt, ...);
NC_LUAI_FUNC const char *luaG_addinfo (nc_lua_flow_t *L, const char *msg, TString *src, int line);
NC_LUAI_FUNC l_noret luaG_errormsg (nc_lua_flow_t *L);
NC_LUAI_FUNC int luaG_traceexec (nc_lua_flow_t *L, const Instruction *pc);
#    endif  /* NC_API */
/* end_of_file */
#endif  // NC_LUA_DEBUG_H //