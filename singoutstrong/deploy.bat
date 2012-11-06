IF EXIST .\Dist rd .\Dist /S /Q
xcopy .\jdksmidi\release\*.dll .\Dist /I
xcopy .\soscore\release\*.dll .\Dist /I
xcopy .\singoutstrong\release\*.exe .\Dist /I
xcopy .\singoutstrong\skins .\Dist\skins /E /I
xcopy .\libs\dll\release\*.* .\Dist /E /I
xcopy .\singoutstrong\samples .\Dist\samples /E /I
xcopy .\singoutstrong\docs .\Dist\docs /E /I
signtool.exe sign /a .\Dist\singoutstrong.exe