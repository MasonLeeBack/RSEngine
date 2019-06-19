/*

RSEngine
Copyright (c) 2019 Mason Lee Back

File name: Character.h

*/

#ifndef _Character_h_
#define _Character_h_

#include <Classes/Camera.h>
#include <Classes/Part.h>

using namespace rs;

class Character : public Instance {
public:
    INITIALIZE_INSTANCE_HEADER(Character);

    public_entity<Camera>   playerCameraObject;
    public_entity<Part>     playerPart;

    void PlayerMove(Vector3 velocity);
    void PlayerTeleport(Vector3 pos);

    float PlayerHealth = 100.0f;

    virtual void tick();
};

#endif // _Character_h_
