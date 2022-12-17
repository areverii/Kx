REM BUILDING DEBUG WINDOWS (MINGW)
bazel build --config=mingw_config --cxxopt=-D_KR_PLATFORM_WINDOWS_ --cxxopt=-D_KR_DEBUG --explain=log.txt --verbose_explanations //...
bazel run --config=mingw_config --cxxopt=-D_KR_PLATFORM_WINDOWS_ --cxxopt=-D_KR_DEBUG //Clients/Sandbox/src:Sandbox
PAUSE