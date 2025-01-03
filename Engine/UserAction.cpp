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
void User_Action::NumGameToFile() {
	std::fstream myFile;
	myFile.open("data/UserGamePlayed.txt", std::ios::out);
	if (myFile.is_open()) {
		for (auto x : User_Game_Played) {
			myFile << x.first << std::endl;
			myFile << x.second << std::endl;
		}
		myFile.close();
	}
	else std::cout << "Can not open UserData file" << std::endl;
}
void User_Action::MoneyGameToFile() {
	std::fstream myFile;
	myFile.open("data/UserMoney.txt", std::ios::out);
	if (myFile.is_open()) {
		for (auto x : User_Money_Data) {
			myFile << x.first << std::endl;
			myFile << x.second << std::endl;
		}
		myFile.close();
	}
	else std::cout << "Can not open UserData file" << std::endl;
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
				SignUp(UserName);
			else if (action == 'N')
				Choice(UserName);
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

void User_Action::Leader_Board() {
	sort(Board.begin(), Board.end());
	int j = 1;
	for (auto x : Board) {
		std::cout << "Ranking " << j << ": " << x.first << " % " << " " << "-" << x.second << std::endl;
		j++;
	}
}
void User_Action::SignUp(std::string& Username1) {
	std::cout << "Welcome to sign up" << " " << std::endl;
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
		Username1 = UserName;
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
		User_Data_Storage[UserName] = PassWord;
		Save_Data(UserName, PassWord);
		User_Money(UserName, 1000); // 1000 USD mac dinh
		//CLI::getEnter();
		LogIn(Username1);
		return;

	} while (true);
}

void User_Action::LogIn(std::string& Username1) {
	std::cout << "Welcome to login" << std::endl;
	std::string UserName, PassWord;

	while (true) {
		std::cout << "Enter your UserName: ";
		getline(std::cin, UserName);
		std::cout << "Enter your PassWord: ";
		getline(std::cin, PassWord);

		// Check if username and password match stored data
		if (User_Data_Storage.find(UserName) != User_Data_Storage.end() && User_Data_Storage[UserName] == PassWord) {
			std::cout << "Log in successfully" << std::endl;
			Username1 = UserName; // Update the reference parameter
			return;
		}
		else {
			std::cout << "Username or Password is not correct!" << std::endl;

			// Offer to sign up or retry
			char action;
			while (true) {
				std::cout << "Do you want to sign up? (Y/N): ";
				std::cin >> action;
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer

				// Normalize input to uppercase and validate
				action = toupper(action);
				if (action == 'Y' || action == 'N') break;
				std::cout << "Invalid input, please enter 'Y' or 'N'." << std::endl;
			}

			if (action == 'Y') {
				SignUp(Username1);
				return;
			}
			else if (action == 'N') {
				Choice(Username1);
				return;
			}
		}
	}
}

bool User_Action::Choice(std::string& Username) {
	// Clear the screen
	CLI::clearScreen();
	//Load_Data();
	//Load_Money();
	//Load_Data_NumGame();
	// 3 ham nay tai khi khoi dong game
	// Print the game title
	CLI::title();
	bool CheckInput = false;
	std::cout << std::endl << "Welcome to the game! Please choose an option: " << std::endl;
	std::cout << "1. Sign Up\n";
	std::cout << "2. Log In\n";
	std::cout << "0. Exit\n";
	int action = CLI::getOptionNum(0, 2);
	if (action == 1) {
		SignUp(Username);
	}
	else if (action == 2) {
		LogIn(Username);
	}
	else if (action == 0) {
		std::cout << "Thanks for using our game!" << std::endl;
		return false;
	}
	else {
		std::cout << "Invalid input, please try again " << std::endl;
		Choice(Username);
	}

	return true;

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

void User_Action::Load_LeaderBoard() {
	for (auto x : User_Game_Played)
		Board.push_back({ Win_Rate(x.first), x.first });
}
void User_Action::Display_Leader_Board(std::string Username) {

	Board.push_back({ Win_Rate(Username), Username });
}
void User_Action::WinRateToFile() {
	std::fstream myFile;
	myFile.open("data/UserWinRate.txt", std::ios::out);
	if (myFile.is_open()) {
		for (auto x : Board) {
			myFile << x.first << std::endl;
			myFile << x.second << std::endl;
		}
		myFile.close();
	}
	else std::cout << "Can not open UserWinRate file" << std::endl;
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

