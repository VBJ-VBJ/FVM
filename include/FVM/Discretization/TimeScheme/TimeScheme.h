/*
 * TimeScheme.h
 *
 *     Créé le : 28 octobre 2025
 *      Auteur : VBJ
 * Description : Schéma de discrétisation en temps.
*/

#ifndef INCLUDE_FVM_TIMESCHEME_TIMESCHEME_H 
#define INCLUDE_FVM_TIMESCHEME_TIMESCHEME_H 

/*    Inclusion des bibliothèques   */

/* Inclusion des fichiers d'en-tête */
#include "FVM/Core/CellField.h"

namespace FVM{

    class Vertex2D;
    class Vectorb;
    class SparseMatrixDIA;


    class TimeScheme {
    public:
        virtual ~TimeScheme() {}

        virtual void executeTimeStep(SparseMatrixDIA& A,
                                     Vectorb& b,
                                     const ScalarCellField& phi,
                                     double dt) const = 0;
    
    };
        
}

#endif // INCLUDE_FVM_TIMESCHEME_TIMESCHEME_H 