# Code de calcul volumes finis pour maillage quadratiques ordonnés.

## Installation

git clone https://github.com/VBJ-VBJ/FVM.git

Dans le dossier principal : 

cmake -S . -B build

Va créer un dossier build. Pour compiler les exemples, se rendre dans le dossier build et choisir le dossier de l'exemple correspondant. 

make 

Puis lancer l'exécutable.


## Documentation 

Pour générer de la documentation avec Doxygen,

## Contenu 

Cette version contient tous les éléments nécessaire pour résoudre un problème de diffusion stationnaire avec terme source.
- Matrice creuse de type DIA (stockage des diagonales non nulles uniquement)
- Solveur pour les système linéaire de type Ax = b basé sur la méthode de Gauss-Seidel.
- Discrétisation du Laplacien $\nabla(\Gamma \nabla \phi)$.
- Schéma d'interpolation CDS.
- Générateur de maillage ordonné uniforme et non-uniforme.
- Possibilité d'exporter les résultats au format .vtk.
- Conditions de Neumann et de Dirichlet.


## Contenu à venir

Contenu à venir prochainement : 
- Ajout de la discrétisation du terme de transport $\vec{\nabla}.(\rho \vec{v} \phi)$.
- Schéma temporel pour la résolution instationnaire (Euler explicite/implicite et Crank-Nicolson).

## Quelques exemples : 

### Équation de Poisson (diffusion pure avec terme source)

Résolution de l'équation de Poisson avec condition de Dirichlet et terme $S(x,y) = T_a(x,y) = cos(\omega x) sin(\omega y)$ (solution analytique connue).

$$
\Delta T = S
$$

<img width="772" height="477" alt="exemple1" src="https://github.com/user-attachments/assets/778e2147-fa71-4951-bce9-fe065a736129" />
