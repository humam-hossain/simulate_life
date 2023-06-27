#include <iostream>
#include <raylib.h>

int main(void)
{
    int screen_width = 400;
    int screen_height = 300;
    InitWindow(screen_width, screen_height, "SmoothLife");
    SetTargetFPS(60);

    Image image = GenImagePerlinNoise(screen_width, screen_height, 0,0,5.0f);
    // Image image = GenImageWhiteNoise(screen_width, screen_height, 0.2f);

    RenderTexture2D state[2];
    state[0] = LoadRenderTexture(screen_width, screen_height);
    state[1] = LoadRenderTexture(screen_width, screen_height);

    UpdateTexture(state[0].texture, image.data);

    Shader shader = LoadShader(NULL, "./smoothlife.fs");

    size_t i = 0;
    while(!WindowShouldClose()){
        BeginTextureMode(state[1 - i]);
            ClearBackground(BLACK);
            BeginShaderMode(shader);
                DrawTexture(state[i].texture, 0, 0, BLUE);
            EndShaderMode();
        EndTextureMode();

        BeginDrawing();
            ClearBackground(BLACK);
            DrawTexture(state[1 - i].texture, 0, 0, BLUE);
        EndDrawing();

        i = i - 1;
    }

    CloseWindow();

    return 0;
}