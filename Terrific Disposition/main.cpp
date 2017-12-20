
#include "SFML_Window.h"
#include "GameLogic.h"

#include <iostream>
#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include <string>

void main() {
	
	int errorCodeInt = 0;
	int countInt = 0;
	const int fixedUpdateIntervalInt = 3;

	SFML_Window* gameWindow = new SFML_Window();
	GameLogic* terrificDispositionGameLogic = new GameLogic();

	gameWindow->linkGameLogic(terrificDispositionGameLogic);
	
	bool gameRunningBool = true;
	while (gameRunningBool)	{

		if (errorCodeInt == 0) errorCodeInt = terrificDispositionGameLogic->Update();
		if (errorCodeInt == 0) errorCodeInt = gameWindow->Update();
		

				
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
			delete gameWindow;
		}

		
	}


}