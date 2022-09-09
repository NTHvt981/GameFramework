@ECHO OFF
SET "FOLDER=data"
SET "SRC=%cd%\%FOLDER%"
SET "DEST=%cd%\release\%FOLDER%"

@REM Xcopy "%SRC%\%FOLDER%" "%DEST%\%FOLDER%" /s /e /z /i /f /k
Xcopy "%FOLDER%" "release\%FOLDER%\" /s /e /z /i /f /k /y /v

ECHO "files from %SRC% to %DEST% finished."
pause