#include "build.h"


const char *out = "program";

const char *source_files[] = {
    "test.c",
    NULL
};

const char *extra_warnings[] = {
    // "error",
    NULL
};

mod_data_t mod_data = {0};

int build(int argc, char *argv[])
{
    compile_info_t info = {
        .output = out,
        .std = "c17",
        .optimisations = RELEASE_FLAG,

        .source_files = source_files,
        .warnings = nice_warnings,
		.warnings_off = nice_warnings_off,
    };

    int res = compile_w(info);
    if (res)
        return res;


    if (contains("run", argc, argv)) {
        printf("./%s:\n", out);

#ifdef _WIN32
        return execute_w("%s.exe", out);
#else
        return execute_w("./%s", out);
#endif // _WIN32
    }

    return 0;
}


int main(int argc, char *argv[])
{
    const char *build_files[] = { "build.c", NULL };
    int res = try_rebuild_self(build_files, argc, argv);
    if (res != -1)
        return res;

    mod_data_load(&mod_data, NULL);
    res = build(argc, argv);
    mod_data_store(&mod_data, NULL);

    return res;
}

