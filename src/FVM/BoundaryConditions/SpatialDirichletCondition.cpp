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
    for (size_t index = 0 ; index < phi.getSize() ; ++index)
    {
        A.setCoefficient(index,0,1);
        b.setValue(index,spatialFunction_(phi.getFieldNode(index).getX(),phi.getFieldNode(index).getY()));
    }
}