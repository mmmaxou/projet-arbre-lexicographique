#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "header.h"

#define AFFICHAGE 1
#define RECHERCHE 2
#define SAUVEGARDE_MOTS 3
#define SAUVEGARDE_ARBRE 4
#define TAILLE 50

/* VARIABLE Globale qui contient le nom du fichier donné en ligne de commande */
static char *filename;


int main(int argc, char *argv[]) {
  Arbre tree;
  int command;
  int userInput = 1;

  /* On vérifie que l'argument donné en ligne de commande est correct et on ouvre le fichier */
  command = parseCommand(argc, argv);
  if ( command > 0 ) {
    tree = readFile();

    /* TEST */
    displayTree( tree );
    printf("\n");
    saveWords( tree );
    saveTree( tree );
    /* FIN TEST */

  } else {
    printf("Command given failed\n");
    exit(0);
  }
  executeCommand( command, tree );

  /* On affiche le menu des commandes */
  /*
  while ( userInput != 0 ) {
    userInput = promptUser();
    executeCommand( userInput, tree );
  }
  */
  return 0;
}

/* 
  Fonction
  Inspecte les arguments données en ligne de commande et renvoi le resultat à effectuer
  Stocke le nom du fichier donné en ligne de commande dans la variable globale <filename>

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
  if ( argc == 3 ) {
    /* Commutateur -l / -s / -r  / -S */
    char *s = argv[1];
    /*
    printf("Commande : %s\n", s);
    printf("*s : %c\n", *s);
    printf("option : %c\n", *(s+1));
    */

    if( *s != '-' ) {
      printf("Please enter a valid option\n  > 'Lexique.exe -<option> <filename>'\nWhere <option> is one of l/s/r/S\n");
      return 0;
    }

    /* Stocke le nom du fichier donné en ligne de commande dans la variable globale <filename> */
    /* argv[argc-1] => Dernier argument donné en ligne de commande = nom_du_fichier */
    filename = argv[argc-1];
    /* printf("filename: %s\n", filename); */

    switch ( *(s+1) ) {
      case 'l':
        return AFFICHAGE;
        break;
      case 's':
        return RECHERCHE;
        break;
      case 'r':
        return SAUVEGARDE_MOTS;
        break;
      case 'S':
        return SAUVEGARDE_ARBRE;
        break;
      default: {
        printf("Please enter a valid option\n  > 'Lexique.exe -<option> <filename>'\nWhere <option> is one of l/s/r/S\n");
        return 0;
      }
        break;
    }


  } else {
    printf("Please enter a valid command\n  > 'Lexique.exe -<option> <filename>'\nWhere <option> is one of l/s/r/S\n");
    return 0;
  }

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

  /* TODO */
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
  int u;

  printf("Please select an option between thoses :\n");
  printf(" > 0: EXIT\n");
  printf(" > %d: AFFICHAGE\n", AFFICHAGE);
  printf(" > %d: RECHERCHE\n", RECHERCHE);
  printf(" > %d: SAUVEGARDE_MOTS\n", SAUVEGARDE_MOTS);
  printf(" > %d: SAUVEGARDE_ARBRE\n", SAUVEGARDE_ARBRE);
  scanf("%d", &u);
  if ( u < 0 || u > SAUVEGARDE_ARBRE ) {
    printf("Invalid input given.\n");
    return promptUser();
  }
  return u;
}

/*
  Fonction Utils
  Copie le filename sans l'extension dans la variable <s>

  @param <char s[]>: La chaine de caractere dans laquelle le filename sera copiée
*/
void getStrippedFilename( char s[] ) {
  if ( strcmp(filename, "") == 0 ) {
    printf("Error : Unknow filename\n");
    return;
  }
  char *lastdot;
  strcpy(s, filename);
  lastdot = strrchr( s, '.' );
  if ( lastdot != NULL ) {
    *lastdot = '\0';
  } else {
    printf("Error finding the . in the file extension\n");
  }
}

/*
  Fonction Utils
  Copie le filename avec une nouvelle extension donnée dans la variable s

  @param <char s[]>: La chaine de caractere dans laquelle le filename sera copiée
  @param <char ext[]>: Une chaine de caractere qui contient l'extension à ajouter à notre chaine <s>
*/
void getFilenameExtension( char s[], char ext[] ) {
  getStrippedFilename(s);
  strcat(s, ext);
}


/* 
  Function
  Malloc un arbre

  @param <char c>:
    La lettre à créer
*/
Arbre allocTree(char c) {
  Arbre a = (Arbre) malloc(sizeof(*a));
  if ( a ) {
    if ( c >= 'A' && c <= 'Z' ) {
      c = c + ('a' - 'A');
    }
    a->lettre = c;
    a->filsg = NULL;
    a->frered = NULL;
    return a;
  } else {
    printf("Memory allocation failed. Program exit\n");
    exit(0);
  }  
}

/*
  Function
  Ajoute un mot à l'arbre
  Pour chaque lettre, crée un nouvel arbre

  @param <Arbre a>:
    L'arbre auquel le mot est ajouté
  @param <char s[]>:
    Une chaine de caractere correspondant au mot à ajouter
  @param <int taille>:
    Taille du mot
  @return:
    -1: Erreur
    0: Ok
*/
int addWord(Arbre *a, char s[]) {
  char c;
  Arbre tmp;
  /*printf("Ajout de %s : ", s);*/

  /* Création de l'arbre */
  c = *s;
  tmp = allocTree(c);

  /* Ajout de l'arbre crée dans l'arbre donné en arg */
  if ( *a == NULL ) {
    *a = tmp;
    /*printf("%c added\n", (*a)->lettre);*/
    if ( c == '\0' ) {
      return 1;
    } else {
      return addWord(&((*a)->filsg), s+1 );
    }
  } else {

    /* On cherche parmis les freres */
    if ( tmp->lettre > (*a)->lettre ) {
      /* La lettre a ajouter est plus grande que le lettre de l'arbre */
      return addWord(&((*a)->frered), s );
    } else if ( tmp->lettre < (*a)->lettre ) {
      /* La lettre a ajouter est plus petite que le lettre de l'arbre */
      tmp->frered = *a;
      *a = tmp;
      return addWord(&((*a)->filsg), s+1 );
    } else {
      /* C'est la meme lettre */
      return addWord(&((*a)->filsg), s+1 );
    }


  }

  return -1;
}

/* 
  Fonction
  Lire le fichier source donné en ligne de commande

  @param <FILE file>
  @return <Arbre> :
    - l'arbre crée
*/
Arbre readFile() {
  Arbre a = NULL;
  FILE *file;
  file = fopen(filename, "r");
  char word[TAILLE] = "";

  if ( file ) {
    printf(" > Création de l'arbre ...\n");

    while (fscanf(file, "%s", word) == 1) {
      addWord(&a, word);
    }

    printf(" > Arbre crée \n");
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


  /* Le bout de code est pas terrible, il me servait juste a tester */
  /*
  if ( a ) {
    printf("%c", a->lettre );
    displayTree( a->filsg );
    displayTree( a->frered );
  } 
  */
}

/*
  Fonction recursive
  Sauvegarde un noeud de l'arbre

  @param <Arbre a>
  @param <FILE file>
*/
void saveWords_rec (Arbre a, FILE file) {
  /* TODO */
}

/*
  Fonction
  Sauvegarder les mots du lexique en ordre alphabétique. Le nom du fichier de sauvegarde est le nom du fichier d'entrée suivi du suffixe ( .L )

  @param <Arbre a>
*/
void saveWords( Arbre a ) {
  FILE file;
  char fileWords[255];
  getFilenameExtension( fileWords, ".L");
  printf("%s\n", fileWords);
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
void saveTree( Arbre a ) {
  FILE file;
  char fileTree[255];
  getFilenameExtension( fileTree, ".DICO");
  printf("%s\n", fileTree);
}

