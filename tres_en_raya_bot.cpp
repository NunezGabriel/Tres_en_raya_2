#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
using namespace std;

int main() {
	srand(time(0));
	int positions[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
	int games[3] = {0, 0, 0}; // numero de juegos ya jugados (empates, gana 1, gana 2)
	int player;
	int change; // guardar el num de la casilla que juega el jugador
	int game_state = 0;
	int bot = 0;
	int bot2 = 0;
	int difficulty;
	string name;
	string replay;
	char char1;
	char char2;
	bool focus = true;
	cout << "Tres en Raya\n\n";
	cout << "Nombre del jugador: ";
	cin >> name;
	while (focus) {
		cout << "Que simbolo quieres? (X/O): ";
		cin >> char1;
		if (char1 == 'X') {
			char2 = 'O';
			focus = false;
		}
		else if (char1 == 'O') {
			char2 = 'X';
			focus = false;
		}
		else {
			cout << "Ese simbolo no es valido\n";
		}
	}	
	focus = true;
	while (focus) {
		cout << "\nFacil: 1\nDificil: 2\nEscoge una dificultad (1/2): ";
		cin >> difficulty;
		if (difficulty != 1 && difficulty != 2) {
			cout << "Ese valor no es valido\n";
		}
		else {
			focus = false;
		}
	}
	focus = true;
	char chars[3] = {' ', char1, char2};
	cout << "\n";
    for (int c = 0; c <= 8; c++) { // imprime el tablero tutorial
		cout << "  " << c + 1 << "  ";
		if (c == 8) {
			cout << " ";
		}
		else if ((c + 1) % 3 == 0) {
			cout << "\n-----------------\n";
		}
		else {
			cout << "!";
		}
	}
	cout << "\n\nPara jugar ingresa el numero de una casilla\n\n";
	while (focus) {
		for (int a = 1; a <= 9 && game_state == 0; a++) {  //cada vez que este bucle se repite es un turno
			player = ((a - 1) % 2) + 1; //alterna entre 1 y 2 cada turno
			for (int c = 0; c <= 8 && player == 1; c++) {
				cout << "  " << chars[positions[c]] << "  ";
				if (c == 8) {
					cout << " ";
				}
				else if ((c + 1) % 3 == 0) {
					cout << "\n-----------------\n";
				}
				else {
					cout << "!";
				}
			}
			if (player == 1) { //pide input si es el turno del jugador
				cout << "\n\nTurno de " << name << ": ";
				cin >> change;
			}
			else {
				if (difficulty == 2) {
					switch (a) {
					case 2:
						if (positions[4] == 0) {
							change = 5;
						}
						else {
							while (positions[change - 1] != 0) {
								change = (rand() % 5) * 2 + 1;
							}
						}
						break;
					default:
						if (bot != 0 && positions[bot - 1] == 0) {
							change = bot;
						}
						else if (bot2 != 0 && positions[bot2 - 1] == 0) {
							change = bot2;
						}
						else {
							while (positions[change - 1] != 0) {
								change = (rand() % 9) + 1;
							}
						}
						break;
					}
				}
				else {
					while (positions[change - 1] != 0) {
						change = (rand() % 9) + 1;
					}
				}
				bot = 0;
				bot2 = 0;
				cout << "Turno del BOT: " << change << "\n\n";
			}
			//checkea si un espacio está ocupado
			if ((1 <= change) && (positions[change - 1] == 0) && (change <= 9)) {
				positions[change - 1] = player;
			}
			else {
				a -= 1;
				cout << "\nNo es valido\n\n";
			}
			// checkea si alguien ganó
			for (int b = 0; b <= 8; b++) { //columnas
				if (positions[b] == player && positions[(b + 3) % 9] == player) {
					if (positions[(b + 6) % 9] == player) {
						game_state = player;
					}
					else {
						if (bot == 0) {
							bot = ((b + 6) % 9) + 1;
						}
						else if (bot2 == 0) {
							bot2 = ((b + 6) % 9) + 1;
						}
					}
				}
			}
			for (int b = 0; b <= 8; b++) {  //filas
				if (positions[b] == player && positions[(b + 1) % 3 + 3 * (b / 3)] == player) {
					if (positions[(b + 2) % 3 + 3 * (b / 3)] == player) {
						game_state = player;
					}
					else {
						if (bot == 0) {
							bot = (b + 2) % 3 + 3 * (b / 3) + 1;
						}
						else if (bot2 == 0) {
							bot2 = (b + 2) % 3 + 3 * (b / 3) + 1;
						}
					}
				}
			}
			for (int b = 0; b <= 8; b += 4) {  //diagonales
				if (positions[b] == player && positions[(b + 4) % 12] == player) {
					if (positions[(b + 8) % 12] == player) {
						game_state = player;
					}
					else {
						if (bot == 0) {
							bot = (b + 8) % 12 + 1;
						}
						else if (bot2 == 0) {
							bot2 = (b + 8) % 12 + 1;
						}
					}
				}
			}
			if (positions[2] == player && positions[4] == player) {
				if (positions[6] == player) {
					game_state = player;
				}
				else {
					if (bot == 0) {
						bot = 7;
					}
					else if (bot2 == 0) {
						bot2 = 7;
					}
				}
			}
			else if (positions[2] == player && positions[6] == player) {
				if (positions[4] == player) {
					game_state = player;
				}
				else {
					if (bot == 0) {
						bot = 5;
					}
					else if (bot2 == 0) {
						bot2 = 5;
					}
				}
			}
			else if (positions[4] == player && positions[6] == player) {
				if (positions[2] == player) {
					game_state = player;
				}
				else {
					if (bot == 0) {
						bot = 3;
					}
					else if (bot2 == 0) {
						bot2 = 3;
					}
				}
			}
		}
		cout << "\n";
		for (int c = 0; c <= 8; c++) {
			cout << "  " << chars[positions[c]] << "  ";
			if (c == 8) {
				cout << " ";
			}
			else if ((c + 1) % 3 == 0) {
				cout << "\n-----------------\n";
			}
			else {
				cout << "!";
			}
		}
		focus = false;
		if (game_state == 0) {   //verificar el estado del juego
			cout << "\n\nEs un empate";
		}
		else if (game_state == 1) {
			cout << "\n\nGana " << name;
		}
		else {
			cout << "\n\nGana el BOT";
		}
		games[game_state] += 1;
		cout << "\a\n\nQuieres jugar de nuevo? (si/no): ";
		cin >> replay;
		if (replay == "si") 
		{
			focus = true;
			for (int d = 0; d <= 8; d++) {
				positions[d] = 0;
			}
			game_state = 0;
			cout << "\nEstas jugando de nuevo\n\n";
/*			replay = names[0];
			names[0] = names[1];
			names[1] = replay;
			char1 = chars[1];
			chars[1] = chars[2];
			chars[2] = char1;
			change = games[1];
			games[1] = games[2];
			games[2] = change;*/
		}
	}
	cout << "\nFin del juego\n\nEmpates: " << games[0] << "\n" << name << " gano: " << games[1] << "\nEl BOT gano: " << games[2] << "\n\nTotal: " << games[0] + games[1] + games[2];
	return 0;
}
