#include "DeleteMethod.h"

// constructor for DeleteMethod
DeleteMethod::DeleteMethod() {}

// executes the DELETE method: tries to remove a URL from the blacklist
// returns "204 No Content" if deleted, "404 Not Found" if the URL was not found
string DeleteMethod::execute(string url) {
    const char* Delete1 = "204 No Content\n";
    const char* Delete2 = "404 Not Found\n";

    bool deleted = BloomFilter::getInstance().deleteFromBlacklist(url, "data/blacklist.txt");

    return deleted ? Delete1 : Delete2;
}
