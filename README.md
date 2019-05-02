# TJA-Player-Vita
A work-in-progress Taiko no Tatsujin Simulator for PlayStation Vita.

### Updates
***02/05/2019:*** All header data is now read. However, while testing on a folder containing more than 300 TJA files,
I've noticed that files using non-ANSI encodings (Shift-JIS, UTF formats) tend to have Japanese characters read as *[mojibake][1]*.
I'll be working on fixing this issue as part of the next commit.

### Notes
In its current state, this application is not playable yet. At best, by modifying the code, you could log all the TJA
files that are in the folder represented by DEFAULT_TJA_PATH in Constants.c.

Another thing to keep into consideration is that the values used in InGameRenderingState for rendering are for sprites extracted
from *Taiko no Tatsujin: V Version*. Due to legal reasons, these files won't be provided. Maybe a way to make skins for the simulator
could be made in the future, but it's not a priority right now. In any case, you're still free to get the required files on your
own if you want to test the application that much.

### Installing
This application requires a PlayStation Vita or a PlayStation TV system capable of running the HENkaku exploit. Compile the
project, and put the vpk on your PlayStation Vita / PlayStation TV system, install it via VitaShell, and a bubble will
appear on the LiveArea that will allow you to launch the game.

[1]: https://en.wikipedia.org/wiki/Mojibake
