#ifndef PARSER_HPP
#define PARSER_HPP

#include "config.hpp"
#include <optional>

std::optional<Config> parse_arguments(int argc, char* argv[], bool& help_requested);
void print_usage(const char* program_name);

#endif // PARSER_HPP
