/*
 * PoissonEquation.h
 *
 *     Créé le : 14 octobre 2025
 *      Auteur : VBJ
 * Description : Résout l'équation de Poisson "/\T = S".
*/

#ifndef INCLUDE_FVM_EQUATIONS_EQUATIONPOISSON_H 
#define INCLUDE_FVM_EQUATIONS_EQUATIONPOISSON_H 

/*    Inclusion des bibliothèques   */


/* Inclusion des fichiers d'en-tête */
#include "FVM/Core/Mesh2D.h"
#include "FVM/LinearSolver/SparseMatrixDIA.h"
#include "FVM/Core/Field.h"
#include "FVM/Equations/Equation.h"

namespace FVM{

    class PoissonEquation : Equation<ScalarField> {
    public:

        /**
         * @brief Constructeur de l'équation de Poisson.
         * @param phi Le champ scalaire à résoudre.
         * @param source Le champ source.
         */
        PoissonEquation(const ScalarField& phi, const ScalarField& source) : phi_(phi), source_(source) {};

        /**
         * @brief Construit les matrices A et b du sytème linéaire.
         * @param A Matrice A.
         * @param b Vecteur source b.
         * @param phi Champ scalaire à déterminer associé à un maillage.
         */
        virtual void assemble(SparseMatrixDIA& A, Vectorb& b, const ScalarField& phi) override;

        /**
         * @brief Résout le système linéaire Ax = b.
         */
        virtual void solve() override;

    private:

        /** @brief Champ scalaire inconnu de l'équation. */
        const ScalarField& phi_; 
        
        /** @brief Terme source de l'équation. */
        const ScalarField& source_;         
    };

}

#endif // INCLUDE_FVM_EQUATIONS_EQUATIONPOISSON_H 