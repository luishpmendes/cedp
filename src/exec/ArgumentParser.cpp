#include "ArgumentParser.hpp"
#include <algorithm>

/*
 * Constructs a new argument parser.
 * @param argc the number of arguments.
 * @param argv the array of arguments.
 */
ArgumentParser::ArgumentParser(int argc, char * argv[]) {
    for (int i = 1; i < argc; i++) {
        this->tokens.push_back(std::string(argv[i]));
    }
}

/*
 * Returns the value of the specified option.
 *
 * @param the option whose value is to be returned.
 *
 * @return the value of the specified option.
 */
std::string ArgumentParser::getCmdOption(const std::string & option) const {
    std::vector<std::string>::const_iterator it = std::find(
            this->tokens.begin(), this->tokens.end(), option);

    if (it != this->tokens.end() && ++it != this->tokens.end()) {
        return *it;
    }

    return std::string("");
}

/*
 * Verifies whether the specified option exists.
 *
 * @param option the option whose existence is to be verified.
 *
 * @return true if the specified option exists; false otherwise.
 */
bool ArgumentParser::cmdOptionExists(const std::string & option) const {
    return (std::find(this->tokens.begin(), this->tokens.end(), option) != this->tokens.end());
}

