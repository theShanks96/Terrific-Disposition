
#include "SFML_Window.h"
#include "GameLogic.h"

#include <iostream>
#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include <string>

#include <fuzzylite\Headers.h>
#include "FuzzyBehaviour.h"

#include "ResourceManager.h"
#include "NaturalLogicManager.h"

#include "AcceptableTile.h"
#include "CautiousTile.h"
#include "DeadlyTile.h"

void main() {
	
	int errorCodeInt = 0;

	SFML_Window* ptr_terrificDispositionGameWindow = new SFML_Window();
	//GameLogic* ptr_terrificDispositionGameLogic = new GameLogic();

	//ptr_terrificDispositionGameWindow->linkGameLogic(ptr_terrificDispositionGameLogic);
	
	bool gameRunningBool = true;
	while (gameRunningBool)	{

		//if (errorCodeInt == 0) errorCodeInt = ptr_terrificDispositionGameLogic->Update();
		if (errorCodeInt == 0) errorCodeInt = ptr_terrificDispositionGameWindow->Update();
		

				
		if (errorCodeInt == 0) {
			//	No error, log this
		}
		else if (errorCodeInt == 1) {
			//	No error, just clicked the close button on the top-right, log this
			gameRunningBool = false;
		}
		else {
			//	Reaches here if an error is found
			//	Use the log to record the error
			delete ptr_terrificDispositionGameWindow;
		}

		
	}
	
	/*
	ResourceManager* ptr_resourceManager = new ResourceManager("../Assets/AssetConfiguration.json");
	saveProfile m_save = ptr_resourceManager->loadSavefile("TestName");

	std::cout << "name: " + m_save.s_playerName << std::endl;
	std::cout << "health: " + std::to_string(m_save.s_playerHealth) << std::endl;

	std::cout << "current location: (" + std::to_string(m_save.s_playerCurrentLocation.s_firstInt) + "," + std::to_string(m_save.s_playerCurrentLocation.s_secondInt) + ")" << std::endl;
	std::cout << "start location: (" + std::to_string(m_save.s_playerStartLocation.s_firstInt) + "," + std::to_string(m_save.s_playerStartLocation.s_secondInt ) + ")" << std::endl;

	std::cout << "interactions: " + std::to_string(m_save.s_interactionsInt) << std::endl;
	std::cout << "hostility: " + std::to_string(m_save.s_hostilityInt) << std::endl;
	std::cout << "recent pleasantry: " + std::to_string(m_save.s_recentPleasantryInt) << std::endl;
	std::cout << "total interaction words: " + std::to_string(m_save.s_totalInteractionWordsInt) << std::endl;

	std::cout << "play style: " + std::to_string(m_save.s_playStyle) << std::endl;
	std::cout << "inventory items" << std::endl;
	for (int i = 0; i < m_save.v_playerInventory.size(); i++) {
		std::cout << "item " + std::to_string(i) + " " + m_save.v_playerInventory.at(i).s_nameString + ": " + m_save.v_playerInventory.at(i).s_titleString + "[" + m_save.v_playerInventory.at(i).s_qualityString + "]" + m_save.v_playerInventory.at(i).s_bodyString << std::endl;
	}
	std::cout << "player head: " + m_save.s_playerHeadAttire << std::endl;
	std::cout << "player torso: " + m_save.s_playerTorsoAttire << std::endl;
	std::cout << "player equipment: " + m_save.s_playerEquipment << std::endl;

	std::cout << "map size: " + std::to_string(m_save.s_mapSize) << std::endl;
	std::cout << "theme: " + m_save.s_worldTheme << std::endl;
	std::cout << "plot points" << std::endl;
	for (int i = 0; i < m_save.v_plotPoints.size(); i++) {
		std::cout << "plot " + std::to_string(i) + ": (" + std::to_string(m_save.v_plotPoints.at(i).s_firstInt) + "," + std::to_string(m_save.v_plotPoints.at(i).s_secondInt) + ")"<< std::endl;
	}

	std::cout << "honest reliable: " + std::to_string(m_save.s_totalHonestReliableInt) << std::endl;
	std::cout << "honest unreliable: " + std::to_string(m_save.s_totalHonestUnreliableInt) << std::endl;
	std::cout << "dishonest reliable: " + std::to_string(m_save.s_totalDishonestReliableInt) << std::endl;
	*/


	/*
	ResourceManager* ptr_resourceManager = new ResourceManager("../Assets/AssetConfiguration.json");
	ptr_resourceManager->loadThematicDictionaries("cyberpunk");

	NaturalLogicManager* ptr_naturalLogicManager = new NaturalLogicManager(ptr_resourceManager);

	std::string m_temp = ptr_naturalLogicManager->nltkDictionaryDefinition("badge");
	std::cout << m_temp << std::endl;
	m_temp = ptr_naturalLogicManager->nltkDictionaryDefinition("chombatta");
	std::cout << m_temp << std::endl;
	m_temp = ptr_naturalLogicManager->nltkDictionaryDefinition("roust");
	std::cout << m_temp << std::endl;
	*/

}