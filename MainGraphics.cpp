#include "Graphics/libs.h"
#include "Graphics/GPokerApp.h"

// Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc, char *args[])
{
    GPokerApp app = GPokerApp();
    app.update();
    return 0;
}
