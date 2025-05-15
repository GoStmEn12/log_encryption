#pragma once
#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <string>
#include <vector>
#include "lcg.h"
using namespace std;

class FileManager {
public:
    bool save_sequence(const string& filename, LCG& lcg, int count);
    vector<char> read_file(const string& filename);
    bool write_file(const string& filename, const vector<char>& data);
};

#endif
