#include "SFML_Window.h"

#include <iostream>

SFML_Window::SFML_Window() {

	c_textCascadingInt = 0;

	//!	SFML Identifies the screen's resolution.
	sf::VideoMode mode = sf::VideoMode::getDesktopMode();
	//!	This information is then used to dictate the size of the display.
	c_windowWidthInt = (int)(3 * mode.width / 4);	
	c_windowHeightInt = (int)(2 * mode.height / 3);
	c_windowUnitInt = (int)(c_windowHeightInt / 100);

	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	ptr_gameRenderWindow = new sf::RenderWindow(sf::VideoMode(c_windowWidthInt, c_windowHeightInt), "Terrific Disposition: Procedural Storyline Generation", sf::Style::Default, settings);
	ptr_gameRenderWindow->setFramerateLimit(30);
	
	arr_foregroundColours[0] = sf::Color(220, 221, 225);
	arr_foregroundColours[1] = sf::Color(192, 57, 43);
	arr_foregroundColours[2] = sf::Color(22, 160, 133);
	arr_foregroundColours[3] = sf::Color(84, 160, 255);

	arr_backgroundColours[0] = sf::Color(47, 54, 64);
	arr_backgroundColours[1] = sf::Color(44, 44, 84);
	arr_backgroundColours[2] = sf::Color(44, 62, 80);
	arr_backgroundColours[3] = sf::Color(48, 57, 82);

	c_foregroundIndexInt = 0;
	c_backgroundIndexInt = 0;

	arr_displayFraming[const_journalIndexInt] = sf::RectangleShape(sf::Vector2f((c_windowWidthInt * 0.3) - c_windowUnitInt, (c_windowHeightInt * 0.6) - c_windowUnitInt));
	arr_displayFraming[const_journalIndexInt].setPosition(sf::Vector2f(0 + c_windowUnitInt, 0 + c_windowUnitInt));
	arr_displayFraming[const_journalIndexInt].setFillColor(arr_backgroundColours[c_backgroundIndexInt]);
	arr_displayFraming[const_journalIndexInt].setOutlineColor(arr_foregroundColours[c_foregroundIndexInt]);
	arr_displayFraming[const_journalIndexInt].setOutlineThickness(c_windowUnitInt);

	arr_displayFraming[const_noteIndexInt] = sf::RectangleShape(sf::Vector2f((c_windowWidthInt * 0.3) - c_windowUnitInt, (c_windowHeightInt * 0.4)));
	arr_displayFraming[const_noteIndexInt].setPosition(sf::Vector2f(0 + c_windowUnitInt, (c_windowHeightInt * 0.6) - c_windowUnitInt));
	arr_displayFraming[const_noteIndexInt].setFillColor(arr_backgroundColours[c_backgroundIndexInt]);
	arr_displayFraming[const_noteIndexInt].setOutlineColor(arr_foregroundColours[c_foregroundIndexInt]);
	arr_displayFraming[const_noteIndexInt].setOutlineThickness(c_windowUnitInt);

	arr_displayFraming[const_outputIndexInt] = sf::RectangleShape(sf::Vector2f((c_windowWidthInt * 0.7), (c_windowHeightInt * 0.6)));
	arr_displayFraming[const_outputIndexInt].setPosition(sf::Vector2f((c_windowWidthInt * 0.3) - c_windowUnitInt, 0 + c_windowUnitInt));
	arr_displayFraming[const_outputIndexInt].setFillColor(arr_backgroundColours[c_backgroundIndexInt]);
	arr_displayFraming[const_outputIndexInt].setOutlineColor(arr_foregroundColours[c_foregroundIndexInt]);
	arr_displayFraming[const_outputIndexInt].setOutlineThickness(c_windowUnitInt);

	arr_displayFraming[const_commandIndexInt] = sf::RectangleShape(sf::Vector2f((c_windowWidthInt * 0.7), (c_windowHeightInt * 0.4)));
	arr_displayFraming[const_commandIndexInt].setPosition(sf::Vector2f((c_windowWidthInt * 0.3) - c_windowUnitInt, (c_windowHeightInt * 0.6) - c_windowUnitInt));
	arr_displayFraming[const_commandIndexInt].setFillColor(arr_backgroundColours[c_backgroundIndexInt]);
	arr_displayFraming[const_commandIndexInt].setOutlineColor(arr_foregroundColours[c_foregroundIndexInt]);
	arr_displayFraming[const_commandIndexInt].setOutlineThickness(c_windowUnitInt);

	if (!c_activeFont.loadFromFile("../Assets/Fonts/Dosis-SemiBold.ttf"))
		c_errorCodeInt = 100;

	v_outputDisplays.push_back(sf::Text(">Output", c_activeFont, (int)(c_windowUnitInt * 3)));
	v_outputDisplays.back().setFillColor(arr_foregroundColours[c_foregroundIndexInt]);

	v_commandDisplays.push_back(sf::Text(">", c_activeFont, (int)(c_windowUnitInt * 3)));
	v_commandDisplays.back().setFillColor(arr_foregroundColours[c_foregroundIndexInt]);

	v_noteDisplays.push_back(sf::Text(">Notes", c_activeFont, (int)(c_windowUnitInt * 3)));
	v_noteDisplays.back().setFillColor(arr_foregroundColours[c_foregroundIndexInt]);

	v_journalDisplays.push_back(sf::Text(">Journal", c_activeFont, (int)(c_windowUnitInt * 3)));
	v_journalDisplays.back().setFillColor(arr_foregroundColours[c_foregroundIndexInt]);



	ptr_gameLogic = new GameLogic();

}
SFML_Window::~SFML_Window() {

	c_errorCodeInt = 0;
}

void SFML_Window::linkGameLogic(GameLogic* logic_in) {
	this->ptr_gameLogic = logic_in;
}

int SFML_Window::Update() {
	if (c_errorCodeInt == 0) {
		
		sf::Event event;
		while (ptr_gameRenderWindow->pollEvent(event))	{
			
			while (ptr_gameLogic->v_pendingOutputStrings.size() > 0) {
				if (ptr_gameLogic->v_pendingOutputStrings.front().compare(0, 22, "You remember going by ") == 0) {

					v_outputDisplays.clear();

					addJournalText("Name: " + ptr_gameLogic->ptr_player->c_nameString);
					addJournalText("Head: " + ptr_gameLogic->ptr_player->c_attireHeadString);
					addJournalText("Torso: " + ptr_gameLogic->ptr_player->c_attireTorsoString);
					addJournalText("Equipment: " + ptr_gameLogic->ptr_player->c_equipmentString);

				}
				if (ptr_gameLogic->v_pendingOutputStrings.front().find("you've left the hideout and your journey begins") != std::string::npos) {
					addJournalText("Position: " + std::to_string(ptr_gameLogic->ptr_player->c_positionInt2d.s_firstInt) + "," + std::to_string(ptr_gameLogic->ptr_player->c_positionInt2d.s_secondInt));
				}
				if (ptr_gameLogic->v_pendingOutputStrings.front().find("Loading Successful: Welcome back ") != std::string::npos) {
					addJournalText("Name: " + ptr_gameLogic->ptr_player->c_nameString);
					addJournalText("Head: " + ptr_gameLogic->ptr_player->c_attireHeadString);
					addJournalText("Torso: " + ptr_gameLogic->ptr_player->c_attireTorsoString);
					addJournalText("Equipment: " + ptr_gameLogic->ptr_player->c_equipmentString);
					addJournalText("Position: " + std::to_string(ptr_gameLogic->ptr_player->c_positionInt2d.s_firstInt) + "," + std::to_string(ptr_gameLogic->ptr_player->c_positionInt2d.s_secondInt));

				}
				addOutputText(ptr_gameLogic->v_pendingOutputStrings.front());
				ptr_gameLogic->v_pendingOutputStrings.erase(ptr_gameLogic->v_pendingOutputStrings.begin());
			
			}

			switch (event.type) {

			case sf::Event::Closed:
				ptr_gameRenderWindow->close();
				c_errorCodeInt = 1;
				break;

			case sf::Event::MouseButtonPressed:
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
					if (c_backgroundIndexInt == 3) {

						c_foregroundIndexInt = 0;
						c_backgroundIndexInt = 0;

					}
					else {
						c_foregroundIndexInt++;
						c_backgroundIndexInt++;

					}
				}

				else if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
					if (c_backgroundIndexInt == 0) {
						c_foregroundIndexInt = 3;
						c_backgroundIndexInt = 3;
					}
					else {
						c_foregroundIndexInt--;
						c_backgroundIndexInt--;

					}
				}

				arr_displayFraming[const_journalIndexInt].setFillColor(arr_backgroundColours[c_backgroundIndexInt]);
				arr_displayFraming[const_journalIndexInt].setOutlineColor(arr_foregroundColours[c_foregroundIndexInt]);
				arr_displayFraming[const_noteIndexInt].setFillColor(arr_backgroundColours[c_backgroundIndexInt]);
				arr_displayFraming[const_noteIndexInt].setOutlineColor(arr_foregroundColours[c_foregroundIndexInt]);
				arr_displayFraming[const_outputIndexInt].setFillColor(arr_backgroundColours[c_backgroundIndexInt]);
				arr_displayFraming[const_outputIndexInt].setOutlineColor(arr_foregroundColours[c_foregroundIndexInt]);
				arr_displayFraming[const_commandIndexInt].setFillColor(arr_backgroundColours[c_backgroundIndexInt]);
				arr_displayFraming[const_commandIndexInt].setOutlineColor(arr_foregroundColours[c_foregroundIndexInt]);
						
				break;
				
			case sf::Event::TextEntered:
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace) && c_entryString.size() > 1) {
					c_entryString = v_commandDisplays.back().getString();
					c_entryString.pop_back();
					v_commandDisplays.back().setString(c_entryString);
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace) && c_entryString.size() == 1) {
					//	Do nothing
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
					c_entryString = v_commandDisplays.back().getString();
					c_entryString.erase(0, 1);	//	This removes the preceding ">" that is present for aesthetic purposes
					//addOutputText(ptr_gameLogic->ptr_interfaceManager->commandPreprocess(c_entryString));
					addOutputText(ptr_gameLogic->commandPreprocess(c_entryString));

					if (v_outputDisplays.size() != 0 && std::string(v_outputDisplays.back().getString()).compare(0, 14, "Entered Note: ") == 0) {
						addNoteText(std::string(v_outputDisplays.back().getString()).substr(14, c_entryString.size()));
					}
					else if (v_outputDisplays.size() != 0 && std::string(v_outputDisplays.back().getString()).compare(0, 14, "Removed Note: ") == 0) {
						removeNoteText(std::string(v_outputDisplays.back().getString()).substr(14, c_entryString.size()));
					}

					else if (v_outputDisplays.size() != 0 && std::string(v_outputDisplays.back().getString()).compare(0, 15, "Starting Game: ") == 0) {
						ptr_gameLogic->startRoomEscape(stoi(std::string(v_outputDisplays.back().getString()).substr(15, 17)));
					}

					else if (v_outputDisplays.size() != 0 && std::string(v_outputDisplays.back().getString()).compare(0, 14, "Look Attempt: ") == 0
						|| v_outputDisplays.size() != 0 && std::string(v_outputDisplays.back().getString()).compare(0, 14, "Move Attempt: ") == 0
						|| v_outputDisplays.size() != 0 && std::string(v_outputDisplays.back().getString()).compare(0, 16, "Pickup Attempt: ") == 0
						|| v_outputDisplays.size() != 0 && std::string(v_outputDisplays.back().getString()).compare(0, 15, "Equip Attempt: ") == 0
						|| v_outputDisplays.size() != 0 && std::string(v_outputDisplays.back().getString()).compare(0, 17, "Inspect Attempt: ") == 0
						|| v_outputDisplays.size() != 0 && std::string(v_outputDisplays.back().getString()).compare(0, 18, "Interact Attempt: ") == 0
						|| v_outputDisplays.size() != 0 && std::string(v_outputDisplays.back().getString()).compare(0, 17, "Discard Attempt: ") == 0) {
						ptr_gameLogic->handleCommand(std::string(v_outputDisplays.back().getString()));
					}
					else if (v_outputDisplays.size() != 0 && std::string(v_outputDisplays.back().getString()) == "65536 Initiate Screen Clear 65536") {
						v_outputDisplays.clear();
						addOutputText(std::string("Screen Successfully Cleared"));
						v_commandDisplays.clear();
					}
					else if ( ptr_gameLogic->ptr_player != NULL &&
						(v_outputDisplays.back().getString().find("Restart Game") != std::string::npos
						|| v_outputDisplays.back().getString().find("restart game") != std::string::npos)) {
						if (ptr_gameLogic->ptr_player->c_healthFloat == 0.0f) {
							v_outputDisplays.clear();
							v_commandDisplays.clear();
							ptr_gameLogic->restartGameLogic();
							removeJournalText(std::string("Name: "));
							removeJournalText(std::string("Head: "));
							removeJournalText(std::string("Torso: "));
							removeJournalText(std::string("Equipment: "));
							removeJournalText(std::string("Position: "));
						}

					}

					v_commandDisplays.push_back(sf::Text(">", c_activeFont, (int)(c_windowUnitInt * 3)));
					v_commandDisplays.shrink_to_fit();
					v_commandDisplays.back().setFillColor(arr_foregroundColours[c_foregroundIndexInt]);
					//compileNotesStrings();

					
				}
				else if (event.text.unicode < 128) {
					c_entryString = v_commandDisplays.back().getString();
					c_entryString.push_back((char)event.text.unicode);
					v_commandDisplays.back().setString(c_entryString);
				}
				break;
			}

		}

		//!		+ The Application clears the display with Wet Asphalt and then draws all the drawable elements.
		ptr_gameRenderWindow->clear(arr_backgroundColours[c_backgroundIndexInt]);
		
		
		for (sf::RectangleShape frameRectangle : arr_displayFraming)
			ptr_gameRenderWindow->draw(frameRectangle);

		if (ptr_gameLogic->ptr_player != nullptr) {
			updateJournalText(std::string("Head: "), ptr_gameLogic->ptr_player->c_attireHeadString);
			updateJournalText(std::string("Torso: "), ptr_gameLogic->ptr_player->c_attireTorsoString);
			updateJournalText(std::string("Equipment: "), ptr_gameLogic->ptr_player->c_equipmentString);
			updateJournalText(std::string("Position: "), std::to_string(ptr_gameLogic->ptr_player->c_positionInt2d.s_firstInt) + "," + std::to_string(ptr_gameLogic->ptr_player->c_positionInt2d.s_secondInt));
		}
		displayTexts();
				
		ptr_gameRenderWindow->display();		

		return c_errorCodeInt;
	}
	else {
		return c_errorCodeInt;
	}
}

int SFML_Window::getWindowWidth() {
	return c_windowWidthInt;
}
void SFML_Window::setWindowWidth(int& width_in) {
	c_windowWidthInt = width_in;
}

int SFML_Window::getWindowHeight() {
	return c_windowHeightInt;
}
void SFML_Window::setWindowHeight(int& height_in) {
	c_windowHeightInt = height_in;
}

void SFML_Window::displayTexts() {
	//	Display journals entries
	if (v_journalDisplays.size() <= 12) {
		for (int i = 0; i < v_journalDisplays.size(); i++) {
			v_journalDisplays.at(i).setPosition(sf::Vector2f(arr_displayFraming[const_journalIndexInt].getPosition().x + c_windowUnitInt + (i * c_windowUnitInt * 3 * c_textCascadingInt),
				arr_displayFraming[const_journalIndexInt].getPosition().y + c_windowUnitInt + (i * c_windowUnitInt * 3.5)));
			v_journalDisplays.at(i).setFillColor(arr_foregroundColours[c_foregroundIndexInt]);
			ptr_gameRenderWindow->draw(v_journalDisplays.at(i));
		}
	}
	else {
		int i, j;
		for (i = v_journalDisplays.size() - 12, j = 0; i < v_journalDisplays.size(); i++ && j++) {
			v_journalDisplays.at(i).setPosition(sf::Vector2f(arr_displayFraming[const_journalIndexInt].getPosition().x + c_windowUnitInt + (j * c_windowUnitInt * 3 * c_textCascadingInt),
				arr_displayFraming[const_journalIndexInt].getPosition().y + c_windowUnitInt + (j * c_windowUnitInt * 3.5)));
			v_journalDisplays.at(i).setFillColor(arr_foregroundColours[c_foregroundIndexInt]);
			ptr_gameRenderWindow->draw(v_journalDisplays.at(i));
		}
	}
	//	End of journal entries
	//	Display notes
	if (v_noteDisplays.size() <= 6) {
		for (int i = 0; i < v_noteDisplays.size(); i++) {
			v_noteDisplays.at(i).setPosition(sf::Vector2f(arr_displayFraming[const_noteIndexInt].getPosition().x + c_windowUnitInt + (i * c_windowUnitInt * 3 * c_textCascadingInt),
				arr_displayFraming[const_noteIndexInt].getPosition().y + c_windowUnitInt + (i * c_windowUnitInt * 3.5)));
			v_noteDisplays.at(i).setFillColor(arr_foregroundColours[c_foregroundIndexInt]);
			ptr_gameRenderWindow->draw(v_noteDisplays.at(i));
		}
	}
	else {
		int i, j;
		for (i = v_noteDisplays.size() - 6, j = 0; i < v_noteDisplays.size(); i++ && j++) {
			v_noteDisplays.at(i).setPosition(sf::Vector2f(arr_displayFraming[const_noteIndexInt].getPosition().x + c_windowUnitInt + (j * c_windowUnitInt * 3 * c_textCascadingInt),
				arr_displayFraming[const_noteIndexInt].getPosition().y + c_windowUnitInt + (j * c_windowUnitInt * 3.5)));
			v_noteDisplays.at(i).setFillColor(arr_foregroundColours[c_foregroundIndexInt]);
			ptr_gameRenderWindow->draw(v_noteDisplays.at(i));
		}
	}
	//	End notes
	//	Display output
	if (v_outputDisplays.size() <= 12) {
		for (int i = 0; i < v_outputDisplays.size(); i++) {
			v_outputDisplays.at(i).setPosition(sf::Vector2f(arr_displayFraming[const_outputIndexInt].getPosition().x + c_windowUnitInt + (i * c_windowUnitInt * 3 * c_textCascadingInt),
				arr_displayFraming[const_outputIndexInt].getPosition().y + c_windowUnitInt + (i * c_windowUnitInt * 3.5)));
			v_outputDisplays.at(i).setFillColor(arr_foregroundColours[c_foregroundIndexInt]);
			ptr_gameRenderWindow->draw(v_outputDisplays.at(i));
		}
	}
	else {
		int i, j;
		for (i = v_outputDisplays.size() - 12, j = 0; i < v_outputDisplays.size(); i++ && j++) {
			v_outputDisplays.at(i).setPosition(sf::Vector2f(arr_displayFraming[const_outputIndexInt].getPosition().x + c_windowUnitInt + (j * c_windowUnitInt * 3 * c_textCascadingInt),
				arr_displayFraming[const_outputIndexInt].getPosition().y + c_windowUnitInt + (j * c_windowUnitInt * 3.5)));
			v_outputDisplays.at(i).setFillColor(arr_foregroundColours[c_foregroundIndexInt]);
			ptr_gameRenderWindow->draw(v_outputDisplays.at(i));
		}
	}
	//	End of output
	//	Display inputted commands
	if (v_commandDisplays.size() <= 6) {
		for (int i = 0; i < v_commandDisplays.size(); i++) {
			v_commandDisplays.at(i).setPosition(sf::Vector2f(arr_displayFraming[const_commandIndexInt].getPosition().x + c_windowUnitInt + (i * c_windowUnitInt * 3 * c_textCascadingInt),
				arr_displayFraming[const_commandIndexInt].getPosition().y + c_windowUnitInt + (i * c_windowUnitInt * 3.5)));
			v_commandDisplays.at(i).setFillColor(arr_foregroundColours[c_foregroundIndexInt]);
			ptr_gameRenderWindow->draw(v_commandDisplays.at(i));
		}
	}
	else {
		int i, j;
		for (i = v_commandDisplays.size() - 6, j = 0; i < v_commandDisplays.size(); i++ && j++) {
			v_commandDisplays.at(i).setPosition(sf::Vector2f(arr_displayFraming[const_commandIndexInt].getPosition().x + c_windowUnitInt + (j * c_windowUnitInt * 3 * c_textCascadingInt),
				arr_displayFraming[const_commandIndexInt].getPosition().y + c_windowUnitInt + (j * c_windowUnitInt * 3.5)));
			v_commandDisplays.at(i).setFillColor(arr_foregroundColours[c_foregroundIndexInt]);
			ptr_gameRenderWindow->draw(v_commandDisplays.at(i));
		}
	}
	//	End of commands
}

void SFML_Window::addOutputText(std::string& string_in) {
	v_outputDisplays.push_back(sf::Text(string_in, c_activeFont, (int)(c_windowUnitInt * 3)));
	v_outputDisplays.shrink_to_fit();
	v_outputDisplays.back().setFillColor(arr_foregroundColours[c_foregroundIndexInt]);
}

void SFML_Window::addJournalText(std::string& string_in) {
	v_journalDisplays.push_back(sf::Text(string_in, c_activeFont, (int)(c_windowUnitInt * 3)));
	v_journalDisplays.shrink_to_fit();
	v_journalDisplays.back().setFillColor(arr_foregroundColours[c_foregroundIndexInt]);
}

bool SFML_Window::updateJournalText(std::string& entry_in, std::string& alteration_in) {
	for (int i = 0; i < v_journalDisplays.size(); i++) {
		if (v_journalDisplays.at(i).getString().find(entry_in) != std::string::npos) {
			v_journalDisplays.at(i).setString(entry_in + alteration_in);
			return true;
		}
	}
	return false;
}

void SFML_Window::removeJournalText(std::string& entry_in) {
	for (int i = 0; i < v_journalDisplays.size(); i++) {
		if (v_journalDisplays.at(i).getString().find(entry_in) != std::string::npos) {
			v_journalDisplays.erase(v_journalDisplays.begin() + i);
		}
	}
}

void SFML_Window::addNoteText(std::string& string_in) {
	v_noteDisplays.push_back(sf::Text(string_in, c_activeFont, (int)(c_windowUnitInt * 3)));
	v_noteDisplays.shrink_to_fit();
	v_noteDisplays.back().setFillColor(arr_foregroundColours[c_foregroundIndexInt]);
}
void SFML_Window::removeNoteText(std::string& string_in) {
	bool m_exists = false;
	
	for (int i = 0; i < v_noteDisplays.size(); i++) {
		if (v_noteDisplays.at(i).getString() == string_in) {
			v_noteDisplays.erase(v_noteDisplays.begin() + i);
			v_noteDisplays.shrink_to_fit();
			i = v_noteDisplays.size() * 2;
		}
	}

		
}