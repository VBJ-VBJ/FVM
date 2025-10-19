/*
 * SurfaceField.h
 *
 *     Créé le : 18 octobre 2025
 *      Auteur : VBJ
 * Description : Classe représentant un champ de valeur quelconque (scalaire ou vecteur) sur les faces des volumes de contrôle du domaine physique discrétisé par le mesh.
*/

#ifndef INCLUDE_FVM_CORE_SURFACEFIELD_H
#define INCLUDE_FVM_CORE_SURFACEFIELD_H

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

    /**
     * @brief Classe représentant un champ sur les surfaces du maillage.
     * @note On indexe d'abord les faces verticales de 0 à Nx*(Ny+1)-1 puis les faces horizontales de Nx*(Ny+1) à Nx*(Ny+1)+Ny*(Nx+1)-1.
    */
    template<typename T>
    class SurfaceField : public Field<T> {
    public:

        /**
		 * @brief Constructeur par défaut.
		 */
		SurfaceField() = default;

        /**
         * @brief Construction du champ à partir d'un mesh.
         */
        SurfaceField(const Mesh2D& mesh) :
          Field<T>(mesh,mesh.getNy()*(mesh.getNx()+1)+mesh.getNx()*(mesh.getNy()+1)) {}

    };
    using ScalarSurfaceField = SurfaceField<double>;

}

#endif // INCLUDE_FVM_CORE_SURFACEFIELD_H