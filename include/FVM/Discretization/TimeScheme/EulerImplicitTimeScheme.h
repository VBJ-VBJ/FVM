/*
 * EulerImplicitTimeScheme.h
 *
 *     Créé le : 28 octobre 2025
 *      Auteur : VBJ
 * Description : Schéma de discrétisation en temps.
*/

#ifndef INCLUDE_FVM_TIMESCHEME_EULERIMPLICITTIMESCHEME_H 
#define INCLUDE_FVM_TIMESCHEME_EULERIMPLICITTIMESCHEME_H 

/*    Inclusion des bibliothèques   */

/* Inclusion des fichiers d'en-tête */
#include "FVM/Discretization/TimeScheme/TimeScheme.h"

namespace FVM{

    class EulerImplicitTimeScheme : public TimeScheme{
    public:

        /**
         * @brief Constructeur pour rho variable.
        */
        EulerImplicitTimeScheme(const ScalarCellField& rho, const ScalarCellField& rhoNext) : rho_(rho), rhoNext_(rhoNext) {}

        /**
         * @brief Constructeur pour rho constant.
        */
        // EulerImplicitTimeScheme(double rho, const Mesh2D& mesh) : rho_(ScalarCellField(mesh,rho)), rhoNext_(ScalarCellField(mesh,rho)) {}   

        virtual void executeTimeStep(SparseMatrixDIA& A,
                                     Vectorb& b,
                                     const ScalarCellField& phi,
                                     double dt) const override;
    
    private: 
        const ScalarCellField& rho_;
        const ScalarCellField& rhoNext_;
    };
        
}

#endif // INCLUDE_FVM_TIMESCHEME_EULERIMPLICITTIMESCHEME_H 