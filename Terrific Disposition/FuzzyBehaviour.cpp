#include "FuzzyBehaviour.h"

FuzzyBehaviour::FuzzyBehaviour(int& hR_in, int& play_in, int& hostility_in) {

	v_playerStrings.reserve(16);
	
	fl::scalar m_storyHonesty = hR_in;
	fl::scalar m_playStyle = play_in;
	fl::scalar m_aggression = hostility_in;
	

	//	This will help determine the context of the game so far
	fl::Engine* m_contextEngine = new fl::Engine;
	m_contextEngine->setName("contextEngine");
	m_contextEngine->setDescription("");

	//	This is the ratio ofstoryHonesty in the game so far (from entities, not the player)
	//	This is essentially based on (honest-reliable + honest-unreliable) / dishonest-reliable
	fl::InputVariable* m_storyHonestyIV = new fl::InputVariable;
	m_storyHonestyIV->setName("storyHonesty");
	m_storyHonestyIV->setDescription("");
	m_storyHonestyIV->setEnabled(true);
	m_storyHonestyIV->setRange(0, 100);
	m_storyHonestyIV->setLockValueInRange(true);
	m_storyHonestyIV->addTerm(new fl::Trapezoid("low", 0, 0, 30, 40, 1));
	m_storyHonestyIV->addTerm(new fl::Trapezoid("medium", 30, 40, 60, 70, 1));
	m_storyHonestyIV->addTerm(new fl::Trapezoid("high", 60, 70, 100, 100, 1));
	m_contextEngine->addInputVariable(m_storyHonestyIV);


	//	This is the user's playstyle as determined in the escape the room situation
	fl::InputVariable* m_playStyleIV = new fl::InputVariable;
	m_playStyleIV->setName("playStyle");
	m_playStyleIV->setDescription("");
	m_playStyleIV->setEnabled(true);
	m_playStyleIV->setRange(0, 100);
	m_playStyleIV->setLockValueInRange(true);
	m_playStyleIV->addTerm(new fl::Trapezoid("slow", 0, 0, 20, 30, 1));
	m_playStyleIV->addTerm(new fl::Trapezoid("medium", 20, 30, 60, 70, 1));
	m_playStyleIV->addTerm(new fl::Trapezoid("fast", 60, 70, 100, 100, 1));
	m_contextEngine->addInputVariable(m_playStyleIV);


	//	This determines how many aggressive words are directed towards the entity at first interaction
	//	Aggressive words are those that threaten or belittle the entity in some way
	fl::InputVariable* m_playerHostilityIV = new fl::InputVariable;
	m_playerHostilityIV->setName("playerHostility");
	m_playerHostilityIV->setDescription("");
	m_playerHostilityIV->setEnabled(true);
	m_playerHostilityIV->setRange(0, 100);
	m_playerHostilityIV->setLockValueInRange(true);
	m_playerHostilityIV->addTerm(new fl::Trapezoid("verylow", 0, 0, 15, 20, 1));
	m_playerHostilityIV->addTerm(new fl::Trapezoid("low", 15, 20, 30, 35, 1));
	m_playerHostilityIV->addTerm(new fl::Trapezoid("medium", 30, 35, 55, 60, 1));
	m_playerHostilityIV->addTerm(new fl::Trapezoid("high", 55, 60, 70, 75, 1));
	m_playerHostilityIV->addTerm(new fl::Trapezoid("veryhigh", 70, 75, 100, 100, 1));
	m_contextEngine->addInputVariable(m_playerHostilityIV);

	//	This will determine what behaviour this entity will have
	//	honest-reliable tells the truth and helps direct the player to the next objective
	//	honest-unreliable tells the truth, but only gives lore or fluff information
	//	dishonest-reliable tells lies, and as a result directs the player away from the next objective
	fl::OutputVariable* m_behaviourOV = new fl::OutputVariable;
	m_behaviourOV->setName("behaviour");
	m_behaviourOV->setDescription("");
	m_behaviourOV->setEnabled(true);
	m_behaviourOV->setRange(0, 90);
	m_behaviourOV->setLockValueInRange(true);
	m_behaviourOV->setAggregation(new fl::Maximum);
	m_behaviourOV->setDefuzzifier(new fl::Bisector());
	m_behaviourOV->setDefaultValue(fl::nan);
	m_behaviourOV->setLockPreviousValue(false);
	m_behaviourOV->addTerm(new fl::Trapezoid("honestUnreliable", 0, 0, 25, 35, 1));
	m_behaviourOV->addTerm(new fl::Trapezoid("honestReliable", 25, 35, 55, 65, 1));
	m_behaviourOV->addTerm(new fl::Trapezoid("dishonestReliable", 55, 65, 90, 90, 1));
	m_contextEngine->addOutputVariable(m_behaviourOV);

	//	This is the ruleset for the behaviourEngine
	fl::RuleBlock* m_contextMamdaniRB = new fl::RuleBlock;
	m_contextMamdaniRB->setName("contextMamdani");
	m_contextMamdaniRB->setDescription("");
	m_contextMamdaniRB->setEnabled(true);
	m_contextMamdaniRB->setConjunction(new fl::Minimum);
	m_contextMamdaniRB->setDisjunction(new fl::Maximum);
	m_contextMamdaniRB->setImplication(new fl::Minimum);
	m_contextMamdaniRB->setActivation(new fl::General);
	
	//	Constant lowstoryHonesty > Variable playStyle and playerHostility
	m_contextMamdaniRB->addRule(fl::Rule::parse("if storyHonesty is low and playStyle is slow and playerHostility is verylow then behaviour is honestReliable", m_contextEngine));
	m_contextMamdaniRB->addRule(fl::Rule::parse("if storyHonesty is low and playStyle is slow and playerHostility is low then behaviour is honestReliable", m_contextEngine));
	m_contextMamdaniRB->addRule(fl::Rule::parse("if storyHonesty is low and playStyle is slow and playerHostility is medium then behaviour is honestUnreliable", m_contextEngine));
	m_contextMamdaniRB->addRule(fl::Rule::parse("if storyHonesty is low and playStyle is slow and playerHostility is high then behaviour is honestUnreliable", m_contextEngine));
	m_contextMamdaniRB->addRule(fl::Rule::parse("if storyHonesty is low and playStyle is slow and playerHostility is veryhigh then behaviour is dishonestReliable", m_contextEngine));

	m_contextMamdaniRB->addRule(fl::Rule::parse("if storyHonesty is low and playStyle is medium and playerHostility is verylow then behaviour is honestReliable", m_contextEngine));
	m_contextMamdaniRB->addRule(fl::Rule::parse("if storyHonesty is low and playStyle is medium and playerHostility is low then behaviour is honestReliable", m_contextEngine));
	m_contextMamdaniRB->addRule(fl::Rule::parse("if storyHonesty is low and playStyle is medium and playerHostility is medium then behaviour is honestUnreliable", m_contextEngine));
	m_contextMamdaniRB->addRule(fl::Rule::parse("if storyHonesty is low and playStyle is medium and playerHostility is high then behaviour is honestUnreliable", m_contextEngine));
	m_contextMamdaniRB->addRule(fl::Rule::parse("if storyHonesty is low and playStyle is medium and playerHostility is veryhigh then behaviour is dishonestReliable", m_contextEngine));

	m_contextMamdaniRB->addRule(fl::Rule::parse("if storyHonesty is low and playStyle is fast and playerHostility is verylow then behaviour is honestReliable", m_contextEngine));
	m_contextMamdaniRB->addRule(fl::Rule::parse("if storyHonesty is low and playStyle is fast and playerHostility is low then behaviour is honestReliable", m_contextEngine));
	m_contextMamdaniRB->addRule(fl::Rule::parse("if storyHonesty is low and playStyle is fast and playerHostility is medium then behaviour is honestUnreliable", m_contextEngine));
	m_contextMamdaniRB->addRule(fl::Rule::parse("if storyHonesty is low and playStyle is fast and playerHostility is high then behaviour is honestUnreliable", m_contextEngine));
	m_contextMamdaniRB->addRule(fl::Rule::parse("if storyHonesty is low and playStyle is fast and playerHostility is veryhigh then behaviour is dishonestReliable", m_contextEngine));
	
	//	Constant medium storyHonesty > Variable playStyle and playerHostility
	m_contextMamdaniRB->addRule(fl::Rule::parse("if storyHonesty is medium and playStyle is slow and playerHostility is verylow then behaviour is honestReliable", m_contextEngine));
	m_contextMamdaniRB->addRule(fl::Rule::parse("if storyHonesty is medium and playStyle is slow and playerHostility is low then behaviour is honestUnreliable", m_contextEngine));
	m_contextMamdaniRB->addRule(fl::Rule::parse("if storyHonesty is medium and playStyle is slow and playerHostility is medium then behaviour is honestUnreliable", m_contextEngine));
	m_contextMamdaniRB->addRule(fl::Rule::parse("if storyHonesty is medium and playStyle is slow and playerHostility is high then behaviour is honestUnreliable", m_contextEngine));
	m_contextMamdaniRB->addRule(fl::Rule::parse("if storyHonesty is medium and playStyle is slow and playerHostility is veryhigh then behaviour is dishonestReliable", m_contextEngine));

	m_contextMamdaniRB->addRule(fl::Rule::parse("if storyHonesty is medium and playStyle is medium and playerHostility is verylow then behaviour is honestReliable", m_contextEngine));
	m_contextMamdaniRB->addRule(fl::Rule::parse("if storyHonesty is medium and playStyle is medium and playerHostility is low then behaviour is honestUnreliable", m_contextEngine));
	m_contextMamdaniRB->addRule(fl::Rule::parse("if storyHonesty is medium and playStyle is medium and playerHostility is medium then behaviour is honestUnreliable", m_contextEngine));
	m_contextMamdaniRB->addRule(fl::Rule::parse("if storyHonesty is medium and playStyle is medium and playerHostility is high then behaviour is dishonestReliable", m_contextEngine));
	m_contextMamdaniRB->addRule(fl::Rule::parse("if storyHonesty is medium and playStyle is medium and playerHostility is veryhigh then behaviour is dishonestReliable", m_contextEngine));

	m_contextMamdaniRB->addRule(fl::Rule::parse("if storyHonesty is medium and playStyle is fast and playerHostility is verylow then behaviour is honestReliable", m_contextEngine));
	m_contextMamdaniRB->addRule(fl::Rule::parse("if storyHonesty is medium and playStyle is fast and playerHostility is low then behaviour is honestUnreliable", m_contextEngine));
	m_contextMamdaniRB->addRule(fl::Rule::parse("if storyHonesty is medium and playStyle is fast and playerHostility is medium then behaviour is honestUnreliable", m_contextEngine));
	m_contextMamdaniRB->addRule(fl::Rule::parse("if storyHonesty is medium and playStyle is fast and playerHostility is high then behaviour is dishonestReliable", m_contextEngine));
	m_contextMamdaniRB->addRule(fl::Rule::parse("if storyHonesty is medium and playStyle is fast and playerHostility is veryhigh then behaviour is dishonestReliable", m_contextEngine));

	//	Constant highstoryHonesty > Variable playStyle and playerHostility
	m_contextMamdaniRB->addRule(fl::Rule::parse("if storyHonesty is high and playStyle is slow and playerHostility is verylow then behaviour is honestReliable", m_contextEngine));
	m_contextMamdaniRB->addRule(fl::Rule::parse("if storyHonesty is high and playStyle is slow and playerHostility is low then behaviour is honestReliable", m_contextEngine));
	m_contextMamdaniRB->addRule(fl::Rule::parse("if storyHonesty is high and playStyle is slow and playerHostility is medium then behaviour is honestUnreliable", m_contextEngine));
	m_contextMamdaniRB->addRule(fl::Rule::parse("if storyHonesty is high and playStyle is slow and playerHostility is high then behaviour is honestUnreliable", m_contextEngine));
	m_contextMamdaniRB->addRule(fl::Rule::parse("if storyHonesty is high and playStyle is slow and playerHostility is veryhigh then behaviour is dishonestReliable", m_contextEngine));

	m_contextMamdaniRB->addRule(fl::Rule::parse("if storyHonesty is high and playStyle is medium and playerHostility is verylow then behaviour is honestReliable", m_contextEngine));
	m_contextMamdaniRB->addRule(fl::Rule::parse("if storyHonesty is high and playStyle is medium and playerHostility is low then behaviour is honestReliable", m_contextEngine));
	m_contextMamdaniRB->addRule(fl::Rule::parse("if storyHonesty is high and playStyle is medium and playerHostility is medium then behaviour is honestUnreliable", m_contextEngine));
	m_contextMamdaniRB->addRule(fl::Rule::parse("if storyHonesty is high and playStyle is medium and playerHostility is high then behaviour is honestUnreliable", m_contextEngine));
	m_contextMamdaniRB->addRule(fl::Rule::parse("if storyHonesty is high and playStyle is medium and playerHostility is veryhigh then behaviour is dishonestReliable", m_contextEngine));

	m_contextMamdaniRB->addRule(fl::Rule::parse("if storyHonesty is high and playStyle is fast and playerHostility is verylow then behaviour is honestReliable", m_contextEngine));
	m_contextMamdaniRB->addRule(fl::Rule::parse("if storyHonesty is high and playStyle is fast and playerHostility is low then behaviour is honestReliable", m_contextEngine));
	m_contextMamdaniRB->addRule(fl::Rule::parse("if storyHonesty is high and playStyle is fast and playerHostility is medium then behaviour is honestUnreliable", m_contextEngine));
	m_contextMamdaniRB->addRule(fl::Rule::parse("if storyHonesty is high and playStyle is fast and playerHostility is high then behaviour is honestUnreliable", m_contextEngine));
	m_contextMamdaniRB->addRule(fl::Rule::parse("if storyHonesty is high and playStyle is fast and playerHostility is veryhigh then behaviour is dishonestReliable", m_contextEngine));
	m_contextEngine->addRuleBlock(m_contextMamdaniRB);

	//	This sets up the engine to run
	m_storyHonestyIV->setValue(m_storyHonesty);
	m_playStyleIV->setValue(m_playStyle);
	m_playerHostilityIV->setValue(m_aggression);
	//	This runs the fuzzy engine once
	m_contextEngine->process();
	//	This will save the output of the engine for later use
	ptr_behaviour = m_behaviourOV->getValue();



	//	What follows is the set up of an interaction engine for when a user talks with this entity
	ptr_interactionEngine = new fl::Engine;
	ptr_interactionEngine->setName("interactionEngine");
	ptr_interactionEngine->setDescription("");


	//	The entity behaviour was determined above by the other engine
	//	This will essentially figure out what behaviour to magnify
	ptr_entityBehaviourIV = new fl::InputVariable;
	ptr_entityBehaviourIV->setName("entityBehaviour");
	ptr_entityBehaviourIV->setDescription("");
	ptr_entityBehaviourIV->setEnabled(true);
	ptr_entityBehaviourIV->setRange(0, 90);
	ptr_entityBehaviourIV->setLockValueInRange(true);
	ptr_entityBehaviourIV->addTerm(new fl::Trapezoid("honestUnreliable", 0, 0, 25, 35, 1));
	ptr_entityBehaviourIV->addTerm(new fl::Trapezoid("honestReliable", 25, 35, 55, 65, 1));
	ptr_entityBehaviourIV->addTerm(new fl::Trapezoid("dishonestReliable", 55, 65, 90, 90, 1));
	ptr_interactionEngine->addInputVariable(ptr_entityBehaviourIV);

	//	This is how many pleasn words the user has used towards the entity
	//	These being words that are not aggressive, nor neutral
	ptr_playerPleasantryIV = new fl::InputVariable;
	ptr_playerPleasantryIV->setName("playerPleasantry");
	ptr_playerPleasantryIV->setDescription("");
	ptr_playerPleasantryIV->setEnabled(true);
	ptr_playerPleasantryIV->setRange(0, 100);
	ptr_playerPleasantryIV->setLockValueInRange(true);
	ptr_playerPleasantryIV->addTerm(new fl::Trapezoid("verylow", 0, 0, 15, 20, 1));
	ptr_playerPleasantryIV->addTerm(new fl::Trapezoid("low", 15, 20, 30, 35, 1));
	ptr_playerPleasantryIV->addTerm(new fl::Trapezoid("medium", 30, 35, 55, 60, 1));
	ptr_playerPleasantryIV->addTerm(new fl::Trapezoid("high", 55, 60, 70, 75, 1));
	ptr_playerPleasantryIV->addTerm(new fl::Trapezoid("veryhigh", 70, 75, 100, 100, 1));
	ptr_interactionEngine->addInputVariable(ptr_playerPleasantryIV);

	//	This is how many pleasn words the user has used towards the entity
	//	These being words that are not aggressive, nor neutral
	ptr_tileClassificationIV = new fl::InputVariable;
	ptr_tileClassificationIV->setName("tileClassification");
	ptr_tileClassificationIV->setDescription("");
	ptr_tileClassificationIV->setEnabled(true);
	ptr_tileClassificationIV->setRange(0, 10);
	ptr_tileClassificationIV->setLockValueInRange(true);
	ptr_tileClassificationIV->addTerm(new fl::Trapezoid("acceptable", 0, 0, 4, 6, 1));
	ptr_tileClassificationIV->addTerm(new fl::Trapezoid("cautious", 4, 6, 10, 10, 1));
	ptr_interactionEngine->addInputVariable(ptr_tileClassificationIV);

	//	This is the magitude of the entity's behaviour
	//	A honest-reliable would give the player greater amounts of useful information with greater behaviour magnitude
	ptr_behaviourMagnitudeOV = new fl::OutputVariable;
	ptr_behaviourMagnitudeOV->setName("behaviourMagnitude");
	ptr_behaviourMagnitudeOV->setDescription("");
	ptr_behaviourMagnitudeOV->setEnabled(true);
	ptr_behaviourMagnitudeOV->setRange(0, 90);
	ptr_behaviourMagnitudeOV->setLockValueInRange(true);
	ptr_behaviourMagnitudeOV->setAggregation(new fl::Maximum);
	ptr_behaviourMagnitudeOV->setDefuzzifier(new fl::Bisector());
	ptr_behaviourMagnitudeOV->setDefaultValue(fl::nan);
	ptr_behaviourMagnitudeOV->setLockPreviousValue(false);
	ptr_behaviourMagnitudeOV->addTerm(new fl::Trapezoid("low", 0, 0, 25, 35, 1));
	ptr_behaviourMagnitudeOV->addTerm(new fl::Trapezoid("medium",25, 35, 55, 65, 1));
	ptr_behaviourMagnitudeOV->addTerm(new fl::Trapezoid("high", 55, 65, 90, 90, 1));
	ptr_interactionEngine->addOutputVariable(ptr_behaviourMagnitudeOV);

	//	These are the rules for this engine
	ptr_interactionMamdaniRB = new fl::RuleBlock;
	ptr_interactionMamdaniRB->setName("interactionMamdani");
	ptr_interactionMamdaniRB->setDescription("");
	ptr_interactionMamdaniRB->setEnabled(true);
	ptr_interactionMamdaniRB->setConjunction(new fl::Minimum);
	ptr_interactionMamdaniRB->setDisjunction(new fl::Maximum);
	ptr_interactionMamdaniRB->setImplication(new fl::Minimum);
	ptr_interactionMamdaniRB->setActivation(new fl::General);
	//	Constant honestUnreliable > Variable playerPleasantry and tileClassification
	ptr_interactionMamdaniRB->addRule(fl::Rule::parse("if entityBehaviour is honestUnreliable and playerPleasantry is verylow and tileClassification is acceptable then behaviourMagnitude is high", ptr_interactionEngine));
	ptr_interactionMamdaniRB->addRule(fl::Rule::parse("if entityBehaviour is honestUnreliable and playerPleasantry is low and tileClassification is acceptable then behaviourMagnitude is high", ptr_interactionEngine));
	ptr_interactionMamdaniRB->addRule(fl::Rule::parse("if entityBehaviour is honestUnreliable and playerPleasantry is medium and tileClassification is acceptable then behaviourMagnitude is medium", ptr_interactionEngine));
	ptr_interactionMamdaniRB->addRule(fl::Rule::parse("if entityBehaviour is honestUnreliable and playerPleasantry is high and tileClassification is acceptable then behaviourMagnitude is medium", ptr_interactionEngine));
	ptr_interactionMamdaniRB->addRule(fl::Rule::parse("if entityBehaviour is honestUnreliable and playerPleasantry is veryhigh and tileClassification is acceptable then behaviourMagnitude is low", ptr_interactionEngine));

	ptr_interactionMamdaniRB->addRule(fl::Rule::parse("if entityBehaviour is honestUnreliable and playerPleasantry is verylow and tileClassification is cautious then behaviourMagnitude is high", ptr_interactionEngine));
	ptr_interactionMamdaniRB->addRule(fl::Rule::parse("if entityBehaviour is honestUnreliable and playerPleasantry is low and tileClassification is cautious then behaviourMagnitude is medium", ptr_interactionEngine));
	ptr_interactionMamdaniRB->addRule(fl::Rule::parse("if entityBehaviour is honestUnreliable and playerPleasantry is medium and tileClassification is cautious then behaviourMagnitude is medium", ptr_interactionEngine));
	ptr_interactionMamdaniRB->addRule(fl::Rule::parse("if entityBehaviour is honestUnreliable and playerPleasantry is high and tileClassification is cautious then behaviourMagnitude is low", ptr_interactionEngine));
	ptr_interactionMamdaniRB->addRule(fl::Rule::parse("if entityBehaviour is honestUnreliable and playerPleasantry is veryhigh and tileClassification is cautious then behaviourMagnitude is low", ptr_interactionEngine));
	//	Constant honestReliable > Variable playerPleasantry and tileClassification
	ptr_interactionMamdaniRB->addRule(fl::Rule::parse("if entityBehaviour is honestReliable and playerPleasantry is verylow and tileClassification is acceptable then behaviourMagnitude is low", ptr_interactionEngine));
	ptr_interactionMamdaniRB->addRule(fl::Rule::parse("if entityBehaviour is honestReliable and playerPleasantry is low and tileClassification is acceptable then behaviourMagnitude is medium", ptr_interactionEngine));
	ptr_interactionMamdaniRB->addRule(fl::Rule::parse("if entityBehaviour is honestReliable and playerPleasantry is medium and tileClassification is acceptable then behaviourMagnitude is medium", ptr_interactionEngine));
	ptr_interactionMamdaniRB->addRule(fl::Rule::parse("if entityBehaviour is honestReliable and playerPleasantry is high and tileClassification is acceptable then behaviourMagnitude is high", ptr_interactionEngine));
	ptr_interactionMamdaniRB->addRule(fl::Rule::parse("if entityBehaviour is honestReliable and playerPleasantry is veryhigh and tileClassification is acceptable then behaviourMagnitude is high", ptr_interactionEngine));

	ptr_interactionMamdaniRB->addRule(fl::Rule::parse("if entityBehaviour is honestReliable and playerPleasantry is verylow and tileClassification is cautious then behaviourMagnitude is low", ptr_interactionEngine));
	ptr_interactionMamdaniRB->addRule(fl::Rule::parse("if entityBehaviour is honestReliable and playerPleasantry is low and tileClassification is cautious then behaviourMagnitude is low", ptr_interactionEngine));
	ptr_interactionMamdaniRB->addRule(fl::Rule::parse("if entityBehaviour is honestReliable and playerPleasantry is medium and tileClassification is cautious then behaviourMagnitude is low", ptr_interactionEngine));
	ptr_interactionMamdaniRB->addRule(fl::Rule::parse("if entityBehaviour is honestReliable and playerPleasantry is high and tileClassification is cautious then behaviourMagnitude is medium", ptr_interactionEngine));
	ptr_interactionMamdaniRB->addRule(fl::Rule::parse("if entityBehaviour is honestReliable and playerPleasantry is veryhigh and tileClassification is cautious then behaviourMagnitude is medium", ptr_interactionEngine));
	//	Constant dishonestReliable > Variable playerPleasantry and tileClassification
	ptr_interactionMamdaniRB->addRule(fl::Rule::parse("if entityBehaviour is dishonestReliable and playerPleasantry is verylow and tileClassification is acceptable then behaviourMagnitude is low", ptr_interactionEngine));
	ptr_interactionMamdaniRB->addRule(fl::Rule::parse("if entityBehaviour is dishonestReliable and playerPleasantry is low and tileClassification is acceptable then behaviourMagnitude is low", ptr_interactionEngine));
	ptr_interactionMamdaniRB->addRule(fl::Rule::parse("if entityBehaviour is dishonestReliable and playerPleasantry is medium and tileClassification is acceptable then behaviourMagnitude is medium", ptr_interactionEngine));
	ptr_interactionMamdaniRB->addRule(fl::Rule::parse("if entityBehaviour is dishonestReliable and playerPleasantry is high and tileClassification is acceptable then behaviourMagnitude is medium", ptr_interactionEngine));
	ptr_interactionMamdaniRB->addRule(fl::Rule::parse("if entityBehaviour is dishonestReliable and playerPleasantry is veryhigh and tileClassification is acceptable then behaviourMagnitude is high", ptr_interactionEngine));

	ptr_interactionMamdaniRB->addRule(fl::Rule::parse("if entityBehaviour is dishonestReliable and playerPleasantry is verylow and tileClassification is cautious then behaviourMagnitude is medium", ptr_interactionEngine));
	ptr_interactionMamdaniRB->addRule(fl::Rule::parse("if entityBehaviour is dishonestReliable and playerPleasantry is low and tileClassification is cautious then behaviourMagnitude is medium", ptr_interactionEngine));
	ptr_interactionMamdaniRB->addRule(fl::Rule::parse("if entityBehaviour is dishonestReliable and playerPleasantry is medium and tileClassification is cautious then behaviourMagnitude is high", ptr_interactionEngine));
	ptr_interactionMamdaniRB->addRule(fl::Rule::parse("if entityBehaviour is dishonestReliable and playerPleasantry is high and tileClassification is cautious then behaviourMagnitude is high", ptr_interactionEngine));
	ptr_interactionMamdaniRB->addRule(fl::Rule::parse("if entityBehaviour is dishonestReliable and playerPleasantry is veryhigh and tileClassification is cautious then behaviourMagnitude is high", ptr_interactionEngine));
	//	Add these rules to the ruleblock to the engine proper
	ptr_interactionEngine->addRuleBlock(ptr_interactionMamdaniRB);

}


FuzzyBehaviour::~FuzzyBehaviour() {

}

std::string FuzzyBehaviour::interactionProcess(std::string userText_in) {
	addInteractionLog(userText_in);

	int m_classification;
	if (c_classification == "acceptable") {
		m_classification = 2;
	}
	else if (c_classification == "cautious") {
		m_classification = 8;
	}
	ptr_entityBehaviourIV->setValue(ptr_behaviour);
	ptr_playerPleasantryIV->setValue(2);
	ptr_tileClassificationIV->setValue(2);

	ptr_interactionEngine->process();
	
	return ptr_naturalLogicManager->fuzzyBehaviourBoardProcessing(ptr_behaviour, ptr_behaviourMagnitudeOV->getValue(), c_nextPlotPoint, c_currentLocation); 
}

std::string FuzzyBehaviour::interactionProcessTesting(int pleasantry_in, std::string classification_in) {
	int m_classification;
	if (classification_in == "acceptable") {
		m_classification = 2;
	}
	else if (classification_in == "cautious") {
		m_classification = 8;
	}

	ptr_entityBehaviourIV->setValue(ptr_behaviour);
	ptr_playerPleasantryIV->setValue(pleasantry_in);
	ptr_tileClassificationIV->setValue(m_classification);

	ptr_interactionEngine->process();

	return "empty";
}


void FuzzyBehaviour::addInteractionLog(std::string& userText_in) {
	if (v_playerStrings.size() >= 16) 
		v_playerStrings.erase(v_playerStrings.begin());

	v_playerStrings.push_back(userText_in);

}

float FuzzyBehaviour::getBehaviourTesting() {
	return ptr_behaviour;
}

float FuzzyBehaviour::getMagnitudeTesting() {
	fl::scalar m_magnitude = ptr_behaviourMagnitudeOV->getValue();
	return m_magnitude;
}