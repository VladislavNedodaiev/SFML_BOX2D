#include "SFML_BOX2D.h"

const float SCALE = 30.f;


/** Create the base for the boxes to land */
void CreateGround(b2World& World, float X, float Y);

/** Create the boxes */
void CreateBox(b2World& World, int MouseX, int MouseY);

int main()
{
	/** Prepare the window */
	sf::RenderWindow Window(sf::VideoMode(800, 600, 32), "Test");
	Window.setFramerateLimit(60);

	/** Prepare the world */
	b2Vec2 Gravity(0.f, 9.8f);
	b2World World(b2Vec2(0, 0));
	CreateGround(World, 400.f, 500.f);
	Gravity.y = -1.0f;
	/** Prepare textures */

	while (Window.isOpen())
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			int MouseX = sf::Mouse::getPosition(Window).x;
			int MouseY = sf::Mouse::getPosition(Window).y;
			CreateBox(World, MouseX, MouseY);
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
		{
			int MouseX = sf::Mouse::getPosition(Window).x;
			int MouseY = sf::Mouse::getPosition(Window).y;
			CreateGround(World, MouseX, MouseY);
		}
		World.Step(1 / 60.f, 8, 3);

		Window.clear(sf::Color::Black);
		int BodyCount = 0;
		for (b2Body* BodyIterator = World.GetBodyList(); BodyIterator != 0; BodyIterator = BodyIterator->GetNext())
		{
			if (BodyIterator->GetType() == b2_dynamicBody)
			{
				sf::RectangleShape recshape(sf::Vector2f(32, 32));
				recshape.setFillColor(sf::Color::White);
				recshape.setOrigin(16.f, 16.f);
				recshape.setPosition(SCALE * BodyIterator->GetPosition().x, SCALE * BodyIterator->GetPosition().y);
				recshape.setRotation(BodyIterator->GetAngle() * 180 / b2_pi);
				Window.draw(recshape);
				++BodyCount;
			}
			else
			{
				sf::RectangleShape recshape(sf::Vector2f(800, 16));
				recshape.setOrigin(400.f, 8.f);
				recshape.setPosition(BodyIterator->GetPosition().x * SCALE, BodyIterator->GetPosition().y * SCALE);
				recshape.setRotation(180 / b2_pi * BodyIterator->GetAngle());
				Window.draw(recshape);
			}
		}
		Window.display();
	}

	return 0;
}

void CreateBox(b2World& World, int MouseX, int MouseY)
{
	b2BodyDef BodyDef;
	BodyDef.position = b2Vec2(MouseX / SCALE, MouseY / SCALE);
	BodyDef.type = b2_dynamicBody;
	b2Body* Body = World.CreateBody(&BodyDef);

	b2PolygonShape Shape;
	Shape.SetAsBox((32.f / 2) / SCALE, (32.f / 2) / SCALE);
	b2FixtureDef FixtureDef;
	FixtureDef.density = 1.f;
	FixtureDef.friction = 0.7f;
	FixtureDef.shape = &Shape;
	Body->CreateFixture(&FixtureDef);
}

void CreateGround(b2World& World, float X, float Y)
{
	b2BodyDef BodyDef;
	BodyDef.position = b2Vec2(X / SCALE, Y / SCALE);
	BodyDef.type = b2_staticBody;
	b2Body* Body = World.CreateBody(&BodyDef);

	b2PolygonShape Shape;
	Shape.SetAsBox((800.f / 2) / SCALE, (16.f / 2) / SCALE);
	b2FixtureDef FixtureDef;
	FixtureDef.density = 0.f;
	FixtureDef.shape = &Shape;
	Body->CreateFixture(&FixtureDef);
}