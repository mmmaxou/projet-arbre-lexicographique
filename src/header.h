#ifndef LEXIQUE_H
#define LEXIQUE_H

/* STRUCTURES */
typedef struct noeud {
  unsigned char lettre;
  struct noeud *filsg, *frered;
} Noeud, *Arbre;


int parseCommand(int argc, char *argv[]);
void executeCommand(int command, Arbre a);
int promptUser();
Arbre readFile();
Arbre allocTree(char c);
void getStrippedFilename(char s[]);
int addWord(Arbre *a, char s[]);
void toLowerCase( char *c );

/* FONCTIONS D'EXECUTIONS */

void printCharTab(int* buffer);
void displayTree( Arbre a, int* buffer, int i );
void displayHelp();
void saveWords_rec (Arbre a, FILE file);
void saveWords(Arbre a);
int research( Arbre a, char* mot );
void saveTree(Arbre a);
#endif
