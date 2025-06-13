import pyray as p

SCREEN_WIDTH: int = 800
SCREEN_HEIGHT: int = 600
SCREEN_TITLE: str = "FALLING SNOW"
SCREEN_BACKGROUND: p.Color = p.BLACK


class Snowflake:
    def __init__(self) -> None:
        self.rect: p.Rectangle = p.Rectangle()


def main() -> None:
    p.init_window(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE)

    while not p.window_should_close():
        p.begin_drawing()
        p.clear_background(SCREEN_BACKGROUND)
        p.end_drawing()

    p.close_window()


if __name__ == "__main__":
    main()
