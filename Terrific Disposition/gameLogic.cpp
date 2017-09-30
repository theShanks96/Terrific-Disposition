#include "gameLogic.h"

GameLogic::GameLogic() {
	//	initialising the timer data
	this->timeFromFailureFloat = 0.0f;
	this->timeToActionFloat = 0.0f;

	//	initialising the success/failure data
	this->successCountFloat = 0.0f;
	this->failureCountFloat = 0.0f;
	updateSuccessRatio();

	//	semanticFieldStringArray initialisation uneccessary

}

GameLogic::GameLogic(float& timeFromFailure_in, float& timeToAction_in, float& successCount_in,
	float& failureCount_in, std::vector<std::string>& semanticField_in) {

	this->timeFromFailureFloat = timeFromFailure_in;
	this->timeToActionFloat = timeToAction_in;

	this->successCountFloat = successCount_in;
	this->failureCountFloat = failureCount_in;
	updateSuccessRatio();

	this->semanticFieldStringArray = semanticField_in;

}

float GameLogic::getTimeFromFailue() {
	return this->timeFromFailureFloat;
}
void GameLogic::setTimeFromFailure(float& timeFromFailure_in) {
	this->timeFromFailureFloat = timeFromFailure_in;
}

float GameLogic::getTimeToAction() {
	return this->timeToActionFloat;
}
void GameLogic::setTimeToAction(float& timeToAction_in) {
	this->timeToActionFloat = timeToAction_in;
}

float GameLogic::getSuccessRatio() {
	updateSuccessRatio();
	return this->successRatioFloat;
}
void GameLogic::setSuccessCount(float& successCount_in) {
	this->successCountFloat = successCountFloat;
}
void GameLogic::setFailureCount(float& failureCount_in) {
	this->failureCountFloat = failureCount_in;
}

std::vector<std::string> GameLogic::getSemanticField() {
	return this->semanticFieldStringArray;
}
void GameLogic::setSemanticField(std::vector<std::string>& semanticField_in) {
	this->semanticFieldStringArray = semanticField_in;
}

void GameLogic::updateSuccessRatio() {
	if (failureCountFloat != 0)
		this->successRatioFloat = successCountFloat / failureCountFloat;
	else
		this->successCountFloat = 0;
}