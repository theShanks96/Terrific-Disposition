#include "SFML_Window.h"

#include <iostream>

SFML_Window::SFML_Window() {

	c_textCascadingInt = 0;

	//!	SFML Identifies the screen's resolution.
	sf::VideoMode mode = sf::VideoMode::getDesktopMode();
	//!	This information is then used to dictate the size of the display.
	this->c_windowWidthInt = (int)(3 * mode.width / 4);	
	this->c_windowHeightInt = (int)(2 * mode.height / 3);
	this->c_windowUnitInt = (int)(c_windowHeightInt / 100);

	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	ptr_gameRenderWindow = new sf::RenderWindow(sf::VideoMode(c_windowWidthInt, c_windowHeightInt), "Terrific Disposition: Procedural Storyline Generation", sf::Style::Default, settings);
	ptr_gameRenderWindow->setFramerateLimit(30);
	
	this->arr_backgroundColours[0] = sf::Color(236, 240, 241);
	this->arr_backgroundColours[1] = sf::Color(189, 195, 199);
	this->arr_backgroundColours[2] = sf::Color(26, 188, 156);

	this->arr_backgroundColours[0] = sf::Color(27, 27, 27);
	this->arr_backgroundColours[1] = sf::Color(52, 73, 94);
	this->arr_backgroundColours[2] = sf::Color(41, 128, 185);

	this->c_foregroundIndexInt = 0;
	this->c_backgroundIndexInt = 0;

	this->arr_displayFraming[JOURNAL_INDEX] = sf::RectangleShape(sf::Vector2f((c_windowWidthInt * 0.3) - this->c_windowUnitInt, (c_windowHeightInt * 0.6) - this->c_windowUnitInt));
	this->arr_displayFraming[JOURNAL_INDEX].setPosition(sf::Vector2f(0 + this->c_windowUnitInt, 0 + this->c_windowUnitInt));
	this->arr_displayFraming[JOURNAL_INDEX].setFillColor(this->arr_backgroundColours[c_backgroundIndexInt]);
	this->arr_displayFraming[JOURNAL_INDEX].setOutlineColor(this->arr_backgroundColours[1]);
	this->arr_displayFraming[JOURNAL_INDEX].setOutlineThickness(this->c_windowUnitInt);

	this->arr_displayFraming[NOTE_INDEX] = sf::RectangleShape(sf::Vector2f((c_windowWidthInt * 0.3) - this->c_windowUnitInt, (c_windowHeightInt * 0.4)));
	this->arr_displayFraming[NOTE_INDEX].setPosition(sf::Vector2f(0 + this->c_windowUnitInt, (c_windowHeightInt * 0.6) - this->c_windowUnitInt));
	this->arr_displayFraming[NOTE_INDEX].setFillColor(this->arr_backgroundColours[c_backgroundIndexInt]);
	this->arr_displayFraming[NOTE_INDEX].setOutlineColor(this->arr_backgroundColours[1]);
	this->arr_displayFraming[NOTE_INDEX].setOutlineThickness(this->c_windowUnitInt);

	this->arr_displayFraming[OUTPUT_INDEX] = sf::RectangleShape(sf::Vector2f((c_windowWidthInt * 0.7), (c_windowHeightInt * 0.6)));
	this->arr_displayFraming[OUTPUT_INDEX].setPosition(sf::Vector2f((c_windowWidthInt * 0.3) - this->c_windowUnitInt, 0 + this->c_windowUnitInt));
	this->arr_displayFraming[OUTPUT_INDEX].setFillColor(this->arr_backgroundColours[c_backgroundIndexInt]);
	this->arr_displayFraming[OUTPUT_INDEX].setOutlineColor(this->arr_backgroundColours[1]);
	this->arr_displayFraming[OUTPUT_INDEX].setOutlineThickness(this->c_windowUnitInt);

	this->arr_displayFraming[COMMAND_INDEX] = sf::RectangleShape(sf::Vector2f((c_windowWidthInt * 0.7), (c_windowHeightInt * 0.4)));
	this->arr_displayFraming[COMMAND_INDEX].setPosition(sf::Vector2f((c_windowWidthInt * 0.3) - this->c_windowUnitInt, (c_windowHeightInt * 0.6) - this->c_windowUnitInt));
	this->arr_displayFraming[COMMAND_INDEX].setFillColor(this->arr_backgroundColours[c_backgroundIndexInt]);
	this->arr_displayFraming[COMMAND_INDEX].setOutlineColor(this->arr_backgroundColours[1]);
	this->arr_displayFraming[COMMAND_INDEX].setOutlineThickness(this->c_windowUnitInt);

	if (!c_activeFont.loadFromFile("../../../Library/Fonts/Dosis-SemiBold.ttf"))
		c_errorCodeInt = 100;

	v_outputDisplays.push_back(sf::Text(">Output", c_activeFont, (int)(c_windowUnitInt * 3)));
	v_outputDisplays.back().setFillColor(this->arr_backgroundColours[1]);

	v_commandDisplays.push_back(sf::Text(">", c_activeFont, (int)(c_windowUnitInt * 3)));
	v_commandDisplays.back().setFillColor(this->arr_backgroundColours[1]);

	v_noteDisplays.push_back(sf::Text(">Notes", c_activeFont, (int)(c_windowUnitInt * 3)));
	v_noteDisplays.back().setFillColor(this->arr_backgroundColours[1]);

	v_journalDisplays.push_back(sf::Text(">Journal", c_activeFont, (int)(c_windowUnitInt * 3)));
	v_journalDisplays.back().setFillColor(this->arr_backgroundColours[1]);

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

			while (ptr_gameLogic->v_pendingOutput.size() > 0) {
				if (ptr_gameLogic->v_pendingOutput.front().compare(0, 22, "You remember going by ") == 0) {
					addJournalText("Name: " + ptr_gameLogic->v_pendingOutput.front().substr(22, ptr_gameLogic->v_pendingOutput.front().size()));
					addJournalText("Head: " + ptr_gameLogic->ptr_player->c_attireHead);
					addJournalText("Torso: " + ptr_gameLogic->ptr_player->c_attireTorso);
					addJournalText("Equipment: " + ptr_gameLogic->ptr_player->c_equipment);
				}
				if (ptr_gameLogic->v_pendingOutput.front().find("you've left the hideout and your journey begins") != std::string::npos) {
					addJournalText("Position: " + std::to_string(ptr_gameLogic->ptr_player->c_position.s_first) + "," + std::to_string(ptr_gameLogic->ptr_player->c_position.s_second));
				}
				addOutputText(ptr_gameLogic->v_pendingOutput.front());
				ptr_gameLogic->v_pendingOutput.erase(ptr_gameLogic->v_pendingOutput.begin());
			
			}

			switch (event.type) {

			case sf::Event::Closed:
				ptr_gameRenderWindow->close();
				c_errorCodeInt = 1;
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
						|| v_outputDisplays.size() != 0 && std::string(v_outputDisplays.back().getString()).compare(0, 17, "Discard Attempt: ") == 0
						|| v_outputDisplays.size() != 0 && std::string(v_outputDisplays.back().getString()).compare(0, 15, "Solve Attempt: ") == 0) {
						ptr_gameLogic->handleCommand(std::string(v_outputDisplays.back().getString()));
					}

					v_commandDisplays.push_back(sf::Text(">", c_activeFont, (int)(c_windowUnitInt * 3)));
					v_commandDisplays.shrink_to_fit();
					v_commandDisplays.back().setFillColor(arr_backgroundColours[1]);
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
			updateJournalText(std::string("Head: "), ptr_gameLogic->ptr_player->c_attireHead);
			updateJournalText(std::string("Torso: "), ptr_gameLogic->ptr_player->c_attireTorso);
			updateJournalText(std::string("Equipment: "), ptr_gameLogic->ptr_player->c_equipment);
			updateJournalText(std::string("Position: "), std::to_string(ptr_gameLogic->ptr_player->c_position.s_first) + "," + std::to_string(ptr_gameLogic->ptr_player->c_position.s_second));
		}
		displayTexts();
				
		ptr_gameRenderWindow->display();		

		return c_errorCodeInt;
	}
	else {
		return c_errorCodeInt;
	}
}

int SFML_Window::getwindowWidth() {
	return this->c_windowWidthInt;
}
void SFML_Window::setwindowWidth(int& width_in) {
	this->c_windowWidthInt = width_in;
}

int SFML_Window::getwindowHeight() {
	return this->c_windowHeightInt;
}
void SFML_Window::setwindowHeight(int& height_in) {
	this->c_windowHeightInt = height_in;
}

void SFML_Window::displayTexts() {

	//	Display journals entries

	if (v_journalDisplays.size() <= 12) {
		for (int i = 0; i < v_journalDisplays.size(); i++) {
			v_journalDisplays.at(i).setPosition(sf::Vector2f(arr_displayFraming[JOURNAL_INDEX].getPosition().x + c_windowUnitInt + (i * c_windowUnitInt * 3 * c_textCascadingInt),
				arr_displayFraming[JOURNAL_INDEX].getPosition().y + c_windowUnitInt + (i * c_windowUnitInt * 3.5)));
			ptr_gameRenderWindow->draw(v_journalDisplays.at(i));
		}

	}
	else {
		int i, j;
		for (i = v_journalDisplays.size() - 12, j = 0; i < v_journalDisplays.size(); i++ && j++) {
			v_journalDisplays.at(i).setPosition(sf::Vector2f(arr_displayFraming[JOURNAL_INDEX].getPosition().x + c_windowUnitInt + (j * c_windowUnitInt * 3 * c_textCascadingInt),
				arr_displayFraming[JOURNAL_INDEX].getPosition().y + c_windowUnitInt + (j * c_windowUnitInt * 3.5)));
			ptr_gameRenderWindow->draw(v_journalDisplays.at(i));

		}

	}

	//	End of journal entries

	//	Display notes

	if (v_noteDisplays.size() <= 6) {
		for (int i = 0; i < v_noteDisplays.size(); i++) {
			v_noteDisplays.at(i).setPosition(sf::Vector2f(arr_displayFraming[NOTE_INDEX].getPosition().x + c_windowUnitInt + (i * c_windowUnitInt * 3 * c_textCascadingInt),
				arr_displayFraming[NOTE_INDEX].getPosition().y + c_windowUnitInt + (i * c_windowUnitInt * 3.5)));
			ptr_gameRenderWindow->draw(v_noteDisplays.at(i));
		}

	}
	else {
		int i, j;
		for (i = v_noteDisplays.size() - 6, j = 0; i < v_noteDisplays.size(); i++ && j++) {
			v_noteDisplays.at(i).setPosition(sf::Vector2f(arr_displayFraming[NOTE_INDEX].getPosition().x + c_windowUnitInt + (j * c_windowUnitInt * 3 * c_textCascadingInt),
				arr_displayFraming[NOTE_INDEX].getPosition().y + c_windowUnitInt + (j * c_windowUnitInt * 3.5)));
			ptr_gameRenderWindow->draw(v_noteDisplays.at(i));

		}

	}

	//	End notes

	//	Display output

	if (v_outputDisplays.size() <= 12) {
		for (int i = 0; i < v_outputDisplays.size(); i++) {
			v_outputDisplays.at(i).setPosition(sf::Vector2f(arr_displayFraming[OUTPUT_INDEX].getPosition().x + c_windowUnitInt + (i * c_windowUnitInt * 3 * c_textCascadingInt),
				arr_displayFraming[OUTPUT_INDEX].getPosition().y + c_windowUnitInt + (i * c_windowUnitInt * 3.5)));
			ptr_gameRenderWindow->draw(v_outputDisplays.at(i));
		}

	}
	else {
		int i, j;
		for (i = v_outputDisplays.size() - 12, j = 0; i < v_outputDisplays.size(); i++ && j++) {
			v_outputDisplays.at(i).setPosition(sf::Vector2f(arr_displayFraming[OUTPUT_INDEX].getPosition().x + c_windowUnitInt + (j * c_windowUnitInt * 3 * c_textCascadingInt),
				arr_displayFraming[OUTPUT_INDEX].getPosition().y + c_windowUnitInt + (j * c_windowUnitInt * 3.5)));
			ptr_gameRenderWindow->draw(v_outputDisplays.at(i));

		}

	}

	//	End of output

	

	//	Display inputted commands
	if (v_commandDisplays.size() <= 6) {
		for (int i = 0; i < v_commandDisplays.size(); i++) {
			v_commandDisplays.at(i).setPosition(sf::Vector2f(arr_displayFraming[COMMAND_INDEX].getPosition().x + c_windowUnitInt + (i * c_windowUnitInt * 3 * c_textCascadingInt),
				arr_displayFraming[COMMAND_INDEX].getPosition().y + c_windowUnitInt + (i * c_windowUnitInt * 3.5)));
			ptr_gameRenderWindow->draw(v_commandDisplays.at(i));
		}

	}
	else {
		int i, j;
		for (i = v_commandDisplays.size() - 6, j = 0; i < v_commandDisplays.size(); i++ && j++) {
			v_commandDisplays.at(i).setPosition(sf::Vector2f(arr_displayFraming[COMMAND_INDEX].getPosition().x + c_windowUnitInt + (j * c_windowUnitInt * 3 * c_textCascadingInt),
				arr_displayFraming[COMMAND_INDEX].getPosition().y + c_windowUnitInt + (j * c_windowUnitInt * 3.5)));
			ptr_gameRenderWindow->draw(v_commandDisplays.at(i));

		}

	}
	//	End of commands

}

void SFML_Window::addOutputText(std::string& string_in) {
	v_outputDisplays.push_back(sf::Text(string_in, c_activeFont, (int)(c_windowUnitInt * 3)));
	v_outputDisplays.shrink_to_fit();
	v_outputDisplays.back().setFillColor(arr_backgroundColours[1]);
}

void SFML_Window::addJournalText(std::string& string_in) {
	v_journalDisplays.push_back(sf::Text(string_in, c_activeFont, (int)(c_windowUnitInt * 3)));
	v_journalDisplays.shrink_to_fit();
	v_journalDisplays.back().setFillColor(arr_backgroundColours[1]);
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

void SFML_Window::addNoteText(std::string& string_in) {
	v_noteDisplays.push_back(sf::Text(string_in, c_activeFont, (int)(c_windowUnitInt * 3)));
	v_noteDisplays.shrink_to_fit();
	v_noteDisplays.back().setFillColor(arr_backgroundColours[1]);
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