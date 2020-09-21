/*

RSEngine
Copyright (c) 2020 Mason Lee Back

File name: GameLib.cpp

*/

#include <Core/GameLib.h>
#include <Classes/RSClasses.h>
#include <Physics/RSPhysics.h>
using namespace rs::Physics;

#include <Core/Engine.h>

namespace rs {
    GameLib* g_GameLib;
    std::shared_ptr<Part> up;
    std::shared_ptr<UIPanel>uip;
    void GameLib::Initialize() {
        /*
        NewInstance(BasePlate, Part);
        BasePlate->Name = "MyBasePlate";
        BasePlate->PhysicsEnabled = false;
        BasePlate->Size = Vector3(100, 1, 100);
        BasePlate->Position = Vector3(0, -3, 0);

        g_RSPhysics->addRigidBody(BasePlate);

        NewInstance(Base, Part);
        Base->Size = Vector3(1, 1, 1);
        Base->Position = Vector3(0, 15, 0);
        Base->PhysicsEnabled = true;
        Base->Name = "yo";

        NewInstance(Texturx, Texture);
        Texturx->SetParent(Base);
        Texturx->File = "data/textures/cute_guinea_pig.png";

        g_RSPhysics->addRigidBody(Base);
        
        NewInstance(BP2, Part);
        BP2->Name = "yo2";
        BP2->PhysicsEnabled = true;
        BP2->Size = Vector3(8, 1, 8);
        BP2->Position = Vector3(0, 3, 4);

        g_RSPhysics->addRigidBody(BP2);



        NewInstance(Tree, MeshPart);
        Tree->Size = Vector3(0.02, 0.02, 0.02);
        Tree->Position = Vector3(0, 0, 0);
        Tree->Rotation = Vector3(90, 90, 0);
        Tree->MeshFile = "data/models/nature/test.fbx";

        NewInstance(MountainTexture, Texture);
        MountainTexture->SetParent(Tree);
        MountainTexture->File = "data/textures/test.png";*/

        NewInstance(Tree, MeshPart);
        Tree->Size = Vector3(0.02f, 0.02f, 0.02f);
        Tree->Position = Vector3(0, 0, 0);
        Tree->Rotation = Vector3(90, 90, 0);
        Tree->MeshFile = "data/models/sponza.obj";

        
        NewInstance(SB, Skybox);
        SB->Name = "Skybox";
        SB->Skymap = "data/textures/test/star.png";

        NewInstance(Texturxv, Texture);
        Texturxv->SetParent(SB);
        Texturxv->File = "data/textures/test/star.png";

        NewInstance(Base, Part);
        Base->Size = Vector3(1, 1, 1);
        Base->Position = Vector3(0, 0, -1);
        Base->PhysicsEnabled = true;
        Base->Name = "yo";
        up = Base;

        //NewInstance(Texturx, Texture);
       // Texturx->SetParent(Base);
        //Texturx->File = "data/textures/loading.png";

        NewInstance(UILoading, UIPanel);
        UILoading->Name = "UILoading";
        UILoading->Size = UIScale(0, 100, 0, 100);
        UILoading->Position = UIScale(1, -125, 1, -125);
        UILoading->Transparency = 1;
        uip = UILoading;

        NewInstance(LoadingTexture, Texture);
        LoadingTexture->SetParent(UILoading);
        LoadingTexture->File = "data/textures/loading.png";

        /*NewInstance(UIPanelp, UIPanel);
        UIPanelp->Size = UIScale(.5, 0, .5, 0);
        UIPanelp->Position = UIScale(0.5, 0, 0.5, 0);
        UIPanelp->Transparency = 1;
        uip = UIPanelp;

        NewInstance(UIpTexture, Texture);
        UIpTexture->SetParent(UIPanelp);
        UIpTexture->File = "data/textures/client_loading_bg.png";*/



    }

    void GameLib::Update() {
        //up->Rotation += Vector3(1, 0, 0);
        uip->Rotation += 1.0f;
    }

    void GameLib::Shutdown() {

    }

} // namespace rs
