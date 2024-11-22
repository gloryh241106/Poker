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
	string UserName;
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
string User_Action::HashPassword(string password) {
	unsigned char hash[SHA256_DIGEST_LENGTH]; // Khoi tao mang Hash voi 256 bits
	SHA256((unsigned char*)password.c_str(), password.size(), hash); // Goi ham bam mat khau co san trong thu vien

	stringstream ss;
	for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
		ss << hex << setw(2) << setfill('0') << (int)hash[i];    // Chuyen qua he Hex
	}
	return ss.str();
}
void User_Action::SignUp() {
	string UserName;
	string PassWord;
	string HashedPassWord;
	bool flag = true;
	do {
		cout << "Enter your username:" << " ";
		getline(cin, UserName);
		if (UserName.empty()) {
			cout << "Error: Username cannot be empty. Please try again." << endl;
			continue;
		}
		if (UserName.find(' ') != string::npos) {
			cout << "Error: Username cannot contain spaces. Please try again." << endl;
			continue;
		}
		if (UserName.length() < 3 || UserName.length() > 20) {
			cout << "Error: Username must be between 3 and 20 characters. Please try again." << endl;
			continue;
		}
		if (User_Data_Storage.find(UserName) != User_Data_Storage.end()) {
			cout << "Username is already available, please try again!" << endl;  //Username da tung duoc luu  
			continue;
		}
		cout << "Enter your password:" << " ";
		getline(cin, PassWord);
		if (PassWord.empty()) {
			cout << "Error: Password cannot be empty. Please try again." << endl;
			continue;
		}
		if (PassWord.length() < 6) {
			cout << "Error: Password must be at least 6 characters long. Please try again." << endl;
			continue;
		}

		//Them 1 ham ma hoa mat khau

		cout << "Sign up successfully" << endl; //Username chua tung duoc luu => khong trung ten
		HashedPassWord = HashPassword(PassWord);
		Save_Data(UserName, HashedPassWord);
		User_Money(UserName, 500000);
		break;
	} while (true);

}

void User_Action::LogIn() {
	string UserName, PassWord;
	cout << "Enter your UserName" << endl;
	getline(cin, UserName);
	cout << "Enter your PassWord" << endl;
	getline(cin, PassWord);
	if (User_Data_Storage[UserName] == HashPassword(PassWord) && User_Data_Storage.find(UserName) != User_Data_Storage.end())
		cout << "Log in successfully" << endl; //Thong tin nhap trung khop voi thong tin da duoc luu
	else cout << "Username or Password is not correct!" << endl;
}

void User_Action::Choice() {
	Load_Data();
	Load_Money();
	Load_Data_NumGame();
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
		cout << "Current balance for " << UserName << ":" << User_Money_Data[UserName] << "VND" << endl;
	else cout << "User not found!" << endl;
}

int User_Action::Num_Game_Played(string Username) {

	return User_Game_Played[Username].second;
}

int User_Action::Num_Game_Won(string Username) {
	return User_Game_Won[Username].second;
}

double User_Action::Win_Rate(string Username) {
	int GamePlayed = Num_Game_Played(Username);
	if (GamePlayed == 0) return 0.0;
	return (Num_Game_Won(Username)) / (Num_Game_Played(Username));
} 

int User_Action::Leader_Board(string Username) {
	Board.push_back({ Win_Rate(Username), Username });
	sort(Board.begin(), Board.end(), greater<>());
	for (auto x : Board)
		cout << x.first << " " << x.second << endl;
}

int User_Action::Load_Data_NumGame() {
	fstream myFile;
	myFile.open("UserGamePlayed.txt", ios::in);
	string Username;
	int GamePlayed;
	if (myFile.is_open()) {
		while(myFile >> Username >> GamePlayed)
			User_Game_Played[Username] = GamePlayed;
		myFile.close();
	}
}

