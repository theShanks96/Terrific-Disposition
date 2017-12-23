#pragma once

#include <fuzzylite/fuzzylite.h>
#include <fuzzylite/Headers.h>

#include "Behaviour.h"

//! An implementation of Behaviour utilising a fuzzy inference engine.
class FuzzyBehaviour : public Behaviour {
private:	
	//! c_behaviour Determined by a specific fuzzy engine
	fl::scalar c_behaviour;

	//! ptr_interactionEngine Used to determine how the entity responds
	fl::Engine* ptr_interactionEngine;
	//! ptr_playerPleasantry Count of pleasant words
	fl::InputVariable* ptr_playerPleasantry;
	//! ptr_entityBehaviour The entity's behaviour profile
	fl::InputVariable* ptr_entityBehaviour;
	//! ptr_behaviourMagnitude The magnitude of the player's output
	fl::OutputVariable* ptr_behaviourMagnitude;
	//! ptr_interactionMamdani A mamdani ruleblock for the ptr_interactionEngine
	fl::RuleBlock* ptr_interactionMamdani;

	void addInteractionLog(std::string& userText_in) override;

public:

	//! Contructor for the fuzzy behaviour behaviour
	//! @param hR_in Count of honest-reliable entities so far
	//! @param dR_in Count of dishonest-reliable entities so far
	//! @param uR_in honest-unreliable entities so far
	//! @param play_in The user's playstyle during calibration
	//! @param aggro_in Count of aggressive words used by the player
	FuzzyBehaviour(int& hR_in, int& dR_in, int& hU_in, int& play_in, int& aggro_in);
	~FuzzyBehaviour();

	//! Intitiates the ptr_interactionEngine to determine behaviour
	//! @param user_in The string given by the user when interacting
	std::string interactionProcess(std::string& userText_in);



};