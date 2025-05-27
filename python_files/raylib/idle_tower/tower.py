import pyray as p


class Tower:
    def __init__(self) -> None:
        self.pos: p.Vector2 = p.Vector2(
            p.get_screen_width() / 2, p.get_screen_height() / 2
        )
        self.radius: float = 50.0
        self.color: p.Color = p.RED

        self.health: float = 10.0

    def is_alive(self) -> bool:
        return self.health >= 0

    def draw(self) -> None:
        p.draw_circle_v(self.pos, self.radius, self.color)

    def update(self) -> None:
        pass