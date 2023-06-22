#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define HEIGHT 10
#define WIDTH 10

float grid[HEIGHT][WIDTH] = { 0.0f };
char level[] = " .-=coaA@#";
#define level_count (sizeof(level) / sizeof(level[0]) - 1)

float ra = 21;

float rand_float(void)
{
    return (float)rand() / (float)RAND_MAX;
}

void random_grid(void) {
    for (size_t y = 0; y < HEIGHT; ++y) {
        for (size_t x = 0; x < WIDTH; ++x) {
            grid[y][x] = rand_float();
        }
    }
}

void display_grid(void) {
    for (size_t y = 0; y < HEIGHT; ++y) {
        for (size_t x = 0; x < WIDTH; ++x) {
            char c = level[(int)(grid[y][x] * (level_count - 1))];

            printf("%c", c);
        }
        printf("\n");
    }
}

int emod(int a, int b) {
    return (a % b + b) % b;
}

int main()
{
    srand(time(0));
    random_grid();

    int cx = 0;
    int cy = 0;
    float m = 0;
    float n = 0;
    int M = 0;
    int N = 0;

    int ri = ra / 3;

    for (int dy = -(ra - 1); dy < ra; ++dy) {
        for (int dx = -(ra - 1); dx < ra; ++dx) {
            int y = emod(cy + dy, HEIGHT);
            int x = emod(cx + dx, WIDTH);

            if (dx * dx + dy * dy <= ri * ri) {
                m += grid[y][x];
                M += 1;
            }
            else if (dx * dy + dy * dy <= ra * ra) {
                n += grid[y][x];
                N += 1;
            }
        }
    }

    m /= M;
    n /= N;

    printf("m = %f \t n=%f\n", m, n);

    // display_grid();

    return 0;
}