#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "header.h"

#define AFFICHAGE 1
#define RECHERCHE 2
#define SAUVEGARDE_MOTS 3
#define SAUVEGARDE_ARBRE 4

/* VARIABLE Globale qui contient le nom du fichier donné en ligne de commande */
static char *filename;

int main(int argc, char *argv[]) {
  Arbre tree;
  int command;
  int userInput = 0;
  
  /* On vérifie que l'argument donné en ligne de commande est correct et on ouvre le fichier */
  command = parseCommand(argc, argv);
  if ( command > 0 ) {
    tree = readFile();
  } else {
    printf("An error occurred\n");
    exit(0);
  }
  executeCommand( command, tree );
  
  /* On affiche le menu des commandes */
  while ( userInput != 0 ) {
    userInput = promptUser();
    executeCommand( command, tree );
  }
  
  return 0;
}

/* 
  Fonction
  Inspecte les arguments données en ligne de commande et renvoi le resultat à effectuer
  Stocke le prefix du fichier donné en ligne de commande dans la variable globale <filePrefix>
  
  @param <int argc>
  @param <char *argv[]>
  @return <int> :
   -1: Erreur inconnu
    0: Mauvais nombre d'argument
    1: LECTURE
    2: RECHERCHE
    3: SAUVEGARDE_MOTS
    4: SAUVEGARDE_ARBRE
*/
int parseCommand(int argc, char *argv[]) {
  /* Inspection des arguments */
  /* TODO */
  
  /* Stocke le nom du fichier donné en ligne de commande dans la variable globale <filePrefix> */
  /* argv[argc-1] => Dernier argument donné en ligne de commande = nom_du_fichier */
  /* TODO */
  filename = "";
  
  return -1;
}

/*
  Fonction
  Effectue l'action liée à la demande de l'utilisateur
  
  @param <int command>:
    0: Arret du programme
    1: LECTURE
    2: RECHERCHE
    3: SAUVEGARDE_MOTS
    4: SAUVEGARDE_ARBRE  
*/
void executeCommand( int command, Arbre a ) {
  
  switch( command ) {
    case AFFICHAGE:
      /* Fonction de LECTURE */
      break;
    case RECHERCHE:
      /* Fonction de RECHERCHE */
      break;
    case SAUVEGARDE_MOTS:
      /* Fonction de SAUVEGARDE_MOTS */
      break;
    case SAUVEGARDE_ARBRE:
      /* Fonction de SAUVEGARDE_ARBRE */
      break;
    default:
      /* Erreur */
      break;
  }
  
}

/*
  Fonction
  Demande à l'utilisateur ce qu'il souhaite faire ensuite et renvoi le code correspondant à l'action en retour
  
  @return <int> :
   -1: Erreur
    0: Arret du programme
    1: LECTURE
    2: RECHERCHE
    3: SAUVEGARDE_MOTS
    4: SAUVEGARDE_ARBRE
*/
int promptUser() {
  
  return 0;
}


/*
  Fonction Utils
  Renvoi le filename sans l'extension
  
  @return <char *>
*/
char* strippedFilename() {
  /* TODO */
  
  return "";
}

/* 
  Fonction
  Lire le fichier source donné en ligne de commande
  
  @param <FILE file>
  @return <Arbre> :
    - l'arbre crée
*/
Arbre readFile() {
  Arbre a;
  FILE *file;
  file = fopen(filename, "r");
  
  if ( file ) {
    /* TODO */
    
    fclose(file);  
  } else {
    printf("Erreur lecture du fichier\n");
    return NULL;
  }
  
  return a;
}


/* FONCTIONS D'EXECUTIONS */

/*
  Fonction
  Afficher les mots du lexique en ordre lexicographique
  
  @param <Arbre a>
*/
void displayTree( Arbre a ) {
  /* TODO */
}

/*
  Fonction recursive
  Sauvegarde un noeud de l'arbre
  
  @param <Arbre a>
  @param <FILE file>
*/
void saveWords_rec (Arbre a, FILE file) {
  
}

/*
  Fonction
  Sauvegarder les mots du lexique en ordre alphabétique. Le nom du fichier de sauvegarde est le nom du fichier d'entrée suivi du suffixe ( .L )
  
  @param <Arbre a>
*/
void saveWords(Arbre a, char *filepath) {
  FILE file;
  /* Creation du fichier */
  /* TODO */
  
  /* Sauvegarde de l'arbre */
  /* TODO */
  saveWords_rec( a, file );
  
  /* Fermeture du fichier */
  /* TODO */
}

/*
  Fonction
  Indiquer si le mot est present dans le texte et affiche "present" ou "absent"
  
  @param <Arbre a>
*/
void research( Arbre a ) {
  /* TODO */
}

/*
  Fonction
  Sauvegarder l'arbre dans un fichier, le nom du fichier de sauvegarde est le nom d'entrée suivi du suffixe (.DICO)
  
  @param <Arbre a>
*/
void saveTree(Arbre a, FILE file, char *filepath) {
  /* TODO */
}

