#include "Read_UserData.h"

int User_Data::Num_Game_Played(string Username) {
	
	return User_Game_Played[Username].second;
}

int User_Data::Num_Game_Won(string Username){
	return User_Game_Won[Username].second;
}

double User_Data::Win_Rate(string Username) {
	return (User_Game_Won[Username].second) / (User_Game_Played[Username]) ;
}
int User_Data::Leader_Board(string Username) {
	Board.push_back(Win_Rate(Username));
	sort(board.begin(), board.end());
	for (auto x : Board)
		cout << x << endl;
}
int User_Data::Load_Data() {
	fstream myFile;
	myFile.open("UserGamePlayed.txt", ios::in);
	string Username;
	int GamePlayed;
	if (myFile.is_open()) {
		While(myFile >> Username >> GamePlayed) 
			User_Game_Played[Username] = GamePlayed;
		myFile.close();
	}
}
