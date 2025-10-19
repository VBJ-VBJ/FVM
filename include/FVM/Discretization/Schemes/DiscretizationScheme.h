/*
 * DiscretizationScheme.h
 *
 *     Créé le : 14 octobre 2025
 *      Auteur : VBJ
 * Description : Définit une classe abstraite qui permet de discrétiser l'opérateur Laplacien.
*/

#ifndef INCLUDE_FVM_DISCRETISATION_SCHEMES_DISCRETIZATIONSCHEME_H 
#define INCLUDE_FVM_DISCRETISATION_SCHEMES_DISCRETIZATIONSCHEME_H 

/*    Inclusion des bibliothèques   */

/* Inclusion des fichiers d'en-tête */

namespace FVM{

    class SparseMatrixDIA;
    class Vectorb;

    template <typename T>
    class CellField;
    using ScalarCellField = CellField<double>;

    class DiscretizationScheme {
    public:
        virtual void apply(SparseMatrixDIA& A, Vectorb& b, const ScalarCellField& phi) const = 0;
    };

}

#endif // INCLUDE_FVM_DISCRETISATION_SCHEMES_DISCRETIZATIONSCHEME_H 