import pyray as p
from random import uniform

SCREEN_WIDTH: int = 800
SCREEN_HEIGHT: int = 600
SCREEN_TITLE: str = "FALLING SNOW"
SCREEN_BACKGROUND: p.Color = p.BLACK

NUM_OF_SNOWFLAKES: int = 400


class Snowflake:
    def __init__(self) -> None:
        self.radius: float = uniform(1, 5)
        self.pos: p.Vector2 = p.Vector2(
            uniform(self.radius, p.get_screen_width() - self.radius),
            uniform(-p.get_screen_height(), 0),
        )
        self.color: p.Color = p.LIGHTGRAY
        self.fall_speed: float = 0
        self.drift_speed: float = 0
        self.drift_angle: float = 0
        self.drift_amplitude: float = 0
        self.drift_frequency: float = 0

    def draw(self) -> None:
        p.draw_circle_v(self.pos, self.radius, self.color)

    def update(self) -> None:
        pass


def main() -> None:
    p.init_window(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE)

    while not p.window_should_close():
        p.begin_drawing()
        p.clear_background(SCREEN_BACKGROUND)
        p.end_drawing()

    p.close_window()


if __name__ == "__main__":
    main()
