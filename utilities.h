#ifndef UTILITIES_H
#define UTILITIES_H

#include <string>

class Utilities {
    public:
        std::string hexToString(unsigned short, bool);
        std::string hexToString(unsigned short);
        std::string opcodeToString(unsigned short);
};

#endif