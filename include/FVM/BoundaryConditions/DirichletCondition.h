/*
 * DirichletCondition.h
 *
 *     Créé le : 14 octobre 2025
 *      Auteur : VBJ
 * Description : Représente les condition de Dirichlet.
*/

#ifndef INCLUDE_FVM_BOUNDARYCONDITION_DIRICHLETCONDITION_H
#define INCLUDE_FVM_BOUNDARYCONDITION_DIRICHLETCONDITION_H

/*    Inclusion des bibliothèques   */
#include <cstddef>

/* Inclusion des fichiers d'en-tête */
#include "FVM/BoundaryConditions/BoundaryCondition.h"

namespace FVM{

    class DirichletCondition : public BoundaryCondition {
    public:

        /** @brief Initialise la valeur de la condition limite. */
        DirichletCondition(double value) : value_(value) {};

        /** 
         * @brief Applique la condition limite au point donné. 
         * @param A Matrice A à construire.
         * @param b Vecteur source b à construire.
         * @param index Index du noeud où appliquer les CL.
        */
        virtual void apply(SparseMatrixDIA& A, Vectorb& b, size_t index) const override;

    private: 
        double value_ ; 

};

}

#endif // INCLUDE_FVM_BOUNDARYCONDITION_DIRICHLETCONDITION_H