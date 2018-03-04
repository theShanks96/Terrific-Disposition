#include "stdafx.h"
#include "CppUnitTest.h"

#include "../Terrific Disposition/ResourceManager.h"
#include "../Terrific Disposition/NaturalLogicManager.h"

#include "../Terrific Disposition/Player.h"
#include "../Terrific Disposition/World.h"



using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TerrificTesting {
	TEST_CLASS(WorldTests) {
public:

	TEST_METHOD(WorldConstructor) {
		ResourceManager* ptr_resourceManager = new ResourceManager("../../../Assets/AssetConfigurationTesting.json");

		std::string m_playerName = ptr_resourceManager->getRandomPseudonymOne(true).s_nameString + " " + ptr_resourceManager->getRandomPseudonymTwo(true).s_nameString;
		Player* ptr_player = new Player(m_playerName);
		Assert::AreNotEqual(0, (int)ptr_player->c_nameString.size(), L"Player name is empty");

		World* ptr_gameWorld = new World(16, ptr_player);
		Assert::AreEqual(16, ptr_gameWorld->c_mapSizeInt, L"World c_mapSizeInt not set up properly");
		Assert::AreNotEqual(0, (int)ptr_gameWorld->ptr_player->c_nameString.size(), L"Player not properly linked");

		//ptr_gameWorld->linkNaturalLogicManager(ptr_naturalLogicManager);
		//Assert::AreEqual(16, ptr_gameWorld->ptr_naturalLogicManager->c_vectorCapacityInt, L"NaturalLogicManager is not linked");
		
	}

	};



}