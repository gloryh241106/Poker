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
//#include <openssl/sha.h>
using namespace std;

class User_Action {
private:
    unordered_map<string, string> User_Data_Storage;
    unordered_map<string, long long> User_Money_Data;
    unordered_map<string, int> User_Game_Played;
    unordered_map<string, int> User_Game_Won;
    vector<pair<double, string>> Board;

   public:
    void Choice();
    void SignUp();
    void Load_Data();
    void Save_Data(string, string);
    void LogIn();
    void Load_Money();
    void User_Money(string, long long);
    void Update_Money(string, long long);
    void Display_Money(string);
    int Num_Game_Played(string);
    int Num_Game_Won(string);
    double Win_Rate(string);
    void Display_Leader_Board(string);
    void Load_Data_NumGame();
   
};

#endif