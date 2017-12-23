#include "FuzzyBehaviour.h"

FuzzyBehaviour::FuzzyBehaviour(int& hR_in, int& dR_in, int& hU_in, int& play_in, int& aggro_in) {

	v_playerInteraction.reserve(16);
	
	fl::scalar m_honestyRatio = 0.0f;
	if (dR_in > 0)
		m_honestyRatio = (hR_in + hU_in) / dR_in;
	else
		m_honestyRatio = 1.0f;

	fl::scalar m_playStyle = play_in;

	fl::scalar m_aggression = aggro_in;
	

	//	This will help determine the context of the game so far
	fl::Engine* m_contextEngine = new fl::Engine;
	m_contextEngine->setName("contextEngine");
	m_contextEngine->setDescription("");

	//	This is the ratio of honesty in the game so far (from entities, not the player)
	//	This is essentially based on (honest-reliable + honest-unreliable) / dishonest-reliable
	fl::InputVariable* m_storyHonesty = new fl::InputVariable;
	m_storyHonesty->setName("honesty");
	m_storyHonesty->setDescription("");
	m_storyHonesty->setEnabled(true);
	m_storyHonesty->setRange(0.000, 1.000);
	m_storyHonesty->setLockValueInRange(false);
	m_storyHonesty->addTerm(new fl::Ramp("left", 1.000, 0.000));
	m_storyHonesty->addTerm(new fl::Ramp("right", 0.000, 1.000));
	m_contextEngine->addInputVariable(m_storyHonesty);


	//	This is the user's p[laystyle as determined in the escape the room situation
	fl::InputVariable* m_userStyle = new fl::InputVariable;
	m_userStyle->setName("playStyle");
	m_userStyle->setDescription("");
	m_userStyle->setEnabled(true);
	m_userStyle->setRange(0.000, 1.000);
	m_userStyle->setLockValueInRange(false);
	m_userStyle->addTerm(new fl::Ramp("left", 1.000, 0.000));
	m_userStyle->addTerm(new fl::Ramp("right", 0.000, 1.000));
	m_contextEngine->addInputVariable(m_userStyle);


	//	This determines how many aggressive words are directed towards the entity at first interaction
	//	Aggressive words are those that threaten or belittle the entity in some way
	fl::InputVariable* m_userAggression = new fl::InputVariable;
	m_userAggression->setName("userAggression");
	m_userAggression->setDescription("");
	m_userAggression->setEnabled(true);
	m_userAggression->setRange(0.000, 1.000);
	m_userAggression->setLockValueInRange(false);
	m_userAggression->addTerm(new fl::Ramp("left", 1.000, 0.000));
	m_userAggression->addTerm(new fl::Ramp("right", 0.000, 1.000));
	m_contextEngine->addInputVariable(m_userAggression);

	//	This will determine what behaviour this entity will have
	//	honest-reliable tells the truth and helps direct the player to the next objective
	//	honest-unreliable tells the truth, but only gives lore or fluff information
	//	dishonest-reliable tells lies, and as a result directs the player away from the next objective
	fl::OutputVariable* m_behaviour = new fl::OutputVariable;
	m_behaviour->setName("behaviour");
	m_behaviour->setDescription("");
	m_behaviour->setEnabled(true);
	m_behaviour->setRange(0.000, 1.000);
	m_behaviour->setLockValueInRange(false);
	m_behaviour->setAggregation(new fl::Maximum);
	m_behaviour->setDefuzzifier(new fl::Centroid(100));
	m_behaviour->setDefaultValue(fl::nan);
	m_behaviour->setLockPreviousValue(false);
	m_behaviour->addTerm(new fl::Ramp("left", 1.000, 0.000));
	m_behaviour->addTerm(new fl::Ramp("right", 0.000, 1.000));
	m_contextEngine->addOutputVariable(m_behaviour);

	//	This is the ruleset for the behaviourEngine
	fl::RuleBlock* m_mamdani = new fl::RuleBlock;
	m_mamdani->setName("mamdani");
	m_mamdani->setDescription("");
	m_mamdani->setEnabled(true);
	m_mamdani->setConjunction(fl::null);
	m_mamdani->setDisjunction(fl::null);
	m_mamdani->setImplication(new fl::AlgebraicProduct);
	m_mamdani->setActivation(new fl::General);
	m_mamdani->addRule(fl::Rule::parse("if obstacle is left then mSteer is right", m_contextEngine));
	m_mamdani->addRule(fl::Rule::parse("if obstacle is right then mSteer is left", m_contextEngine));
	m_contextEngine->addRuleBlock(m_mamdani);

	//	This sets up the engine to run
	m_storyHonesty->setValue(m_honestyRatio);
	m_userStyle->setValue(m_playStyle);
	m_userAggression->setValue(m_aggression);

	//	This runs the fuzzy engine once
	m_contextEngine->process();

	//	This will save the output of the engine for later use
	c_behaviour = m_behaviour->getValue();



	//	What follows is the set up of an interaction engine for when a user talks with this entity
	ptr_interactionEngine = new fl::Engine;
	ptr_interactionEngine->setName("interactionEngine");
	ptr_interactionEngine->setDescription("");


	//	The entity behaviour was determined above by the other engine
	//	This will essentially figure out what behaviour to magnify
	ptr_entityBehaviour = new fl::InputVariable;
	ptr_entityBehaviour->setName("entityBehaviour");
	ptr_entityBehaviour->setDescription("");
	ptr_entityBehaviour->setEnabled(true);
	ptr_entityBehaviour->setRange(0.000, 1.000);
	ptr_entityBehaviour->setLockValueInRange(false);
	ptr_entityBehaviour->addTerm(new fl::Ramp("left", 1.000, 0.000));
	ptr_entityBehaviour->addTerm(new fl::Ramp("right", 0.000, 1.000));
	m_contextEngine->addInputVariable(m_storyHonesty);

	//	This is how many pleasn words the user has used towards the entity
	//	These being words that are not aggressive, nor neutral
	ptr_playerPleasantry = new fl::InputVariable;
	ptr_playerPleasantry->setName("playerPleasantry");
	ptr_playerPleasantry->setDescription("");
	ptr_playerPleasantry->setEnabled(true);
	ptr_playerPleasantry->setRange(0.000, 1.000);
	ptr_playerPleasantry->setLockValueInRange(false);
	ptr_playerPleasantry->addTerm(new fl::Ramp("left", 1.000, 0.000));
	ptr_playerPleasantry->addTerm(new fl::Ramp("right", 0.000, 1.000));
	m_contextEngine->addInputVariable(m_userStyle);

	//	This is the magitude of the entity's behaviour
	//	A honest-reliable would give the player greater amounts of useful information with greater behaviour magnitude
	ptr_behaviourMagnitude = new fl::OutputVariable;
	ptr_behaviourMagnitude->setName("behaviourMagnitude");
	ptr_behaviourMagnitude->setDescription("");
	ptr_behaviourMagnitude->setEnabled(true);
	ptr_behaviourMagnitude->setRange(0.000, 1.000);
	ptr_behaviourMagnitude->setLockValueInRange(false);
	ptr_behaviourMagnitude->setAggregation(new fl::Maximum);
	ptr_behaviourMagnitude->setDefuzzifier(new fl::Centroid(100));
	ptr_behaviourMagnitude->setDefaultValue(fl::nan);
	ptr_behaviourMagnitude->setLockPreviousValue(false);
	ptr_behaviourMagnitude->addTerm(new fl::Ramp("left", 1.000, 0.000));
	ptr_behaviourMagnitude->addTerm(new fl::Ramp("right", 0.000, 1.000));
	ptr_interactionEngine->addOutputVariable(ptr_behaviourMagnitude);

	//	These are the rules for this engine
	ptr_interactionMamdani = new fl::RuleBlock;
	ptr_interactionMamdani->setName("interactionMamdani");
	ptr_interactionMamdani->setDescription("");
	ptr_interactionMamdani->setEnabled(true);
	ptr_interactionMamdani->setConjunction(fl::null);
	ptr_interactionMamdani->setDisjunction(fl::null);
	ptr_interactionMamdani->setImplication(new fl::AlgebraicProduct);
	ptr_interactionMamdani->setActivation(new fl::General);
	ptr_interactionMamdani->addRule(fl::Rule::parse("if obstacle is left then mSteer is right", m_contextEngine));
	ptr_interactionMamdani->addRule(fl::Rule::parse("if obstacle is right then mSteer is left", m_contextEngine));
	ptr_interactionEngine->addRuleBlock(ptr_interactionMamdani);

}


FuzzyBehaviour::~FuzzyBehaviour() {

}

std::string FuzzyBehaviour::interactionProcess(std::string& userText_in) {
	addInteractionLog(userText_in);
	return "empty";
}


void FuzzyBehaviour::addInteractionLog(std::string& userText_in) {
	if (v_playerInteraction.size() >= 16) 
		v_playerInteraction.erase(v_playerInteraction.begin());

	v_playerInteraction.push_back(userText_in);

}