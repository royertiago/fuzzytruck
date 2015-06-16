#include <algorithm>
#include <cmath>
#include "fuzzy_rule_set.h"

FuzzyRuleSet::FuzzyRuleSet( std::vector<FuzzyRule> rules ) :
    rules( rules )
{}

double FuzzyRuleSet::operator()( double x, double y, double angle ) const {
    angle = std::fmod( angle + 180.0, 360.0 ) - 180.0;

    double output_sum = 0.0;
    double weight_sum = 0.0;
    for( double output = -30.0; output <= 30.0; output += 1.0 ) {
        double max_weight = 0.0;
        for( const auto & rule : rules )
            max_weight = std::max( max_weight, rule(x, y, angle, output) );
        weight_sum += max_weight;
        output_sum += max_weight * output;
    }

    return std::fmod( output_sum/weight_sum + 180.0, 360.0 ) - 180.0;
}
