  /*
 * Field.cpp
 *
*/

/* Inclusion du fichier d'en tête  */
#include "FVM/Core/Field.h"

/*    Inclusion des bibliothèques   */
#include <cstdlib> // Pour std::abs.

/*    Autres fichiers d'en-tête     */

namespace FVM {

  Field<double> operator-(const Vectorb& vec, const Field<double>& field) {
        if (vec.getSize() != field.getSize()) {
            std::cerr << "Les tailles du vecteur et du champ ne correspondent pas pour la soustraction." << std::endl;
            return Field<double>(0);
        }

        Field<double> result(vec.getSize());
        for (size_t i = 0; i < vec.getSize(); ++i) {
            result.setField(i, vec.getCoefficient(i) - field.getField(i));
        }
        return result;
    }


    Field<double> operator-(const Field<double>& field, const Vectorb& vec) {
        if (vec.getSize() != field.getSize()) {
            std::cerr << "Les tailles du vecteur et du champ ne correspondent pas pour la soustraction." << std::endl;
            return Field<double>(0);
        }

        Field<double> result(vec.getSize());
        for (size_t i = 0; i < vec.getSize(); ++i) {
            result.setField(i, -vec.getCoefficient(i) + field.getField(i));
        }
        return result;
    }


    Field<double> operator*(const SparseMatrixDIA& mat, const Field<double>& field) {
        if (mat.getSize() != field.getSize()) {
            std::cerr << "Les tailles de la matrice et du champ ne correspondent pas pour la multiplication." << std::endl;
            return Field<double>(0);
        }

        Field<double> result(field.getSize());
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