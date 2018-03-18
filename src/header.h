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

/* FONCTIONS D'EXECUTIONS */
void displayTree( Arbre a );
void saveWords_rec (Arbre a, FILE file);
void saveWords(Arbre a);
void research( Arbre a );
void saveTree(Arbre a);
#endif
