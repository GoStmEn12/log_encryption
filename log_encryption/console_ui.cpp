#include <iostream>
#include "console_ui.h"
#include "utils.h"

void ConsoleUI::show_menu() {
    cout << "=================Main Menu=================\n";
    cout << "1. Set generator parameters\n";
    cout << "2. Generate and save sequence of numbers\n";
    cout << "3. Encrypt text message\n";
    cout << "4. Encrypt file\n";
    cout << "5. Decrypt file\n";
    cout << "6. Exit\n";
    cout << "Make your choice: ";
}

char ConsoleUI::get_choice() {
    char choice;
    cin >> choice;
    return choice;
}

void ConsoleUI::get_parameters(unsigned long long& a, unsigned long long& c, unsigned long long& m, unsigned long long& x0) {
    string input_a, input_c, input_m, input_x0;
    bool valid = false;

    do {
        cout << "Enter a (multiplier): ";
        cin.ignore();
        getline(cin, input_a);
        if (!isValidNumber(input_a, a)) {
            cout << "Invalid input for a! Enter a valid integer.\n";
            continue;
        }

        cout << "Enter c (increment): ";
        getline(cin, input_c);
        if (!isValidNumber(input_c, c)) {
            cout << "Invalid input for c! Enter a valid integer.\n";
            continue;
        }

        cout << "Enter m (modulus, m > 0): ";
        getline(cin, input_m);
        if (!isValidNumber(input_m, m)) {
            cout << "Invalid input for m! Enter a valid integer.\n";
            continue;
        }

        cout << "Enter x0 (initial value): ";
        getline(cin, input_x0);
        if (!isValidNumber(input_x0, x0)) {
            cout << "Invalid input for x0! Enter a valid integer.\n";
            continue;
        }

        valid = true;
    } while (!valid);
}

string ConsoleUI::get_filename(const string& prompt) {
    string filename;
    cout << prompt;
    cin.ignore();
    getline(cin, filename);
    return filename;
}

int ConsoleUI::get_sequence_count() {
    int count;
    cout << "Enter the number of values to generate: ";
    cin >> count;
    return count;
}

string ConsoleUI::get_text_to_encrypt() {
    string message;
    cout << "Enter text to encrypt: ";
    cin.ignore();
    getline(cin, message);
    return message;
}

void ConsoleUI::show_encrypted_decrypted_text(const vector<char>& encrypted, const vector<char>& decrypted) {
    cout << "Encrypted text: ";
    for (char ch : encrypted) cout << ch;
    cout << "\n";

    cout << "Decrypted text: ";
    for (char ch : decrypted) cout << ch;
    cout << "\n";
}

void ConsoleUI::show_message(const string& message) {
    cout << message << "\n";
}