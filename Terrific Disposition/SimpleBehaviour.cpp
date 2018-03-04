#include "SimpleBehaviour.h"

SimpleBehaviour::SimpleBehaviour() {


}


SimpleBehaviour::~SimpleBehaviour() {

}

std::string SimpleBehaviour::interactionProcess(std::string userText_in) {

	return ptr_naturalLogicManager->simpleBehaviourBoardProcessing();
}

void SimpleBehaviour::addInteractionLog(std::string& userText_in) {

}

