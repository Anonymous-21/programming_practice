#include "utils.h"
#include <raylib.h>
#include <raymath.h>

// BALL
typedef struct Ball
{
    Vector2 initial_pos;
    Vector2 pos;
    Vector2 direction;
    float radius;
    float initial_speed;
    float speed;
    float speed_increment;
    Color color;
    bool active;
    IntervalTimer interval_timer;

} Ball;

void
ball_init(Ball* ball)
{
    ball->initial_pos = (Vector2){ GetScreenWidth() * 0.5f, GetScreenHeight() * 0.5f };
    ball->pos = ball->initial_pos;
    ball->radius = 10.0f;
    ball->initial_speed = 300.0f;
    ball->speed = ball->initial_speed;
    ball->speed_increment = 10.0f;
    ball->direction.x = GetRandomValue(0, 1) == 0 ? -1 : 1;
    ball->direction.y = GetRandomValue(0, 1) == 0 ? -1 : 1;
    ball->color = RED;
    ball->active = false;

    interval_timer_init(&ball->interval_timer, 1.0f);
}

void
ball_reset(Ball* ball)
{
    ball->pos = ball->initial_pos;
    ball->speed = ball->initial_speed;
    ball->direction.x = GetRandomValue(0, 1) == 0 ? -1 : 1;
    ball->direction.y = GetRandomValue(0, 1) == 0 ? -1 : 1;
    ball->active = false;
}

void
ball_draw(Ball* ball)
{
    if (interval_timer_toggled(&ball->interval_timer) && !ball->active)
    {
        center_and_draw_text(
          "press SPACE to begin",
          30,
          (Rectangle){ 0, 0, ( float ) GetScreenWidth(), GetScreenHeight() + 300.0f });
    }

    DrawCircleV(ball->pos, ball->radius, ball->color);
}

void
ball_update(Ball* ball)
{
    interval_timer_update(&ball->interval_timer);

    // activate ball
    if (IsKeyPressed(KEY_SPACE))
    {
        ball->active = !ball->active;
    }

    // move ball
    if (ball->active)
    {
        ball->pos.x += ball->direction.x * ball->speed * GetFrameTime();
        ball->pos.y += ball->direction.y * ball->speed * GetFrameTime();
    }

    // normalize direction vector
    if (ball->direction.x != 0 && ball->direction.y != 0)
    {
        ball->direction = Vector2Normalize(ball->direction);
    }

    // ball bounds
    if (ball->pos.x < ball->radius || ball->pos.x > GetScreenWidth() - ball->radius)
    {
        ball->direction.x *= -1;
    }
    if (ball->pos.y < ball->radius || ball->pos.y > GetScreenHeight() - ball->radius)
    {
        ball->direction.y *= -1;
    }
}

// PADDLE
typedef struct Paddle
{
    Rectangle initial_rect;
    Rectangle rect;
    float speed;
    Color color;

} Paddle;

void
paddle_init(Paddle* paddle, float x)
{
    float height = 100.0f;
    paddle->initial_rect =
      (Rectangle){ x, ( float ) (GetScreenHeight()) / 2 - height / 2, 10.0f, height };
    paddle->rect = paddle->initial_rect;
    paddle->speed = 300.0f;
    paddle->color = BLACK;
}

void
paddle_draw(Paddle* paddle)
{
    DrawRectangleRec(paddle->rect, paddle->color);
}

void
paddle_update_player(Paddle* paddle)
{
    if (IsKeyDown(KEY_UP) && paddle->rect.y > 0)
    {
        paddle->rect.y -= paddle->speed * GetFrameTime();
    }
    if (IsKeyDown(KEY_DOWN) && paddle->rect.y < GetScreenHeight() - paddle->rect.height)
    {
        paddle->rect.y += paddle->speed * GetFrameTime();
    }
}

void
paddle_update_ai(Paddle* paddle, Ball* ball)
{
    if (ball->pos.y < paddle->rect.y + paddle->rect.height / 2 && paddle->rect.y > 0)
    {
        paddle->rect.y -= paddle->speed * GetFrameTime();
    }
    if (ball->pos.y > paddle->rect.y + paddle->rect.height / 2 &&
        paddle->rect.y < GetScreenHeight() - paddle->rect.height)
    {
        paddle->rect.y += paddle->speed * GetFrameTime();
    }
}

// MAIN
int
main(void)
{
    const int SCREEN_WIDTH = 800;
    const int SCREEN_HEIGHT = 600;
    const char SCREEN_TITLE[] = "Pong";
    const Color SCREEN_BACKGROUND = LIGHTGRAY;

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE);

    int score_left = 0;
    int score_right = 0;

    Ball ball;
    Paddle player;
    Paddle ai;

    ball_init(&ball);
    paddle_init(&player, 10.0f);
    paddle_init(&ai, GetScreenWidth() - player.rect.width - 10.0f);

    while (!WindowShouldClose())
    {
        ball_update(&ball);
        paddle_update_player(&player);
        paddle_update_ai(&ai, &ball);

        BeginDrawing();
        ClearBackground(SCREEN_BACKGROUND);

        center_and_draw_text(TextFormat("%d", score_left),
                             40,
                             (Rectangle){ 0, 0, GetScreenWidth() * 0.5f, 100.0f },
                             BLACK);
        center_and_draw_text(
          TextFormat("%d", score_left),
          40,
          (Rectangle){ GetScreenWidth() * 0.5f, 0, GetScreenWidth() * 0.5f, 100.0f },
          BLACK);

        ball_draw(&ball);
        paddle_draw(&player);
        paddle_draw(&ai);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}