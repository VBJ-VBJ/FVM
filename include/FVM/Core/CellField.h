/*
 * CellField.h
 *
 *     Créé le : 18 octobre 2025
 *      Auteur : VBJ
 * Description : Classe représentant un champ de valeur quelconque (scalaire ou vecteur) dans les volumes de contrôle du domaine physique discrétisé par le mesh.
*/

#ifndef INCLUDE_FVM_CORE_CELLFIELD_H
#define INCLUDE_FVM_CORE_CELLFIELD_H

/*    Inclusion des bibliothèques   */
#include <vector>
#include <iostream>
#include <cassert>
#include <cmath>
#include <memory>
#include <map>

/* Inclusion des fichiers d'en-tête */
#include "Field.h"

namespace FVM {

    template<typename T>
    class CellField : public Field<T> {
    public:

        /**
         * @brief Construction du champ à partir d'un mesh.
         */
        CellField(const Mesh2D& mesh) : Field<T>(mesh,(mesh.getNx()+1)*(mesh.getNy()+1)) {}

        /**
         * @brief Construction du champ à partir d'un mesh avec valeur initiale.
         */
        CellField(const Mesh2D& mesh,T initValue) : Field<T>(mesh,(mesh.getNx()+1)*(mesh.getNy()+1),initValue) {}

    };

    using ScalarCellField = CellField<double>;

    // Opérateur sur les champs scalaires.
    ScalarCellField operator-(const Vectorb& vec, const ScalarCellField& field);

    ScalarCellField operator-(const ScalarCellField& field, const Vectorb& vec);

    ScalarCellField operator-(const ScalarCellField& field1, const ScalarCellField& field2);

    ScalarCellField operator+(const ScalarCellField& field1, const ScalarCellField& field2);

    ScalarCellField operator/(const ScalarCellField& field1, const ScalarCellField& field2);

    ScalarCellField operator*(const ScalarCellField& field1, const ScalarCellField& field2);

    ScalarCellField operator*(double number, const ScalarCellField& field);

    ScalarCellField operator*(const SparseMatrixDIA& mat, const ScalarCellField& field); 

}

#endif // INCLUDE_FVM_CORE_CELLFIELD_H