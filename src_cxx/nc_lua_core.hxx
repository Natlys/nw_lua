#ifndef NC_LUA_CORE_HXX
#    define NC_LUA_CORE_HXX
/* config */
/* building */
#   if (defined NC_BUILD)
#       undef NC_BUILD
#   endif   /* NC_BUILD */
#   define NC_BUILD NC_BUILD_EXE
// #   define NC_BUILD NC_BUILD_LIB
/* include */
#   include "nc_lua_pch.hxx"
/* defines */
/** linkage  **/
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
/** coding **/
#   define NC_LUA_MRET (-1) /* option for multiple returns in 'lua_pcall' and 'lua_call' */
#   define NC_LUA_SIGN "\x1blua" /* signature for compiled code */
/** directories and files **/
#	define NC_LUA_VDIR NC_LUA_VER_MAJOR "." NC_LUA_VER_MINOR /* */
#   if (NC_WAPI & NC_WAPI_WIN)
#	    define NC_LUA_PATH_FSEP ";" /* character that separates templates in a path; */
#	    define NC_LUA_PATH_MARK "?" /* the string that marks the substitution points in a template; */
#	    define NC_LUA_EXEC_FDIR "!" /* in windows gets replaced by the executable's directory; */
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
/* NC_LUA_LPATH */
#	    define NC_LUA_CPATH  /*defaul path for "require" cxx libraries*/     \
		    NC_LUA_CDIR NC_STR_FDIR ".dll" NC_LUA_PATH_FSEP                  \
		    NC_LUA_CDIR ".." NC_STR_FDIR "lib" NC_STR_FDIR "lua" NC_STR_FDIR \
            NC_LUA_VDIR NC_STR_FDIR "?.dll" NC_LUA_PATH_FSEP                 \
		    NC_LUA_CDIR "loadall.dll" NC_LUA_PATH_FSEP "." NC_STR_FDIR NC_LUA_PATH_MARK ".dll" \
/* NC_LUA_CPATH */
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
/* NC_LUA_LPATH */
#       define NC_LUA_CPATH                                                                  \
            NC_LUA_CDIR NC_LUA_PATH_MARK ".so" NC_LUA_PATH_FSEP                              \
            NC_LUA_CDIR "loadall.so" NC_LUA_PATH_FSEP "." NC_STR_FDIR NC_LUA_PATH_MARK ".so" \
/* NC_LUA_CPATH */
#   endif   /* NC_WAPI_WIN */
/** all functions that are not to be exported to outside modules  **/
#   if ((NC_CAPI & NC_CAPI_GNU) && ((__GNUC__*100 + __GNUC_MINOR__) >= 302) && defined(__ELF__)) 
#	    define NC_LUA_DECL_FUNC __attribute__((visibility("internal"))) extern
#   else
#	    define NC_LUA_DECL_FUNC (extern)
#   endif   /* NC_CAPI_GNU */
#   define NC_LUA_DDEC(dec) (NC_LUAI_FUNC (dec)) /* extern const variables */
#   define NC_LUA_DDEF	    (NC_VOID) /* extern const variables */
/* end_of_file */
#endif  /* NC_LUA_CORE_HXX */