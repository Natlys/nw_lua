#ifndef NC_LUA_LIB_H
#    define NC_LUA_LIB_H
#    include "../nc_lua_core.h"
#    if (defined NC_API)
// version suffix for environment variable names
#define NC_LUA_VERSUFFIX	"_" NC_LUA_VERSION_MAJOR "_" NC_LUA_VERSION_MINOR

NC_LUAMOD_API int (luaopen_base) (lua_State *L);

#define NC_LUA_COLIBNAME	"coroutine"
NC_LUAMOD_API int (luaopen_coroutine) (lua_State *L);

#define NC_LUA_TABLIBNAME	"table"
NC_LUAMOD_API int (luaopen_table) (lua_State *L);

#define NC_LUA_IOLIBNAME	"io"
NC_LUAMOD_API int (luaopen_io) (lua_State *L);

#define NC_LUA_OSLIBNAME	"os"
NC_LUAMOD_API int (luaopen_os) (lua_State *L);

#define NC_LUA_STRLIBNAME	"string"
NC_LUAMOD_API int (luaopen_string) (lua_State *L);

#define NC_LUA_UTF8LIBNAME	"utf8"
NC_LUAMOD_API int (luaopen_utf8) (lua_State *L);

#define NC_LUA_MATHLIBNAME	"math"
NC_LUAMOD_API int (luaopen_math) (lua_State *L);

#define NC_LUA_DBLIBNAME	"debug"
NC_LUAMOD_API int (luaopen_debug) (lua_State *L);

#define NC_LUA_LOADLIBNAME	"package"
NC_LUAMOD_API int (luaopen_package) (lua_State *L);

// open all previous libraries
NC_LUA_API void (luaL_openlibs) (lua_State *L);

#        if !defined(lua_assert)
#	         define lua_assert(x) ((void)0)
#        endif // lua_assert //
#    endif // NC_API //
// end_of_file //
#endif	// NC_LUALIB_H //