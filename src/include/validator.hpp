#ifndef VALIDATOR_HPP
#define VALIDATOR_HPP

#include "config.hpp"
#include <optional>
#include <string>

std::optional<std::string> validate_config(const Config& config);

#endif // VALIDATOR_HPP
