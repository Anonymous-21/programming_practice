import pyray as p

SCREEN_WIDTH: int = 1000
SCREEN_HEIGHT: int = 800
SCREEN_TITLE: str = "PONG"
SCREEN_BACKGROUND: p.Color = p.LIGHTGRAY


class Ball:
    def __init__(self) -> None:
        self.initial_x: float = p.get_screen_width() / 2
        self.initial_y: float = p.get_screen_height() / 2
        self.pos: p.Vector2 = p.Vector2(self.initial_x, self.initial_y)
        self.radius: float = 10.0
        self.initial_speed: float = 400.0
        self.speed: float = self.initial_speed
        self.speed_increment: float = 10.0
        self.direction: p.Vector2 = p.Vector2(
            -1 if p.get_random_value(0, 1) == 0 else -1,
            -1 if p.get_random_value(0, 1) == 0 else -1,
        )
        self.color: p.Color = p.RED
        self.active: bool = False

    def reset(self) -> None:
        self.pos = p.Vector2(self.initial_x, self.initial_y)
        self.direction = p.Vector2(
            -1 if p.get_random_value(0, 1) == 0 else -1,
            -1 if p.get_random_value(0, 1) == 0 else -1,
        )
        self.active = False
        self.speed = self.initial_speed

    def draw(self) -> None:
        p.draw_circle_v(self.pos, self.radius, self.color)

    def update(self) -> None:
        # activate/deactivate ball
        if p.is_key_pressed(p.KeyboardKey.KEY_SPACE):
            self.active = not self.active

        # move ball
        if self.active:
            self.pos.x += self.direction.x * self.speed * p.get_frame_time()
            self.pos.y += self.direction.y * self.speed * p.get_frame_time()

        # normalize direction vector
        if self.direction.x != 0 and self.direction.y != 0:
            self.direction = p.vector2_normalize(self.direction)

        # ball bounds
        if (
            self.pos.y - self.radius < 0
            or self.pos.y + self.radius > p.get_screen_height()
        ):
            self.direction.y *= -1


class Paddle:
    def __init__(self, x: float) -> None:
        height: float = 100.0
        self.initial_y: float = p.get_screen_height() / 2 - height / 2
        self.rect: p.Rectangle = p.Rectangle(x, self.initial_y, 10.0, height)
        self.speed: float = 300.0
        self.color: p.Color = p.BLACK

    def reset(self) -> None:
        self.rect.y = self.initial_y

    def draw(self) -> None:
        p.draw_rectangle_rec(self.rect, self.color)

    def update_player(self) -> None:
        if p.is_key_down(p.KeyboardKey.KEY_UP) and self.rect.y > 0:
            self.rect.y -= self.speed * p.get_frame_time()
        if (
            p.is_key_down(p.KeyboardKey.KEY_DOWN)
            and self.rect.y < p.get_screen_height() - self.rect.height
        ):
            self.rect.y += self.speed * p.get_frame_time()

    def update_ai(self, ball: Ball) -> None:
        if ball.pos.y < self.rect.y + self.rect.height / 2 and self.rect.y > 0:
            self.rect.y -= self.speed * p.get_frame_time()
        if (
            ball.pos.y > self.rect.y + self.rect.height / 2
            and self.rect.y < p.get_screen_height() - self.rect.height
        ):
            self.rect.y += self.speed * p.get_frame_time()


def main() -> None:
    p.init_window(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE)

    score_left: int = 0
    score_right: int = 0

    ball: Ball = Ball()
    player: Paddle = Paddle(10.0)
    ai: Paddle = Paddle(p.get_screen_width() - player.rect.width - 10.0)

    while not p.window_should_close():
        ball.update()
        player.update_player()
        ai.update_ai(ball)

        # ball collision paddles
        if p.check_collision_circle_rec(ball.pos, ball.radius, player.rect):
            ball.direction.x *= -1
            ball.speed += ball.speed_increment
        if p.check_collision_circle_rec(ball.pos, ball.radius, ai.rect):
            ball.direction.x *= -1
            ball.speed += ball.speed_increment

        # update scores
        if ball.pos.x + ball.radius < 0:
            score_right += 1
            ball.reset()
            player.reset()
            ai.reset()
        if ball.pos.x - ball.radius > p.get_screen_width():
            score_left += 1
            ball.reset()
            player.reset()
            ai.reset()

        p.begin_drawing()
        p.clear_background(SCREEN_BACKGROUND)

        # draw screen divider
        p.draw_line_ex(
            p.Vector2(p.get_screen_width() / 2, 0),
            p.Vector2(p.get_screen_width() / 2, p.get_screen_height()),
            5.0,
            p.GRAY,
        )

        # draw scores
        p.draw_text(str(score_left), 250, 30, 40, p.BLACK)
        p.draw_text(str(score_right), p.get_screen_width() - 250, 30, 40, p.BLACK)

        ball.draw()
        player.draw()
        ai.draw()

        p.end_drawing()

    p.close_window()


if __name__ == "__main__":
    main()
