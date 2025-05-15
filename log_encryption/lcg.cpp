#include "lcg.h"


LCG::LCG() : a(0), c(0), m(0), x0(0), current_x(0), is_initialized(false) {}

bool LCG::set_parameters(unsigned long long a, unsigned long long c, unsigned long long m, unsigned long long x0) {
    if (m <= 0 || a >= m || c >= m || x0 >= m) {
        return false;
    }
    this->a = a;
    this->c = c;
    this->m = m;
    this->x0 = x0;
    current_x = x0;
    is_initialized = true;
    return true;
}

unsigned long long LCG::next() {
    if (!is_initialized) return 0;
    current_x = (a * current_x + c) % m;
    return current_x;
}

void LCG::reset() {
    current_x = x0;
}

bool LCG::is_ready() const {
    return is_initialized;
}

vector<char> LCG::encrypt_decrypt(const vector<char>& data, int length) {
    vector<char> result = data;
    reset();
    for (int i = 0; i < length; i++) {
        unsigned long long key = next();
        char key_byte = static_cast<char>(key & 0xFF);
        result[i] = data[i] ^ key_byte;
    }
    return result;
}