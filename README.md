# Kremonte_Engine

To build and run Kremonte on Windows in Debug mode, run KremonteEngine.bat.






Manual build all:
bazel build //...

Build Kremonte Engine with _KR_PLATFORM_WINDOWS_ enabled:
bazel build --cxxopt=-D_KR_PLATFORM_WINDOWS_ //Kremonte:Kremonte
bazel build --config=mingw_config --cxxopt=-D_KR_PLATFORM_WINDOWS_ //Kremonte:Kremonte

Build Sandbox with _KR_PLATFORM_WINDOWS_ enabled:
bazel build --cxxopt=-D_KR_PLATFORM_WINDOWS_ //Clients/Sandbox/src:Sandbox

Build YOSHKA:
bazel build //Clients/YOSHKA/src:YOSHKA