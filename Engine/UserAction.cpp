#include "Read_UserData.h"

// Tai ten dang nhap va mat khau da duoc luu cua nguoi dung vao chuong trinh
void User_Action::Load_Data() {
	fstream myFile;
	myFile.open("UserData.txt", ios::in);
	string UserName, PassWord;
	if (myFile.is_open()) {
		while (myFile >> UserName >> PassWord)
			User_Data_Storage[UserName] = PassWord;
		myFile.close();
	}
}

// Tai so tien cua nguoi dung 
void User_Action::Load_Money() {
	fstream myFile;
	myFile.open("UserMoney.txt", ios::in);
	string UserName
	long long Money;
	if (myFile.is_open()) {
		while (myFile >> UserName >> Money)
			User_Money_Data[UserName] = Money;
		myFile.close();
	}
}

//Luu thong tin nguoi dung dang ki
void User_Action::Save_Data(string UserName, string PassWord) {
	fstream myFile;
	myFile.open("UserData.txt", ios::app);
	if (myFile.is_open()) {
		myFile << UserName << endl;
		myFile << PassWord << endl;
		myFile.close();
	}
	else cout << "Trouble in saving data!" << endl;
}

//Luu money nguoi dung luc dang ki
void User_Action::User_Money(string UserName, long long Money) {
	fstream myFile;
	myFile.open("UserMoney.txt", ios::app);
	if (myFile.is_open()) {
		myFile << UserName << endl;
		myFile << Money << endl;
		myFile.close();
	}
	else cout << "Trouble in saving data!" << endl;
}

void User_Action::SignUp() {
	string UserName;
	string PassWord;
	bool flag = true;
	do {
		cout << "Enter your username:" << " ";
		getline(cin, UserName);
		cout << "Enter your password:" << " ";
		getline(cin, PassWord);
		if (User_Data_Storage.find(UserName) != User_Data_Storage.end()) {
			cout << "Username is already available, please try again!" << endl;  //Username da tung duoc luu => trung ten
			flag = false;
		}
		else {
			cout << "Sign up successfully" << endl; //Username chua tung duoc luu => khong trung ten
			Save_Data(UserName, PassWord);
			User_Money(UserName, 50000);
			flag = true;
		}
	} while (flag == false);

}

void User_Action::LogIn() {
	string UserName, PassWord;
	cout << "Enter your UserName" << " ";
	getline(cin, UserName);
	cout << "Enter your PassWord" << " ";
	getline(cin, PassWord);
	if (User_Data_Storage[UserName] == PassWord && User_Data_Storage.find(UserName) != User_Data_Storage.end())
		cout << "Log in successfully" << endl; //Thong tin nhap trung khop voi thong tin da duoc luu
	else cout << "Username or Password is not correct!" << endl;
}

void User_Action::Choice() {
	Load_Data();
	Load_Money();
	string action;
	bool CheckInput = false;
	while (!CheckInput) {
		cout << endl << "What you want to do? Please type 1 of 3 (Sign up/ Log in/ Out)" << endl;
		getline(cin, action);
		if (action == "Sign up") {
			SignUp();
			CheckInput = true;
		}
		else if (action == "Log in") {
			LogIn();
			CheckInput = true;
		}
		else if (action == "Out") {
			cout << "Thanks for using our game!" << endl;
			break;
		}
	}
}

//Cap nhat so tien nguoi dung va luu lai trong file UserMoney.txt
void User_Action::Update_Money(string UserName, long long MoneyChange) {
	if (User_Money_Data.find(UserName) != User_Money_Data.end()) {
		User_Money_Data[UserName] += MoneyChange;
		fstream myFile;
		myFile.open("UserMoney.txt", ios::out);
		if (myFile.is_open()) {
			for (const auto& user : User_Money_Data) {
				myFile << user.first << endl;
				myFile << user.second << endl;
			}
			myFile.close();
		}
		else cout << "Trouble in updating money data!" << endl;
	}
	else cout << "User not found, cannot update money!" << endl;
}

//Hien thi so tien nguoi dung
void User_Action::Display_Money(string UserName) {
	if (User_Money_Data.find(UserName) != User_Money_Data.end()) 
		cout << "Current balance for " << UserName << ": " << User_Money_Data[UserName] << " units." << endl;
	else cout << "User not found!" << endl;
}
