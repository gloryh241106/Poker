#include "Read_UserData.h"

void User_Action::Load_Data() {
    fstream myFile;
    myFile.open("StorageUserData.txt", ios::in);
    string UserName, PassWord;
    while (myFile >> UserName >> PassWord)
        User_Data_Storage[UserName] = PassWord;
    myFile.close();
}
// Doc du lieu tu File UserData de tai thong tin nguoi dung len

void User_Action::Save_Data(string UserName, string PassWord) {
    fstream myFile;
    myFile.open("StorageUserData.txt", ios::app);
    if (myFile.is_open()) {
        myFile << UserName << endl;
        myFile << PassWord << endl;
        myFile.close();
    } else
        cout << "Trouble in saving data!" << endl;
}
// Luu thong tin nguoi dung vao file UserData
// TODO: Merge SignUp and LogIn into one. If the user name is found then we ask
// TODO: the user for password. If not then we ask them to create a new password
void User_Action::SignUp() {
    string UserName;
    string PassWord;
    bool flag = true;
    do {
        Load_Data();
        cout << "Enter your username:" << " ";
        getline(cin, UserName);
        cout << "Enter your password:" << " ";
        getline(cin, PassWord);
        if (User_Data_Storage.find(UserName) != User_Data_Storage.end()) {
            cout << "Username is already available, please try again!"
                 << endl;  // Username da tung duoc luu => trung ten
            flag = false;
        } else {
            cout << "Sign up successfully"
                 << endl;  // Username chua tung duoc luu => khong trung ten
            Save_Data(UserName, PassWord);
            flag = true;
        }
    } while (flag == false);
}

void User_Action::LogIn() {
    Load_Data();
    string UserName, PassWord;
    cout << "Enter your UserName" << " ";
    getline(cin, UserName);
    cout << "Enter your PassWord" << " ";
    getline(cin, PassWord);
    if (User_Data_Storage[UserName] == PassWord &&
        User_Data_Storage.find(UserName) != User_Data_Storage.end())
        cout << "Log in successfully"
             << endl;  // Thong tin nhap trung khop voi thong tin da duoc luu
    else
        cout << "Username or Password is not correct!" << endl;
}

void User_Action::Choice() {
    string action;
    bool CheckInput = false;
    while (!CheckInput) {
        cout << endl
             << "What you want to do? Please type 1 of 3 (Sign up/ Log in/ Out)"
             << endl;
        getline(cin, action);
        if (action == "Sign up") {
            SignUp();
            CheckInput = true;
        } else if (action == "Log in") {
            LogIn();
            CheckInput = true;
        } else if (action == "Out") {
            cout << "Thanks for using our game!" << endl;
            break;
        }
    }
}