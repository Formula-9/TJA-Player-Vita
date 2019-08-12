# TJA-Player-Vita
A work-in-progress Taiko no Tatsujin Simulator for PlayStation Vita.

### Updates

***12/08/2019:*** Big rewrite, the application will still use Vita2D for rendering, and audio playback
will be done with SDL2 (with Mixer). Also, chart search is done on start on another thread, which
allows the main thread to display a "Now Loading" message on the screen!

### Notes
In its current state, this application is not playable yet.
However, by modifying the code slightly, it is possible to test a few things right now.

### Installing
This application requires a PlayStation Vita or a PlayStation TV system capable of running the HENkaku exploit. Compile the
project, and put the vpk on your PlayStation Vita / PlayStation TV system, install it via VitaShell, and a bubble will
appear on the LiveArea that will allow you to launch the game.

[1]: https://en.wikipedia.org/wiki/Mojibake
