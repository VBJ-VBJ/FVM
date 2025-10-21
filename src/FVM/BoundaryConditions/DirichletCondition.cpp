/*
 * DirichletCondition.cpp
 *
*/

/* Inclusion du fichier d'en tête  */
#include "FVM/BoundaryConditions/DirichletCondition.h"

/*    Inclusion des bibliothèques   */


/*    Autres fichiers d'en-tête     */
#include "FVM/LinearSolver/SparseMatrixDIA.h"
#include "FVM/LinearSolver/Vectorb.h"


void FVM::DirichletCondition::apply(SparseMatrixDIA& A, Vectorb& b, size_t index, const ScalarCellField& phi) const{

    A.setCoefficient(index,0,1);
    b.setValue(index,value_);
}
