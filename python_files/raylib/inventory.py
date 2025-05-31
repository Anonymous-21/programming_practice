import pyray as p

SCREEN_WIDTH: int = 1000
SCREEN_HEIGHT: int = 800
SCREEN_TITLE: str = "Inventory"
SCREEN_BACKGROUND: p.Color = p.LIGHTGRAY
GAME_FPS: int = 60

ROWS: int = 5
COLS: int = 5
SLOT_SIZE: int = 100
SLOT_GAP: int = 3

NUM_OF_ITEMS: int = 5


class Item:
    def __init__(self, id: int, x: float, y: float) -> None:
        self.id: int = id
        self.rect: p.Rectangle = p.Rectangle(x, y, 60, 60)
        self.color: p.Color = p.GRAY
        self.offset: p.Vector2 = p.Vector2(0, 0)
        self.is_dragging: bool = False

    def draw(self) -> None:
        p.draw_rectangle_rec(self.rect, self.color)


def main() -> None:
    p.init_window(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE)
    p.set_target_fps(GAME_FPS)

    pos: p.Vector2 = p.Vector2(20, 20)
    show_inventory: bool = True

    slots: list[p.Rectangle] = []

    for i in range(ROWS):
        for j in range(COLS):
            x: float = j * (SLOT_SIZE + SLOT_GAP) + pos.x
            y: float = i * (SLOT_SIZE + SLOT_GAP) + pos.y

            slots.append(p.Rectangle(x, y, SLOT_SIZE, SLOT_SIZE))

    item_list: list[Item] = []

    for i in range(NUM_OF_ITEMS):
        item_list.append(Item(i, 800, (i * 100) + 50))

    inventory: list[Item] = []

    while not p.window_should_close():
        # show and hide inventory and slots
        if p.is_key_pressed(p.KeyboardKey.KEY_I):
            show_inventory = not show_inventory

        mouse_pos: p.Vector2 = p.get_mouse_position()

        # remove item from inventory
        for item in inventory[:]:
            if p.check_collision_point_rec(
                mouse_pos, item.rect
            ) and p.is_mouse_button_pressed(0):
                item.is_dragging = True
                item.offset.x = mouse_pos.x - item.rect.x
                item.offset.y = mouse_pos.y - item.rect.y

                # remove item from inventory and add it to item_list
                item_list.append(item)
                inventory.remove(item)

        # drag and drop item
        for item in item_list[:]:
            if p.check_collision_point_rec(
                mouse_pos, item.rect
            ) and p.is_mouse_button_pressed(0):
                item.is_dragging = True
                item.offset.x = mouse_pos.x - item.rect.x
                item.offset.y = mouse_pos.y - item.rect.y

            if item.is_dragging:
                item.rect.x = mouse_pos.x - item.offset.x
                item.rect.y = mouse_pos.y - item.offset.y

            if p.is_mouse_button_released(0) and item.is_dragging:
                item.is_dragging = False

                # snap to slot
                for slot in slots:
                    if p.check_collision_recs(slot, item.rect):
                        item.rect.x = slot.x + (slot.width - item.rect.width) / 2
                        item.rect.y = slot.y + (slot.height - item.rect.height) / 2

                        # add item to inventory
                        inventory.append(item)
                        item_list.remove(item)

        # inventory and item list checks
        print("*********** INVENTORY *****************")
        for item in inventory:
            print(f"ID: {item.id}")
        print("*********** ITEM_LIST *****************")
        for item in item_list:
            print(f"ID: {item.id}")

        p.begin_drawing()
        p.clear_background(SCREEN_BACKGROUND)

        if show_inventory:
            for slot in slots:
                color: p.Color = (
                    p.RED if p.check_collision_point_rec(mouse_pos, slot) else p.BLACK
                )

                p.draw_rectangle_lines_ex(slot, 5.0, color)

            for item in inventory:
                item.draw()

        for item in item_list:
            item.draw()

        p.end_drawing()

    p.close_window()


if __name__ == "__main__":
    main()
