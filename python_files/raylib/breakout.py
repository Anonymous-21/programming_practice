import pyray as p
from random import choice

from center_and_draw_texts import center_and_draw_text

SCREEN_WIDTH: int = 1000
SCREEN_HEIGHT: int = 800
SCREEN_TITLE: str = "BREAKOUT"
SCREEN_BACKGROUND: p.Color = p.RAYWHITE

ROWS: int = 5
COLS: int = 10
BRICK_WIDTH: int = SCREEN_WIDTH // COLS
BRICK_HEIGHT: int = 40
BRICK_GAP: int = 2


class Brick:
    def __init__(self, x: int, y: int) -> None:
        self.rect: p.Rectangle = p.Rectangle(x, y, BRICK_WIDTH, BRICK_HEIGHT)
        self.color: p.Color = p.GRAY
        self.active: bool = True

    def draw(self) -> None:
        p.draw_rectangle_rec(self.rect, self.color)


class Paddle:
    def __init__(self) -> None:
        height: float = 15.0
        width: float = 100.0
        self.initial_x: float = p.get_screen_width() / 2 - width / 2
        self.rect: p.Rectangle = p.Rectangle(
            self.initial_x, p.get_screen_height() - height * 2, width, height
        )
        self.speed: float = 300.0
        self.color: p.Color = p.BLACK

    def reset(self) -> None:
        self.rect.x = self.initial_x

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
            self.paddle.rect.y - self.radius * 2,
        )
        self.initial_speed: float = 400.0
        self.speed: float = self.initial_speed
        self.speed_increment: float = 10.0
        self.direction: p.Vector2 = choice([p.Vector2(-1, -1), p.Vector2(1, -1)])
        self.color: p.Color = p.RED
        self.active: bool = False

    def reset(self) -> None:
        self.pos = p.Vector2(
            self.paddle.rect.x + self.paddle.rect.width / 2,
            self.paddle.rect.y - self.radius * 2,
        )
        self.direction = choice([p.Vector2(-1, -1), p.Vector2(1, -1)])
        self.speed = self.initial_speed
        self.active = False

    def draw(self) -> None:
        p.draw_circle_v(self.pos, self.radius, self.color)

    def update(self) -> None:
        # update ball position when not active
        if not self.active:
            self.pos = p.Vector2(
                self.paddle.rect.x + self.paddle.rect.width / 2,
                self.paddle.rect.y - self.radius * 2,
            )

        # activate/deactivate ball
        if p.is_key_pressed(p.KeyboardKey.KEY_SPACE):
            self.active = True

        # move ball
        if self.active:
            self.pos.x += self.direction.x * self.speed * p.get_frame_time()
            self.pos.y += self.direction.y * self.speed * p.get_frame_time()

        # normalize direction vector
        if self.direction.x != 0 and self.direction.y != 0:
            self.direction = p.vector2_normalize(self.direction)

        # ball bounds
        if (
            self.pos.x - self.radius < 0
            or self.pos.x + self.radius > p.get_screen_width()
        ):
            self.direction.x *= -1
        if self.pos.y - self.radius < 0:
            self.direction.y *= -1


def main() -> None:
    p.init_window(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE)

    lives: int = 5
    game_over: bool = False
    game_won: bool = False

    bricks: list[Brick] = []
    for i in range(ROWS):
        for j in range(COLS):
            x: int = j * (BRICK_WIDTH + BRICK_GAP)
            y: int = i * (BRICK_HEIGHT + BRICK_GAP)

            bricks.append(Brick(x, y))

    paddle: Paddle = Paddle()
    ball: Ball = Ball(paddle)

    while not p.window_should_close():
        # game over condition
        if lives <= 0:
            game_over = True

        # game win condition
        all_bricks_inactive: bool = True
        for brick in bricks:
            if brick.active:
                all_bricks_inactive = False
                break

        if all_bricks_inactive:
            game_won = True

        # game running
        if not game_over and not game_won:
            paddle.update()
            ball.update()

            # ball collision paddle
            if p.check_collision_circle_rec(ball.pos, ball.radius, paddle.rect):
                ball.direction.y *= -1
                ball.speed += ball.speed_increment

            # update lives
            if ball.pos.y - ball.radius > p.get_screen_height():
                lives -= 1
                paddle.reset()
                ball.reset()

            # ball collision bricks
            for brick in bricks:
                if (
                    p.check_collision_circle_rec(
                        ball.pos,
                        ball.radius,
                        brick.rect,
                    )
                    and brick.active
                ):
                    brick.active = False
                    ball.direction.y *= -1

        else:
            if p.is_key_pressed(p.KeyboardKey.KEY_ENTER):
                lives = 5
                game_over = False
                game_won = False

                for brick in bricks:
                    brick.active = True
                paddle = Paddle()
                ball = Ball(paddle)

        p.begin_drawing()
        p.clear_background(SCREEN_BACKGROUND)

        # draw lives
        p.draw_text(str(lives), 20, p.get_screen_height() - 50, 40, p.GRAY)

        paddle.draw()
        ball.draw()

        for brick in bricks:
            if brick.active:
                brick.draw()

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
        if game_won:
            center_and_draw_text(
                "YOU WIN",
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
