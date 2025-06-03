from enum import Enum


class GameState(Enum):
    STATE_MAIN_MENU = 0
    STATE_PLAYER_SELECTION = 1
    STATE_TOWN = 2
    STATE_MAP = 3
    STATE_SHOP = 4
    STATE_QUEST = 5

    STATE_QUIT = 6
