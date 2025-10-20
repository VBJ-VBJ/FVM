/*
 * SourceTerm.h
 *
 *     Créé le : 20 octobre 2025
 *      Auteur : VBJ
 * Description : Construit le terme source de l'équation.
*/

#ifndef INCLUDE_FVM_DISCRETISATION_SOURCETERM_SOURCETERM_H 
#define INCLUDE_FVM_DISCRETISATION_SOURCETERM_SOURCETERM_H 

/*    Inclusion des bibliothèques   */

/* Inclusion des fichiers d'en-tête */
#include "FVM/Core/CellField.h"

namespace FVM{

    class Vertex2D;
    class Vectorb;
    class SparseMatrixDIA;


    class SourceTerm {
    public:
        virtual ~SourceTerm() {}

        /**
        * Applique la contribution du terme source au système linéaire (A, b)
        * pour une cellule donnée.
        *
        * @param A La matrice du système (généralement creuse).
        * @param b Le vecteur second membre.
        * @param field Le champ.
        */
        virtual void apply(SparseMatrixDIA& A, 
                        Vectorb& b, 
                        const ScalarCellField& field) const = 0;
    };

}

#endif // INCLUDE_FVM_DISCRETISATION_SOURCETERM_SOURCETERM_H 