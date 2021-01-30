@echo off

mkdir ..\..\build
pushd ..\..\build
cl -Zi  ..\handmadeHero\code\Win32_handmade.cpp user32.lib Gdi32.lib
popd 
