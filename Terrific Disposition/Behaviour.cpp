#include "Behaviour.h"

Behaviour::Behaviour() {


}

Behaviour::~Behaviour() {

}


void Behaviour::addInteractionLog(std::string& userText_in) {

}

void Behaviour::linkResourceManager(ResourceManager* resource_in) {
	ptr_resourceManager = resource_in;
}

void Behaviour::linkNaturalLogicManager(NaturalLogicManager* natural_in) {
	ptr_naturalLogicManager = natural_in;
}