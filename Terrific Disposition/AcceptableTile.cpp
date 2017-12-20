#include "AcceptableTile.h"

AcceptableTile::AcceptableTile() {
	c_maximumInteractables = 3;
	v_interactables.reserve(c_maximumInteractables);

	setTypeFlavour("");
	c_classification = "acceptable";
	c_availablePlot = true;
}

AcceptableTile::AcceptableTile(std::string description_in) {
	c_maximumInteractables = 3;

	c_description = description_in;
	setTypeFlavour("");
	c_classification = "acceptable";
	c_availablePlot = true;

}
AcceptableTile::~AcceptableTile() {

}