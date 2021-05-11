#ifndef NC_LUA_CONFIG_H
#	define NC_LUA_CONFIG_H
// standard c libraries //
#	include <limits.h>
#	include <stddef.h>
// general configuration file for lua
// some definitions here can be changed externally, through the compiler (e.g., with '-D' options);
// those are protected by '#if !defined' guards;
// however, several other definitions should be changed directly here
// either because they affect the lua api or because they are seldom changed;
// (by making the changes here, you ensure that all software connected to lua,
// such as C libraries, will be compiled with the same configuration)
// search for "@@" to find all configurable definitions;
//
// system configuration: macros to adapt (if needed) lua to some
// particular platform, for instance restricting it to C89.
//
// @@ NC_LUA_USE_C89 controls the use of non-ISO-C89 features;
// define it if you want lua to avoid the use of a few C99 features or windows-specific features on windows;
// #define NC_LUA_USE_C89
// by default, lua on windows use (some) specific windows features;
#if !defined(NC_LUA_USE_C89) && defined(_WIN32) && !defined(_WIN32_WCE)
#	define NC_LUA_USE_WINDOWS // enable goodies for regular windows;
#endif
// windows platform config
#if defined(NC_LUA_USE_WINDOWS)
#	define NC_LUA_DL_DLL	// enable support for dynamic library linking
#	define NC_LUA_USE_C89	// broadly, windows is C89
#endif
// linux platform config
#if defined(NC_LUA_USE_LINUX)
#	define NC_LUA_USE_POSIX
#	define NC_LUA_USE_DLOPEN		// needs an extra library: -ldl;
#endif
// macosx platform config
#if defined(NC_LUA_USE_MACOSX)
#	define NC_LUA_USE_POSIX
#	define NC_LUA_USE_DLOPEN		// MacOS does not need -ldl;
#endif
// @@ NC_LUAI_IS32INT is true if 'int' has (at least) 32 bits.
#define NC_LUAI_IS32INT	((UINT_MAX >> 30) >= 3)
// configuration for number types.
// @@ NC_LUA_32BITS enables Lua with 32-bit integers and 32-bit floats.
 #define NC_LUA_32BITS
// @@ NC_LUA_C89_NUMBERS ensures that lua uses the largest types available for
// C89 ('long' and 'double'); windows always has '__int64', so it does
// not need to use this case.
#if defined(NC_LUA_USE_C89) && !defined(NC_LUA_USE_WINDOWS)
#	define NC_LUA_C89_NUMBERS
#endif
// @@ NC_LUA_INT_TYPE defines the type for lua integers;
// @@ NC_LUA_FLOAT_TYPE defines the type for lua floats;
// lua should work fine with any mix of these options supported by your C compiler;
// the usual configurations are:
// default: 64-bit integers and 'double';
// for restricted platforms: 32-bit integers and 'float';
// for C compilers not compliant with C99: 'long'/'double' (may not have support for 'long long');
//
// predefined options for NC_LUA_INT_TYPE
#define NC_LUA_INT_INT		1
#define NC_LUA_INT_LONG		2
#define NC_LUA_INT_LONGLONG	3
// predefined options for NC_LUA_FLOAT_TYPE
#define NC_LUA_FLOAT_FLOAT		1
#define NC_LUA_FLOAT_DOUBLE		2
#define NC_LUA_FLOAT_LONGDOUBLE	3
// int and float
#if defined(NC_LUA_32BITS) // 32-bit integers and 'float'
#	if NC_LUAI_IS32INT  // use 'int' if big enough
#		define NC_LUA_INT_TYPE	NC_LUA_INT_INT
#	else  // otherwise use long
#		define NC_LUA_INT_TYPE	NC_LUA_INT_LONG
#	endif
#		define NC_LUA_FLOAT_TYPE	NC_LUA_FLOAT_FLOAT
#elif defined(NC_LUA_C89_NUMBERS)
// largest types available for C89 ('long' and 'double')
#	define NC_LUA_INT_TYPE	NC_LUA_INT_LONG
#	define NC_LUA_FLOAT_TYPE	NC_LUA_FLOAT_DOUBLE
#endif
// default configuration for 64-bit Lua ('long long' and 'double')
#if !defined(NC_LUA_INT_TYPE)
#	define NC_LUA_INT_TYPE	NC_LUA_INT_LONGLONG
#endif
#if !defined(NC_LUA_FLOAT_TYPE)
#	define NC_LUA_FLOAT_TYPE	NC_LUA_FLOAT_DOUBLE
#endif

// --==<configuration_for_paths>==--
// NC_LUAPATH_SEP is the character that separates templates in a path;
// NC_LUAPATH_MARK is the string that marks the substitution points in a template;
// NC_LUAEXEC_DIR in a Windows path is replaced by the executable's directory;
#define NC_LUA_PATH_SEP            ";"
#define NC_LUA_PATH_MARK           "?"
#define NC_LUA_EXEC_DIR            "!"
// @@ NC_LUA_PATH_DEFAULT is the default path that lua uses to look for lua libraries;
// @@ NC_LUA_CPATH_DEFAULT is the default path that lua uses to look for C libraries.
// CHANGE them if your machine has a non-conventional directory
// hierarchy or if you want to install your libraries in
// non-conventional directories.
#define NC_LUA_VDIR	NC_LUA_VERSION_MAJOR "." NC_LUA_VERSION_MINOR
#if defined(_WIN32)
// in windows, any exclamation mark ('!') in the path is replaced by the
// path of the directory of the executable file of the current process.
#	define NC_LUA_LDIR	"!\\lua\\"
#	define NC_LUA_CDIR	"!\\"
#	define NC_LUA_SHRDIR	"!\\..\\share\\lua\\" NC_LUA_VDIR "\\"
#	if !defined(NC_LUA_PATH_DEFAULT)
#	define NC_LUA_PATH_DEFAULT  \
		NC_LUA_LDIR"?.lua;"  NC_LUA_LDIR"?\\init.lua;" \
		NC_LUA_CDIR"?.lua;"  NC_LUA_CDIR"?\\init.lua;" \
		NC_LUA_SHRDIR"?.lua;" NC_LUA_SHRDIR"?\\init.lua;" \
		".\\?.lua;" ".\\?\\init.lua"
#	endif
#	if !defined(NC_LUA_CPATH_DEFAULT)
#	define NC_LUA_CPATH_DEFAULT \
		NC_LUA_CDIR"?.dll;" \
		NC_LUA_CDIR"..\\lib\\lua\\" NC_LUA_VDIR "\\?.dll;" \
		NC_LUA_CDIR"loadall.dll;" ".\\?.dll"
#	endif
#else
#	define NC_LUA_ROOT	"/usr/local/"
#	define NC_LUA_LDIR	NC_LUA_ROOT "share/lua/" NC_LUA_VDIR "/"
#	define NC_LUA_CDIR	NC_LUA_ROOT "lib/lua/" NC_LUA_VDIR "/"
#	if !defined(NC_LUA_PATH_DEFAULT)
#	define NC_LUA_PATH_DEFAULT  \
		NC_LUA_LDIR"?.lua;"  NC_LUA_LDIR"?/init.lua;" \
		NC_LUA_CDIR"?.lua;"  NC_LUA_CDIR"?/init.lua;" \
		"./?.lua;" "./?/init.lua"
#	endif
#	if !defined(NC_LUA_CPATH_DEFAULT)
#	define NC_LUA_CPATH_DEFAULT \
		NC_LUA_CDIR"?.so;" NC_LUA_CDIR"loadall.so;" "./?.so"
#	endif
#endif
// @@ NC_LUA_DIRSEP is the directory separator (for submodules);
// change it if your machine does not use "/" as the directory separator and is not windows;
// (on windows lua automatically uses "\");
#if !defined(NC_LUA_DIRSEP)
#	if defined(_WIN32)
#		define NC_LUA_DIRSEP	"\\"
#	else
#		define NC_LUA_DIRSEP	"/"
#	endif
#endif
// marks for exported symbols in the C code;
// @@ NC_LUA_API is a mark for all core api functions;
// @@ NC_LUA_API is a mark for all auxiliary library functions;
// @@ NC_LUAMOD_API is a mark for all standard library opening functions;
// change them if you need to define those functions in some special way;
// for instance, if you want to create one windows dll with the core and
// the libraries, you may want to use the following definition;
// (define NC_LUA_BUILD_AS_DLL to get it);
#if defined(NC_LUA_BUILD_DLL)
#	if defined(NC_LUA_CORE) || defined(NC_LUA_LIB)
#		define NC_LUA_API __declspec(dlua_lexport)
#	else
	#	define NC_LUA_API __declspec(dllimport)
#	endif
#else
#	define NC_LUALIB_API		extern
#endif
#define NC_LUA_API		NC_LUALIB_API
#define NC_LUAMOD_API	NC_LUA_API
// @@ NC_LUAI_FUNC is a mark for all extern functions that are not to be exported to outside modules;
// @@ NC_LUAI_DDEF and NC_LUAI_DDEC are marks for all extern (const) variables,
// none of which to be exported to outside modules (NC_LUAI_DDEF for
// definitions and NC_LUAI_DDEC for declarations);
// CHANGE them if you need to mark them in some special way. Elf/gcc
// (versions 3.2 and later) mark them as "hidden" to optimize access
// when Lua is compiled as a shared library. Not all elf targets support
// this attribute. Unfortunately, gcc does not offer a way to check
// whether the target offers that support, and those without support
// give a warning about it. To avoid these warnings, change to the
// default definition.
#if defined(__GNUC__) && ((__GNUC__*100 + __GNUC_MINOR__) >= 302) && defined(__ELF__) 
#	define NC_LUAI_FUNC	__attribute__((visibility("internal"))) extern
#else 
#	define NC_LUAI_FUNC	extern
#endif

#define NC_LUAI_DDEC(dec)	NC_LUAI_FUNC dec
#define NC_LUAI_DDEF	 // empty 
// --==</configuration_for_paths>==--

// --==<compatibility_with_previous_versions>==---
// @@ NC_LUA_COMPAT_5_3 controls other macros for compatibility with lua 5.3;
// you can define it to get all options, or change specific options to fit your specific needs;
#if defined(NC_LUA_COMPAT_5_3)
// @@ NC_LUA_COMPAT_MATHLIB controls the presence of several deprecated
// functions in the mathematical library.
// (These functions were already officially removed in 5.3;
// nevertheless they are still available here.)
#	define NC_LUA_COMPAT_MATHLIB
// @@ NC_LUA_COMPAT_APIINTCASTS controls the presence of macros for
// manipulating other integer types (lua_pushunsigned, lua_tounsigned,
// luaL_checkint, luaL_checklong, etc.)
// (These macros were also officially removed in 5.3, but they are still
// available here.)
#	define NC_LUA_COMPAT_APIINTCASTS
// @@ NC_LUA_COMPAT_LT_LE controls the emulation of the '__le' metamethod
// using '__lt'.
#	define NC_LUA_COMPAT_LT_LE
// @@ the following macros supply trivial compatibility for some changes in the api;
// the macros themselves document how to change your code to avoid using them;
// (once more, these macros were officially removed in 5.3, but they are still available here);
#	define lua_strlen(L,i)		lua_rawlen(L, (i))
#	define lua_objlen(L,i)		lua_rawlen(L, (i))
#	define lua_equal(L,idx1,idx2)		lua_compare(L,(idx1),(idx2),NC_LUA_OPEQ)
#	define lua_lessthan(L,idx1,idx2)	lua_compare(L,(idx1),(idx2),NC_LUA_OPLT)
#endif
// --==</compatibility_with_previous_versions>==---

// --==<configuration_for_numbers>==--
// change these definitions if no predefined NC_LUA_FLOAT_* / NC_LUA_INT_*
// satisfy your needs;
// @@ NC_LUA_NUMBER is the floating-point type used by lua;
// @@ NC_LUAI_UACNUMBER is the result of a 'default argument promotion'
// @@ over a floating number;
// @@ l_floatatt(x) corrects float attribute 'x' to the proper float type
// by prefixing it with one of FLT/DBL/LDBL;
// @@ NC_LUA_NUMBER_FRMLEN is the length modifier for writing floats;
// @@ NC_LUA_NUMBER_FMT is the format for writing floats;
// @@ lua_number2str converts a float to a string;
// @@ l_mathop allows the addition of an 'l' or 'f' to all math operations;
// @@ l_floor takes the floor of a float;
// @@ lua_str2number converts a decimal numeral to a number;
// the following definitions are good for most cases here 
#define l_floor(x)		(l_mathop(floor)(x))
#define lua_number2str(s,sz,n) l_sprintf((s), sz, NC_LUA_NUMBER_FMT, (NC_LUAI_UACNUMBER)(n))
// @@ lua_numbertointeger converts a float number with an integral value
// to an integer, or returns 0 if float is not within the range of
// a lua_Integer.  (The range comparisons are tricky because of
// rounding. The tests here assume a two-complement representation,
// where MININTEGER always has an exact representation as a float;
// MAXINTEGER may not have one, and therefore its conversion to float
// may have an ill-defined value);
#define lua_numbertointeger(n,p) \
  ((n) >= (NC_LUA_NUMBER)(NC_LUA_MININTEGER) && \
   (n) < -(NC_LUA_NUMBER)(NC_LUA_MININTEGER) && \
      (*(p) = (NC_LUA_INTEGER)(n), 1))
// now the variable definitions
#if NC_LUA_FLOAT_TYPE == NC_LUA_FLOAT_FLOAT
#	define NC_LUA_NUMBER	float
#	define l_floatatt(n)		(FLT_##n)
#	define NC_LUAI_UACNUMBER	double
#	define NC_LUA_NUMBER_FRMLEN	""
#	define NC_LUA_NUMBER_FMT		"%.7g"
#	define l_mathop(op)		op##f
#	define lua_str2number(s,p)	strtof((s), (p))
#elif NC_LUA_FLOAT_TYPE == NC_LUA_FLOAT_LONGDOUBLE
#	define NC_LUA_NUMBER	long double
#	define l_floatatt(n)		(LDBL_##n)
#	define NC_LUAI_UACNUMBER	long double
#	define NC_LUA_NUMBER_FRMLEN	"L"
#	define NC_LUA_NUMBER_FMT		"%.19Lg"
#	define l_mathop(op)		op##l
#	define lua_str2number(s,p)	strtold((s), (p))
#elif NC_LUA_FLOAT_TYPE == NC_LUA_FLOAT_DOUBLE
#	define NC_LUA_NUMBER		double
#	define l_floatatt(n)	(DBL_##n)
#	define NC_LUAI_UACNUMBER	double
#	define NC_LUA_NUMBER_FRMLEN	""
#	define NC_LUA_NUMBER_FMT		"%.14g"
#	define l_mathop(op)		op
#	define lua_str2number(s,p)	strtod((s), (p))
#else
#	error "numeric float type not defined"
#endif
// @@ NC_LUA_INTEGER is the integer type used by lua;
// @@ NC_LUA_UNSIGNED is the unsigned version of NC_LUA_INTEGER;
// @@ NC_LUA_UINT is the result of a "default argument promotion" over a NC_LUA_INTEGER;
// @@ NC_LUA_INTEGER_FRMLEN is the length modifier for reading/writing integers;
// @@ NC_LUA_INTEGER_FMT is the format for writing integers;
// @@ NC_LUA_MAXINTEGER is the maximum value for a NC_LUA_INTEGER;
// @@ NC_LUA_MININTEGER is the minimum value for a NC_LUA_INTEGER;
// @@ NC_LUA_MAXUNSIGNED is the maximum value for a NC_LUA_UNSIGNED;
// @@ NC_LUA_UNSIGNEDBITS is the number of bits in a NC_LUA_UNSIGNED;
// @@ lua_integer2str converts an integer to a string;
// the following definitions are good for most cases here
#define NC_LUA_INTEGER_FMT		"%" NC_LUA_INTEGER_FRMLEN "d"
#define NC_LUA_UINT				unsigned NC_LUA_INTEGER
#define lua_integer2str(s,sz,n) l_sprintf((s), sz, NC_LUA_INTEGER_FMT, (NC_LUA_UINT)(n))
// use NC_LUA_UINT here to avoid problems with promotions
// (which can turn a comparison between unsigneds into a signed comparison)
#define NC_LUA_UNSIGNED		unsigned
#define NC_LUA_UNSIGNEDBITS	(sizeof(NC_LUA_UNSIGNED) * CHAR_BIT)
// now the variable definitions
#if NC_LUA_INT_TYPE == NC_LUA_INT_INT
#	define NC_LUA_INTEGER			int
#	define NC_LUA_INTEGER_FRMLEN	""
#	define NC_LUA_MAXINTEGER		INT_MAX
#	define NC_LUA_MININTEGER		INT_MIN
#	define NC_LUA_MAXUNSIGNED		UINT_MAX
#elif NC_LUA_INT_TYPE == NC_LUA_INT_LONG
#	define NC_LUA_INTEGER		long
#	define NC_LUA_INTEGER_FRMLEN	"l"
#	define NC_LUA_MAXINTEGER		LONG_MAX
#	define NC_LUA_MININTEGER		LONG_MIN
#	define NC_LUA_MAXUNSIGNED		ULONG_MAX
#elif NC_LUA_INT_TYPE == NC_LUA_INT_LONGLONG // use presence of macro LLONG_MAX as proxy for C99 compliance;
#	if defined(LLONG_MAX)	// use iso C99 stuff 
#		define NC_LUA_INTEGER			long long
#		define NC_LUA_INTEGER_FRMLEN	"ll"
#		define NC_LUA_MAXINTEGER		LLONG_MAX
#		define NC_LUA_MININTEGER		LLONG_MIN
#		define NC_LUA_MAXUNSIGNED		ULLONG_MAX
#	elif defined(NC_LUA_USE_WINDOWS) 
 // in windows, can use specific windows types;
#		define NC_LUA_INTEGER		__int64
#		define NC_LUA_INTEGER_FRMLEN	"I64"
#		define NC_LUA_MAXINTEGER		_I64_MAX
#		define NC_LUA_MININTEGER		_I64_MIN
#		define NC_LUA_MAXUNSIGNED		_UI64_MAX
#	else
#		error "Compiler does not support 'long long'. Use option '-DNC_LUA_32BITS' \
	or '-DNC_LUA_C89_NUMBERS' (see file 'lua_config.h' for details)"
#	endif
#else
#	error "numeric integer type not defined"
#endif
// dependencies with C99 and other C details
// @@ l_sprintf is equivalent to 'snprintf' or 'sprintf' in C89.
// (all uses in lua have only one format item);
#if !defined(NC_LUA_USE_C89)
#	define l_sprintf(s,sz,f,i)	snprintf(s,sz,f,i)
#else
#	define l_sprintf(s,sz,f,i)	((void)(sz), sprintf(s,f,i))
#endif
// @@ lua_strx2number converts a hexadecimal numeral to a number;
// in C99, 'strtod' does that conversion;
// otherwise, you can leave 'lua_strx2number' undefined and lua will provide its own implementation;
#if !defined(NC_LUA_USE_C89)
#	define lua_strx2number(s,p)		lua_str2number(s,p)
#endif
// @@ lua_pointer2str converts a pointer to a readable string in a non-specified way;
#define lua_pointer2str(buff,sz,p)	l_sprintf(buff,sz,"%p",p)
// @@ lua_number2strx converts a float to a hexadecimal numeral;
// in C99, 'sprintf' (with format specifiers '%a'/'%A') does that;
// otherwise, you can leave 'lua_number2strx' undefined and lua will provide its own implementation;
#if !defined(NC_LUA_USE_C89)
#	define lua_number2strx(L,b,sz,f,n)	((void)L, l_sprintf(b,sz,f,(NC_LUAI_UACNUMBER)(n)))
#endif
// 'strtof' and 'opf' variants for math functions are not valid in C89;
// otherwise, the macro 'HUGE_VALF' is a good proxy for testing the availability of these variants;
// ('math.h' is already included in all files that use these macros);
#if defined(NC_LUA_USE_C89) || (defined(HUGE_VAL) && !defined(HUGE_VALF))
#	undef l_mathop   // variants not available 
#	undef lua_str2number
#	define l_mathop(op)		(lua_Number)op   // no variant 
#	define lua_str2number(s,p)	((lua_Number)strtod((s), (p)))
#endif
// @@ NC_LUA_KCONTEXT is the type of the context ('ctx') for continuation functions;
// it must be a numerical type;
// lua will use 'intptr_t' if available, otherwise it will use 'ptrdiff_t'
// (the nearest thing to 'intptr_t' in C89);
#define NC_LUA_KCONTEXT	ptrdiff_t
#if !defined(NC_LUA_USE_C89) && defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
#	include <stdint.h>
#	if defined(INTPTR_MAX)   // even in C99 this type is optional 
#		undef NC_LUA_KCONTEXT
#		define NC_LUA_KCONTEXT	intptr_t
#	endif
#endif
// @@ lua_getlocaledecpoint gets the locale "radix character" (decimal point);
// change that if you do not want to use C locales;
// (code using this macro must include the header 'locale.h'.)
#if !defined(lua_getlocaledecpoint)
#	define lua_getlocaledecpoint()		(localeconv()->decimal_point[0])
#endif
// --==</configuration_for_numbers>==--

// --==<language_variations>==--
// @@ NC_LUA_NOCVTN2S/NC_LUA_NOCVTS2N control how lua performs some convertions;
// define NC_LUA_NOCVTN2S to turn off automatic convertion from numbers to strings;
// #define NC_LUA_NOCVTN2S
// #define NC_LUA_NOCVTS2N
// @@ NC_LUA_USE_APICHECK turns on several consistency checks on the C api;
// define it as a help when debugging C code;
#if defined(NC_LUA_USE_APICHECK)
#	include <assert.h>
#	define luai_apicheck(l,e)	assert(e)
#endif
// macros that affect the API and must be stable
// (that is, must be the same when you compile lua and when you compile code that links to lua);
// @@ NC_LUAI_MAXSTACK limits the size of the Lua stack.
// CHANGE it if you need a different limit. This limit is arbitrary;
// its only purpose is to stop Lua from consuming unlimited stack
// space (and to reserve some numbers for pseudo-indices).
// (It must fit into max(size_t)/32.)
#if NC_LUAI_IS32INT
#	define NC_LUAI_MAXSTACK		1000000
#else
#	define NC_LUAI_MAXSTACK		15000
#endif
// @@ NC_LUA_EXTRASPACE defines the size of a raw memory area
// associated with a lua state with very fast access;
// change it if you need a different size;
#define NC_LUA_EXTRASPACE		(sizeof(void *))
// @@ NC_LUA_IDSIZE gives the maximum size for the description of the source of a function in debug information;
// change it if you want a different size.
#define NC_LUA_IDSIZE	60
// @@ NC_LUAL_BUFFERSIZE is the buffer size used by the lauxlib buffer system;
#define NC_LUAL_BUFFERSIZE   ((int)(16 * sizeof(void*) * sizeof(lua_Number)))
// @@ NC_LUAI_MAXALIGN defines fields that, when used in a union, ensure
// maximum alignment for the other items in that union;
#define NC_LUAI_MAXALIGN  lua_Number n; double u; void *s; lua_Integer i; long l
// --==</language_variations>==--

// --==<local_configuration>==--
// you can use this space to add your redefinitions
// without modifying the main part of the file.
// --==</local_configuration>==--

// information //
#    define NC_LUA_VERSION_MAJOR	"5"
#    define NC_LUA_VERSION_MINOR	"4"
#    define NC_LUA_VERSION_RELEASE	"2"
#    define NC_LUA_VERSION_NUM			    504
#    define NC_LUA_VERSION_RELEASE_NUM		(NC_LUA_VERSION_NUM * 100 + 0)
#    define NC_LUA_VERSION	"Lua " NC_LUA_VERSION_MAJOR "." NC_LUA_VERSION_MINOR
#    define NC_LUA_RELEASE	NC_LUA_VERSION "." NC_LUA_VERSION_RELEASE
#    define NC_LUA_COPYRIGHT	NC_LUA_RELEASE "  Copyright (C) 1994-2020 Lua.org, PUC-Rio"
#    define NC_LUA_AUTHORS	"R. Ierusalimschy, L. H. de Figueiredo, W. Celes"
// signatures for compiled code //
#    define NC_LUA_SIGNATURE	"\x1bLua"
// option for multiple returns in 'lua_pcall' and 'lua_call'
#    define NC_LUA_MULTRET	(-1)
// pseudo-indices //
// (-NC_LUAI_MAXSTACK is the minimum valid index;
// we keep some free empty space after that to help overflow detection)
#    define NC_LUA_REGISTRYINDEX	(-NC_LUAI_MAXSTACK - 1000)
#    define lua_upvalueindex(i)	(NC_LUA_REGISTRYINDEX - (i))
// thread status //
#    define NC_LUA_OK		0
#    define NC_LUA_YIELD	1
#    define NC_LUA_ERRRUN	2
#    define NC_LUA_ERRSYNTAX	3
#    define NC_LUA_ERRMEM	4
#    define NC_LUA_ERRERR	5
// basic types //
#    define NC_LUA_TNONE		(-1)
#    define NC_LUA_TNIL           0
#    define NC_LUA_TBOOLEAN       1
#    define NC_LUA_TLIGHTUSERDATA 2
#    define NC_LUA_TNUMBER        3
#    define NC_LUA_TSTRING        4
#    define NC_LUA_TTABLE         5
#    define NC_LUA_TFUNCTION      6
#    define NC_LUA_TUSERDATA      7
#    define NC_LUA_TTHREAD        8
#    define NC_LUA_NUMTYPES   9
// minimum Lua stack available to a c function //
#    define NC_LUA_MINSTACK 20
// predefined values in the registry //
#    define NC_LUA_RIDX_MAINTHREAD 1
#    define NC_LUA_RIDX_GLOBALS    2
#    define NC_LUA_RIDX_LAST       NC_LUA_RIDX_GLOBALS
// main lua virtual machiene //
typedef struct lua_State lua_State;
// type of numbers in lua //
typedef NC_LUA_NUMBER lua_Number;
// type for integer functions //
typedef NC_LUA_INTEGER lua_Integer;
// unsigned integer type //
typedef NC_LUA_UNSIGNED lua_Unsigned;
// type for continuation-function contexts //
typedef NC_LUA_KCONTEXT lua_KContext;
// type for c functions registered with lua //
typedef int (*lua_CFunction) (lua_State *L);
// type for continuation functions //
typedef int (*lua_KFunction) (lua_State *L, int status, lua_KContext ctx);
// type for functions that read/write blocks when loading/dumping Lua chunks //
typedef const char * (*lua_Reader) (lua_State *L, void *ud, size_t *sz);
typedef int (*lua_Writer) (lua_State *L, const void *p, size_t sz, void *ud);
// type for memory-allocation functions //
typedef void * (*lua_Alloc) (void *ud, void *ptr, size_t osize, size_t nsize);
// type for warning functions //
typedef void (*lua_WarnFunction) (void *ud, const char *msg, int tocont);
// generic extra include file //
#    if defined(NC_LUA_USER_H)
#        include NC_LUA_USER_H
#    endif
// rcs ident string //
extern const char lua_ident[];
// state manipulation //
NC_LUA_API lua_State *(lua_newstate) (lua_Alloc f, void *ud);
NC_LUA_API void       (lua_close) (lua_State *L);
NC_LUA_API lua_State *(lua_newthread) (lua_State *L);
NC_LUA_API int        (lua_resetthread) (lua_State *L);
// error callback function //
NC_LUA_API lua_CFunction (lua_atpanic) (lua_State *L, lua_CFunction panicf);
// version getter //
NC_LUA_API lua_Number (lua_version) (lua_State *L);
// basic stack manipulation
NC_LUA_API int   (lua_absindex) (lua_State *L, int idx);
NC_LUA_API int   (lua_gettop) (lua_State *L);
NC_LUA_API void  (lua_settop) (lua_State *L, int idx);
NC_LUA_API void  (lua_pushvalue) (lua_State *L, int idx);
NC_LUA_API void  (lua_rotate) (lua_State *L, int idx, int n);
NC_LUA_API void  (lua_copy) (lua_State *L, int fromidx, int toidx);
NC_LUA_API int   (lua_checkstack) (lua_State *L, int n);
NC_LUA_API void  (lua_xmove) (lua_State *from, lua_State *to, int n);
// getters (stack -> c) //
NC_LUA_API int             (lua_isnumber) (lua_State *L, int idx);
NC_LUA_API int             (lua_isstring) (lua_State *L, int idx);
NC_LUA_API int             (lua_iscfunction) (lua_State *L, int idx);
NC_LUA_API int             (lua_isinteger) (lua_State *L, int idx);
NC_LUA_API int             (lua_isuserdata) (lua_State *L, int idx);
NC_LUA_API int             (lua_type) (lua_State *L, int idx);
NC_LUA_API const char     *(lua_typename) (lua_State *L, int tp);
NC_LUA_API lua_Number      (lua_tonumberx) (lua_State *L, int idx, int *isnum);
NC_LUA_API lua_Integer     (lua_tointegerx) (lua_State *L, int idx, int *isnum);
NC_LUA_API int             (lua_toboolean) (lua_State *L, int idx);
NC_LUA_API const char     *(lua_tolstring) (lua_State *L, int idx, size_t *len);
NC_LUA_API lua_Unsigned    (lua_rawlen) (lua_State *L, int idx);
NC_LUA_API lua_CFunction   (lua_tocfunction) (lua_State *L, int idx);
NC_LUA_API void	       *(lua_touserdata) (lua_State *L, int idx);
NC_LUA_API lua_State      *(lua_tothread) (lua_State *L, int idx);
NC_LUA_API const void     *(lua_topointer) (lua_State *L, int idx);
// comparison and arithmetic functions //
#    define NC_LUA_OPADD    0
#    define NC_LUA_OPSUB    1
#    define NC_LUA_OPMUL    2
#    define NC_LUA_OPMOD    3
#    define NC_LUA_OPPOW    4
#    define NC_LUA_OPDIV    5
#    define NC_LUA_OPIDIV   6
#    define NC_LUA_OPBAND   7
#    define NC_LUA_OPBOR    8
#    define NC_LUA_OPBXOR   9
#    define NC_LUA_OPSHL    10
#    define NC_LUA_OPSHR    11
#    define NC_LUA_OPUNM    12
#    define NC_LUA_OPBNOT   13
// function view //
NC_LUA_API void  (lua_arith) (lua_State *L, int op);

#    define NC_LUA_OPEQ 0
#    define NC_LUA_OPLT 1
#    define NC_LUA_OPLE 2

NC_LUA_API int   (lua_rawequal) (lua_State *L, int idx1, int idx2);
NC_LUA_API int   (lua_compare) (lua_State *L, int idx1, int idx2, int op);

// setters (c -> stack) //
NC_LUA_API void        (lua_pushnil) (lua_State *L);
NC_LUA_API void        (lua_pushnumber) (lua_State *L, lua_Number n);
NC_LUA_API void        (lua_pushinteger) (lua_State *L, lua_Integer n);
NC_LUA_API const char *(lua_pushlstring) (lua_State *L, const char *s, size_t len);
NC_LUA_API const char *(lua_pushstring) (lua_State *L, const char *s);
NC_LUA_API const char *(lua_pushvfstring) (lua_State *L, const char *fmt, va_list argp);
NC_LUA_API const char *(lua_pushfstring) (lua_State *L, const char *fmt, ...);
NC_LUA_API void  (lua_pushcclosure) (lua_State *L, lua_CFunction fn, int n);
NC_LUA_API void  (lua_pushboolean) (lua_State *L, int b);
NC_LUA_API void  (lua_pushlightuserdata) (lua_State *L, void *p);
NC_LUA_API int   (lua_pushthread) (lua_State *L);
// getters (lua -> stack) //
NC_LUA_API int (lua_getglobal) (lua_State *L, const char *name);
NC_LUA_API int (lua_gettable) (lua_State *L, int idx);
NC_LUA_API int (lua_getfield) (lua_State *L, int idx, const char *k);
NC_LUA_API int (lua_geti) (lua_State *L, int idx, lua_Integer n);
NC_LUA_API int (lua_rawget) (lua_State *L, int idx);
NC_LUA_API int (lua_rawgeti) (lua_State *L, int idx, lua_Integer n);
NC_LUA_API int (lua_rawgetp) (lua_State *L, int idx, const void *p);
NC_LUA_API void  (lua_createtable) (lua_State *L, int narr, int nrec);
NC_LUA_API void *(lua_newuserdatauv) (lua_State *L, size_t sz, int nuvalue);
NC_LUA_API int   (lua_getmetatable) (lua_State *L, int objindex);
NC_LUA_API int  (lua_getiuservalue) (lua_State *L, int idx, int n);
// setters (stack -> Lua) //
NC_LUA_API void  (lua_setglobal) (lua_State *L, const char *name);
NC_LUA_API void  (lua_settable) (lua_State *L, int idx);
NC_LUA_API void  (lua_setfield) (lua_State *L, int idx, const char *k);
NC_LUA_API void  (lua_seti) (lua_State *L, int idx, lua_Integer n);
NC_LUA_API void  (lua_rawset) (lua_State *L, int idx);
NC_LUA_API void  (lua_rawseti) (lua_State *L, int idx, lua_Integer n);
NC_LUA_API void  (lua_rawsetp) (lua_State *L, int idx, const void *p);
NC_LUA_API int   (lua_setmetatable) (lua_State *L, int objindex);
NC_LUA_API int   (lua_setiuservalue) (lua_State *L, int idx, int n);
// 'load' and 'call' functions (load and run lua code) //
NC_LUA_API void  (lua_callk) (lua_State *L, int nargs, int nresults, lua_KContext ctx, lua_KFunction k);
#define lua_call(L,n,r)		lua_callk(L, (n), (r), 0, NULL)
NC_LUA_API int   (lua_pcallk) (lua_State *L, int nargs, int nresults, int errfunc, lua_KContext ctx, lua_KFunction k);
#define lua_pcall(L,n,r,f)	lua_pcallk(L, (n), (r), (f), 0, NULL)
NC_LUA_API int   (lua_load) (lua_State *L, lua_Reader reader, void *dt, const char *chunkname, const char *mode);
NC_LUA_API int (lua_dump) (lua_State *L, lua_Writer writer, void *data, int strip);
// coroutine functions //
NC_LUA_API int  (lua_yieldk)     (lua_State *L, int nresults, lua_KContext ctx, lua_KFunction k);
NC_LUA_API int  (lua_resume)     (lua_State *L, lua_State *from, int narg, int *nres);
NC_LUA_API int  (lua_status)     (lua_State *L);
NC_LUA_API int (lua_isyieldable) (lua_State *L);
#define lua_yield(L,n)		lua_yieldk(L, (n), 0, NULL)
// warning-related functions //
NC_LUA_API void (lua_setwarnf) (lua_State *L, lua_WarnFunction f, void *ud);
NC_LUA_API void (lua_warning)  (lua_State *L, const char *msg, int tocont);
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
NC_LUA_API int (lua_gc) (lua_State *L, int what, ...);
// miscellaneous functions //
NC_LUA_API int   (lua_error) (lua_State *L);
NC_LUA_API int   (lua_next) (lua_State *L, int idx);
NC_LUA_API void  (lua_concat) (lua_State *L, int n);
NC_LUA_API void  (lua_len)    (lua_State *L, int idx);
NC_LUA_API size_t   (lstringtonumber) (lua_State *L, const char *s);
NC_LUA_API lua_Alloc (lua_getallocf) (lua_State *L, void **ud);
NC_LUA_API void      (lua_setallocf) (lua_State *L, lua_Alloc f, void *ud);
NC_LUA_API void  (lua_toclose) (lua_State *L, int idx);
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
typedef void (*lua_Hook) (lua_State *L, lua_Debug *ar);

NC_LUA_API int (lua_getstack) (lua_State *L, int level, lua_Debug *ar);
NC_LUA_API int (lua_getinfo) (lua_State *L, const char *what, lua_Debug *ar);
NC_LUA_API const char *(lua_getlocal) (lua_State *L, const lua_Debug *ar, int n);
NC_LUA_API const char *(lua_setlocal) (lua_State *L, const lua_Debug *ar, int n);
NC_LUA_API const char *(lua_getupvalue) (lua_State *L, int funcindex, int n);
NC_LUA_API const char *(lua_setupvalue) (lua_State *L, int funcindex, int n);

NC_LUA_API void *(lua_upvalueid) (lua_State *L, int fidx, int n);
NC_LUA_API void  (lua_upvaluejoin) (lua_State *L, int fidx1, int n1, int fidx2, int n2);

NC_LUA_API void (lua_sethook) (lua_State *L, lua_Hook func, int mask, int count);
NC_LUA_API lua_Hook (lua_gethook) (lua_State *L);
NC_LUA_API int (lua_gethookmask) (lua_State *L);
NC_LUA_API int (lua_gethookcount) (lua_State *L);

NC_LUA_API int (lua_setcstacklimit) (lua_State *L, unsigned int limit);

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
// end_of_file //
#endif	// NC_LUACONFIG_H //