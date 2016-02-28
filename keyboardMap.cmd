@echo off
cls
set /p comIn=Enter COM Port Number:
set /p BAUD=Enter BAUD Rate:
set COM=COM%comIn%
mode %COM% BAUD=%BAUD% PARITY=n DATA=8
echo Writing To %COM% with baud=%BAUD%
pause

   :menu
   cls
   echo.
   echo Writing To %COM%
   echo       Q - Wrist Up
   echo       A - Wrist Down
   echo       W - Elbow Up
   echo       S - Elbow Down
   echo       E - Base Up
   echo       D - Base Down
   echo       J - Rotate Left
   echo       L - Rotate Right
   echo       I - Open Grip
   echo       K - Close Grip
   echo       B - End
   echo.

   choice /c:qweasdjlikb > nul

   if errorlevel 11 goto B
   if errorlevel 10 goto K
   if errorlevel 9 goto I
   if errorlevel 8 goto L
   if errorlevel 7 goto J
   if errorlevel 6 goto D
   if errorlevel 5 goto S
   if errorlevel 4 goto A
   if errorlevel 3 goto E
   if errorlevel 2 goto W
   if errorlevel 1 goto Q
   echo Error... choice not installed
   pause
   goto end

   REM Wrist Up - Servo 3
   :Q
   echo 0131;
   ping 192.0.2.2 -n 1 -w 8 > nul
   pause;
   goto menu

   REM Elbow Down - Servo 2
   :W
   echo 0221; > %COM%
   ping 192.0.2.2 -n 1 -w 8 > nul
   pause;
   goto menu

   REM Base up - Servo 1
   :E
   echo 0111; > %COM%
   ping 192.0.2.2 -n 1 -w 8 > nul
   pause;
   goto menu

   REM Wrist Down - Servo 3
   :A
   echo 0231; > %COM%
   ping 192.0.2.2 -n 1 -w 8 > nul
   pause;
   goto menu

   REM Elbow Down - Servo 2
   :S
   echo 0221; > %COM%
   ping 192.0.2.2 -n 1 -w 8 > nul
   pause;
   goto menu

   REM Base Down - Servo 1
   :D
   echo 0211; > %COM%
   ping 192.0.2.2 -n 1 -w 8 > nul
   pause;
   goto menu

   REM Rotate left(down) - Servo 0
   :J
   echo 0201; > %COM%
   ping 192.0.2.2 -n 1 -w 8 > nul
   pause;
   goto menu

   REM Rotate Right(up) - Servo 0
   :L
   echo 0101; > %COM%
   ping 192.0.2.2 -n 1 -w 8 > nul
   pause;
   goto menu

   REM Close Grip (up) - Servo 4
   :K
   echo 0141; > %COM%
   ping 192.0.2.2 -n 1 -w 8 > nul
   pause;
   goto menu

   REM Open Grip (down) - Servo 4
   :I
   echo 0241; > %COM%
   ping 192.0.2.2 -n 1 -w 8 > nul
   pause;
   goto menu

   :B
   :end
   