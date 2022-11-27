SET PROJDIR=%CD%
PUSHD C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build
/wait vcvarsall.bat amd64
POPD
IF NOT EXIST build\debug ( MKDIR build\debug )
CD build\debug
call cl.exe -Zi ..\..\src\main.cpp
CD %PROJDIR%
