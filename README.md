# StealthGAS - Stealth AI + Gameplay Ability System Prototype

A solo UE5 stealth prototype themed around Avatar: The Last Airbender. You play as Zuko in Season 1, Episode 13, infiltrating a Fire Nation base to rescue Aang. 

https://github.com/user-attachments/assets/d87c90ad-194a-4169-bb91-3ec53f8a7b2e

Full design breakdown: https://emilalmazov.framer.website/projects/stealth-gas

## Play It

A packaged Windows build is available on the [Releases page](https://github.com/EmilAlmazov/StealthGAS/releases). Download, unzip, and run the `.exe` file.

## Tech Stack

- **Engine:** Unreal Engine 5.7
- **Languages:** C++ and Blueprints
- **Core Systems:** Gameplay Ability System (GAS), State Tree AI, AI Perception

## Systems Built

- **Stealth AI** - enemies with Patrol, Investigate, and Combat states driven by State Trees
- **Detection system** - sight-based detection via AI Perception with a fill-up detection meter driven via GAS attributes
- **Fire-sense mechanic** - unique enemy type that detects the player's "inner fire" unless the player suppresses their breath, draining a `FireStamina` attribute. This is the **key** mechanic utilising GAS and AI together.
- **Suppress ability** - player holds SHIFT to suppress their inner fire, blocking fire-sense detection at the cost of draining `FireStamina`
- **Other GAS abilities** - sword attack and stealth takedown using Gameplay Tags and Effects
- **Level blockout** - level introduces mechanics one by one:
  - stealth takedown (stationary enemy) → sight detection (patrolling enemy) → fire-sense detection (fire-sense patrolling enemy)

## Controls

| Action | Input |
|--------|-------|
| Move | WASD |
| Look | Mouse |
| Attack | Left Mouse Click |
| Crouch | Hold C |
| Suppress Inner Fire | Hold SHIFT |
| Stealth Takedown | F (before the enemy fully detects you) |
| Quit | ESC |

## Running the Code

This project uses **Git LFS** for large binary files (meshes, textures, audio). A standard GitHub zip download **will not work** - you must clone with Git LFS.

### Step 1: Copy the clone URL

```
https://github.com/EmilAlmazov/StealthGAS.git
```

### Step 2: Clone the repo

| Terminal | GitHub Desktop |
|----------|----------------|
| Run `git lfs install` | Open GitHub Desktop |
| Run `git clone https://github.com/EmilAlmazov/StealthGAS.git` | File → Clone Repository |
| | Paste the URL and click Clone |
| | LFS is handled automatically |

### Step 3: Build and run

Open the `.uproject` file with **Rider** (or for _Visual Studio_, right-click -> `Generate Visual Studio Project Files` -> open `.sln` file), then build and run.

Requires **Unreal Engine 5.7**.

## Asset Attribution

Character assets used in this project (Paragon Kwang, Paragon Minions) are the property of **Epic Games**, originally created for the game *Paragon*, and are used under the [Unreal Engine Content License Agreement](https://www.unrealengine.com/en-US/eula/content). These assets are permitted for use within Unreal Engine projects.

## Author

**Emil Almazov** - Technical Game Designer
- Portfolio: [emilalmazov.framer.website](https://emilalmazov.framer.website/)
- LinkedIn: [linkedin.com/in/emilalmazov](https://linkedin.com/in/emilalmazov)
