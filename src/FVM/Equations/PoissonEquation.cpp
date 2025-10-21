/*
 * PoissonEquation.cpp
 *
*/

/* Inclusion du fichier d'en tête  */
#include "FVM/Equations/PoissonEquation.h"

/*    Inclusion des bibliothèques   */

/*    Autres fichiers d'en-tête     */
#include "FVM/BoundaryConditions/DirichletCondition.h"


void FVM::PoissonEquation::assemble(SparseMatrixDIA& A, Vectorb& b, const ScalarPhysicalCellField& phi)
{
    
    // Application des conditions limites
    for (const auto& pair : phi.getBoundaryConditions())
    {
        for (const auto& index : phi.getMesh().getBoundaryPatchesNodes(pair.first) )
        {
            pair.second->apply(A,b,index,phi);
        }
    }

}

void FVM::PoissonEquation::solve()
{


}