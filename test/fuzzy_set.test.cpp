#include "fuzzy_set.h"
#include <catch.hpp>

TEST_CASE( "FuzzySet wrong constructors", "[FuzzySet][exception]" ) {
    CHECK_THROWS( FuzzySet( 1.0, 0.0, 2.0, 3.0 ) );
    CHECK_THROWS( FuzzySet( 0.0, 2.0, 1.0, 3.0 ) );
    CHECK_THROWS( FuzzySet( 0.0, 1.0, 3.0, 2.0 ) );
    CHECK_NOTHROW( FuzzySet( 0.0, 0.0, 1.0, 2.0 ) );
    CHECK_NOTHROW( FuzzySet( 0.0, 1.0, 1.0, 2.0 ) );
    CHECK_NOTHROW( FuzzySet( 0.0, 1.0, 2.0, 2.0 ) );
}

TEST_CASE( "FuzzySet membership", "[FuzzySet]" ) {
    FuzzySet square( 0.0, 0.0, 1.0, 1.0 );
    CHECK( square(-1.0) == 0.0 );
    CHECK( square(2.0) == 0.0 );
    CHECK( square(0.5) == 1.0 );
    CHECK( square(0.0) == 0.5 );
    CHECK( square(1.0) == 0.5 );

    FuzzySet triangle( 0.0, 1.0, 1.0, 2.0 );
    CHECK( triangle(0.0) == 0.0 );
    CHECK( triangle(2.0) == 0.0 );
    CHECK( triangle(1.0) == 1.0 );
    CHECK( triangle(0.5) == Approx( 0.5 ) );
    CHECK( triangle(1.5) == Approx( 0.5 ) );
    CHECK( triangle(0.2) == Approx( 0.2 ) );
    CHECK( triangle(1.8) == Approx( 0.2 ) );
    CHECK( triangle(0.8) == Approx( 0.8 ) );
    CHECK( triangle(1.2) == Approx( 0.8 ) );

    FuzzySet trapezoid( 0.0, 1.0, 3.0, 5.0 );
    CHECK( trapezoid( 0.0 ) == 0.0 );
    CHECK( trapezoid( 5.0 ) == 0.0 );
    CHECK( trapezoid( 1.0 ) == 1.0 );
    CHECK( trapezoid( 3.0 ) == 1.0 );
    CHECK( trapezoid( 0.5 ) == Approx( 0.5 ) );
    CHECK( trapezoid( 0.2 ) == Approx( 0.2 ) );
    CHECK( trapezoid( 0.8 ) == Approx( 0.8 ) );
    CHECK( trapezoid( 3.4 ) == Approx( 0.8 ) );
    CHECK( trapezoid( 4.0 ) == Approx( 0.5 ) );
    CHECK( trapezoid( 4.6 ) == Approx( 0.2 ) );
}
