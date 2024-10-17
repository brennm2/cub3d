<div align="center">
  <h1>What is this all about?</h1>
</div>

<p>This project is about creating a replication of the famous Wolfenstein 3D (1992)

<p>We needed to create a 2D mini-game/labyrinth and transform it into “3D” using the Ray-Casting algorithm. Obviously, everything needs to be functional and without problems or leaks.
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



