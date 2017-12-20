#include "CautiousTile.h"

CautiousTile::CautiousTile() {
	setTypeFlavour("Might be best to move away from here.");
	c_classification = "cautious";
	c_availablePlot = true;
}

CautiousTile::CautiousTile(std::string description_in) {
	c_description = description_in;
	setTypeFlavour("Might be best to move away from here.");
	c_classification = "cautious";
	c_availablePlot = true;

}
CautiousTile::~CautiousTile() {

}
