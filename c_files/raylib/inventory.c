#include <raylib.h>

// NOTE: big box from where you can drag rects of random colors, inventory, drag and drop

int main(void) {
  const int SCREEN_WIDTH = 800;
  const int SCREEN_HEIGHT = 600;
  const char SCREEN_TITLE[] = "Inventory";
  const Color SCREEN_BACKGROUND = RAYWHITE;

  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE);

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(SCREEN_BACKGROUND);
    EndDrawing();
  }

  CloseWindow();

  return 0;
}