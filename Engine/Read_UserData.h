#ifndef READ_USERDATA_H
#define READ_USERDATA_H

#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

class User_Action {
   private:
    unordered_map<string, string> User_Data_Storage;

   public:
    void Choice();
    void SignUp();
    void Load_Data();
    void Save_Data(string, string);
    void LogIn();
};

/* TODO:
User data:
- tên (name)
- điểm
- số game đã chơi (gamesPlayed)
- số game đã thắng (gamesWon)
- winrate (tính từ hai thông số trên)
- favoriteStrat ("chiến thuật" hay chơi nhất, e.g. flush, straight, ...)

Hiển thị leaderboard gồm 10 người chơi tốt nhất (mấy ông cứ tạo dữ liệu giả bỏ
vào :V)

Có thể nghiên cứu thêm cách store dữ liệu vào file binary để tăng tốc độ,giảm
kích cỡ,...
https://www.eecs.umich.edu/courses/eecs380/HANDOUTS/cppBinaryFileIO-2.html
*/

#endif