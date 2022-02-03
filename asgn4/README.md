# John Conway's Game of Life

Game of Life is a 0 player game, where the only input necessary is the location of the starting cell. The game is played on a specified grid, with the cells inside are either alive or dead.

## Usage

Program is initiated by the following command-line command: 

`./life`

bellow are the possible command-line options:
> **Required**

`-i [file]`

specifies what is the input file to the program. The input file should include the grid dimensions on the first line, and the positions of the *alive* cells on the subsequent lines.

> **Optional**

`-s`

silences ***ncurses***, which show the resulting game program on a screen

`-t`

toggles ***toroidal*** mode on, in which the universe wraps around itself, rather than being confined by bounds

`-n [generations]`
 
specifies the number of generations/steps the game is going to go over. The default is **100**

`-o [file]`

specifies the output file, in which the final state of the universe is printed out, instead of the console

## Info

Created by Martin Michalko for CSE13s Assignement 4, in Winter of 2022
