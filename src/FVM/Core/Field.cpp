/*
 * Field.cpp
 *
*/

/* Inclusion du fichier d'en tête  */
#include "FVM/Core/Field.h"

/*    Inclusion des bibliothèques   */
#include <cstdlib> // Pour std::abs.

/*    Autres fichiers d'en-tête     */
#include "FVM/BoundaryConditions/DirichletCondition.h"

namespace FVM {

  ScalarField operator-(const Vectorb& vec, const ScalarField& field) {
        if (vec.getSize() != field.getSize()) {
            throw std::runtime_error("Les tailles du vecteur et du champ ne correspondent pas pour la soustraction.");
        }

        ScalarField result(field.getMesh());
        for (size_t i = 0; i < vec.getSize(); ++i) {
            result.setField(i, vec.getCoefficient(i) - field.getField(i));
        }
        return result;
    }


    ScalarField operator-(const ScalarField& field, const Vectorb& vec) {
        if (vec.getSize() != field.getSize()) {
            throw std::runtime_error("Les tailles du vecteur et du champ ne correspondent pas pour la soustraction.");
        }

        ScalarField result(field.getMesh());
        for (size_t i = 0; i < vec.getSize(); ++i) {
            result.setField(i, -vec.getCoefficient(i) + field.getField(i));
        }
        return result;
    }


    ScalarField operator*(const SparseMatrixDIA& mat, const ScalarField& field) {
        if (mat.getSize() != field.getSize()) {
            throw std::runtime_error("Les tailles de la matrice et du champ ne correspondent pas pour la multiplication.");
        }

        ScalarField result(field.getMesh()) ;
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