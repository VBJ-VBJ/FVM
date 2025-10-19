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
#include "FVM/Core/PhysicalCellField.h"
#include "FVM/Equations/Equation.h"

namespace FVM{

    class PoissonEquation : Equation<ScalarPhysicalCellField> {
    public:

        /**
         * @brief Constructeur de l'équation de Poisson.
         * @param phi Le champ scalaire à résoudre.
         * @param source Le champ source.
         */
        PoissonEquation(const ScalarPhysicalCellField& phi, const ScalarCellField& source) : phi_(phi), source_(source) {};

        /**
         * @brief Construit les matrices A et b du sytème linéaire.
         * @param A Matrice A.
         * @param b Vecteur source b.
         * @param phi Champ scalaire à déterminer associé à un maillage.
         */
        virtual void assemble(SparseMatrixDIA& A, Vectorb& b, const ScalarPhysicalCellField& phi) override;

        /**
         * @brief Résout le système linéaire Ax = b.
         */
        virtual void solve() override;

    private:

        /** @brief Champ scalaire inconnu de l'équation. */
        const ScalarPhysicalCellField& phi_; 
        
        /** @brief Terme source de l'équation. */
        const ScalarCellField& source_;         
    };

}

#endif // INCLUDE_FVM_EQUATIONS_EQUATIONPOISSON_H 