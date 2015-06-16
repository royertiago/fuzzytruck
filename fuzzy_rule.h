#ifndef FUZZY_RULE_H
#define FUZZY_RULE_H

/* Class that encapsulates a single fuzzy rule.
 *
 * For simplicity, we will treat only the special case
 * with three inputs combined with AND.
 */

#include "fuzzy_set.h"

class FuzzyRule {
    FuzzySet input[3];
    FuzzySet output;

public:
    FuzzyRule( FuzzySet, FuzzySet, FuzzySet, FuzzySet output );

    /* Returns the intensity of which this rule is actived
     * for the given output value.
     *
     * Se the documentation for details.
     */
    double intensity( double, double, double, double output_value ) const;
    double operator()( double x, double y, double angle, double output ) const {
        return intensity( x, y, angle, output );
    }
};

#endif // FUZZY_RULE_H
