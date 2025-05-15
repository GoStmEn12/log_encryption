#include <iostream>
#include "console_ui.h"
#include "utils.h"

void ConsoleUI::show_menu() {
    cout << "\tМеню\n";
    cout << "1- Налаштувати параметри генератора\n";
    cout << "2- Згенерувати та зберегти послідовність чисел\n";
    cout << "3- Зашифрувати текстове повідомлення\n";
    cout << "4- Зашифрувати файл\n";
    cout << "5- Розшифрувати файл\n";
    cout << "6- Вихід\n";
    cout << "Зробіть вибір: ";
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
        cout << "Введіть a (множник): ";
        cin.ignore();
        getline(cin, input_a);
        if (!isValidNumber(input_a, a)) {
            cout << "Недійсне введення для a! Введіть коректне ціле число.\n";
            continue;
        }

        cout << "Введіть c (доданок): ";
        getline(cin, input_c);
        if (!isValidNumber(input_c, c)) {
            cout << "Недійсне введення для c! Введіть коректне ціле число.\n";
            continue;
        }

        cout << "Введіть m (модуль, m > 0): ";
        getline(cin, input_m);
        if (!isValidNumber(input_m, m)) {
            cout << "Недійсне введення для m! Введіть коректне ціле число.\n";
            continue;
        }

        cout << "Введіть x0 (початкове значення): ";
        getline(cin, input_x0);
        if (!isValidNumber(input_x0, x0)) {
            cout << "Недійсне введення для x0! Введіть коректне ціле число.\n";
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
    cout << "Введіть кількість значень для генерації: ";
    cin >> count;
    return count;
}

string ConsoleUI::get_text_to_encrypt() {
    string message;
    cout << "Введіть текст для шифрування: ";
    cin.ignore();
    getline(cin, message);
    return message;
}

void ConsoleUI::show_encrypted_decrypted_text(const vector<char>& encrypted, const vector<char>& decrypted) {
    cout << "Зашифрований текст: ";
    for (char ch : encrypted) cout << ch;
    cout << "\n";

    cout << "Розшифрований текст: ";
    for (char ch : decrypted) cout << ch;
    cout << "\n";
}

void ConsoleUI::show_message(const string& message) {
    cout << message << "\n";
}