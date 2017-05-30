Juego de la vida
================
Usage:
	[-h|--help]
	[-x|--size_x <num>
	[-y|--size_y <num>
	[-i|--init <init_mode>
	[-s|--save_file <file>
	[-r|--restore_file <file>	
	[file]

	initialization modes: 
	default
	glider
	random

Exemples: 
./game_of_life -x 30 -y 30 -i glider 

./game_of_life -x 20 -y 20 -i random

./game_of_life -x 20 -y 20 -i glider -s game.txt

./game_of_life -r game.txt

./game_of_life config.txt
