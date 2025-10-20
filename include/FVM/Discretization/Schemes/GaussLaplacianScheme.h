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
#include <memory>


/* Inclusion des fichiers d'en-tête */
#include "FVM/Discretization/Schemes/DiscretizationScheme.h"
#include "FVM/Core/CellField.h"
#include "FVM/LinearSolver/SparseMatrixDIA.h"
#include "FVM/LinearSolver/Vectorb.h"
#include "FVM/Core/SurfaceField.h"
#include "FVM/Interpolation/CDSScheme.h"

namespace FVM{

    class Mesh2D; 
    class InterpolationScheme;



    class GaussLaplacianScheme : public DiscretizationScheme {
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
        ScalarCellField gamma_ ;
    };

}

#endif // INCLUDE_FVM_DISCRETISATION_SCHEMES_GAUSSLAPLACIANSCHEME_H 