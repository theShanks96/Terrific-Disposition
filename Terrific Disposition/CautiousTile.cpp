#include "CautiousTile.h"

CautiousTile::CautiousTile() {
	setTypeFlavour("Might be best to move away from here.");
	c_classificationString = "cautious";
	c_availablePlotPosBool = true;
}

CautiousTile::CautiousTile(std::string description_in) {
	c_descriptionString = description_in;
	setTypeFlavour("Might be best to move away from here.");
	c_classificationString = "cautious";
	c_availablePlotPosBool = true;

}

CautiousTile::CautiousTile(bool hideoutTile_in) {

	if (hideoutTile_in) {
		c_descriptionString = "The compromised hideout from before.";
		setTypeFlavour("Might be best to move away from here.");
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

bool CautiousTile::populateInteractables(int2d nextPlotPoint_in, int honestReliable_in, int honestUnreliable_in, int dishonestReliable_in, int play_in, int aggressiveness_in) {
	if (c_interactable == nullptr) {
		c_interactable = new Interactable();
		c_interactable->ptr_behaviour = new FuzzyBehaviour(honestReliable_in, dishonestReliable_in, honestUnreliable_in, play_in, aggressiveness_in);
		c_interactable->ptr_behaviour->c_nextPlotPoint = nextPlotPoint_in;
		c_interactable->c_sapienceBool = true;
	}


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
