import pyray as rl
import math

# Window dimensions
SCREEN_WIDTH = 800
SCREEN_HEIGHT = 600

# Map settings
MAP_WIDTH = 10
MAP_HEIGHT = 10
TILE_SIZE = 64

# Field of view in radians
FOV = math.pi / 3  # 60 degrees
NUM_RAYS = 120
MAX_DEPTH = 800
DELTA_ANGLE = FOV / NUM_RAYS

# Simple 2D map (1 = wall, 0 = empty space)
WORLD_MAP = [
    [1,1,1,1,1,1,1,1,1,1],
    [1,0,0,0,0,0,0,0,0,1],
    [1,0,1,0,1,0,1,0,0,1],
    [1,0,1,0,1,0,1,0,0,1],
    [1,0,0,0,0,0,1,0,0,1],
    [1,0,1,0,1,0,1,0,0,1],
    [1,0,1,0,1,0,1,0,0,1],
    [1,0,0,0,0,0,0,0,0,1],
    [1,0,0,0,0,0,0,0,0,1],
    [1,1,1,1,1,1,1,1,1,1],
]

# Player settings
player_x = 300
player_y = 300
player_angle = 0
player_speed = 2
rotation_speed = 0.04


# Start window
rl.init_window(SCREEN_WIDTH, SCREEN_HEIGHT, "Raycaster in Raylib Python")
rl.set_target_fps(60)

def cast_ray(x, y, angle):
    """Cast a single ray and return distance to the wall and hit coordinates."""
    sin_a = math.sin(angle)
    cos_a = math.cos(angle)
    
    for depth in range(1, MAX_DEPTH):
        target_x = x + cos_a * depth
        target_y = y + sin_a * depth

        map_x = int(target_x / TILE_SIZE)
        map_y = int(target_y / TILE_SIZE)

        if 0 <= map_x < MAP_WIDTH and 0 <= map_y < MAP_HEIGHT:
            if WORLD_MAP[map_y][map_x] == 1:
                return depth, target_x, target_y

    return MAX_DEPTH, x + cos_a * MAX_DEPTH, y + sin_a * MAX_DEPTH

while not rl.window_should_close():
    # Handle movement
    if rl.is_key_down(rl.KeyboardKey.KEY_W):
        player_x += math.cos(player_angle) * player_speed
        player_y += math.sin(player_angle) * player_speed
    if rl.is_key_down(rl.KeyboardKey.KEY_S):
        player_x -= math.cos(player_angle) * player_speed
        player_y -= math.sin(player_angle) * player_speed
    if rl.is_key_down(rl.KeyboardKey.KEY_A):
        player_angle -= rotation_speed
    if rl.is_key_down(rl.KeyboardKey.KEY_D):
        player_angle += rotation_speed

    # Begin drawing
    rl.begin_drawing()
    rl.clear_background(rl.DARKGRAY)

    # Render 3D walls via raycasting
    start_angle = player_angle - FOV / 2
    for ray in range(NUM_RAYS):
        ray_angle = start_angle + ray * DELTA_ANGLE
        depth, target_x, target_y = cast_ray(player_x, player_y, ray_angle)

        # Remove fish-eye effect
        corrected_depth = depth * math.cos(player_angle - ray_angle)

        # Calculate projected wall height
        wall_height = 5000 / (corrected_depth + 0.0001)

        # Determine color based on distance
        shade = 255 / (1 + corrected_depth * corrected_depth * 0.0001)
        color = rl.Color(int(shade), int(shade), int(shade), 255)

        # Draw vertical wall slice
        rl.draw_line(ray * (SCREEN_WIDTH // NUM_RAYS),
                     int(SCREEN_HEIGHT / 2 - wall_height / 2),
                     ray * (SCREEN_WIDTH // NUM_RAYS),
                     int(SCREEN_HEIGHT / 2 + wall_height / 2),
                     color)

    # Optionally draw 2D map and player
    for y in range(MAP_HEIGHT):
        for x in range(MAP_WIDTH):
            rect_color = rl.GRAY if WORLD_MAP[y][x] == 1 else rl.DARKGRAY
            rl.draw_rectangle(x * 10, y * 10, 10, 10, rect_color)
    rl.draw_circle(int(player_x / 6.4), int(player_y / 6.4), 3, rl.RED)

    rl.end_drawing()

# Close window
rl.close_window()
