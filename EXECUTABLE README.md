# UntitledEngine

Team members: Huadong Zhang, Rongyi Zhao
-------------------------
Used libraries & API:
Rendering: We used SOIL for rendering images.
Link: https://www.lonesock.net/soil.html

Input: We used XInput for controller inputs.
Link: https://docs.microsoft.com/en-us/windows/win32/xinput/getting-started-with-xinput

Audio: We used irrKlang for audio.
Link: https://www.ambiera.com/irrklang/downloads.html
-------------------------
Art: Made by Huadong Zhang
-------------------------
Credits:
PickUp.wav - pcmac        Link: https://freesound.org/people/pcmac/sounds/464529/
Death.wav - AlineAudio    Link: https://freesound.org/people/AlineAudio/sounds/416839/
ShootBullet.wav - mdl_03  Link: https://freesound.org/people/mdl_03/sounds/209554/
Win.wav - Mativve         Link: https://freesound.org/people/Mativve/sounds/391535/
-------------------------
Required Controller: XBox One Controller
-------------------------
Control:

Gamepad:
Move  - Left Joystick
Aim   - Right Joystick
Shoot - RT

Keyboard:
Move    - WASD
Shoot   - Space
Restart - T
-------------------------
Rules:
The player and enemies will die if they are hit by bullets.
The player will win after eliminating all the enemies.
The player will lose after death.
The player can pick up items by walking on them, including pistol, assault rifle, ammo supply.
-------------------------
How to edit the scene:
In data\scene.txt, the two numbers of the first line mean the world position of the first object.
(Since the camera will follow the player, this setting is not important.)
From the second line to the end, each line represents one line of objects' information.
For each line, one character represents the information about that location.
1 = Player
2 = Enemy
3 = Wood Tile Obstacle
4 = Iron Tile Obstacle
5 = Pistol
6 = Assault Rifle
7 = Ammo Supply
0 or - or something else = Empty