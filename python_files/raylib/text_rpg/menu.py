import pyray as p


class Menu:
    def __init__(
        self,
        text_list: list[str],
        font_size: int,
        text_gap: int,
        layout_rect: p.Rectangle,
    ) -> None:
        self.text_list: list[str] = text_list
        self.font_size: int = font_size
        self.text_gap: int = text_gap
        self.text_height: int = self.font_size + self.text_gap
        self.layout_rect: p.Rectangle = layout_rect

        self.selected_element_idx: int = 0
        self.first_visible_element_idx: int = 0
        self.max_visible_elements: int = int(
            (self.layout_rect.height - self.text_gap) / self.text_height
        )
        self.max_visible_height: int = (self.font_size * len(self.text_list)) + (
            self.text_gap * (len(self.text_list) - 1)
        )

    def draw(self) -> None:
        last_visible_element: int = (
            self.first_visible_element_idx + self.max_visible_elements
        )

        for i in range(self.first_visible_element_idx, last_visible_element):
            if i >= 0 and i < len(self.text_list):
                text_width: int = p.measure_text(self.text_list[i], self.font_size)
                text_x: int = int(
                    self.layout_rect.x + self.layout_rect.width / 2 - text_width / 2
                )
                text_y: int = int(
                    self.layout_rect.y
                    + self.layout_rect.height / 2
                    - self.max_visible_height / 2
                    + (i - self.first_visible_element_idx) * self.text_height
                )

                self.color: p.Color = (
                    p.BLACK if i == self.selected_element_idx else p.GRAY
                )

                p.draw_text(
                    self.text_list[i], text_x, text_y, self.font_size, self.color
                )

                if i == self.selected_element_idx:
                    horizontal_gap: int = 30
                    p.draw_text(
                        ">", text_x - horizontal_gap, text_y, self.font_size, self.color
                    )

    def update(self) -> None:
        if p.is_key_pressed(p.KeyboardKey.KEY_UP):
            self.selected_element_idx = (
                self.selected_element_idx - 1 + len(self.text_list)
            ) % len(self.text_list)

        if p.is_key_pressed(p.KeyboardKey.KEY_DOWN):
            self.selected_element_idx = (self.selected_element_idx + 1) % len(
                self.text_list
            )

