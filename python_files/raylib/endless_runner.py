import pyray as p
from random import uniform

from center_and_draw_texts import center_and_draw_text

SCREEN_WIDTH: int = 1000
SCREEN_HEIGHT: int = 250
SCREEN_TITLE: str = "ENDLESS RUNNER"
SCREEN_BACKGROUND: p.Color = p.LIGHTGRAY


class Player:
    def __init__(self) -> None:
        height: float = 70.0
        self.rect: p.Rectangle = p.Rectangle(
            200, p.get_screen_height() - height, 30, height
        )
        self.color: p.Color = p.BLUE

        self.jump_force: float = -700.0
        self.gravity: float = 1500.0
        self.change_y: float = 0.0
        self.is_jumping: bool = False

    def draw(self) -> None:
        p.draw_rectangle_rec(self.rect, self.color)

    def update(self) -> None:
        if p.is_key_pressed(p.KeyboardKey.KEY_UP) and not self.is_jumping:
            self.is_jumping = True
            self.change_y = self.jump_force

        if self.is_jumping:
            self.change_y += self.gravity * p.get_frame_time()
            self.rect.y += self.change_y * p.get_frame_time()

        if self.rect.y > p.get_screen_height() - self.rect.height:
            self.is_jumping = False

        self.rect.y = max(
            0.0, min(self.rect.y, p.get_screen_height() - self.rect.height)
        )


class Enemy:
    def __init__(self) -> None:
        width: float = uniform(30, 70)
        height: float = uniform(50, 100)
        self.rect: p.Rectangle = p.Rectangle(
            p.get_screen_width(), p.get_screen_height() - height, width, height
        )
        self.color: p.Color = p.DARKGREEN

        self.horizontal_distance: float = uniform(400, 500)
        self.scored: bool = False

    def draw(self) -> None:
        p.draw_rectangle_rec(self.rect, self.color)

    def update(self, speed: float) -> None:
        self.rect.x -= speed * p.get_frame_time()


class Enemies:
    def __init__(self) -> None:
        self.list: list[Enemy] = []

        self.speed: float = 300.0
        self.speed_increment: float = 10.0

    def draw(self) -> None:
        for enemy in self.list:
            enemy.draw()

    def update(self, player: Player, score: list[int], game_over: bool) -> bool:
        # add new enemy
        if (
            len(self.list) <= 0
            or self.list[-1].rect.x
            + self.list[-1].rect.width
            + self.list[-1].horizontal_distance
            < p.get_screen_width()
        ):
            self.list.append(Enemy())

        for enemy in self.list[:]:
            # move enemy
            enemy.update(self.speed)

            # increment speed
            self.speed += self.speed_increment * p.get_frame_time()

            # update score
            if player.rect.x > enemy.rect.x + enemy.rect.width and not enemy.scored:
                enemy.scored = True
                score[0] += 1

            # player collision enemy
            if p.check_collision_recs(player.rect, enemy.rect):
                game_over = True

            # remove enemy
            if enemy.rect.x + enemy.rect.width + enemy.horizontal_distance < 0:
                self.list.remove(enemy)

        return game_over


def main() -> None:
    p.init_window(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE)

    score: list[int] = [0]
    game_over: bool = False

    player: Player = Player()
    enemies: Enemies = Enemies()

    while not p.window_should_close():
        if not game_over:
            player.update()
            game_over = enemies.update(player, score, game_over)
        else:
            if p.is_key_pressed(p.KeyboardKey.KEY_ENTER):
                score[0] = 0
                game_over = False

                player = Player()
                enemies = Enemies()

        p.begin_drawing()
        p.clear_background(SCREEN_BACKGROUND)

        # draw score
        p.draw_text(f"Score: {score[0]}", 20, 20, 30, p.DARKGRAY)

        if not game_over:
            player.draw()
            enemies.draw()

        if game_over:
            center_and_draw_text(
                "GAME OVER",
                40,
                p.Rectangle(0, 0, p.get_screen_width(), p.get_screen_height()),
                p.DARKGRAY,
            )
            center_and_draw_text(
                "press ENTER to restart",
                30,
                p.Rectangle(0, 0, p.get_screen_width(), p.get_screen_height() + 100),
                p.DARKGRAY,
            )

        p.end_drawing()

    p.close_window()


if __name__ == "__main__":
    main()
