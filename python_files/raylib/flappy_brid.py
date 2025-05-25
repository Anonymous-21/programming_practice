import pyray as p
from random import uniform

from utility.center_and_draw_text import center_and_draw_text
from utility.timer import IntervalTimer

SCREEN_WIDTH: int = 800
SCREEN_HEIGHT: int = 600
SCREEN_TITLE: str = "Flappy Brid"
SCREEN_BACKGROUND: p.Color = p.SKYBLUE


class Player:
    def __init__(self) -> None:
        self.rect: p.Rectangle = p.Rectangle(200, 200, 50, 50)
        self.color: p.Color = p.RED
        self.change_y: float = 0.0
        self.jump_force: float = -500
        self.gravity: float = 1500
        self.jumping: bool = False

    def draw(self) -> None:
        p.draw_rectangle_rec(self.rect, self.color)

    def update(self) -> None:
        if p.is_key_pressed(p.KeyboardKey.KEY_UP):
            self.active = True
            self.jumping = True
            self.change_y = self.jump_force

        self.change_y += self.gravity * p.get_frame_time()
        self.rect.y += self.change_y * p.get_frame_time()

        self.rect.y = max(
            0.0, min(self.rect.y, p.get_screen_height() - self.rect.height)
        )


class Pillar:
    def __init__(self) -> None:
        self.vertical_distance: float = 200.0
        self.horizontal_distance: float = 400.0
        height: float = uniform(0, p.get_screen_height() - self.vertical_distance)
        self.rect: p.Rectangle = p.Rectangle(p.get_screen_width(), 0, 100, height)
        self.color: p.Color = p.DARKGREEN
        self.speed: float = 300.0
        self.speed_increment: float = 10.0
        self.scored: bool = False

    def draw(self) -> None:
        # top pillar
        p.draw_rectangle_rec(self.rect, self.color)

        # bottom pillar
        bottom_y: float = self.rect.height + self.vertical_distance
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

        self.last_score: int = 0

    def draw(self) -> None:
        for pillar in self.list:
            pillar.draw()

    def update(self, score: int, player_x: float) -> int:
        # add pillars
        if (
            len(self.list) <= 0
            or self.list[-1].rect.x
            < p.get_screen_width() - self.list[-1].horizontal_distance
        ):
            self.list.append(Pillar())

        for pillar in self.list[:]:
            # move pillars
            pillar.update()

            # increment pillar speed
            if score % 10 == 0 and score != self.last_score:
                self.last_score = score
                pillar.speed += pillar.speed_increment * p.get_frame_time()

            # update score
            if player_x > pillar.rect.x + pillar.rect.width and not pillar.scored:
                score += 1
                pillar.scored = True

            # remove pillar
            if pillar.rect.x < -pillar.rect.width:
                self.list.remove(pillar)

        return score


def main() -> None:
    p.init_window(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE)

    score: int = 0
    active: bool = False
    game_over: bool = False
    interval_timer: IntervalTimer = IntervalTimer(1.0)

    player: Player = Player()
    pillars: Pillars = Pillars()

    while not p.window_should_close():
        interval_timer.update()

        # activate game
        if p.is_key_pressed(p.KeyboardKey.KEY_UP):
            active = True

        if active and not game_over:
            player.update()
            score = pillars.update(score, player.rect.x)

            # pillar collision player
            for pillar in pillars.list:
                # top pillar
                if p.check_collision_recs(player.rect, pillar.rect):
                    game_over = True

                # bottom pillar
                bottom_y: float = pillar.rect.height + pillar.vertical_distance
                if p.check_collision_recs(
                    player.rect,
                    p.Rectangle(
                        pillar.rect.x,
                        bottom_y,
                        pillar.rect.width,
                        p.get_screen_height() - bottom_y,
                    ),
                ):
                    game_over = True

        else:
            if p.is_key_pressed(p.KeyboardKey.KEY_ENTER):
                score = 0
                active = False
                game_over = False

                player = Player()
                pillars = Pillars()

        p.begin_drawing()
        p.clear_background(SCREEN_BACKGROUND)

        player.draw()
        pillars.draw()

        p.draw_text(f"Score: {score}", 20, 20, 30, p.BLACK)

        if not active and interval_timer.is_ready():
            center_and_draw_text(
                "press UP to start",
                30,
                0,
                0,
                p.get_screen_width(),
                p.get_screen_height() + 300,
            )

        if game_over:
            center_and_draw_text(
                "GAME OVER", 40, 0, 0, p.get_screen_width(), p.get_screen_height()
            )

            if interval_timer.is_ready():
                center_and_draw_text(
                    "press ENTER to restart",
                    30,
                    0,
                    0,
                    p.get_screen_width(),
                    p.get_screen_height() + 300,
                )

        p.end_drawing()

    p.close_window()


if __name__ == "__main__":
    main()
