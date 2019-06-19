@echo off

echo ------------------------------------------------
echo  RSEngine Build Utility
echo  Copyright (c) 2019 Mason Lee Back
echo ------------------------------------------------

call engine_env.bat

call build_sdk.bat
call build_shaders.bat
call build_engine.bat

call build_devtools.bat
call build_editor.bat
call build_output.bat

call postbuild.bat