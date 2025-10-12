/*
 * MeshFactory.h
 *
 *     Créé le : 11 octobre 2025
 *      Auteur : VBJ
 * Description : Fonctions responsables de la création de maillages 2D ordonnés.
*/

#ifndef INCLUDE_FVM_I_O_MESHFACTORY_H
#define INCLUDE_FVM_I_O_MESHFACTORY_H

/*    Inclusion des bibliothèques   */

/* Inclusion des fichiers d'en-tête */
#include "FVM/Core/Vertex2D.h"
#include "FVM/Core/Mesh2D.h"

namespace FVM {

    /*
    * @function uniformMeshing
    * @brief Cette fonction permet de creer un maillage uniforme.
    * @param Nx Nombre de mailles par lignes.
    * @param Ny Nombre de mailles par colonnes.
    * @param L Longueur de la plaque.
    * @param H Hauteur de la plaque.
    */
    FVM::Mesh2D uniformMeshing(size_t Nx, size_t Ny,double L, double H);


    /* 
    * @function cosMeshing
    * @brief Cette fonction permet de créer un maillage non uniforme généré grâce à une fonction cosinus.
    * @param Nx Nombre de mailles par lignes.
    * @param Ny Nombre de mailles par colonnes.
    * @param L Longueur de la plaque.
    * @param H Hauteur de la plaque.
    */
    FVM::Mesh2D cosMeshing(size_t Nx, size_t Ny,double L, double H);

}

#endif // INCLUDE_FVM_I_O_MESHFACTORY_H
