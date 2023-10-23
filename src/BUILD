load("@com_grail_bazel_compdb//:defs.bzl", "compilation_database")
# load("@com_grail_bazel_output_base_util//:defs.bzl", "OUTPUT_BASE")

compilation_database(
    name = "example_compdb",
    # output_base = OUTPUT_BASE,
    targets = [
        "//proto:hello_greeter_cpp_grpc",
        "//src/server:server",
        "//src/client:client",
    ],
)


