#pragma once
#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <regex>

bool isValidNumber(const std::string& input, unsigned long long& value);
bool isValidFilename(const std::string& filename);

#endif
