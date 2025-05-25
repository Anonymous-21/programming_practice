import pyray as p

from utility.center_and_draw_text import center_and_draw_text

SCREEN_WIDTH: int = 800
SCREEN_HEIGHT: int = 600
SCREEN_TITLE: str = "Pong"
SCREEN_BACKGROUND: p.Color = p.SKYBLUE


class Ball:
    def __init__(self) -> None:
        self.initial_x: float = p.get_screen_width() / 2
        self.initial_y: float = p.get_screen_height() / 2
        self.x: float = self.initial_x
        self.y: float = self.initial_y
        self.radius: float = 10.0
        self.speed: float = 400.0
        self.direction: p.Vector2 = p.Vector2(
            -1 if p.get_random_value(0, 1) == 0 else 1,
            -1 if p.get_random_value(0, 1) == 0 else 1,
        )
        self.color: p.Color = p.RED
        self.active: bool = False
        self.show_text: bool = False
        self.last_current_time: float = p.get_time()
        self.blink_interval: float = 1.0

    def reset(self) -> None:
        self.x = self.initial_x
        self.y = self.initial_y
        self.direction = p.Vector2(
            -1 if p.get_random_value(0, 1) == 0 else 1,
            -1 if p.get_random_value(0, 1) == 0 else 1,
        )
        self.active = False
        self.show_text = False

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

        p.draw_circle_v(p.Vector2(self.x, self.y), self.radius, self.color)

    def update(self) -> None:
        if not self.active:
            current_time: float = p.get_time()
            if current_time - self.last_current_time >= self.blink_interval:
                self.last_current_time = current_time
                self.show_text = not self.show_text

        if p.is_key_pressed(p.KeyboardKey.KEY_SPACE):
            self.active = not self.active
            self.show_text = False

        if self.active:
            self.x += self.direction.x * self.speed * p.get_frame_time()
            self.y += self.direction.y * self.speed * p.get_frame_time()

        if self.direction.x != 0 and self.direction.y != 0:
            self.direction = p.vector2_normalize(self.direction)

        if self.y < self.radius or self.y > p.get_screen_height() - self.radius:
            self.direction.y *= -1


class Paddle:
    def __init__(self, x: float) -> None:
        self.width: float = 10.0
        self.height: float = 100.0
        self.initial_x: float = x
        self.initial_y: float = p.get_screen_height() / 2 - self.height / 2
        self.x: float = self.initial_x
        self.y: float = self.initial_y
        self.speed: float = 300.0
        self.color: p.Color = p.BLACK

    def reset(self) -> None:
        self.x = self.initial_x
        self.y = self.initial_y

    def draw(self) -> None:
        p.draw_rectangle_rec(
            p.Rectangle(self.x, self.y, self.width, self.height), self.color
        )

    def update_player(self) -> None:
        if p.is_key_down(p.KeyboardKey.KEY_UP) and self.y > 0:
            self.y -= self.speed * p.get_frame_time()
        if (
            p.is_key_down(p.KeyboardKey.KEY_DOWN)
            and self.y < p.get_screen_height() - self.height
        ):
            self.y += self.speed * p.get_frame_time()

    def update_ai(self, ball_y: float) -> None:
        if ball_y < self.y + self.height / 2 and self.y > 0:
            self.y -= self.speed * p.get_frame_time()
        if (
            ball_y > self.y + self.height / 2
            and self.y < p.get_screen_height() - self.height
        ):
            self.y += self.speed * p.get_frame_time()


def game_reset(ball: Ball, player: Paddle, ai: Paddle) -> None:
    ball.reset()
    player.reset()
    ai.reset()


def main() -> None:
    p.init_window(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE)

    score_left: int = 0
    score_right: int = 0

    ball: Ball = Ball()
    player: Paddle = Paddle(10.0)
    ai: Paddle = Paddle(p.get_screen_width() - player.width - 10.0)

    while not p.window_should_close():
        ball.update()
        player.update_player()
        ai.update_ai(ball.y)

        # ball collision paddles
        if p.check_collision_circle_rec(
            p.Vector2(ball.x, ball.y),
            ball.radius,
            p.Rectangle(player.x, player.y, player.width, player.height),
        ):
            ball.direction.x *= -1
        if p.check_collision_circle_rec(
            p.Vector2(ball.x, ball.y),
            ball.radius,
            p.Rectangle(ai.x, ai.y, ai.width, ai.height),
        ):
            ball.direction.x *= -1

        # update scores
        if ball.x < ball.radius:
            score_right += 1
            game_reset(ball, player, ai)
        if ball.x > p.get_screen_width() - ball.radius:
            score_left += 1
            game_reset(ball, player, ai)

        p.begin_drawing()
        p.clear_background(SCREEN_BACKGROUND)

        p.draw_text(str(score_left), 200, 30, 40, p.BLACK)
        p.draw_text(str(score_right), p.get_screen_width() - 200, 30, 40, p.BLACK)

        ball.draw()
        player.draw()
        ai.draw()

        p.end_drawing()

    p.close_window()


if __name__ == "__main__":
    main()
