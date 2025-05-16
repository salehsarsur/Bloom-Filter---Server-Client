#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include "BloomFilter.h"
#include "StdHashFunction.h"
#include "DoubleStdHashFunction.h"
#include "IHTTPMethods.h"
#include "PostMethod.h"
#include "GetMethod.h"
#include "DeleteMethod.h"
#include <sstream>
#include <regex>
using namespace std;

// server class handles HTTP requests: listens for incoming connections, processes commands, and manages BloomFilter
class Server {
private:
    int m_port; // port on which the server listens
    map<string, IHTTPMethods*> methods; // maps HTTP methods (POST, GET, DELETE) to their respective handlers

    bool parseConfigurationArguments(int argc, char* argv[], string& line); // parses configuration arguments
    int setupSocket(); // sets up the server socket
    int acceptClient(int server_sock); // accepts a client connection
    void initializeBloomFilter(const string& config_line); // initializes BloomFilter with configuration
    void handleClient(int client_sock); // handles communication with a connected client
    void initializeMethods(); // initializes HTTP method handlers (POST, GET, DELETE)

public:
    void run(int argc, char* argv[]); // main server run function
};
