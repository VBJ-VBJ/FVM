/*
 * PoissonEquation.cpp
 *
*/

/* Inclusion du fichier d'en tête  */
#include "FVM/Equations/PoissonEquation.h"

/*    Inclusion des bibliothèques   */

/*    Autres fichiers d'en-tête     */


void FVM::PoissonEquation::assemble(SparseMatrixDIA& A, Vectorb& b, const ScalarField& phi)
{
    // Application des conditions limites

}