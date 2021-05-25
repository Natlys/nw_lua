#include "nc_lua_pch.hxx"
#include "nc_lua.hxx"
#if (defined NC_BUILD)
#   if (NC_BUILD & NC_BUILD_EXE)
int main(int arg_num, const char* arg_str[])
{
    /* init */
    NC_OLOG(NC_GREETING);
    /* work */
    NC_BREAK();
    /* quit */
    return NC_ZERO;
}
#   endif  /* NC_BUILD_EXE */
#endif  /* NC_BUILD */