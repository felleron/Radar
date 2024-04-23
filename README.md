# Radar

Radar is a simple radar simulation program written in C using the SDL (Simple DirectMedia Layer) library.

## Description

This program simulates a radar display with a rotating line representing a radar sweep. The radar sweep rotates around its center, displaying a red line that indicates the current angle of the sweep. Additionally, it displays fading shadow lines representing previous positions of the radar sweep.

## Features

- Real-time radar simulation
- Smooth rotation animation
- Fading shadow lines for previous radar sweep positions
- Background music playback using SDL_mixer library

## Requirements

- SDL2 library
- SDL2_image library
- SDL2_gfx library
- SDL2_mixer library

## Installation

1. Make sure you have SDL2, SDL2_image, SDL2_gfx, and SDL2_mixer libraries installed on your system.
2. Clone this repository to your local machine.
3. Compile the program using a C compiler (e.g., gcc) with the appropriate flags to link SDL libraries. For example:
    ```bash
    gcc radar.c -o radar -lSDL2 -lSDL2_image -lSDL2_gfx -lSDL2_mixer -lm
    ```
4. Run the compiled executable:
    ```bash
    ./radar
    ```

## Controls

- Close the window: Click the close button or press Alt+F4.

## Acknowledgements

- The radar simulation is based on the Simple DirectMedia Layer (SDL) library.
- Background music is played using the SDL_mixer library.

## Author

Felleron

