#pragma once

#include <vector>
#include <string>

class GameLogic {
private:
	float timeFromFailureFloat;
	float timeToActionFloat;
	float successRatioFloat;

	float successCountFloat;
	float failureCountFloat;

	std::vector<std::string> semanticFieldStringArray;
	
public:
	GameLogic();
	GameLogic(float& timeFromFailure_in, float& timeToAction_in, float& successCount_in, float& failureCount_in, std::vector<std::string>& semanticField_in);

	float getTimeFromFailue();
	void setTimeFromFailure(float& timeFromFailure_in);

	float getTimeToAction();
	void setTimeToAction(float& timeToAction_in);

	float getSuccessRatio();
	void setSuccessCount(float& successCount_in);
	void setFailureCount(float& failureCount_in);

	std::vector<std::string> getSemanticField();
	void setSemanticField(std::vector<std::string>& semanticField_in);

	void updateSuccessRatio();
};