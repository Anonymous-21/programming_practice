import pyray as p

def center_and_draw_text(
    text: str,
    font_size: int,
    rect_x: int,
    rect_y: int,
    rect_width: int,
    rect_height: int,
    color: p.Color = p.BLACK,
) -> None:
    text_width: int = p.measure_text(text, font_size)
    text_x: int = rect_x + rect_width // 2 - text_width // 2
    text_y: int = rect_y + rect_height // 2 - font_size // 2

    p.draw_text(text, text_x, text_y, font_size, color)