#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "file_manager.h"


bool FileManager::save_sequence(const string& filename, LCG& lcg, int count) {
    if (!lcg.is_ready()) {
        cout << "Генератор не ініціалізований. Спочатку налаштуйте параметри.\n";
        return false;
    }
    ofstream out(filename, ios::binary);
    if (!out) {
        cout << "Не вдалося відкрити файл для збереження послідовності.\n";
        return false;
    }

    lcg.reset();
    for (int i = 0; i < count; i++) {
        unsigned long long val = lcg.next();
        out.write(reinterpret_cast<char*>(&val), sizeof(val));
    }
    out.close();
    return true;
}

vector<char> FileManager::read_file(const string& filename) {
    ifstream in(filename, ios::binary);
    if (!in) {
        cout << "Не вдалося відкрити файл.\n";
        return vector<char>();
    }

    in.seekg(0, ios::end);
    size_t size = in.tellg();
    in.seekg(0, ios::beg);
    vector<char> data(size);
    in.read(data.data(), size);
    in.close();
    return data;
}

bool FileManager::write_file(const string& filename, const vector<char>& data) {
    ofstream out(filename, ios::binary);
    if (!out) {
        cout << "Не вдалося відкрити файл для запису.\n";
        return false;
    }
    out.write(data.data(), data.size());
    out.close();
    return true;
}