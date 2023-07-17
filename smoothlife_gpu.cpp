#include <iostream>
#include <raylib.h>

int main() {
	int screen_width = 800;
	int screen_height = 600;
	InitWindow(screen_width, screen_height, "SmoothLife");
	SetTargetFPS(60);

	// Image image = GenImagePerlinNoise(screen_width, screen_height, 0, 0, 5.0f);
	// Image image = GenImageWhiteNoise(screen_width, screen_height, 0.2f);
	Image image = GenImageCellular(screen_width, screen_height, screen_height/6);
	
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
