#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800
#define SCREEN_TITLE "CHESS"
#define SCREEN_BACKGROUND LIGHTGRAY
#define GAME_FPS 60

#define ROWS 8
#define COLS 8
#define SLOT_WIDTH (SCREEN_WIDTH / ROWS)
#define SLOT_HEIGHT (SCREEN_HEIGHT / COLS)

void
draw_board()
{
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            int x = j * SLOT_WIDTH;
            int y = i * SLOT_HEIGHT;

            Color color = (i + j) % 2 == 0 ? LIGHTGRAY : DARKGRAY;

            DrawRectangle(x, y, SLOT_WIDTH, SLOT_HEIGHT, color);
        }
    }
}

typedef enum PieceType
{
    TYPE_KING,
    TYPE_QUEEN,
    TYPE_ROOK,
    TYPE_KNIGHT,
    TYPE_BISHOP,
    TYPE_PAWN,

} PieceType;

typedef enum PieceColor
{
    COLOR_BLACK,
    COLOR_WHITE,

} PieceColor;

void
load_texture(Texture2D* texture, PieceType type, PieceColor color)
{
    switch (type)
    {
        case TYPE_KING:
            if (color == COLOR_BLACK)
            {
                *texture = LoadTexture("assets/b_king_1x_ns.png");
            }
            else if (color == COLOR_WHITE)
            {
                *texture = LoadTexture("assets/w_king_1x_ns.png");
            }
            break;
        case TYPE_QUEEN:
            if (color == COLOR_BLACK)
            {
                *texture = LoadTexture("assets/b_queen_1x_ns.png");
            }
            else if (color == COLOR_WHITE)
            {
                *texture = LoadTexture("assets/w_queen_1x_ns.png");
            }
            break;
        case TYPE_ROOK:
            if (color == COLOR_BLACK)
            {
                *texture = LoadTexture("assets/b_rook_1x_ns.png");
            }
            else if (color == COLOR_WHITE)
            {
                *texture = LoadTexture("assets/w_rook_1x_ns.png");
            }
            break;
        case TYPE_KNIGHT:
            if (color == COLOR_BLACK)
            {
                *texture = LoadTexture("assets/b_knight_1x_ns.png");
            }
            else if (color == COLOR_WHITE)
            {
                *texture = LoadTexture("assets/w_knight_1x_ns.png");
            }
            break;
        case TYPE_BISHOP:
            if (color == COLOR_BLACK)
            {
                *texture = LoadTexture("assets/b_bishop_1x_ns.png");
            }
            else if (color == COLOR_WHITE)
            {
                *texture = LoadTexture("assets/w_bishop_1x_ns.png");
            }
            break;
        case TYPE_PAWN:
            if (color == COLOR_BLACK)
            {
                *texture = LoadTexture("assets/b_pawn_1x_ns.png");
            }
            else if (color == COLOR_WHITE)
            {
                *texture = LoadTexture("assets/w_pawn_1x_ns.png");
            }
            break;
        default:
            fprintf(stderr, "texture not found\n");
            exit(EXIT_FAILURE);
            break;
    }
}

typedef struct Piece
{
    PieceType type;
    PieceColor color;
    Texture2D texture;
    Rectangle source_rect;
    Rectangle dest_rect;
    Vector2 origin;
    float rotation;
    Color tint;
    bool active;
    bool is_dragging;
    Vector2 offset;

} Piece;

void
piece_init(Piece* piece, PieceType type, PieceColor color, float x, float y, int padding)
{
    piece->type = type;
    piece->color = color;
    load_texture(&piece->texture, piece->type, piece->color);
    piece->source_rect = (Rectangle){ 0, 0, piece->texture.width, piece->texture.height };
    piece->dest_rect = (Rectangle){ x, y, SLOT_WIDTH - padding * 2, SLOT_HEIGHT - padding * 2 };
    piece->origin = (Vector2){ 0, 0 };
    piece->rotation = 0.0f;
    piece->tint = WHITE;
    piece->active = true;
    piece->is_dragging = false;
    piece->offset = (Vector2){ 0, 0 };
}

void
piece_draw(Piece* piece)
{
    DrawTexturePro(piece->texture,
                   piece->source_rect,
                   piece->dest_rect,
                   piece->origin,
                   piece->rotation,
                   piece->tint);
}

// PIECE LIST
void
pieces_init(Piece* pieces, int piece_padding)
{
    piece_init(&pieces[0],
               TYPE_ROOK,
               COLOR_BLACK,
               0 * SLOT_WIDTH + piece_padding,
               0 * SLOT_HEIGHT + piece_padding,
               piece_padding);
    piece_init(&pieces[1],
               TYPE_KNIGHT,
               COLOR_BLACK,
               1 * SLOT_WIDTH + piece_padding,
               0 * SLOT_HEIGHT + piece_padding,
               piece_padding);
    piece_init(&pieces[2],
               TYPE_BISHOP,
               COLOR_BLACK,
               2 * SLOT_WIDTH + piece_padding,
               0 * SLOT_HEIGHT + piece_padding,
               piece_padding);
    piece_init(&pieces[3],
               TYPE_QUEEN,
               COLOR_BLACK,
               3 * SLOT_WIDTH + piece_padding,
               0 * SLOT_HEIGHT + piece_padding,
               piece_padding);
    piece_init(&pieces[4],
               TYPE_KING,
               COLOR_BLACK,
               4 * SLOT_WIDTH + piece_padding,
               0 * SLOT_HEIGHT + piece_padding,
               piece_padding);
    piece_init(&pieces[5],
               TYPE_BISHOP,
               COLOR_BLACK,
               5 * SLOT_WIDTH + piece_padding,
               0 * SLOT_HEIGHT + piece_padding,
               piece_padding);
    piece_init(&pieces[6],
               TYPE_KNIGHT,
               COLOR_BLACK,
               6 * SLOT_WIDTH + piece_padding,
               0 * SLOT_HEIGHT + piece_padding,
               piece_padding);
    piece_init(&pieces[7],
               TYPE_ROOK,
               COLOR_BLACK,
               7 * SLOT_WIDTH + piece_padding,
               0 * SLOT_HEIGHT + piece_padding,
               piece_padding);

    for (int i = 8; i < 16; i++)
    {
        piece_init(&pieces[i],
                   TYPE_PAWN,
                   COLOR_BLACK,
                   (i - 8) * SLOT_WIDTH + piece_padding,
                   1 * SLOT_HEIGHT + piece_padding,
                   piece_padding);
    }

    piece_init(&pieces[16],
               TYPE_ROOK,
               COLOR_WHITE,
               0 * SLOT_WIDTH + piece_padding,
               7 * SLOT_HEIGHT + piece_padding,
               piece_padding);
    piece_init(&pieces[17],
               TYPE_KNIGHT,
               COLOR_WHITE,
               1 * SLOT_WIDTH + piece_padding,
               7 * SLOT_HEIGHT + piece_padding,
               piece_padding);
    piece_init(&pieces[18],
               TYPE_BISHOP,
               COLOR_WHITE,
               2 * SLOT_WIDTH + piece_padding,
               7 * SLOT_HEIGHT + piece_padding,
               piece_padding);
    piece_init(&pieces[19],
               TYPE_QUEEN,
               COLOR_WHITE,
               3 * SLOT_WIDTH + piece_padding,
               7 * SLOT_HEIGHT + piece_padding,
               piece_padding);
    piece_init(&pieces[20],
               TYPE_KING,
               COLOR_WHITE,
               4 * SLOT_WIDTH + piece_padding,
               7 * SLOT_HEIGHT + piece_padding,
               piece_padding);
    piece_init(&pieces[21],
               TYPE_BISHOP,
               COLOR_WHITE,
               5 * SLOT_WIDTH + piece_padding,
               7 * SLOT_HEIGHT + piece_padding,
               piece_padding);
    piece_init(&pieces[22],
               TYPE_KNIGHT,
               COLOR_WHITE,
               6 * SLOT_WIDTH + piece_padding,
               7 * SLOT_HEIGHT + piece_padding,
               piece_padding);
    piece_init(&pieces[23],
               TYPE_ROOK,
               COLOR_WHITE,
               7 * SLOT_WIDTH + piece_padding,
               7 * SLOT_HEIGHT + piece_padding,
               piece_padding);

    for (int i = 24; i < 32; i++)
    {
        piece_init(&pieces[i],
                   TYPE_PAWN,
                   COLOR_WHITE,
                   (i - 24) * SLOT_WIDTH + piece_padding,
                   6 * SLOT_HEIGHT + piece_padding,
                   piece_padding);
    }
}

void gen_current_board_fen(Piece * pieces, int pieces_count, int piece_padding)
{
    char * fen_string;
}

int
main(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE);
    SetTargetFPS(GAME_FPS);

    int pieces_count = 32;
    Piece pieces[pieces_count];
    int piece_padding = 20;

    pieces_init(pieces, piece_padding);

    while (!WindowShouldClose())
    {
        Vector2 mouse_pos = GetMousePosition();

        // drag and drop piece
        for (int i = 0; i < pieces_count; i++)
        {
            if (pieces[i].active)
            {
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) &&
                    CheckCollisionPointRec(mouse_pos, pieces[i].dest_rect) &&
                    !pieces[i].is_dragging)
                {
                    pieces[i].is_dragging = true;
                    pieces[i].offset.x = mouse_pos.x - pieces[i].dest_rect.x;
                    pieces[i].offset.y = mouse_pos.y - pieces[i].dest_rect.y;
                }

                if (pieces[i].is_dragging)
                {
                    pieces[i].dest_rect.x = mouse_pos.x - pieces[i].offset.x;
                    pieces[i].dest_rect.y = mouse_pos.y - pieces[i].offset.y;
                }

                if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
                {
                    pieces[i].is_dragging = false;

                    // snap piece to slot
                    for (int j = 0; j < ROWS; j++)
                    {
                        for (int k = 0; k < COLS; k++)
                        {
                            int x = k * SLOT_WIDTH;
                            int y = j * SLOT_HEIGHT;

                            if (CheckCollisionRecs(pieces[i].dest_rect,
                                                   (Rectangle){ x, y, SLOT_WIDTH, SLOT_HEIGHT }))
                            {
                                pieces[i].dest_rect.x = x + piece_padding;
                                pieces[i].dest_rect.y = y + piece_padding;
                            }
                        }
                    }
                }
            }
        }

        BeginDrawing();
        ClearBackground(SCREEN_BACKGROUND);

        draw_board();

        for (int i = 0; i < pieces_count; i++)
        {
            if (pieces[i].active)
            {
                piece_draw(&pieces[i]);
            }
        }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}