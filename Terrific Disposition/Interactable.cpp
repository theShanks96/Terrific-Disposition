#include "Interactable.h"

Interactable::Interactable() {
	
}
Interactable::~Interactable() {

}


std::string Interactable::getName() {
	return c_nameString;
}

void Interactable::setName(std::string name_in) {
	c_nameString = name_in;
}
std::string Interactable::getDescription() {
	return c_descriptionString;
}
