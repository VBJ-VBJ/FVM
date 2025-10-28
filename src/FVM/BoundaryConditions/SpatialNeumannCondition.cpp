/*
 * SpatialNeumannCondition.cpp
 *
*/

/* Inclusion du fichier d'en tête  */
#include "FVM/BoundaryConditions/SpatialNeumannCondition.h"

/*    Inclusion des bibliothèques   */
#include <utility> // Pour std::pair.


/*    Autres fichiers d'en-tête     */
#include "FVM/LinearSolver/SparseMatrixDIA.h"
#include "FVM/LinearSolver/Vectorb.h"
#include "FVM/Core/Utils.h"


void FVM::SpatialNeumannCondition::apply(SparseMatrixDIA& A, Vectorb& b, size_t index, const ScalarCellField& phi) const{
    const auto& mesh = phi.getMesh();
    assert(mesh.getdeltay_s(index) == 0 ||
           mesh.getdeltay_n(index) == 0 ||
           mesh.getdeltax_e(index) == 0 ||
           mesh.getdeltax_w(index) == 0);
    if (mesh.getdeltay_s(index) == 0) // Sud.
        b.addValue(index,-gamma_*spatialFunction_(phi.getFieldNode(index).getX(),phi.getFieldNode(index).getY())*mesh.getDeltax(index));
    else if (mesh.getdeltay_n(index) == 0) // Nord.
        b.addValue(index,-gamma_*spatialFunction_(phi.getFieldNode(index).getX(),phi.getFieldNode(index).getY())*mesh.getDeltax(index));
    else if (mesh.getdeltax_w(index) == 0) // Ouest.
        b.addValue(index,-gamma_*spatialFunction_(phi.getFieldNode(index).getX(),phi.getFieldNode(index).getY())*mesh.getDeltay(index));
    else if (mesh.getdeltax_e(index) == 0) // Est.
        b.addValue(index,-gamma_*spatialFunction_(phi.getFieldNode(index).getX(),phi.getFieldNode(index).getY())*mesh.getDeltay(index)); 
}
