#include "MainGame.h"
#include "MyObjects/MyObject.h"

MainGame::MainGame(const dx3d::GameDesc& desc): dx3d::Game(desc)
{
}

void MainGame::onCreate()
{
	Game::onCreate();
	auto& world = getWorld();

	auto object = world.createGameObject<dx3d::GameObject>();
	auto myObject = world.createGameObject<MyObject>();

	if (!myObject) return;

	auto transform = myObject->getComponent<dx3d::TransformComponent>();
	if (!transform) return;

	transform->setPosition({ 10,10,10 });
	transform->setRotation({ 1.57f,0.707f,1.57f });


}

void MainGame::onUpdate(dx3d::f32 deltaTime)
{
	Game::onUpdate(deltaTime);
}
