#include <iostream>
#include <raylib.h>

int main(void)
{
    int screen_width = 800;
    int screen_height = 600;
    InitWindow(screen_width, screen_height, "SmoothLife");
    SetTargetFPS(60);

    while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(RED);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}