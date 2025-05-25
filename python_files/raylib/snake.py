import pyray as p
from enum import Enum
from collections import deque

from utility.center_and_draw_text import center_and_draw_text

SCREEN_WIDTH: int = 800
SCREEN_HEIGHT: int = 800
SCREEN_TITLE: str = "Snake"
SCREEN_BACKGROUND: p.Color = p.RAYWHITE
GAME_FPS: int = 60

ROWS: int = 20
COLS: int = 20
BLOCK_SIZE: int = 30
MARGIN: int = 100


def draw_grid() -> None:
    # outline rectangle
    p.draw_rectangle_lines_ex(
        p.Rectangle(
            MARGIN,
            MARGIN,
            p.get_screen_width() - MARGIN * 2,
            p.get_screen_height() - MARGIN * 2,
        ),
        5.0,
        p.BLACK,
    )

    # horizontal lines
    for x in range(MARGIN + BLOCK_SIZE, p.get_screen_width() - MARGIN, BLOCK_SIZE):
        p.draw_line_ex(
            p.Vector2(x, MARGIN),
            p.Vector2(x, p.get_screen_height() - MARGIN),
            2.0,
            p.BLACK,
        )
    # vertical lines
    for y in range(MARGIN + BLOCK_SIZE, p.get_screen_height() - MARGIN, BLOCK_SIZE):
        p.draw_line_ex(
            p.Vector2(MARGIN, y),
            p.Vector2(p.get_screen_width() - MARGIN, y),
            2.0,
            p.BLACK,
        )


class Direction(Enum):
    right = 1
    left = 2
    up = 3
    down = 4


class Snake:
    def __init__(self) -> None:
        self.x: int = MARGIN
        self.y: int = MARGIN
        self.direction: Direction = Direction.right

        self.list: deque[p.Rectangle] = deque(
            [p.Rectangle(self.x, self.y, BLOCK_SIZE, BLOCK_SIZE)]
        )

        self.last_time: float = p.get_time()
        self.move_interval: float = 0.08

    def draw(self) -> None:
        for i, segment in enumerate(self.list):
            color: p.Color = p.BLUE if i == 0 else p.SKYBLUE

            p.draw_rectangle_rec(segment, color)

    def handle_input(self) -> None:
        if (
            p.is_key_pressed(p.KeyboardKey.KEY_RIGHT)
            and self.direction != Direction.left
        ):
            self.direction = Direction.right
        if (
            p.is_key_pressed(p.KeyboardKey.KEY_LEFT)
            and self.direction != Direction.right
        ):
            self.direction = Direction.left
        if p.is_key_pressed(p.KeyboardKey.KEY_UP) and self.direction != Direction.down:
            self.direction = Direction.up
        if p.is_key_pressed(p.KeyboardKey.KEY_DOWN) and self.direction != Direction.up:
            self.direction = Direction.down

    def move(self) -> None:
        match self.direction:
            case Direction.right:
                self.x += BLOCK_SIZE
            case Direction.left:
                self.x -= BLOCK_SIZE
            case Direction.up:
                self.y -= BLOCK_SIZE
            case Direction.down:
                self.y += BLOCK_SIZE

    def collision_walls(self) -> bool:
        if self.x < MARGIN or self.x > p.get_screen_width() - MARGIN - BLOCK_SIZE:
            return True
        if self.y < MARGIN or self.y > p.get_screen_height() - MARGIN - BLOCK_SIZE:
            return True

        return False

    def collision_itself(self) -> bool:
        for i in range(1, len(self.list) - 1):
            if self.x == self.list[i].x and self.y == self.list[i].y:
                return True
        return False

    def update(self) -> bool:
        self.handle_input()

        current_time: float = p.get_time()
        if current_time - self.last_time >= self.move_interval:
            self.last_time = current_time

            self.move()

            self.list.appendleft(p.Rectangle(self.x, self.y, BLOCK_SIZE, BLOCK_SIZE))
            self.list.pop()

            if self.collision_walls() or self.collision_itself():
                return True

        return False


class Food:
    def __init__(self, snake: Snake) -> None:
        self.snake: Snake = snake
        self.color: p.Color = p.RED

        self.gen_position()

    def gen_position(self) -> None:
        while True:
            position_in_list: bool = False

            x: float = p.get_random_value(0, COLS - 1) * BLOCK_SIZE + MARGIN
            y: float = p.get_random_value(0, ROWS - 1) * BLOCK_SIZE + MARGIN

            for segment in self.snake.list:
                if segment.x == x and segment.y == y:
                    position_in_list = True
                    break

            if not position_in_list:
                self.rect: p.Rectangle = p.Rectangle(x, y, BLOCK_SIZE, BLOCK_SIZE)
                return

    def draw(self) -> None:
        p.draw_rectangle_rec(self.rect, self.color)


def main() -> None:
    p.init_window(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE)
    p.set_target_fps(GAME_FPS)

    score: int = 0
    game_over: bool = False
    show_text: bool = False
    last_time: float = p.get_time()
    blink_interval: float = 1.0

    snake: Snake = Snake()
    food: Food = Food(snake)

    while not p.window_should_close():
        if game_over:
            current_time: float = p.get_time()
            if current_time - last_time >= blink_interval:
                last_time = current_time
                show_text = not show_text

        if not game_over:
            game_over = snake.update()

            # snake head collision food
            if p.check_collision_recs(snake.list[0], food.rect):
                food.gen_position()
                snake.list.append(snake.list[-1])

        else:
            if p.is_key_pressed(p.KeyboardKey.KEY_ENTER):
                score = 0
                game_over = False

                snake = Snake()
                food = Food(snake)

        p.begin_drawing()
        p.clear_background(SCREEN_BACKGROUND)

        center_and_draw_text(f"Score: {score}", 30, 0, 0, p.get_screen_width(), 120)

        if not game_over:
            snake.draw()
            food.draw()
            draw_grid()

        if game_over:
            center_and_draw_text(
                "GAME OVER", 40, 0, 0, p.get_screen_width(), p.get_screen_height()
            )

            if show_text:
                center_and_draw_text(
                    "press ENTER to restart",
                    30,
                    0,
                    0,
                    p.get_screen_width(),
                    p.get_screen_height() + 300,
                )

        p.end_drawing()

    p.close_window()


if __name__ == "__main__":
    main()
