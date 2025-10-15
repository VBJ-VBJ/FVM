/*
 * Equation.h
 *
 *     Créé le : 14 octobre 2025
 *      Auteur : VBJ
 * Description : Définit une classe de base abstraite qui représente n'importe quelle équation.
*/

#ifndef INCLUDE_FVM_EQUATIONS_EQUATIONS_H 
#define INCLUDE_FVM_EQUATIONS_EQUATIONS_H 

/*    Inclusion des bibliothèques   */


/* Inclusion des fichiers d'en-tête */
#include "FVM/Core/Mesh2D.h"
#include "FVM/LinearSolver/SparseMatrixDIA.h"
#include "FVM/Core/Field.h"

namespace FVM{

    template<typename T>
    class Equation {
    public:
        virtual ~Equation() = default;
        
        virtual void assemble(SparseMatrixDIA& A, Vectorb& b, const T& phi) = 0;
        virtual void solve() = 0;
    };

}

#endif // INCLUDE_FVM_DISCRETISATION_EQUATIONS_EQUATIONS_H 