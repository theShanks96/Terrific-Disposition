#include "stdafx.h"
#include "CppUnitTest.h"

#include "../Terrific Disposition/ResourceManager.h"
#include "../Terrific Disposition/NaturalLogicManager.h"

#include "../Terrific Disposition/Player.h"
#include "../Terrific Disposition/RoomEscape.h"



using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TerrificTesting {
	TEST_CLASS(RoomEscapeTests) {
public:

	TEST_METHOD(RoomEscapeConstructor) {
		ResourceManager* ptr_resourceManager = new ResourceManager("../../../Assets/AssetConfigurationTesting.json");
		NaturalLogicManager* ptr_naturalLogicManager = new NaturalLogicManager(ptr_resourceManager);

		std::string m_playerName = ptr_resourceManager->getRandomPseudonymOne(true).s_nameString + " " + ptr_resourceManager->getRandomPseudonymTwo(true).s_nameString;
		Player* ptr_player = new Player(m_playerName);
		Assert::AreNotEqual(0, (int)ptr_player->c_nameString.size(), L"Player name is empty");

		int c_mapSizeInt = 16;
		RoomEscape* ptr_roomEscape = new RoomEscape();
		Assert::AreEqual(4, (int)ptr_roomEscape->getChosenTheme().size(), L"RoomEscape c_chosenTheme incorrectly initialised");
		Assert::AreEqual(commandProfile(0, 0, 0, 0, 0, 0).s_adjectivesInt, ptr_roomEscape->c_commandProfile.s_adjectivesInt, L"RoomEscape c_commandProfile incorrectly initialised");


		//	Although the basic constructor has been tested, it is best to test the full contructor
		ptr_roomEscape->readFromConfiguration(ptr_resourceManager->getThemePath("RoomEscapeConfiguration"));
		ptr_roomEscape->linkPlayer(ptr_player);
		ptr_roomEscape->linkNaturalLogicManager(ptr_naturalLogicManager);
		
		Assert::AreNotEqual(0, (int)ptr_roomEscape->ptr_player->c_nameString.size(), L"Player is not linked");
		Assert::AreEqual(16, ptr_roomEscape->ptr_naturalLogicManager->c_vectorCapacityInt, L"NaturalLogicManager is not linked");
	}

	};

	

}