#include "CautiousTile.h"

CautiousTile::CautiousTile() {
	c_populated = false;
	setTypeFlavour("Might be best to move away from here.");
	c_classificationString = "cautious";
	c_availablePlotPosBool = true;
}

CautiousTile::CautiousTile(std::string description_in) {
	c_populated = false;
	c_descriptionString = description_in;
	setTypeFlavour("Seems you are nearing death, best to move away from here.");
	c_classificationString = "cautious";
	c_availablePlotPosBool = true;

}

CautiousTile::CautiousTile(bool hideoutTile_in) {

	if (hideoutTile_in) {
		c_populated = true;
		c_descriptionString = "The compromised hideout from before.";
		setTypeFlavour("Seems you are nearing death, best to move away from here.");
		c_classificationString = "cautious";
		c_availablePlotPosBool = false;

		c_interactable = new Interactable();
		c_interactable->setName("GoofyGoober2048");
	}

	else {
		CautiousTile();
	}
}
CautiousTile::~CautiousTile() {

}

bool CautiousTile::populateInteractables(int2d nextPlotPoint_in, int2d location_in, int storyHonesty_in, int play_in, int hostility_in, ResourceManager* resource_in, NaturalLogicManager* python_in) {
	
	c_interactable = new Interactable();
	c_interactable->ptr_behaviour = new FuzzyBehaviour(storyHonesty_in, play_in, hostility_in);
	c_interactable->ptr_behaviour->c_nextPlotPoint = nextPlotPoint_in;
	c_interactable->ptr_behaviour->c_currentLocation = location_in;
	c_interactable->c_sapienceBool = true;
	c_interactable->c_nameString = resource_in->getRandomPseudonymOne(false).s_nameString + " " + resource_in->getRandomPseudonymTwo(false).s_nameString;

	c_interactable->ptr_behaviour->linkResourceManager(resource_in);
	c_interactable->ptr_behaviour->linkNaturalLogicManager(python_in);
	
	c_populated = true;

	return true;
}


std::string CautiousTile::getTileInformation() {
	if (c_interactable->getName() == "GoofyGoober2048") 
		return c_descriptionString + " Nothing else seems to be here, best leave.";
	
	else 
		return c_descriptionString + " You see: " + c_interactable->getDescription() + ".";

}


bool CautiousTile::getInteractablePresence(std::string text_in) {
	if (text_in.find(c_interactable->getName()) != std::string::npos
		|| text_in.find(c_interactable->getDescription()) != std::string::npos) {
		return true;
	}
	
	return false;
}

std::string CautiousTile::interactByName(std::string entry_in) {
	std::string m_temp = c_interactable->c_nameString;
	std::transform(m_temp.begin(), m_temp.end(), m_temp.begin(), ::tolower);

	if (entry_in.find(m_temp) != std::string::npos) {
		return c_interactable->ptr_behaviour->interactionProcess(entry_in.substr(1, c_interactable->c_nameString.size()));
	}
	return "There was no reply";
}
