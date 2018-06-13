@echo off

set C_FLAGS=-FC -I../inc -DWINDOWS=1
set D_FLAGS=-Zi -MT -Od -D__DEBUG
set R_FLAGS=-MD -O2 
set C_LINK_FLAGS=/link /LIBPATH:..\lib\win64 SDL2.lib SDL2main.lib
REM glew32.lib opengl32.lib
set R_LINK_FLAGS=/SUBSYSTEM:windows /RELEASE 

set ORIGINAL_PATH=%PATH%
call "E:/init_dev.bat"

pushd "E:/Dev/SpriteShow/bin"

REM this toggles release and debug mode.
set IS_RELEASE="" 

if %IS_RELEASE% == "yes" (
	cl %C_FLAGS% %R_FLAGS% -Fess.exe ..\src\ss_main.cpp %C_LINK_FLAGS% %R_LINK_FLAGS%
) else (
	cl %C_FLAGS% %D_FLAGS% -Fedebug.exe ..\src\ss_main.cpp %C_LINK_FLAGS%
)

if not %ErrorLevel% == 0 (
	echo Compilation failed
	goto _END
)

copy /Y ..\lib\win64\SDL2.dll
cd ..
if "%1" == "run" (
	if %IS_RELEASE% == "yes" (
		start bin/ss.exe
	) else (
		start bin/debug.exe
	)
)
:_END
set PATH=%ORIGINAL_PATH%
popd
