#include "Read_UserData.h"

std::unordered_map<std::string, std::string> User_Data_Storage;
std::unordered_map<std::string, long long> User_Money_Data;
std::unordered_map<std::string, int> User_Game_Played;
std::unordered_map<std::string, int> User_Game_Won;
std::vector<std::pair<double, std::string>> Board;

// Tai ten dang nhap va mat khau da duoc luu cua nguoi dung vao chuong trinh
void User_Action::Load_Data() {
	std::fstream myFile("data/UserData.txt", std::ios::out | std::ios::app); // Tao file neu chua ton tai file san
	myFile.close(); // Dong lai file sau khi kiem tra
	myFile.open("data/UserData.txt", std::ios::in); 
	std::string UserName, PassWord;
	if (myFile.is_open()) {
		while (myFile >> UserName >> PassWord)
			User_Data_Storage[UserName] = PassWord;
		myFile.close();
	}
	else std::cout << "Trouble in loading user data" << std::endl;
}

// Tai so tien cua nguoi dung 
void User_Action::Load_Money() {
	std::fstream myFile("data/UserMoney.txt", std::ios::out | std::ios::app);
	myFile.close(); 
	myFile.open("data/UserMoney.txt", std::ios::in);
	std::string UserName;
	long long Money;
	if (myFile.is_open()) {
		while (myFile >> UserName >> Money)
			User_Money_Data[UserName] = Money;
		myFile.close();
	}
	else std::cout << "Trouble in loading user data" << std::endl;
}

//Luu thong tin nguoi dung dang ki
void User_Action::Save_Data(std::string UserName, std::string PassWord) {
	std::fstream myFile;
	myFile.open("data/UserData.txt", std::ios::app);
	if (myFile.is_open()) {
		myFile << UserName << std::endl;
		myFile << PassWord << std::endl;
		myFile.close();
	}
	else {
		char action;
		std::cout << "Trouble in saving UserData!" << std::endl; 
		std::cout << "Do you want to sign up again? (Y/N)" << std::endl;
		do {
			std::cin >> action;
			toupper(action);
			if (action == 'Y')
				SignUp();
			else if (action == 'N')
				Choice();
		} while (action != 'Y' && action != 'N');
	}
}

//Luu money nguoi dung luc dang ki
void User_Action::User_Money(std::string UserName, long long Money) {
	std::fstream myFile;
	myFile.open("data/UserMoney.txt", std::ios::app);
	if (myFile.is_open()) {
		myFile << UserName << std::endl;
		myFile << Money << std::endl;
		myFile.close();
	}
	else std::cout << "Trouble in saving UserMoney!" << std::endl;
}

// Ham nay giup nguoi dung dang ki
void User_Action::SignUp() {
	std::string UserName;
	std::string PassWord;
	std::string HashedPassWord;
	do {
		std::cout << "Enter your username:" << " ";
		getline(std::cin, UserName);
		if (UserName.empty()) {
			std::cout << "Error: Username cannot be empty. Please try again." << std::endl;
			continue;
		}
		if (UserName.find(' ') != std::string::npos) {
			std::cout << "Error: Username cannot contain spaces. Please try again." << std::endl;
			continue;
		}
		if (UserName.length() < 3 || UserName.length() > 20) {
			std::cout << "Error: Username must be between 3 and 20 characters. Please try again." << std::endl;
			continue;
		}
		if (User_Data_Storage.find(UserName) != User_Data_Storage.end()) {
			std::cout << "Username is already available, please try again!" << std::endl;  //Username da tung duoc luu  
			continue;
		}
		std::cout << "Enter your password:" << " ";
		getline(std::cin, PassWord);
		if (PassWord.empty()) {
			std::cout << "Error: Password cannot be empty. Please try again." << std::endl;
			continue;
		}
		if (PassWord.length() < 6) {
			std::cout << "Error: Password must be at least 6 characters long. Please try again." << std::endl;
			continue;
		}
		if (PassWord.find(' ') != std::string::npos) {
			std::cout << "Error: Password cannot contain spaces. Please try again." << std::endl;
			continue;
		}
		std::cout << "Sign up successfully" << std::endl; //Username chua tung duoc luu => khong trung ten
		Save_Data(UserName, PassWord);
		User_Money(UserName, 5000); // 5000 USD mac dinh
		CLI::getEnter();
		return;
	} while (true);
}

void User_Action::LogIn() {
	std::string UserName, PassWord;
	while (true) {
		std::cout << "Enter your UserName" << std::endl;
		getline(std::cin, UserName);
		std::cout << "Enter your PassWord" << std::endl;
		getline(std::cin, PassWord);
		if (User_Data_Storage.find(UserName) != User_Data_Storage.end() && User_Data_Storage[UserName] == PassWord) {
			std::cout << "Log in successfully" << std::endl; //Thong tin nhap trung khop voi thong tin da duoc luu
			return;
		}
		else {
		TryAgain :
			std::cout << "Username or Password is not correct!" << std::endl;
			std::cout << "Do you want to sign up ? (Y/N)" << std::endl;
			char action;
			std::cin >> action;
			if (std::cin.fail() || (action != 'y' && action != 'Y' && action != 'n' && action != 'N')) {
				std::cout << "Invalid input, please try again" << std::endl;
				std::cin.clear(); // Clear the error flag
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard the row
				CLI::getEnter();
				goto TryAgain;
			}
			action = toupper(action);
			std::cout << action << std::endl;
			do {
				if (action == 'Y'){
					std::cout << "bruh wtf" << std::endl;
					SignUp();  
					break;
				}
				else if (action == 'N') {
					Choice();
					return;
				}
			} while (action != 'Y' && action != 'N');
		}
	}
}	

int User_Action::Choice() {
	// Clear the screen
	CLI::clearScreen();

	// Loading data to the game
	Load_Data();
	Load_Money();
	Load_Data_NumGame();

	// Print the game title
	CLI::title();

	// User action
	std::cout << std::endl << "Welcome to the game! Please choose an option: " << std::endl;
	std::cout << "1. Sign Up\n";
	std::cout << "2. Log In\n";
	std::cout << "0. Exit\n";
	int action = CLI::getOptionNum(0, 2);
	if (action == 1) {
		SignUp();
	}
	else if (action == 2) {
		LogIn();
	}
	else if (action == 0) {
		std::cout << "Thanks for using our game!" << std::endl;
	}
	else {
		std::cout << "Invalid input, please try again " << std::endl;
		Choice();
	}

	return action;
}

//Cap nhat so tien nguoi dung va luu lai trong file UserMoney.txt
void User_Action::Update_Money(std::string UserName, long long MoneyChange) {
	if (User_Money_Data.find(UserName) != User_Money_Data.end()) {
		User_Money_Data[UserName] += MoneyChange;
		std::fstream myFile;
		myFile.open("data/UserMoney.txt", std::ios::out);
		if (myFile.is_open()) {
			for (const auto& user : User_Money_Data) {
				myFile << user.first << std::endl;
				myFile << user.second << std::endl;
			}
			myFile.close();
		}
		else std::cout << "Trouble in updating money data!" << std::endl;
	}
	else std::cout << "User not found, cannot update money!" << std::endl;
}

//Hien thi so tien nguoi dung
void User_Action::Display_Money(std::string UserName) {
	if (User_Money_Data.find(UserName) != User_Money_Data.end()) 
		std::cout << "Current balance for " << UserName << ":" << User_Money_Data[UserName] << "$" << std::endl;
	else std::cout << "User not found!" << std::endl;
}

int User_Action::Num_Game_Played(std::string Username) {
	return User_Game_Played[Username];
}

int User_Action::Num_Game_Won(std::string Username) {
	return User_Game_Won[Username];
}

double User_Action::Win_Rate(std::string Username) {
	int GamePlayed = User_Game_Played[Username];
	if (GamePlayed == 0) return 0.0;
	return ((Num_Game_Won(Username)) / (Num_Game_Played(Username)));
} 

void User_Action::Display_Leader_Board(std::string Username) {
	Board.push_back({Win_Rate(Username), Username});
	sort(Board.begin(), Board.end());
	for (auto x : Board)
		std::cout << x.first << " " << x.second << std::endl;
}

void User_Action::Load_Data_NumGame() {
	std::fstream myFile("data/UserGamePlayed.txt", std::ios::out | std::ios::app); 
	myFile.close(); 
	myFile.open("data/UserGamePlayed.txt", std::ios::in);
	std::string Username;
	int GamePlayed, GameWon;
	if (myFile.is_open()) {
		while (myFile >> Username >> GamePlayed >> GameWon) {
			User_Game_Won[Username] = GameWon;
			User_Game_Played[Username] = GamePlayed;
		}
		myFile.close();
	}
	else std::cout << "Can not open UserGamePlayed.txt file" << std::endl;
}

