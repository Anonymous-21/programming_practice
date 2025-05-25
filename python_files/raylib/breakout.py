import pyray as p

from utility.center_and_draw_text import center_and_draw_text

SCREEN_WIDTH: int = 800
SCREEN_HEIGHT: int = 600
SCREEN_TITLE: str = "Breakout"
SCREEN_BACKGROUND: p.Color = p.RAYWHITE

ROWS: int = 5
COLS: int = 10
BRICK_WIDTH: int = 79
BRICK_HEIGHT: int = 30
BRICK_GAP: int = 2


class Bricks:
    def __init__(self) -> None:
        self.list: list[p.Rectangle] = []

        for i in range(ROWS):
            for j in range(COLS):
                x: float = j * (BRICK_WIDTH + BRICK_GAP)
                y: float = i * (BRICK_HEIGHT + BRICK_GAP)

                self.list.append(p.Rectangle(x, y, BRICK_WIDTH, BRICK_HEIGHT))

        self.color: p.Color = p.GRAY

    def draw(self) -> None:
        for brick in self.list:
            p.draw_rectangle_rec(brick, self.color)


class Paddle:
    def __init__(self) -> None:
        width: float = 100.0
        height: float = 10.0
        self.rect: p.Rectangle = p.Rectangle(
            p.get_screen_width() / 2 - width / 2,
            p.get_screen_height() - height - 10.0,
            width,
            height,
        )
        self.speed: float = 300.0
        self.color: p.Color = p.BLACK

    def reset(self) -> None:
        self.__init__()

    def draw(self) -> None:
        p.draw_rectangle_rec(self.rect, self.color)

    def update(self) -> None:
        if p.is_key_down(p.KeyboardKey.KEY_LEFT) and self.rect.x > 0:
            self.rect.x -= self.speed * p.get_frame_time()
        if (
            p.is_key_down(p.KeyboardKey.KEY_RIGHT)
            and self.rect.x < p.get_screen_width() - self.rect.width
        ):
            self.rect.x += self.speed * p.get_frame_time()


class Ball:
    def __init__(self, paddle: Paddle) -> None:
        self.paddle: Paddle = paddle
        self.radius: float = 10.0
        self.pos: p.Vector2 = p.Vector2(
            self.paddle.rect.x + self.paddle.rect.width / 2,
            self.paddle.rect.y - self.radius,
        )
        self.speed: float = 400.0
        self.direction: p.Vector2 = p.Vector2(
            -1 if p.get_random_value(0, 1) == 0 else 1,
            -1 if p.get_random_value(0, 1) == 0 else 1,
        )
        self.color: p.Color = p.RED
        self.active: bool = False
        self.show_text: bool = False
        self.last_time: float = p.get_time()
        self.blink_interval: float = 1.0

    def reset(self) -> None:
        self.__init__(self.paddle)

    def draw(self) -> None:
        if self.show_text:
            center_and_draw_text(
                "press SPACE to begin",
                30,
                0,
                0,
                p.get_screen_width(),
                p.get_screen_height() + 300,
            )

        p.draw_circle_v(self.pos, self.radius, self.color)

    def update(self) -> None:
        # show blinking text
        if not self.active:
            # update ball position
            self.pos: p.Vector2 = p.Vector2(
                self.paddle.rect.x + self.paddle.rect.width / 2,
                self.paddle.rect.y - self.radius,
            )

            current_time: float = p.get_time()
            if current_time - self.last_time >= self.blink_interval:
                self.last_time = current_time
                self.show_text = not self.show_text

        # activate ball
        if p.is_key_pressed(p.KeyboardKey.KEY_SPACE):
            self.active = not self.active
            self.show_text = False

        # move ball
        if self.active:
            self.pos.x += self.direction.x * self.speed * p.get_frame_time()
            self.pos.y += self.direction.y * self.speed * p.get_frame_time()

        # normalize direction vector
        if self.direction.x != 0 and self.direction.y != 0:
            self.direction = p.vector2_normalize(self.direction)

        # ball bounds
        if self.pos.x < self.radius or self.pos.x > p.get_screen_width() - self.radius:
            self.direction.x *= -1
        if self.pos.y < self.radius:
            self.direction.y *= -1


def main() -> None:
    p.init_window(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE)

    lives: int = 5
    game_over: bool = False
    game_won: bool = False
    show_text: bool = False
    last_time: float = p.get_time()
    blink_interval: float = 1.0

    bricks: Bricks = Bricks()
    paddle: Paddle = Paddle()
    ball: Ball = Ball(paddle)

    while not p.window_should_close():
        if game_over or game_won:
            current_time: float = p.get_time()
            if current_time - last_time >= blink_interval:
                show_text = not show_text
                last_time = current_time

        if lives <= 0:
            game_over = True

        if len(bricks.list) <= 0:
            game_won = True

        if not game_over and not game_won:
            paddle.update()
            ball.update()

            # ball collision paddle
            if p.check_collision_circle_rec(ball.pos, ball.radius, paddle.rect):
                ball.direction.y *= -1

            # update lives
            if ball.pos.y > p.get_screen_height() - ball.radius:
                lives -= 1
                ball.reset()
                paddle.reset()

            # ball collision bricks
            for brick in bricks.list[:]:
                if p.check_collision_circle_rec(ball.pos, ball.radius, brick):
                    ball.direction.y *= -1
                    bricks.list.remove(brick)

        else:
            if p.is_key_pressed(p.KeyboardKey.KEY_ENTER):
                lives = 5
                game_over = False
                game_won = False

                bricks = Bricks()
                paddle = Paddle()
                ball = Ball(paddle)

        p.begin_drawing()
        p.clear_background(SCREEN_BACKGROUND)

        if not game_over and not game_won:
            p.draw_text(str(lives), 20, p.get_screen_height() - 50, 40, p.BLACK)

            bricks.draw()
            paddle.draw()
            ball.draw()
        elif game_over:
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
        elif game_won:
            center_and_draw_text(
                "YOU WIN", 40, 0, 0, p.get_screen_width(), p.get_screen_height()
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
