import pyray as p
from math import cos, sin, radians

SCREEN_WIDTH: int = 800
SCREEN_HEIGHT: int = 600
SCREEN_TITLE: str = "Radar Sweep"
SCREEN_BACKGROUND: p.Color = p.SKYBLUE


class Ring:
    def __init__(self) -> None:
        self.center: p.Vector2 = p.Vector2(
            p.get_screen_width() / 2, p.get_screen_height() / 2
        )
        self.inner_radius: float = 250.0
        self.outer_radius: float = 260.0
        self.start_angle: float = 0.0
        self.end_angle: float = 360.0
        self.segments: int = 64
        self.color: p.Color = p.BLACK

    def draw(self) -> None:
        p.draw_ring(
            self.center,
            self.inner_radius,
            self.outer_radius,
            self.start_angle,
            self.end_angle,
            self.segments,
            self.color,
        )


class Line:
    def __init__(self, ring_center: p.Vector2) -> None:
        self.start_pos: p.Vector2 = ring_center
        self.end_pos: p.Vector2 = p.Vector2(0, 0)
        self.thickness: float = 10.0
        self.color: p.Color = p.RED

    def draw(self) -> None:
        p.draw_line_ex(self.start_pos, self.end_pos, self.thickness, self.color)


def main() -> None:
    p.init_window(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE)

    ring: Ring = Ring()
    line: Line = Line(ring.center)

    angle: float = 0.0
    speed: float = 20.0

    while not p.window_should_close():
        angle += speed * p.get_frame_time()
        if angle >= 360.0:
            angle = 0.0

        angle_radians: float = radians(angle)

        line.end_pos.x = cos(angle_radians) * ring.inner_radius + ring.center.x
        line.end_pos.y = sin(angle_radians) * ring.inner_radius + ring.center.y

        p.begin_drawing()
        p.clear_background(SCREEN_BACKGROUND)

        ring.draw()
        line.draw()

        p.end_drawing()

    p.close_window()


if __name__ == "__main__":
    main()
