# B-OOP-400-REN-4-1-arcade-aurelien.joncour

Arcade is a gaming platform: a program that lets the user choose a game to play and keeps a register of player scores.

**Group members:**
  - [@SimonRacaud](https://github.com/SimonRacaud)
  - [@AurelienJoncour](https://github.com/aurelienjoncour)
  - [@ThomasJouanolle](https://github.com/Axas753)


# INTERFACE SHARING
Graphical and game library interfaces are share with 1 group:

- [@VincentAndrieu](https://github.com/vincent-andrieu) (Groupe Leader)
- [@SullivanGeslot](https://github.com/sullmin)
- [@PolBachelin](https://github.com/memoniak)


# How to run the project

Compile the whole project
```
$> make re
```
Compile graphics libraries
```
$> make graphicals
```
Compile games libraries
```
$> make games
```

You need install the SFML, Ncurses, and SDL2 previously.

Compile the arcade core
```
$> make core
```

Then u can use it

```
$> ./arcade lib/arcade_{lib_name}
```

# Documentation

- Interfaces:
[Interfaces_Documentaion](./doc/Documentation.pdf)

- Class Diagram:
![Class_Diagram](doc/class%20diagram.png)

