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
    
    // Noeuds centraux 
    for (size_t i = 1 ; i < mesh_.getNy() ; ++i)
    {
        for (size_t j = 1 ; j < mesh_.getNx() ; ++j)
        {
            size_t nodeId = toLinearIndex(mesh_,i, j);
            double a_W = gammaSurface.getField(mesh_.getWestFaceId(nodeId))*mesh_.getDeltay(nodeId)/mesh_.getdeltax_w(nodeId);
            double a_E = gammaSurface.getField(mesh_.getEastFaceId(nodeId))*mesh_.getDeltay(nodeId)/mesh_.getdeltax_e(nodeId);
            double a_N = gammaSurface.getField(mesh_.getNorthFaceId(nodeId))*mesh_.getDeltax(nodeId)/mesh_.getdeltay_n(nodeId);
            double a_S = gammaSurface.getField(mesh_.getSouthFaceId(nodeId))*mesh_.getDeltax(nodeId)/mesh_.getdeltay_s(nodeId);
            double a_P = a_W + a_E +a_N + a_S;
            A.addCoefficient(nodeId, -1, a_W); // W
            A.addCoefficient(nodeId, 0, -a_P); // P
            A.addCoefficient(nodeId, 1, a_E); // E
            A.addCoefficient(nodeId, mesh_.getNx(), a_N); // N
            A.addCoefficient(nodeId, -mesh_.getNx(), a_S); // S
        }
    }

    // Noeuds à gauche
    for (size_t i = 1 ; i < mesh_.getNy() ; ++i)
    {
        size_t j = 0;
        size_t nodeId = toLinearIndex(mesh_,i, j);
        double a_E = gammaSurface.getField(mesh_.getEastFaceId(nodeId))*mesh_.getDeltay(nodeId)/mesh_.getdeltax_e(nodeId);
        double a_N = gammaSurface.getField(mesh_.getNorthFaceId(nodeId))*mesh_.getDeltax(nodeId)/mesh_.getdeltay_n(nodeId);
        double a_S = gammaSurface.getField(mesh_.getSouthFaceId(nodeId))*mesh_.getDeltax(nodeId)/mesh_.getdeltay_s(nodeId);
        double a_P = a_E +a_N + a_S;
        A.addCoefficient(nodeId, 0, -a_P); // P
        A.addCoefficient(nodeId, 1, a_E); // E
        A.addCoefficient(nodeId, mesh_.getNx(), a_N); // N
        A.addCoefficient(nodeId, -mesh_.getNx(), a_S); // S
    }

    // Noeuds à droite
    for (size_t i = 1 ; i < mesh_.getNy() ; ++i)
    {
        size_t j = mesh_.getNx();
        size_t nodeId = toLinearIndex(mesh_,i, j);
        double a_W = gammaSurface.getField(mesh_.getWestFaceId(nodeId))*mesh_.getDeltay(nodeId)/mesh_.getdeltax_w(nodeId);
        double a_N = gammaSurface.getField(mesh_.getNorthFaceId(nodeId))*mesh_.getDeltax(nodeId)/mesh_.getdeltay_n(nodeId);
        double a_S = gammaSurface.getField(mesh_.getSouthFaceId(nodeId))*mesh_.getDeltax(nodeId)/mesh_.getdeltay_s(nodeId);
        double a_P = a_W +a_N + a_S;
        A.addCoefficient(nodeId, -1, a_W); // W
        A.addCoefficient(nodeId, 0, -a_P); // P
        A.addCoefficient(nodeId, mesh_.getNx(), a_N); // N
        A.addCoefficient(nodeId, -mesh_.getNx(), a_S); // S
    }

    // Noeud en haut
    for (size_t j = 1 ; j < mesh_.getNx() ; ++j)
    {
        size_t i = mesh_.getNy();
        size_t nodeId = toLinearIndex(mesh_,i, j);
        double a_E = gammaSurface.getField(mesh_.getEastFaceId(nodeId))*mesh_.getDeltay(nodeId)/mesh_.getdeltax_e(nodeId);
        double a_W = gammaSurface.getField(mesh_.getWestFaceId(nodeId))*mesh_.getDeltay(nodeId)/mesh_.getdeltax_w(nodeId);
        double a_S = gammaSurface.getField(mesh_.getSouthFaceId(nodeId))*mesh_.getDeltax(nodeId)/mesh_.getdeltay_s(nodeId);
        double a_P = a_W +a_E+ a_S;
        A.addCoefficient(nodeId, -1, a_W); // W
        A.addCoefficient(nodeId, 0, -a_P); // P
        A.addCoefficient(nodeId, 1, a_E); // P
        A.addCoefficient(nodeId, -mesh_.getNx(), a_S); // S
    }

    // Noeuds en bas.
    for (size_t j = 1 ; j < mesh_.getNx() ; ++j)
    {
        size_t i = 0;
        size_t nodeId = toLinearIndex(mesh_,i, j);
        double a_E = gammaSurface.getField(mesh_.getEastFaceId(nodeId))*mesh_.getDeltay(nodeId)/mesh_.getdeltax_e(nodeId);
        double a_W = gammaSurface.getField(mesh_.getWestFaceId(nodeId))*mesh_.getDeltay(nodeId)/mesh_.getdeltax_w(nodeId);
        double a_N = gammaSurface.getField(mesh_.getNorthFaceId(nodeId))*mesh_.getDeltax(nodeId)/mesh_.getdeltay_n(nodeId);
        double a_P = a_W +a_E+ a_N;
        A.addCoefficient(nodeId, -1, a_W); // W
        A.addCoefficient(nodeId, 0, -a_P); // P
        A.addCoefficient(nodeId, 1, a_E); // P
        A.addCoefficient(nodeId, mesh_.getNx(), a_N); // N
    }

    // Coin bas gauche
    size_t i = 0 ;
    size_t j = 0 ; 
    size_t nodeId = toLinearIndex(mesh_,i, j);
    double a_E = gammaSurface.getField(mesh_.getEastFaceId(nodeId))*mesh_.getDeltay(nodeId)/mesh_.getdeltax_e(nodeId);
    double a_N = gammaSurface.getField(mesh_.getNorthFaceId(nodeId))*mesh_.getDeltax(nodeId)/mesh_.getdeltay_n(nodeId);
    double a_P = a_E +a_N;
    A.addCoefficient(nodeId, 0, -a_P); // P
    A.addCoefficient(nodeId, 1, a_E); // E
    A.addCoefficient(nodeId, mesh_.getNx(), a_N); // N

    // Coin bas droite 
    i = 0;
    j = mesh_.getNx(); 
    nodeId = toLinearIndex(mesh_,i, j);
    double a_W = gammaSurface.getField(mesh_.getWestFaceId(nodeId))*mesh_.getDeltay(nodeId)/mesh_.getdeltax_w(nodeId);
    a_N = gammaSurface.getField(mesh_.getNorthFaceId(nodeId))*mesh_.getDeltax(nodeId)/mesh_.getdeltay_n(nodeId);
    a_P = a_W+ a_N;
    A.addCoefficient(nodeId, -1, a_W); // W
    A.addCoefficient(nodeId, 0, -a_P); // P
    A.addCoefficient(nodeId, mesh_.getNx(), a_N); // N

    // Coin haut gauche 
    i = mesh_.getNy();
    j = 0 ; 
    nodeId = toLinearIndex(mesh_,i, j);
    a_E = gammaSurface.getField(mesh_.getEastFaceId(nodeId))*mesh_.getDeltay(nodeId)/mesh_.getdeltax_e(nodeId);
    double a_S = gammaSurface.getField(mesh_.getSouthFaceId(nodeId))*mesh_.getDeltax(nodeId)/mesh_.getdeltay_s(nodeId);
    a_P = a_E+ a_S;
    A.addCoefficient(nodeId, 0, -a_P); // P
    A.addCoefficient(nodeId, 1, a_E); // E
    A.addCoefficient(nodeId, -mesh_.getNx(), a_S); // S

    // Coin haut droite
    i = mesh_.getNy();
    j = mesh_.getNx(); 
    nodeId = toLinearIndex(mesh_,i, j);
    a_W = gammaSurface.getField(mesh_.getWestFaceId(nodeId))*mesh_.getDeltay(nodeId)/mesh_.getdeltax_w(nodeId);
    a_S = gammaSurface.getField(mesh_.getSouthFaceId(nodeId))*mesh_.getDeltax(nodeId)/mesh_.getdeltay_s(nodeId);
    a_P = a_W+ a_S;
    A.addCoefficient(nodeId, 0, -a_P); // P
    A.addCoefficient(nodeId, -1, a_W); // W
    A.addCoefficient(nodeId, -mesh_.getNx(), a_S); // S
}

}




