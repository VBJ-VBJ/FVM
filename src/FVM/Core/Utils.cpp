/*
 * Utils.cpp
 *
*/

/* Inclusion du fichier d'en tête  */
#include "FVM/Core/Utils.h"

/*    Inclusion des bibliothèques   */
#include <cassert>

/*    Autres fichiers d'en-tête     */


size_t FVM::toLinearIndex(const FVM::Mesh2D& mesh, size_t i, size_t j)
{
    if (i < 0 || i >= mesh.getNx()+1 || j < 0 || j >= mesh.getNy()+1) {
        throw std::out_of_range("Indices de ligne ou de colonne hors des limites de la matrice.");
    }
    return i * (mesh.getNy()+1) + j;
}
