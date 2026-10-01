# Réponses — TP séance 7 (jusqu'à l'exercice 5)

## Sortie de `exo.c` fourni (TP de révision)

Voici la sortie du programme de révision `exo.c`. Je m'en suis servi pour reprendre les fonctions de liste dans l'exercice 1.

```text
Pret.
--- R1 : entiers ---
 int max       = 2147483647
 int max + 1   = non defini par la norme C
 uint max      = 4294967295
 uint max + 1  = 0
 -7 % 3        = -1
--- R2 : tableaux et chaines ---
 mot            = bonjour
 strlen(mot)    = 7
 sizeof(mot)    = 20
 a == b         = false
 strcmp(a,b)==0 = true
--- R3 : structures ---
 p.nom            = Camille
 ptr->nom         = Camille
 (*ptr).age       = 23
 sizeof(Personne) = 36 octets
--- R4 : pointeurs ---
 apres doubler_copie(x) : x = 21
 apres doubler_vrai(&x) : x = 42
 p == NULL : true
 test tableau (tab_test[0]) : 999
--- R5 : memoire dynamique ---
 tab = 0 1 4 9 16
 apres realloc a 10 : 0 1 4 9 16 25 36 49 64 81
 libere, pointeur remis a NULL
--- R6 : liste chainee ---
 liste : 50 -> 40 -> 30 -> 20 -> 10 -> NULL
 longueur : 5
 contient 30 : oui
 contient 99 : non
 liste vide, contient 30 : non
 apres inserer_en_queue(5) [5 maillons parcourus] : 50 -> 40 -> 30 -> 20 -> 10 -> 5 -> NULL
 apres suppression de 50 et 20 : 40 -> 30 -> 10 -> 5 -> NULL
 liberee
--- R7 : compter les operations ---
        n     simple     double     moitie    n_log_n
       10         10        100          4         40
      100        100      10000          7        700
     1000       1000    1000000         10      10000
```

## Exercice 0

Les fichiers `.o` et l'exécutable sont générés pendant la compilation. Je ne les versionne pas, car ils peuvent être recréés à partir des sources et dépendent de la machine.

## Exercice 1

| Question | Réponse |
| --- | --- |
| A | `main.c` utilise `Maillon`, donc sa définition doit être dans `liste.h` pour être connue des autres fichiers. |
| B | `liste.c` inclut `liste.h` pour vérifier que les fonctions définies correspondent bien à leurs déclarations. |

## Exercice 2

Sortie attendue :

```text
liste     : 50 -> 40 -> 30 -> 20 -> 10 -> NULL
longueur  : 5
contient 30 : oui
liberee
```

| Question | Réponse |
| --- | --- |
| A | Deux fichiers objets : `main.o` et `liste.o`. Il n'y a pas de `liste.h.o`, car le fichier d'en-tête est inclus dans les fichiers `.c`, il ne se compile pas seul. |
| B | En une étape, les deux fichiers sont recompilés à chaque fois. En deux étapes, on peut garder les objets et ne recompiler que le fichier qui a changé. |

## Exercice 3

Les messages exacts dépendent du compilateur utilisé. Les premiers messages attendus sont :

| Cas | Premier message attendu | Compilation ou lien |
| --- | --- | --- |
| 1 | `undefined reference to ...` pour les fonctions `liste_*`, puis `ld returned 1 exit status` | Éditeur de liens |
| 2 | `unknown type name 'Maillon'` | Compilation |
| 3 | `redefinition of 'struct Maillon'` ou `conflicting types for 'Maillon'` | Compilation |

| Question | Réponse |
| --- | --- |
| 1 | Le cas 1 vient de l'éditeur de liens : il indique que les fonctions `liste_*` n'ont pas été trouvées. |
| 2 | Le premier message, `unknown type name 'Maillon'`, indique le problème. Les suivants en découlent. |
| 3 | L'erreur peut arriver quand un fichier `.h` est inclus plusieurs fois, directement ou par l'intermédiaire d'un autre en-tête. |

## Exercice 4

| Question | Réponse |
| --- | --- |
| A | `make` ne recompile rien parce que les fichiers produits sont plus récents que leurs sources. |
| B | `make` affiche généralement `missing separator`. Une commande de recette doit commencer par une tabulation. |

## Exercice 5

| Étape | Ce que make recompile |
| --- | --- |
| 2, avec la dépendance | `main.o` et `liste.o`, puis l'édition des liens de `demo` |
| 4, sans la dépendance de `main.o` | `liste.o`, puis l'édition des liens de `demo`; `main.o` n'est pas recompilé |

| Question | Réponse |
| --- | --- |
| A | Avec la dépendance, `main.o` et `liste.o` sont recompilés. Sans elle, seul `liste.o` est recompilé, puis `demo` est relié. |
| B | `main.o` garde l'ancienne définition de `Maillon`, tandis que `liste.o` utilise la nouvelle. Les deux fichiers peuvent alors interpréter la structure différemment et le programme risque de mal fonctionner. |

La dépendance à `liste.h` est bien présente dans le Makefile final.
