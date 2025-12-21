#include <iostream>
#include<locale.h>
#include <windows.h>
//-------------------
//Fonction affichage
//-------------------
void afficherPlateau(int tab[6][7])
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

		if (scanf_s("%d", &colonne) != 1 || colonne > 7 || colonne < 1)
		{
			printf("ce nombre est ou incorrect veuillez choisir un nombre entre 1 et 7\n");
			while ((getchar()) != '\n');
		}
	} while (colonne > 7 || colonne < 1);
	while ((getchar()) != '\n');
	return colonne - 1;
}
//------------------------------
//Placement du pion
//------------------------------
int placementPion(int plateau[6][7], int colonne, int joueur)
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
		for (int j = 0; j < 7; j++)
		{
			int joueur = plateau[i][j];
			if (joueur == 0) 
				continue;

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
			if (i <= 2 && j <=3 &&
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
//Sous algorithme joueur 
//--------------------------------

int tourJoueur(int plateau[6][7], int joueur)
{
	int colonne;
	int pionPlace;
	printf("Place au joueur %d !\n", joueur);
	do
	{
		colonne = lireColonne();
		pionPlace = placementPion(plateau, colonne, joueur);

		if (pionPlace == 0)
			printf("Il n'y a plus de place! recommencez.\n");

	} while (pionPlace == 0);

	afficherPlateau(plateau);

	if (isPuissance4(plateau) == joueur)
		return joueur;
	if (plateauPlein(plateau) == 1)
		return -1;

	return 0; 
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
	int joueur = 1;
	afficherPlateau(plateau);

	printf("Bienvenue dans puissance 4!, selectionnez une colonne pour jouer.\n");
	do 
	{
		victoire = tourJoueur(plateau, joueur);

		if (joueur == 1)
			joueur = 2;
		else
			joueur = 1;

	} while (victoire == 0);

	if (victoire == -1)
		printf("Match Nul! appuyez entrée pour quitter..\n");
	else
		printf("Bien joué joueur %d! appuyez entrée pour quitter..\n", victoire);

	(void)getchar();
	return 0;

}