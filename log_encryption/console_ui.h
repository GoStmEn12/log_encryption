#pragma once
#ifndef CONSOLE_UI_H
#define CONSOLE_UI_H

#include <string>
#include <vector>
using namespace std;
class ConsoleUI {
public:
    void show_menu();
    char get_choice();
    void get_parameters(unsigned long long& a, unsigned long long& c, unsigned long long& m, unsigned long long& x0);
    string get_filename(const string& prompt);
    int get_sequence_count();
    string get_text_to_encrypt();
    void show_encrypted_decrypted_text(const vector<char>& encrypted, const vector<char>& decrypted);
    void show_message(const string& message);
};

#endif
