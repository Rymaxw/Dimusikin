@echo off
echo Compiling Music Player...
g++ Main.cpp admin/AdminMenu.cpp user/UserMenu.cpp library/LibraryManager.cpp playlist/PlaylistManager.cpp player/PlayerEngine.cpp utils/Utils.cpp utils/JsonHelper.cpp -o MusicPlayer

if %errorlevel% neq 0 (
    echo Compilation Failed!
    pause
    exit /b %errorlevel%
)

echo Compilation Success! Running Music Player...
echo.
MusicPlayer.exe
pause
