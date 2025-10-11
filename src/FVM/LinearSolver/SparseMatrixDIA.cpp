/*
 * SparseMatrixDIA.cpp
 *
*/

/* Inclusion du fichier d'en tête  */
#include "FVM/LinearSolver/SparseMatrixDIA.h"

/*    Inclusion des bibliothèques   */
#include <cstdlib> // Pour std::abs.

/*    Autres fichiers d'en-tête     */


FVM::SparseMatrixDIA::SparseMatrixDIA(size_t N, std::vector<int> offsets)
{
    N_diag_ = offsets.size();
    N_ = N;
    offsets_ = offsets;
    data_.resize(N_, std::vector<double>(N_diag_, 0.0));
    for (size_t d = 0; d < N_diag_; ++d) {
        offset2Index[offsets_[d]] = d;
    }
    
    if (offset2Index.size() != offsets_.size()) {
        throw std::invalid_argument("Les offsets des diagonales contiennent des doublons.");
    }
}

double FVM::SparseMatrixDIA::getCoefficient(size_t i, int offset) const
{
    auto it = offset2Index.find(offset);
    
    if (it == offset2Index.end()) {
        std::cerr << "Le decalage specifie n'existe pas dans la matrice." << std::endl;
        return 0;
    }

    size_t d = it->second; // Index de la diagonale correspondante.

    assert(d < N_diag_ && i < N_);
    return data_[i][d];
}


void FVM::SparseMatrixDIA::addCoefficient(size_t i, int offset, double value)
{
    auto it = offset2Index.find(offset);
    if (it == offset2Index.end()) {
        std::cerr << "Le decalage specifie n'existe pas dans la matrice." << std::endl;
        return;
    }

    size_t d = it->second; // Index de la diagonale correspondante.
    // if (i > N_ - std::abs(offset)) {
    //     std::cerr << "L'index de la diagonale est hors des limites de la matrice." << std::endl;
    //     return;
    // }
    assert(!(offset > 0 && i >= N_-offset));
    assert(!(offset < 0 && i < -offset));
    assert(!(i > N_ || i < 0));
    data_[i][d] += value;
}


void FVM::SparseMatrixDIA::print() const {
    for (size_t i = 0; i < N_; ++i) {
        for (size_t d = 0; d < N_diag_; ++d) 
        {
            std::cout << data_[i][d] << " ";
        }
        std::cout << "\n";
    }
}


size_t FVM::SparseMatrixDIA::getSize() const {
    return N_;
}


std::vector<int> FVM::SparseMatrixDIA::getOffsets() const {
    return offsets_;
}
