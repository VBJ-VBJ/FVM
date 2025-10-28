/*
 * PoissonEquation.cpp
 *
*/

/* Inclusion du fichier d'en tête  */
#include "FVM/Discretization/Schemes/GaussLaplacianScheme.h"

/*    Inclusion des bibliothèques   */

/*    Autres fichiers d'en-tête     */
#include "FVM/Core/Utils.h"

namespace FVM{

void GaussLaplacianScheme::apply(SparseMatrixDIA& A, Vectorb& b, const ScalarCellField& phi) const
{
    ScalarSurfaceField gammaSurface = gammaInterpolator_->interpolate(gamma_);
    
    for (size_t nodeId = 0 ; nodeId < (mesh_.getNx()+1)*(mesh_.getNy()+1) ; ++nodeId)
    {
        const auto [i,j] = toMatrixIndices(phi.getMesh().getNx(), phi.getMesh().getNy(), nodeId);

        double a_W{0};
        double a_E{0};
        double a_P{0};
        double a_S{0};
        double a_N{0};
        
        if (mesh_.getdeltax_w(nodeId) != 0)
        {
            a_W = gammaSurface.getField(mesh_.getWestFaceId(nodeId))*mesh_.getDeltay(nodeId)/mesh_.getdeltax_w(nodeId);
            A.addCoefficient(nodeId, -1, a_W);
        }
        if (mesh_.getdeltax_e(nodeId) != 0)
        {
            a_E = gammaSurface.getField(mesh_.getEastFaceId(nodeId))*mesh_.getDeltay(nodeId)/mesh_.getdeltax_e(nodeId);
            A.addCoefficient(nodeId, 1, a_E);
        }
        if (mesh_.getdeltay_n(nodeId) != 0)
        {
            a_N = gammaSurface.getField(mesh_.getNorthFaceId(nodeId))*mesh_.getDeltax(nodeId)/mesh_.getdeltay_n(nodeId);
            A.addCoefficient(nodeId, mesh_.getNx()+1, a_N);
        }
        if (mesh_.getdeltay_s(nodeId) != 0)
        {
            a_S = gammaSurface.getField(mesh_.getSouthFaceId(nodeId))*mesh_.getDeltax(nodeId)/mesh_.getdeltay_s(nodeId);
            A.addCoefficient(nodeId, -(mesh_.getNx()+1), a_S);
        }
        a_P = a_W + a_E +a_N + a_S;
        A.addCoefficient(nodeId, 0, -a_P); 
    }   
        

}

}




