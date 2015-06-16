#ifndef FUZZY_RULE_SET_H
#define FUZZY_RULE_SET_H

/* Class that takes the compound decision
 * for a set of fuzzy rules.
 *
 * For simplicity, we consider only the special case with three input variables
 * and the output variable is a angle in degrees between -30 and 30.
 */

#include <vector>
#include "fuzzy_rule.h"

class FuzzyRuleSet {
    std::vector<FuzzyRule> rules;

public:
    FuzzyRuleSet( std::vector<FuzzyRule> );

    // Computes the target rule.
    double operator()( double x, double y, double angle ) const;
};

#endif // FUZZY_RULE_SET_H
