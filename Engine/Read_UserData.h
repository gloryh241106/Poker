//#pragma once

#ifndef READ_USERDATA_H
#define READ_USERDATA_H

#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <vector>
#include <sstream>
#include <iomanip>

extern std::unordered_map<std::string, std::string> User_Data_Storage;
extern std::unordered_map<std::string, long long> User_Money_Data;
extern std::unordered_map<std::string, int> User_Game_Played;
extern std::unordered_map<std::string, int> User_Game_Won;
extern std::vector<std::pair<double, std::string>> Board;

class User_Action {
public:
    void Choice();
    void SignUp();
    void Load_Data();
    void Save_Data(std::string, std::string);
    void LogIn();
    void Load_Money();
    void User_Money(std::string, long long);
    void Update_Money(std::string, long long);
    void Display_Money(std::string);
    int Num_Game_Played(std::string);
    int Num_Game_Won(std::string);
    double Win_Rate(std::string);
    void Display_Leader_Board(std::string);
    void Load_Data_NumGame();
};

#endif