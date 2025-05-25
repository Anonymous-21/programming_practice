import pyray as p


class IntervalTimer:
    def __init__(self, interval_seconds: float) -> None:
        self.last_update_time: float = p.get_time()
        self.interval_seconds: float = interval_seconds
        self.toggle_state: bool = False

    def update(self) -> None:
        current_time: float = p.get_time()

        if current_time - self.last_update_time >= self.interval_seconds:
            self.last_update_time = current_time
            self.toggle_state = not self.toggle_state

    def is_ready(self) -> bool:
        if self.toggle_state:
            return True
        return False
