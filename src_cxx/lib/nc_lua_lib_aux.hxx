#ifndef NC_LUA_LIB_AUXIAURY_H
#    define NC_LUA_LIB_AUXIAURY_H
#    include "../nc_lua_core.hxx"
#    include <stddef.h>
#    include <stdio.h>
/* global table */
#    define NC_LUA_GNAME "_G"
typedef struct luaL_Buffer luaL_Buffer;
/* extra error code for 'luaL_loadfilex' */
#    define NC_LUA_ERRFILE     (NC_LUA_ERRERR+1)
/* key, in the registry, for table of loaded modules */
#define NC_LUA_LOADED_TABLE	"_LOADED"
/* key, in the registry, for table of preloaded loaders */
#define NC_LUA_PRELOAD_TABLE	"_PRELOAD"
typedef struct luaL_Reg {
  const char *name;
  lua_CFunction func;
} luaL_Reg;
#define NC_LUAL_NUMSIZES	(sizeof(lua_Integer)*16 + sizeof(lua_Number))

NC_API void (luaL_checkversion_) (nc_lua_flow_t *L, lua_Number ver, size_t sz);
#define luaL_checkversion(L)  \
	  luaL_checkversion_(L, NC_LUA_VERSION_NUM, NC_LUAL_NUMSIZES)

NC_API int (luaL_getmetafield) (nc_lua_flow_t *L, int obj, const char *e);
NC_API int (luaL_callmeta) (nc_lua_flow_t *L, int obj, const char *e);
NC_API const char *(luaL_tolstring) (nc_lua_flow_t *L, int idx, size_t *len);
NC_API int (luaL_argerror) (nc_lua_flow_t *L, int arg, const char *extramsg);
NC_API int (luaL_typeerror) (nc_lua_flow_t *L, int arg, const char *tname);
NC_API const char *(luaL_checklstring) (nc_lua_flow_t *L, int arg,
                                                          size_t *l);
NC_API const char *(luaL_optlstring) (nc_lua_flow_t *L, int arg,
                                          const char *def, size_t *l);
NC_API lua_Number (luaL_checknumber) (nc_lua_flow_t *L, int arg);
NC_API lua_Number (luaL_optnumber) (nc_lua_flow_t *L, int arg, lua_Number def);

NC_API lua_Integer (luaL_checkinteger) (nc_lua_flow_t *L, int arg);
NC_API lua_Integer (luaL_optinteger) (nc_lua_flow_t *L, int arg,
                                          lua_Integer def);

NC_API void (luaL_checkstack) (nc_lua_flow_t *L, int sz, const char *msg);
NC_API void (luaL_checktype) (nc_lua_flow_t *L, int arg, int t);
NC_API void (luaL_checkany) (nc_lua_flow_t *L, int arg);

NC_API int   (luaL_newmetatable) (nc_lua_flow_t *L, const char *tname);
NC_API void  (luaL_setmetatable) (nc_lua_flow_t *L, const char *tname);
NC_API void *(luaL_testudata) (nc_lua_flow_t *L, int ud, const char *tname);
NC_API void *(luaL_checkudata) (nc_lua_flow_t *L, int ud, const char *tname);

NC_API void (luaL_where) (nc_lua_flow_t *L, int lvl);
NC_API int (luaL_error) (nc_lua_flow_t *L, const char *fmt, ...);

NC_API int (luaL_checkoption) (nc_lua_flow_t *L, int arg, const char *def,
                                   const char *const lst[]);

NC_API int (luaL_fileresult) (nc_lua_flow_t *L, int stat, const char *fname);
NC_API int (luaL_execresult) (nc_lua_flow_t *L, int stat);


/* predefined references */
#define NC_LUA_NOREF       (-2)
#define NC_LUA_REFNIL      (-1)

NC_API int (luaL_ref) (nc_lua_flow_t *L, int t);
NC_API void (luaL_unref) (nc_lua_flow_t *L, int t, int ref);

NC_API int (luaL_loadfilex) (nc_lua_flow_t *L, const char *filename,
                                               const char *mode);

#define luaL_loadfile(L,f)	luaL_loadfilex(L,f,NULL)

NC_API int (luaL_loadbufferx) (nc_lua_flow_t *L, const char *buff, size_t sz,
                                   const char *name, const char *mode);
NC_API int (luaL_loadstr) (nc_lua_flow_t *L, const char *s);

NC_API nc_lua_flow_t *(luaL_newstate) (void);

NC_API lua_Integer (luaL_len) (nc_lua_flow_t *L, int idx);

NC_API void luaL_addgsub (luaL_Buffer *b, const char *s,
                                     const char *p, const char *r);
NC_API const char *(luaL_gsub) (nc_lua_flow_t *L, const char *s,
                                    const char *p, const char *r);

NC_API void (luaL_setfuncs) (nc_lua_flow_t *L, const luaL_Reg *l, int nup);

NC_API int (luaL_getsubtable) (nc_lua_flow_t *L, int idx, const char *fname);

NC_API void (luaL_traceback) (nc_lua_flow_t *L, nc_lua_flow_t *L1,
                                  const char *msg, int level);

NC_API void (luaL_requiref) (nc_lua_flow_t *L, const char *modname,
                                 lua_CFunction openf, int glb);

/*
** ===============================================================
** some useful macros
** ===============================================================
*/


#define luaL_newlibtable(L,l)	\
  lua_createtable(L, 0, sizeof(l)/sizeof((l)[0]) - 1)

#define luaL_newlib(L,l)  \
  (luaL_checkversion(L), luaL_newlibtable(L,l), luaL_setfuncs(L,l,0))

#define luaL_argcheck(L, cond,arg,extramsg)	\
		((void)((cond) || luaL_argerror(L, (arg), (extramsg))))

#define luaL_argexpected(L,cond,arg,tname)	\
		((void)((cond) || luaL_typeerror(L, (arg), (tname))))

#define luaL_checkstring(L,n)	(luaL_checklstring(L, (n), NULL))
#define luaL_optstring(L,n,d)	(luaL_optlstring(L, (n), (d), NULL))

#define luaL_typename(L,i)	lua_typename(L, lua_type(L,(i)))

#define luaL_dofile(L, fn) \
	(luaL_loadfile(L, fn) || lua_pcall(L, 0, NC_LUA_MULTRET, 0))

#define luaL_dostring(L, s) \
	(luaL_loadstr(L, s) || lua_pcall(L, 0, NC_LUA_MULTRET, 0))

#define luaL_getmetatable(L,n)	(lua_getfield(L, NC_LUA_REGISTRYINDEX, (n)))

#define luaL_opt(L,f,n,d)	(lua_isnoneornil(L,(n)) ? (d) : f(L,(n)))

#define luaL_loadbuffer(L,s,sz,n)	luaL_loadbufferx(L,s,sz,n,NULL)


/* push the value used to represent failure/error */
#define luaL_pushfail(L)	lua_pushnil(L)


/*
** {======================================================
** Generic Buffer manipulation
** =======================================================
*/

struct luaL_Buffer {
  char *b;  /* buffer address */
  size_t size;  /* buffer size */
  size_t n;  /* number of characters in buffer */
  nc_lua_flow_t *L;
  union {
    NC_LUAI_MAXALIGN;  /* ensure maximum alignment for buffer */
    char b[NC_LUAL_BUFFERSIZE];  /* initial buffer */
  } init;
};


#define luaL_bufflen(bf)	((bf)->n)
#define luaL_buffaddr(bf)	((bf)->b)


#define luaL_addchar(B,c) \
  ((void)((B)->n < (B)->size || luaL_prepbuffsize((B), 1)), \
   ((B)->b[(B)->n++] = (c)))

#define luaL_addsize(B,s)	((B)->n += (s))

#define luaL_buffsub(B,s)	((B)->n -= (s))

NC_API void (luaL_buffinit) (nc_lua_flow_t *L, luaL_Buffer *B);
NC_API char *(luaL_prepbuffsize) (luaL_Buffer *B, size_t sz);
NC_API void (luaL_addlstring) (luaL_Buffer *B, const char *s, size_t l);
NC_API void (luaL_addstr) (luaL_Buffer *B, const char *s);
NC_API void (luaL_addvalue) (luaL_Buffer *B);
NC_API void (luaL_pushresult) (luaL_Buffer *B);
NC_API void (luaL_pushresultsize) (luaL_Buffer *B, size_t sz);
NC_API char *(luaL_buffinitsize) (nc_lua_flow_t *L, luaL_Buffer *B, size_t sz);

#define luaL_prepbuffer(B)	luaL_prepbuffsize(B, NC_LUAL_BUFFERSIZE)

/* }====================================================== */



/*
** {======================================================
** File handles for IO library
** =======================================================
*/

/*
** A file handle is a userdata with metatable 'NC_LUA_FILEHANDLE' and
** initial structure 'luaL_Stream' (it may contain other fields
** after that initial structure).
*/

#define NC_LUA_FILEHANDLE          "FILE*"


typedef struct luaL_Stream {
  FILE *f;  /* stream (NULL for incompletely created streams) */
  lua_CFunction closef;  /* to close stream (NULL for closed streams) */
} luaL_Stream;

/* }====================================================== */

/*
** {==================================================================
** "Abstraction Layer" for basic report of messages and errors
** ===================================================================
*/

/* print a string */
#if !defined(lua_writestring)
#define lua_writestring(s,l)   fwrite((s), sizeof(char), (l), stdout)
#endif

/* print a newline and flush the output */
#if !defined(lua_writeline)
#define lua_writeline()        (lua_writestring("\n", 1), fflush(stdout))
#endif

/* print an error message */
#if !defined(lua_writestringerror)
#define lua_writestringerror(s,p) \
        (fprintf(stderr, (s), (p)), fflush(stderr))
#endif

/* }================================================================== */


/*
** {============================================================
** Compatibility with deprecated conversions
** =============================================================
*/
#if defined(NC_LUA_COMPAT_APIINTCASTS)

#define luaL_checkunsigned(L,a)	((lua_Unsigned)luaL_checkinteger(L,a))
#define luaL_optunsigned(L,a,d)	\
	((lua_Unsigned)luaL_optinteger(L,a,(lua_Integer)(d)))

#define luaL_checkint(L,n)	((int)luaL_checkinteger(L, (n)))
#define luaL_optint(L,n,d)	((int)luaL_optinteger(L, (n), (d)))

#define luaL_checklong(L,n)	((long)luaL_checkinteger(L, (n)))
#define luaL_optlong(L,n,d)	((long)luaL_optinteger(L, (n), (d)))

#endif
/* }============================================================ */
/* end_of_file */
#endif  // NC_LUA_LIB_AUXIAURY_H //