#pragma once

#include "StringStructs.h"
#include "NumeralStructs.h"
#include "ComplexStructs.h"

#include <string>
#include <vector>
#include <map>
#include <json/json.h>
#include <fstream>
#include <sstream>
#include <iostream>


class ResourceManager {
public:
	//	Series of vectors containing the information to be used by other managers
	std::vector<stringPair> v_savedText;				//	Vector of text to be displayed
	std::vector<modelResource> v_modelPaths;			//	Vector of models to be displayed
	std::vector<stringPair> v_levelPaths;				//	Vector of levels that will dictate model quantity and position
	std::vector<stringPair> v_additionalFilePaths;		//	Vector for additional resources
	std::vector<resolutionGroup> v_windowResolutions;	//	Vector of window resolutions

	int m_currentLevel, m_totalLevels;

	ResourceManager(std::string configFilepath_in) {
		std::fstream jsonData;
		Json::Value root;
		Json::Reader reader;
		jsonData.open(configFilepath_in.c_str());	// check for errors

		if (!reader.parse(jsonData, root)) {
			std::cout << "Failed to open config file: " << configFilepath_in << reader.getFormattedErrorMessages();
		}
		else {

			//	If there are levels, which there must, then save the paths for future use
			const Json::Value levelPaths = root["LevelPaths"];	// size() tells us how large the array is
			v_levelPaths.reserve(levelPaths.size());

			for (int i = 0; i < levelPaths.size(); i++) {
				std::cout << levelPaths[i]["name"].asString() << " loaded\n";
				addLevelPath(levelPaths[i]["name"].asString(), levelPaths[i]["filepath"].asString());
			}

			//	If there is text, such as titles and whatnot, load them for future reference
			const Json::Value savedText = root["SavedText"];	// size() tells us how large the array is
			v_savedText.reserve(savedText.size());

			for (int i = 0; i < savedText.size(); i++) {
				std::cout << savedText[i]["title"].asString() << " loaded\n";
				addSavedText(savedText[i]["title"].asString(), savedText[i]["text"].asString());
			}
			
			//	If there are models to be loaded, load them for future reference
			const Json::Value modelPaths = root["ModelPaths"];	// size() tells us how large the array is
			v_modelPaths.reserve(modelPaths.size());

			for (int i = 0; i < modelPaths.size(); i++) {
				std::cout << modelPaths[i]["name"].asString() << " loaded\n";
				addModelPath(modelPaths[i]["name"].asString(), modelPaths[i]["filepath"].asString(), modelPaths[i]["x_bound"].asFloat(), modelPaths[i]["y_bound"].asFloat(), modelPaths[i]["z_bound"].asFloat());
			}
			
			//	Window resolution for the application will then be added
			const Json::Value windowResolutions = root["WindowResolutions"];	// size() tells us how large the array is
			v_windowResolutions.reserve(windowResolutions.size());

			for (int i = 0; i < windowResolutions.size(); i++) {
				std::cout << windowResolutions[i]["name"].asString() << " loaded\n";
				addWindowResolution(windowResolutions[i]["name"].asString(), windowResolutions[i]["width"].asString(), windowResolutions[i]["height"].asString());
			}

			//	If there are additional file paths to be loaded, load them into the vector for storage
			const Json::Value additionalFilePaths = root["AdditionalFilePaths"];	// size() tells us how large the array is
			v_additionalFilePaths.reserve(additionalFilePaths.size());

			for (int i = 0; i < additionalFilePaths.size(); i++) {
				std::cout << additionalFilePaths[i]["name"].asString() << " loaded\n";
				addFilePath(additionalFilePaths[i]["name"].asString(), additionalFilePaths[i]["filepath"].asString());
			}

			m_totalLevels = v_levelPaths.size();
			m_currentLevel = 0;
		}
	}

	std::string nextLevelPath() {
		if (m_currentLevel < m_totalLevels - 1) {
			m_currentLevel++;
		}
		else { m_currentLevel = m_totalLevels - 1; }

		return currentLevelPath();
	}

	std::string previousLevelPath() {
		if (m_currentLevel > 0) {
			m_currentLevel--;
		}
		else { m_currentLevel = 0; }
		
		return currentLevelPath();
	}

	std::string currentLevelPath() {
		return v_levelPaths.at(m_currentLevel).m_path;
	}

	//	Adding and getting the saved texts
	bool addSavedText(std::string textTitle_in, std::string text_in) {
		for (stringPair savedText : v_savedText) {
			if (savedText.m_name == textTitle_in)
				return true;
		}
		v_savedText.push_back(stringPair(textTitle_in, text_in));
		return true;
	}
	std::string getSavedText(std::string textTitle_in) {
		for (stringPair filePath : v_savedText) {
			if (filePath.m_name == textTitle_in)
				return filePath.m_path;
		}
		return v_savedText.at(0).m_path;
	}

	//	Adding and getting the level paths
	bool addLevelPath(std::string levelName_in, std::string levelPath_in) {
		for (stringPair levelPath : v_levelPaths) {
			if (levelPath.m_name == levelName_in)
				return true;
		}
		v_levelPaths.push_back(stringPair(levelName_in, levelPath_in));
		return true;
	}
	std::string getLevelPath(std::string levelName_in) {
		for (stringPair levelPath : v_levelPaths) {
			if (levelPath.m_name == levelName_in)
				return levelPath.m_path;
		}
		return v_levelPaths.at(0).m_path;
	}
	
	//	Adding and getting the model paths
	bool addModelPath(std::string modelName_in, std::string modelPath_in, float xBoundary_in, float yBoundary_in, float zBoundary_in) {
		for (modelResource modelPath : v_modelPaths) {
			if (modelPath.m_name == modelName_in)
				return true;
		}
		v_modelPaths.push_back(modelResource(modelName_in, modelPath_in, xBoundary_in, yBoundary_in, zBoundary_in));
		return true;
	}
	std::string* getModelPath(std::string modelName_in) {
		for (modelResource modelPath : v_modelPaths) {
			if (modelPath.m_name == modelName_in)
				return &modelPath.m_path;
		}
		return &v_modelPaths.at(0).m_path;
	}

	glm::vec3* getModelBoundaries(std::string modelName_in) {
		for (modelResource modelPath : v_modelPaths) {
			if (modelPath.m_name == modelName_in)
				return new glm::vec3(modelPath.m_xBoundary, modelPath.m_yBoundary, modelPath.m_zBoundary);
		}
		return new glm::vec3(v_modelPaths.at(0).m_xBoundary, v_modelPaths.at(0).m_yBoundary, v_modelPaths.at(0).m_zBoundary);
	}

	//	Adding and getting the window resolutions
	bool addWindowResolution(std::string resolutionName_in, std::string width_in, std::string height_in) {
		for (resolutionGroup resolution : v_windowResolutions) {
			if (resolution.m_name == resolutionName_in)
				return true;
		}
		v_windowResolutions.push_back(resolutionGroup(resolutionName_in, width_in, height_in));
		return true;
	}
	integerPair getWindowResolution(std::string resolutionName_in) {
		for (resolutionGroup resolution : v_windowResolutions) {
			if (resolution.m_name == resolutionName_in)
				return integerPair(resolution.m_width, resolution.m_height);
		}
		return integerPair(v_windowResolutions.at(0).m_width, v_windowResolutions.at(0).m_height);
	}

	//	Adding and getting additional files paths
	bool addFilePath(std::string fileName_in, std::string filePath_in) {
		for (stringPair filePath : v_additionalFilePaths) {
			if (filePath.m_name == fileName_in)
				return true;
		}
		v_additionalFilePaths.push_back(stringPair(fileName_in, filePath_in));
		return true;
	}
	std::string getFilePath(std::string fileName_in) {
		for (stringPair filePath : v_additionalFilePaths) {
			if (filePath.m_name == fileName_in)
				return filePath.m_path;
		}
		return v_additionalFilePaths.at(0).m_path;
	}
};