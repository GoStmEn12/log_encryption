#pragma once
#ifndef LCG_H
#define LCG_H

#include <vector>
using namespace std;

class LCG {
private:
    unsigned long long a, c, m, x0, current_x;
    bool is_initialized;

public:
    LCG();
    bool set_parameters(unsigned long long a_, unsigned long long c_, unsigned long long m_, unsigned long long x0_);
    unsigned long long next();
    void reset();
    bool is_ready() const;
    vector<char> encrypt_decrypt(const vector<char>& data, int length);
};

#endif