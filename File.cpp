
#include <filesystem>
#include <string>
#include <fstream>
#include <iostream>
#include <valarray>
#include <cstring>


#include "File.h"

    const std::string& File::getFile() const {
        return file;
    }
     void File::timestamp() {
        auto time = std::time(nullptr);
        std::tm* localtime = std::localtime(&time);
        int hours = localtime ->tm_hour;
        int minutes = localtime ->tm_min;
        int seconds = localtime -> tm_sec;
        std::string line1 = "hh" + std::to_string(hours);
        std::string line2 = "mm" + std::to_string(minutes);
        std::string line3 = "ss" + std::to_string(seconds);
        std::string timestamp = "timestamp.txt";
        std::ofstream timestampFile(timestamp, std::ios::out);

        if(!timestampFile.is_open()){
            std::cout<<"Something went wrong..."<<std::endl;
            return;
        }


        for (int i = 0; i <= 9; ++i) {
            timestampFile<<"\n";
        }
        timestampFile << line1;
        for (int i = 0; i <= 10; ++i) {
            timestampFile<<"\n";
        }
        timestampFile << line2 << std::endl;
        for (int i = 0; i <= 9; ++i) {
            timestampFile<<"\n";
        }
        timestampFile << line3 << std::endl;


        timestampFile.close();
    }
    void File::login(){
        std::cout<<"Enter the filename or path to file: \n";
        std::cin >> file;
        std::ifstream fin;
        fin.open(file, std::fstream::in);
        if(!fin.is_open()){
            timestamp();
            std::cout<<"Wrong filename or path.";
            std::exit(0);
        }else{
            char tab[50];
            timestamp();
            std::cout<<"Enter the password: \n";
            std::cin>>tab;
            int sum = 0;
            int size = std::strlen(tab);
            for (int i = 0; i < size; ++i) {
                sum+=static_cast<int>(tab[i]);
            }
            if(sum==std::sqrt(576081)){
                std::cout<<"\nLogged in Succesfully!\n";
            } else{
                std::cout<<"WRONG PASSWORD!"<<std::endl;
                std::exit(0);
            }
        }
        fin.close();
    }

