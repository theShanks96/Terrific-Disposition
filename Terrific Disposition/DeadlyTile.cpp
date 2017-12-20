#include "DeadlyTile.h"

DeadlyTile::DeadlyTile() {
	setTypeFlavour("You are dead.");
	c_classification = "deadly";
	c_availablePlot = false;
}

DeadlyTile::DeadlyTile(std::string description_in) {
	c_description = description_in;
	setTypeFlavour("You are dead.");
	c_classification = "deadly";
	c_availablePlot = false;

}
DeadlyTile::~DeadlyTile() {

}
