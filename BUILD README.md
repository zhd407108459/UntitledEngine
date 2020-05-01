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
Credits:
PickUp.wav - pcmac        Link: https://freesound.org/people/pcmac/sounds/464529/
Death.wav - AlineAudio    Link: https://freesound.org/people/AlineAudio/sounds/416839/
ShootBullet.wav - mdl_03  Link: https://freesound.org/people/mdl_03/sounds/209554/
Win.wav - Mativve         Link: https://freesound.org/people/Mativve/sounds/391535/
-------------------------
Build instructions:
Recommend Visual Studio 2019(Didn't try other versions)
Build under Debug/Release(better performance) and x86.
Don't include any special character such as "," in the file path which might cause problems.

The solution should already be set properly. But just in case, the setting in C/C++ and Linker should be like these:

C/C++ -> Additional Include Directories: 
$(SolutionDir)Dependencies\GLFW\include
$(SolutionDir)Dependencies\GLEW\include
$(SolutionDir)Dependencies\include

Linker -> Additional Library Directories:
$(SolutionDir)Dependencies\GLEW\lib\Release\Win32
$(SolutionDir)Dependencies\GLFW\lib-vc2019
$(SolutionDir)Dependencies\lib

Linker -> Addtional Dependencies:
irrKlang.lib;
SOIL.lib;
glew32s.lib;
glfw3.lib;
opengl32.lib;
....(default ones)

