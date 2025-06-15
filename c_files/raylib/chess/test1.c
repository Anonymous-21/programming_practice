#include <math.h>
#include <raylib.h>

#define SCREEN_SIZE 800
#define SCREEN_TITLE "CHESS"
#define SCREEN_BACKGROUND RAYWHITE
#define GAME_FPS 60

#define BOARD_SIZE 8
#define TILE_SIZE (SCREEN_SIZE / BOARD_SIZE)

#define PIECE_COUNT 12
#define ASCII_SIZE 128

void
texture_arr_init(Texture2D* texture_arr)
{
    texture_arr[0] = LoadTexture("./assets/b_king_1x_ns.png");
    texture_arr[1] = LoadTexture("./assets/b_queen_1x_ns.png");
    texture_arr[2] = LoadTexture("./assets/b_rook_1x_ns.png");
    texture_arr[3] = LoadTexture("./assets/b_knight_1x_ns.png");
    texture_arr[4] = LoadTexture("./assets/b_bishop_1x_ns.png");
    texture_arr[5] = LoadTexture("./assets/b_pawn_1x_ns.png");
    texture_arr[6] = LoadTexture("./assets/w_king_1x_ns.png");
    texture_arr[7] = LoadTexture("./assets/w_queen_1x_ns.png");
    texture_arr[8] = LoadTexture("./assets/w_rook_1x_ns.png");
    texture_arr[9] = LoadTexture("./assets/w_knight_1x_ns.png");
    texture_arr[10] = LoadTexture("./assets/w_bishop_1x_ns.png");
    texture_arr[11] = LoadTexture("./assets/w_pawn_1x_ns.png");
}

void
piece_index_map_init(int* piece_index_map)
{
    // small_case is black
    piece_index_map['k'] = 0;
    piece_index_map['q'] = 1;
    piece_index_map['r'] = 2;
    piece_index_map['n'] = 3;
    piece_index_map['b'] = 4;
    piece_index_map['p'] = 5;

    // upper_case is white
    piece_index_map['K'] = 6;
    piece_index_map['Q'] = 7;
    piece_index_map['R'] = 8;
    piece_index_map['N'] = 9;
    piece_index_map['B'] = 10;
    piece_index_map['P'] = 11;
}

void
draw_board(char board[BOARD_SIZE][BOARD_SIZE],
           Texture2D* texture_arr,
           int* piece_index_map,
           int piece_padding)
{
    int index;

    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            int x = j * TILE_SIZE;
            int y = i * TILE_SIZE;

            // draw background blocks
            Color color = (i + j) % 2 == 0 ? LIGHTGRAY : DARKGRAY;
            DrawRectangle(x, y, TILE_SIZE, TILE_SIZE, color);

            // draw pieces
            if (board[i][j] != '_')
            {
                index = piece_index_map[( int ) board[i][j]];

                Texture2D current_texture = texture_arr[index];
                Rectangle source =
                  (Rectangle){ 0, 0, current_texture.width, current_texture.height };
                Rectangle dest = (Rectangle){ x + piece_padding,
                                              y + piece_padding,
                                              TILE_SIZE - piece_padding * 2,
                                              TILE_SIZE - piece_padding * 2 };
                Vector2 origin = (Vector2){ 0, 0 };
                float rotation = 0.0f;
                Color tint = WHITE;

                DrawTexturePro(current_texture, source, dest, origin, rotation, tint);
            }
        }
    }
}

bool
is_tile_occupied(char board[BOARD_SIZE][BOARD_SIZE], int row_index, int col_index)
{
    if (board[row_index][col_index] != "_")
    {
        return true;
    }

    return false;
}

void
drag_and_drop(char board[BOARD_SIZE][BOARD_SIZE])
{
    Vector2 mouse_pos = GetMousePosition();
    bool is_dragging = false;

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && !is_dragging)
    {
        int row_index = floor(mouse_pos.y / TILE_SIZE);
        int col_index = floor(mouse_pos.x / TILE_SIZE);

        if (is_tile_occupied(board, row_index, col_index))
        {
            is_dragging = true;
        }
    }
}

int
main(void)
{
    InitWindow(SCREEN_SIZE, SCREEN_SIZE, SCREEN_TITLE);
    SetTargetFPS(GAME_FPS);

    int piece_padding = 20;

    Texture2D texture_arr[PIECE_COUNT];
    texture_arr_init(texture_arr);

    int piece_index_map[ASCII_SIZE];
    piece_index_map_init(piece_index_map);

    char board[BOARD_SIZE][BOARD_SIZE] = {
        { 'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r' }, { 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p' },
        { '_', '_', '_', '_', '_', '_', '_', '_' }, { '_', '_', '_', '_', '_', '_', '_', '_' },
        { '_', '_', '_', '_', '_', '_', '_', '_' }, { '_', '_', '_', '_', '_', '_', '_', '_' },
        { 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P' }, { 'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R' }
    };

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(SCREEN_BACKGROUND);

        draw_board(board, texture_arr, piece_index_map, piece_padding);

        EndDrawing();
    }

    // unload textures
    for (int i = 0; i < PIECE_COUNT; i++)
    {
        UnloadTexture(texture_arr[i]);
    }

    CloseWindow();

    return 0;
}