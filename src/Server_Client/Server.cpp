#include "Server.h"

// runs the server: parses configuration, sets up socket, accepts client, initializes filter, and handles requests
void Server::run(int argc, char* argv[]) {
    string config_line;
    if (!parseConfigurationArguments(argc, argv, config_line)) return;

    int server_sock = setupSocket();
    if (server_sock < 0) return;

    int client_sock = acceptClient(server_sock);
    if (client_sock < 0) return;

    initializeBloomFilter(config_line);
    initializeMethods();
    handleClient(client_sock);

    close(client_sock);
    close(server_sock);
}

// parses configuration arguments passed to the server, validates format
bool Server::parseConfigurationArguments(int argc, char* argv[], string& line) {
    regex config(R"(^\d+( [12])+$)");
    m_port = stoi(argv[1]);
    for (int i = 2; i < argc; ++i) {
        line += argv[i];
        if (i < argc - 1) line += " ";
    }
    return regex_match(line, config);
}

// sets up the server socket, binds and listens for client connections
int Server::setupSocket() {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("error creating socket");
        return -1;
    }

    struct sockaddr_in sin = {};
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons(m_port);

    if (bind(sock, (struct sockaddr*)&sin, sizeof(sin)) < 0) {
        perror("error binding socket");
        close(sock);
        return -1;
    }

    if (listen(sock, 5) < 0) {
        perror("error listening to socket");
        close(sock);
        return -1;
    }

    return sock;
}

// accepts client connections and returns the client socket
int Server::acceptClient(int server_sock) {
    struct sockaddr_in client_sin;
    unsigned int addr_len = sizeof(client_sin);
    int client_sock = accept(server_sock, (struct sockaddr*)&client_sin, &addr_len);
    if (client_sock < 0) {
        perror("error accepting client");
    }
    return client_sock;
}

// initializes the BloomFilter with given configuration and loads blacklist
void Server::initializeBloomFilter(const string& config_line) {
    istringstream iss(config_line);
    int size, type;
    iss >> size;
    vector<IHashFunction*> hashers;
    while (iss >> type) {
        if (type == 1) hashers.push_back(new StdHashFunction());
        else hashers.push_back(new DoubleStdHashFunction());
    }
    BloomFilter::initBloomFilter(size, hashers);
    BloomFilter::getInstance().loadBlacklistFromFile("data/blacklist.txt");
    BloomFilter::getInstance().saveToFile("data/bloom.dat");
}

// initializes HTTP methods (POST, GET, DELETE) for the server
void Server::initializeMethods() {
    IHTTPMethods* Post = new PostMethod();
    IHTTPMethods* Get = new GetMethod();
    IHTTPMethods* Delete = new DeleteMethod();

    methods["POST"] = Post;
    methods["GET"] = Get;
    methods["DELETE"] = Delete;
}

// handles incoming client requests, processes HTTP methods, and sends responses
void Server::handleClient(int client_sock) {
    char buffer[4096];
    int expected_data_len = sizeof(buffer);
    string cmd, url;
    const char* Bad = "400 Bad Request\n";

    regex cmdR(R"(^((POST|GET|DELETE)) \S+$)"), urlR(R"(^((https?:\/\/)?(www\.)?([\w-]+\.)+\w{2,})(\/\S*)?$)");

    while (true) {
        memset(buffer, 0, expected_data_len);
        int read_bytes = recv(client_sock, buffer, expected_data_len, 0);
        if (read_bytes <= 0) continue;

        string msg(buffer, read_bytes);
        istringstream iss(msg);
        iss >> cmd >> url;
        string response;
        int sent_bytes = 0;
        if (regex_match(msg, cmdR) && regex_match(url, urlR) && methods.count(cmd)) {
            try {
                response = methods[cmd]->execute(url);
                sent_bytes = send(client_sock, response.c_str(), response.size(), 0);
            } catch (...) {
                sent_bytes = send(client_sock, Bad, strlen(Bad), 0);
            }
        } else {
            sent_bytes = send(client_sock, Bad, strlen(Bad), 0);
        }

        if (sent_bytes < 0) {
            perror("error sending to client");
            break;
        }
    }
}
