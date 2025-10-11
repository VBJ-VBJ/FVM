/*
 * Vectorb.h
 *
 *     Créé le : 11 octobre 2025
 *      Auteur : VBJ
 * Description : Classe pour représenter un vecteur de nombres réels dans un système linéaire.
*/

#ifndef INCLUDE_FVM_LINEARSOLVER_VECTORD_H
#define INCLUDE_FVM_LINEARSOLVER_VECTORD_H

/*    Inclusion des bibliothèques   */
#include <vector>
#include <iostream>

/* Inclusion des fichiers d'en-tête */


namespace FVM {

    class Vectorb {
    public:
        /** 
         * @brief Constructeur par défaut.
         */
        Vectorb() : data_() {}

        /**
         * @brief Constructeur avec taille.
         * @param size Taille du vecteur.
         */
        Vectorb(size_t size) : data_(size, 0.0) {}

        /**
         * @brief Ajoute une valeur à l'élément i du vecteur.
         * @param i Index de l'élément.
         * @param value Valeur à ajouter.
         */
        void addValue(size_t i, double value);

        /**
         * @brief Retourne la valeur du coefficient à un index donné.
         */
        double getCoefficient(size_t i) const;

        /**
         * @brief Retourne la taille du vecteur.
        */
        size_t getSize() const;

        /**
         * @brief Affiche le vecteur (pour le débogage).
         */
        void print() const;

        /**
         * @brief Calcule la norme L2 du vecteur.
         * @return La norme L2 du vecteur.
         */
        double getNormL2Field() const;
    private:
        std::vector<double> data_;
    };

}

#endif // INCLUDE_FVM_LINEARSOLVER_VECTORD_H
