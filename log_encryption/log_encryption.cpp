#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
#include <string>
#include <Windows.h>
#include "lcg.h"
#include "file_manager.h"
#include "utils.h"
using namespace std;

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    LCG lcg;
    FileManager fileManager;
    unsigned long long a, c, m, x0;
    char choice = ' ';
    do {
        cout << "\tМеню\n";
        cout << "1- Налаштувати параметри генератора\n";
        cout << "2- Згенерувати та зберегти послідовність чисел\n";
        cout << "3- Зашифрувати текстове повідомлення\n";
        cout << "4- Зашифрувати файл\n";
        cout << "5- Розшифрувати файл\n";
        cout << "6- Вихід\n";
        cout << "Зробіть вибір: ";
        cin >> choice;
        switch (choice)
        {
        case '1': {
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

                valid = lcg.set_parameters(a, c, m, x0);
                if (!valid) {
                    cout << "Недійсні параметри! Переконайтеся, що m > 0 і a, c, x0 є в діапазоні [0, m-1].\n";
                }
            } while (!valid);

            cout << "Параметри успішно встановлено.\n";
            break;
        }
        case '2': {
            string filename;
            int count;
            cout << "Введіть ім'я файлу для збереження послідовності: ";
            cin.ignore();
            getline(cin, filename);
            if (!isValidFilename(filename)) {
                cout << "Недійсне ім'я файлу! Використовуйте лише латинські літери, цифри, _, -, та крапку для розширення.\n";
                continue;
            }
            cout << "Введіть кількість значень для генерації: ";
            cin >> count;

            if (fileManager.save_sequence(filename, lcg, count)) {
                cout << "Послідовність збережено у " << filename << "\n";
            }
            else {
                cout << "Не вдалося зберегти послідовність.\n";
            }
            break;
        }
        case '3': {
            if (!lcg.is_ready()) {
                cout << "Генератор не ініціалізований. Спочатку налаштуйте параметри.\n";
                break;
            }
            string message;
            cin.ignore();
            cout << "Введіть текст для шифрування: ";
            getline(cin, message);

            vector<char> data(message.begin(), message.end());
            vector<char> encrypted = lcg.encrypt_decrypt(data, message.length());
            cout << "Зашифрований текст: ";
            for (char ch : encrypted) cout << ch;
            cout << "\n";

            vector<char> decrypted = lcg.encrypt_decrypt(encrypted, message.length());
            cout << "Розшифрований текст: ";
            for (char ch : decrypted) cout << ch;
            cout << "\n";
            break;
        }
        case '4': {
            if (!lcg.is_ready()) {
                cout << "Генератор не ініціалізований. Спочатку налаштуйте параметри.\n";
                break;
            }
            string filename;
            cout << "Введіть ім'я файлу для шифрування: ";
            cin.ignore();
            getline(cin, filename);
            if (!isValidFilename(filename)) {
                cout << "Недійсне ім'я файлу! Використовуйте лише латинські літери, цифри, _, -, та крапку для розширення.\n";
                continue;
            }

            vector<char> data = fileManager.read_file(filename);
            if (data.empty()) {
                continue;
            }

            vector<char> result = lcg.encrypt_decrypt(data, data.size());

            if (fileManager.write_file("encrypted_" + filename, result)) {
                cout << "Файл зашифровано та збережено як encrypted_" + filename << "\n";
            }
            else {
                cout << "Не вдалося зберегти зашифрований файл.\n";
            }
            break;
        }
        case '5': {
            string filename;
            cout << "Введіть ім'я файлу для розшифрування: ";
            cin.ignore();
            getline(cin, filename);
            if (!isValidFilename(filename)) {
                cout << "Недійсне ім'я файлу! Використовуйте лише латинські літери, цифри, _, -, та крапку для розширення.\n";
                continue;
            }

            vector<char> data = fileManager.read_file(filename);
            if (data.empty()) {
                continue;
            }

            cout << "Введіть параметри для розшифрування:\n";
            cout << "Введіть a (множник): ";
            cin >> a;
            cout << "Введіть c (доданок): ";
            cin >> c;
            cout << "Введіть m (модуль, m > 0): ";
            cin >> m;
            cout << "Введіть x0 (початкове значення): ";
            cin >> x0;

            if (!lcg.set_parameters(a, c, m, x0)) {
                cout << "Недійсні параметри! Переконайтеся, що m > 0 і a, c, x0 є в діапазоні [0, m-1].\n";
                break;
            }

            vector<char> result = lcg.encrypt_decrypt(data, data.size());

            if (fileManager.write_file("decrypted_" + filename, result)) {
                cout << "Файл розшифровано та збережено як decrypted_" + filename << "\n";
            }
            else {
                cout << "Не вдалося зберегти розшифрований файл.\n";
            }
            break;
        }
        case '6':
            break;
        default:
            cout << "\nПомилка у виборі! Оберіть опцію з меню!\n";
            break;
        }
    } while (choice != '6');

    return 0;
}

bool isValidNumber(const string& input, unsigned long long& value) {
    if (!regex_match(input, regex("^\\d+$")) || input.empty()) {
        return false;
    }
    try {
        size_t pos;
        value = stoull(input, &pos);
        return pos == input.length();
    }
    catch (const exception& e) {
        return false;
    }
}

bool isValidFilename(const string& filename) {
    regex filename_regex("^[a-zA-Z0-9_\\-\\.]+\\.[a-zA-Z0-9]+$");
    return regex_match(filename, filename_regex);
}