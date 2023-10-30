@echo off

SETLOCAL enabledelayedexpansion
set sourcePath=application\sandbox\src\sandbox\resources\shaders
set destinationPathOGL=application\sandbox\src\sandbox\resources\shaders\ogl
set destinationPathDX11=application\sandbox\src\sandbox\resources\shaders\dx11
set includePath=application\sandbox\src\sandbox\resources\shaders\include
set oglProfile=420
set dx11Profile=s_5_0


for %%i in (%sourcePath%\*.sc) do (
    echo %%~ni | find /i "FS">nul 
    if !errorlevel! equ 0 (
    "resources\tools\shader compiler\shaderc.exe" -f %sourcePath%\%%~ni.sc --profile %oglProfile% --type fragment -o %destinationPathOGL%\%%~ni.shader --varyingdef %includePath%\varying.def.sc --v -i %includePath%
    "resources\tools\shader compiler\shaderc.exe" -f %sourcePath%\%%~ni.sc --profile %dx11Profile% --type fragment -o %destinationPathDX11%\%%~ni.shader --varyingdef %includePath%\varying.def.sc --v -i %includePath%
    )

    echo %%~ni| find /i "VS">nul 
    if !errorlevel! equ 0 (
    "resources\tools\shader compiler\shaderc.exe" -f %sourcePath%\%%~ni.sc --profile %oglProfile% --type vertex -o %destinationPathOGL%\%%~ni.shader --varyingdef %includePath%\varying.def.sc --v -i %includePath%
    "resources\tools\shader compiler\shaderc.exe" -f %sourcePath%\%%~ni.sc --profile %dx11Profile% --type vertex -o %destinationPathDX11%\%%~ni.shader --varyingdef %includePath%\varying.def.sc --v -i %includePath%
    )
)
ENDLOCAL
pause
