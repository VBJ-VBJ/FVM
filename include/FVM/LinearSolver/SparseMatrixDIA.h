/*
 * SparseMatrixDIA.h
 *
 *     Créé le : 11 octobre 2025
 *      Auteur : VBJ
 * Description : Classe représentant la matrice A (matrice creuse au format DIA) dans un système linéaire Ax = b.
*/

#ifndef FVM_LINEARSOLVER_SPARSEMATRIXDIA_H
#define FVM_LINEARSOLVER_SPARSEMATRIXDIA_H

/*    Inclusion des bibliothèques   */
#include <vector>
#include <iostream>
#include <cassert>
#include <unordered_map>
#include <stdexcept>
#include <cstddef> // Pour size_t.

/* Inclusion des fichiers d'en-tête */
#include "Vectorb.h"


namespace FVM {

    class SparseMatrixDIA {
    public:
        /**
         *  @brief Constructeur par défaut.
        */
        SparseMatrixDIA() : N_(0), N_diag_(0) {}

        /**
         *  @brief Constructeur avec taille et offsets.
         *  @param N Dimension de la matrice (N x N).
         *  @param offsets Décalages des diagonales par rapport à la diagonale principale.
         *                 (0 pour la diagonale principale, positif pour les diagonales supérieures, négatif pour les diagonales inférieures).
         *  @throws std::invalid_argument si des doublons sont trouvés dans les offsets.
        */
        SparseMatrixDIA(size_t N, std::vector<int> offsets);
        
        /**
        *  @brief Ajoute une valeur à la matrice.
        *  @param i Index de la ligne.
        *  @param offset Décalage par rapport à la diagonale centrale.
        */
        double getCoefficient(size_t i, int offset) const;

        /**
        *  @brief Ajoute une valeur à la matrice.
        *  @param i Index de la ligne.
        *  @param offset Décalage de la diagonale (0 pour la diagonale principale, positif pour les diagonales supérieures, négatif pour les diagonales inférieures).
        *  @param value Valeur à ajouter.
        */
        void addCoefficient(size_t i, int offset, double value);

        /**
         *  @brief Retourne la taille de la matrice.
         *  @return Taille de la matrice (N x N).
        */
        size_t getSize() const;

        /**
         *  @brief Affiche la matrice DIA (pour le débogage).
        */
        void print() const;

        /**
         * @brief Récupérer le vecteur offsets.
         * @return Vecteur offsets.
        */
        std::vector<int> getOffsets() const;

    private:
        /** @brief Dimension de la matrice (N x N). */
        size_t N_;

        /** @brief Nombre de diagonales de la matrice. */
        size_t N_diag_;
        
        /** @brief Données de la matrice au format DIA.
         *  @note Chaque colonne correspond à une diagonale. */
        std::vector<std::vector<double>> data_;

        /** @brief Décalages des diagonales par rapport à la diagonale principale. */
        std::vector<int> offsets_;

        /** @brief Map pour retrouver l'index d'une diagonale à partir de son décalage. */
        std::unordered_map<int, size_t> offset2Index;
    };

}

#endif // FVM_LINEAR_SOLVER_SPARSEMATRIXDIA_H