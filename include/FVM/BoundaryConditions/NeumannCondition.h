/*
 * NeumannCondition.h
 *
 *     Créé le : 23 octobre 2025
 *      Auteur : VBJ
 * Description : Représente les conditions de Neumann.
*/

#ifndef INCLUDE_FVM_BOUNDARYCONDITION_NEUMANNCONDITION_H
#define INCLUDE_FVM_BOUNDARYCONDITION_NEUMANNCONDITION_H

/*    Inclusion des bibliothèques   */
#include <cstddef>

/* Inclusion des fichiers d'en-tête */
#include "FVM/BoundaryConditions/BoundaryCondition.h"

namespace FVM{

    class NeumannCondition : public BoundaryCondition {
    public:

        /** @brief Initialise la valeur de la condition limite. */
        NeumannCondition(double value, double gamma) : value_(value), u_(0), gamma_(gamma) {};

        NeumannCondition(double value, double gamma, double u) : value_(value), u_(u), gamma_(gamma) {};
        

        /** 
         * @brief Applique la condition limite au point donné. 
         * @param A Matrice A à construire.
         * @param b Vecteur source b à construire.
         * @param index Index du noeud où appliquer les CL.
        */
        virtual void apply(SparseMatrixDIA& A, Vectorb& b, size_t index,const ScalarCellField& phi) const override;

    private: 
        double value_ ; 
        double u_;
        double gamma_;

};

}

#endif // INCLUDE_FVM_BOUNDARYCONDITION_NEUMANNCONDITION_H