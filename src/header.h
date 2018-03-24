#ifndef LEXIQUE_H
#define LEXIQUE_H

#include <stdio.h>

/* STRUCTURES */
typedef struct noeud {
  unsigned char lettre;
  struct noeud *filsg, *frered;
} Noeud, *Arbre;

typedef struct mot {
  char lettre;
  struct mot *suiv;
  struct mot *prec;
} *Mot;

typedef struct doublelist {
	Mot premier;
	Mot dernier;	
	int taille;
} UListe;

int parseCommand(int argc, char *argv[]);
void executeCommand(int command, Arbre a);
int promptUser();
Arbre readFile();
Arbre allocTree(char c);
void getStrippedFilename(char s[]);
int addWord(Arbre *a, char s[]);
void toLowerCase( char *c );

/* FONCTIONS D'EXECUTIONS */

void displayTree_rec( Arbre a, UListe *path );
void displayTree( Arbre a );
void displayHelp();
void saveWords_rec (Arbre a, FILE *file, UListe *path);
void saveWords(Arbre a);
void saveTree_rec(Arbre a, FILE *file);
void saveTree(Arbre a);
int research( Arbre a, char* mot );

/* ULISTE */
Mot creerMot(char lettre);
void ajouterFinUListe(UListe *liste , char c);
void afficherUListe ( UListe *liste );
int supprimerDernierUListe ( UListe *liste );
int supprimerUListe ( UListe * liste, char lettre );

/* DOT */
int rec_dot_export(Arbre a, int nodeID, FILE *dot_file);
void dot_export(Arbre a, FILE *dot_file);
void free_arbre(Arbre a);



#endif
