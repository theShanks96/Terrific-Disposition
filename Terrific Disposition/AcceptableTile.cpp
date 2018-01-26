#include "AcceptableTile.h"

AcceptableTile::AcceptableTile() {
	c_maximumInteractables = 3;
	v_interactables.reserve(c_maximumInteractables);

	setTypeFlavour("");
	c_classificationString = "acceptable";
	c_availablePlotPosBool = true;
}

AcceptableTile::AcceptableTile(std::string description_in) {
	c_maximumInteractables = 3;

	c_descriptionString = description_in;
	setTypeFlavour("");
	c_classificationString = "acceptable";
	c_availablePlotPosBool = true;

}
AcceptableTile::~AcceptableTile() {

}



bool AcceptableTile::populateInteractables(int2d nextPlotPoint_in, int honestReliable_in, int honestUnreliable_in, int dishonestReliable_in, int play_in ,int aggressiveness_in) {


	for (int i = 0; i < 3; i++) {
		v_interactables.push_back(new Interactable());


		//	An acceptable tile holds one simplebehaviour and two fuzzy behaviours
		if (i = 0) {
			v_interactables.at(0)->ptr_behaviour = new SimpleBehaviour();
			v_interactables.at(0)->c_sapienceBool = false;
		}
		else {
			v_interactables.at(i)->ptr_behaviour = new FuzzyBehaviour(honestReliable_in, dishonestReliable_in, honestUnreliable_in, play_in, aggressiveness_in);
			v_interactables.at(i)->c_sapienceBool = true;
		}
		//	Tell the behaviour where the next plot point is, for interaction purposes
		v_interactables.at(i)->ptr_behaviour->c_nextPlotPoint = nextPlotPoint_in;
	}


	return true;
}


std::string AcceptableTile::getTileInformation() {
	if (v_interactables.at(0) == nullptr && v_interactables.at(1) == nullptr && v_interactables.at(22) == nullptr)
		return c_descriptionString + " Nothing else seems to be here, best leave.";

	else
		return c_descriptionString + " You see: " + v_interactables.at(0)->getDescription() + ", " + v_interactables.at(1)->getDescription() + ", and " + v_interactables.at(2)->getDescription() + ".";

}

bool AcceptableTile::getInteractablePresence(std::string text_in) {
	for (Interactable* l_interactable : v_interactables) {
		if (text_in.find(l_interactable->getName()) != std::string::npos
			|| text_in.find(l_interactable->getDescription()) != std::string::npos) {
			return true;
		}
	}
	return false;
}
