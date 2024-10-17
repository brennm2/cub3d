<div align="center">
  <h1>What is this all about?</h1>
</div>

<p>Esse projeto e sobre criar uma replica do famoso wolfenstein 3D (1992)

<p>Voce precisa criar um mini-jogo/labirinto em 2D e transforma-lo em "3D" usando o algoritimo de Ray-Casting. Obviamente, tudo precisa ser funcional e sem problemas ou leaks.
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
