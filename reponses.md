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

## Exercice 6

| Mesure | Sans fuite | Avec une liste de 3 maillons oubliée |
| --- | ---: | ---: |
| Après construction de la première liste | 5 | 5 |
| Après sa libération | 0 | 0 |
| Compteur final après ajout de la seconde liste | 0 | 3 |

| Question | Réponse |
| --- | --- |
| A | Le compteur et les fonctions de suivi sont `static` car ils ne servent qu'à `liste.c`. Le `.h` ne déclare que les fonctions accessibles depuis les autres fichiers. |
| B | Un échec de `malloc` ferait compter une allocation qui n'a pas eu lieu. Décrémenter pour `NULL` ferait baisser le compteur sans libérer de bloc. |
| C | Non. Je peux afficher le compteur après chaque allocation et libération pour réduire l'endroit où chercher, puis examiner les appels de la zone concernée. |

## Exercice 7

Pour une liste oubliée de trois maillons, le compteur reste à 3. L'outil classe normalement le premier maillon comme `definitely lost` et les deux suivants comme `indirectly lost`, car ils restent accessibles depuis le premier maillon perdu.

| Mesure | Sans fuite | Avec fuite |
| --- | ---: | ---: |
| `definitely lost` | 0 octet | `sizeof(Maillon)` |
| `indirectly lost` | 0 octet | `2 * sizeof(Maillon)` |
| Allocations / libérations du module | 5 / 5 | 8 / 5 |
| Compteur final | 0 | 3 |

Sur une cible où `Maillon` fait 16 octets, la fuite représente 48 octets. Cette taille dépend de la plateforme.

| Question | Réponse |
| --- | --- |
| A | La pile remonte à la ligne de `main.c` qui construit la liste oubliée. Le `free` manquant concerne la tête de cette seconde liste, et donc aussi les maillons qui la suivent. |
| B | Un maillon est perdu directement et les deux autres indirectement, car on pouvait les atteindre en suivant les pointeurs depuis le premier. |
| C | Sans fuite : 5 allocations et 5 libérations. Avec fuite : 8 allocations et 5 libérations. Il y a une allocation par maillon ; le nombre inclut donc tous les maillons construits dans les deux listes. |

## Exercice 8

| Observation | Résultat attendu sans outil |
| --- | --- |
| Sortie affichée | `42` |
| Code de sortie | 0 sur une exécution habituelle, mais le comportement est indéfini |
| Message de l'outil | AddressSanitizer signale un `heap-buffer-overflow` à l'accès `t[5]`; Valgrind signale un accès invalide juste après le bloc |

| Question | Réponse |
| --- | --- |
| A | Non. Il y a un `malloc` et un `free`, donc le compteur revient à zéro. Il ne détecte pas le dépassement. |
| B | Le bloc contient cinq entiers, soit 20 octets si `int` fait 4 octets. `t[5]` commence exactement après ces 20 octets, d'où le décalage de 0 octet. `t[6]` serait à 4 octets après le bloc. |
| C | Un résultat qui semble correct ne prouve pas que le programme est valide. Ici, l'accès hors limites a un comportement indéfini. |
| D | Le compteur sert à repérer rapidement un nombre d'allocations non libérées dans ce module. Pour trouver les lignes responsables ou repérer un accès mémoire invalide, j'utilise Valgrind ou AddressSanitizer. |

## Exercice 9

La fonction maximum renvoie `true` et écrit `50` pour la liste de cinq éléments. Pour `NULL`, elle renvoie `false` et ne modifie pas le résultat.

Sortie finale attendue du programme :

```text
blocs apres construction : 5
liste     : 50 -> 40 -> 30 -> 20 -> 10 -> NULL
longueur  : 5
contient 30 : oui
maximum : 50
maximum liste vide : aucun
blocs apres liberation : 0
liberee
```

| Question | Réponse |
| --- | --- |
| A | J'ai modifié `liste.h`, `liste.c` et `main.c`. Avec la règle `%.o: %.c liste.h`, `main.o` et `liste.o` sont recompilés, puis `demo` est relié. |
| B | `-1` peut être une valeur valide de la liste. Le booléen permet de distinguer sans ambiguïté une liste vide d'un maximum égal à `-1`. |
