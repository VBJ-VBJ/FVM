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
            std::cout << index<< std::endl ;
            pair.second->apply(A,b,index);
        }
    }

}

void FVM::PoissonEquation::solve()
{


}