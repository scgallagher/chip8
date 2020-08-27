#include "utilities.h"
#include <string>
#include <sstream>
#include <boost/algorithm/string.hpp>

std::string Utilities::hexToString(unsigned short hexCode, bool includePrefix) {
    std::stringstream ss;
    ss << std::hex << hexCode;
    std::string hexString = boost::to_upper_copy<std::string>(ss.str());

    if (includePrefix) {
        hexString = "0x" + hexString;
    }

    return hexString;
}

std::string Utilities::hexToString(unsigned short hexCode) {
    return Utilities::hexToString(hexCode, true);
}

std::string Utilities::opcodeToString(unsigned short hexCode) {
    std::string instruction = Utilities::hexToString(hexCode, false);
    if (instruction.length() == 2) {
        instruction = "00" + instruction;
    }
    return "0x" + instruction;
}