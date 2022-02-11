#include <string>
#include <vector>
#include <iostream>
#include "../lib/DataStorage.cpp"
DataStorage dataStorage("Runtime,Scope,ForStmt 2219597,CXXMemberCallExpr 2219614,CXXMemberCallExpr 2219644,CXXMemberCallExpr 2219662");
int main(void) {
dataStorage.startEvent(0);
    std::vector <std::string> passwordStorage;
    std::string password;
    char current;

    dataStorage.startEvent(1);
for (int passwordCount = 0; passwordCount < 1000000; passwordCount++) {
        dataStorage.startEvent(2);
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
dataStorage.endEvent(2);
        dataStorage.startEvent(3);
password.pop_back();
dataStorage.endEvent(3);
        dataStorage.startEvent(4);
passwordStorage.push_back(password);
dataStorage.endEvent(4);
        dataStorage.startEvent(5);
password.clear();
dataStorage.endEvent(5);
    }
dataStorage.endEvent(1);

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