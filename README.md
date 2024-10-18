<div align="center">
  <img src="https://i.imgur.com/vwyPraS.png">
</div>

<div align="center">
  <h1>What is this all about?</h1>
</div>

<p>This project is about creating a replication of the famous Wolfenstein 3D (1992)

We needed to create a 2D mini-game/labyrinth and transform it into “3D” using the Ray-Casting algorithm. Obviously, everything needs to be functional and without problems or leaks.
  In addition, as in the [SO_LONG](https://github.com/brennm2/so_long) project, we need to have strong parsing for the map, because in it, the player can create it, modify textures and even change the color of the ceiling and floor.
  
<p>Our game is inspired by, of course, DOOM (1993), and for me, it was a proof of concept and study in optimizing code and graphics to get the best performance and use of available resources, i.e. the highest possible FPS.

  To put it simply, the aim of the project is: transform map (text / 2D) into “3D” objects and textures. All using rays and perspective.
  <div align="center">
  <p><h3>Just like that: </h3> 
  <div>
  <img src="https://github.com/user-attachments/assets/f2a0b67c-85a5-4b29-b982-0cfd759a4e25"style="width:60%">
  </div>
  </div>


  
  



<div align="center">
  <h1>How can I test it?</h1>
</div>
<div align="center">
<p>I'm glad you asked! The process is very simple.</p>
</div>
<br>
<h4>1º Step - Download the files:</h4>

```bash
git clone https://github.com/brennm2/cub3d.git | cd cub3d
```

<h4>2º Step - Compiling the program(You wil need the Minilibx (make update))</h4>

```bash
make update
make
```
I recommend playing on bonus, so:
```bash
make update
make bonus
```
<br>
<h4>3º Step - Running the game!</h4>

Now you need to put in the following inputs:<br>
- cub3d version (cub3d_bonus or cub3d)<br>
- Map directory (assets/map_files/valid/...)<br>
```bash
./cub3d_bonus assets/map_files/valid/dungeon_bonus.cub
```

<h4>4º Step - Playing the game!</h4>

- You can move your character with the <strong>[WASD]</strong> keys
- You can change the direction with the <strong>[ARROW]</strong> keys or <strong>[MOUSE]</strong>
- You open the map with <strong>[M]</strong> key
- You open the doors with <strong>[E]</strong> key
- If you want to stop playing, just press <strong>[ESC]</strong> or close the window with the <strong>X</strong> button.
<br>

<div align="center">
  <img src="https://github.com/user-attachments/assets/3173cdc9-8a4b-48fa-8610-86cd80eca81e">
</div>


<div align="center">
  <h1>Considerations and Explanations</h1>
</div>

<div align="center">
<h3>--------- The Map ---------</h3>
</div>
<br>
<p>The map can be modified, altered or even created in a simple and functional way, as long as it follows these rules:</p>

```bash
- Only have ONE Player and depending on the letter, which direction will you look when you start the game ([N][S][W][E])
- It has to got a valid RGB value for Floor[F] and Ceiling[C] (No duplicated or invalid RGB value)
- It has to got a valid texture PATH (No duplicated paths or invalid path)
- It has to be enclosed by Walls (1)
- And it needs to be filled with floors (0)
- It can be on any shape, but it HAS to be closed by wall
- The map can only use the following characters: 1, 0, [SPACE], [N,S,W,E] and D -> (D is for Doors only in bonus)
- The map extension must be ".cub"
```
<br>
<br>
<p>Here's a simple example:</p>

```bash
NO assets/sprites/default/north_wall.xpm
SO assets/sprites/default/south_wall.xpm
WE assets/sprites/default/west_wall.xpm
EA assets/sprites/default/east_wall.xpm

F 18,53,25
C 153,204,255

111111111
100000001
1000W0001
100000001
111111111
```
<br>
<br>
<div align="center">
<h3>--------- 42 Rules ---------</h3>
</div>
<br>
<p>In every project we must follow certain rules, here are the rules for this project:</p>

```bash
- The project must not have memory leaks
- The project must use the flags -Wall -Wextra -Werror
- Each function can have a maximum of 25 lines
- Each file should only have 5 functions
- We should keep the code as clean as possible, for example, declarations should be on separate lines
- We cannot use "for", "do...while", "switch", "case", "goto", ternary operators, or variable-length arrays
```

<br>
<br>
<div align="center">

<h3>--------- Credits ---------</h3>
</div>

* My awesome duo in this project: [Bruno](https://github.com/Bruno0798)
* [Textures](https://little-martian.itch.io/retro-texture-pack) and little of handwork of me
* [Ray-Casting]
*   - [Ahmed Fatir](https://medium.com/@afatir.ahmedfatir/cub3d-tutorial-af5dd31d2fcf) (Cub3d Tutorial)
    - [Lode's Computer Graphics Tutorial](https://lodev.org/cgtutor/raycasting.html#The_Basic_Idea_)
* All my friends who helped me do this project


