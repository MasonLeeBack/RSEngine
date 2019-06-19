/*

RSEngine
Copyright (c) 2019 Mason Lee Back

File name: RSMain.cpp

*/

#include "Entities/Character.h"

extern "C" _declspec(dllexport) bool GameLib_Initialize() {
    NewInstance(myCharacter, Character);
    NewInstance(characterBase, Part);
    NewInstance(characterCamera, Camera);
    characterCamera->Parent = characterBase;

    myCharacter->playerCameraObject = characterCamera;
    myCharacter->playerPart = characterBase;
}

extern "C" _declspec(dllexport) void GameLib_Update() {

}

extern "C" _declspec(dllexport) void GameLib_Shutdown() {

}
