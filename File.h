//
// Created by jacke on 27.05.2023.
//

#ifndef S24911_FILE_H
#define S24911_FILE_H


class File {
private:
    std::string file;
public:

    void timestamp();

    void login();

    const std::string &getFile() const;
};


#endif //S24911_FILE_H
