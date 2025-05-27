import pyray as p
from random import uniform
from math import pi, sin

SCREEN_WIDTH: int = 800
SCREEN_HEIGHT: int = 600
SCREEN_TITLE: str = "Falling Snow"
SCREEN_BACKGROUND: p.Color = p.BLACK

NUM_OF_SNOWFLAKES: int = 200


class Snowflake:
    def __init__(self) -> None:
        self.radius: float = uniform(1, 4)
        x: float = uniform(self.radius, p.get_screen_width() - self.radius)
        y: float = uniform(-p.get_screen_height(), -self.radius)
        self.position: p.Vector2 = p.Vector2(x, y)
        self.color: p.Color = p.LIGHTGRAY
        self.fall_speed: float = uniform(12, 60)
        self.drift_speed: float = uniform(0.05, 0.3)
        self.drift_amplitude: float = uniform(10, 50)
        self.drift_frequency: float = uniform(0.1, 0.5)
        self.drift_angle: float = uniform(0, pi * 2)

    def draw(self) -> None:
        p.draw_circle_v(self.position, self.radius, self.color)

    def update(self) -> None:
        time: float = p.get_time()

        self.position.y += self.fall_speed * p.get_frame_time()

        self.position.x += (
            sin(time * self.drift_frequency + self.drift_angle)
            * self.drift_amplitude
            * self.drift_speed
            * p.get_frame_time()
        )

        if self.position.y > p.get_screen_height() + self.radius:
            self.__init__()

def main() -> None:
    p.init_window(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE)

    snowflakes: list[Snowflake] = []

    for i in range(NUM_OF_SNOWFLAKES):
        snowflakes.append(Snowflake())

    while not p.window_should_close():

        for snowflake in snowflakes:
            snowflake.update()

        p.begin_drawing()
        p.clear_background(SCREEN_BACKGROUND)

        for snowflake in snowflakes:
            snowflake.draw()

        p.end_drawing()

    p.close_window()


if __name__ == "__main__":
    main()
