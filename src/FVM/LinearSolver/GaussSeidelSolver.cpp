/*
 * SparseMatrixDIA.cpp
 *
*/

/* Inclusion du fichier d'en tête  */
#include "FVM/LinearSolver/GaussSeidelSolver.h"

/*    Inclusion des bibliothèques   */
#include <cstdlib> // Pour std::abs.
#include <iostream>

/*    Autres fichiers d'en-tête     */


void FVM::GaussSeidelSolver::solve(const SparseMatrixDIA &A, const Vectorb &b, ScalarCellField &x) 
{
    if (b.getSize() != x.getSize())
    {
        std::cerr << "La taille du vecteur x n'est pas compatible avec le système." << std::endl;
        return ;
    }

    ScalarCellField x_next = x;
    double sum_next,sum;
    size_t it{0};
    double res{(A*x-b).getNormL2Field()/b.getNormL2()};
    while(it < maxIter_ && res > tol_)
    {
        for (size_t i{0}; i < b.getSize(); ++i)
        {
            sum_next = 0;
            sum = 0; 
            
            for (auto& offset : A.getOffsets())
            {
                if (offset > 0 && i < b.getSize()-offset) 
                    sum += A.getCoefficient(i,offset)*x.getField(static_cast<size_t>(i+offset));
                if (offset < 0 && i >= static_cast<size_t>(-offset))
                    sum_next += A.getCoefficient(i,offset)*x_next.getField(static_cast<size_t>(i+offset));
            }
            x_next.setField(i,1/A.getCoefficient(i,0)*( b.getCoefficient(i)-sum_next - sum));
        }
        x = x_next;
        res = (A*x-b).getNormL2Field()/b.getNormL2();
        std::cout << "res = " << res << std::endl;
        it++; 
    }   
}