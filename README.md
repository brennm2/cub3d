<div align="center">
  <h1>What is this all about?</h1>
</div>

<p>This project is about creating a replication of the famous Wolfenstein 3D (1992)

We needed to create a 2D mini-game/labyrinth and transform it into “3D” using the Ray-Casting algorithm. Obviously, everything needs to be functional and without problems or leaks.
  In addition, as in the [SO_LONG](https://github.com/brennm2/so_long) project, we need to have strong parsing for the map, because in it, the player can create it, modify textures and even change the color of the ceiling and floor.
  
<p>Our game is inspired by, of course, DOOM (1993), and for me, it was a proof of concept and study in optimizing code and graphics to get the best performance and use of available resources, i.e. the highest possible FPS.
<div align="center">
  <img src="">
</div>


<div align="center">
  <h1>How can I test it?</h1>
</div>
<div align="center">
<p>I'm glad you asked! The process is very simple.</p>
</div>
<div align="center">
  <img src="https://i.imgur.com/vwyPraS.png">
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
- The map can only use the following characters: 1, 0, [SPACE], [N,S,W,E] and D -> (D is for Doors in bonus)
- The map extension must be ".cub"
```
<br>
<br>
<p>Here's a simple example:</p>

```bash
11111111111
1000E0CX001
1000P00C001
10011111001
1X0CX0X0011
1000C000001
10011111001
100C0000001
1000C000X01
11111111111
```
<br>
<br>



