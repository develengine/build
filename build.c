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
        .optimisations = "2",

        .source_files = source_files,
        .warnings = nice_warnings,
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
}

int main(int argc, char *argv[])
{
    if ((file_time_cmp(mod_time("build.c"), mod_time("build")) > 0)) {
        printf("recompiling build\n");

        if (exists("build.old")) {
            remove("build.old");
        }

        rename("build", "build.old");

        const char *src[] = { "build.c", NULL };

        compile_info_t info = { .output = "build", .source_files = src };

        int res = compile_w(info);
        if (res)
            return res;

        return execute_argv_w(argv);
    }

    mod_data_load(&mod_data, NULL);
    int res = build(argc, argv);
    mod_data_store(&mod_data, NULL);

    return res;
}

