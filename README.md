# Space Shooter

GAME DEMO: https://drive.google.com/file/d/1cffzCQohXsu4BaqqAR8F5qMLv4eXa2hZ/view?usp=sharing

## Introduction
Welcome to the **Space Shooter** game! This is an exciting and action-packed game developed as part of the Advanced Programming INT2215 course. In this game, players take control of a spaceship and navigate it to shoot down enemies and avoiding their bullets.

![Screenshot 2024-04-22 110108](https://github.com/dinhdat07/space_shooter/assets/117900502/8e80ea9a-138d-40df-bfa8-3898abc20c4a)

1. [Game Resources](#game-resources)
2. [Source Code Structure](#source-code-structure)
3. [Features](#features)
4. [Installation and Usage](#installation-and-usage)
5. [Acknowledgments](#acknowledgments)

## Game Resources
### Fonts & Graphics
- **Sources**: Acquired from various online repositories.
- **Usage**: Utilized for game interfaces and visual elements.
### Sound & Music
- **Sources**: Parallel Realities.
- **Integration**: Incorporated to enhance the gameplay experience.

## Source Code Structure
### `common.h`
- **Purpose**: Manages essential libraries and shared variables across the program.
### `Game`
- **Components**: important variables for the game (e.g., main objects, sounds, fonts, scores, GUI).
- **Functionality**: Contains functions for game execution, including display of main and instruction screens, and essential game loop operations.
 
### `Entity`
- **Management**: Manages object coordinates (x, y) and movement (dx, dy).
- **Classification**: categorizes and archives object textures.
### `Player` (subclass of `Entity`)
- **Inheritance**: Gains attributes from `Entity`.
- **Enhancements**: variables for input handling (up, down, left, right, fire), state management (reload, enhance, decay, stunt, RGBTimer) and variables for reload rate (reloadRate) and damage rate (damageRate).
### `Enemy` (subclass of `Entity`)
- **Inheritance**: Inherits `Entity` characteristics.
- **Enhancements**: variables for shooting mechanics (reload, fire) and color state tracking (RGBTimer).
### `Effect`
- **Attributes**: Color properties (r, g, b, a) for simplified explosion effect management.
 
### `Button`
- **Basics**: Fundamental variables for position, size, and texture storage.
- **Interaction**: State variable for hover detection (hovered).


## Features
Our game offers a variety of features that make it engaging and fun to play:

- **Boss System**: In Space Shooter, each boss boasts unique skill effects and a menacing appearance. A boss appears every time the player scores 20 points. As the game progresses, bosses become increasingly challenging to defeat, providing an engaging experience for even the most seasoned gamers.
Currently, the Boss system features 3 forms:

1. **Oblivion Overlord**: Fires bullets that inflict substantial damage.

![enemyBoss1](https://github.com/dinhdat07/space_shooter/assets/117900502/232df6b3-aa9d-4335-9d33-1e3010353731)

2. **Nebula Nemesis**: Shoots bullets with the ability to stun, immobilizing the player.

![enemyBoss2](https://github.com/dinhdat07/space_shooter/assets/117900502/75899f52-2c65-475a-b6ea-3159d7db5583)


3. **Galactic Gorgon**: Launches bullets that reduce the player's health to 1 over a certain period. During this time, if the player is hit by another bullet, they will lose.

![enemyBoss3](https://github.com/dinhdat07/space_shooter/assets/117900502/ac30d52b-d639-4fcc-99e7-a57adb1bcf37)

- **Power-ups**: Throughout the game, players can collect power-ups that enhance their spaceship's abilities. These power-ups can give you an edge in combat, making it easier to defeat enemies and progress through the game.
Space Shooter currently offers two power-ups:
1. **Increased Energy**: Players will fire 3 bullets simultaneously instead of a single bullet.
2. **Health Restore**: Players will recover 4 health points.

- **High Score and Hero System**:
The game features a score system where players earn points for each enemy they defeat. Strive to surpass your previous scores to unlock new galactic warriors.
Space Shooter currently features 5 warriors:

1. **Galaxy Guardian**: The initial hero (Damage: 1, Fire rate: 1)

![white](https://github.com/dinhdat07/space_shooter/assets/117900502/3b7285c5-344a-4b27-9f68-4b897c103e20)

2. **Stellar Savior**: (Damage: 1, Fire rate: 2)

![yellow-white](https://github.com/dinhdat07/space_shooter/assets/117900502/7864f724-d89b-4f0e-b161-c7abf93c6e08)

3. **Cosmic Crusader**: (Damage: 3, Fire rate: 1)

![blue](https://github.com/dinhdat07/space_shooter/assets/117900502/38725a25-a32f-4796-8007-ebfba714add1)

4. **Astro Avenger**: (Damage: 3, Fire rate: 2)

![green](https://github.com/dinhdat07/space_shooter/assets/117900502/7bf29d0e-7cc8-4647-998e-4f53f6c8b3c4)

5. **Nebula Knight**: (Damage: 5, Fire rate: 3)

![rship](https://github.com/dinhdat07/space_shooter/assets/117900502/c64dd1a6-2212-4e9e-9c6c-0ce64957c60e)


## Installation and Usage

### Option 1: Game Download Without Source Code
•	Acquisition: Obtain the game in a compressed .rar format directly from the [official release page](https://github.com/dinhdat07/space_shooter/releases).

•	Efficiency: This approach is memory-efficient and expedites the download process, with the file size approximately 4MB.

•	Execution: After downloading, extract the contents to a designated folder and execute SpaceShooter.exe to commence gameplay.

### Option 2: Game Download With Source Code (Compilable)
•	Step 1: Clone the repository to your local machine, use the command `git clone https://github.com/dinhdat07/space_shooter.git`. Alternatively, download a zipped archive of the code by selecting ‘Code’ -> ‘Download Zip’. Code Repository: All source code is located within the src folder. To begin playing immediately, proceed to Step 5.

• Step 2: Visual Studio Setup: Install Visual Studio with the C++ development environment and ensure that the SDL2 libraries are included.

• Step 3: Project Configuration: Open the cloned repository or unzipped code in Visual Studio. Set up the project properties to link against the SDL2 libraries.

• Step 4: Compilation: Use Visual Studio’s built-in compiler to build the project. Address any issues or dependencies that arise during the compilation process.

• Step 5: Game Launch: After a successful build, run the generated SpaceShooter.exe from within Visual Studio to start the game and enjoy the experience.


## Acknowledgments
We would like to express our gratitude to the following:

- The instructors of the Advanced Programming course for their guidance and support throughout the development of this project.
- [andreanlay](https://github.com/andreanlay/space-shooter-sdl2) for his foundational contributions to the codebase, particularly in the development of basic objects and processing functions.
- [Lazyfoo](https://lazyfoo.net/tutorials/SDL/) and [Parallel Realities](https://www.parallelrealities.co.uk/tutorials/#shooter) for providing invaluable instructions and resources that greatly aided the development of this game


Thank you for your interest in my Space Shooter. Enjoy the game!
