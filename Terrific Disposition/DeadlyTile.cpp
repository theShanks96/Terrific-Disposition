#include "DeadlyTile.h"

DeadlyTile::DeadlyTile() {
	c_populated = true;
	setTypeFlavour("You are dead.");
	c_classificationString = "deadly";
	c_availablePlotPosBool = false;
}

DeadlyTile::DeadlyTile(std::string description_in) {
	c_populated = true;
	c_descriptionString = description_in;
	setTypeFlavour("You are dead.");
	c_classificationString = "deadly";
	c_availablePlotPosBool = false;

}
DeadlyTile::~DeadlyTile() {

}

bool DeadlyTile::populateInteractables(int2d nextPlotPoint_in, int2d location_in, int storyHonesty_in, int play_in, int hostility_in, ResourceManager* resource_in, NaturalLogicManager* python_in) {
	c_populated = true;
	return true;
}


std::string DeadlyTile::getTileInformation() {
	return "You look around but remain dead, nothing may save you now.";

}



bool DeadlyTile::getInteractablePresence(std::string text_in) {
	return false;
}
std::string DeadlyTile::interactByName(std::string entry_in){
	return	"You are dead.";
}
