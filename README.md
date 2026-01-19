# York
A 2D sandbox survival game that runs entirely in your terminal. Yes, you read that right - a fully functional Minecraft-like experience with procedural world generation, cave systems, and ore distribution, all rendered using ASCII characters in your command prompt.

Built from scratch in C++. No game engines. No libraries beyond standard stuff.

---

## Why This Game is Actually Insane


It's Running in a Terminal. Not a game engine. Not a graphics library. Just your plain old terminal window. Every block, every animation, every menu - rendered frame by frame using colored ASCII characters. The entire game loop runs at ~30 FPS with smooth character movement, falling physics, and real-time world generation.

Infinite Procedurally Generated Worlds. Enter a seed and watch as the game generates an endless world with realistic terrain, underground cave systems, and ore veins. Each world is completely unique, with rolling hills, deep caverns, and valuable resources scattered throughout. The terrain generation uses Perlin noise and fractional Brownian motion - the same techniques used in professional game engines.

A Full Window Management System. The game implements its own window manager with stacking, layering, animations, and state management. Menus slide in smoothly, dialog boxes pop up with proper borders, and everything feels responsive despite running in a text-based environment.

---

## How to Play
Creating Your World: Start the game and you'll see an intro sequence (yes, with story and animated character movement). Enter your name and choose a character icon. Then create a new world by giving it a name and optionally a seed number. The game will generate your unique world and spawn you on the surface.

Mining and Building: Use arrow keys with Shift held down to break blocks around you (up, down, left, right). Each block you break goes into your inventory - grass, stone, iron, gold, and diamonds. Switch to placement mode by releasing Shift, then use arrow keys to place blocks from your inventory. Press 'E' to open your inventory and select which block type to place.

Exploring Caves: As you dig down, you'll discover massive cave systems. These aren't random - they're generated using 3D noise functions that create realistic cavern networks. Caves become more common the deeper you go, with a gradual transition zone so they feel natural.

Finding Ores: Iron appears below Y level 100, gold below 300, and diamonds at 500+. Each ore has its own generation pattern using layered noise functions, creating veins that feel like real geological formations rather than random scattered blocks.

Saving Your Progress: Press Enter during gameplay to open the pause menu. Here you can save your world, enable cheats, or return to the main menu. Your world, inventory, and character position are all preserved between sessions.

---

## The Story (Just the Beginning!)

The intro presents you with a mysterious dialogue:

*"Hi, Spatial - oh, you seem confused by that word, so let me explain: you are a tri-dimensional organism, and that's why I call you Spatial."*

*"As I promised, I surrender my will to you - but in return, you must make me YORK; and because a world can endure only one YORK, you will have to erase the one who exists now."*

*"Strip me of my old name and grant me a new one - and if it pleases you, reshape my very appearance as well."*

This is just 1% of the story. Who is speaking? What is YORK? Why must you erase someone? These mysteries and more will unfold in future updates. The narrative will weave through your gameplay, revealing itself as you explore deeper into the world.

---

## Controls
Movement: A and D to move left and right. Space to jump (you can jump 8 blocks high!). The game has proper gravity and collision detection.

Mining: Hold Shift + Arrow Keys to break blocks in that direction. Broken blocks automatically go to your inventory.
Placing Blocks: Arrow Keys (without Shift) to place the selected block in that direction.

Inventory: Press E to open your inventory screen. Use W and S to navigate, Enter to select a block type for placing.
Pause Menu: Press Enter during gameplay to pause, save, or access cheats.

Cheats Menu: From the pause menu, you can enable Speed Mode (removes all delays for instant movement), Ghost Mode (fly through blocks and walls), or give yourself 9999 diamonds.

---

## This is Just the Beginning

Right now you can explore, mine, build, and save your worlds. But I have so many features planned: multiplayer support (the UI already has a placeholder for it), more block types, crafting systems, mobs and enemies, better world generation with biomes and structures, and a complete story mode. The foundation is solid - now it's time to build an entire game on top of it.

---

## How Does This Even Work?

The Window System (The Heart of Everything)
Imagine your game as a stack of windows, like papers piled on a desk. Each "window" is a game state - the main menu, a dialog box, the game world, the inventory screen. The game uses a literal stack<win> data structure where each window has:

A name (like "main_menu", "inventory", "pause")
Multiple screen layers (stored as maps of 2D pixel arrays)
State variables (positions, counters, flags)
An initialization flag

Every frame, the game looks at the top window on the stack and calls its corresponding function. That function updates its state, draws to its screen layers, and the final composed result gets rendered. Want to open the inventory? Push a new inventory window onto the stack. Close it? Pop it off. This creates natural state management where pausing the game doesn't freeze it - it just adds a new layer on top.


## Terminal Rendering Magic
The Pixel System: Each cell on screen is a pixel struct with a color (0-9 integer) and a value (string, usually one character). The game maintains a 2D array of these pixels matching your terminal size.

Screen Clearing: The game uses two methods. Soft clear (\033[H) just moves the cursor to the top-left and overwrites the previous frame. Hard clear (calling system("clear") or system("cls")) actually clears the screen buffer - used when switching between major game states to prevent visual glitches.

Color System: Each color is a stored ANSI escape code. Before drawing a pixel, the game outputs the escape code for that color, then the character, creating colored text. There are 9 colors including standard ones (red, blue, green) plus custom RGB codes for materials like iron (\033[38;2;160;150;130m) and gold (\033[38;2;200;200;0m).

Animation: There's no animation library - everything is manual frame-by-frame updates. The main menu sliding title? It's a counter that increments each frame, updating the Y position where the title is drawn. Character walking? Update the X position while checking collision each frame. All animations use delay functions for timing, with a "speed" cheat flag that disables delays for instant movement.

Screen Layer System: Windows can have multiple named screens (like "screen", "menu", "dialog", "platform"). Each is a separate 2D pixel array. The ita() function (image to array) composites these layers together, with configurable positions and border clipping. The main game composites the terrain layer, then the player layer on top, then the status bar, all in separate draw calls.

---
## Data Storage and Persistence
Boot Data: Player name, character icon, and color preferences are stored in data/boot.kp as binary. The game writes string lengths followed by the strings, and long longs directly as bytes. On load, it reads lengths first to know how many bytes to read for each string.

World Data: Each world gets a folder in data/worlds/[worldname]/. The data.kp file contains the seed, player position, health, inventory (as a map of item ID to count), and all modified chunks. Only chunks with player modifications are saved - unmodified chunks are regenerated from the seed when loaded.

Chunk Data: Each chunk stores its X/Y position, whether it should always stay loaded (for structures later), and a map of local coordinates to block IDs - but only for blocks the player has changed. When you break a block, it adds an entry to this change map. On save, the entire change map is serialized. On load, the chunk regenerates from the world seed, then applies the change map on top.

---

## Window-to-Window Data Transfer
This is where it gets clever. When window A needs to ask the user for input and give it to window B, here's the flow:

Window A creates a new window, sets its sts["api"] field to a key name

Window A pushes the new window onto the stack

The input window collects data from the user

When done, the input window pops itself off the stack

But after popping, it sets wino.top().sts[api_key] = user_data

Wait, but it just popped itself, so wino.top() is now the calling window! This is the magic. By accessing the stack top right after popping, the input window writes directly to its caller's state map. No return values, no global variables - just stack manipulation.

For example, the "new game" window needs a world name. It creates an input_str window with sts["api"] = "world_name" and stl["limit"] = 10. The input window collects the string, then does wino.pop() followed by wino.top().sts["world_name"] = collected_string. The new game window checks if sts["world_name"] exists, and if so, uses it to create the world.

---

## World Generation (The Fun Part)

Height Generation: Uses 1D Perlin noise with fractional Brownian motion (FBM). For each X coordinate, the game hashes the seed and X value to get a pseudorandom value between 0 and 1. It then interpolates between grid points using smoothstep for natural-looking curves. FBM layers multiple octaves of noise at different frequencies - high frequency for small details, low frequency for rolling hills.

Grass Layer: Separate noise function determines where grass transitions to stone. This creates variety where some hills are grassy all the way down, others expose stone quickly.

Cave Generation: Uses 2D Perlin noise on the X-Y plane. For each potential block position, the game samples the noise at that coordinate. If the value exceeds a threshold (0.55), it's air - creating a cave. The threshold increases near the surface using a falloff function, so caves gradually fade out instead of just stopping. Caves become more common with depth because the noise scale is different on the Y axis (multiplied by 3.0), creating vertical stretching.

Ore Distribution: Each ore type (iron, gold, diamond) uses its own noise function with a minimum Y level. The noise is raised to a power (2.5 for iron, 3.0 for gold, 3.5 for diamonds) which creates rarer but more concentrated veins for rarer ores. A "mask" noise layer adds large-scale variation, and a "breaker" noise creates gaps in veins so they're not solid blobs. All three layers must pass their thresholds for an ore block to generate.

Seeded Randomness: Every noise function uses the world seed. Hash the seed with the coordinates to get a deterministic but unpredictable value. Same seed = same world, every time.

---

## The Chunk System

Chunk Size: The world is divided into 10x10 block chunks. When you're at position (23, 47), that's in chunk (20, 40) - always rounded down to nearest multiple of 10.

Render Distance: The game maintains a render distance of 120 blocks. Every frame, it calculates which chunks should be loaded based on player position. If a chunk is loaded but outside render distance, it saves any modifications to the world data structure and unloads it from memory.

Lazy Loading: Chunks only generate when needed. If you request a block in an unloaded chunk, get_block() triggers chunk generation for that chunk. This means you never wait for world generation - it happens on-demand as you explore.

Rendering: To render, the game finds all loaded chunks, calculates where each would appear relative to the player (who's always at screen center), and composites them onto the screen buffer. Each chunk's blocks are copied pixel by pixel to the screen, with the player as the reference point for camera positioning.

---

Look, I know this is a lot to take in. A complete game, with physics, world generation, save systems, and a UI framework, all running in a terminal. Built from scratch in C++. No game engines. No libraries beyond standard stuff. Just code and passion.
But that's what makes it special. This is pure creativity - taking the constraints of a text-based environment and building something that shouldn't be possible. And I'm just getting started.

## Use of Ai

I have only used ai in learning procedural generation , input system and writing this readme!(coz i sucks in english).