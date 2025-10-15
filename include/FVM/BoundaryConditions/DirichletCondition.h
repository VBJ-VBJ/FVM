/*
 * DirichletCondition.h
 *
 *     Créé le : 14 octobre 2025
 *      Auteur : VBJ
 * Description : Représente les condition de Dirichlet.
*/

#ifndef INCLUDE_FVM_BOUNDARYCONDITION_DIRICHLETCONDITION_H
#define INCLUDE_FVM_BOUNDARYCONDITION_DIRICHLETCONDITION_H

/*    Inclusion des bibliothèques   */

/* Inclusion des fichiers d'en-tête */
#include "FVM/LinearSolver/SparseMatrixDIA.h"
#include "FVM/LinearSolver/Vectorb.h"
#include "FVM/Core/Utils.h"
#include "FVM/BoundaryConditions/BoundaryCondition.h"

namespace FVM{

    class DirichletCondition : public BoundaryCondition {
public:

    DirichletCondition()

    virtual void apply(SparseMatrixDIA& A, Vectorb& b, size_t i, size_t j) const override;
};

}

#endif // INCLUDE_FVM_BOUNDARYCONDITION_DIRICHLETCONDITION_H