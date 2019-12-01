/*

RSEngine
Copyright (c) 2019 Mason Lee Back

*/

#include "Character.h"

Character::~Character()
{

}
Character::Character(Part* characterPart, Camera* characterCamera)
{
	if (characterPart == NULL) {

	}
}

void Character::PlayerMove(Vector3 velocity)
{
}

void Character::PlayerTeleport(Vector3 pos)
{
}

void Character::InputHandler(InputMap characterInput)
{
}

void Character::tick()
{
	// Make sure the character camera follows 
    tickChildren();
}
