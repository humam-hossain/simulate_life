#include <iostream>
#include <stdlib.h>
#include <raylib.h>

float rand_float(void)
{
    return (float)rand() / (float)RAND_MAX;
}

int main() {
	int factor = 80;
	int screen_width = 16*factor;
	int screen_height = 9*factor;
	InitWindow(screen_width, screen_height, "SmoothLife");
	SetTargetFPS(60);

	Image image = GenImagePerlinNoise(screen_width, screen_height, 0, 0, 5.0f);
	// Image image = GenImageWhiteNoise(screen_width, screen_height, 0.8f);
	// Image image = GenImageCellular(screen_width, screen_height, screen_height/6);
	// Image image = GenImageColor(screen_width, screen_height, BLACK);
	// for(int y=0; y<screen_height/4; ++y){
	// 	for(int x=0; x<screen_width/4; ++x){

	// 		uint8_t v = rand_float()*255.0f;
	// 		Color color = {v, v, v, 255};
	// 		ImageDrawPixel(&image, x, y, color);
	// 	}
	// }
	
	RenderTexture2D state[2];
	
	state[0] = LoadRenderTexture(screen_width, screen_height);
	SetTextureWrap(state[0].texture, TEXTURE_WRAP_REPEAT);
	UpdateTexture(state[0].texture, image.data);

	state[1] = LoadRenderTexture(screen_width, screen_height);
	SetTextureWrap(state[1].texture, TEXTURE_WRAP_REPEAT);

	Shader shader = LoadShader(NULL, "./smoothlife.fs");
	Vector2 resolution = {screen_width, screen_height};
	int resolution_loc = GetShaderLocation(shader, "resolution");
	SetShaderValue(shader, resolution_loc, &resolution, SHADER_UNIFORM_VEC2);

	size_t i = 0;

	while (!WindowShouldClose()) {
		BeginTextureMode(state[1 - i]);
			ClearBackground(BLACK);
			BeginShaderMode(shader);
				DrawTexture(state[i].texture, 0, 0, WHITE);
			EndShaderMode();
		EndTextureMode();
		
		BeginDrawing();
			ClearBackground(BLACK);
			DrawTexture(state[1 - i].texture, 0, 0, WHITE);
		EndDrawing();

		i = 1 - i;
	}

	CloseWindow(); 

	return 0;
}
