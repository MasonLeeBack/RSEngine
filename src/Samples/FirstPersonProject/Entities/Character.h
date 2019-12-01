/*

RSEngine
Copyright (c) 2019 Mason Lee Back

File name: Character.h

*/

#ifndef _Character_h_
#define _Character_h_

#include <Classes/Camera.h>
#include <Classes/Part.h>
#include <Input/RareInput.h>

using namespace rs;

class Character : public Instance {
public:
	//INITIALIZE_INSTANCE_HEADER(Character)

	Character();
	Character(Part* characterPart, Camera* characterCamera);
	~Character();

    public_entity<Camera>   playerCameraObject;
    public_entity<Part>     playerPart;

    void PlayerMove(Vector3 velocity);
    void PlayerTeleport(Vector3 pos);

	Vector3 GeneralPosition = Vector3(0, 0, 0);
	Vector3 GeneralVelocity = Vector3(0, 0, 0);

	void InputHandler(InputMap characterInput);

    float PlayerHealth = 100.0f;
	float PlayerMovementSpeed = 15.0f;

    virtual void tick();
};

#endif // _Character_h_
