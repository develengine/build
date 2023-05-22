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

int main(int argc, char *argv[])
{
    compile_info_t info = {
        .output = out,
        .std = "c17",
        .optimisations = "2",

        .source_files = source_files,
        .warnings = merge(nice_warnings, extra_warnings),
    };

    int res;
    if ((res = compile_w(info)))
        return res;

    if (contains("run", argc, argv)) {
        printf("./%s:\n", out);
        return execute_w("./%s", out);
    }

    return 0;
}
