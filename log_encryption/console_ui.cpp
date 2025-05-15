#include <iostream>
#include "console_ui.h"
#include "utils.h"

void ConsoleUI::show_menu() {
    cout << "\t����\n";
    cout << "1- ����������� ��������� ����������\n";
    cout << "2- ����������� �� �������� ����������� �����\n";
    cout << "3- ����������� �������� �����������\n";
    cout << "4- ����������� ����\n";
    cout << "5- ������������ ����\n";
    cout << "6- �����\n";
    cout << "������ ����: ";
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
        cout << "������ a (�������): ";
        cin.ignore();
        getline(cin, input_a);
        if (!isValidNumber(input_a, a)) {
            cout << "������� �������� ��� a! ������ �������� ���� �����.\n";
            continue;
        }

        cout << "������ c (�������): ";
        getline(cin, input_c);
        if (!isValidNumber(input_c, c)) {
            cout << "������� �������� ��� c! ������ �������� ���� �����.\n";
            continue;
        }

        cout << "������ m (������, m > 0): ";
        getline(cin, input_m);
        if (!isValidNumber(input_m, m)) {
            cout << "������� �������� ��� m! ������ �������� ���� �����.\n";
            continue;
        }

        cout << "������ x0 (��������� ��������): ";
        getline(cin, input_x0);
        if (!isValidNumber(input_x0, x0)) {
            cout << "������� �������� ��� x0! ������ �������� ���� �����.\n";
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
    cout << "������ ������� ������� ��� ���������: ";
    cin >> count;
    return count;
}

string ConsoleUI::get_text_to_encrypt() {
    string message;
    cout << "������ ����� ��� ����������: ";
    cin.ignore();
    getline(cin, message);
    return message;
}

void ConsoleUI::show_encrypted_decrypted_text(const vector<char>& encrypted, const vector<char>& decrypted) {
    cout << "������������ �����: ";
    for (char ch : encrypted) cout << ch;
    cout << "\n";

    cout << "������������� �����: ";
    for (char ch : decrypted) cout << ch;
    cout << "\n";
}

void ConsoleUI::show_message(const string& message) {
    cout << message << "\n";
}