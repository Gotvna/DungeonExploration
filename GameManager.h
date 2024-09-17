#pragma once

#include "Renderer.h"

class Entity;


class GameManager
{
public:

	GameManager();

	void run();

private:

	void loadMap();

	void playerAction();

	bool isMoveValid(Entity *entity, int desiredX, int desiredY);


private:

	Renderer renderer;
};
