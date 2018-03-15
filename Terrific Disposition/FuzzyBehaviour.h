#pragma once

#include <fuzzylite/fuzzylite.h>
#include <fuzzylite/Headers.h>

#include "Behaviour.h"

//! An implementation of Behaviour utilising a fuzzy inference engine.
class FuzzyBehaviour : public Behaviour {
public:
	std::string c_classification;

private:	
	//! ptr_behaviour Determined by a specific fuzzy engine
	fl::scalar ptr_behaviour;

	//! ptr_interactionEngine Used to determine how the entity responds
	fl::Engine* ptr_interactionEngine;
	//! ptr_playerPleasantry Count of pleasant words
	fl::InputVariable* ptr_playerPleasantryIV;
	//! ptr_entityBehaviour The entity's behaviour profile
	fl::InputVariable* ptr_entityBehaviourIV;
	//! ptr_tileClassification The entity's current tile
	fl::InputVariable* ptr_tileClassificationIV;
	//! ptr_behaviourMagnitude The magnitude of the player's output
	fl::OutputVariable* ptr_behaviourMagnitudeOV;
	//! ptr_interactionMamdani A mamdani ruleblock for the ptr_interactionEngine
	fl::RuleBlock* ptr_interactionMamdaniRB;
	
public:
	//! Contructor for the fuzzy behaviour behaviour
	//! @param hR_in Count of honest-reliable entities so far
	//! @param dR_in Count of dishonest-reliable entities so far
	//! @param uR_in honest-unreliable entities so far
	//! @param play_in The user's playstyle during calibration
	//! @param hostility_in Count of aggressive words used by the player
	FuzzyBehaviour(int& hR_in, int& play_in, int& hostility_in);
	~FuzzyBehaviour();

	//! Intitiates the ptr_interactionEngine to determine behaviour
	//! @param user_in The string given by the user when interacting
	//! @return The resulting string to be shown to the user
	std::string interactionProcess(std::string userText_in) override;

	std::string interactionProcessTesting(int pleasantry_in, std::string classification_in);
	float getBehaviourTesting();
	float getMagnitudeTesting();
	
private:
	void addInteractionLog(std::string& userText_in) override;
};