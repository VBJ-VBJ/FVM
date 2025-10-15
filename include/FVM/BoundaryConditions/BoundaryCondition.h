/*
 * BoundaryCondition.h
 *
 *     Créé le : 14 octobre 2025
 *      Auteur : VBJ
 * Description : Classe abstraite représentant les conditions aux limites.
*/

#ifndef INCLUDE_FVM_BOUNDARYCONDITION_BOUNDARYCONDITION_H
#define INCLUDE_FVM_BOUNDARYCONDITION_BOUNDARYCONDITION_H

/*    Inclusion des bibliothèques   */

/* Inclusion des fichiers d'en-tête */
#include "FVM/LinearSolver/SparseMatrixDIA.h"
#include "FVM/LinearSolver/Vectorb.h"
#include "FVM/Core/Utils.h"

namespace FVM{

    class BoundaryCondition {
public:

    virtual ~BoundaryCondition() = default;

    virtual void apply(SparseMatrixDIA& A, Vectorb& b, size_t i, size_t j) const = 0;
};

}

#endif // INCLUDE_FVM_BOUNDARYCONDITION_BOUNDARYCONDITION_H