#include <raylib.h>
#include <raymath.h>
#include <cmath>

#define NUM_OF_BALLS 200

class Ball
{
  public:
    Vector2 pos;
    float radius;
    Vector2 velocity;
    Color color;

    Ball()
    {
        radius = GetRandomValue(10, 30);
        pos.x = GetRandomValue(radius, GetScreenWidth() - radius);
        pos.y = GetRandomValue(radius, GetScreenHeight() - radius);
        float speed = GetRandomValue(100, 300);
        float angle = GetRandomValue(0, 360) * DEG2RAD;
        velocity.x = cos(angle) * speed;
        velocity.y = sin(angle) * speed;
        color = (Color){ static_cast<unsigned char>(GetRandomValue(0, 255)),
                         static_cast<unsigned char>(GetRandomValue(0, 255)),
                         static_cast<unsigned char>(GetRandomValue(0, 255)),
                         255 };
    }

    void draw() const
    {
        DrawCircleV(pos, radius, color);
    }

    void update()
    {
        // move ball
        pos.x += velocity.x * GetFrameTime();
        pos.y += velocity.y * GetFrameTime();

        // ball bounds
        if (pos.x < radius || pos.x > GetScreenWidth() - radius)
        {
            velocity.x *= -1;
        }
        if (pos.y < radius || pos.y > GetScreenHeight() - radius)
        {
            velocity.y *= -1;
        }
    }
};

int
main(void)
{
    const int SCREEN_WIDTH = 800;
    const int SCREEN_HEIGHT = 600;
    const char SCREEN_TITLE[] = "Bouncing Balls";
    const Color SCREEN_BACKGROUND = LIGHTGRAY;

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE);

    Ball balls[NUM_OF_BALLS];

    for (int i = 0; i < NUM_OF_BALLS; i++)
    {
        Ball ball;

        balls[i] = ball;
    }

    while (!WindowShouldClose())
    {
        for (int i = 0; i < NUM_OF_BALLS; i++)
        {
            balls[i].update();
        }

        BeginDrawing();
        ClearBackground(SCREEN_BACKGROUND);

        for (int i = 0; i < NUM_OF_BALLS; i++)
        {
            balls[i].draw();
        }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}