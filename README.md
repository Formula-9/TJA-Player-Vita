# TJA-Player-Vita
A work-in-progress Taiko no Tatsujin Simulator for PlayStation Vita.

### Updates
***02/05/2019:*** All header data is now read. However, while testing on a folder containing more than 300 TJA files,
I've noticed that files using non-ANSI encodings (Shift-JIS, UTF formats) tend to have Japanese characters read as *[mojibake][1]*.

***05/05/2019:*** I've started adding a "default skin". To use it, put the files from "skin_default" in "ux0:/data/tjapvita/gfx".
Once the application will be "stable" enough, they will likely be bundled with the VPK.

### Notes
In its current state, this application is not playable yet.
However, by modifying the code slightly, it is possible to test a few things right now.

Another thing to keep into consideration is that the values used in InGameRenderingState for rendering are for sprites extracted
from *Taiko no Tatsujin: V Version*. Due to legal reasons, these files won't be provided. Maybe a way to make skins for the simulator
could be made in the future, but it's not a priority right now. In any case, you're still free to get the required files on your
own if you want to test the application that much.

### Installing
This application requires a PlayStation Vita or a PlayStation TV system capable of running the HENkaku exploit. Compile the
project, and put the vpk on your PlayStation Vita / PlayStation TV system, install it via VitaShell, and a bubble will
appear on the LiveArea that will allow you to launch the game.

[1]: https://en.wikipedia.org/wiki/Mojibake
