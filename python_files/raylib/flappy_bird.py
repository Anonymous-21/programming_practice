import pyray as p
from random import uniform

from center_and_draw_texts import center_and_draw_text

SCREEN_WIDTH: int = 800
SCREEN_HEIGHT: int = 600
SCREEN_TITLE: str = "FLAPPY BIRD"
SCREEN_BACKGROUND: p.Color = p.LIGHTGRAY


class Player:
    def __init__(self) -> None:
        self.rect: p.Rectangle = p.Rectangle(200, 200, 30, 30)
        self.color: p.Color = p.BLUE
        self.jump_force: float = -500
        self.gravity: float = 1500
        self.change_y: float = 0.0

        self.active: bool = False

    def draw(self) -> None:
        p.draw_rectangle_rec(self.rect, self.color)

    def update(self) -> None:
        if p.is_key_pressed(p.KeyboardKey.KEY_UP):
            self.change_y = self.jump_force
            self.active = True

        if self.active:
            self.change_y += self.gravity * p.get_frame_time()
            self.rect.y += self.change_y * p.get_frame_time()

        self.rect.y = max(
            0.0, min(self.rect.y, p.get_screen_height() - self.rect.height)
        )


class Pillar:
    def __init__(self, vertical_gap: float, speed: float) -> None:
        self.vertical_gap: float = vertical_gap
        height: float = uniform(0, p.get_screen_height() - vertical_gap)
        self.rect: p.Rectangle = p.Rectangle(p.get_screen_width(), 0, 100, height)
        self.speed: float = speed
        self.color: p.Color = p.DARKGREEN

        self.scored: bool = False

    def draw(self) -> None:
        # draw top pillar
        p.draw_rectangle_rec(self.rect, self.color)

        # draw bottom pillar
        bottom_y: float = self.rect.y + self.rect.height + self.vertical_gap
        p.draw_rectangle_rec(
            p.Rectangle(
                self.rect.x, bottom_y, self.rect.width, p.get_screen_height() - bottom_y
            ),
            self.color,
        )

    def update(self) -> None:
        self.rect.x -= self.speed * p.get_frame_time()


class Pillars:
    def __init__(self) -> None:
        self.list: list[Pillar] = []

        self.vertical_gap: float = 250.0
        self.horizontal_gap: float = 200.0
        self.speed: float = 200.0
        self.speed_increment: float = 5.0

    def draw(self) -> None:
        for pillar in self.list:
            pillar.draw()

    def update(self, player: Player, score: list[int]) -> bool:
        # add new pillars to list
        if (
            len(self.list) <= 0
            or self.list[-1].rect.x + self.list[-1].rect.width + self.horizontal_gap
            < p.get_screen_width()
        ):
            self.list.append(Pillar(self.vertical_gap, self.speed))

        # increment pillar speed
        self.speed += self.speed_increment * p.get_frame_time()

        # manage pillars in list
        for pillar in self.list[:]:
            pillar.update()

            # update score
            if player.rect.x > pillar.rect.x + pillar.rect.width and not pillar.scored:
                pillar.scored = True
                score[0] += 1

            # check player collision with pillars
            # top pillar collision
            if p.check_collision_recs(player.rect, pillar.rect):
                return True

            # bottom pillar collision
            bottom_y: float = pillar.rect.y + pillar.rect.height + self.vertical_gap
            bottom_pillar_rect: p.Rectangle = p.Rectangle(
                pillar.rect.x,
                bottom_y,
                pillar.rect.width,
                p.get_screen_height() - bottom_y,
            )
            if p.check_collision_recs(player.rect, bottom_pillar_rect):
                return True

            # remove offscreen pillar
            if pillar.rect.x + pillar.rect.width + self.horizontal_gap < 0:
                self.list.remove(pillar)

        return False


def main() -> None:
    p.init_window(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE)

    score: list[int] = [0]
    game_over: bool = False

    player: Player = Player()
    pillars: Pillars = Pillars()

    while not p.window_should_close():
        if not game_over:
            player.update()
            game_over = pillars.update(player, score)
        else:
            if p.is_key_pressed(p.KeyboardKey.KEY_ENTER):
                score[0] = 0
                game_over = False

                player = Player()
                pillars = Pillars()

        p.begin_drawing()
        p.clear_background(SCREEN_BACKGROUND)

        if not game_over:
            player.draw()
            pillars.draw()

        # draw score
        p.draw_text(f"Score: {score[0]}", 10, 20, 30, p.BLACK)

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

        p.end_drawing()

    p.close_window()


if __name__ == "__main__":
    main()
