### Projet Arbres lexicographiques

Projet de création d'un arbre lexicographique en Langage C au moyen d'un arbre de forme FILS GAUCHE, FRERE DROIT

Lien du sujet : 
https://elearning.u-pem.fr/pluginfile.php/183409/mod_resource/content/1/Fgfrd.pdf

> __C'est trivial en vrai__

> Pour lancer le programme :

```
	Lexique.exe -<option> <filename>
```

> Par exemple : 

```
	Lexique.exe -l data/book.txt
```
Set à afficher le livre

Liste des options :
 * `-l <filename>` : Lecture du livre
 * `-r <mot> <filename>` : Recherche du mot dans le livre
 * `-s <filename>` : Sauvegarde du livre
 * `-S <filename>` : Sauvegarde de l'arbre
 * `-h` : Affiche l'aide
 
 
 
# TODO

* Reconstruire a partir du fichier .DICO
* Rapport

# DONE

* Sauvegarder l'arbre dans un fichier, le nom du fichier de sauvegarde est le nom d'entrée suivi du suffixe (.DICO)
* Afficher les mots du lexique en ordre lexicographique
* Sauvegarder les mots du lexique en ordre alphabétique. Le nom du fichier de sauvegarde est le nom du fichier d'entrée suivi du suffixe ( .L )
* Indiquer si le mot est present dans le texte sous forme __*present*__ ou __*absent*__
* Menu des commandes :
  * -> Affichage
  * -> Sauvegarde des mots du lexique (.L)
  * -> Recherche
  * -> Sauvegarde de l'arbre (.DICO)
* Ligne de commande :
  * -> Affichage
  * -> Sauvegarde des mots du lexique (.L)
  * -> Recherche
  * -> Sauvegarde de l'arbre (.DICO)

