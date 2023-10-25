#include <string>
#include <vector>
#include "Encryption.h"

    std::string Encryption::encrypt(std::string input) {
        std::vector<char> word(input.begin(), input.end());
        std::string alphabet = "abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%^&*()-_=+[{]};:',<.>/?`~|";
        for (int i = 0; i < (int)input.length(); i++) {
            for (int j = 0; j < (int)alphabet.length(); j++) {
                if (word[i] == alphabet[j]) {
                    word[i] = alphabet[(j + i%4) % alphabet.length()];
                    break;
                }
            }
        }
        std::string str(word.begin(), word.end());
        return str;
    }

    std::string Encryption::decrypt(std::string input) {
        std::vector<char> word(input.begin(), input.end());
        std::string alphabet = "abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%^&*()-_=+[{]};:',<.>/?`~|";
        for (int i = 0; i < (int)input.length(); i++) {
            for (int j = 0; j < (int)alphabet.length(); j++) {
                if (word[i] == alphabet[j]) {
                    word[i] = alphabet[(j - i%4 + alphabet.length()) % alphabet.length()];
                    break;
                }
            }
        }
        std::string str(word.begin(), word.end());
        return str;
    }
