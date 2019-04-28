#include "EntityManager.h"

const float EntityManager::PIXELS_PER_METER = 10.f;

EntityManager::EntityManager() : World(b2Vec2(0, 0))
{
} // default constructor

EntityManager::~EntityManager()
{

	for (int i = 0; i < this->_entities.size(); i++)
		delete this->_entities[i];

	this->_entities.clear();

} // destructor 

EntityManager* EntityManager::input(sf::Event &event)
{
	return this;
} // input

EntityManager* EntityManager::update(float dt)
{

	//for (int i = 0; i < this->_entities.size(); i++)
		//this->_entities[i];
	World.Step(dt * 60, 8, 3);

	return this;

} // update

EntityManager* EntityManager::render(sf::RenderTarget &target)
{



	return this;
} // render
