/*
** $Id: lua_undump.h $
** load precompiled Lua chunks
** See Copyright Notice in lua_core.h
*/

#ifndef NC_LUA_DUMP_H
#define NC_LUA_DUMP_H

#include "nc_lua_limit.h"
#include "nc_lua_obj.h"
#include "nc_lua_zbuf.h"


/* data to catch conversion errors */
#define NC_LUAC_DATA	"\x19\x93\r\n\x1a\n"

#define NC_LUAC_INT	0x5678
#define NC_LUAC_NUM	cast_num(370.5)

/*
** Encode major-minor version in one byte, one nibble for each
*/
#define MYINT(s)	(s[0]-'0')  /* assume one-digit numerals */
#define NC_LUAC_VERSION	(MYINT(NC_LUA_VERSION_MAJOR)*16+MYINT(NC_LUA_VERSION_MINOR))

#define NC_LUAC_FORMAT	0	/* this is the official format */

/* load one chunk; from lundump.c */
NC_LUAI_FUNC LClosure* luaU_undump (lua_State* L, ZIO* Z, const char* name);

/* dump one chunk; from ldump.c */
NC_LUAI_FUNC int luaU_dump (lua_State* L, const Proto* f, lua_Writer w,
                         void* data, int strip);

#endif  // NC_LUA_DUMP_H
