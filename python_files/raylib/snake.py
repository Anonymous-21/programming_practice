import pyray as p
from enum import Enum

from center_and_draw_texts import center_and_draw_text

SCREEN_WIDTH: int = 1000
SCREEN_HEIGHT: int = 1000
SCREEN_TITLE: str = "SNAKE"
SCREEN_BACKGROUND: p.Color = p.RAYWHITE
GAME_FPS: int = 60

BLOCK_SIZE: int = 40
MARGIN: int = 100
ROWS: int = (SCREEN_WIDTH - MARGIN * 2) // BLOCK_SIZE
COLS: int = (SCREEN_HEIGHT - MARGIN * 2) // BLOCK_SIZE


def draw_grid() -> None:
    for x in range(MARGIN + BLOCK_SIZE, p.get_screen_width() - MARGIN, BLOCK_SIZE):
        p.draw_line_ex(
            p.Vector2(x, MARGIN),
            p.Vector2(x, p.get_screen_height() - MARGIN),
            2.0,
            p.GRAY,
        )
    for y in range(MARGIN + BLOCK_SIZE, p.get_screen_height() - MARGIN, BLOCK_SIZE):
        p.draw_line_ex(
            p.Vector2(MARGIN, y),
            p.Vector2(p.get_screen_width() - MARGIN, y),
            2.0,
            p.GRAY,
        )

    # draw outline rect
    p.draw_rectangle_lines_ex(
        p.Rectangle(
            MARGIN,
            MARGIN,
            p.get_screen_width() - MARGIN * 2,
            p.get_screen_height() - MARGIN * 2,
        ),
        5.0,
        p.GRAY,
    )


class Direction(Enum):
    RIGHT = 1
    LEFT = 2
    UP = 3
    DOWN = 4


class Snake:
    def __init__(self) -> None:
        self.x: int = MARGIN
        self.y: int = MARGIN
        self.direction: Direction = Direction.RIGHT
        self.list: list[p.Vector2] = [p.Vector2(self.x, self.y)]

        self.last_time: float = p.get_time()
        self.move_interval: float = 0.07

    def draw(self) -> None:
        for segment in self.list:
            color: p.Color = p.BLUE if self.list.index(segment) == 0 else p.SKYBLUE

            p.draw_rectangle_rec(
                p.Rectangle(segment.x, segment.y, BLOCK_SIZE, BLOCK_SIZE), color
            )

    def handle_direction_input(self) -> None:
        if (
            p.is_key_pressed(p.KeyboardKey.KEY_LEFT)
            and self.direction != Direction.RIGHT
        ):
            self.direction = Direction.LEFT
        if (
            p.is_key_pressed(p.KeyboardKey.KEY_RIGHT)
            and self.direction != Direction.LEFT
        ):
            self.direction = Direction.RIGHT
        if p.is_key_pressed(p.KeyboardKey.KEY_UP) and self.direction != Direction.DOWN:
            self.direction = Direction.UP
        if p.is_key_pressed(p.KeyboardKey.KEY_DOWN) and self.direction != Direction.UP:
            self.direction = Direction.DOWN

    def move(self) -> None:
        match self.direction:
            case Direction.RIGHT:
                self.x += BLOCK_SIZE
            case Direction.LEFT:
                self.x -= BLOCK_SIZE
            case Direction.DOWN:
                self.y += BLOCK_SIZE
            case Direction.UP:
                self.y -= BLOCK_SIZE

    def collision_walls(self) -> bool:
        return (
            self.x < MARGIN
            or self.x + BLOCK_SIZE + MARGIN > p.get_screen_width()
            or self.y < MARGIN
            or self.y + BLOCK_SIZE + MARGIN > p.get_screen_height()
        )

    def collision_itself(self) -> bool:
        for segment in self.list:
            if segment.x == self.x and segment.y == self.y:
                return True
        return False

    def update(self) -> bool:
        self.handle_direction_input()

        current_time: float = p.get_time()
        if current_time - self.last_time >= self.move_interval:
            self.last_time = current_time

            self.move()
            if self.collision_itself():
                return True
            if self.collision_walls():
                return True

            self.list.insert(0, p.Vector2(self.x, self.y))
            self.list.pop()

        return False


class Food:
    def __init__(self, snake: Snake) -> None:
        self.snake: Snake = snake
        self.color: p.Color = p.RED

        self.gen_random_food()

    def gen_random_food(self) -> None:
        while True:
            coordinate_in_list: bool = False

            x: int = p.get_random_value(0, COLS - 1) * BLOCK_SIZE + MARGIN
            y: int = p.get_random_value(0, ROWS - 1) * BLOCK_SIZE + MARGIN

            for segment in self.snake.list:
                if segment.x == x and segment.y == y:
                    coordinate_in_list = True
                    break

            if not coordinate_in_list:
                self.x: int = x
                self.y: int = y
                break

    def draw(self) -> None:
        p.draw_rectangle(self.x, self.y, BLOCK_SIZE, BLOCK_SIZE, self.color)


def main() -> None:
    p.init_window(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE)
    p.set_target_fps(GAME_FPS)

    score: int = 0
    game_over: bool = False

    snake: Snake = Snake()
    food: Food = Food(snake)

    while not p.window_should_close():
        if not game_over:
            game_over = snake.update()

            # snake collision food
            if p.check_collision_recs(
                p.Rectangle(snake.list[0].x, snake.list[0].y, BLOCK_SIZE, BLOCK_SIZE),
                p.Rectangle(food.x, food.y, BLOCK_SIZE, BLOCK_SIZE),
            ):
                food.gen_random_food()
                snake.list.append(snake.list[-1])
                score += 1

        else:
            if p.is_key_pressed(p.KeyboardKey.KEY_ENTER):
                score = 0
                game_over = False

                snake = Snake()
                food = Food(snake)

        p.begin_drawing()
        p.clear_background(SCREEN_BACKGROUND)

        # draw score
        center_and_draw_text(
            f"Score: {score}", 40, p.Rectangle(0, 0, p.get_screen_width(), 100), p.GRAY
        )

        if not game_over:
            snake.draw()
            food.draw()
            draw_grid()

        if game_over:
            center_and_draw_text(
                "GAME OVER",
                40,
                p.Rectangle(0, 0, p.get_screen_width(), p.get_screen_height()),
            )
            center_and_draw_text(
                "press ENTER to restart",
                30,
                p.Rectangle(0, 0, p.get_screen_width(), p.get_screen_height() + 100),
            )

        p.end_drawing()

    p.close_window()


if __name__ == "__main__":
    main()
