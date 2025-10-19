/*
 * CDSScheme.h
 *
 *     Créé le : 19 octobre 2025
 *      Auteur : VBJ
 * Description : Approximation des valeurs aux faces par schéma centré (CDS).
*/

#ifndef FVM_INTERPOLATION_CDSSCHEME
#define FVM_INTERPOLATION_CDSSCHEME

/*    Inclusion des bibliothèques   */

/* Inclusion des fichiers d'en-tête */
#include "InterpolationScheme.h"

namespace FVM{

    template <typename T>
    class SurfaceField;
    using ScalarSurfaceField = SurfaceField<double>;

    template <typename T>
    class CellField;
    using ScalarCellField = CellField<double>;

    class CDSScheme : public InterpolationScheme {
    public:

        CDSScheme(const Mesh2D& mesh) : InterpolationScheme(mesh) {}

        /**
         * @brief Interpole un champ sur les faces en utilisant un schéma CDS.
         * @param cellField Champ scalaire au cnetre des volumes de contrôle (au noeud).
         * @return Le champ scalaire sur les faces.
        */
        virtual ScalarSurfaceField interpolate(const ScalarCellField& cellField) const override;

    };

}


#endif // FVM_INTERPOLATION_CDSSCHEME