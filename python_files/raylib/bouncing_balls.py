import pyray as p

SCREEN_WIDTH: int = 800
SCREEN_HEIGHT: int = 600
SCREEN_TITLE: str = "Bouncing Balls"
SCREEN_BACKGROUND: p.Color = p.RAYWHITE

NUM_OF_BALLS: int = 200


class Ball:
    def __init__(self) -> None:
        self.radius: float = p.get_random_value(10, 30)
        self.x: float = p.get_random_value(
            self.radius, p.get_screen_width() - self.radius
        )
        self.y: float = p.get_random_value(
            self.radius, p.get_screen_height() - self.radius
        )
        self.speed: float = p.get_random_value(100, 300)
        self.color: p.Color = p.Color(
            p.get_random_value(0, 255),
            p.get_random_value(0, 255),
            p.get_random_value(0, 255),
            255,
        )
        self.direction: p.Vector2 = p.Vector2(
            -1 if p.get_random_value(0, 1) == 0 else 1,
            -1 if p.get_random_value(0, 1) == 0 else 1,
        )

    def draw(self) -> None:
        p.draw_circle_v(p.Vector2(self.x, self.y), self.radius, self.color)

    def update(self) -> None:
        # move ball
        self.x += self.direction.x * self.speed * p.get_frame_time()
        self.y += self.direction.y * self.speed * p.get_frame_time()

        # normalize direction vector
        if self.direction.x != 0 and self.direction.y != 0:
            self.direction = p.vector2_normalize(self.direction)

        # ball bounds
        if self.x < self.radius or self.x > p.get_screen_width() - self.radius:
            self.direction.x *= -1
        if self.y < self.radius or self.y > p.get_screen_height() - self.radius:
            self.direction.y *= -1


def main() -> None:
    p.init_window(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE)

    balls: list[Ball] = []

    for i in range(NUM_OF_BALLS):
        balls.append(Ball())

    while not p.window_should_close():
        for ball in balls:
            ball.update()

        p.begin_drawing()
        p.clear_background(SCREEN_BACKGROUND)

        for ball in balls:
            ball.draw()

        p.end_drawing()

    p.close_window()


if __name__ == "__main__":
    main()
