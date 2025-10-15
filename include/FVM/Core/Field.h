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
#include "Mesh2D.h"

namespace FVM {

    template<typename T>
    class Field {
    public:

        /**
         * @brief Construction du champ à partir d'un mesh.
         */
        Field(const Mesh2D& mesh) : mesh_(mesh), data_((mesh.getNx()+1)*(mesh.getNy()+1)) {}

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

        /** 
         * @brief Retourne l'adresse du mesh associé au champ.
         */
        const Mesh2D& getMesh() const {
            return mesh_;
        }

       T& operator[](size_t i){
            if (i < 0 || static_cast<size_t>(i) >= data_.size()){
                throw std::out_of_range("Index de cellule hors limites.");
            }
            return  data_[i];
        }

        Field& operator=(const Field& other) {
        if (this != &other) {
            if (&mesh_ != &other.mesh_) {
                throw std::runtime_error("Vous ne pouvez pas assigner deux maillages avec deux mesh différents.");
            }
            this->data_ = other.data_; 
        }
        return *this;
    }

    private:
        std::vector<T> data_;
        const Mesh2D& mesh_;
    };

    using scalarField=Field<double>;

    scalarField operator-(const Vectorb& vec, const scalarField& field);

    scalarField operator-(const scalarField& field, const Vectorb& vec);

    scalarField operator*(const SparseMatrixDIA& mat, const scalarField& field); 
}

#endif // INCLUDE_FVM_CORE_FIELD_H