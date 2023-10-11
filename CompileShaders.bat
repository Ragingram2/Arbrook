@echo off
SETLOCAL
set sourcePath="application\sandbox\src\sandbox\resources\shaders"
set destinationPathOGL="application\sandbox\src\sandbox\resources\shaders\ogl"
set destinationPathDX11="application\sandbox\src\sandbox\resources\shaders\dx11"
set includePath="application\sandbox\src\sandbox\resources\shaders\include"

"resources\tools\shader compiler\shaderc.exe" -f %sourcePath%\testFS.sc -p 440 --type fragment -o %destinationPathOGL%\testFS.shader --varyingdef %sourcePath%\varying.def.sc --v -i %includePath%
"resources\tools\shader compiler\shaderc.exe" -f %sourcePath%\testVS.sc -p 440 --type vertex -o %destinationPathOGL%\testVS.shader --varyingdef %sourcePath%\varying.def.sc --v -i %includePath%
"resources\tools\shader compiler\shaderc.exe" -f %sourcePath%\instance_testFS.sc -p 440 --type fragment -o %destinationPathOGL%\instance_testFS.shader --varyingdef %sourcePath%\varying.def.sc --v -i %includePath%
"resources\tools\shader compiler\shaderc.exe" -f %sourcePath%\instance_testVS.sc -p 440 --type vertex -o %destinationPathOGL%\instance_testVS.shader --varyingdef %sourcePath%\varying.def.sc --v -i %includePath%
ENDLOCAL
pause