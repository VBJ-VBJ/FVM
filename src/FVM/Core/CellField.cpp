/*
 * CellField.cpp
 *
*/

/* Inclusion du fichier d'en tête  */
#include "FVM/Core/CellField.h"

/*    Inclusion des bibliothèques   */
#include <cstdlib> // Pour std::abs.

/*    Autres fichiers d'en-tête     */
#include "FVM/BoundaryConditions/DirichletCondition.h"

namespace FVM {

  ScalarCellField operator-(const Vectorb& vec, const ScalarCellField& field) {
        if (vec.getSize() != field.getSize()) {
            throw std::runtime_error("Les tailles du vecteur et du champ ne correspondent pas pour la soustraction.");
        }

        ScalarCellField result(field.getMesh());
        for (size_t i = 0; i < vec.getSize(); ++i) {
            result.setField(i, vec.getCoefficient(i) - field.getField(i));
        }
        return result;
    }


    ScalarCellField operator-(const ScalarCellField& field, const Vectorb& vec) {
        if (vec.getSize() != field.getSize()) {
            throw std::runtime_error("Les tailles du vecteur et du champ ne correspondent pas pour la soustraction.");
        }

        ScalarCellField result(field.getMesh());
        for (size_t i = 0; i < vec.getSize(); ++i) {
            result.setField(i, -vec.getCoefficient(i) + field.getField(i));
        }
        return result;
    }


    ScalarCellField operator*(const SparseMatrixDIA& mat, const ScalarCellField& field) {
        if (mat.getSize() != field.getSize()) {
            throw std::runtime_error("Les tailles de la matrice et du champ ne correspondent pas pour la multiplication.");
        }

        ScalarCellField result(field.getMesh()) ;
        for (size_t i = 0; i < field.getSize(); ++i) {
            double sum = 0.0;
            for (auto& offset : mat.getOffsets()) {
                if (offset > 0 && i < field.getSize() - offset) 
                    sum += mat.getCoefficient(i, offset) * field.getField(static_cast<size_t>(i + offset));
                if (offset < 0 && i >= static_cast<size_t>(-offset))
                    sum += mat.getCoefficient(i, offset) * field.getField(static_cast<size_t>(i + offset));
                if (offset == 0)
                    sum += mat.getCoefficient(i, offset) * field.getField(i);
            }
            result.setField(i, sum);
        }
        return result;
    }


    

}