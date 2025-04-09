# This is SeaBattle
## to build it:
```
mkdir build
cd build
cmake ..
make
```
## to play it:
1. WASD - to move pointer/change field size;
2. ENTER - to attack/scan/confirm;
3. E - to rotate field/pointer/use ability(scan/double damage/shelling);
4. Q - to skip positioning ships/set default field size;
5. 1 - to save game;
6. 2 - to load game anywhere;
#### you can change controls in game/data/controls.json
#### if you want to use TUI change in main.cpp to SeaBattle<TUIInput, TUIOutput> and recompile project
#### if you want to change setting of game go to game/src/utilities/settings.h change and recompile project.
##### also i like my log chat
