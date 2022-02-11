#include <string>
#include <vector>
#include <iostream>
#include "../lib/DataStorage.cpp"
DataStorage dataStorage("Runtime,Scope,CustomCompoundStmt i000002,ForStmt 2219672,CustomCompoundStmt i000005");
int main(void) {
dataStorage.startEvent(0);
    dataStorage.startEvent(2);
std::vector <std::string> passwordStorage;
    std::string password;
    char current;

    dataStorage.endEvent(2);
dataStorage.startEvent(3);
for (int passwordCount = 0; passwordCount < 1000000; passwordCount++) {
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
dataStorage.endEvent(3);

    dataStorage.startEvent(4);
std::sort(passwordStorage.begin(), passwordStorage.end());
    passwordStorage.erase(std::unique(passwordStorage.begin(),
                                            passwordStorage.end()),
                          passwordStorage.end());

    for (std::string currentPassword: passwordStorage) {
        std::cout << currentPassword << '\n';
    }
dataStorage.endEvent(4);

    dataStorage.endEvent(0);
dataStorage.print();return 0;
}