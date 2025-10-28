/*
 * SpatialDirichletCondition.cpp
 *
*/

/* Inclusion du fichier d'en tête  */
#include "FVM/BoundaryConditions/SpatialDirichletCondition.h"

/*    Inclusion des bibliothèques   */

/*    Autres fichiers d'en-tête     */
#include "FVM/LinearSolver/SparseMatrixDIA.h"
#include "FVM/LinearSolver/Vectorb.h"
#include "FVM/Core/CellField.h"


void FVM::SpatialDirichletCondition::apply(SparseMatrixDIA& A,Vectorb& b,size_t index,const ScalarCellField& phi) const
{
    const auto& mesh = phi.getMesh();
    A.setCoefficient(index,0,1);
    if (mesh.getdeltax_w(index) != 0)            
        A.setCoefficient(index, -1, 0);
    if (mesh.getdeltax_e(index) != 0) 
        A.setCoefficient(index, 1, 0);
    if (mesh.getdeltay_s(index) != 0) 
        A.setCoefficient(index, -(mesh.getNx()+1), 0);
    if (mesh.getdeltay_n(index) != 0) 
        A.setCoefficient(index, mesh.getNx()+1, 0);
    b.setValue(index,spatialFunction_(phi.getFieldNode(index).getX(),phi.getFieldNode(index).getY()));
    std::cout << "Apply du terme source noeud : " << index << std::endl;
}