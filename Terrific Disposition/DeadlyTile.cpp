#include "DeadlyTile.h"

DeadlyTile::DeadlyTile() {
	setTypeFlavour("You are dead.");
	c_classificationString = "deadly";
	c_availablePlotPosBool = false;
}

DeadlyTile::DeadlyTile(std::string description_in) {
	c_descriptionString = description_in;
	setTypeFlavour("You are dead.");
	c_classificationString = "deadly";
	c_availablePlotPosBool = false;

}
DeadlyTile::~DeadlyTile() {

}

bool DeadlyTile::populateInteractables(int2d nextPlotPoint_in, int honestReliable_in, int honestUnreliable_in, int dishonestReliable_in, int play_in, int aggressiveness_in) {
	return true;
}


std::string DeadlyTile::getTileInformation() {
	return "You look around but remain dead, nothing may save you now.";

}



bool DeadlyTile::getInteractablePresence(std::string text_in) {
	return false;
}
