#include "nc_lua_pch.hpp"
#include "nc_lua.hpp"
#if (defined NC_BUILD)
#   if (NC_BUILD & NC_BUILD_EXE)
int main(int arg_num, const char* arg_str[]) {
    NC_OLOG(NC_GREETING);
    NC_BREAK();
    return NC_ZERO;
}
#endif  /* NC_BUILD */
/* end_of_file */