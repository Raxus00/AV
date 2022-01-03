#ifndef AV_HPP
#define AV_HPP
#include<string>
#include<iostream>
#include<vector>
#include<fstream>
#include<dirent.h>
#include<sstream>
#include<cstring>
#include<bitset>
#include <bits/stdc++.h>

//Rasmus Andersen   rasmus.andersen00@gmail.com
//Erik Nordahl  eriknordahl23@gmail.com

class AV
{
public:
    std::vector<std::string> read();
    void treverase(std::string path, std::vector<std::string> datavector, std::vector<std::string> signatures, std::vector<std::string> virusname);
    void compare(std::string path, std::vector<std::string> signatures, std::vector<std::string> virusname);
    std::string read_binary(std::string path);
    void createMap(std::unordered_map<std::string, char> *um);
    std::string to_hex(std::string binary);
    std::vector<std::string> read_signatures(std::vector<std::string> datavector);
    std::vector<std::string> read_virusname(std::vector<std::string> datavector);
    void write(std::string path, std::string name);
private:
protected:
};


#endif
