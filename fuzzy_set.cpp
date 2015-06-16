#include <limits>
#include <stdexcept>
#include "fuzzy_set.h"

namespace {
    constexpr double machine_epsilon = std::numeric_limits<double>::epsilon();
} // anonymous namespace


FuzzySet::FuzzySet( double le, double lm, double rm, double re ) :
    le( le ),
    lm( lm ),
    rm( rm ),
    re( re )
{
    if( le > lm || lm > rm || rm > re )
        throw std::logic_error( "Inconsistent fuzzy limits." );
}

double FuzzySet::pertinence( double d ) const {
    if( d < le || d > re )
        return 0.0;
    if( d > lm && d < rm )
        return 1.0;

    if( d <= lm ) {// && d >= le
        if( lm - le <= machine_epsilon )
            return 0.5;
        return (d - le)/(lm - le);
    }
    else {// d >= rm  && d <= re
        if( re - rm <= machine_epsilon )
            return 0.5;
        return (re - d)/(re - rm);
    }
}
