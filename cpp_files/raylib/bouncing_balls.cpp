#include <raylib.h>
#include <raymath.h>

#define NUM_OF_BALLS 200

class Ball
{
  public:
    Vector2 pos;
    float radius;
    float speed;
    Vector2 direction;
    Color color;

    Ball()
    {
        radius = GetRandomValue(10, 30);
        pos.x = GetRandomValue(radius, GetScreenWidth() - radius);
        pos.y = GetRandomValue(radius, GetScreenHeight() - radius);
        speed = GetRandomValue(100, 300);
        direction.x = GetRandomValue(0, 1) == 0 ? -1 : 1;
        direction.y = GetRandomValue(0, 1) == 0 ? -1 : 1;
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
        pos.x += direction.x * speed * GetFrameTime();
        pos.y += direction.y * speed * GetFrameTime();

        // normalize direction vector
        if (direction.x != 0 && direction.y != 0)
        {
            direction = Vector2Normalize(direction);
        }

        // ball bounds
        if (pos.x < radius || pos.x > GetScreenWidth() - radius)
        {
            direction.x *= -1;
        }
        if (pos.y < radius || pos.y > GetScreenHeight() - radius)
        {
            direction.y *= -1;
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