/*
 * LaplacianScheme.h
 *
 *     Créé le : 14 octobre 2025
 *      Auteur : VBJ
 * Description : Définit une classe abstraite qui permet de discrétiser l'opérateur Laplacien.
*/

#ifndef INCLUDE_FVM_DISCRETISATION_SCHEMES_LAPLACIAN_LAPLACIANSCHEME_H 
#define INCLUDE_FVM_DISCRETISATION_SCHEMES_LAPLACIAN_LAPLACIANSCHEME_H 

/*    Inclusion des bibliothèques   */


/* Inclusion des fichiers d'en-tête */
#include "FVM/LinearSolver/SparseMatrixDIA.h"
#include "Vectorb.h"
#include "Field.h"

namespace FVM{

    class LaplacianScheme {
    public:
        virtual void discretize(SparseMatrixDIA& A, Vectorb& b, const ScalarField& phi) = 0;
    };

}

#endif // INCLUDE_FVM_DISCRETISATION_SCHEMES_LAPLACIAN_LAPLACIANSCHEME_H 