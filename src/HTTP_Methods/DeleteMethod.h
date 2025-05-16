#ifndef DELETEMETHOD_H
#define DELETEMETHOD_H

#include "IHTTPMethods.h"

// DeleteMethod handles the HTTP DELETE operation
// it removes a URL from the blacklist

class DeleteMethod : public IHTTPMethods {
public:
    DeleteMethod(); // constructor
    string execute(string url); // executes the DELETE method for the given URL
};

#endif
