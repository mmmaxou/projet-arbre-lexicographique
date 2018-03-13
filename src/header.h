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

/* FONCTIONS D'EXECUTIONS */
void displayTree( Arbre a );
void saveWords_rec (Arbre a, FILE file);
void saveWords(Arbre a, char *filepath);
void research( Arbre a );
void saveTree(Arbre a, FILE file, char *filepath);
#endif
