/*
Author

Maximilien Pluchard
Nathanaël Rovere
*/


#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "header.h"

#define AFFICHAGE 1
#define RECHERCHE 2
#define SAUVEGARDE_MOTS 3
#define SAUVEGARDE_ARBRE 4
#define HELP 5
#define SATANIZE 6
#define TAILLE 1000

/* Couleurs */
#define RED   "\x1B[31m"
#define GREEN   "\x1B[32m"
#define YELLOW   "\x1B[33m"
#define BLUE   "\x1B[34m"
#define MAGENTA   "\x1B[35m"
#define CYAN   "\x1B[36m"
#define WHITE   "\x1B[37m"
#define RESET "\x1B[0m"

/* VARIABLE Globale qui contient le nom du fichier donné en ligne de commande */
static char *filename;
static char *researchedWord;


int main(int argc, char *argv[]) {
	Arbre tree = NULL;
	int command;
  int userInput = 1;
	/* On vérifie que l'argument donné en ligne de commande est correct et on ouvre le fichier */
	command = parseCommand(argc, argv);
	if ( command > 0 ) {
		
		if ( command != SATANIZE
			&& command != HELP) {
		
			char dico[255];
			getFilenameExtension( dico, ".DICO");

			/* Si le fichier DICO existe et que la commande entrée n'est pas SAUVEGARDE_ARBRE on créer a partir du DICO */
			if (fopen(dico, "r")!= NULL && command != SAUVEGARDE_ARBRE) {
				printf("Création de l'arbre depuis le fichier DICO\n");
				tree = readDICO();
			} else {
				printf("Création de l'arbre depuis le fichier texte\n");
				tree = readFile();
			}
		}
	} else {
		printf("Command given failed\n");
		exit(0);
	}  
	executeCommand( command, tree );

	/* On affiche le menu des commandes */
  while ( userInput != 0 ) {
    userInput = promptUser();
    executeCommand( userInput, tree );
  }

	FILE *file;
	file = fopen("tree.dot", "w+");
	if ( file ) {
		dot_export( tree, file );
		fclose(file);
	}
	if ( tree != NULL ) {
		free_arbre( tree );		
	}

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
		5: HELP
		6: SATANIZE
*/
int parseCommand(int argc, char *argv[]) {
	/* Inspection des arguments */
	if ( argc == 3 || argc == 4 ) {
		/* Commutateur -l / -s / -r  / -S / -h */
		char *option = argv[1];

		if( *option != '-' ) {
			printf("Please enter a valid option\n  > 'Lexique.exe -<option> <filename>'\nWhere <option> is one of l/s/r/S/h/c\n");
			return 0;
		}

		/* Stocke le nom du fichier donné en ligne de commande dans la variable globale <filename> */
		filename = argv[argc-1];

		/* Si on recherche un mot, on sauvegarde le mot dans la variable statique */
		if ( argc == 4 ) {
			researchedWord = argv[2];
		}

		switch ( *(option+1) ) {
			case 'l':
				return AFFICHAGE;
				break;
			case 'r':
				return RECHERCHE;
				break;
			case 's':
				return SAUVEGARDE_MOTS;
				break;
			case 'S':
				return SAUVEGARDE_ARBRE;
				break;
			case 'h':
				return HELP;
				break;
			case 'c':
				return SATANIZE;
				break;
			default: {
				printf("Please enter a valid option\n  > 'Lexique.exe -<option> <filename>'\nWhere <option> is one of l/s/r/S/h/c\n");
				return 0;
			}
				break;
		}


	} else {
		printf("Please enter a valid command\n  > 'Lexique.exe -<option> <filename>'\nWhere <option> is one of l/s/r/S/h/c\n");
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
		5: HELP
		6: SATANIZE
*/
void executeCommand( int command, Arbre a ) {
	int res;
	printf("execCommand: %d\n", command);
	switch( command ) {
		case AFFICHAGE:
			/* Fonction de LECTURE */
			displayTree(a);
			break;
		case RECHERCHE:
			res = research( a, researchedWord );
			if ( res ) {
				printf("Word found !(%s)\n", researchedWord);
			} else {
				printf("Word not found !(%s)\n", researchedWord);
			}
			/* Fonction de RECHERCHE */
			break;
		case SAUVEGARDE_MOTS:
			/* Fonction de SAUVEGARDE_MOTS */
			saveWords( a );
			break;
		case SAUVEGARDE_ARBRE:
			/* Fonction de SAUVEGARDE_ARBRE */
			saveTree( a );
			break;
		case HELP:
			/* Fonction de HELP */
			displayHelp();
			break;
		case SATANIZE:
			/* Fonction de HELP */
			satanizeFile();
			exit(0);
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
		5: HELP
		6: SATANIZE
*/
int promptUser() {
	int u, i;
	/*char c;*/

	printf(CYAN "Please select an option between thoses :\n");
	printf(" > 0: EXIT\n");
	printf(" > %d: AFFICHAGE\n", AFFICHAGE);
	printf(" > %d: RECHERCHE\n", RECHERCHE);
	printf(" > %d: SAUVEGARDE_MOTS\n", SAUVEGARDE_MOTS);
	printf(" > %d: SAUVEGARDE_ARBRE\n", SAUVEGARDE_ARBRE);
	printf(" > %d: HELP\n", HELP);
	printf(" > %d: CLEAN\n" RESET, SATANIZE);
	scanf("%d", &u);

	if ( u == RECHERCHE ) {
		printf(CYAN "Please enter a word you want to research :\n" RESET);
		scanf("%s", researchedWord);

		/* Change le mot donné en minuscule */
		i=0;
		while ( *(researchedWord + i) != '\0' ) {
			toLowerCase(researchedWord + i);
			i++;
		}
	}

	if ( u < 0 || u > SATANIZE ) {
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

	Affiche une aide sur l'utilisation du programme
*/
void displayHelp() {
	printf(GREEN "\n----- AIDE -----\n" RESET);
	printf("Pour lancer le programme :\n");
	printf(MAGENTA "Lexique.exe -<option> <filename>\n" RESET);
	printf("Par exemple :");
	printf(MAGENTA "\nLexique.exe -l data/book.txt\n" RESET);
	printf(GREEN "\n----- Options ----- \n" RESET);
	printf(MAGENTA "-l <filename>" RESET);
	printf(": Lecture du livre\n");
	printf(MAGENTA "-r <mot> <filename>" RESET);
	printf(": Recherche du mot dans le livre\n");
	printf(MAGENTA "-s <filename>" RESET);
	printf(": Sauvegarde du livre\n");
	printf(MAGENTA "-S <filename>" RESET);
	printf(": Sauvegarde de l'arbre\n");
	printf(MAGENTA "-c <filename>" RESET);
	printf(": Nettoie le fichier\n");
	printf(MAGENTA "-h" RESET);
	printf(": Affiche l'aide\n\n");
}

/* 
  Function
  Malloc un arbre

  @param <char c>:
    La lettre à créer
*/
Arbre allocTree(char c) {
	Arbre a = (Arbre) malloc(sizeof(Arbre));
	if ( a ) {
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
	Function Utils
	Prend une lettre en parametre et la transforme en lowercase si besoin

	@param <char c>
*/
void toLowerCase( char *c ) {
	if ( *c >= 'A' && *c <= 'Z' ) {
		*c = *c + ('a' - 'A');
	}
}

void addBranch(Arbre *a, char *s) {
	/* Ajout un mot dans une branche vide */
	*a = allocTree(s[0]);
	
	if ( *a != NULL )
		if ( s[0] != '\0' )
			addBranch(&(*a)->filsg, &s[1]);
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
void addWord(Arbre *a, char *s) {
	/* Ajout de l'arbre crée dans l'arbre donné en arg */
	if ( *a == NULL )
		addBranch(a, s);
	
	else {
		/* On cherche parmis les freres */
		/* La lettre a ajouter est plus grande que le lettre de l'arbre */
		if ( s[0] > (*a)->lettre ) 
			addWord(&((*a)->frered), s );
		else {			
			/* C'est la meme lettre */
			if ( s[0] == (*a)->lettre )  {
				if ( s[0] != '\0' )
					addWord(&((*a)->filsg), &s[1] );
			} else {
				/* La lettre a ajouter est plus petite que le lettre de l'arbre */
				Arbre tmp = NULL;
				addBranch(&tmp, s);
				tmp->frered = *a;
				*a = tmp;
			}
		}
	}
}

/* 
  Fonction
  Lire le fichier DICO donné en ligne de commande

  @param <FILE file>
  @return <Arbre> :
    - l'arbre crée
*/
Arbre readDICO() {
	Arbre a = NULL;
	FILE *file;
	char dico[255];
	int lettre = 0;
	char word[TAILLE] = "";
	int index = 0;


	/* Lecture du fichier */
	getFilenameExtension(dico, ".DICO");
	file = fopen(dico, "r");

	if ( file ) {
		printf(" > Création de l'arbre ...\n");

		/* On lis les caractères un à un */
		do{
			lettre = fgetc(file);
			/* Affichage DEBUG */
			/*
      if ( lettre == '\n' ) {
        printf("\\n");
      } else {
        printf("%c", lettre);
      }
      */

			/* Creation des mots */
			if ( lettre == '\n' ) {
				word[index] = 0;
				index--;
			} else if ( lettre == ' ' ) {
				word[index] = '\0';
				addWord(&a, word);
				word[index] = 0;
			} else {
				word[index] = lettre;
				index++;
			}
		} while (lettre != EOF);

		printf(" > Arbre crée \n");
		fclose(file);  
	} else {
		printf("Erreur lecture du fichier\n");
		return NULL;
	}

	return a;
}

/*
	Fonction Utils
	Rend le fichier propre	
*/
void satanizeFile() {

	FILE *file_input;
	FILE *file_clean;
	
	char clean[255];
	getFilenameExtension( clean, "_clean.txt");
	
	file_input = fopen(filename, "r");
	file_clean = fopen(clean, "w");
	char letter = ' ';
	char last = ' ';

	if ( file_input && file_clean ) {
		printf(" > Satanization du fichier ...\n");

		do {

			last = letter;
			letter = fgetc(file_input);			
			
			/* Clean */
			if ( letter != EOF ) {
				toLowerCase( &letter );
				if ( letter < 'a' || letter > 'z') {
					letter = ' ';
				}
				if ( letter == ' ' && last == ' ') {
					fseek(file_clean, -1, SEEK_CUR);
				}
				/* Copy */
				fputc(letter, file_clean);
			}

		} while ( letter != EOF );

		printf(" > Fichier propre \n");
		fclose(file_input);
		fclose(file_clean);
	} else {
		printf("Erreur lecture du fichier\n");
		return;
	}
}

/* 
  Fonction
  Lire le fichier texte donné en ligne de commande

  @param <FILE file>
  @return <Arbre> :
    - l'arbre crée
*/
Arbre readFile() {
	Arbre a = NULL;
	FILE *file;
	file = fopen(filename, "r");
	char word[TAILLE];
	int cpt = 0;
	int LAST = 36;

	if ( file ) {
		printf(" > Création de l'arbre ...\n");

		while (fscanf(file, "%1000s", word) == 1 && cpt <= LAST ) {
			addWord(&a, word);
			cpt++;
			if ( cpt == LAST ) 
				printf("%s\n", word);
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
  Fonction Reccursive
  Afficher les mots du lexique en ordre lexicographique

  @param <Arbre a>
  @param <int *buffer>
  @param <int i>
*/
void displayTree_rec( Arbre a, UListe *path ) {
	if ( a ) {
		ajouterFinUListe( path, a->lettre );
		if( a->lettre == '\0' ) {
			afficherUListe( path );
		}
		displayTree_rec( a->filsg, path );
		supprimerDernierUListe( path );
		displayTree_rec( a->frered, path );
	}
}

/*
  Fonction
  Afficher les mots du lexique en ordre lexicographique

  @param <Arbre a>
*/
void displayTree( Arbre a ) {
	if ( a == NULL ) return;  
	UListe path;
	path.premier = NULL;
	path.dernier = NULL;
	path.taille = 0;
	displayTree_rec(a, &path);
}

/*
  Fonction recursive
  Sauvegarde un noeud de l'arbre

  @param <Arbre a>
  @param <FILE file>
*/
void saveWords_rec (Arbre a, FILE *file, UListe *path) {
	if ( a ) {
		ajouterFinUListe( path, a->lettre );

		/* Sauvegarde */
		if( a->lettre == '\0' ) {
			Mot actuel = path->premier;
			while ( actuel != NULL ) {
				if ( actuel->lettre == '\0') {
					fputc(' ', file);
				} else {
					fputc(actuel->lettre, file );
				}
				actuel = actuel->suiv;
			}
			fputc('\n', file);
		}
		/* Fin Sauvegarde */

		saveWords_rec( a->filsg, file, path );
		supprimerDernierUListe( path );
		saveWords_rec( a->frered, file, path );
	}
}

/*
  Fonction
  Sauvegarder les mots du lexique en ordre alphabétique. Le nom du fichier de sauvegarde est le nom du fichier d'entrée suivi du suffixe ( .L )

  @param <Arbre a>
*/
void saveWords( Arbre a ) {
	if ( a == NULL ) return;

	/* Fichier */
	FILE *file;
	char fileWords[255];
	getFilenameExtension( fileWords, ".L");
	printf("%s\n", fileWords);

	/* Liste chainée */
	UListe path;
	path.premier = NULL;
	path.dernier = NULL;
	path.taille = 0;

	/* Creation du fichier */
	file = fopen(fileWords, "w+");

	/* Sauvegarde de l'arbre */
	saveWords_rec( a, file, &path );

	/* Fermeture du fichier */
	fclose(file);
}

/*
  Fonction
  Indiquer si le mot est present dans le texte et affiche "present" ou "absent"

  @param <Arbre a>
	@return <int>
		0: Non trouvé
		1: Trouvé
*/
int research( Arbre a, char* mot ) {
	if ( a == NULL || *mot < a->lettre ) return 0;
	if (*mot == a->lettre) {
		if (*mot == '\0') return 1;
		return research(a->filsg, mot+1);
	}
	return research(a->frered, mot);
}


/*
  Fonction recursive
  Sauvegarde un noeud de l'arbre

  @param <Arbre a>
  @param <FILE file>
*/
void saveTree_rec (Arbre a, FILE *file) {
	if ( a ) {

		/* Sauvegarde */
		if( a->lettre == '\0' ) {
			fputc(' ', file);
		} else {
			fputc(a->lettre, file);      
		}
		/* Fin Sauvegarde */

		if ( a->lettre != '\0') {
			saveTree_rec( a->filsg, file );
		}
		saveTree_rec( a->frered, file );
	} else {
		/*
      fputc('\'', file);
      fputc('\\', file);
      fputc('n', file);
      fputc('\'', file);
      */
		fputc('\n', file);
	}
}

/*
  Fonction
  Sauvegarder l'arbre dans un fichier, le nom du fichier de sauvegarde est le nom d'entrée suivi du suffixe (.DICO)

  @param <Arbre a>
*/
void saveTree( Arbre a ) {
	if ( a == NULL ) return;

	/* Fichier */
	FILE *file;
	char fileWords[255];
	getFilenameExtension( fileWords, ".DICO");
	printf("%s\n", fileWords);

	/* Creation du fichier */
	file = fopen(fileWords, "w+");

	/* Sauvegarde de l'arbre */
	saveTree_rec( a, file );

	/* Fermeture du fichier */
	fclose(file);
}

int rec_dot_export(Arbre a, int nodeID, FILE *dot_file) {
	char val, res_fg=0, res_fd=0;
	if (a != NULL) {
		val = a->lettre;
		if ( val == '\0' ) val = '0';
		fprintf(dot_file, "\tn%d [label=\"<fils> | <lettre> %c | <frere>\"];\n", nodeID, val);
	}
	if (a->frered != NULL) {
		fprintf(dot_file, "\tn%d:fils:c -> n%d:lettre;\n", nodeID, nodeID+1);
		res_fg = rec_dot_export(a->frered, nodeID+1, dot_file);
	}
	if (a->filsg != NULL) {
		fprintf(dot_file, "\tn%d:frere:c -> n%d:lettre;\n", nodeID, nodeID+res_fg+1);
		res_fd = rec_dot_export(a->filsg, nodeID+res_fg+1, dot_file);
	}
	return res_fg+res_fd+1;
}
void dot_export(Arbre a, FILE *dot_file) {
	fprintf(dot_file, "digraph arbre {\n");
	fprintf(dot_file, "\tnode [shape=record,height=.1]\n");
	fprintf(dot_file, "\tedge [tailclip=false,arrowtail=dot,dir=both]\n");
	rec_dot_export(a, 0, dot_file);
	fprintf(dot_file, "}\n");
}
void free_arbre(Arbre a) {
	if (a != NULL) {
		free_arbre(a->frered);
		free_arbre(a->filsg);
		free(a);
	}
}