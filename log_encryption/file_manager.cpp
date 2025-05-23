#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "file_manager.h"

bool FileManager::save_sequence(const string& filename, LCG& lcg, int count) {
    if (!lcg.is_ready()) {
        cout << "Generator not initialized. Set parameters first.\n";
        return false;
    }
    ofstream out(filename, ios::binary);
    if (!out) {
        cout << "Failed to open file for saving sequence.\n";
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
    // ³�������� ���� �� �����
    ifstream in(filename);
    if (!in) {
        cout << "Failed to open file.\n";
        return vector<char>();
    }

    // ������� ���� ����� �� �����
    string content;
    string line;
    while (getline(in, line)) {
        // ��������� \r, ���� � (��� �������� � Windows)
        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }
        content += line;
    }
    in.close();

    // ���������� � vector<char>
    vector<char> data(content.begin(), content.end());
    return data;
}

bool FileManager::write_file(const string& filename, const vector<char>& data) {
    // ³�������� ���� � �������� �����, ��� �������� ��������� \r\n
    ofstream out(filename, ios::binary);
    if (!out) {
        cout << "Failed to open file for writing.\n";
        return false;
    }
    out.write(data.data(), data.size());
    out.close();
    return true;
}