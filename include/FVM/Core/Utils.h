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
     * @param i Nombre de lignes.
     * @param j Nombre de colonnes.
     * @param k Indice linéaire.
     * @throw std::out_of_range Si i ou j hors limite.
     */
    size_t toLinearIndex(const FVM::Mesh2D& mesh, size_t i, size_t j);

}

#endif // INCLUDE_FVM_CORE_UTILS_H