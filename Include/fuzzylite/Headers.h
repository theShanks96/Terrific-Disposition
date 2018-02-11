/*
 fuzzylite (R), a fuzzy logic control library in C++.
 Copyright (C) 2010-2017 FuzzyLite Limited. All rights reserved.
 Author: Juan Rada-Vilela, Ph.D. <jcrada@fuzzylite.com>

 This file is part of fuzzylite.

 fuzzylite is free software: you can redistribute it and/or modify it under
 the terms of the FuzzyLite License included with the software.

 You should have received a copy of the FuzzyLite License along with
 fuzzylite. If not, see <http://www.fuzzylite.com/license/>.

 fuzzylite is a registered trademark of FuzzyLite Limited.
 */

#ifndef FL_HEADERS_H
#define FL_HEADERS_H

/**
    The Headers.h file contains the headers of all the classes in the
    `fuzzylite` library, thereby encouraging the use of the directive `#include
    "fl/Headers.h"` in projects using the library.
 */


#define NOMINMAX

#include "fuzzylite.h"

#include "Benchmark.h"
#include "Complexity.h"
#include "Console.h"
#include "Engine.h"
#include "Exception.h"

#include "activation/Activation.h"
#include "activation/First.h"
#include "activation/General.h"
#include "activation/Highest.h"
#include "activation/Last.h"
#include "activation/Lowest.h"
#include "activation/Proportional.h"
#include "activation/Threshold.h"

#include "defuzzifier/Bisector.h"
#include "defuzzifier/Centroid.h"
#include "defuzzifier/Defuzzifier.h"
#include "defuzzifier/IntegralDefuzzifier.h"
#include "defuzzifier/SmallestOfMaximum.h"
#include "defuzzifier/LargestOfMaximum.h"
#include "defuzzifier/MeanOfMaximum.h"
#include "defuzzifier/WeightedAverage.h"
#include "defuzzifier/WeightedDefuzzifier.h"
#include "defuzzifier/WeightedSum.h"

#include "factory/ActivationFactory.h"
#include "factory/CloningFactory.h"
#include "factory/ConstructionFactory.h"
#include "factory/FactoryManager.h"
#include "factory/FunctionFactory.h"
#include "factory/DefuzzifierFactory.h"
#include "factory/HedgeFactory.h"
#include "factory/SNormFactory.h"
#include "factory/TNormFactory.h"
#include "factory/TermFactory.h"

#include "imex/CppExporter.h"
#include "imex/FclImporter.h"
#include "imex/FclExporter.h"
#include "imex/FisImporter.h"
#include "imex/FisExporter.h"
#include "imex/FldExporter.h"
#include "imex/FllImporter.h"
#include "imex/FllExporter.h"
#include "imex/JavaExporter.h"
#include "imex/RScriptExporter.h"

#include "hedge/Any.h"
#include "hedge/Extremely.h"
#include "hedge/Hedge.h"
#include "hedge/HedgeFunction.h"
#include "hedge/Not.h"
#include "hedge/Seldom.h"
#include "hedge/Somewhat.h"
#include "hedge/Very.h"

#include "Operation.h"

#include "norm/Norm.h"
#include "norm/SNorm.h"
#include "norm/TNorm.h"

#include "norm/s/AlgebraicSum.h"
#include "norm/s/BoundedSum.h"
#include "norm/s/DrasticSum.h"
#include "norm/s/EinsteinSum.h"
#include "norm/s/HamacherSum.h"
#include "norm/s/Maximum.h"
#include "norm/s/NilpotentMaximum.h"
#include "norm/s/NormalizedSum.h"
#include "norm/s/SNormFunction.h"
#include "norm/s/UnboundedSum.h"

#include "norm/t/AlgebraicProduct.h"
#include "norm/t/BoundedDifference.h"
#include "norm/t/DrasticProduct.h"
#include "norm/t/EinsteinProduct.h"
#include "norm/t/HamacherProduct.h"
#include "norm/t/Minimum.h"
#include "norm/t/NilpotentMinimum.h"
#include "norm/t/TNormFunction.h"

#include "rule/Antecedent.h"
#include "rule/Consequent.h"
#include "rule/Rule.h"
#include "rule/RuleBlock.h"
#include "rule/Expression.h"

#include "term/Aggregated.h"
#include "term/Bell.h"
#include "term/Binary.h"
#include "term/Concave.h"
#include "term/Constant.h"
#include "term/Cosine.h"
#include "term/Discrete.h"
#include "term/Function.h"
#include "term/Gaussian.h"
#include "term/GaussianProduct.h"
#include "term/Linear.h"
#include "term/PiShape.h"
#include "term/Ramp.h"
#include "term/Rectangle.h"
#include "term/SShape.h"
#include "term/Sigmoid.h"
#include "term/SigmoidDifference.h"
#include "term/SigmoidProduct.h"
#include "term/Spike.h"
#include "term/Term.h"
#include "term/Activated.h"
#include "term/Trapezoid.h"
#include "term/Triangle.h"
#include "term/ZShape.h"

#include "variable/InputVariable.h"
#include "variable/OutputVariable.h"
#include "variable/Variable.h"


#endif /* FL_HEADERS_H */
