@echo off

echo ------------------------------------------------
echo  Building SDK...
echo ------------------------------------------------

xcopy /S %RSEngine_EngineProj%\Include %RSEngine_Root%\sdk\temp

