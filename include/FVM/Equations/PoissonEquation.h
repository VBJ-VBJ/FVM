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

    class PoissonEquation : Equation<scalarField> {
    public:

        /**
         * @brief Constructeur de l'équation de Poisson.
         * @param phi Le champ scalaire à résoudre.
         * @param source Le champ source.
         * @param mesh Le maillage associé.
         */
        PoissonEquation(const scalarField& phi, const scalarField& source, const Mesh2D& mesh) : phi_(phi), source_(source), mesh_(mesh) {};

        /**
         * @brief 
         */
        virtual void assemble(SparseMatrixDIA& A, Vectorb& b, const scalarField& phi) override;
        virtual void solve() override;

    private:

        /** @brief Champ scalaire inconnu de l'équation. */
        const scalarField& phi_; 
        
        /** @brief Terme source de l'équation. */
        const scalarField& source_;

        /** @brief Maillage associé au domaine physique. */
        const Mesh2D& mesh_;           
    };

}

#endif // INCLUDE_FVM_EQUATIONS_EQUATIONPOISSON_H 