/*
 * EulerImplicitTimeScheme.cpp
 *
*/

/* Inclusion du fichier d'en tête  */
#include "FVM/Discretization/TimeScheme/EulerImplicitTimeScheme.h"

/*    Inclusion des bibliothèques   */

/*    Autres fichiers d'en-tête     */
#include "FVM/LinearSolver/SparseMatrixDIA.h"
#include "FVM/LinearSolver/Vectorb.h"


namespace FVM{

    void EulerImplicitTimeScheme::executeTimeStep(SparseMatrixDIA& A,Vectorb& b,const ScalarCellField& phi,double dt) const
    {
        const auto& mesh = phi.getMesh();
        for (size_t nodeId = 0 ; nodeId < (mesh.getNx()+1)*(mesh.getNy()+1) ; ++nodeId)
        {
            A.addCoefficient(nodeId,0,(1/dt)*rhoNext_.getField(nodeId)*mesh.getDeltax(nodeId)*mesh.getDeltay(nodeId));
            b.addValue(nodeId,(1/dt)*rho_.getField(nodeId)*phi.getField(nodeId)*mesh.getDeltax(nodeId)*mesh.getDeltay(nodeId));
        }

    }
}
