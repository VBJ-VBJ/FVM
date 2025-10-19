/*
 * InterpolationScheme.h
 *
 *     Créé le : 18 octobre 2025
 *      Auteur : VBJ
 * Description : Interface pour interpoler un champ sur la face du volume de contrôle.
*/

#ifndef FVM_INTERPOLATION_INTERPOLATIONSCHEME
#define FVM_INTERPOLATION_INTERPOLATIONSCHEME

/*    Inclusion des bibliothèques   */

/* Inclusion des fichiers d'en-tête */


namespace FVM{

    class Mesh2D;

    template <typename T>
    class SurfaceField;
    using ScalarSurfaceField = SurfaceField<double>;

    template <typename T>
    class CellField;
    using ScalarCellField = CellField<double>;

    class InterpolationScheme{
    public:
        
        /** @brief Constructeur de base à partir du maillage. */
        InterpolationScheme(const Mesh2D& mesh) : mesh_(mesh) {}

        virtual ~InterpolationScheme() = default;

        virtual ScalarSurfaceField interpolate(const ScalarCellField& cellField) const = 0;

    protected:

        /** @brief Référence vers le maillage sur lequel on réalise l'interpolation. */
        const Mesh2D& mesh_ ; 
    };

}


#endif // FVM_INTERPOLATION_INTERPOLATIONSCHEME