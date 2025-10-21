/*
 * FunctionSource.cpp
 *
*/

/* Inclusion du fichier d'en tête  */
#include "FVM/Discretization/SourceTerm/FunctionSource.h"

/*    Inclusion des bibliothèques   */

/*    Autres fichiers d'en-tête     */
#include "FVM/Core/CellField.h"
#include "FVM/LinearSolver/SparseMatrixDIA.h"
#include "FVM/LinearSolver/Vectorb.h"


void FVM::FunctionSource::apply(SparseMatrixDIA& A,Vectorb& b,const ScalarCellField& field) const
{
    for (size_t index = 0 ; index < field.getSize() ; ++index)
    {
        b.addValue(index,functionSource_(field.getFieldNode(index).getX(),field.getFieldNode(index).getY())
            *field.getMesh().getDeltax(index)*field.getMesh().getDeltay(index));
    }
}
    