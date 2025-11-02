# Code de Calcul par Volumes Finis (FVM) pour Maillages Quadratiques Ordonnés

## 📝 Introduction

Ce projet implémente un code de calcul basé sur la **Méthode des Volumes Finis (FVM)**, spécifiquement conçu pour la résolution d'équations aux dérivées partielles sur des **maillages quadratiques ordonnés**.

La version actuelle permet de résoudre un **problème de diffusion stationnaire avec terme source** (par exemple, l'équation de Poisson). Le code est écrit en **C++** et utilise **CMake** pour la gestion de la compilation.

---

## 🚀 Installation et Compilation

### Prérequis

Assurez-vous d'avoir installé :
* `git`
* `cmake` (version 3.10 ou supérieure recommandée)
* Un compilateur C++ (e.g., GCC ou Clang)

### Étapes

1.  **Clonage du dépôt** :

    ```bash
    git clone [https://github.com/VBJ-VBJ/FVM.git](https://github.com/VBJ-VBJ/FVM.git)
    cd FVM
    ```

2.  **Configuration du projet avec CMake** :

    Cette commande configure le projet et crée un dossier `build`.

    ```bash
    cmake -S . -B build
    ```

3.  **Compilation d'un exemple** :

    Rendez-vous dans le dossier `build/examples/[nom_de_l_exemple]` et compilez.

    ```bash
    cd build/examples/[nom_de_l_exemple]
    make
    ```

4.  **Exécution des Exemples** :

    Les exécutables se trouvent dans le sous-dossier `build/examples/[nom_de_l_exemple]`. Par exemple, pour lancer l'exemple de Poisson :

    ```bash
    ./build/exemples/diffusion_stationnaire_2D/diffusion_stationnaire_2D
    ```

---

## 🛠️ Fonctionnalités Implémentées

Cette version contient tous les éléments nécessaires pour résoudre un problème de diffusion stationnaire :

* **Maillage** :
    * Générateur de **maillage quadratique ordonné** uniforme et non-uniforme.
* **Discrétisation et Équations** :
    * Discrétisation du **Laplacien** : $\vec{\nabla} \cdot (\Gamma \vec{\nabla} \phi)$.
* **Conditions aux Limites** :
    * Gestion des **Conditions de Neumann** et **Conditions de Dirichlet**.
* **Solveur Linéaire** :
    * **Matrice Creuse** de type **DIA** (Diagonal Storage - stockage des diagonales non nulles uniquement).
    * Solveur itératif basé sur la méthode de **Gauss-Seidel**.
* **Post-Traitement** :
    * Possibilité d'exporter les résultats au format standard **`.vtk`** pour la visualisation.

---

## 🔮 Contenu à Venir

Le développement futur se concentrera sur les points suivants :

* **Équation de Transport** : Ajout de la discrétisation du terme de convection $\vec{\nabla} \cdot (\rho \vec{v} \phi)$.
* **Résolution Instationnaire** : Implémentation de schémas temporels pour la résolution transitoire :
    * Euler Explicite/Implicite
    * Crank-Nicolson

---

## 📖 Documentation

Pour générer une documentation complète du code source (classes, fonctions) à l'aide de **Doxygen** :

1.  Assurez-vous que Doxygen ainsi que Graphviz sont bien installés sur votre système.
2.  Après avoir configurer le projet (voir plus haut), exécutez la commande suivante depuis le dossier build (`FVM/build`) :

    ```bash
    make doc
    ```
    Les fichiers de documentation seront générés dans le dossier `doc/html/`.

---

## 💡 Exemples

Le résultat des calculs est représenté via ParaView.

### 1. Équation de Poisson (Diffusion pure avec terme source)

Résolution de l'équation de Poisson avec terme source $S$ :

$$
\Delta T = S(x,y)
$$

**Description** : L'exemple résout cette équation avec des conditions de Dirichlet, où le terme source est défini comme $S(x,y) = T_a(x,y) = \cos(\omega x) \sin(\omega y)$, permettant une comparaison directe avec la solution analytique.

<img width="772" height="477" alt="Solution numérique de l'équation de Poisson" src="https://github.com/user-attachments/assets/778e2147-fa71-4951-bce9-fe065a736129" />

### 2. Point chaud (Diffusion pure instationnaire)

Résolution de l'équation de la chaleur instationnaire.

$$
\frac{\partial T}{\partial t} + \Delta T = 0
$$

La capacité thermique du milieu ainsi que sa conductivité thermique sont égales à 1 pour l'exemple.

![ezgif com-animated-gif-maker](https://github.com/user-attachments/assets/9fafe717-09fe-4b76-b640-4e8704901219)




