Votre objectif est de créer une librairie de filtres de blooms capable de charger les k-mers d'un génome puis permettre de le requêter. Les propriétés et requêtes sont expliquées dans la sous partie "Librairie filtre de blooms"

ATTENTION : Veillez à bien tout lire de ce fichier avant de vous lancer dans la programmation.


# Projet global

Je vous demande de produire un logiciel qui prend en ligne de commande:
- 1 fichier fasta
- Une valeur de k (inférieur ou égal à 31)
- Une taille n de filtre de bloom (max 2^34 (16 Go))
- Une valeur nf qui donne le nombre de fonction de hashage (max 64)
- Une valeur r d'un nombre de requête.

Ce ligiciel doit construire en interne un filtre de bloom de taille n avec nf fonctions de hashages puis le remplir avec tous les k-mers du fichier passé en entrée.
Il doit ensuite effectuer r requêtes aléatoires is_present sur le filtre de bloom (ie générer r kmers aléatoires et les rechercher)

Exemple de ligne de commande:
```bash
  #         fichier          k    n   nf   r
  ./monprog data/ecoli.fasta 31 456637 3 10000
```

## Mes attentes

- Un github contenant votre projet dont le lien m'est envoyé avant lundi 24 Janvier (avant == max le 23 à 23h59 et 59s)  
- Un readme dans le github expliquant comment compiler et exécuter votre code.
- Un code qui compile
- Un code qui s'exécute avec la ligne de commande que vous avez donné.
- Des fichiers commentés
- Un code propre et reprenable par quelqu'un d'autre.


## Les étapes du projets

Je vous conseille de procéder par résolution des étapes suivantes dans l'ordre :  
- Télécharger un génome (commencez par le plus petit)  
- Faites vous une fonction qui vous permet de lire le fichier fasta de manière à ce que chaque appel à la fonction vous renvoie uniquement le charactère suivant de la séquence ADN  
- Faites une fonction qui encode un tableau de caractère de taille k en une valeur entière.
- Créez un fonction qui à partir d'un kmer précédent et une lecture du caratére suivant dans le fichier vous donne le kmer suivant.  
- Créez une classe bloom filter suivant la librairie
- Listez tous les k-mer dans l'ordre du fichier, les hasher, les entrer dans le filtre de bloom
- Codez la fonction de requête du BF.
- Bravo, vous avez fini le code


# Librairie filtre de blooms

Rappel de ce qu'est un filtre de bloom : https://fr.wikipedia.org/wiki/Filtre_de_Bloom  

Vous devrez coder une librairie (ici classe) de filtre de blooms.
Cette classe contient un tableau de Bytes (8 bits / Byte).
Si le bloom filter est de taille n, le tableau fera une taille n/8 + 1.
Ce bloom filter aura 3 fonctions : un constructeur, add_value et is_present.

## Constructeur

Le filtre de bloom est construit vide mais avec 2 parametres:  
- Sa taille (en nombre de bits) n.
- Le nombre de fonctions de hashage utilisées nf.

## add_value

La fonction permet d'ajouter une nouvelle entrée x dans le bloom filter.
Cette entrée doit être hashée nf fois en utilisant la fonction xorshift fournie dans le fichier hash.cpp puis les bits correspondant doivent être mis à 1.
Attention, la valeur 0 ne peut pas être hashée (elle retourne toujours 0).
Trouvez une astuce pour contourner ce problème.

## is_present

La fonction prend en paramètre une valeur x et retourne faux si l'entrée n'est pas dans le BF et vrai si elle l'est.


# Datasets : Séquences ADN

## Téléchargement

Pour télécharger un génome il faut:  
1 - Cliquer sur le lien correspondant au génome (voir ci-après)  
2 - Cliquer en haut à droite sur "send to"  
3 - Sélectionner "File"  
4 - Modifier le format pour mettre "FASTA"  
5 - Cliquer sur "Create File"  

- Virus (Sars-Cov-2): https://www.ncbi.nlm.nih.gov/nuccore/NC_045512.2  
- Bactérie (e.coli): https://www.ncbi.nlm.nih.gov/nuccore/NZ_LN874954.1  
- Humain (Chromosome 1): https://www.ncbi.nlm.nih.gov/nuccore/NC_008801.1

## Lecture du fichier .fasta

Les fichiers fasta ci-dessus sont tous formatés de la même manière.
La première ligne est une entête dont le premier caractère est un Chevron fermant.
Les lignes suivantes représentent la séquence ADN.
Les retours à la ligne sont uniquement pour faciliter la lecture d'un Humain et ne représentent rien.
Vous devez donc les ignorer lors de la lecture du fichier.  

Les séquences sont composées principalement des 4 lettres A, C, G, T.
Parfois, les meilleurs machines actuelles n'ont pas réussit à parfaitement lire certains nucléotides.
Ces nucléotides sont remplacés par des N (dans la bactérie et l'Humain).
Pour ce projets, ignorez les N.
Ainsi, si la séquence est ACTTNNNNATNGCT considérez à la place que c'est ACTTATGCT.
TTA est donc un 3-mer valide ici.
Votre lecteur de fichier dois passer par dessus ces caractères sans les retourner.
ATTENTION : Lorsque je testerai votre code, j'utiliserai des séquences avec des N. Votre programme ne dois pas planter.



## k-mers

Pour rappel, un k-mer est un mot de taille k.
Ici, il vous faudra tous les générer à partir de la séquence en entrée.
Ainsi la séquence ACTT avec k=3 doit générer ACT et CTT.
  
Pour pouvoir entrer un k-mer dans un BF, vous devez le transformer en entier.
Pour cela vous pourrez utiliser l'encodage 2 bits de votre choix.
Par exemple avec l'encodage A:0 C:1 T:2 G:3 le kmer CTT vaut 1 * 4^2 + 2 * 4^1 + 2 * 4^0 = 26.


## Reverse complement.

Comme vous le savez certainement, en génétique, chaque nucléotide a son complément.
Ainsi au sein de la double élice d'ADN chaque A est pairé avec un T et chaque C avec G.
Ce qui veut alors dire que chaque séquence peut être lue à l'endroit normalement ou à l'envers comme son complément.
ACTT peut donc également être lue comme AAGT.
Chaque k-mer a donc un reverse complement.
Pour choisir entre les deux formes, nous prendrons toujours celui qui est le plus petit dans l'ordre lexicographique.
Dans l'exemple précédent, j'ai dit que la séquence ACTT générait 2 3-mers ACT et CTT.
En appliquant la règle du plus petit lexicographique on génère ACT (plus petit que AGT) et AAG (plus petit que CTT).
