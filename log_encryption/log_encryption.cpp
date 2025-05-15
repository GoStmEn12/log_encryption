#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
#include <string>
#include <Windows.h>
#include "lcg.h"
#include "file_manager.h"
#include "utils.h"
#include "console_ui.h"
using namespace std;

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    LCG lcg;
    FileManager fileManager;
    ConsoleUI ui;
    unsigned long long a, c, m, x0;
    char choice = ' ';
    do {
        ui.show_menu();
        choice = ui.get_choice();
        switch (choice)
        {
        case '1': {
            ui.get_parameters(a, c, m, x0);
            if (lcg.set_parameters(a, c, m, x0)) {
                ui.show_message("Параметри успішно встановлено.");
            }
            else {
                ui.show_message("Недійсні параметри! Переконайтеся, що m > 0 і a, c, x0 є в діапазоні [0, m-1].");
            }
            break;
        }
        case '2': {
            string filename = ui.get_filename("Введіть ім'я файлу для збереження послідовності: ");
            if (!isValidFilename(filename)) {
                ui.show_message("Недійсне ім'я файлу! Використовуйте лише латинські літери, цифри, _, -, та крапку для розширення.");
                break;
            }
            int count = ui.get_sequence_count();

            if (fileManager.save_sequence(filename, lcg, count)) {
                ui.show_message("Послідовність збережено у " + filename);
            }
            break;
        }
        case '3': {
            if (!lcg.is_ready()) {
                ui.show_message("Генератор не ініціалізований. Спочатку налаштуйте параметри.");
                break;
            }
            string message = ui.get_text_to_encrypt();

            vector<char> data(message.begin(), message.end());
            vector<char> encrypted = lcg.encrypt_decrypt(data, message.length());
            vector<char> decrypted = lcg.encrypt_decrypt(encrypted, message.length());
            ui.show_encrypted_decrypted_text(encrypted, decrypted);
            break;
        }
        case '4': {
            if (!lcg.is_ready()) {
                ui.show_message("Генератор не ініціалізований. Спочатку налаштуйте параметри.");
                break;
            }
            string filename = ui.get_filename("Введіть ім'я файлу для шифрування: ");
            if (!isValidFilename(filename)) {
                ui.show_message("Недійсне ім'я файлу! Використовуйте лише латинські літери, цифри, _, -, та крапку для розширення.");
                break;
            }

            vector<char> data = fileManager.read_file(filename);
            if (data.empty()) {
                break;
            }

            vector<char> result = lcg.encrypt_decrypt(data, data.size());

            string encrypted_filename = "encrypted_" + filename;
            if (fileManager.write_file(encrypted_filename, result)) {
                ui.show_message("Файл зашифровано та збережено як " + encrypted_filename);
            }
            break;
        }
        case '5': {
            string filename = ui.get_filename("Введіть ім'я файлу для розшифрування: ");
            if (!isValidFilename(filename)) {
                ui.show_message("Недійсне ім'я файлу! Використовуйте лише латинські літери, цифри, _, -, та крапку для розширення.");
                break;
            }

            vector<char> data = fileManager.read_file(filename);
            if (data.empty()) {
                break;
            }

            ui.show_message("Введіть параметри для розшифрування:");
            ui.get_parameters(a, c, m, x0);

            if (!lcg.set_parameters(a, c, m, x0)) {
                ui.show_message("Недійсні параметри! Переконайтеся, що m > 0 і a, c, x0 є в діапазоні [0, m-1].");
                break;
            }

            vector<char> result = lcg.encrypt_decrypt(data, data.size());

            string decrypted_filename = "decrypted_" + filename;
            if (fileManager.write_file(decrypted_filename, result)) {
                ui.show_message("Файл розшифровано та збережено як " + decrypted_filename);
            }
            break;
        }
        case '6':
            break;
        default:
            ui.show_message("\nПомилка у виборі! Оберіть опцію з меню!");
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
    catch (const std::exception& e) {
        return false;
    }
}

bool isValidFilename(const string& filename) {
    regex filename_regex("^[a-zA-Z0-9_\\-\\.]+\\.[a-zA-Z0-9]+$");
    return regex_match(filename, filename_regex);
}