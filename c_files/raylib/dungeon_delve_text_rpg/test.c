#include <raylib.h>

int
main(void)
{
    const int SCREEN_WIDTH = 800;
    const int SCREEN_HEIGHT = 600;
    const char SCREEN_TITLE[] = "";
    const Color SCREEN_BACKGROUND = RAYWHITE;

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE);

    char* arr[] = { "test1",  "test2",  "test3",  "test4",  "test5",
                    "test6",  "test7",  "test8",  "test9",  "test10",
                    "test11", "test12", "test13", "test14", "test15",
                    "test16", "test17", "test18", "test19", "test20" };

    int total_elements = sizeof(arr) / sizeof(arr[0]);

    Rectangle layout_rect =
      (Rectangle){ 0, 0, GetScreenWidth(), GetScreenHeight() };

    int selected = 0;
    int first_visible_element = 0;
    int font_size = 30; // text_height
    int line_gap = 5;
    int line_height = font_size + line_gap;
    int margin = 100;
    int max_visible_elements =
      (layout_rect.height - line_gap - margin * 2) / line_height;
    int visible_text_height = (font_size * max_visible_elements) +
                              (line_gap * (max_visible_elements - 1));

    while (!WindowShouldClose()) {

        if (IsKeyPressed(KEY_UP)) {
            selected--;
            if (selected < 0) {
                selected = 0;
            }

            if (selected < first_visible_element) {
                first_visible_element = selected;
            }
        }
        if (IsKeyPressed(KEY_DOWN)) {
            selected++;
            if (selected > total_elements - 1) {
                selected = total_elements - 1;
            }

            if (selected > first_visible_element + max_visible_elements - 1) {
                first_visible_element++;
            }
        }

        BeginDrawing();
        ClearBackground(SCREEN_BACKGROUND);

        int last_visible_element = first_visible_element + max_visible_elements;

        for (int i = first_visible_element;
             i < total_elements && i < last_visible_element;
             i++) {
            int text_width = MeasureText(arr[i], font_size);
            int text_x =
              (int)layout_rect.x + (int)layout_rect.width / 2 - text_width / 2;
            int text_y = (int)layout_rect.y + (int)layout_rect.height / 2 -
                         visible_text_height / 2 +
                         ((i - first_visible_element) * line_height);

            Color color = (i == selected) ? BLACK : GRAY;
            DrawText(arr[i], text_x, text_y, font_size, color);

            if (i == selected) {
                DrawText(">", text_x - 30, text_y, font_size, color);
            }
        }

        DrawRectangleLinesEx((Rectangle){margin,
                      margin,
                      GetScreenWidth() - margin * 2,
                      GetScreenHeight() - margin * 2},
					  5.0,
                      GRAY);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}