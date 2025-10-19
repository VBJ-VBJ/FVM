/*
 * PoissonEquation.cpp
 *
*/

/* Inclusion du fichier d'en tête  */
#include "FVM/Discretization/GaussLaplacianScheme.h"

/*    Inclusion des bibliothèques   */

/*    Autres fichiers d'en-tête     */
#include "FVM/LinearSolver/SparseMatrixDIA.h"
#include "FVM/LinearSolver/Vectorb.h"
#include "FVM/Core/CellField.h"
#include "FVM/Core/SurfaceField.h"


void FVM::apply(SparseMatrixDIA& A, Vectorb& b, const ScalarCellField& phi) const
{
    FVM::ScalarSurfaceField gammaSurface = gammaInterpolator_->interpolate(gamma_);
    

}





