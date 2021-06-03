#ifndef NC_LUA_SYSTEM_HXX
#   define NC_LUA_SYSTEM_HXX
#   include "../nc_lua_core.hxx"
#   if (defined(NC_API))
/* defines */
#       if (NC_LANG && NC_LANG_CPP)
extern "C" {
#       endif   /* NC_LANG_CPP */
/* includes */
/* types */
/* lua_system_type
 * description:
 * ->
*/
typedef struct nc_lua_sys_t nc_lua_sys_t;
/** getters **/
NC_API nc_lua_sys_t* nc_lua_sys_get();
/** setters **/
/** vetters **/
/** commands **/
NC_API v1bit_t nc_lua_sys_init();
NC_API v1bit_t nc_lua_sys_quit();
NC_API v1bit_t nc_lua_sys_work();
NC_API v1bit_t nc_lua_sys_smem(ptr_t* data, size_t isize, size_t osize);
#       if (NC_LANG && NC_LANG_CPP)
} /* extern "C" */
#       endif   /* NC_LANG_CPP */
#   endif  /* NC_API */
#endif  /* NC_LUA_SYSTEM_HXX */