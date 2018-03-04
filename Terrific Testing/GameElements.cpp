#include "stdafx.h"
#include "CppUnitTest.h"

#include "../Terrific Disposition/ResourceManager.h"
#include "../Terrific Disposition/NaturalLogicManager.h"

#include "../Terrific Disposition/Player.h"
#include "../Terrific Disposition/Interactable.h"



using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TerrificTesting {
	TEST_CLASS(PlayerTests) {
public:

	TEST_METHOD(PlayerConstructor) {
		ResourceManager* ptr_resourceManager = new ResourceManager("../../../Assets/AssetConfigurationTesting.json");

		std::string m_playerName = ptr_resourceManager->getRandomPseudonymOne(true).s_nameString + " " + ptr_resourceManager->getRandomPseudonymTwo(true).s_nameString;
		Player* ptr_player = new Player(m_playerName);
		Assert::AreNotEqual(0, (int)ptr_player->c_nameString.size(), L"Player name is empty");

	}

	};

	TEST_CLASS(InteractableTests) {
public:

	TEST_METHOD(InteractableConstructor) {
		Interactable* ptr_interactableTest = new Interactable();
		ptr_interactableTest->setName("The Great Cornholio");

		Assert::AreEqual("The Great Cornholio", ptr_interactableTest->getName().c_str(), L"Incorrect name definition for Interactable");
	
	}

	};



}