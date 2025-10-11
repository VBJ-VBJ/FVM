/*
 * Field.h
 *
 *     Créé le : 11 octobre 2025
 *      Auteur : VBJ
 * Description : Classe représentant un champ de valeur quelconque (scalaire ou vecteur) dans le domaine physique discrétisé par le mesh.
*/

#ifndef INCLUDE_FVM_CORE_FIELD_H
#define INCLUDE_FVM_CORE_FIELD_H

/*    Inclusion des bibliothèques   */
#include <vector>
#include <iostream>
#include <cassert>
#include <cmath>

/* Inclusion des fichiers d'en-tête */
#include "FVM/LinearSolver/Vectorb.h"
#include "FVM/LinearSolver/SparseMatrixDIA.h"

namespace FVM {

    template<typename T>
    class Field {
    public:
        /**
         * @brief Constructeur de base.
         * @param size Nombre d'éléments.
         */
        Field(size_t size) : data_(size) {}

        /**
         * @brief Constructeur avec valeur initiale.
         * @param size Nombre d'éléments.
         * @param initialValue Valeur initiale pour chaque élément.
         */
        Field(size_t size, T initialValue) : data_(size, initialValue) {}

        /** 
         * @brief Ajoute un terme à un index donné du champ.
         * @param index L'index du terme en question.
         * @param value Valeur à ajouter (scalaire, vecteur etc.).
         */
        void addField(size_t i, T value)
        {
            if (i >= data_.size())
            {
                std::cerr << "Index hors des limites du champ." << std::endl;
                return;
            }
            data_[i] += value ; 
        }

        /**
         * @brief Fixe une valeur pour un index donné.
         * @param i Index.
         * @param value Valeur du champ.
         */
        void setField(size_t i,double value) 
        {
            if (i >= this->getSize())
            {
                std::cerr << "Dépassement d'indice, impossible de définir cette valeur." << std::endl;
                return;
            }
            data_[i] = value; 
        }
        
        /**
         * @brief Retourne la valeur du coefficient à un index donné.
         */
        double getField(size_t i) const 
        {
            if (i >= this->getSize())
            {
                std::cerr << "Dépassement d'indice." << std::endl;
                return -1;
            }
            return data_[i];
        }

        /**
         * @brief Retourne la taille du vecteur.
        */
        size_t getSize() const
        {
            return data_.size();
        }

        /** 
        * @brief Calcule la norme L2 du champ.
        * @return La norme L2 du champ.
        */
        double getNormL2Field() const
        {
            double sum = 0.0;
            for (const auto& val : data_) {
                sum += val * val;
            }
            return std::sqrt(sum);
        }

        /** 
        * @brief Affiche le champ (pour le débogage).
        */
       void print() const {
           for (const auto& val : data_) {
               std::cout << val << " ";
           }
           std::cout << std::endl;
       }

    private:
        std::vector<T> data_;
    };

    Field<double> operator-(const Vectorb& vec, const Field<double>& field);

    Field<double> operator-(const Field<double>& field, const Vectorb& vec);

    Field<double> operator*(const SparseMatrixDIA& mat, const Field<double>& field); 

}

#endif // INCLUDE_FVM_CORE_FIELD_H