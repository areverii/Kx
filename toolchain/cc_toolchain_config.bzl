load("@bazel_tools//tools/build_defs/cc:action_names.bzl", "ACTION_NAMES")

load(
   "@bazel_tools//tools/cpp:cc_toolchain_config_lib.bzl",
   "artifact_name_pattern",
   "feature",
   "flag_group",
   "flag_set",
   "tool_path",
)

all_link_actions = [
   ACTION_NAMES.cpp_link_executable,
   ACTION_NAMES.cpp_link_dynamic_library,
   ACTION_NAMES.cpp_link_nodeps_dynamic_library,
]

def _impl(ctx):
   tool_paths = [
       tool_path(
           name = "gcc",
           path = "C:/mingw64/bin/gcc",
       ),
       tool_path(
           name = "ld",
           path = "C:/mingw64/bin/ld",
       ),
       tool_path(
           name = "ar",
           path = "C:/mingw64/bin/ar",
       ),
       tool_path(
           name = "cpp",
           path = "C:/mingw64/bin/cpp",
       ),
       tool_path(
           name = "gcov",
           path = "C:/mingw64/bin/gcov",
       ),
       tool_path(
           name = "nm",
           path = "C:/mingw64/bin/nm",
       ),
       tool_path(
           name = "objdump",
           path = "C:/mingw64/bin/objdump",
       ),
       tool_path(
           name = "strip",
           path = "C:/mingw64/bin/strip",
       ),
   ]

   features = [
       feature(
           name = "default_linker_flags",
           enabled = True,
           flag_sets = [
               flag_set(
                   actions = all_link_actions,
                   flag_groups = ([
                       flag_group(
                           flags = [
                               "-lstdc++", "-lgdi32", "-static-libgcc", "-static-libstdc++", "-static",
                           ],
                       ),
                   ]),
               ),
           ],
       ),
   ]

   return cc_common.create_cc_toolchain_config_info(
       ctx = ctx,
       features = features,
       cxx_builtin_include_directories = [
           "C:/mingw64/include",
           "C:/mingw64/x86_64-w64-mingw32/include",
           "C:/mingw64/lib/gcc/x86_64-w64-mingw32/12.2.0/include-fixed",
           "C:/mingw64/lib/gcc/x86_64-w64-mingw32/12.2.0/include",
           "C:/mingw64/lib/gcc/x86_64-w64-mingw32/12.2.0",
           "C:/mingw64/x86_64-w64-mingw32/lib", #temp
       ],
       toolchain_identifier = "local",
       host_system_name = "local",
       target_system_name = "local",
       target_cpu = "x64_windows",
       target_libc = "unknown",
       compiler = "g++",
       abi_version = "unknown",
       abi_libc_version = "unknown",
       tool_paths = tool_paths,

       artifact_name_patterns = [
          artifact_name_pattern (
              category_name = "executable",
              prefix = "",
              extension = ".exe",
          ),
       ]
   )

cc_toolchain_config = rule (
   implementation = _impl,
   attrs = {},
   provides = [CcToolchainConfigInfo],
)