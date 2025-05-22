#include <raylib.h>

int
main(void)
{
  const int SCREEN_WIDTH = 800;
  const int SCREEN_HEIGHT = 600;
  const char SCREEN_TITLE[] = "";
  const Color SCREEN_BACKGROUND = RAYWHITE;

  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE);

  Rectangle rect = (Rectangle){ 10, 10, 100, 100 };
  Color color = RED;
  Vector2 offset = (Vector2){ 0, 0 };
  bool dragging = false;

  while (!WindowShouldClose()) {
    Vector2 mouse_pos = GetMousePosition();

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) &&
        CheckCollisionPointRec(mouse_pos, rect)) {
      dragging = true;
      offset.x = mouse_pos.x - rect.x;
      offset.y = mouse_pos.y - rect.y;
    }

    if (dragging) {
      rect.x = mouse_pos.x - offset.x;
      rect.y = mouse_pos.y - offset.y;
    }

    if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
      dragging = false;
    }

    BeginDrawing();
    ClearBackground(SCREEN_BACKGROUND);

    DrawRectangleRec(rect, color);

    EndDrawing();
  }

  CloseWindow();

  return 0;
}