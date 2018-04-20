#include "stdafx.h"
#include "CppUnitTest.h"

#include "../Terrific Disposition/ResourceManager.h"
#include "../Terrific Disposition/NaturalLogicManager.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TerrificTesting {
	TEST_CLASS(ResourceManagerTests) {
public:

	TEST_METHOD(ResourceManagerConstructor) {

		ResourceManager* ptr_resourceManager = new ResourceManager("../../../Assets/AssetConfigurationTesting.json");

		Assert::AreNotEqual(0, (int)ptr_resourceManager->v_vulgarities.size(), L"Vulgarities not properly loaded");

		Assert::AreNotEqual(0, (int)ptr_resourceManager->v_hostileAdjectives.size(), L"Hostile Adjective not properly loaded");
		Assert::AreNotEqual(0, (int)ptr_resourceManager->v_hostileNouns.size(), L"Hostile Nouns not properly loaded");
		Assert::AreNotEqual(0, (int)ptr_resourceManager->v_hostileVerbs.size(), L"Hostile Verbs not properly loaded");

		Assert::AreNotEqual(0, (int)ptr_resourceManager->v_pleasantAdjectives.size(), L"Pleasant Adjectives not properly loaded");
		Assert::AreNotEqual(0, (int)ptr_resourceManager->v_pleasantNouns.size(), L"Pleasant Nouns not properly loaded");
		Assert::AreNotEqual(0, (int)ptr_resourceManager->v_pleasantVerbs.size(), L"Pleasant Verbs not properly loaded");
	}

	TEST_METHOD(LoadingThematicDictionaries) {

		ResourceManager* ptr_resourceManager = new ResourceManager("../../../Assets/AssetConfigurationTesting.json");
		ptr_resourceManager->loadThematicDictionaries("cyberpunk");

		int m_expectedSizeInt = 3;
		
		Assert::AreEqual(m_expectedSizeInt, (int)ptr_resourceManager->v_thematicNegativeAdjectives.size(), L"Incorrect number of negative adjectives");
		Assert::AreEqual(m_expectedSizeInt, (int)ptr_resourceManager->v_thematicPositiveAdjectives.size(), L"Incorrect number of positive adjectives");

		Assert::AreEqual(m_expectedSizeInt, (int)ptr_resourceManager->v_thematicNegativeVerbs.size(), L"Incorrect number of negative verbs");
		Assert::AreEqual(m_expectedSizeInt, (int)ptr_resourceManager->v_thematicPositiveVerbs.size(), L"Incorrect number of positive verbs");

		Assert::AreEqual(m_expectedSizeInt, (int)ptr_resourceManager->v_thematicNegativeObjectNouns.size(), L"Incorrect number of object negative nouns");
		Assert::AreEqual(m_expectedSizeInt, (int)ptr_resourceManager->v_thematicPositivePersonNouns.size(), L"Incorrect number of person positive nouns");
		Assert::AreEqual(m_expectedSizeInt, (int)ptr_resourceManager->v_thematicNegativeObjectNouns.size(), L"Incorrect number of object positive nouns");
		Assert::AreEqual(m_expectedSizeInt, (int)ptr_resourceManager->v_thematicPositivePersonNouns.size(), L"Incorrect number of person negative nouns");
	}

	};

	TEST_CLASS(NaturalLogicManagerTests) {
public:

	TEST_METHOD(NaturalLogicManagerConstructor) {
		ResourceManager* ptr_resourceManager = new ResourceManager("../../../Assets/AssetConfigurationTesting.json");
		NaturalLogicManager* ptr_naturalLogicManager = new NaturalLogicManager(ptr_resourceManager);

		Assert::AreEqual(16, ptr_naturalLogicManager->c_vectorCapacityInt, L"NaturalLogicManager not correctly initialised");
		ptr_naturalLogicManager->~NaturalLogicManager();
		delete ptr_naturalLogicManager;
	}

	TEST_METHOD(NLTKEntryProcessing) {
		ResourceManager* ptr_resourceManager = new ResourceManager("../../../Assets/AssetConfigurationTesting.json");
		NaturalLogicManager* ptr_naturalLogicManager = new NaturalLogicManager(ptr_resourceManager);
		
		std::string m_stringTested = "Chocolate milk is delicious";
		commandProfile m_nltkTestResult = ptr_naturalLogicManager->nltkEntryProcessing(m_stringTested);
		Assert::AreEqual(1, m_nltkTestResult.s_adjectivesInt, L"Incorrect adjective count");
		Assert::AreEqual(2, m_nltkTestResult.s_nounsInt, L"Incorrect noun count");
		Assert::AreEqual(1, m_nltkTestResult.s_verbsInt, L"Incorrect verb count");

		m_stringTested = "Spicy peppers give food a nice kick";
		m_nltkTestResult = ptr_naturalLogicManager->nltkEntryProcessing(m_stringTested);
		Assert::AreEqual(1, m_nltkTestResult.s_adjectivesInt, L"Incorrect adjective count");
		Assert::AreEqual(4, m_nltkTestResult.s_nounsInt, L"Incorrect noun count");
		Assert::AreEqual(1, m_nltkTestResult.s_verbsInt, L"Incorrect verb count");

		ptr_naturalLogicManager->~NaturalLogicManager();
		delete ptr_naturalLogicManager;
	}

	};

}