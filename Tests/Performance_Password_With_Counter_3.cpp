#include <string>
#include <vector>
#include <iostream>
#include "../lib/DataStorage.cpp"
DataStorage dataStorage("Runtime,Scope,ForStmt 2219423,CustomCompoundStmt i000004");
int main(void) {
dataStorage.startEvent(0);
    std::vector <std::string> passwordStorage;
    std::string password;
    char current;

    for (int passwordCount = 0; passwordCount < 1000000; passwordCount++) {
        dataStorage.startEvent(1);
for (int sectionCount = 0; sectionCount < 3; sectionCount++) {
            dataStorage.startEvent(2);
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
dataStorage.endEvent(2);
            dataStorage.startEvent(3);
password += '-';
dataStorage.endEvent(3);
        }
dataStorage.endEvent(1);
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
    }

    dataStorage.endEvent(0);
dataStorage.print();return 0;
}