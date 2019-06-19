@echo off

echo[
echo Setting environment variables...
echo[

set RSEngine_EngineName=RSEngine

set RSEngine_Root=%cd%
set RSEngine_EngineProj=%cd%\%RSEngine_EngineName%

set RSEngine_SDK=%RSEngine_Root%\sdk\private

echo ------------------------------------------------
echo RSEngine_EngineName = %RSEngine_EngineName%
echo[
echo RSEngine_Root = %RSEngine_Root%
echo RSEngine_EngineProj = %RSEngine_EngineProj%
echo ------------------------------------------------
