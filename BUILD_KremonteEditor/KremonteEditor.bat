REM BUILDING DEBUG WINDOWS (MINGW)
bazel build --config=mingw_config --cxxopt=-D_KR_PLATFORM_WINDOWS_ --cxxopt=-D_KR_DEBUG --compilation_mode=dbg -s --explain=log.txt --verbose_explanations //...

IF %ERRORLEVEL% EQU 0 (
	bazel run --config=mingw_config --cxxopt=-D_KR_PLATFORM_WINDOWS_ --cxxopt=-D_KR_DEBUG //Clients/KremonteEditor/src:KremonteEditor
)
PAUSE