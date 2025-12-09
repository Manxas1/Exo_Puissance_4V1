#include <iostream>
#include<locale.h>
#include <windows.h>
//-------------------
//Fonction affichage
//-------------------
void lirePlateau(int tab[6][7])
{
	system("cls");
	printf("Voici le plateau: \n");
	printf("\t \t \t  -----------------------------\n");
	for (int x = 5; x >= 0; x--)
	{
		printf("\t\t\t%d | ", x + 1);
		for (int y = 0; y < 7; y++)
		{
			if (tab[x][y] == 1)
				printf("\033[31m●\033[0m | ");
			if (tab[x][y] == 2)
				printf("\033[34m●\033[0m | ");
			if (tab[x][y] == 0)
				printf("  | ");
		}

		printf("\n \t \t \t  -----------------------------\n");
	}
	printf("\t \t \t    1   2   3   4   5   6   7    \n");


}

//-------------------
//fonctions lecture
//-------------------
int lireColonne()
{
	int colonne = 0;
	do {
		printf("Quelle colonne? (1-7)\n");

		if (scanf_s("%d", &colonne) != 1)
		{
			printf("ce nombre est ou incorrect veuillez choisir un nombre entre 1 et 7\n");
			while ((getchar()) != '\n');
			continue;
		}

		if (colonne > 7 || colonne < 1)
		{
			printf("Nombre hors limite, recommencez.\n");
			while ((getchar()) != '\n');
		}

	} while (colonne > 7 || colonne < 1);
	while ((getchar()) != '\n');
	return colonne - 1;
}

//------------------------------
//Placement du pion
//------------------------------
int placerPion(int plateau[6][7], int colonne, int joueur)
{
	for (int i = 0; i < 6; i++)
	{
		if (plateau[i][colonne] == 0)
		{
			plateau[i][colonne] = joueur;
			return 1; 
		}
	}
	return 0; 
}
//-------------------------------
// isPuissance4?
// -------------------------------
int isPuissance4(int plateau[6][7])
{
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 7; j++) {

			int joueur = plateau[i][j];
			if (joueur == 0) continue;

			// Horizontal 
			if (j <= 3 &&
				plateau[i][j + 1] == joueur &&
				plateau[i][j + 2] == joueur &&
				plateau[i][j + 3] == joueur)
				return joueur;

			// Vertical 
			if (i <= 2 &&
				plateau[i + 1][j] == joueur &&
				plateau[i + 2][j] == joueur &&
				plateau[i + 3][j] == joueur)
				return joueur;

			// Diagonales 
			if (i <= 2 && j <= 3 &&
				plateau[i + 1][j + 1] == joueur &&
				plateau[i + 2][j + 2] == joueur &&
				plateau[i + 3][j + 3] == joueur)
				return joueur;

			if (i >= 3 && j <= 3 &&
				plateau[i - 1][j + 1] == joueur &&
				plateau[i - 2][j + 2] == joueur &&
				plateau[i - 3][j + 3] == joueur)
				return joueur;
		}
	}	
	return 0; 
}

//--------------------------------
//Match nul? 
//--------------------------------

int plateauPlein(int plateau[6][7])
{
	for (int j = 0; j < 7; j++)
		if (plateau[5][j] == 0)
			return 0;

	return 1;
}

//--------------------------------
//Algorithme principal
//--------------------------------
int main()
{
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);
	setlocale(LC_ALL, ".UTF-8");
	int plateau[6][7] = { 0 };
	int victoire = 0;
	int colonne = 0;
	int isPionPlace;
	lirePlateau(plateau);

	printf("Bienvenue dans puissance 4!, selectionnez une colonne pour jouer.\n");
	while (victoire == 0)
	{
		//-------------------------------
		// Joueur 1
		//-------------------------------
		printf("Place au joueur 1(rouge)!\n");

		do
		{
			colonne = lireColonne();
			isPionPlace = placerPion(plateau, colonne, 1);

			if (isPionPlace == 0)
				printf("Il n'y a plus de place! recommencez.\n");
		} while (isPionPlace == 0);

		lirePlateau(plateau);
		if ((victoire = isPuissance4(plateau)) == 1)
			continue;
		if (plateauPlein(plateau) == 1)
		{
			printf("Match nul !Appuyez entrée pour quitter...\n");
			return 0;
		}

		//------------------------------
		//Joueur 2
		//------------------------------
		printf("Place au joueur 2!(bleu)\n");

		do
		{
			colonne = lireColonne();
			isPionPlace = placerPion(plateau, colonne, 2);

			if (isPionPlace == 0)
				printf("Il n'y a plus de place! recommencez.\n");
		} while (isPionPlace == 0);

		lirePlateau(plateau);
		if ((victoire = isPuissance4(plateau)) == 1)
			continue;
		if (plateauPlein(plateau) == 1)
		{
			printf("Match nul !Appuyez entrée pour quitter...\n");
			return 0;
		}
	}
	printf("Bien joué joueur %d! appuyez entrée pour quitter..\n", victoire);
	getchar();
	return 0;

}

