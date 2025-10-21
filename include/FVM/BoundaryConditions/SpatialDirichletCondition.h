/*
 * SpatialDirichletCondition.h
 *
 *     Créé le : 21 octobre 2025
 *      Auteur : VBJ
 * Description : Représente les conditions de Dirichlet avec une fonction dépendant de l'espace.
*/

#ifndef INCLUDE_FVM_BOUNDARYCONDITION_SPATIALDIRICHLETCONDITION_H
#define INCLUDE_FVM_BOUNDARYCONDITION_SPATIALDIRICHLETCONDITION_H

/*    Inclusion des bibliothèques   */
#include <cstddef>
#include <functional>

/* Inclusion des fichiers d'en-tête */
#include "FVM/BoundaryConditions/BoundaryCondition.h"

namespace FVM{

    using SpatialFunction = std::function<double(double,double)>;

    class SpatialDirichletCondition : public BoundaryCondition {
    public:

        /** @brief Initialise la valeur de la condition limite. */
        SpatialDirichletCondition(SpatialFunction spatialFunction) : spatialFunction_(spatialFunction) {};

        /** 
         * @brief Applique la condition limite au point donné. 
         * @param A Matrice A à construire.
         * @param b Vecteur source b à construire.
         * @param index Index du noeud où appliquer les CL.
        */
        virtual void apply(SparseMatrixDIA& A, Vectorb& b, size_t index,const ScalarCellField& phi) const override;

    private: 
        SpatialFunction spatialFunction_; 

};

}

#endif // INCLUDE_FVM_BOUNDARYCONDITION_SPATIALDIRICHLETCONDITION_H