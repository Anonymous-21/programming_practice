#include <ctype.h>
#include <raylib.h>
#include <string.h>

#define SCREEN_SIZE 800
#define SCREEN_TITLE "CHESS"
#define SCREEN_BACKGROUND RAYWHITE
#define GAME_FPS 60

#define BOARD_SIZE 8
#define SLOT_SIZE (SCREEN_SIZE / BOARD_SIZE)

#define PIECE_COUNT 12

void
draw_board()
{
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            int x = j * SLOT_SIZE;
            int y = i * SLOT_SIZE;

            Color color = (i + j) % 2 == 0 ? LIGHTGRAY : DARKGRAY;
            DrawRectangle(x, y, SLOT_SIZE, SLOT_SIZE, color);
        }
    }
}

// PIECE
typedef struct Piece
{
    Texture2D texture;
    Rectangle source;
    Rectangle dest;
    Vector2 origin;
    float rotation;
    Color tint;

} Piece;

void
piece_init(Piece* piece, const char* texture_path, int x, int y, int piece_padding)
{
    piece->texture = LoadTexture(texture_path);
    piece->source = (Rectangle){ 0, 0, piece->texture.width, piece->texture.height };
    piece->dest = (Rectangle){ x, y, SLOT_SIZE - piece_padding * 2, SLOT_SIZE - piece_padding * 2 };
    piece->origin = (Vector2){ 0, 0 };
    piece->rotation = 0.0f;
    piece->tint = WHITE;
}

void
piece_draw(Piece* piece)
{
    DrawTexturePro(
      piece->texture, piece->source, piece->dest, piece->origin, piece->rotation, piece->tint);
}

// PIECE INDEX MAP
typedef struct PieceIndexMap
{
    char character;
    int index;

} PieceIndexMap;

// DRAW PIECES ON BOARD
void
draw_pieces(char* fen_string,
            Texture2D* texture_arr,
            PieceIndexMap* piece_index_map,
            int piece_padding)
{
    int x = 0;
    int y = 0;

    for (int i = 0; fen_string[i] != '\0'; i++)
    {
        if (fen_string[i] == '/')
        {
            y++;
            x = 0;
        }
        else if (isdigit(fen_string[i]))
        {
            x += fen_string[i] - '0';
        }
        else
        {
            int index;
            for (int j = 0; j < PIECE_COUNT; j++)
            {
                if (piece_index_map[j].character == fen_string[i])
                {
                    index = piece_index_map[j].index;
                    break;
                }
            }
            
            Texture2D current_texture = texture_arr[index];
            Rectangle source = (Rectangle){ 0, 0, current_texture.width, current_texture.height };
            Rectangle dest = (Rectangle){ x * SLOT_SIZE + piece_padding,
                                          y * SLOT_SIZE + piece_padding,
                                          SLOT_SIZE - piece_padding * 2,
                                          SLOT_SIZE - piece_padding * 2 };
            Vector2 origin = (Vector2){ 0, 0 };
            float rotation = 0.0f;
            Color tint = WHITE;

            DrawTexturePro(current_texture, source, dest, origin, rotation, tint);

            x++;
        }
    }
}

// UNLOAD TEXTURES
void
unload_textures(Texture2D* texture_arr)
{
    for (int i = 0; i < PIECE_COUNT; i++)
    {
        UnloadTexture(texture_arr[i]);
    }
}

// MAIN
int
main(void)
{
    InitWindow(SCREEN_SIZE, SCREEN_SIZE, SCREEN_TITLE);
    SetTargetFPS(GAME_FPS);

    int piece_padding = 20;

    // texture array
    Texture2D texture_arr[PIECE_COUNT] = {
        LoadTexture("./assets/b_king_1x_ns.png"),   LoadTexture("./assets/b_queen_1x_ns.png"),
        LoadTexture("./assets/b_rook_1x_ns.png"),   LoadTexture("./assets/b_knight_1x_ns.png"),
        LoadTexture("./assets/b_bishop_1x_ns.png"), LoadTexture("./assets/b_pawn_1x_ns.png"),

        LoadTexture("./assets/w_king_1x_ns.png"),   LoadTexture("./assets/w_queen_1x_ns.png"),
        LoadTexture("./assets/w_rook_1x_ns.png"),   LoadTexture("./assets/w_knight_1x_ns.png"),
        LoadTexture("./assets/w_bishop_1x_ns.png"), LoadTexture("./assets/w_pawn_1x_ns.png"),
    };

    PieceIndexMap piece_index_map[PIECE_COUNT];
    piece_index_map[0].character = 'k';
    piece_index_map[0].index = 0;
    piece_index_map[1].character = 'q';
    piece_index_map[1].index = 1;
    piece_index_map[2].character = 'r';
    piece_index_map[2].index = 2;
    piece_index_map[3].character = 'n';
    piece_index_map[3].index = 3;
    piece_index_map[4].character = 'b';
    piece_index_map[4].index = 4;
    piece_index_map[5].character = 'p';
    piece_index_map[5].index = 5;
    piece_index_map[6].character = 'K';
    piece_index_map[6].index = 6;
    piece_index_map[7].character = 'Q';
    piece_index_map[7].index = 7;
    piece_index_map[8].character = 'R';
    piece_index_map[8].index = 8;
    piece_index_map[9].character = 'N';
    piece_index_map[9].index = 9;
    piece_index_map[10].character = 'B';
    piece_index_map[10].index = 10;
    piece_index_map[11].character = 'P';
    piece_index_map[11].index = 11;

    // fen string - starting position
    char fen_starting_position[] = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(SCREEN_BACKGROUND);

        draw_board();
        draw_pieces(fen_starting_position, texture_arr, piece_index_map, piece_padding);

        EndDrawing();
    }

    unload_textures(texture_arr);

    CloseWindow();

    return 0;
}