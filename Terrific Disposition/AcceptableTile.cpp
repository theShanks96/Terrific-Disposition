#include "AcceptableTile.h"

AcceptableTile::AcceptableTile() {
	c_populated = false;
	c_maximumInteractables = 3;
	v_interactables.reserve(c_maximumInteractables);

	setTypeFlavour("You should still be wary, but for now you seem relatively safe.");
	c_classificationString = "acceptable";
	c_availablePlotPosBool = true;
}

AcceptableTile::AcceptableTile(std::string description_in) {
	c_populated = false;
	c_maximumInteractables = 3;
	v_interactables.reserve(c_maximumInteractables);

	c_descriptionString = description_in;
	setTypeFlavour("You should still be wary, but for now you seem relatively safe.");
	c_classificationString = "acceptable";
	c_availablePlotPosBool = true;

}
AcceptableTile::~AcceptableTile() {

}



bool AcceptableTile::populateInteractables(int2d nextPlotPoint_in, int2d location_in, int storyHonesty_in, int play_in, int hostility_in, ResourceManager* resource_in, NaturalLogicManager* python_in) {
	std::vector<std::string> v_selectedPsuedonyms;
	v_selectedPsuedonyms.reserve(c_maximumInteractables);
	std::string m_temporaryNameString = "";
	bool m_pseudonameConflict = true;

	for (int i = 0; i < c_maximumInteractables; i++) {
		v_interactables.push_back(new Interactable());
		
		do {
			m_temporaryNameString = resource_in->getRandomPseudonymOne(false).s_nameString + " " + resource_in->getRandomPseudonymTwo(false).s_nameString;
			m_pseudonameConflict = false;

			//	The following is put in place to ensure that no two interactables have the exact same name
			for (int i = 0; i < v_selectedPsuedonyms.size(); i++) {
				//	If no match is found then the outer do-while loop will stop running
				if (m_temporaryNameString == v_selectedPsuedonyms.at(i)
					|| m_temporaryNameString.find(v_selectedPsuedonyms.at(i)) != std::string::npos)
					m_pseudonameConflict = true;
			}	
		} while (m_pseudonameConflict);
		v_selectedPsuedonyms.push_back(m_temporaryNameString);
		v_interactables.at(i)->c_nameString = m_temporaryNameString;

		//	An acceptable tile holds one simplebehaviour and two fuzzy behaviours
		if (i == 0) {
			v_interactables.at(0)->ptr_behaviour = new SimpleBehaviour();
			v_interactables.at(0)->c_sapienceBool = false;
		}
		else {
			v_interactables.at(i)->ptr_behaviour = new FuzzyBehaviour(storyHonesty_in, play_in, hostility_in);
			v_interactables.at(i)->c_sapienceBool = true;
		}
		//	Tell the behaviour where the next plot point is, for interaction purposes
		v_interactables.at(i)->ptr_behaviour->c_nextPlotPoint = nextPlotPoint_in;
		v_interactables.at(i)->ptr_behaviour->c_currentLocation = location_in;
		//	Link the python and resource managers
		v_interactables.at(i)->ptr_behaviour->linkResourceManager(resource_in);
		v_interactables.at(i)->ptr_behaviour->linkNaturalLogicManager(python_in);
	}
	c_populated = true;

	return true;
}


std::string AcceptableTile::getTileInformation() {
	if (v_interactables.size() < c_maximumInteractables && v_interactables.size() == 0)
		return c_descriptionString + " Nothing else seems to be here, best leave.";

	else if (v_interactables.size() < c_maximumInteractables && v_interactables.size() == 1)
		return "You see: " + v_interactables.at(0)->getName() + ".";

	else if (v_interactables.size() < c_maximumInteractables && v_interactables.size() == 2)
		return "You see: " + v_interactables.at(0)->getName() + ", " + v_interactables.at(1)->getName() + ".";

	else if(v_interactables.size() == c_maximumInteractables)
		return "You see: " + v_interactables.at(0)->getName() + ", " + v_interactables.at(1)->getName() + ", and " + v_interactables.at(2)->getName() + ".";

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

std::string AcceptableTile::interactByName(std::string entry_in) {
	std::string m_temp = "";
	for (int i = 0; i < c_maximumInteractables; i++) {
		m_temp = v_interactables.at(i)->c_nameString;
		std::transform(m_temp.begin(), m_temp.end(), m_temp.begin(), ::tolower);

		if (entry_in.find(m_temp) != std::string::npos) {
			return v_interactables.at(i)->ptr_behaviour->interactionProcess(entry_in.substr(1, v_interactables.at(i)->c_nameString.size()));
		}
	}
	return "There was no reply";
}
