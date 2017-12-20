#pragma once

#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include <vector>
#include <string>
#include <algorithm>

#include "GameLogic.h"

class SFML_Window {
private:
	GameLogic *ptr_gameLogic;

	static constexpr int JOURNAL_INDEX = 0;
	static constexpr int NOTE_INDEX = 1;
	static constexpr int OUTPUT_INDEX = 2;
	static constexpr int COMMAND_INDEX = 3;
	
	sf::RenderWindow* ptr_gameRenderWindow;

	sf::Font c_activeFont;


	sf::Text c_txt;
	std::vector<sf::Text> v_commandDisplays;
	std::vector<sf::Text> v_outputDisplays;
	std::vector<sf::Text> v_noteDisplays;
	std::vector<sf::Text> v_journalDisplays;


	sf::RectangleShape arr_displayFraming[4];

	std::string c_entryString;
	std::string c_displayString;
	std::string c_notesString;
	std::string c_journalString;

	std::vector<std::string> v_commandStrings;
	std::vector<std::string> v_displayStrings;
	std::vector<std::string> v_noteStrings;
	std::vector<std::string> v_journalStrings;

	sf::Color arr_backgroundColours[3];
	sf::Color arr_foregroundColours[3];

	int c_windowWidthInt;
	int c_windowHeightInt;
	int c_windowUnitInt;

	int c_textCascadingInt;

	int c_errorCodeInt;

	int c_foregroundIndexInt;
	int c_backgroundIndexInt;

public:
	SFML_Window();
	~SFML_Window();
	
	void linkGameLogic(GameLogic* logic_in);

	int Update();

	int getwindowWidth();
	void setwindowWidth(int& width_in);

	int getwindowHeight();
	void setwindowHeight(int& height_in);

	void addOutputText(std::string& string_in);
	void addJournalText(std::string& string_in);
	bool updateJournalText(std::string& entry_in, std::string& alteration_in);
	void addNoteText(std::string& string_in);
	void removeNoteText(std::string& string_in);

private:
	void displayTexts();


};