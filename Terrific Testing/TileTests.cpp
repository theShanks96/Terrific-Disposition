#include "stdafx.h"
#include "CppUnitTest.h"

#include "../Terrific Disposition/ResourceManager.h"
#include "../Terrific Disposition/NaturalLogicManager.h"

#include "../Terrific Disposition/AcceptableTile.h"
#include "../Terrific Disposition/CautiousTile.h"
#include "../Terrific Disposition/DeadlyTile.h"



using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TerrificTesting {
	TEST_CLASS(AcceptableTileTests) {
public:

	TEST_METHOD(AcceptableTileConstructor) {
		AcceptableTile* ptr_testTileZero = new AcceptableTile();
		Tile* ptr_testTileOne = new AcceptableTile("There's cheese all over the floor.");

		Assert::AreEqual(3, ptr_testTileZero->c_maximumInteractables, L"Incorrect maximum interactables.");
		std::string m_testString = ptr_testTileOne->getTileInformation();
		bool m_cheese = (m_testString.find("cheese") != std::string::npos);
 		Assert::AreEqual(true, m_cheese, L"Construction with information text failed.");

	}

	};

	TEST_CLASS(CautiousTileTests) {
public:

	TEST_METHOD(CautiousTileConstructor) {
		CautiousTile* ptr_testTileZero = new CautiousTile();
		Tile* ptr_testTileOne = new CautiousTile(true);
		
		Assert::AreEqual("Might be best to move away from here.", ptr_testTileZero->getTypeFlavour().c_str(), L"Incorrect flavour text.");
		std::string m_testString = ptr_testTileOne->getDescription();
		bool m_hideout = (m_testString.find("hideout") != std::string::npos);
		Assert::AreEqual(true, m_hideout, L"Construction with information text failed.");
	}

	};

	TEST_CLASS(DeadlyTileTests) {
public:

	TEST_METHOD(DeadlyTileConstructor) {
		DeadlyTile* ptr_testTileZero = new DeadlyTile();
		Tile* ptr_testTileOne = new DeadlyTile("The winos are picking a fight with a hickory beam.");

		Assert::AreEqual("You are dead.", ptr_testTileZero->getTypeFlavour().c_str(), L"Incorrect flavour text.");
		std::string m_testString = ptr_testTileOne->getDescription();
		bool m_hickory = (m_testString.find("hickory") != std::string::npos);
		Assert::AreEqual(true, m_hickory, L"Construction with information text failed.");
	}

	};

}