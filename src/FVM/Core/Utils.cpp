/*
 * Utils.cpp
 *
*/

/* Inclusion du fichier d'en tête  */
#include "FVM/Core/Utils.h"

/*    Inclusion des bibliothèques   */
#include <cassert>

/*    Autres fichiers d'en-tête     */

/**
 * @brief Convertit les index (ligne,colonne) en un index unique k.
 */
size_t FVM::toLinearIndex(const FVM::Mesh2D& mesh, size_t i, size_t j)
{
    if (i > mesh.getNy() || j > mesh.getNx()) {
        throw std::out_of_range("Indices de ligne ou de colonne hors des limites de la matrice.");
    }
    return i * (mesh.getNx() + 1) + j;
}


size_t FVM::toLinearIndex(size_t Nx, size_t Ny, size_t i, size_t j)
{
    if (i > Ny || j > Nx) {
        throw std::out_of_range("Indices de ligne ou de colonne hors des limites de la matrice.");
    }
    return i * Nx + j;
}


std::pair<size_t, size_t> FVM::toMatrixIndices(size_t Nx, size_t Ny, size_t k)
{
    const size_t step = Nx + 1;
    size_t i = k / step;
    size_t j = k % step;
    if (i > Ny) {
        throw std::out_of_range("L'indice linéaire k est hors des limites de la grille (Ny, Nx).");
    }
    return {i, j};
}
