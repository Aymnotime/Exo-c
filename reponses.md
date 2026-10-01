# Réponses — TP séance 7 (jusqu'à l'exercice 5)

## Exercice 0

Les fichiers `.o` sont des résultats intermédiaires propres à une compilation et à une machine. L'exécutable est lui aussi généré depuis les sources. On les ignore pour éviter de versionner des artefacts reproductibles et d'écraser ceux d'un autre environnement.

## Exercice 1

| Question | Réponse |
| --- | --- |
| A | `main.c` utilise le type `Maillon` et doit connaître sa définition pour déclarer et parcourir des maillons. Le `.h` expose donc la définition partagée par le module et ses utilisateurs. |
| B | Cela vérifie que `liste.c` compile avec ses propres déclarations publiques. Si le `.h` change, une incohérence entre l'interface et les définitions est détectée lors de la compilation du module. |

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
| A | Deux fichiers objets : `main.o` et `liste.o`. Il n'y a pas de `liste.h.o` : un en-tête est inclus dans les unités de compilation, il n'est pas compilé séparément. |
| B | La commande en une étape compile et lie tout à chaque fois. Les deux étapes rendent visibles les objets séparés et permettent de ne recompiler que les sources modifiées. |

## Exercice 3

Les formulations exactes varient selon la version et le fournisseur de GCC. Relever ici les premiers messages avec le compilateur de la machine avant de comparer.

| Cas | Premier message attendu | Compilation ou lien |
| --- | --- | --- |
| 1 | `undefined reference to ...` (symboles `liste_*`) puis `collect2: error: ld returned 1 exit status` | Éditeur de liens |
| 2 | `unknown type name 'Maillon'` | Compilation |
| 3 | `redefinition of 'struct Maillon'` ou `conflicting types for 'Maillon'` | Compilation |

| Question | Réponse |
| --- | --- |
| 1 | Cas 1 : le message vient de l'éditeur de liens. Il mentionne les références non définies et `ld`/`collect2`, après la compilation de `main.c`. |
| 2 | Le premier diagnostic, `unknown type name 'Maillon'`, est la cause utile. Les autres erreurs découlent de l'absence des déclarations et du type. |
| 3 | Dès qu'un même en-tête est inclus plusieurs fois dans une unité de compilation, directement ou indirectement, par exemple dans des en-têtes imbriqués. |

## Exercice 4

| Question | Réponse |
| --- | --- |
| A | `make` compare les dates des cibles et de leurs dépendances. Après une construction réussie, `demo` est plus récent que ses objets et ceux-ci sont plus récents que leurs sources : rien n'a besoin d'être reconstruit. |
| B | Avec des espaces au début d'une recette, GNU make signale typiquement `missing separator. Stop.`. Une recette doit commencer par une tabulation. |

## Exercice 5

| Étape | Ce que make recompile |
| --- | --- |
| 2, avec la dépendance | `main.o` et `liste.o`, puis l'édition des liens de `demo` |
| 4, sans la dépendance de `main.o` | `liste.o`, puis l'édition des liens de `demo`; `main.o` n'est pas recompilé |

| Question | Réponse |
| --- | --- |
| A | Sans `liste.h` dans les dépendances de `main.o`, make ne sait pas que l'en-tête affecte `main.c`; il garde donc un objet potentiellement périmé. |
| B | L'exécutable mélange un `main.o` compilé avec l'ancienne définition de `Maillon` et `liste.o` compilé avec la nouvelle. La disposition ou la taille du type peut différer, ce qui rend le programme incohérent et son comportement indéfini. |

La dépendance à `liste.h` est rétablie dans le Makefile final. Les commandes et observations dépendant du compilateur et de `make` locaux devront être exécutées dans un environnement où ces outils sont installés.
