#include "FuzzyBehaviour.h"

FuzzyBehaviour::FuzzyBehaviour(int& hR_in, int& dR_in, int& hU_in, int& play_in, int& aggro_in) {

	v_playerStrings.reserve(16);
	
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
	m_storyHonesty->setRange(0, 100);
	m_storyHonesty->setLockValueInRange(true);
	ptr_entityBehaviour->addTerm(new fl::Trapezoid("low", 0, 0, 30, 40, 1));
	ptr_entityBehaviour->addTerm(new fl::Trapezoid("medium", 30, 40, 60, 70, 1));
	ptr_entityBehaviour->addTerm(new fl::Trapezoid("high", 60, 70, 100, 100, 1));
	m_contextEngine->addInputVariable(m_storyHonesty);


	//	This is the user's playstyle as determined in the escape the room situation
	fl::InputVariable* m_userStyle = new fl::InputVariable;
	m_userStyle->setName("playStyle");
	m_userStyle->setDescription("");
	m_userStyle->setEnabled(true);
	m_userStyle->setRange(0.000, 1.000);
	m_userStyle->setLockValueInRange(true);
	ptr_entityBehaviour->addTerm(new fl::Trapezoid("slow", 0, 0, 0.2, 0.3, 1));
	ptr_entityBehaviour->addTerm(new fl::Trapezoid("medium", 0.2, 0.3, 0.6, 0.7, 1));
	ptr_entityBehaviour->addTerm(new fl::Trapezoid("fast", 0.6, 0.7, 1.0, 1.0, 1));
	m_contextEngine->addInputVariable(m_userStyle);


	//	This determines how many aggressive words are directed towards the entity at first interaction
	//	Aggressive words are those that threaten or belittle the entity in some way
	fl::InputVariable* m_playerAggression = new fl::InputVariable;
	m_playerAggression->setName("playerAggression");
	m_playerAggression->setDescription("");
	m_playerAggression->setEnabled(true);
	m_playerAggression->setRange(0, 200);
	m_playerAggression->setLockValueInRange(true);
	ptr_entityBehaviour->addTerm(new fl::Trapezoid("verylow", 0, 0, 30, 40, 1));
	ptr_entityBehaviour->addTerm(new fl::Trapezoid("low", 30, 40, 60, 70, 1));
	ptr_entityBehaviour->addTerm(new fl::Trapezoid("medium", 60, 70, 110, 120, 1));
	ptr_entityBehaviour->addTerm(new fl::Trapezoid("high", 110, 120, 140, 150, 1));
	ptr_entityBehaviour->addTerm(new fl::Trapezoid("veryhigh", 140, 150, 200, 200, 1));
	m_contextEngine->addInputVariable(m_playerAggression);

	//	This will determine what behaviour this entity will have
	//	honest-reliable tells the truth and helps direct the player to the next objective
	//	honest-unreliable tells the truth, but only gives lore or fluff information
	//	dishonest-reliable tells lies, and as a result directs the player away from the next objective
	fl::OutputVariable* m_behaviour = new fl::OutputVariable;
	m_behaviour->setName("behaviour");
	m_behaviour->setDescription("");
	m_behaviour->setEnabled(true);
	m_behaviour->setRange(0, 90);
	m_behaviour->setLockValueInRange(true);
	m_behaviour->setAggregation(new fl::Maximum);
	m_behaviour->setDefuzzifier(new fl::Bisector());
	m_behaviour->setDefaultValue(fl::nan);
	m_behaviour->setLockPreviousValue(false);
	ptr_entityBehaviour->addTerm(new fl::Trapezoid("honestUnreliable", 0, 0, 20, 30, 1));
	ptr_entityBehaviour->addTerm(new fl::Trapezoid("honestReliable", 20, 30, 70, 80, 1));
	ptr_entityBehaviour->addTerm(new fl::Trapezoid("dishonestReliable", 70, 80, 90, 90, 1));
	m_contextEngine->addOutputVariable(m_behaviour);

	//	This is the ruleset for the behaviourEngine
	fl::RuleBlock* m_contextMamdani = new fl::RuleBlock;
	m_contextMamdani->setName("mamdani");
	m_contextMamdani->setDescription("");
	m_contextMamdani->setEnabled(true);
	m_contextMamdani->setConjunction(fl::null);
	m_contextMamdani->setDisjunction(fl::null);
	m_contextMamdani->setImplication(new fl::AlgebraicProduct);
	m_contextMamdani->setActivation(new fl::General);
	
	//	Constant low honesty > Variable playStyle and playerAggression
	m_contextMamdani->addRule(fl::Rule::parse("if honesty is low and playStyle is slow and playerAggression is verylow then behaviour is honestReliable", m_contextEngine));
	m_contextMamdani->addRule(fl::Rule::parse("if honesty is low and playStyle is slow and playerAggression is low then behaviour is honestReliable", m_contextEngine));
	m_contextMamdani->addRule(fl::Rule::parse("if honesty is low and playStyle is slow and playerAggression is medium then behaviour is honestUnreliable", m_contextEngine));
	m_contextMamdani->addRule(fl::Rule::parse("if honesty is low and playStyle is slow and playerAggression is high then behaviour is honestUnreliable", m_contextEngine));
	m_contextMamdani->addRule(fl::Rule::parse("if honesty is low and playStyle is slow and playerAggression is veryhigh then behaviour is dishonestReliable", m_contextEngine));

	m_contextMamdani->addRule(fl::Rule::parse("if honesty is low and playStyle is medium and playerAggression is verylow then behaviour is honestReliable", m_contextEngine));
	m_contextMamdani->addRule(fl::Rule::parse("if honesty is low and playStyle is medium and playerAggression is low then behaviour is honestReliable", m_contextEngine));
	m_contextMamdani->addRule(fl::Rule::parse("if honesty is low and playStyle is medium and playerAggression is medium then behaviour is honestUnreliable", m_contextEngine));
	m_contextMamdani->addRule(fl::Rule::parse("if honesty is low and playStyle is medium and playerAggression is high then behaviour is honestUnreliable", m_contextEngine));
	m_contextMamdani->addRule(fl::Rule::parse("if honesty is low and playStyle is medium and playerAggression is veryhigh then behaviour is dishonestReliable", m_contextEngine));

	m_contextMamdani->addRule(fl::Rule::parse("if honesty is low and playStyle is fast and playerAggression is verylow then behaviour is honestReliable", m_contextEngine));
	m_contextMamdani->addRule(fl::Rule::parse("if honesty is low and playStyle is fast and playerAggression is low then behaviour is honestReliable", m_contextEngine));
	m_contextMamdani->addRule(fl::Rule::parse("if honesty is low and playStyle is fast and playerAggression is medium then behaviour is honestUnreliable", m_contextEngine));
	m_contextMamdani->addRule(fl::Rule::parse("if honesty is low and playStyle is fast and playerAggression is high then behaviour is honestUnreliable", m_contextEngine));
	m_contextMamdani->addRule(fl::Rule::parse("if honesty is low and playStyle is fast and playerAggression is veryhigh then behaviour is dishonestReliable", m_contextEngine));
	
	//	Constant medium honesty > Variable playStyle and playerAggression
	m_contextMamdani->addRule(fl::Rule::parse("if honesty is medium and playStyle is slow and playerAggression is verylow then behaviour is honestReliable", m_contextEngine));
	m_contextMamdani->addRule(fl::Rule::parse("if honesty is medium and playStyle is slow and playerAggression is low then behaviour is honestUnreliable", m_contextEngine));
	m_contextMamdani->addRule(fl::Rule::parse("if honesty is medium and playStyle is slow and playerAggression is medium then behaviour is honestUnreliable", m_contextEngine));
	m_contextMamdani->addRule(fl::Rule::parse("if honesty is medium and playStyle is slow and playerAggression is high then behaviour is honestUnreliable", m_contextEngine));
	m_contextMamdani->addRule(fl::Rule::parse("if honesty is medium and playStyle is slow and playerAggression is veryhigh then behaviour is dishonestReliable", m_contextEngine));

	m_contextMamdani->addRule(fl::Rule::parse("if honesty is medium and playStyle is medium and playerAggression is verylow then behaviour is honestReliable", m_contextEngine));
	m_contextMamdani->addRule(fl::Rule::parse("if honesty is medium and playStyle is medium and playerAggression is low then behaviour is honestUnreliable", m_contextEngine));
	m_contextMamdani->addRule(fl::Rule::parse("if honesty is medium and playStyle is medium and playerAggression is medium then behaviour is honestUnreliable", m_contextEngine));
	m_contextMamdani->addRule(fl::Rule::parse("if honesty is medium and playStyle is medium and playerAggression is high then behaviour is dishonestReliable", m_contextEngine));
	m_contextMamdani->addRule(fl::Rule::parse("if honesty is medium and playStyle is medium and playerAggression is veryhigh then behaviour is dishonestReliable", m_contextEngine));

	m_contextMamdani->addRule(fl::Rule::parse("if honesty is medium and playStyle is fast and playerAggression is verylow then behaviour is honestReliable", m_contextEngine));
	m_contextMamdani->addRule(fl::Rule::parse("if honesty is medium and playStyle is fast and playerAggression is low then behaviour is honestUnreliable", m_contextEngine));
	m_contextMamdani->addRule(fl::Rule::parse("if honesty is medium and playStyle is fast and playerAggression is medium then behaviour is honestUnreliable", m_contextEngine));
	m_contextMamdani->addRule(fl::Rule::parse("if honesty is medium and playStyle is fast and playerAggression is high then behaviour is dishonestReliable", m_contextEngine));
	m_contextMamdani->addRule(fl::Rule::parse("if honesty is medium and playStyle is fast and playerAggression is veryhigh then behaviour is dishonestReliable", m_contextEngine));

	//	Constant high honesty > Variable playStyle and playerAggression
	m_contextMamdani->addRule(fl::Rule::parse("if honesty is high and playStyle is slow and playerAggression is verylow then behaviour is honestReliable", m_contextEngine));
	m_contextMamdani->addRule(fl::Rule::parse("if honesty is high and playStyle is slow and playerAggression is low then behaviour is honestReliable", m_contextEngine));
	m_contextMamdani->addRule(fl::Rule::parse("if honesty is high and playStyle is slow and playerAggression is medium then behaviour is honestUnreliable", m_contextEngine));
	m_contextMamdani->addRule(fl::Rule::parse("if honesty is high and playStyle is slow and playerAggression is high then behaviour is honestUnreliable", m_contextEngine));
	m_contextMamdani->addRule(fl::Rule::parse("if honesty is high and playStyle is slow and playerAggression is veryhigh then behaviour is dishonestReliable", m_contextEngine));

	m_contextMamdani->addRule(fl::Rule::parse("if honesty is high and playStyle is medium and playerAggression is verylow then behaviour is honestReliable", m_contextEngine));
	m_contextMamdani->addRule(fl::Rule::parse("if honesty is high and playStyle is medium and playerAggression is low then behaviour is honestReliable", m_contextEngine));
	m_contextMamdani->addRule(fl::Rule::parse("if honesty is high and playStyle is medium and playerAggression is medium then behaviour is honestUnreliable", m_contextEngine));
	m_contextMamdani->addRule(fl::Rule::parse("if honesty is high and playStyle is medium and playerAggression is high then behaviour is honestUnreliable", m_contextEngine));
	m_contextMamdani->addRule(fl::Rule::parse("if honesty is high and playStyle is medium and playerAggression is veryhigh then behaviour is dishonestReliable", m_contextEngine));

	m_contextMamdani->addRule(fl::Rule::parse("if honesty is high and playStyle is fast and playerAggression is verylow then behaviour is honestReliable", m_contextEngine));
	m_contextMamdani->addRule(fl::Rule::parse("if honesty is high and playStyle is fast and playerAggression is low then behaviour is honestReliable", m_contextEngine));
	m_contextMamdani->addRule(fl::Rule::parse("if honesty is high and playStyle is fast and playerAggression is medium then behaviour is honestUnreliable", m_contextEngine));
	m_contextMamdani->addRule(fl::Rule::parse("if honesty is high and playStyle is fast and playerAggression is high then behaviour is honestUnreliable", m_contextEngine));
	m_contextMamdani->addRule(fl::Rule::parse("if honesty is high and playStyle is fast and playerAggression is veryhigh then behaviour is dishonestReliable", m_contextEngine));
	m_contextMamdani->addRule(fl::Rule::parse("if obstacle is right then mSteer is left", m_contextEngine));
	m_contextEngine->addRuleBlock(m_contextMamdani);

	//	This sets up the engine to run
	m_storyHonesty->setValue(m_honestyRatio);
	m_userStyle->setValue(m_playStyle);
	m_playerAggression->setValue(m_aggression);
	//	This runs the fuzzy engine once
	m_contextEngine->process();
	//	This will save the output of the engine for later use
	ptr_behaviour = m_behaviour->getValue();



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
	ptr_entityBehaviour->setRange(0, 90);
	ptr_entityBehaviour->setLockValueInRange(true);
	ptr_entityBehaviour->addTerm(new fl::Trapezoid("honestUnreliable", 0, 0, 25, 35, 1));
	ptr_entityBehaviour->addTerm(new fl::Trapezoid("honestReliable", 25, 35, 55, 65, 1));
	ptr_entityBehaviour->addTerm(new fl::Trapezoid("dishonestReliable", 55, 65, 90, 90, 1));
	ptr_interactionEngine->addInputVariable(m_storyHonesty);

	//	This is how many pleasn words the user has used towards the entity
	//	These being words that are not aggressive, nor neutral
	ptr_playerPleasantry = new fl::InputVariable;
	ptr_playerPleasantry->setName("playerPleasantry");
	ptr_playerPleasantry->setDescription("");
	ptr_playerPleasantry->setEnabled(true);
	ptr_playerPleasantry->setRange(0, 20);
	ptr_playerPleasantry->setLockValueInRange(true);
	ptr_playerPleasantry->addTerm(new fl::Trapezoid("verylow", 0, 0, 3, 4, 1));
	ptr_playerPleasantry->addTerm(new fl::Trapezoid("low", 3, 4, 6, 7, 1));
	ptr_playerPleasantry->addTerm(new fl::Trapezoid("medium", 6, 7, 11, 12, 1));
	ptr_playerPleasantry->addTerm(new fl::Trapezoid("high", 11, 12, 14, 15, 1));
	ptr_playerPleasantry->addTerm(new fl::Trapezoid("veryhigh", 14, 15, 20, 20, 1));
	ptr_interactionEngine->addInputVariable(m_userStyle);

	//	This is how many pleasn words the user has used towards the entity
	//	These being words that are not aggressive, nor neutral
	ptr_tileClassification = new fl::InputVariable;
	ptr_tileClassification->setName("tileClassification");
	ptr_tileClassification->setDescription("");
	ptr_tileClassification->setEnabled(true);
	ptr_tileClassification->setRange(0, 10);
	ptr_tileClassification->setLockValueInRange(true);
	ptr_tileClassification->addTerm(new fl::Trapezoid("acceptable", 0, 0, 4, 6, 1));
	ptr_tileClassification->addTerm(new fl::Trapezoid("cautious", 4, 6, 10, 10, 1));
	ptr_interactionEngine->addInputVariable(m_userStyle);

	//	This is the magitude of the entity's behaviour
	//	A honest-reliable would give the player greater amounts of useful information with greater behaviour magnitude
	ptr_behaviourMagnitude = new fl::OutputVariable;
	ptr_behaviourMagnitude->setName("behaviourMagnitude");
	ptr_behaviourMagnitude->setDescription("");
	ptr_behaviourMagnitude->setEnabled(true);
	ptr_behaviourMagnitude->setRange(0, 90);
	ptr_behaviourMagnitude->setLockValueInRange(true);
	ptr_behaviourMagnitude->setAggregation(new fl::Maximum);
	ptr_behaviourMagnitude->setDefuzzifier(new fl::Bisector());
	ptr_behaviourMagnitude->setDefaultValue(fl::nan);
	ptr_behaviourMagnitude->setLockPreviousValue(false);
	ptr_behaviourMagnitude->addTerm(new fl::Trapezoid("low", 0, 0, 25, 35, 1));
	ptr_behaviourMagnitude->addTerm(new fl::Trapezoid("medium",25, 35, 55, 65, 1));
	ptr_behaviourMagnitude->addTerm(new fl::Trapezoid("high", 55, 65, 90, 90, 1));
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
	//	Constant honestUnreliable > Variable playerPleasantry and tileClassification
	ptr_interactionMamdani->addRule(fl::Rule::parse("if entityBehaviour is honestUnreliable and playerPleasantry is verylow and tileClassification is acceptable then behaviourMagnitude is high", ptr_interactionEngine));
	ptr_interactionMamdani->addRule(fl::Rule::parse("if entityBehaviour is honestUnreliable and playerPleasantry is low and tileClassification is acceptable then behaviourMagnitude is high", ptr_interactionEngine));
	ptr_interactionMamdani->addRule(fl::Rule::parse("if entityBehaviour is honestUnreliable and playerPleasantry is medium and tileClassification is acceptable then behaviourMagnitude is medium", ptr_interactionEngine));
	ptr_interactionMamdani->addRule(fl::Rule::parse("if entityBehaviour is honestUnreliable and playerPleasantry is high and tileClassification is acceptable then behaviourMagnitude is medium", ptr_interactionEngine));
	ptr_interactionMamdani->addRule(fl::Rule::parse("if entityBehaviour is honestUnreliable and playerPleasantry is veryhigh and tileClassification is acceptable then behaviourMagnitude is low", ptr_interactionEngine));

	ptr_interactionMamdani->addRule(fl::Rule::parse("if entityBehaviour is honestUnreliable and playerPleasantry is verylow and tileClassification is cautious then behaviourMagnitude is high", ptr_interactionEngine));
	ptr_interactionMamdani->addRule(fl::Rule::parse("if entityBehaviour is honestUnreliable and playerPleasantry is low and tileClassification is cautious then behaviourMagnitude is medium", ptr_interactionEngine));
	ptr_interactionMamdani->addRule(fl::Rule::parse("if entityBehaviour is honestUnreliable and playerPleasantry is medium and tileClassification is cautious then behaviourMagnitude is medium", ptr_interactionEngine));
	ptr_interactionMamdani->addRule(fl::Rule::parse("if entityBehaviour is honestUnreliable and playerPleasantry is high and tileClassification is cautious then behaviourMagnitude is low", ptr_interactionEngine));
	ptr_interactionMamdani->addRule(fl::Rule::parse("if entityBehaviour is honestUnreliable and playerPleasantry is veryhigh and tileClassification is cautious then behaviourMagnitude is low", ptr_interactionEngine));
	//	Constant honestReliable > Variable playerPleasantry and tileClassification
	ptr_interactionMamdani->addRule(fl::Rule::parse("if entityBehaviour is honestReliable and playerPleasantry is verylow and tileClassification is acceptable then behaviourMagnitude is low", ptr_interactionEngine));
	ptr_interactionMamdani->addRule(fl::Rule::parse("if entityBehaviour is honestReliable and playerPleasantry is low and tileClassification is acceptable then behaviourMagnitude is medium", ptr_interactionEngine));
	ptr_interactionMamdani->addRule(fl::Rule::parse("if entityBehaviour is honestReliable and playerPleasantry is medium and tileClassification is acceptable then behaviourMagnitude is medium", ptr_interactionEngine));
	ptr_interactionMamdani->addRule(fl::Rule::parse("if entityBehaviour is honestReliable and playerPleasantry is high and tileClassification is acceptable then behaviourMagnitude is high", ptr_interactionEngine));
	ptr_interactionMamdani->addRule(fl::Rule::parse("if entityBehaviour is honestReliable and playerPleasantry is veryhigh and tileClassification is acceptable then behaviourMagnitude is high", ptr_interactionEngine));

	ptr_interactionMamdani->addRule(fl::Rule::parse("if entityBehaviour is honestReliable and playerPleasantry is verylow and tileClassification is cautious then behaviourMagnitude is low", ptr_interactionEngine));
	ptr_interactionMamdani->addRule(fl::Rule::parse("if entityBehaviour is honestReliable and playerPleasantry is low and tileClassification is cautious then behaviourMagnitude is low", ptr_interactionEngine));
	ptr_interactionMamdani->addRule(fl::Rule::parse("if entityBehaviour is honestReliable and playerPleasantry is medium and tileClassification is cautious then behaviourMagnitude is low", ptr_interactionEngine));
	ptr_interactionMamdani->addRule(fl::Rule::parse("if entityBehaviour is honestReliable and playerPleasantry is high and tileClassification is cautious then behaviourMagnitude is medium", ptr_interactionEngine));
	ptr_interactionMamdani->addRule(fl::Rule::parse("if entityBehaviour is honestReliable and playerPleasantry is veryhigh and tileClassification is cautious then behaviourMagnitude is medium", ptr_interactionEngine));
	//	Constant dishonestReliable > Variable playerPleasantry and tileClassification
	ptr_interactionMamdani->addRule(fl::Rule::parse("if entityBehaviour is dishonestReliable and playerPleasantry is verylow and tileClassification is acceptable then behaviourMagnitude is low", ptr_interactionEngine));
	ptr_interactionMamdani->addRule(fl::Rule::parse("if entityBehaviour is dishonestReliable and playerPleasantry is low and tileClassification is acceptable then behaviourMagnitude is low", ptr_interactionEngine));
	ptr_interactionMamdani->addRule(fl::Rule::parse("if entityBehaviour is dishonestReliable and playerPleasantry is medium and tileClassification is acceptable then behaviourMagnitude is medium", ptr_interactionEngine));
	ptr_interactionMamdani->addRule(fl::Rule::parse("if entityBehaviour is dishonestReliable and playerPleasantry is high and tileClassification is acceptable then behaviourMagnitude is medium", ptr_interactionEngine));
	ptr_interactionMamdani->addRule(fl::Rule::parse("if entityBehaviour is dishonestReliable and playerPleasantry is veryhigh and tileClassification is acceptable then behaviourMagnitude is high", ptr_interactionEngine));

	ptr_interactionMamdani->addRule(fl::Rule::parse("if entityBehaviour is dishonestReliable and playerPleasantry is verylow and tileClassification is cautious then behaviourMagnitude is medium", ptr_interactionEngine));
	ptr_interactionMamdani->addRule(fl::Rule::parse("if entityBehaviour is dishonestReliable and playerPleasantry is low and tileClassification is cautious then behaviourMagnitude is medium", ptr_interactionEngine));
	ptr_interactionMamdani->addRule(fl::Rule::parse("if entityBehaviour is dishonestReliable and playerPleasantry is medium and tileClassification is cautious then behaviourMagnitude is high", ptr_interactionEngine));
	ptr_interactionMamdani->addRule(fl::Rule::parse("if entityBehaviour is dishonestReliable and playerPleasantry is high and tileClassification is cautious then behaviourMagnitude is high", ptr_interactionEngine));
	ptr_interactionMamdani->addRule(fl::Rule::parse("if entityBehaviour is dishonestReliable and playerPleasantry is veryhigh and tileClassification is cautious then behaviourMagnitude is high", ptr_interactionEngine));
	//	Add these rules to the ruleblock to the engine proper
	ptr_interactionEngine->addRuleBlock(ptr_interactionMamdani);

}


FuzzyBehaviour::~FuzzyBehaviour() {

}

std::string FuzzyBehaviour::interactionProcess(std::string userText_in) {
	addInteractionLog(userText_in);

	ptr_entityBehaviour->setValue(ptr_behaviour);
	ptr_playerPleasantry->setValue(2);
	ptr_tileClassification->setValue(2);

	ptr_interactionEngine->process();

	return "empty";
}


void FuzzyBehaviour::addInteractionLog(std::string& userText_in) {
	if (v_playerStrings.size() >= 16) 
		v_playerStrings.erase(v_playerStrings.begin());

	v_playerStrings.push_back(userText_in);

}