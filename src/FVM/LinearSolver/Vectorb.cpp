/*
 * Vectorb.cpp
 *
*/

/* Inclusion du fichier d'en tête  */
#include "FVM/LinearSolver/Vectorb.h"

/*    Inclusion des bibliothèques   */
#include <iostream>
#include <cassert>
#include <cmath> // Pour std::sqrt.

/*    Autres fichiers d'en-tête     */


void FVM::Vectorb::addValue(size_t i, double value) {
    if (i >= data_.size()) {
        std::cerr << "Index hors des limites du vecteur." << std::endl;
        return;
    }
    data_[i] += value;
}

void FVM::Vectorb::setValue(size_t i, double value) {
    if (i >= data_.size()) {
        std::cerr << "Index hors des limites du vecteur." << std::endl;
        return;
    }
    data_[i] = value;
}


double FVM::Vectorb::getCoefficient(size_t i) const
{
    if (i >= this->getSize())
    {
        std::cerr << "Dépassement d'indice." << std::endl;
        return -1;
    }
    return data_[i];
}


size_t FVM::Vectorb::getSize() const
{
    return data_.size();
}


void FVM::Vectorb::print() const {
    for (const auto& val : data_) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
}


double FVM::Vectorb::getNormL2() const
        {
            double sum = 0.0;
            for (const auto& val : data_) {
                sum += val * val;
            }
            return std::sqrt(sum);
        }