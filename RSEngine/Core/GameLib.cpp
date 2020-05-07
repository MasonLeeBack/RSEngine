/*

RSEngine
Copyright (c) 2019 Mason Lee Back

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

File name: GameLib.cpp

*/

#include <Core/GameLib.h>
#include <Classes/RSClasses.h>

namespace rs {
    GameLib* g_GameLib;
    std::shared_ptr<MeshPart> myPart;
    void GameLib::Initialize() {

        NewInstance(Base, Part);
        Base->Size = Vector3(1, 1, 1);
        Base->Position = Vector3(0, 0, 0);

        NewInstance(Texturx, Texture);
        Texturx->SetParent(Base);
        Texturx->File = "data/textures/cute_guinea_pig.png";

        NewInstance(Brick, MeshPart);
        Brick->Size = Vector3(1024, 1024, 1024);
        Brick->Position = Vector3(0, 0, 0);
        Brick->Name = "Skybox";
        myPart = Brick;

        NewInstance(Texturxv, Texture);
        Texturxv->SetParent(Brick);
        Texturxv->File = "data/textures/test/star.png";

        NewInstance(Tree, MeshPart);
        Tree->Size = Vector3(0.02, 0.02, 0.02);
        Tree->Position = Vector3(0, 0, 0);
        Tree->Rotation = Vector3(90, 90, 0);
        Tree->MeshFile = "data/models/nature/test.fbx";

        NewInstance(MountainTexture, Texture);
        MountainTexture->SetParent(Tree);
        MountainTexture->File = "data/textures/test.png";

    }
    void GameLib::Update() {
    }

    void GameLib::Shutdown() {

    }

} // namespace rs
