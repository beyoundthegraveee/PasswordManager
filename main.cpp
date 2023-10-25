#include <iostream>
#include <vector>
#include "Options.h"
#include "File.h"





auto main() -> int {
    File file;
    Options options;
    using std::cout;
    file.login();
    int choice;
    while (true) {
        cout << "Choose your option :\n";
        cout << "[1] View file.\n";
        cout << "[2] Insert data.\n";
        cout << "[3] Password by category.\n";
        cout << "[4] Password by link.\n";
        cout << "[5] Change password.\n";
        cout << "[6] Change category.\n";
        cout << "[7] Delete password.\n";
        cout << "[8] Delete category.\n";
        cout << "[9] Exit.\n";
        cout << "[10] View logs.\n";
        cout << "\n >  ";
        std::cin >> choice;
        if (std::cin.fail()) {
            std::cout << "Invalid option." << std::endl;
            std::cin.clear();
            break;
        }
        cout << "\n";
        try{
        switch (choice) {
            case 1:
                options.view_file(file);
                break;
            case 2:
                options.insertData(file);
                break;
            case 3:
                options.password_by_category(file);
                break;
            case 4:
                options.password_by_link(file);
                break;
            case 5:
                options.change_password(file);
                break;
            case 6:
                options.change_category(file);
                break;
            case 7:
                options.delete_password(file);
                break;
            case 8:
                options.delete_category(file);
                break;
            case 9:
                options.file_exit();
                break;
            case 10:
                options.view_logs();
                break;
            default :
                cout << "OPPS! Invalid option;\n";
                break;
        }
    }
        catch (const std::exception &e) {
            std::cerr << e.what() << '\n';
            cout << "[ERROR] : error while executing the program!" << std::endl;
        }
    }
}