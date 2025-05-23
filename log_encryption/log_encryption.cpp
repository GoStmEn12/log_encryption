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
            system("cls");
            cout << "======Set Generator Parameters======" << endl;
            ui.get_parameters(a, c, m, x0);
            if (lcg.set_parameters(a, c, m, x0)) {
                ui.show_message("Parameters set successfully.");
            }
            else {
                ui.show_message("Invalid parameters! Ensure that m > 0 and a, c, x0 are in range [0, m-1].");
            }
            break;
        }
        case '2': {
            system("cls");
            cout << "======Generate and Save Sequence======";
            string filename = ui.get_filename("\nEnter filename to save sequence: ");
            if (!isValidFilename(filename)) {
                ui.show_message("Invalid filename! Use only Latin letters, digits, _, -, and a dot for extension.");
                break;
            }
            int count = ui.get_sequence_count();

            if (fileManager.save_sequence(filename, lcg, count)) {
                ui.show_message("Sequence saved to " + filename);
            }
            break;
        }
        case '3': {
            system("cls");
            cout << "======Encrypt Text======" << endl;
            if (!lcg.is_ready()) {
                ui.show_message("Generator not initialized. Set parameters first.");
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
            system("cls");
            cout << "===============Encrypt File===============" << endl;
            if (!lcg.is_ready()) {
                ui.show_message("Generator not initialized. Set parameters first.");
                break;
            }
            string filename = ui.get_filename("Enter filename to encrypt: ");
            if (!isValidFilename(filename)) {
                ui.show_message("Invalid filename! Use only Latin letters, digits, _, -, and a dot for extension.");
                break;
            }

            vector<char> data = fileManager.read_file(filename);
            if (data.empty()) {
                break;
            }

            vector<char> result = lcg.encrypt_decrypt(data, data.size());

            string encrypted_filename = "encrypted_" + filename;
            if (fileManager.write_file(encrypted_filename, result)) {
                ui.show_message("File encrypted and saved as " + encrypted_filename);
            }
            break;
        }
        case '5': {
            system("cls");
            cout << "==============Decrypt File===============" << endl;
            string filename = ui.get_filename("Enter filename to decrypt: ");
            if (!isValidFilename(filename)) {
                ui.show_message("Invalid filename! Use only Latin letters, digits, _, -, and a dot for extension.");
                break;
            }

            vector<char> data = fileManager.read_file(filename);
            if (data.empty()) {
                break;
            }

            ui.show_message("Enter parameters for decryption:");
            ui.get_parameters(a, c, m, x0);

            if (!lcg.set_parameters(a, c, m, x0)) {
                ui.show_message("Invalid parameters! Ensure that m > 0 and a, c, x0 are in range [0, m-1].");
                break;
            }

            vector<char> result = lcg.encrypt_decrypt(data, data.size());

            string decrypted_filename = "decrypted_" + filename;
            if (fileManager.write_file(decrypted_filename, result)) {
                ui.show_message("File decrypted and saved as " + decrypted_filename);
                // Виводимо розшифрований текст у консоль для перевірки
                ui.show_encrypted_decrypted_text(data, result);
            }
            break;
        }

        case '6':
            cout << "==========================================";
            cout << "\nExit!!!"<<endl;
            break;
        default:
            ui.show_message("\nInvalid choice! Select an option from the menu!");
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