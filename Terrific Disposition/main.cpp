
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

}