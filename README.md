# Exponential Engine

> *It's called 'Exponential' because it runs in O(2ⁿ) time.*

A 2.5D raycast game engine built around an object-oriented architecture. Still in early development — core rendering is functional, with multiplayer, textures, a level editor, and entities all on the way.

---

## How it works

The engine renders a 2.5D perspective view using a column-based raycasting algorithm, similar in spirit to classic engines like Wolfenstein 3D. Rendering is triggered whenever a change in the player's position or orientation is detected.

### CalculatePoint()

The core of the renderer is the `CalculatePoint()` subroutine. It takes a position and direction in a 2D grid space and determines the exact point at which the ray crosses into the next grid cell. The steps are:

1. Get the x and y direction components from the current heading
2. Determine the next integer grid coordinates (`x2`, `y2`) in that direction
3. Compare `nx()` and `ny()` to find which axis boundary is closer
4. Use the closer value as the known coordinate of the cell border
5. Solve for the unknown coordinate algebraically
6. Return the cell border crossing point

This process repeats recursively — stepping from cell to cell — until either a wall is hit or the maximum render distance is exceeded.

### Render()

The full render pipeline runs as follows:

1. **Calculate projection angles** — the player's heading is partitioned across the screen width to span the configured FOV, producing a `projectionAngles` vector
2. **Draw background** — the ceiling and floor are drawn first via `DrawBackground()`
3. **Raycast each column** — for each partition angle, `Raycast()` is called from the player's position. It calls `CalculatePoint()` recursively and either returns a ray length (sum of all ray segments to the wall) or `-1` on timeout
4. **Fisheye correction** — the raw ray length is converted to a *range* (the component projecting along the player's heading) via `Utils::GetRayRange()`. Using raw length would produce a fisheye distortion
5. **Draw column** — `GetColumnHeight()` converts the range to a screen-space column height, and `DrawColumn()` renders it with proximity-based grayscale shading to simulate depth

---

## File structure

The project layout is modelled after Source Engine, with assets divided into typed subdirectories. Search paths are defined in `gameinfo.json` and loaded at startup.

```
game/
├── config/       # Engine and game configuration files
├── maps/         # Map files
├── resources/    # General assets and resources
└── sound/        # Audio files
```

Search paths can be restructured — see the [gameinfo.json](#gameinfojson) section below. Adding a new path requires an `extern` declaration in `system.h` and an implementation in `system.cpp`.

---

## gameinfo.json

Inspired by Source Engine's `gameinfo.txt`, this file provides metadata and search paths loaded by `System::LoadGameInfo()` on startup.

```json
{
    "game": "Executable Name",
    "title": "InGame Title",
    "type": "single_player",
    "debug": true,
    "search_paths": {
        "maps": "game/maps/",
        "sound": "game/sound/",
        "resources": "game/resources/",
        "textures": "game/textures/"
    }
}
```

| Field | Description |
|---|---|
| `game` | The executable name |
| `title` | Title displayed in-game |
| `type` | Game mode — `single_player` or `multiplayer` |
| `debug` | Enables debug output when `true` |
| `search_paths` | Asset directory paths resolved at startup |

### Adding a custom search path

**system.h** — declare the extern:
```cpp
extern std::string searchPath_res;
extern std::string searchPath_textures;
extern [type] [identifier];
```

**system.cpp** — implement and load it:
```cpp
[type] [identifier];

void System::LoadGameInfo() {
    json gameInfo = Globals::ParseJson("gameinfo.json");
    if (gameInfo == NULL) return;

    [identifier] = gameInfo[[gameinfo_key]].template get<[type]>();
}
```

**gameinfo.json** — add the entry under `search_paths`:
```json
"search_paths": {
    "my_path": "game/my_path/"
}
```

---

## Features

- Raycast 2.5D graphics with fisheye correction
- Object-oriented architecture
- Moddable without writing code

**Coming soon**

- Textures
- Entities
- Level editor
- Multiplayer

---

## Contact

- Email: mawsesoftware@gmail.com
- Instagram: [@mawsesoftware](https://instagram.com/mawsesoftware)
