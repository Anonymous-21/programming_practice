import pyray as p
from tower import Tower

SCREEN_WIDTH: int = 1000
SCREEN_HEIGHT: int = 800
SCREEN_TITLE: str = "Idle Tower"
SCREEN_BACKGROUND: p.Color = p.LIGHTGRAY

def main() -> None:
    p.init_window(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE)

    tower: Tower = Tower()

    while not p.window_should_close():
        p.begin_drawing()
        p.clear_background(SCREEN_BACKGROUND)

        tower.draw()

        p.end_drawing()

    p.close_window()

if __name__ == "__main__":
    main()