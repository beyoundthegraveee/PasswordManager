//
// Created by jacke on 27.05.2023.
//

#ifndef S24911_OPTIONS_H
#define S24911_OPTIONS_H


#include "File.h"
#include "Encryption.h"

class Options {
private:
    std::vector<std::string>passwords;
    Encryption encryption;
public:

    std::string passwordGenerator();

    void view_file(File file);

    int CheckPasswords(std::string pass, File file);

    void insertData(File file);

    void password_by_category(File file);

    void password_by_link(File file);

    void file_exit();

    void change_category(File file);

    void change_password(File file);

    void delete_password(File file);

    void delete_category(File file);

    void view_logs();



};


#endif //S24911_OPTIONS_H
