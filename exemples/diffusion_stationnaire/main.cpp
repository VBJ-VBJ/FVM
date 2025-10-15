
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
#include "FVM/I_O/MeshFactory.h"
#include "FVM/Core/Mesh2D.h"
#include "FVM/Core/Utils.h"
#include <iostream>


int main()
{
    // FVM::Mesh2D mesh = FVM::uniformMeshing(2,2,1,1);
    // FVM::SparseMatrixDIA A(9,{-1,0,1});
    // FVM::Vectorb b(9);
    // for (int i = 0; i < 9;++i)
    // {
    //     A.addCoefficient(i,0,4);
    // }
    // // A.addCoefficient(2,0,4);
    // b.addValue(2,2);
    // FVM::scalarField x(mesh);

    // FVM::GaussSeidelSolver solver;
    // solver.solve(A,b,x);

    

}
    