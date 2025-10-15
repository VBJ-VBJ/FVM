/*
 * LinearSolver.h
 *
 *     Créé le : 11 octobre 2025
 *      Auteur : VBJ
 * Description : Interface pour les solveurs de systèmes linéaires.
*/

#ifndef INCLUDE_FVM_LINEARSOLVER_LINEARSOLVER_H
#define INCLUDE_FVM_LINEARSOLVER_LINEARSOLVER_H

/*    Inclusion des bibliothèques   */
#include <memory>

/* Inclusion des fichiers d'en-tête */
#include "FVM/LinearSolver/SparseMatrixDIA.h"
#include "FVM/LinearSolver/Vectorb.h"
#include "FVM/Core/Field.h"

namespace FVM {

    class LinearSolver {
    public:
        virtual ~LinearSolver() = default;

        /**
         * @brief Résout le système linéaire Ax = b.
         * @param A Matrice du système linéaire.
         * @param b Vecteur du système linéaire.
         * @return Vecteur solution x.
         */
        virtual void solve(const SparseMatrixDIA& A, const Vectorb& b, scalarField& x) = 0;
    };

}

#endif // INCLUDE_FVM_LINEARSOLVER_LINEARSOLVER_H
