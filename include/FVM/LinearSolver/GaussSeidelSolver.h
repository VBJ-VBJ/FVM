/*
 * GaussSeidelSolver.h
 *
 *     Créé le : 11 octobre 2025
 *      Auteur : VBJ
 * Description : Classe pour résoudre un système linéaire Ax = b en utilisant la méthode de Gauss-Seidel.
*/

#ifndef FVM_LINEARSOLVER_GAUSSSEIDELSOLVER_H
#define FVM_LINEARSOLVER_GAUSSSEIDELSOLVER_H

/*    Inclusion des bibliothèques   */
#include <memory>

/* Inclusion des fichiers d'en-tête */
#include "LinearSolver.h"


namespace FVM {

    /**
     * @class GaussSeidel
     * @brief Permet de résoudre un système linéaire de type $Ax = b$ avec la méthode itérative de Gauss-Seidel.
     *
     * @note La matrice A doit être strictement diagonale dominante pour garantir la convergence. Les éléments de la diagonale principale doivent être non nuls.
    */
    class GaussSeidelSolver : public LinearSolver {
    public:

        /** 
         * @brief Résout le système linéaire avec la méthode de Gauss-Seidel.
         * @param A Matrice A.
         * @param b Vecteur b.
         * @param x Vecteur x.
         * @note Le vecteur x doit être initialisé et de la taille du vecteur b.
         */
        virtual void solve(const SparseMatrixDIA& A, const Vectorb& b, ScalarField& x) override ;
        
        void setTolerance(double tol) { tol_ = tol; }
        void setMaxIterations(int maxIter) { maxIter_ = maxIter; }
    private:
        /** @brief Critère de tolérance. */
        double tol_ = 1e-6;

        /** @brief Maximum d'itération de l'algorithme. */
        unsigned int maxIter_ = 100;

    };

}

#endif // FVM_LINEARSOLVER_GAUSSSEIDELSOLVER_H