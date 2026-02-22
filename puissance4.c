// gcc -Wall -o puissance4 puissance4.c && ./puissance4




#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int min_max(unsigned char **tab, unsigned char profondeur, unsigned char actual_player);

// checking values
bool checking_value(unsigned char value, unsigned char minimum_value, unsigned char maximum_value) {
	if (value < minimum_value || value > maximum_value) {
		return false;
	}
	return true;
}

// creation of a array and memory allocation
unsigned char **CreateArray(unsigned char lines_number, unsigned char columns_number){
	unsigned char **tab = (unsigned char **)malloc(lines_number * sizeof(unsigned char *));
	if (tab == NULL) {
		printf("Erreur d'allocation mémoire\n");
		return NULL; 
	}
	for (unsigned char i = 0; i < lines_number; i++){
		tab[i] = (unsigned char *)malloc(columns_number * sizeof(unsigned char));
		if (tab[i] == NULL){
			printf("Erreur d'allocation mémoire\n");
			return NULL;
		}
	}
	return tab;
}

// liberation of the memory allocation 
void freeArray(unsigned char **tab, unsigned char lines_number) {
    for (unsigned char i = 0; i < lines_number; i++) {
        free(tab[i]);
    }
    free(tab);
}

// array filling
void fillArray(unsigned char **tab, unsigned char lines_number, unsigned char columns_number){
	for (unsigned char i = 0; i <lines_number; i++) {
		for (unsigned char j = 0; j < columns_number; j++){
			tab [i][j] = 0; 
		}
	}
}


// return player poster
char* Pion(unsigned char **tab, unsigned char lines_number, unsigned char columns_number) {
	if (tab[lines_number][columns_number] == 1) {
		return "X";
	}
	if (tab[lines_number][columns_number] == 2) {
		return "O";
	}
	if (tab[lines_number][columns_number] == 0) {
		return " "; 
	}
	else {
		printf("Il y semble avoir une erreur dans l'assignation de la valeur dans le tableau");
		return "P";
	}
}


// reading of the array
void reading(unsigned char **tab, unsigned char lines_number, unsigned char columns_number) {
	char* value;
	printf("-----------------------------\n");
	for (unsigned char i = 0; i< lines_number; i++) {
		printf("|");
		for (unsigned char j = 0; j < columns_number; j++) {
			value = Pion(tab,i,j);
			printf(" %s |",value);
		}
		printf("\n");
	}
	printf("  1   2   3   4   5   6   7\n");
}

// the player choose the columns
unsigned char player_choice() {
	unsigned char choice;
	printf("Veuillez choisir le numéro d'une colonne\n"); 
	scanf("%hhu", &choice);
	choice = choice - 1; // on enlève 1 pour correcpondre au tableau
	return choice; // correspond à la colonne du tableau 
}

// the player plays
unsigned char player_turn(unsigned char **tab, unsigned char lines_number, unsigned char columns_number, unsigned char player) {
	unsigned char columns;
	bool ok = false;
	bool check = false;
	do {
		do {
			columns = player_choice();
			check = checking_value(columns, 0, columns_number);
		} while (check == false); 
		if (tab[0][columns] == 0) {
			ok = true;
		}
		else { 
			printf("la colonne est pleine...\n");
		}
	} while (ok == false);
	for (int row = lines_number -1; row >= 0 ; row--) {
		if (tab[row][columns] == 0){
			tab[row][columns] = player;
			return **tab;
		}
	}
	printf("Problème dans la fonction player_choice\n");
	return 0;
}

// fonction pour vérifier si un joueur à gagner en horizontale, verticale et diagonale des deux sens \ ou / 
bool win(unsigned char **tab, unsigned char lines_number, unsigned char columns_number, unsigned char player) {
	// honrizontale verirfiaction
	for (unsigned char i = 0; i < lines_number; i++) {
		for (unsigned char j = 0; j < (columns_number - 3); j++) {
			if ((tab[i][j] == player) && (tab[i][(j+1)] == player) && (tab[i][(j+2)] == player) && (tab[i][(j+3)]) == player) {
				return true;
			}
		}
	}
	// vertical verirication
	for (unsigned char x = 0; x < columns_number; x++) {
		for (unsigned char y = (lines_number - 1); y >= 3; y--) {
			if ((tab[y][x] == player) && (tab[(y-1)][x] == player) && (tab[(y-2)][x] == player) && (tab[(y-3)][x]) == player) { 
				return true;
			}
		}
	}
	// \ verification
	for (unsigned char i = 0; i < (lines_number-3); i++) {
		for (unsigned char j = 0; j < (columns_number - 3); j++) {
			if ((tab[i][j] == player) && (tab[i+1][(j+1)] == player) && (tab[i+2][(j+2)] == player) && (tab[i+3][(j+3)]) == player) {
				return true;
			}
		}
	}
	// / verification
	for (unsigned char i = 0; i < (lines_number - 3); i++) {
		for (unsigned char j = 4; j < columns_number; j++) {
			if ((tab[i][j] == player) && (tab[i+1][(j-1)] == player) && (tab[i+2][(j-2)] == player) && (tab[i+3][(j-3)]) == player) {
				return true;
			}
		}
	}
	return false;

}

bool tab_full(unsigned char **tab, unsigned char lines_number, unsigned char columns_number) {
	for (unsigned char i = 0; i < columns_number; i++) {
		if (tab[0][i] == 0) {
			return false;
		}
	}
	return true;
}

int count_score(unsigned char **tab, unsigned char player) {
	unsigned char columns_number = 7;
	unsigned char lines_number = 6;
	unsigned char score[6][7] = {{3,4,5,7,5,4,3},{4,6,8,10,8,6,4}, {5,8,11,13,11,8,5},{5,8,11,13,11,8,5},{4,6,8,10,8,6,4},{3,4,5,7,5,4,3}};
	int somme =0;
	for (unsigned char i=0; i < 6; i++) {
		for (unsigned char j=0; j < 7; j++) {
			if (tab[i][j] == player) {
				somme = somme + score[i][j];
			}
		}
	}
	// verification for 4 
	// honrizontale verirfiaction
	for (unsigned char i = 0; i < lines_number; i++) {
		for (unsigned char j = 0; j < (columns_number - 3); j++) {
			if ((tab[i][j] == player) && (tab[i][(j+1)] == player) && (tab[i][(j+2)] == player) && (tab[i][(j+3)]) == player) {
				somme += 10;
			}
		}
	}
	// vertical verirication
	for (unsigned char x = 0; x < columns_number; x++) {
		for (unsigned char y = (lines_number - 1); y >= 3; y--) {
			if ((tab[y][x] == player) && (tab[(y-1)][x] == player) && (tab[(y-2)][x] == player) && (tab[(y-3)][x]) == player) { 
				somme += 10;
			}
		}
	}
	// \ verification
	for (unsigned char i = 0; i < (lines_number-3); i++) {
		for (unsigned char j = 0; j < (columns_number - 3); j++) {
			if ((tab[i][j] == player) && (tab[i+1][(j+1)] == player) && (tab[i+2][(j+2)] == player) && (tab[i+3][j+3] == player)) {
				somme += 10;
			}
		}
	}
	// / verification
	for (unsigned char i = 0; i < (lines_number - 3); i++) {
		for (unsigned char j = 4; j < columns_number; j++) {
			if ((tab[i][j] == player) && (tab[i+1][(j-1)] == player) && (tab[i+2][(j-2)] == player) && (tab[i+3][(j-3)]) == player) {
				somme += 10;
			}
		}
	}
	// veririfation for 3
	// honrizontale verirfiaction
	for (unsigned char i = 0; i < lines_number; i++) {
		for (unsigned char j = 0; j < (columns_number - 2); j++) {
			if ((tab[i][j] == player) && (tab[i][(j+1)] == player) && (tab[i][(j+2)] == player)) {
				somme += 5;
			}
		}
	}
	// vertical verirication
	for (unsigned char x = 0; x < columns_number; x++) {
		for (unsigned char y = (lines_number - 1); y >= 2; y--) {
			if ((tab[y][x] == player) && (tab[(y-1)][x] == player) && (tab[(y-2)][x] == player)) { 
				somme += 5;
			}
		}
	}
	// \ verification
	for (unsigned char i = 0; i < (lines_number-2); i++) {
		for (unsigned char j = 0; j < (columns_number - 2); j++) {
			if ((tab[i][j] == player) && (tab[i+1][(j+1)] == player) && (tab[i+2][(j+2)] == player)) {
				somme += 5;
			}
		}
	}
	// / verification
	for (unsigned char i = 0; i < (lines_number - 2); i++) {
		for (unsigned char j = 2; j < columns_number; j++) {
			if ((tab[i][j] == player) && (tab[i+1][(j-1)] == player) && (tab[i+2][(j-2)] == player)) {
				somme += 5;
			}
		}
	}
	// veririfation for 2
	// honrizontale verirfiaction
	for (unsigned char i = 0; i < lines_number; i++) {
		for (unsigned char j = 0; j < (columns_number - 1); j++) {
			if ((tab[i][j] == player) && (tab[i][(j+1)] == player)) {
				somme += 3;
			}
		}
	}
	// vertical verirication
	for (unsigned char x = 0; x < columns_number; x++) {
		for (unsigned char y = (lines_number - 1); y >= 1; y--) {
			if ((tab[y][x] == player) && (tab[(y-1)][x] == player)) { 
				somme += 3;
			}
		}
	}
	// \ verification
	for (unsigned char i = 0; i < (lines_number-1); i++) {
		for (unsigned char j = 0; j < (columns_number - 1); j++) {
			if ((tab[i][j] == player) && (tab[i+1][(j+1)] == player)) {
				somme += 3;
			}
		}
	}
	// / verification
	for (unsigned char i = 0; i < (lines_number - 1); i++) {
		for (unsigned char j = 1; j < columns_number; j++) {
			if ((tab[i][j] == player) && (tab[i+1][(j-1)] == player)) {
				somme += 3;
			}
		}
	}
	return somme; 
}

unsigned char get_first_row(unsigned char **tab, unsigned char columns) {
	for (int i = 5; i >= 0; i--) {
		if (tab[i][columns] == 0) {
			return i;
		}
	}
	return 55; // the columns is full
}

int evaluate_board(unsigned char **tab) {
    int score_IA = count_score(tab, 2);
    int score_player = count_score(tab, 1);
    return score_IA - score_player;
}

int min_max( unsigned char **tab, unsigned char profondeur, unsigned char actual_player) {
	unsigned char row;
	int best_score;
	unsigned char IA = 2;
	unsigned char player = 1;
	if (win(tab, 6, 7, 2)) { // if IA win
    		return 10000;
	}
	if (win(tab, 6, 7, 1)) { // if the player win
    		return -10000;
	}
	if ((profondeur == 0) ||(tab_full(tab, 6,7) == true)) {
		return evaluate_board(tab);
	}
	if (actual_player == 2) {
		best_score = -1000;
		for (unsigned char i=0; i < 7; i++) {
			row = get_first_row(tab, i);
			if (row != 55) {
				tab[row][i] = IA;
				int score = min_max(tab, (profondeur - 1), player);
				tab[row][i] = 0;
				if (score > best_score) {
					best_score = score;
				}
			}
		}
		return best_score;
	}
	if (actual_player == player) {
		int worse_score = 1000;
		for (unsigned char i=0; i < 7; i++) {
			row = get_first_row(tab, i);
			if (row != 55) {
				tab[row][i] = player;
				int score = min_max(tab, (profondeur - 1), IA);
				tab[row][i] = 0;
				if (score < worse_score) {
					worse_score = score;
				}
			}
		}
		return worse_score;
	}
	return 0;
}

unsigned char best_shot(unsigned char **tab,unsigned char profondeur) {
	int best_score = (-10000);
	unsigned char best_columns = 44;
	int score;
	unsigned char row;
	for (unsigned char i=0; i < 7; i++) {
		row = get_first_row(tab, i);
		if (row != 55) {
			tab[row][i] = 2;
			score = min_max(tab, (profondeur -1), 1);
			tab[row][i] = 0;
			if (score > best_score) {
				best_score = score;
				best_columns = i;
			}
		}
	}
	return best_columns;
}


int main(void) {
    const unsigned char LINES = 6;
    const unsigned char COLUMNS = 7;
    unsigned char **board = CreateArray(LINES, COLUMNS);
    if (board == NULL) {
        return 1;
    }
    fillArray(board, LINES, COLUMNS);
    
    reading(board, LINES, COLUMNS);
    
    int game_over = 0;
    int turn = 1; // 1 pour le joueur humain (X), 2 pour l'IA (O)
    
    while (!game_over) {
        if (turn == 1) {
            // Tour du joueur humain
            printf("Tour du joueur (X) :\n");
            player_turn(board, LINES, COLUMNS, 1);
            reading(board, LINES, COLUMNS);
            if (win(board, LINES, COLUMNS, 1)) {
                printf("Le joueur gagne !\n");
                game_over = 1;
                break;
            }
        } else {
            // Tour de l'IA
            printf("Tour de l'IA (O) :\n");
            unsigned char ai_col = best_shot(board, 5);
            if (ai_col == 44) {  // 44 indique qu'aucun coup n'est valide
                printf("Aucun coup valide pour l'IA !\n");
                game_over = 1;
                break;
            }
            unsigned char row = get_first_row(board, ai_col);
            if (row == 55) {
                printf("La colonne est pleine, l'IA ne peut pas jouer.\n");
            } else {
                board[row][ai_col] = 2;
                printf("L'IA joue en colonne %d.\n", ai_col + 1);
                reading(board, LINES, COLUMNS);
                if (win(board, LINES, COLUMNS, 2)) {
                    printf("L'IA gagne !\n");
                    game_over = 1;
                    break;
                }
            }
        }
        if (tab_full(board, LINES, COLUMNS)) {
            printf("Match nul !\n");
            break;
        }
        // Changement de tour
        turn = (turn == 1) ? 2 : 1;
    }
    
    freeArray(board, LINES);
    return 0;
}

