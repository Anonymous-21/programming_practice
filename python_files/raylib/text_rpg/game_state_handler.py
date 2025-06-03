from game_state import GameState

class GameStateHandler:
    def __init__(self) -> None:
        self.current_state: GameState = GameState.STATE_MAIN_MENU
