#include <algorithm>
#include "fuzzy_rule.h"

FuzzyRule::FuzzyRule( FuzzySet i1, FuzzySet i2, FuzzySet i3, FuzzySet output ) :
    input{ i1, i2, i3 },
    output( output )
{}

double FuzzyRule::intensity( double x, double y, double z, double out ) const {
    return std::min( std::min( std::min(
        input[0](x),
        input[1](y)),
        input[2](z)),
        output(out)
    );
}
