#include <raylib.h>

#define ROWS 20
#define COLS 20
#define BLOCK_SIZE 30
#define MARGIN 100

typedef enum Direction
{
  RIGHT,
  LEFT,
  UP,
  DOWN

} Direction;

// SNAKE
typedef struct Snake
{
  int x;
  int y;
  int size;
  Direction direction;
  Rectangle list[ROWS * COLS];
  float last_time;
  float move_interval;

} Snake;

void
snake_init(Snake* snake)
{
  snake->x = MARGIN;
  snake->y = MARGIN;
  snake->direction = RIGHT;
  snake->size = 1;
  snake->list[0] = (Rectangle){ snake->x, snake->y, BLOCK_SIZE, BLOCK_SIZE };

  snake->last_time = 0.0f;
  snake->move_interval = 0.08f;
}

void
snake_draw(Snake* snake)
{
  for (int i = 0; i < snake->size; i++) {
    Color color = (i == 0) ? BLUE : SKYBLUE;

    DrawRectangleRec(snake->list[i], color);
  }
}

void
snake_handle_input(Snake* snake)
{
  if (IsKeyPressed(KEY_RIGHT) && snake->direction != LEFT) {
    snake->direction = RIGHT;
  }
  if (IsKeyPressed(KEY_LEFT) && snake->direction != RIGHT) {
    snake->direction = LEFT;
  }
  if (IsKeyPressed(KEY_DOWN) && snake->direction != UP) {
    snake->direction = DOWN;
  }
  if (IsKeyPressed(KEY_UP) && snake->direction != DOWN) {
    snake->direction = UP;
  }
}

void
snake_move(Snake* snake)
{
  switch (snake->direction) {
    case RIGHT:
      snake->x += BLOCK_SIZE;
      break;
    case LEFT:
      snake->x -= BLOCK_SIZE;
      break;
    case UP:
      snake->y -= BLOCK_SIZE;
      break;
    case DOWN:
      snake->y += BLOCK_SIZE;
      break;
  }
}

void
snake_update(Snake* snake)
{
  snake_handle_input(snake);

  float current_time = GetTime();
  if (current_time - snake->last_time >= snake->move_interval) {
    snake->last_time = current_time;
  }
}

// DRAW GRID
void
draw_grid()
{
  // outline rectangle
  DrawRectangleLinesEx((Rectangle){ MARGIN,
                                    MARGIN,
                                    GetScreenWidth() - MARGIN * 2,
                                    GetRenderHeight() - MARGIN * 2 },
                       5.0,
                       BLACK);

  // vertical lines
  for (int x = MARGIN + BLOCK_SIZE; x < GetScreenWidth() - MARGIN;
       x += BLOCK_SIZE) {
    DrawLineEx((Vector2){ x, MARGIN },
               (Vector2){ x, GetScreenHeight() - MARGIN },
               2.0f,
               BLACK);
  }
  // horizontal lines
  for (int y = MARGIN + BLOCK_SIZE; y < GetScreenHeight() - MARGIN;
       y += BLOCK_SIZE) {
    DrawLineEx((Vector2){ MARGIN, y },
               (Vector2){ GetScreenWidth() - MARGIN, y },
               2.0f,
               BLACK);
  }
}

// MAIN
int
main(void)
{
  const int SCREEN_WIDTH = 800;
  const int SCREEN_HEIGHT = 800;
  const char SCREEN_TITLE[] = "Snake";
  const Color SCREEN_BACKGROUND = RAYWHITE;
  const int GAME_FPS = 60;

  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE);
  SetTargetFPS(GAME_FPS);

  Snake snake;

  snake_init(&snake);

  while (!WindowShouldClose()) {
    // UPDATES
    snake_update(&snake);

    BeginDrawing();
    ClearBackground(SCREEN_BACKGROUND);

    // DRAW
    snake_draw(&snake);

    draw_grid();

    EndDrawing();
  }

  CloseWindow();

  return 0;
}