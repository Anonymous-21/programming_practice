import pyray as p
from random import uniform

from utility.center_and_draw_text import center_and_draw_text
from utility.timer import IntervalTimer

SCREEN_WIDTH: int = 800
SCREEN_HEIGHT: int = 200
SCREEN_TITLE: str = "Endless Runner"
SCREEN_BACKGROUND: p.Color = p.SKYBLUE


class Player:
    def __init__(self) -> None:
        height: float = 50.0
        self.rect: p.Rectangle = p.Rectangle(
            150, p.get_screen_height() - height, 20, height
        )
        self.color: p.Color = p.RED
        self.gravity: float = 1500.0
        self.jump_force: float = -550.0
        self.change_y: float = 0.0
        self.jumping: bool = False

    def draw(self) -> None:
        p.draw_rectangle_rec(self.rect, self.color)

    def update(self) -> None:
        if p.is_key_pressed(p.KeyboardKey.KEY_UP) and not self.jumping:
            self.jumping = True
            self.change_y = self.jump_force

        if self.jumping:
            self.change_y += self.gravity * p.get_frame_time()
            self.rect.y += self.change_y * p.get_frame_time()

            if self.rect.y > p.get_screen_height() - self.rect.height:
                self.jumping = False

        self.rect.y = max(
            0.0, min(self.rect.y, p.get_screen_height() - self.rect.height)
        )


class Enemy:
    def __init__(self) -> None:
        height: float = uniform(50, 70)
        width: float = uniform(10, 30)
        self.rect: p.Rectangle = p.Rectangle(
            p.get_screen_width(), p.get_screen_height() - height, width, height
        )
        self.color: p.Color = p.DARKGREEN
        self.horizontal_distance: float = uniform(300, 400)
        self.speed: float = 300.0
        self.speed_increment: float = 10.0

        self.scored: bool = False
        self.last_score: int = 0

    def draw(self) -> None:
        p.draw_rectangle_rec(self.rect, self.color)

    def update(self, score: int) -> None:
        # move
        self.rect.x -= self.speed * p.get_frame_time()

        # increment speed
        if score != 0 and score % 10 == 0 and self.last_score != 0:
            self.speed += self.speed_increment
            self.last_score = score


class Enemies:
    def __init__(self) -> None:
        self.list: list[Enemy] = []

    def draw(self) -> None:
        for enemy in self.list:
            enemy.draw()

    def update(self, score: int, player_x: float) -> int:
        if (
            len(self.list) <= 0
            or self.list[-1].rect.x
            < p.get_screen_width() - self.list[-1].horizontal_distance
        ):
            enemy: Enemy = Enemy()
            self.list.append(enemy)

        for enemy in self.list[:]:
            enemy.update(score)

            # update score
            if player_x >= enemy.rect.x + enemy.rect.width and not enemy.scored:
                score += 1
                enemy.scored = True

            # remove enemy
            if enemy.rect.x < -enemy.rect.width:
                self.list.remove(enemy)

        return score


def main() -> None:
    p.init_window(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE)

    score: int = 0
    game_over: bool = False
    interval_timer: IntervalTimer = IntervalTimer(1.0)

    player: Player = Player()
    enemies: Enemies = Enemies()

    while not p.window_should_close():
        interval_timer.update()

        if not game_over:
            player.update()
            score = enemies.update(score, player.rect.x)

            # player collision enemies
            for enemy in enemies.list:
                if p.check_collision_recs(player.rect, enemy.rect):
                    game_over = True

        else:
            if p.is_key_pressed(p.KeyboardKey.KEY_ENTER):
                score = 0
                game_over = False

                player = Player()
                enemies = Enemies()

        p.begin_drawing()
        p.clear_background(SCREEN_BACKGROUND)

        p.draw_text(f"Score: {score}", 10, 10, 30, p.BLACK)

        if not game_over:
            enemies.draw()
            player.draw()

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
                    p.get_screen_height() + 100,
                )

        p.end_drawing()

    p.close_window()


if __name__ == "__main__":
    main()
