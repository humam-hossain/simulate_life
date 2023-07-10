#include <iostream>
#include <raylib.h>

int main(void)
{
    int screen_width = 1000;
    int screen_height = 800;
    InitWindow(screen_width, screen_height, "SmoothLife");
    SetTargetFPS(60);

    Image image = GenImagePerlinNoise(screen_width, screen_width, 0, 0, 5.0f);
    // Image image = GenImageWhiteNoise(screen_width, screen_height, 0.8f);
    RenderTexture2D texture = LoadRenderTexture(screen_width, screen_height);
    UpdateTexture(texture.texture, image.data);

    Shader shader = LoadShader(NULL, "./smoothlife.fs");

    while(!WindowShouldClose()){
        BeginDrawing();
            ClearBackground(BLACK);
            BeginShaderMode(shader);
                DrawTexture(texture.texture, 0, 0, BLUE);
            EndShaderMode();
        EndDrawing();
    }

    CloseWindow();

    return 0;
}