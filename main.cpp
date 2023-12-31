#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string>

#define HEIGHT 100
#define WIDTH 100

float grid[HEIGHT][WIDTH] = {0.0f};
float grid_diff[HEIGHT][WIDTH] = {0.0f};

char level[] = " .-=coaA@#";
#define level_count (sizeof(level) / sizeof(level[0]) - 1)

float ra = 11.0f;
float alpha_n = 0.028f;
float alpha_m = 0.147f;
float b1 = 0.278f;
float b2 = 0.365f;
float d1 = 0.267f;
float d2 = 0.445f;
float dt = 0.01f;

float rand_float(void)
{
    return (float)rand() / (float)RAND_MAX;
}

void random_grid(void)
{
    size_t w = WIDTH / 2;
    size_t h = HEIGHT / 2;
    for (size_t dy = 0; dy < h; ++dy)
    {
        for (size_t dx = 0; dx < w; ++dx)
        {
            size_t y = dy + HEIGHT / 2 - h / 2;
            size_t x = dx + WIDTH / 2 - w / 2;

            grid[y][x] = rand_float();
        }
    }
}

void display_grid(float grid[HEIGHT][WIDTH])
{
    for (size_t y = 0; y < HEIGHT; ++y)
    {
        for (size_t x = 0; x < WIDTH; ++x)
        {
            char c = level[(int)(grid[y][x] * (level_count - 1))];

            fputc(c, stdout);
            fputc(c, stdout);
        }
        fputc('\n', stdout);
    }
}

int emod(int a, int b)
{
    return (a % b + b) % b;
}

float sigma(float x, float a, float alpha)
{
    return 1.0f / (1.0f + expf(-(x - a) * 4 / alpha));
}

float sigma_n(float x, float a, float b)
{
    return sigma(x, a, alpha_n) * (1 - sigma(x, b, alpha_n));
}

float sigma_m(float x, float y, float m)
{
    return x * (1 - sigma(m, 0.5f, alpha_m)) + y * sigma(m, 0.5f, alpha_m);
}

float s(float n, float m)
{
    return sigma_n(n, sigma_m(b1, d1, m), sigma_m(b2, d2, m));
}

void compute_grid_diff(void)
{
    for (int cy = 0; cy < HEIGHT; ++cy)
    {
        for (int cx = 0; cx < WIDTH; ++cx)
        {
            float m = 0;
            float n = 0;
            float M = 0;
            float N = 0;

            float ri = ra / 3;

            for (int dy = -(ra - 1); dy < ra; ++dy)
            {
                for (int dx = -(ra - 1); dx < ra; ++dx)
                {
                    int y = emod(cy + dy, HEIGHT);
                    int x = emod(cx + dx, WIDTH);

                    if (dx * dx + dy * dy <= ri * ri)
                    {
                        m += grid[y][x];
                        M += 1;
                    }
                    else if (dx * dy + dy * dy <= ra * ra)
                    {
                        n += grid[y][x];
                        N += 1;
                    }
                }
            }

            m /= M;
            n /= N;

            float q = s(n, m);
            grid_diff[cy][cx] = 2 * q - 1;
        }
    }
}

void clamp(float *x, float l, float h)
{
    if (*x < l)
        *x = l;
    if (*x > h)
        *x = h;
}

int main()
{
    srand((unsigned int)time(0));
    random_grid();

    for (;;)
    {
        std::cout << "SIMULATION OF LIFE \n\n";
        display_grid(grid);
        for (size_t y = 0; y < HEIGHT; ++y)
        {
            for (size_t x = 0; x < WIDTH; ++x)
            {
                grid[y][x] += dt * grid_diff[y][x];
                clamp(&grid[y][x], 0, 1);
            }
        }
        compute_grid_diff();
    }

    return 0;
}