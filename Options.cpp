#include <iostream>
#include <fstream>
#include <vector>
#include <filesystem>
#include "File.h"
#include "Options.h"

    void Options::view_file(File file) {
        std::fstream fin;
        std::string str;
        fin.open(file.getFile(), std::fstream::in);
        if (!fin.is_open()) {
            std::cout << "Something went wrong...\n";
        } else {
            std::cout <<"\n______START______\n";
            while (getline(fin, str)) {
                if(!str.empty()) {
                    std::cout<< encryption.decrypt(str) << std::endl;
                }
                std::cout<<"\n";

            }
            std::cout<<"______END______\n";
        }
        fin.close();

    }

    std::string Options::passwordGenerator() {
    bool wrk = false;
    std::string pass;
        while (!wrk) {
            std::cout << "Enter character count: [12 - 30]" << std::endl;
            int count = 0;
            std::cin >> count;
            if (std::cin.fail()) {
                std::cout << "Please enter a valid integer." << std::endl;
                std::cin.clear();
                exit(1);
            } else if (count <= 11) {
                std::cout << "The minimum number of characters is 12." << std::endl;
                exit(1);
            } else if (count > 31) {
                std::cout << "The maximum number of characters is 30." << std::endl;
                exit(1);
            } else {
                std::cout << "[1] Password with special symbols.\n"
                             "[2] Password with uppercase and lowercase letters." << std::endl;
                srand(time(NULL));
                std::string choice;
                std::cin >> choice;
                if (choice == "1") {
                    char str[]{"0123456789abcdefghijklmnopqrstuvwxyz!@#$%^&*()-_=+[{]};:',<.>/?`~|"};
                    int strN = 64;
                    for (int i = 0; i < count; i++) {
                        pass += str[rand() % strN];
                    }
                    wrk = true;
                } else if (choice == "2") {
                    char str[]{"0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"};
                    int strN = 62;
                    for (int i = 0; i < count; i++) {
                        pass += str[rand() % strN];
                    }
                    wrk = true;
                } else {
                    std::cout << "Wrong option." << std::endl;
                    exit(1);
                }


            }
        }
        return pass;


}


    int Options::CheckPasswords(std::string pass, File file){
        std::fstream fin;
        std::string str;
        std::string whitespace = " ";
        std::vector<std::string>lines;
        fin.open(file.getFile(), std::fstream::in);
        if (!fin.is_open()) {
            std::cout << "Something went wrong...\n";
            exit(0);
        } else {
            while (getline(fin, str)) {
                std::string decrypted = encryption.decrypt(str);
                if (decrypted.find("Password: ") == 0) {
                    std::string password = decrypted.substr(decrypted.find(whitespace) + 1);
                    passwords.push_back(password);
                }
            }
            fin.close();
        }
        for (std::string line : passwords){
            if (line == pass){
                return 1;
            }
        }
        return 0;

}


    void Options::insertData(File file) {
        std::string link;
        std::string category;
        std::string name;
        std::string password;
        std::ofstream fout;
        bool elif = false;
        while (!elif) {
            std::cout << "Write the name of service." << std::endl;
            std::cin >> name;
            std::cout << "Write category." << std::endl;
            std::cin >> category;
            std::vector<std::string> lines;
            lines.push_back("Service: " + name);
            lines.push_back("Category: " + category);
            std::cout << "Write the link of service." << std::endl;
            std::cin >> link;
            lines.push_back("Link: " + link);
            try {
                std::cout << "[1] To generate new password.\n[2] To make your own" << std::endl;
                std::string a;
                std::cin >> a;
                if (a == "1") {
                    password = passwordGenerator();
                    if (CheckPasswords(password, file) == 0) {
                        passwords.push_back(password);
                    } else {
                        std::cout << "Password already exists." << std::endl;
                        return;
                    }
                    lines.push_back("Password: " + password);
                    fout.open(file.getFile(), std::ofstream::app);
                    for (std::string line: lines) {
                        fout << encryption.encrypt(line) << "\n";
                        std::cout << line << std::endl;
                    }
                    fout << "\n";
                    elif = true;
                } else if (a == "2") {
                    std::cout << "Write your password here: [12 - 30]\n";
                    std::string pass;
                    std::cin >> pass;
                    if (pass.size() <= 11) {
                        std::cout << "The minimum number of characters is 12." << std::endl;
                        elif = true;
                    }
                    if (pass.size() > 31) {
                        std::cout << "The maximum number of characters is 30." << std::endl;
                        elif = true;
                    }
                    lines.push_back("Password: " + pass);
                    if (CheckPasswords(pass, file) == 0) {
                        passwords.push_back(pass);
                    } else {
                        std::cout << "Password already exists." << std::endl;
                        return;
                    }
                    fout.open(file.getFile(), std::ofstream::app);
                    for (std::string line: lines) {
                        fout << encryption.encrypt(line) << "\n";
                        std::cout << line << std::endl;
                    }
                    fout << "\n";
                    elif = true;
                } else {
                    std::cout << "Wrong option." << std::endl;
                    elif = true;
                }
                fout.close();
            } catch (const std::exception &e) {
                std::cout << "Exception: " << e.what() << std::endl;
            }
        }
    }

    void Options::password_by_category(File file) {
        std::cout << "Write your category." << std::endl;
        std::string cat;
        std::cin>>cat;
        std::fstream fin;
        std::string str;
        std::vector<std::string> lines;
        fin.open(file.getFile(), std::fstream::in);
        if (!fin.is_open()) {
            std::cout << "Something went wrong...\n";
        } else {
            while (getline(fin, str)) {
                lines.push_back(encryption.decrypt(str));
            }
            bool passFound= false;

            for (std::string line : lines) {
                if(line.find("Category: ") == 0 && line.find(cat)!=std::string::npos)
                    passFound = true;
            }
            if(!passFound){
                std::cout<<"Passwords not found."<<std::endl;
                return;
            }
            std::cout << "All passwords in the category " + cat+":"<< std::endl;
            for (int i = 0; i < lines.size(); ++i) {
                if(lines[i] == ("Category: " + cat)){
                    std::cout<<lines[i+2]<< std::endl;
                }
            }
            std::cout<<"\n";
        }
        fin.close();
    }

    void Options::password_by_link(File file) {
        std::cout << "Write your account link." << std::endl;
        std::string service;
        std::cin>>service;
        std::fstream fin;
        std::string str;
        std::vector<std::string> lines;
        fin.open(file.getFile(), std::fstream::in);
        if (!fin.is_open()) {
            std::cout << "Something went wrong...\n";
        } else {
            while (getline(fin, str)) {
                lines.push_back(encryption.decrypt(str));
            }
            bool passFound= false;

            for (std::string line : lines) {
                if(line.find("Link: ") == 0 && line.find(service)!=std::string::npos)
                    passFound = true;
            }

            if(!passFound){
                std::cout<<"Passwords not found."<<std::endl;
                return;
            }
            std::cout << "All passwords with link " + service+":"<< std::endl;
            for (int i = 0; i < lines.size(); ++i) {
                if(lines[i] == ("Link: " + service)){
                    std::cout<<lines[i+1]<< std::endl;
                }
            }
            std::cout<<"\n";
        }
        fin.close();
    }


    void Options::file_exit() {
    bool wrk = false;
        while (!wrk) {
            std::cout << "Exit?" << std::endl;
            std::cout << "[1]Yes." << std::endl;
            std::cout << "[2]No." << std::endl;
            std::string q;
            std::cin >> q;
            if (q == "1") {
                exit(0);
            } else if (q == "2") {
                return;
            } else {
                std::cout << "You can choose only 2 options." << std::endl;
                wrk = true;
            }
        }

    }


    void Options::change_category(File file) {
    bool wrk = false;
        while (!wrk) {
            std::cout << "[1] To change category.\n[2] return." << std::endl;
            std::string choice;
            std::cin >> choice;
            if (choice == "2")
                return;
            else if (choice == "1") {
                std::string temp = "temp.txt";
                std::cout << "Write a category that you want to change:" << std::endl;
                std::string cat;
                std::cin >> cat;
                std::string str;
                std::fstream fin;
                fin.open(file.getFile(), std::fstream::in);
                if (!fin.is_open()) {
                    std::cout << "Something went wrong...\n";
                    return;
                }
                std::ofstream fout(temp);
                if (!fout.is_open()) {
                    std::cout << "Something went wrong...\n" << std::endl;
                    return;
                }
                std::cout << "Write new category:" << std::endl;
                std::string newcat;
                std::cin >> newcat;
                bool categoryFound = false;
                while (getline(fin, str)) {
                    std::string line = encryption.decrypt(str);
                    if (line.find("Category: ") == 0 && line.find(cat) != std::string::npos) {
                        line.replace(line.find(cat), cat.length(), newcat);
                        categoryFound = true;
                    }
                    fout << encryption.encrypt(line) << '\n';
                }
                fin.close();
                fout.close();

                if (!categoryFound) {
                    std::cout << "Category not found." << std::endl;
                    try {
                        std::filesystem::remove(temp);
                    } catch (const std::exception &e) {
                        std::cout << "Exception: " << e.what() << std::endl;
                    }
                    return;
                }

                try {
                    std::filesystem::remove(file.getFile());
                    std::filesystem::rename(temp, file.getFile());
                } catch (const std::exception &e) {
                    std::cout << "Exception: " << e.what() << std::endl;
                }

                std::cout << "Category changed successfully." << std::endl;
                wrk = true;


            } else {
                std::cout << "Wrong option." << std::endl;
                wrk = true;
            }
        }
    }

    void Options::change_password(File file){
    bool elif = false;
        while (!elif) {
            std::cout << "[1] To change password.\n[2] return." << std::endl;
            std::string choice;
            std::cin >> choice;
            if (choice == "2")
                return;
            else if (choice == "1") {
                std::string temp = "temp.txt";
                std::cout << "Write a password that you want to change:" << std::endl;
                std::string password;
                std::cin >> password;
                std::string str;
                std::fstream fin;
                std::ofstream fout(temp);
                fin.open(file.getFile(), std::fstream::in);
                if (!fin.is_open()) {
                    std::cout << "Something went wrong...\n";
                    return;
                }
                if (!fout.is_open()) {
                    std::cout << "Something went wrong...\n" << std::endl;
                    return;
                }
                bool passFound = false;
                bool elif2 = false;
                while (std::getline(fin, str) && !elif2) {
                    std::string line = encryption.decrypt(str);
                    if (line.find("Password: ") == 0 && line.find(password) != std::string::npos) {
                        std::cout << "[1] To generate new password.\n[2] To make your own." << std::endl;
                        std::string a;
                        std::cin >> a;
                        if (a == "1") {
                            std::string newpass = passwordGenerator();
                            if (CheckPasswords(newpass, file) == 0) {
                                passwords.push_back(newpass);
                            } else {
                                std::cout << "Password already exists." << std::endl;
                                return;
                            }
                            line.replace(line.find(password), password.length(), newpass);
                            passwords.erase(std::remove(passwords.begin(), passwords.end(), password), passwords.end());
                            std::cout << "Password changed successfully." << std::endl;
                            elif2 = true;
                        } else if (a == "2") {
                            std::cout << "Write new password. [12 - 30]" << std::endl;
                            std::string newpass;
                            std::cin >> newpass;
                            if (newpass.size() <= 11) {
                                std::cout << "The minimum number of characters is 12." << std::endl;
                                elif2 = true;
                            }
                            if (newpass.size() > 31) {
                                std::cout << "The maximum number of characters is 30." << std::endl;
                                elif2 = true;
                            }

                            if (CheckPasswords(newpass, file) == 0) {
                                passwords.push_back(newpass);
                            } else {
                                std::cout << "Password already exists." << std::endl;
                                return;
                            }
                            std::cout << "Password changed successfully." << std::endl;
                            line.replace(line.find(password), password.length(), newpass);
                            passwords.erase(std::remove(passwords.begin(), passwords.end(), password), passwords.end());
                        } else {
                            std::cout << "Wrong option." << std::endl;
                            elif2 = true;
                        }
                        passFound = true;
                    }
                    fout << encryption.encrypt(line) << '\n';
                }
                fin.close();
                fout.close();

                if (!passFound) {
                    std::cout << "Password not found." << std::endl;
                    try {
                        std::filesystem::remove(temp);
                    } catch (const std::exception &e) {
                        std::cout << "Exception: " << e.what() << std::endl;
                    }
                    return;
                }

                try {
                    std::filesystem::remove(file.getFile());
                    std::filesystem::rename(temp, file.getFile());
                } catch (const std::exception &e) {
                    std::cout << "Exception: " << e.what() << std::endl;
                }
                elif = true;


            } else {
                std::cout << "Wrong option." << std::endl;
                elif = true;
            }
        }

    }

    void Options::delete_password(File file) {
    bool wrk = false;
        while (!wrk) {
            std::cout << "[1] Delete password.\n[2] return." << std::endl;
            std::string a;
            std::cin >> a;
            if (a == "2") {
                return;
            }
            if (a == "1") {
                std::cout << "[1] Delete all passwords.\n[2] Choose password to delete.\n[3] return." << std::endl;
                std::string b;
                std::cin >> b;
                std::string str;
                std::fstream fin;
                bool passFound = false;
                int count = 0;
                if (b == "1") {
                    std::string pattern = "Password: ";
                    fin.open(file.getFile(), std::fstream::in);
                    if (!fin.is_open()) {
                        std::cout << "Something went wrong...\n";
                        return;
                    } else {
                        while (std::getline(fin, str)) {
                            std::string line = encryption.decrypt(str);
                            if (line.find(pattern) == 0) {
                                count++;
                                passFound = true;
                            }
                        }
                        fin.close();

                        if (!passFound) {
                            std::cout << "Passwords not found." << std::endl;
                            return;
                        }
                        std::ofstream del(file.getFile(), std::ios::trunc);
                        del.close();
                        passwords.clear();
                        std::cout << count << " Passwords deleted successfully." << std::endl;
                        wrk = true;
                    }

                } else if (b == "2") {
                    std::vector<std::string> lines;
                    std::string temp = "temp.txt";
                    std::ofstream fout(temp);
                    std::cout << "Write password to delete." << std::endl;
                    std::string pass;
                    std::cin >> pass;

                    fin.open(file.getFile(), std::fstream::in);
                    if (!fin.is_open()) {
                        std::cout << "Something went wrong...\n";
                        return;
                    }
                    if (!fout.is_open()) {
                        std::cout << "Something went wrong...\n" << std::endl;
                        return;
                    }
                    while (std::getline(fin, str)) {
                        lines.push_back(encryption.decrypt(str));
                    }

                    std::string pattern = "Password: ";
                    for (int i = 0; i < lines.size(); ++i) {
                        if (lines[i].find(pattern) != std::string::npos && lines[i].find(pass) != std::string::npos) {
                            passwords.erase(std::remove(passwords.begin(), passwords.end(), pass), passwords.end());
                            lines.erase(lines.begin() + i - 3, lines.begin() + i + 1);
                            passFound = true;
                            count++;
                        }
                    }
                    fin.close();
                    for (const std::string &line: lines) {
                        fout << encryption.encrypt(line) << '\n';
                    }
                    fout.close();

                    if (!passFound) {
                        std::cout << "Password not found." << std::endl;
                        try {
                            std::filesystem::remove(temp);
                        } catch (const std::exception &e) {
                            std::cout << "Exception: " << e.what() << std::endl;
                        }
                        return;
                    }
                    try {
                        std::filesystem::remove(file.getFile());
                        std::filesystem::rename(temp, file.getFile());
                    } catch (const std::exception &e) {
                        std::cout << "Exception: " << e.what() << std::endl;
                    }
                    std::cout << count << " Passwords deleted successfully." << std::endl;
                    wrk = true;

                } else if (b == "3") {
                    wrk = true;
                } else {
                    std::cout << "Wrong option." << std::endl;
                    wrk = true;
                }

            } else {
                std::cout << "Wrong option." << std::endl;
                wrk = true;
            }
        }
    }

    void Options::delete_category(File file){
    bool wrk = false;
        while (!wrk) {
            std::cout << "[1] Delete category.\n[2] return." << std::endl;
            std::string a;
            std::cin >> a;
            if (a == "2")
                return;
            if (a == "1") {
                std::cout << "Write category to delete." << std::endl;
                std::string cat;
                std::cin >> cat;
                std::vector<std::string> lines;
                std::fstream fin;
                std::string temp = "temp.txt";
                std::string str;
                bool catFound = false;
                int count = 0;
                std::ofstream fout(temp);

                fin.open(file.getFile(), std::fstream::in);
                if (!fin.is_open()) {
                    std::cout << "Something went wrong...\n";
                } else {
                    while (getline(fin, str)) {
                        lines.push_back(encryption.decrypt(str));
                    }
                }
                fin.close();

                std::string pattern = "Category: ";

                for (int i = 0; i < lines.size(); ++i) {
                    if (lines[i].find(pattern) != std::string::npos && lines[i].find(cat) != std::string::npos) {
                        lines.erase(lines.begin() + i - 1, lines.begin() + i + 3);
                        catFound = true;
                        count++;
                    }
                }
                if (!catFound) {
                    std::cout << "Category not found." << std::endl;
                    return;
                }

                for (const std::string &line: lines) {
                    fout << encryption.encrypt(line) << '\n';
                }
                fout.close();

                try {
                    std::filesystem::remove(file.getFile());
                    std::filesystem::rename(temp, file.getFile());
                } catch (const std::exception &e) {
                    std::cout << "Exception: " << e.what() << std::endl;
                }
                std::cout << count << " Categories deleted successfully." << std::endl;
                wrk = true;

            } else {
                std::cout << "Wrong option." << std::endl;
                wrk = true;
            }
        }

    }

    void Options::view_logs(){
        std::fstream fin;
        std::string file="timestamp.txt";
        std::string line;
        fin.open(file, std::ios::in);
        if(!fin.is_open()){
            std::cout<<"Something went wrong..."<<std::endl;
            return;
        } else{
            std::cout<<"Logs:"<<std::endl;
            while (getline(fin,line)){
                std::cout.write(line.c_str(), line.length());
            }
            std::cout<<std::endl;
        }

    }

