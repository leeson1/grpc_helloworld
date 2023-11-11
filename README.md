<!--
 * @Author: Leeson
 * @Date: 2023-09-25 23:46:38
-->
# Overview
grpc examples compiled through Bazel.

# Building 
Generate compile_commands.json

```shell
bazel build src:example_compdb
```

To only build the server and client, run the following:

```shell
bazel build ...
bazel build src/...
```
