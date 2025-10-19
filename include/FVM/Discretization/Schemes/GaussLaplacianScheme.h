/*
 * GaussLaplacianScheme.h
 *
 *     Créé le : 14 octobre 2025
 *      Auteur : VBJ
 * Description : Définit une classe abstraite qui permet de discrétiser l'opérateur Laplacien.
*/

#ifndef INCLUDE_FVM_DISCRETISATION_SCHEMES_GAUSSLAPLACIANSCHEME_H 
#define INCLUDE_FVM_DISCRETISATION_SCHEMES_GAUSSLAPLACIANSCHEME_H 

/*    Inclusion des bibliothèques   */


/* Inclusion des fichiers d'en-tête */
#include "DiscretizationScheme.h"

namespace FVM{

    class Mesh2D; 

    class GaussLaplacianScheme {
    public:

        /**
         * @brief Constructeur pour gamma variable.
        */
        GaussLaplacianScheme(const ScalarCellField& gamma, const Mesh2D& mesh) : mesh_(mesh), 
            gammaInterpolator_(std::make_unique<CDSScheme>(mesh_)),
            gamma_(gamma) {}

        /**
         * @brief Constructeur pour gamma constant.
        */
        GaussLaplacianScheme(double gamma, const Mesh2D& mesh) : mesh_(mesh), 
            gammaInterpolator_(std::make_unique<CDSScheme>(mesh_)),
            gamma_(ScalarCellField(mesh,gamma)) {}


        virtual void apply(SparseMatrixDIA& A, Vectorb& b, const ScalarCellField& phi) const override ;

    private:
        const Mesh2D& mesh_;
        std::shared_ptr<InterpolationScheme> gammaInterpolator_ ;
        const ScalarCellField gamma_ ;
    };

}

#endif // INCLUDE_FVM_DISCRETISATION_SCHEMES_GAUSSLAPLACIANSCHEME_H 