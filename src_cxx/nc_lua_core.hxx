#ifndef NC_LUA_CORE_HXX
#    define NC_LUA_CORE_HXX
/* config */
// building //
#   if (defined NC_BUILD)
#       undef NC_BUILD
#   endif   /* NC_BUILD */
#   define NC_BUILD NC_BUILD_LIB
// include //
#   include "nc_lua_pch.hxx"
/* defines */
/** coding **/
#   define NC_LUA_MRET (-1) /* option for multiple returns in 'lua_pcall' and 'lua_call' */
#   define NC_LUA_SIGN "\x1blua" /* signature for compiled code */
/** directories and files **/
#	define NC_LUA_VDIR NC_LUA_VER_MAJOR "." NC_LUA_VER_MINOR /* */
#   if (NC_WAPI & NC_WAPI_WIN)
#	    define NC_LUA_PATH_FSEP ";" // character that separates templates in a path; //
#	    define NC_LUA_PATH_MARK "?" // the string that marks the substitution points in a template; //
#	    define NC_LUA_EXEC_FDIR "!" // in windows gets replaced by the executable's directory; //
#		define NC_LUA_LDIR NC_LUA_EXEC_FDIR NC_STR_FDIR "lua" NC_STR_FDIR
#		define NC_LUA_CDIR NC_LUA_EXEC_FDIR NC_STR_FDIR
#		define NC_LUA_SDIR NC_LUA_EXEC_FDIR NC_STR_FDIR ".." NC_STR_FDIR "share" NC_STR_FDIR "lua" NC_STR_FDIR NC_LUA_VDIR NC_STR_FDIR
#		define NC_LUA_LPATH /*default path for "require" lua libraries*/         \
		    NC_LUA_LDIR NC_LUA_PATH_MARK ".lua" NC_LUA_PATH_FSEP                 \
		    NC_LUA_CDIR NC_LUA_PATH_MARK ".lua" NC_LUA_PATH_FSEP                 \
		    NC_LUA_SDIR NC_LUA_PATH_MARK ".lua" NC_LUA_PATH_FSEP                 \
            NC_LUA_LDIR NC_LUA_PATH_MARK NC_STR_FDIR "init.lua" NC_LUA_PATH_FSEP \
            NC_LUA_CDIR NC_LUA_PATH_MARK NC_STR_FDIR "init.lua" NC_LUA_PATH_FSEP \
            NC_LUA_SDIR NC_LUA_PATH_MARK NC_STR_FDIR "init.lua" NC_LUA_PATH_FSEP \
		    "." NC_STR_FDIR NC_LUA_PATH_MARK ".lua" NC_LUA_PATH_FSEP             \
            "." NC_STR_FDIR NC_LUA_PATH_MARK NC_STR_FDIR "init.lua"              \
// NC_LUA_LPATH //
#	    define NC_LUA_CPATH  /*defaul path for "require" cxx libraries*/     \
		    NC_LUA_CDIR NC_STR_FDIR ".dll" NC_LUA_PATH_FSEP                  \
		    NC_LUA_CDIR ".." NC_STR_FDIR "lib" NC_STR_FDIR "lua" NC_STR_FDIR \
            NC_LUA_VDIR NC_STR_FDIR "?.dll" NC_LUA_PATH_FSEP                 \
		    NC_LUA_CDIR "loadall.dll" NC_LUA_PATH_FSEP "." NC_STR_FDIR NC_LUA_PATH_MARK ".dll" \
// NC_LUA_CPATH //
#   else
#	    define NC_LUA_RDIR NC_STR_FDIR "usr"   NC_STR_FDIR "local" NC_STR_FDIR
#	    define NC_LUA_LDIR NC_LUA_RDIR "share" NC_STR_FDIR "lua" NC_STR_FDIR NC_LUA_VDIR NC_STR_FDIR
#	    define NC_LUA_CDIR NC_LUA_RDIR "lib"   NC_STR_FDIR "lua" NC_STR_FDIR NC_LUA_VDIR NC_STR_FDIR
#	    define NC_LUA_LPATH                                                      \
	        NC_LUA_LDIR NC_LUA_PATH_MARK ".lua" NC_LUA_PATH_FSEP                 \
        	NC_LUA_CDIR NC_LUA_PATH_MARK ".lua" NC_LUA_PATH_FSEP                 \
            NC_LUA_LDIR NC_LUA_PATH_MARK NC_STR_FDIR "init.lua" NC_LUA_PATH_FSEP \
            NC_LUA_CDIR NC_LUA_PATH_MARK NC_STR_FDIR "init.lua" NC_LUA_PATH_FSEP \
        	"." NC_STR_FDIR NC_LUA_PATH_MARK ".lua" NC_LUA_PATH_FSEP             \
            "." NC_STR_FDIR NC_LUA_PATH_MARK NC_STR_FDIR "init.lua"              \
// NC_LUA_LPATH //
#       define NC_LUA_CPATH                                                                  \
            NC_LUA_CDIR NC_LUA_PATH_MARK ".so" NC_LUA_PATH_FSEP                              \
            NC_LUA_CDIR "loadall.so" NC_LUA_PATH_FSEP "." NC_STR_FDIR NC_LUA_PATH_MARK ".so" \
// NC_LUA_CPATH //
#   endif   // NC_WAPI_WIN //
// // all functions that are not to be exported to outside modules // //
#   if (NC_CAPI & NC_CAPI_GNU) && ((__GNUC__*100 + __GNUC_MINOR__) >= 302) && defined(__ELF__) 
#	    define NC_LUAI_FUNC	__attribute__((visibility("internal"))) extern
#   else
#	    define NC_LUAI_FUNC	extern
#   endif   // NC_CAPI_GNU //
#define NC_LUAI_DDEC(dec) NC_LUAI_FUNC dec // extern const variables //
#define NC_LUAI_DDEF	  NC_VOID // extern const variables //
// // linkage // //
#   if (defined NC_API)
#       undef NC_API
#   endif   /* NC_API */
#   if (!(defined NC_BUILD))
#       error "undefined build type!"
#   elif (NC_BUILD & NC_BUILD_EXE)
#       define NC_API extern
#   elif (NC_BUILD & NC_BUILD_LIB)
#       define NC_API extern
#   elif (NC_BUILD & NC_BUILD_DLL)
#       define NC_API NC_DLL_EXPORT
#   else
#       define NC_API NC_DLL_IMPORT
#   endif	/* NC_BUILD */
/* end_of_file */
#endif  // NC_LUA_CORE_HXX //

#ifndef NC_LUA_CONFIG_H
#	define NC_LUA_CONFIG_H
// pseudo-indices //
// basic types //
#    define NC_LUA_TYPE_NON (-1)
#    define NC_LUA_TYPE_NIL (+0)
#    define NC_LUA_TYPE_BIT (+1)
#    define NC_LUA_TYPE_LDA (+2)
#    define NC_LUA_TYPE_NUM (+3)
#    define NC_LUA_TYPE_STR (+4)
#    define NC_LUA_TYPE_TAB (+5)
#    define NC_LUA_TYPE_FUN (+6)
#    define NC_LUA_TYPE_VAL (+7)
#    define NC_LUA_TYPE_FLO (+8)
#    define NC_LUA_TYPE_NTP (+9)
typedef struct nc_lua_flow_t nc_lua_flow_t; /* main lua thread */
typedef intptr_t intptr_t; /* type for continuation-function contexts */
typedef v1s_t  (*nc_lua_native_tf) (nc_lua_flow_t *L); /* cxx function registered with lua */
typedef v1s_t  (*nc_lua_contin_tf) (nc_lua_flow_t *L, int status, intptr_t ctx); /* continuation functions */
typedef cstr_t (*nc_lua_oput_tf) (nc_lua_flow_t *L, void *ud, size_t *sz); /* read blocks when loading lua chunks */
typedef v1s_t  (*nc_lua_iput_tf) (nc_lua_flow_t *L, const void *p, size_t sz, void *ud); /* read blocks when dumping lua chunks */
// type for memory-allocation functions //
typedef ptr_t (*nc_lua_alloc_tf) (ptr_t ud, ptr_t ptr, size_t osize, size_t nsize);
// type for warning functions //
typedef nil_t (*nc_lua_warn) (ptr_t ud, cstr_t msg, v1s_t tocont);
// rcs ident string //
extern const char lua_ident[];
// state manipulation //
NC_API nc_lua_flow_t *(lua_newstate) (nc_lua_alloc_tf f, void *ud);
NC_API void       (lua_close) (nc_lua_flow_t *L);
NC_API nc_lua_flow_t *(lua_newthread) (nc_lua_flow_t *L);
NC_API int        (lua_resetthread) (nc_lua_flow_t *L);
// error callback function //
NC_API lua_CFunction (lua_atpanic) (nc_lua_flow_t *L, lua_CFunction panicf);
// version getter //
NC_API lua_Number (lua_version) (nc_lua_flow_t *L);
// basic stack manipulation
NC_API int   (lua_absindex) (nc_lua_flow_t *L, int idx);
NC_API int   (lua_gettop) (nc_lua_flow_t *L);
NC_API void  (lua_settop) (nc_lua_flow_t *L, int idx);
NC_API void  (lua_pushvalue) (nc_lua_flow_t *L, int idx);
NC_API void  (lua_rotate) (nc_lua_flow_t *L, int idx, int n);
NC_API void  (lua_copy) (nc_lua_flow_t *L, int fromidx, int toidx);
NC_API int   (lua_checkstack) (nc_lua_flow_t *L, int n);
NC_API void  (lua_xmove) (nc_lua_flow_t *from, nc_lua_flow_t *to, int n);
// getters (stack -> c) //
NC_API int             (lua_isnumber) (nc_lua_flow_t *L, int idx);
NC_API int             (lua_isstring) (nc_lua_flow_t *L, int idx);
NC_API int             (lua_iscfunction) (nc_lua_flow_t *L, int idx);
NC_API int             (lua_isinteger) (nc_lua_flow_t *L, int idx);
NC_API int             (lua_isuserdata) (nc_lua_flow_t *L, int idx);
NC_API int             (lua_type) (nc_lua_flow_t *L, int idx);
NC_API const char     *(lua_typename) (nc_lua_flow_t *L, int tp);
NC_API lua_Number      (lua_tonumberx) (nc_lua_flow_t *L, int idx, int *isnum);
NC_API lua_Integer     (lua_tointegerx) (nc_lua_flow_t *L, int idx, int *isnum);
NC_API int             (lua_toboolean) (nc_lua_flow_t *L, int idx);
NC_API const char     *(lua_tolstring) (nc_lua_flow_t *L, int idx, size_t *len);
NC_API lua_Unsigned    (lua_rawlen) (nc_lua_flow_t *L, int idx);
NC_API lua_CFunction   (lua_tocfunction) (nc_lua_flow_t *L, int idx);
NC_API void	       *(lua_touserdata) (nc_lua_flow_t *L, int idx);
NC_API nc_lua_flow_t      *(lua_tothread) (nc_lua_flow_t *L, int idx);
NC_API const void     *(lua_topointer) (nc_lua_flow_t *L, int idx);
// comparison and arithmetic functions //
#    define NC_OPER_ADD   0 /* add */
#    define NC_OPER_SUB   1 /* substract */
#    define NC_OPER_MUL   2 /* multiply */
#    define NC_OPER_MOD   3 /* modulus */
#    define NC_OPER_POW   4 /* power */
#    define NC_OPER_FDIV  5 /* float division */
#    define NC_OPER_IDIV  6 /* integer division */
#    define NC_OPER_BNOT  7 /* and */
#    define NC_OPER_BAND  8 /* and */
#    define NC_OPER_BOR   9 /* or */
#    define NC_OPER_BXOR  10 /* exclusive or */
#    define NC_OPER_SHL   11 /* smth */
#    define NC_OPER_SHR   12 /* smth */
#    define NC_OPER_UNM   13 /* smth */
/* function view */
NC_API nil_t (nc_lua_arith)(nc_lua_flow_t *L, v1s_t op);

#    define NC_OPER_TEQU 0
#    define NC_OPER_LESS 1
#    define NC_OPER_LEQU 2
#    define NC_OPER_GRET 3
#    define NC_OPER_GEQU 4

NC_API v1s_t (nc_lua_rawequal) (nc_lua_flow_t *L, int idx1, int idx2);
NC_API v1s_t (lua_compare) (nc_lua_flow_t *L, int idx1, int idx2, int op);

// setters (c -> stack) //
NC_API void        (lua_pushnil) (nc_lua_flow_t *L);
NC_API void        (lua_pushnumber) (nc_lua_flow_t *L, lua_Number n);
NC_API void        (lua_pushinteger) (nc_lua_flow_t *L, lua_Integer n);
NC_API const char *(lua_pushlstring) (nc_lua_flow_t *L, const char *s, size_t len);
NC_API const char *(lua_pushstring) (nc_lua_flow_t *L, const char *s);
NC_API const char *(lua_pushvfstring) (nc_lua_flow_t *L, const char *fmt, va_list argp);
NC_API const char *(lua_pushfstring) (nc_lua_flow_t *L, const char *fmt, ...);
NC_API void  (lua_pushcclosure) (nc_lua_flow_t *L, lua_CFunction fn, int n);
NC_API void  (lua_pushboolean) (nc_lua_flow_t *L, int b);
NC_API void  (lua_pushlightuserdata) (nc_lua_flow_t *L, void *p);
NC_API int   (lua_pushthread) (nc_lua_flow_t *L);
// getters (lua -> stack) //
NC_API int (lua_getglobal) (nc_lua_flow_t *L, const char *name);
NC_API int (lua_gettable) (nc_lua_flow_t *L, int idx);
NC_API int (lua_getfield) (nc_lua_flow_t *L, int idx, const char *k);
NC_API int (lua_geti) (nc_lua_flow_t *L, int idx, lua_Integer n);
NC_API int (lua_rawget) (nc_lua_flow_t *L, int idx);
NC_API int (lua_rawgeti) (nc_lua_flow_t *L, int idx, lua_Integer n);
NC_API int (lua_rawgetp) (nc_lua_flow_t *L, int idx, const void *p);
NC_API void  (lua_createtable) (nc_lua_flow_t *L, int narr, int nrec);
NC_API void *(lua_newuserdatauv) (nc_lua_flow_t *L, size_t sz, int nuvalue);
NC_API int   (lua_getmetatable) (nc_lua_flow_t *L, int objindex);
NC_API int  (lua_getiuservalue) (nc_lua_flow_t *L, int idx, int n);
// setters (stack -> Lua) //
NC_API void  (lua_setglobal) (nc_lua_flow_t *L, const char *name);
NC_API void  (lua_settable) (nc_lua_flow_t *L, int idx);
NC_API void  (lua_setfield) (nc_lua_flow_t *L, int idx, const char *k);
NC_API void  (lua_seti) (nc_lua_flow_t *L, int idx, lua_Integer n);
NC_API void  (lua_rawset) (nc_lua_flow_t *L, int idx);
NC_API void  (lua_rawseti) (nc_lua_flow_t *L, int idx, lua_Integer n);
NC_API void  (lua_rawsetp) (nc_lua_flow_t *L, int idx, const void *p);
NC_API int   (lua_setmetatable) (nc_lua_flow_t *L, int objindex);
NC_API int   (lua_setiuservalue) (nc_lua_flow_t *L, int idx, int n);
// 'load' and 'call' functions (load and run lua code) //
NC_API void  (lua_callk) (nc_lua_flow_t *L, int nargs, int nresults, intptr_t ctx, lua_KFunction k);
#define lua_call(L,n,r)		lua_callk(L, (n), (r), 0, NULL)
NC_API int   (lua_pcallk) (nc_lua_flow_t *L, int nargs, int nresults, int errfunc, intptr_t ctx, lua_KFunction k);
#define lua_pcall(L,n,r,f)	lua_pcallk(L, (n), (r), (f), 0, NULL)
NC_API int   (lua_load) (nc_lua_flow_t *L, lua_Reader reader, void *dt, const char *chunkname, const char *mode);
NC_API int (lua_dump) (nc_lua_flow_t *L, lua_Writer writer, void *data, int strip);
// coroutine functions //
NC_API int  (lua_yieldk)     (nc_lua_flow_t *L, int nresults, intptr_t ctx, lua_KFunction k);
NC_API int  (lua_resume)     (nc_lua_flow_t *L, nc_lua_flow_t *from, int narg, int *nres);
NC_API int  (lua_status)     (nc_lua_flow_t *L);
NC_API int (lua_isyieldable) (nc_lua_flow_t *L);
#define lua_yield(L,n)		lua_yieldk(L, (n), 0, NULL)
// warning-related functions //
NC_API void (lua_setwarnf) (nc_lua_flow_t *L, lua_WarnFunction f, void *ud);
NC_API void (lua_warning)  (nc_lua_flow_t *L, const char *msg, int tocont);
// garbage-collection function and options //
#   define NC_LUA_GCSTOP       0
#   define NC_LUA_GCRESTART    1
#   define NC_LUA_GCCOLLECT    2
#   define NC_LUA_GCCOUNT	   3
#   define NC_LUA_GCCOUNTB     4
#   define NC_LUA_GCSTEP       5
#   define NC_LUA_GCSETPAUSE   6
#   define NC_LUA_GCSETSTEPMUL 7
#   define NC_LUA_GCISRUNNING  9
#   define NC_LUA_GCGEN        10
#   define NC_LUA_GCINC        11
NC_API int (lua_gc) (nc_lua_flow_t *L, int what, ...);
// miscellaneous functions //
NC_API int   (lua_error) (nc_lua_flow_t *L);
NC_API int   (lua_next) (nc_lua_flow_t *L, int idx);
NC_API void  (lua_concat) (nc_lua_flow_t *L, int n);
NC_API void  (lua_len)    (nc_lua_flow_t *L, int idx);
NC_API size_t   (lstringtonumber) (nc_lua_flow_t *L, const char *s);
NC_API lua_Alloc (lua_getallocf) (nc_lua_flow_t *L, void **ud);
NC_API void      (lua_setallocf) (nc_lua_flow_t *L, lua_Alloc f, void *ud);
NC_API void  (lua_toclose) (nc_lua_flow_t *L, int idx);
// useful_macros //
#define lua_getextraspace(L)	((void *)((char *)(L) - NC_LUA_EXTRASPACE))

#define lua_tonumber(L,i)	lua_tonumberx(L,(i),NULL)
#define lua_tointeger(L,i)	lua_tointegerx(L,(i),NULL)

#define lua_pop(L,n)		lua_settop(L, -(n)-1)

#define lua_newtable(L)		lua_createtable(L, 0, 0)

#define lua_register(L,n,f) (lua_pushcfunction(L, (f)), lua_setglobal(L, (n)))

#define lua_pushcfunction(L,f)	lua_pushcclosure(L, (f), 0)

#define lua_isfunction(L,n)	(lua_type(L, (n)) == NC_LUA_TFUNCTION)
#define lua_istable(L,n)	(lua_type(L, (n)) == NC_LUA_TTABLE)
#define lua_islightuserdata(L,n)	(lua_type(L, (n)) == NC_LUA_TLIGHTUSERDATA)
#define lua_isnil(L,n)		(lua_type(L, (n)) == NC_LUA_TNIL)
#define lua_isboolean(L,n)	(lua_type(L, (n)) == NC_LUA_TBOOLEAN)
#define lua_isthread(L,n)	(lua_type(L, (n)) == NC_LUA_TTHREAD)
#define lua_isnone(L,n)		(lua_type(L, (n)) == NC_LUA_TNONE)
#define lua_isnoneornil(L, n)	(lua_type(L, (n)) <= 0)

#define lua_pushliteral(L, s)	lua_pushstring(L, "" s)

#define lua_pushglobalua_tab(L) ((void)lua_rawgeti(L, NC_LUA_REGISTRYINDEX, NC_LUA_RIDX_GLOBALS))

#define lua_tostring(L,i)	lua_tolstring(L, (i), NULL)

#define lua_insert(L,idx)	lua_rotate(L, (idx), 1)

#define lua_remove(L,idx)	(lua_rotate(L, (idx), -1), lua_pop(L, 1))

#define lua_replace(L,idx)	(lua_copy(L, -1, (idx)), lua_pop(L, 1))
// compatibility_macros //
#    if defined(NC_LUA_COMPAT_APIINTCASTS)
#        define lua_pushunsigned(L,n)    lua_pushinteger(L, (lua_Integer)(n))
#        define lua_tounsignedx(L,i,is)  ((lua_Unsigned)lua_tointegerx(L,i,is))
#        define lua_tounsigned(L,i)      lua_tounsignedx(L,(i),NULL)
#    endif
// user_data //
#define lua_newuserdata(L,s)	lua_newuserdatauv(L,s,1)
#define lua_getuservalue(L,idx)	lua_getiuservalue(L,idx,1)
#define lua_setuservalue(L,idx)	lua_setiuservalue(L,idx,1)
#define NC_LUA_NUMTAGS		NC_LUA_NUMTYPES
// debug_api //
// // event codes // //
#define NC_LUA_HOOKCALL	0
#define NC_LUA_HOOKRET	1
#define NC_LUA_HOOKLINE	2
#define NC_LUA_HOOKCOUNT	3
#define NC_LUA_HOOKTAILCALL 4
// // event masks // //
#define NC_LUA_MASKCALL	(1 << NC_LUA_HOOKCALL)
#define NC_LUA_MASKRET	(1 << NC_LUA_HOOKRET)
#define NC_LUA_MASKLINE	(1 << NC_LUA_HOOKLINE)
#define NC_LUA_MASKCOUNT	(1 << NC_LUA_HOOKCOUNT)

typedef struct lua_Debug lua_Debug;  // activation record

// functions to be called by the debugger in specific events
typedef void (*lua_Hook) (nc_lua_flow_t *L, lua_Debug *ar);

NC_API int (lua_getstack) (nc_lua_flow_t *L, int level, lua_Debug *ar);
NC_API int (lua_getinfo) (nc_lua_flow_t *L, const char *what, lua_Debug *ar);
NC_API const char *(lua_getlocal) (nc_lua_flow_t *L, const lua_Debug *ar, int n);
NC_API const char *(lua_setlocal) (nc_lua_flow_t *L, const lua_Debug *ar, int n);
NC_API const char *(lua_getupvalue) (nc_lua_flow_t *L, int funcindex, int n);
NC_API const char *(lua_setupvalue) (nc_lua_flow_t *L, int funcindex, int n);

NC_API void *(lua_upvalueid) (nc_lua_flow_t *L, int fidx, int n);
NC_API void  (lua_upvaluejoin) (nc_lua_flow_t *L, int fidx1, int n1, int fidx2, int n2);

NC_API void (lua_sethook) (nc_lua_flow_t *L, lua_Hook func, int mask, int count);
NC_API lua_Hook (lua_gethook) (nc_lua_flow_t *L);
NC_API int (lua_gethookmask) (nc_lua_flow_t *L);
NC_API int (lua_gethookcount) (nc_lua_flow_t *L);

NC_API int (lua_setcstacklimit) (nc_lua_flow_t *L, unsigned int limit);

struct lua_Debug {
    int event;
    const char* name;	/* (n) */
    const char* namewhat;	/* (n) 'global', 'local', 'field', 'method' */
    const char* what;	/* (S) 'Lua', 'C', 'main', 'tail' */
    const char* source;	/* (S) */
    size_t srclen;	/* (S) */
    int currentline;	/* (l) */
    int linedefined;	/* (S) */
    int lastlinedefined;	/* (S) */
    unsigned char nups;	/* (u) number of upvalues */
    unsigned char nparams;/* (u) number of parameters */
    char isvararg;        /* (u) */
    char istailcall;	/* (t) */
    unsigned short ftransfer;   /* (r) index of first value transferred */
    unsigned short ntransfer;   /* (r) number of transferred values */
    char short_src[NC_LUA_IDSIZE]; /* (S) */
    /* private part */
    struct CallInfo* i_ci;  /* active function */
};
/* end_of_file */
#endif	// NC_LUACONFIG_H //