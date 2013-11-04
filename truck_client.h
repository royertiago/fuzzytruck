#ifndef TRUCK_CLIENT_H_
#define TRUCK_CLIENT_H_

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <sstream>
#include <sys/socket.h>
#include <netdb.h>
#include <exception>

struct ServerResposePackage{
    double x;
    double y;
    double angle;
    ServerResposePackage():
        x(0),
        y(0),
        angle(0){}
};

class TruckClientException: public std::exception {
private:
    const char *_msg;

public:
    TruckClientException(const char *msg) : _msg(msg) {};

    virtual const char* what() const throw() {
        return _msg;
    }
};

class TruckClient {
private:
    int _socketfd;
    bool _debug;

    inline ServerResposePackage _parseTruckData(char *raw_data);

public:
    static const char *DEFAULT_HOST;
    static const char *DEFAULT_PORT;
    static const char *PLAYER1_PORT;
    static const char *PLAYER2_PORT;

    TruckClient();
    void setDebug(bool debug);
    void conn(const char *host, const char *port);
    ServerResposePackage getTruckData();
    void sendTruckInstruction(double instruction);
};

#endif /* TRUCK_CLIENT_H_ */
