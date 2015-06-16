#include "truck_client.h"

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
        ServerResposePackage data = client.getTruckData();
        std::cout << "x = " << data.x << " - "
            << "y = " << data.y << " - "
            << "angle = " << data.angle;
        client.sendTruckInstruction( 30 ); // 30 degrees
    }
    return 0;
}
