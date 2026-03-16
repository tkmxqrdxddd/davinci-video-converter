#ifndef VALIDATOR_HPP
#define VALIDATOR_HPP

#include "config.hpp"
#include <string>

bool validate_config(const Config& config, std::string& error);

#endif // VALIDATOR_HPP
