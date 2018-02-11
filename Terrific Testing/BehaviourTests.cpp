#include "stdafx.h"
#include "CppUnitTest.h"

#include "../Terrific Disposition/Behaviour.h"
#include "../Terrific Disposition/SimpleBehaviour.h"
#include "../Terrific Disposition/FuzzyBehaviour.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TerrificTesting{		
	TEST_CLASS(SimpleBehaviourTests)	{
	public:
		
		TEST_METHOD(SimpleBehaviourConstructor)		{
			
			Behaviour* ptr_testedClassZero = new SimpleBehaviour();
			SimpleBehaviour m_testedClassOne = SimpleBehaviour();

			ptr_testedClassZero->c_nextPlotPoint = int2d(16, 32);
			m_testedClassOne.c_nextPlotPoint = int2d(16, 32);

			Assert::AreEqual(ptr_testedClassZero->c_nextPlotPoint.s_firstInt, m_testedClassOne.c_nextPlotPoint.s_firstInt, L"Different c_nextPlotPoint.s_firstInt Values");
			Assert::AreEqual(ptr_testedClassZero->c_nextPlotPoint.s_secondInt, m_testedClassOne.c_nextPlotPoint.s_secondInt, L"Different c_nextPlotPoint.s_secondInt Values");
		}

	};

	TEST_CLASS(FuzzyBehaviourTests) {
public:

	TEST_METHOD(FuzzyBehaviourConstructor) {
		int j = 1;
		Behaviour* ptr_testedClassZero = new FuzzyBehaviour(j, j, j);
		FuzzyBehaviour m_testedClassOne = FuzzyBehaviour(j, j, j);

		ptr_testedClassZero->c_nextPlotPoint = int2d(16, 32);
		m_testedClassOne.c_nextPlotPoint = int2d(16, 32);

		Assert::AreEqual(ptr_testedClassZero->c_nextPlotPoint.s_firstInt, m_testedClassOne.c_nextPlotPoint.s_firstInt, L"Different c_nextPlotPoint.s_firstInt Values");
		Assert::AreEqual(ptr_testedClassZero->c_nextPlotPoint.s_secondInt, m_testedClassOne.c_nextPlotPoint.s_secondInt, L"Different c_nextPlotPoint.s_secondInt Values");
	}

	TEST_METHOD(ContextFuzzyEngine) {
		int m_storyHonestyInt = 10;
		int m_playStyleInt = 5;
		int m_playerHostilityInt = 20;

		int m_behaviourInt = 1;

		int m_pleasantriesInt = 1;
		std::string m_tileClassificationString = "";
		

		//	The vast majority of the following tests will confirm the matlab outline/design
		//	low honestyIndex constant >> playstyle and playerHostility variable
		
		m_storyHonestyInt = 20;
		m_playStyleInt = 15;
		m_playerHostilityInt = 10;
		FuzzyBehaviour* ptr_testedClassZero = new FuzzyBehaviour(m_storyHonestyInt, m_playStyleInt, m_playerHostilityInt);
		Assert::AreEqual(45.0f, ptr_testedClassZero->getBehaviourTesting(), 1.0f, L"Incorrect behaviour from contextEngine");

		m_playerHostilityInt = 25;
		ptr_testedClassZero = new FuzzyBehaviour(m_storyHonestyInt, m_playStyleInt, m_playerHostilityInt);
		Assert::AreEqual(45.0f, ptr_testedClassZero->getBehaviourTesting(), 1.0f, L"Incorrect behaviour from contextEngine");

		m_playerHostilityInt = 50;
		ptr_testedClassZero = new FuzzyBehaviour(m_storyHonestyInt, m_playStyleInt, m_playerHostilityInt);
		Assert::AreEqual(15.0f, ptr_testedClassZero->getBehaviourTesting(), 1.0f, L"Incorrect behaviour from contextEngine");

		m_playerHostilityInt = 65;
		ptr_testedClassZero = new FuzzyBehaviour(m_storyHonestyInt, m_playStyleInt, m_playerHostilityInt);
		Assert::AreEqual(15.0f, ptr_testedClassZero->getBehaviourTesting(), 1.0f, L"Incorrect behaviour from contextEngine");

		m_playerHostilityInt = 90;
		ptr_testedClassZero = new FuzzyBehaviour(m_storyHonestyInt, m_playStyleInt, m_playerHostilityInt);
		Assert::AreEqual(75.0f, ptr_testedClassZero->getBehaviourTesting(), 1.0f, L"Incorrect behaviour from contextEngine");
		
		m_playStyleInt = 40;
		m_playerHostilityInt = 10;
		ptr_testedClassZero = new FuzzyBehaviour(m_storyHonestyInt, m_playStyleInt, m_playerHostilityInt);
		Assert::AreEqual(45, ptr_testedClassZero->getBehaviourTesting(), 1.0f, L"Incorrect behaviour from contextEngine");

		m_playerHostilityInt = 25;
		ptr_testedClassZero = new FuzzyBehaviour(m_storyHonestyInt, m_playStyleInt, m_playerHostilityInt);
		Assert::AreEqual(45.0f, ptr_testedClassZero->getBehaviourTesting(), 1.0f, L"Incorrect behaviour from contextEngine");

		m_playerHostilityInt = 50;
		ptr_testedClassZero = new FuzzyBehaviour(m_storyHonestyInt, m_playStyleInt, m_playerHostilityInt);
		Assert::AreEqual(15.0f, ptr_testedClassZero->getBehaviourTesting(), 1.0f, L"Incorrect behaviour from contextEngine");

		m_playerHostilityInt = 65;
		ptr_testedClassZero = new FuzzyBehaviour(m_storyHonestyInt, m_playStyleInt, m_playerHostilityInt);
		Assert::AreEqual(15.0f, ptr_testedClassZero->getBehaviourTesting(), 1.0f, L"Incorrect behaviour from contextEngine");

		m_playerHostilityInt = 90;
		ptr_testedClassZero = new FuzzyBehaviour(m_storyHonestyInt, m_playStyleInt, m_playerHostilityInt);
		Assert::AreEqual(75.0f, ptr_testedClassZero->getBehaviourTesting(), 1.0f, L"Incorrect behaviour from contextEngine");

		m_playStyleInt = 80;
		m_playerHostilityInt = 10;
		ptr_testedClassZero = new FuzzyBehaviour(m_storyHonestyInt, m_playStyleInt, m_playerHostilityInt);
		Assert::AreEqual(45.0f, ptr_testedClassZero->getBehaviourTesting(), 1.0f, L"Incorrect behaviour from contextEngine");

		m_playerHostilityInt = 25;
		ptr_testedClassZero = new FuzzyBehaviour(m_storyHonestyInt, m_playStyleInt, m_playerHostilityInt);
		Assert::AreEqual(45.0f, ptr_testedClassZero->getBehaviourTesting(), 1.0f, L"Incorrect behaviour from contextEngine");

		m_playerHostilityInt = 50;
		ptr_testedClassZero = new FuzzyBehaviour(m_storyHonestyInt, m_playStyleInt, m_playerHostilityInt);
		Assert::AreEqual(15.0f, ptr_testedClassZero->getBehaviourTesting(), 1.0f, L"Incorrect behaviour from contextEngine");

		m_playerHostilityInt = 65;
		ptr_testedClassZero = new FuzzyBehaviour(m_storyHonestyInt, m_playStyleInt, m_playerHostilityInt);
		Assert::AreEqual(15.0f, ptr_testedClassZero->getBehaviourTesting(), 1.0f, L"Incorrect behaviour from contextEngine");

		m_playerHostilityInt = 90;
		ptr_testedClassZero = new FuzzyBehaviour(m_storyHonestyInt, m_playStyleInt, m_playerHostilityInt);
		Assert::AreEqual(75.0f, ptr_testedClassZero->getBehaviourTesting(), 1.0f, L"Incorrect behaviour from contextEngine");

		//	medium honestyIndex constant >> playstyle and playerHostility variable

		m_storyHonestyInt = 45;
		m_playStyleInt = 15;
		m_playerHostilityInt = 10;
		ptr_testedClassZero = new FuzzyBehaviour(m_storyHonestyInt, m_playStyleInt, m_playerHostilityInt);
		Assert::AreEqual(45.0f, ptr_testedClassZero->getBehaviourTesting(), 1.0f, L"Incorrect behaviour from contextEngine");

		m_playerHostilityInt = 25;
		ptr_testedClassZero = new FuzzyBehaviour(m_storyHonestyInt, m_playStyleInt, m_playerHostilityInt);
		Assert::AreEqual(15.0f, ptr_testedClassZero->getBehaviourTesting(), 1.0f, L"Incorrect behaviour from contextEngine");

		m_playerHostilityInt = 50;
		ptr_testedClassZero = new FuzzyBehaviour(m_storyHonestyInt, m_playStyleInt, m_playerHostilityInt);
		Assert::AreEqual(15.0f, ptr_testedClassZero->getBehaviourTesting(), 1.0f, L"Incorrect behaviour from contextEngine");

		m_playerHostilityInt = 65;
		ptr_testedClassZero = new FuzzyBehaviour(m_storyHonestyInt, m_playStyleInt, m_playerHostilityInt);
		Assert::AreEqual(15.0f, ptr_testedClassZero->getBehaviourTesting(), 1.0f, L"Incorrect behaviour from contextEngine");

		m_playerHostilityInt = 90;
		ptr_testedClassZero = new FuzzyBehaviour(m_storyHonestyInt, m_playStyleInt, m_playerHostilityInt);
		Assert::AreEqual(75.0f, ptr_testedClassZero->getBehaviourTesting(), 1.0f, L"Incorrect behaviour from contextEngine");

		m_playStyleInt = 40;
		m_playerHostilityInt = 10;
		ptr_testedClassZero = new FuzzyBehaviour(m_storyHonestyInt, m_playStyleInt, m_playerHostilityInt);
		Assert::AreEqual(45.0f, ptr_testedClassZero->getBehaviourTesting(), 1.0f, L"Incorrect behaviour from contextEngine");

		m_playerHostilityInt = 25;
		ptr_testedClassZero = new FuzzyBehaviour(m_storyHonestyInt, m_playStyleInt, m_playerHostilityInt);
		Assert::AreEqual(15.0f, ptr_testedClassZero->getBehaviourTesting(), 1.0f, L"Incorrect behaviour from contextEngine");

		m_playerHostilityInt = 50;
		ptr_testedClassZero = new FuzzyBehaviour(m_storyHonestyInt, m_playStyleInt, m_playerHostilityInt);
		Assert::AreEqual(15.0f, ptr_testedClassZero->getBehaviourTesting(), 1.0f, L"Incorrect behaviour from contextEngine");

		m_playerHostilityInt = 65;
		ptr_testedClassZero = new FuzzyBehaviour(m_storyHonestyInt, m_playStyleInt, m_playerHostilityInt);
		Assert::AreEqual(75.0f, ptr_testedClassZero->getBehaviourTesting(), 1.0f, L"Incorrect behaviour from contextEngine");

		m_playerHostilityInt = 90;
		ptr_testedClassZero = new FuzzyBehaviour(m_storyHonestyInt, m_playStyleInt, m_playerHostilityInt);
		Assert::AreEqual(75.0f, ptr_testedClassZero->getBehaviourTesting(), 1.0f, L"Incorrect behaviour from contextEngine");

		m_playStyleInt = 80;
		m_playerHostilityInt = 10;
		ptr_testedClassZero = new FuzzyBehaviour(m_storyHonestyInt, m_playStyleInt, m_playerHostilityInt);
		Assert::AreEqual(45.0f, ptr_testedClassZero->getBehaviourTesting(), 1.0f, L"Incorrect behaviour from contextEngine");

		m_playerHostilityInt = 25;
		ptr_testedClassZero = new FuzzyBehaviour(m_storyHonestyInt, m_playStyleInt, m_playerHostilityInt);
		Assert::AreEqual(15.0f, ptr_testedClassZero->getBehaviourTesting(), 1.0f, L"Incorrect behaviour from contextEngine");

		m_playerHostilityInt = 50;
		ptr_testedClassZero = new FuzzyBehaviour(m_storyHonestyInt, m_playStyleInt, m_playerHostilityInt);
		Assert::AreEqual(15.0f, ptr_testedClassZero->getBehaviourTesting(), 1.0f, L"Incorrect behaviour from contextEngine");

		m_playerHostilityInt = 65;
		ptr_testedClassZero = new FuzzyBehaviour(m_storyHonestyInt, m_playStyleInt, m_playerHostilityInt);
		Assert::AreEqual(75.0f, ptr_testedClassZero->getBehaviourTesting(), 1.0f, L"Incorrect behaviour from contextEngine");

		m_playerHostilityInt = 90;
		ptr_testedClassZero = new FuzzyBehaviour(m_storyHonestyInt, m_playStyleInt, m_playerHostilityInt);
		Assert::AreEqual(75.0f, ptr_testedClassZero->getBehaviourTesting(), 1.0f, L"Incorrect behaviour from contextEngine");

		//	high honestyIndex constant >> playstyle and playerHostility variable

		m_storyHonestyInt = 80;
		m_playStyleInt = 15;
		m_playerHostilityInt = 10;
		ptr_testedClassZero = new FuzzyBehaviour(m_storyHonestyInt, m_playStyleInt, m_playerHostilityInt);
		Assert::AreEqual(45.0f, ptr_testedClassZero->getBehaviourTesting(), 1.0f, L"Incorrect behaviour from contextEngine");

		m_playerHostilityInt = 25;
		ptr_testedClassZero = new FuzzyBehaviour(m_storyHonestyInt, m_playStyleInt, m_playerHostilityInt);
		Assert::AreEqual(45.0f, ptr_testedClassZero->getBehaviourTesting(), 1.0f, L"Incorrect behaviour from contextEngine");

		m_playerHostilityInt = 50;
		ptr_testedClassZero = new FuzzyBehaviour(m_storyHonestyInt, m_playStyleInt, m_playerHostilityInt);
		Assert::AreEqual(15.0f, ptr_testedClassZero->getBehaviourTesting(), 1.0f, L"Incorrect behaviour from contextEngine");

		m_playerHostilityInt = 65;
		ptr_testedClassZero = new FuzzyBehaviour(m_storyHonestyInt, m_playStyleInt, m_playerHostilityInt);
		Assert::AreEqual(15.0f, ptr_testedClassZero->getBehaviourTesting(), 1.0f, L"Incorrect behaviour from contextEngine");

		m_playerHostilityInt = 90;
		ptr_testedClassZero = new FuzzyBehaviour(m_storyHonestyInt, m_playStyleInt, m_playerHostilityInt);
		Assert::AreEqual(75.0f, ptr_testedClassZero->getBehaviourTesting(), 1.0f, L"Incorrect behaviour from contextEngine");

		m_playStyleInt = 40;
		m_playerHostilityInt = 10;
		ptr_testedClassZero = new FuzzyBehaviour(m_storyHonestyInt, m_playStyleInt, m_playerHostilityInt);
		Assert::AreEqual(45.0f, ptr_testedClassZero->getBehaviourTesting(), 1.0f, L"Incorrect behaviour from contextEngine");

		m_playerHostilityInt = 25;
		ptr_testedClassZero = new FuzzyBehaviour(m_storyHonestyInt, m_playStyleInt, m_playerHostilityInt);
		Assert::AreEqual(45.0f, ptr_testedClassZero->getBehaviourTesting(), 1.0f, L"Incorrect behaviour from contextEngine");

		m_playerHostilityInt = 50;
		ptr_testedClassZero = new FuzzyBehaviour(m_storyHonestyInt, m_playStyleInt, m_playerHostilityInt);
		Assert::AreEqual(15.0f, ptr_testedClassZero->getBehaviourTesting(), 1.0f, L"Incorrect behaviour from contextEngine");

		m_playerHostilityInt = 65;
		ptr_testedClassZero = new FuzzyBehaviour(m_storyHonestyInt, m_playStyleInt, m_playerHostilityInt);
		Assert::AreEqual(15.0f, ptr_testedClassZero->getBehaviourTesting(), 1.0f, L"Incorrect behaviour from contextEngine");

		m_playerHostilityInt = 90;
		ptr_testedClassZero = new FuzzyBehaviour(m_storyHonestyInt, m_playStyleInt, m_playerHostilityInt);
		Assert::AreEqual(75.0f, ptr_testedClassZero->getBehaviourTesting(), 1.0f, L"Incorrect behaviour from contextEngine");

		m_playStyleInt = 80;
		m_playerHostilityInt = 10;
		ptr_testedClassZero = new FuzzyBehaviour(m_storyHonestyInt, m_playStyleInt, m_playerHostilityInt);
		Assert::AreEqual(45.0f, ptr_testedClassZero->getBehaviourTesting(), 1.0f, L"Incorrect behaviour from contextEngine");

		m_playerHostilityInt = 25;
		ptr_testedClassZero = new FuzzyBehaviour(m_storyHonestyInt, m_playStyleInt, m_playerHostilityInt);
		Assert::AreEqual(45.0f, ptr_testedClassZero->getBehaviourTesting(), 1.0f, L"Incorrect behaviour from contextEngine");

		m_playerHostilityInt = 50;
		ptr_testedClassZero = new FuzzyBehaviour(m_storyHonestyInt, m_playStyleInt, m_playerHostilityInt);
		Assert::AreEqual(15.0f, ptr_testedClassZero->getBehaviourTesting(), 1.0f, L"Incorrect behaviour from contextEngine");

		m_playerHostilityInt = 65;
		ptr_testedClassZero = new FuzzyBehaviour(m_storyHonestyInt, m_playStyleInt, m_playerHostilityInt);
		Assert::AreEqual(15.0f, ptr_testedClassZero->getBehaviourTesting(), 1.0f, L"Incorrect behaviour from contextEngine");

		m_playerHostilityInt = 90;
		ptr_testedClassZero = new FuzzyBehaviour(m_storyHonestyInt, m_playStyleInt, m_playerHostilityInt);
		Assert::AreEqual(75.0f, ptr_testedClassZero->getBehaviourTesting(), 1.0f, L"Incorrect behaviour from contextEngine");

	}

	TEST_METHOD(InteractionFuzzyEngine) {

		//	The vast majority of the following tests will confirm the matlab outline/design
		//	honestUnreliable behaviour constant >> pleasantries and classification variable
		int m_storyHonestyInt = 20;
		int m_playStyleInt = 15;
		int m_playerHostilityInt = 50;
		FuzzyBehaviour* ptr_testedClassZero = new FuzzyBehaviour(m_storyHonestyInt, m_playStyleInt, m_playerHostilityInt);
		ptr_testedClassZero->interactionProcessTesting(10, "acceptable");
		Assert::AreEqual(75.0f, ptr_testedClassZero->getMagnitudeTesting(), 1.0f, L"HonestReliable + 2 + acceptable != 75");
		ptr_testedClassZero->interactionProcessTesting(25, "acceptable");
		Assert::AreEqual(75.0f, ptr_testedClassZero->getMagnitudeTesting(), 1.0f, L"HonestReliable + 5 + acceptable != 75");
		ptr_testedClassZero->interactionProcessTesting(45, "acceptable");
		Assert::AreEqual(45.0f, ptr_testedClassZero->getMagnitudeTesting(), 1.0f, L"HonestReliable + 9 + acceptable != 45");
		ptr_testedClassZero->interactionProcessTesting(65, "acceptable");
		Assert::AreEqual(45.0f, ptr_testedClassZero->getMagnitudeTesting(), 1.0f, L"HonestReliable + 13 + acceptable != 45");
		ptr_testedClassZero->interactionProcessTesting(90, "acceptable");
		Assert::AreEqual(15.0f, ptr_testedClassZero->getMagnitudeTesting(), 1.0f, L"HonestReliable + 17 + acceptable != 15");

		ptr_testedClassZero->interactionProcessTesting(10, "cautious");
		Assert::AreEqual(75.0f, ptr_testedClassZero->getMagnitudeTesting(), 1.0f, L"HonestReliable + 2 + cautious != 75");
		ptr_testedClassZero->interactionProcessTesting(25, "cautious");
		Assert::AreEqual(45.0f, ptr_testedClassZero->getMagnitudeTesting(), 1.0f, L"HonestReliable + 5 + cautious != 45");
		ptr_testedClassZero->interactionProcessTesting(45, "cautious");
		Assert::AreEqual(45.0f, ptr_testedClassZero->getMagnitudeTesting(), 1.0f, L"HonestReliable + 9 + cautious != 45");
		ptr_testedClassZero->interactionProcessTesting(65, "cautious");
		Assert::AreEqual(15.0f, ptr_testedClassZero->getMagnitudeTesting(), 1.0f, L"HonestReliable + 13 + cautious != 15");
		ptr_testedClassZero->interactionProcessTesting(90, "cautious");
		Assert::AreEqual(15.0f, ptr_testedClassZero->getMagnitudeTesting(), 1.0f, L"HonestReliable + 17 + cautious != 15");

		//	honestReliable behaviour constant >> pleasantries and classification variable
		m_storyHonestyInt = 20;
		m_playStyleInt = 15;
		m_playerHostilityInt = 10;
		ptr_testedClassZero = new FuzzyBehaviour(m_storyHonestyInt, m_playStyleInt, m_playerHostilityInt);
		ptr_testedClassZero->interactionProcessTesting(10, "acceptable");
		Assert::AreEqual(15.0f, ptr_testedClassZero->getMagnitudeTesting(), 1.0f, L"HonestUnreliable + 2 + acceptable != 15");
		ptr_testedClassZero->interactionProcessTesting(25, "acceptable");
		Assert::AreEqual(45.0f, ptr_testedClassZero->getMagnitudeTesting(), 1.0f, L"HonestUnreliable + 5 + acceptable != 45");
		ptr_testedClassZero->interactionProcessTesting(45, "acceptable");
		Assert::AreEqual(45.0f, ptr_testedClassZero->getMagnitudeTesting(), 1.0f, L"HonestUnreliable + 9 + acceptable != 45");
		ptr_testedClassZero->interactionProcessTesting(65, "acceptable");
		Assert::AreEqual(75.0f, ptr_testedClassZero->getMagnitudeTesting(), 1.0f, L"HonestUnreliable + 13 + acceptable != 75");
		ptr_testedClassZero->interactionProcessTesting(90, "acceptable");
		Assert::AreEqual(75.0f, ptr_testedClassZero->getMagnitudeTesting(), 1.0f, L"HonestUnreliable + 17 + acceptable != 75");

		ptr_testedClassZero->interactionProcessTesting(10, "cautious");
		Assert::AreEqual(15.0f, ptr_testedClassZero->getMagnitudeTesting(), 1.0f, L"HonestUnreliable + 2 + cautious != 15");
		ptr_testedClassZero->interactionProcessTesting(25, "cautious");
		Assert::AreEqual(15.0f, ptr_testedClassZero->getMagnitudeTesting(), 1.0f, L"HonestUnreliable + 5 + cautious != 15");
		ptr_testedClassZero->interactionProcessTesting(45, "cautious");
		Assert::AreEqual(15.0f, ptr_testedClassZero->getMagnitudeTesting(), 1.0f, L"HonestUnreliable + 9 + cautious != 15");
		ptr_testedClassZero->interactionProcessTesting(65, "cautious");
		Assert::AreEqual(45.0f, ptr_testedClassZero->getMagnitudeTesting(), 1.0f, L"HonestUnreliable + 13 + cautious != 45");
		ptr_testedClassZero->interactionProcessTesting(90, "cautious");
		Assert::AreEqual(45.0f, ptr_testedClassZero->getMagnitudeTesting(), 1.0f, L"HonestUnreliable + 17 + cautious != 45");

		//	dishonestReliable behaviour constant >> pleasantries and classification variable
		m_storyHonestyInt = 20;
		m_playStyleInt = 15;
		m_playerHostilityInt = 90;
		ptr_testedClassZero = new FuzzyBehaviour(m_storyHonestyInt, m_playStyleInt, m_playerHostilityInt);
		ptr_testedClassZero->interactionProcessTesting(10, "acceptable");
		Assert::AreEqual(15.0f, ptr_testedClassZero->getMagnitudeTesting(), 1.0f, L"DishonestReliable + 2 + acceptable != 15");
		ptr_testedClassZero->interactionProcessTesting(25, "acceptable");
		Assert::AreEqual(15.0f, ptr_testedClassZero->getMagnitudeTesting(), 1.0f, L"DishonestReliable + 5 + acceptable != 15");
		ptr_testedClassZero->interactionProcessTesting(45, "acceptable");
		Assert::AreEqual(45.0f, ptr_testedClassZero->getMagnitudeTesting(), 1.0f, L"DishonestReliable + 9 + acceptable != 45");
		ptr_testedClassZero->interactionProcessTesting(65, "acceptable");
		Assert::AreEqual(45.0f, ptr_testedClassZero->getMagnitudeTesting(), 1.0f, L"DishonestReliable + 13 + acceptable != 45");
		ptr_testedClassZero->interactionProcessTesting(90, "acceptable");
		Assert::AreEqual(75.0f, ptr_testedClassZero->getMagnitudeTesting(), 1.0f, L"DishonestReliable + 17 + acceptable != 75");

		ptr_testedClassZero->interactionProcessTesting(10, "cautious");
		Assert::AreEqual(45.0f, ptr_testedClassZero->getMagnitudeTesting(), 1.0f, L"DishonestReliable + 2 + cautious != 45");
		ptr_testedClassZero->interactionProcessTesting(25, "cautious");
		Assert::AreEqual(45.0f, ptr_testedClassZero->getMagnitudeTesting(), 1.0f, L"DishonestReliable + 5 + cautious != 45");
		ptr_testedClassZero->interactionProcessTesting(45, "cautious");
		Assert::AreEqual(75.0f, ptr_testedClassZero->getMagnitudeTesting(), 1.0f, L"DishonestReliable + 9 + cautious != 75");
		ptr_testedClassZero->interactionProcessTesting(65, "cautious");
		Assert::AreEqual(75.0f, ptr_testedClassZero->getMagnitudeTesting(), 1.0f, L"DishonestReliable + 13 + cautious != 75");
		ptr_testedClassZero->interactionProcessTesting(90, "cautious");
		Assert::AreEqual(75.0f, ptr_testedClassZero->getMagnitudeTesting(), 1.0f, L"DishonestReliable + 17 + cautious != 75");

	}

	};
}