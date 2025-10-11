
/*
 * main.cpp (diffusion stationnaire)
 *
 *     Créé le : 11 octobre 2025
 *      Auteur : VBJ
 * Description : Cas test pour le calcul de la diffusion stationnaire.
*/

#include "FVM/LinearSolver/Vectorb.h"
#include "FVM/LinearSolver/SparseMatrixDIA.h"
#include "FVM/LinearSolver/GaussSeidelSolver.h"
#include "FVM/Core/Field.h"
#include <iostream>


int main()
{
    FVM::SparseMatrixDIA A(8,{-1,0,5});
    FVM::Vectorb b(A.getSize());
    FVM::Field<double> x(A.getSize(),1.0);
    

    for (int i = 0;i<8;++i)
    {
        A.addCoefficient(i,0,2);

    }
    A.addCoefficient(1,5,5);
    A.addCoefficient(1,5,3);
    b.addValue(6, 2.0);
    std::cout << "ok" << std::endl ; 
    A.print();
    x.print();
    FVM::GaussSeidelSolver solver;
    solver.solve(A,b,x);

    std::cout << "-----" << std::endl ;
    FVM::Field<double> res = A*x-b;
    res.print();


}
    