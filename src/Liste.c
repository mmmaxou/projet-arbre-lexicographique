#include <stdio.h>
#include <stdlib.h>
#include "header.h"

Mot creerMot(char lettre) {
  Mot tmp = (Mot) malloc( sizeof( Mot ) );
  if ( !tmp ) {
    printf("Erreur allocation mémoire\n");
    exit(0);
  }
  tmp->lettre = lettre;
  tmp->suiv = NULL;
  tmp->prec = NULL;
  return tmp;
}
void ajouterFinUListe(UListe *liste , char c) {
	Mot m = creerMot( c );
  
	if ( liste->taille == 0 ) {
		liste->premier = m;
		liste->dernier = m;		
	} else {
		liste->dernier->suiv = m;
		m->prec = liste->dernier;
		liste->dernier = m;
	}
	
	liste->taille++;
}
void afficherUListe ( UListe *liste ) {
	Mot actuel = liste->premier;
  while ( actuel != NULL ) {
    printf("%c", actuel->lettre);
    actuel = actuel->suiv;
  }
  printf("\n");
}
int supprimerDernierUListe ( UListe *liste ) {  
  if ( liste->taille == 0 ) {
    printf("Liste vide\n");
    return 0;
  }
  return supprimerUListe( liste, liste->dernier->lettre );
}
/*
	Supprime une unite de la liste doublement chainée
	L'unite a supprimer est identifiée par son id
*/
int supprimerUListe ( UListe * liste, char lettre ) {
	Mot tmp = liste->premier;
	int found = 0;
	while ( tmp != NULL && !found ) {
		if ( tmp->lettre == lettre ) {
			if ( liste->taille == 1 ) {
				liste->premier = NULL;	
				liste->dernier = NULL;
			} else if ( tmp->suiv == NULL ) {
				liste->dernier = tmp->prec;
				liste->dernier->suiv = NULL;
			} else if ( tmp->prec == NULL ) {
				liste->premier = tmp->suiv;
				liste->premier->prec = NULL;				
			} else {
				tmp->suiv->prec = tmp->prec;
				tmp->prec->suiv = tmp->suiv;
			}
			found = 1;
			liste->taille--;
		} else {
			tmp = tmp->suiv;
		}
	}
	
	return 1;	
}
