#include <string>
#include <vector>
#include <iostream>
#include <random>
#include <fstream>
#include "../lib/DataStorage.cpp"
DataStorage dataStorage("Runtime,Scope,CustomCompoundStmt i000002,IfStmt 2218252,CustomCompoundStmt i000005");

int main(void) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<std::int64_t> dis(1, 20000000000);
    std::int64_t random = dis(gen);

    ofstream callsFile;
    callsFile.open("Password_Size.txt", ios_base::app);
    callsFile << random << "\n";

    dataStorage.startEvent(0);
    std::vector <std::string> passwordStorage;
    std::string password;
    char current;
    for (int passwordCount = 0; passwordCount < random; passwordCount++) {
        for (int sectionCount = 0; sectionCount < 3; sectionCount++) {
            for (int sectionLength = 0; sectionLength < 6; sectionLength++) {
                char lowerCase = rand() % 26 + 'a';
                char upperCase = rand() % 26 + 'A';
                char number = rand() % 10 + '0';

                char randomChoice = (rand() % 100 + 1);
                if (randomChoice <= 40) {
                    current = lowerCase;
                } else if (randomChoice <= 80) {
                    current = upperCase;
                } else {
                    current = number;
                }
                password += current;
            }
            password += '-';
        }
        password.pop_back();
        passwordStorage.push_back(password);
        password.clear();
    }

    std::sort(passwordStorage.begin(), passwordStorage.end());
    passwordStorage.erase(std::unique(passwordStorage.begin(),
                                      passwordStorage.end()),
                          passwordStorage.end());

    for (std::string currentPassword: passwordStorage) {
        std::cout << currentPassword << '\n';
        currentPassword.clear();
    }

    dataStorage.endEvent(0);
    dataStorage.print();
    passwordStorage.clear();
    passwordStorage.shrink_to_fit();
    return 0;
}