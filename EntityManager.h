#pragma once

#include "Entity.h"

#include <vector>

class EntityManager
{

	std::vector <Entity*> _entities;

public:

	// pixels per meter (used in Box2D)
	static const float PIXELS_PER_METER;
	b2World World;

	EntityManager();
	~EntityManager();

	EntityManager* input(sf::Event &event);
	EntityManager* update(float dt);
	EntityManager* render(sf::RenderTarget &target);

	Entity* pushEntity(Entity* entity);

};