#pragma once

#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <vector>
#include <string>
#include <algorithm>

#include "GameLogic.h"


//! This deals with all input/output, also interfaces with the gamelogic
class SFML_Window {
private:
	GameLogic *ptr_gameLogic;

	static constexpr int const_journalIndexInt = 0;
	static constexpr int const_noteIndexInt = 1;
	static constexpr int const_outputIndexInt = 2;
	static constexpr int const_commandIndexInt = 3;
	
	sf::RenderWindow* ptr_gameRenderWindow;

	sf::Font c_activeFont;

	std::vector<sf::Text> v_commandDisplays;
	std::vector<sf::Text> v_outputDisplays;
	std::vector<sf::Text> v_noteDisplays;
	std::vector<sf::Text> v_journalDisplays;

	sf::Text c_tempText;

	sf::RectangleShape arr_displayFraming[4];

	std::string c_entryString;
	//std::string c_displayString;
	//std::string c_notesString;
	//std::string c_journalString;

	//std::vector<std::string> v_commandStrings;
	//std::vector<std::string> v_displayStrings;
	//std::vector<std::string> v_noteStrings;
	//std::vector<std::string> v_journalStrings;

	sf::Color arr_backgroundColours[4];
	sf::Color arr_foregroundColours[4];

	int c_foregroundIndexInt;
	int c_backgroundIndexInt;

	int c_windowWidthInt;
	int c_windowHeightInt;
	int c_windowUnitInt;

	int c_textCascadingInt;

	int c_errorCodeInt;

public:
	SFML_Window();
	~SFML_Window();
	
	void linkGameLogic(GameLogic* logic_in);

	int Update();

	int getWindowWidth();
	void setWindowWidth(int& width_in);

	int getWindowHeight();
	void setWindowHeight(int& height_in);

	void addOutputText(std::string& string_in);
	void addJournalText(std::string& string_in);
	bool updateJournalText(std::string& entry_in, std::string& alteration_in);
	void removeJournalText(std::string& entry_in);
	void addNoteText(std::string& string_in);
	void removeNoteText(std::string& string_in);

private:
	void displayTexts();


};
