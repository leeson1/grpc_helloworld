# Overview
Getting started with grpc (in C++).

Building with bazel.

# Building 
Generate compile_commands.json

```shell
bazel build src:example_compdb
```

Build project

```shell
bazel build ...
bazel build src:server
bazel build src:client
```
