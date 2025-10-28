/*
 * SpatialNeumannCondition.h
 *
 *     Créé le : 23 octobre 2025
 *      Auteur : VBJ
 * Description : Représente les conditions de Neumann avec une fonction dépendant de l'espace.
*/

#ifndef INCLUDE_FVM_BOUNDARYCONDITION_SPATIALNEUMANNCONDITION_H
#define INCLUDE_FVM_BOUNDARYCONDITION_SPATIALNEUMANNCONDITION_H

/*    Inclusion des bibliothèques   */
#include <cstddef>
#include <functional>

/* Inclusion des fichiers d'en-tête */
#include "FVM/BoundaryConditions/BoundaryCondition.h"

namespace FVM{

    using SpatialFunction = std::function<double(double,double)>;

    class SpatialNeumannCondition : public BoundaryCondition {
    public:

        /** @brief Initialise la valeur de la condition limite. */
        SpatialNeumannCondition(SpatialFunction spatialFunction, double gamma) : spatialFunction_(spatialFunction), u_(0), gamma_(gamma) {};

        SpatialNeumannCondition(SpatialFunction spatialFunction, double gamma, double u) : spatialFunction_(spatialFunction), u_(u), gamma_(gamma) {};

        /** 
         * @brief Applique la condition limite au point donné. 
         * @param A Matrice A à construire.
         * @param b Vecteur source b à construire.
         * @param index Index du noeud où appliquer les CL.
        */
        virtual void apply(SparseMatrixDIA& A, Vectorb& b, size_t index,const ScalarCellField& phi) const override;

    private: 
        SpatialFunction spatialFunction_; 
        double u_;
        double gamma_;

};

}

#endif // INCLUDE_FVM_BOUNDARYCONDITION_SPATIALNEUMANNCONDITION_H