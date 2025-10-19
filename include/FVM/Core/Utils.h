/*
 * Utils.h
 *
 *     Créé le : 14 octobre 2025
 *      Auteur : VBJ
 * Description : Regroupe plusieurs fonction utiles...
*/

#ifndef INCLUDE_FVM_CORE_UTILS_H 
#define INCLUDE_FVM_CORE_UTILS_H

/*    Inclusion des bibliothèques   */
#include <stdexcept>

/* Inclusion des fichiers d'en-tête */
#include "Mesh2D.h"

namespace FVM{

    /** 
     * @brief Cette fonction permet de convertir un couple d'indice (i,j)
     * (ligne,colonne) en un indice linéaire k.
     * @param mesh Référence vers le mesh.
     * @param i Indice de lignes.
     * @param j Indice de colonnes.
     * @return k Indice linéaire.
     * @throw std::out_of_range Si i ou j hors limite.
     */
    size_t toLinearIndex(const FVM::Mesh2D& mesh, size_t i, size_t j);


    /** 
     * @brief Cette fonction permet de convertir un couple d'indice (i,j)
     * (ligne,colonne) en un indice linéaire k.
     * @param Nx nombre de lignes.
     * @param Ny nombre de colonnes.
     * @param i Indice de lignes.
     * @param j Indice de colonnes.
     * @return k Indice linéaire.
     * @throw std::out_of_range Si i ou j hors limite.
     */
    size_t toLinearIndex(size_t Nx, size_t Ny, size_t i, size_t j);


    /**
    * @brief Convertit un indice linéaire k en indices (i, j) de matrice 2D.
    * * L'indexation linéaire originale est : k = i * (Nx + 1) + j.
    * La taille totale de la grille est implicitement (Ny + 1) x (Nx + 1).
    * * @param Nx La dimension horizontale maximale (indice de colonne maximal).
    * @param Ny La dimension verticale maximale (indice de ligne maximal).
    * @param k L'indice linéaire à convertir (doit être dans la plage [0, (Ny+1)(Nx+1) - 1]).
    * @return std::pair<size_t, size_t> Une paire où le premier élément est l'indice de ligne (i) et le second est l'indice de colonne (j).
    * @throws std::out_of_range si l'indice linéaire k est hors des limites de la matrice.
    */
    std::pair<size_t, size_t> toMatrixIndices(size_t Nx, size_t Ny, size_t k);

}

#endif // INCLUDE_FVM_CORE_UTILS_H