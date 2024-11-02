#ifndef READ_USERDATA_H
#define READ_USERDATA_H

#include <fstream>
#include <string>
#include <iostream>
#include <unordered_map>
using namespace std;

class User_Action {
private:
	unordered_map< string, string> User_Data_Storage;
public:
	void Choice();
	void SignUp();
	void Load_Data();
	void Save_Data(string, string);
	void LogIn();
};

#endif