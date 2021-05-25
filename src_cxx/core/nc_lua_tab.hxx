/*
** $Id: lua_tab.h $
** Lua tables (hash)
** See Copyright Notice in lua_core.h
*/

#ifndef lua_tab_h
#define lua_tab_h

#include "nc_lua_obj.hxx"


#define gnode(t,i)	(&(t)->node[i])
#define gval(n)		(&(n)->i_val)
#define gnext(n)	((n)->u.next)


/*
** Clear all bits of fast-access metamethods, which means that the table
** may have any of these metamethods. (First access that fails after the
** clearing will set the bit again.)
*/
#define invalidateTMcache(t)	((t)->flags &= ~maskflags)


/* true when 't' is using 'dummynode' as its hash part */
#define isdummy(t)		((t)->lastfree == NULL)


/* allocated size for hash nodes */
#define allocsizenode(t)	(isdummy(t) ? 0 : sizenode(t))


/* returns the Node, given the value of a table entry */
#define nodefromval(v)	cast(Node *, (v))


NC_LUAI_FUNC const TValue *luaH_getint (Table *t, lua_Integer key);
NC_LUAI_FUNC void luaH_setint (nc_lua_flow_t *L, Table *t, lua_Integer key,
                                                    TValue *value);
NC_LUAI_FUNC const TValue *luaH_getshortstr (Table *t, TString *key);
NC_LUAI_FUNC const TValue *luaH_getstr (Table *t, TString *key);
NC_LUAI_FUNC const TValue *luaH_get (Table *t, const TValue *key);
NC_LUAI_FUNC TValue *luaH_newkey (nc_lua_flow_t *L, Table *t, const TValue *key);
NC_LUAI_FUNC TValue *luaH_set (nc_lua_flow_t *L, Table *t, const TValue *key);
NC_LUAI_FUNC Table *luaH_new (nc_lua_flow_t *L);
NC_LUAI_FUNC void luaH_resize (nc_lua_flow_t *L, Table *t, unsigned int nasize,
                                                    unsigned int nhsize);
NC_LUAI_FUNC void luaH_resizearray (nc_lua_flow_t *L, Table *t, unsigned int nasize);
NC_LUAI_FUNC void luaH_free (nc_lua_flow_t *L, Table *t);
NC_LUAI_FUNC int luaH_next (nc_lua_flow_t *L, Table *t, StkId key);
NC_LUAI_FUNC lua_Unsigned luaH_getn (Table *t);
NC_LUAI_FUNC unsigned int luaH_realasize (const Table *t);


#if defined(NC_LUA_DEBUG)
NC_LUAI_FUNC Node *luaH_mainposition (const Table *t, const TValue *key);
NC_LUAI_FUNC int luaH_isdummy (const Table *t);
#endif


#endif
