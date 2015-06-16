#include <cmath>
#include <limits>
#include "truck_client.h"
#include "fuzzy_rule_set.h"

namespace rules {
    constexpr double inf = std::numeric_limits<double>::infinity();

    // Concepts for x
    FuzzySet left( -inf, -inf, -0.4, 0.0 );
    FuzzySet center( -0.4, 0.0, 0.0, 0.4 );
    FuzzySet right( 0.0, 0.4, inf, inf );

    // Concepts for y
    FuzzySet far( -inf, -inf, 0.2, 0.8 );
    FuzzySet near( 0.2, 0.8, inf, inf );

    // Concepts for angle
    FuzzySet a_straight( -5, 0, 0, 5 );
    FuzzySet a_left( -20, -5, -5, 0 );
    FuzzySet a_right( 0, 5, 5, 20 );
    FuzzySet a_very_left( -inf, -inf, -20, -5 );
    FuzzySet a_very_right( 5, 20, inf, inf );

    // Wildard concept
    FuzzySet any( -inf, -inf, inf, inf );

    FuzzyRuleSet rules({
        FuzzyRule( left, any, a_very_left, a_very_right ),
        FuzzyRule( left, any, a_very_right, a_very_right ),
        FuzzyRule( right, any, a_very_left, a_very_left ),
        FuzzyRule( right, any, a_very_right, a_very_left ),
        FuzzyRule( center, any, a_very_left, a_very_right ),
        FuzzyRule( center, any, a_very_right, a_very_left ),
        FuzzyRule( left, far, a_left, a_very_right ),
        FuzzyRule( left, far, a_right, a_very_right ),
        FuzzyRule( left, far, a_straight, a_very_right ),
        FuzzyRule( right, far, a_left, a_very_left ),
        FuzzyRule( right, far, a_right, a_very_left ),
        FuzzyRule( right, far, a_straight, a_very_left ),
        FuzzyRule( center, far, a_left, a_very_right ),
        FuzzyRule( center, far, a_right, a_very_left ),
        FuzzyRule( center, any, a_straight, a_straight ),
        FuzzyRule( left, near, a_left, a_right ),
        FuzzyRule( left, near, a_right, a_right ),
        FuzzyRule( left, near, a_straight, a_right ),
        FuzzyRule( right, near, a_left, a_left ),
        FuzzyRule( right, near, a_right, a_left ),
        FuzzyRule( right, near, a_straight, a_left ),
        FuzzyRule( center, near, a_left, a_right ),
        FuzzyRule( center, near, a_right, a_left ),
    });
} // namespace rules

int main() {
    TruckClient client;
    try {
        client.conn( TruckClient::DEFAULT_HOST, TruckClient::DEFAULT_PORT );
    }
    catch( TruckClientException & ex ) {
        std::cout << "Error on TruckClient::conn: " << ex.what() << "\n"
            << "Maybe you forgot to run 'java -jar jar/fuzzy_truck.jar'?"
            << std::endl;
        return 1;
    }

    while( true ) {
        ServerResponsePackage data = client.getTruckData();
        // Normalize the angle so that 0.0 points toward the parking lot.
        data.angle = std::fmod( data.angle + 90, 360.0 ) - 180.0;
        data.x -= 0.5;

        double instruction = rules::rules( data.x, data.y, data.angle );

        std::cout << "x = " << data.x << " - "
            << "y = " << data.y << " - "
            << "angle = " << data.angle << " - "
            << "sent = " << instruction << '\n';
        client.sendTruckInstruction( instruction ); // 30 degrees
    }
    return 0;
}
