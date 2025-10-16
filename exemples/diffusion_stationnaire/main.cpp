
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
    // FVM::Mesh2D mesh = FVM::uniformMeshing(10,10,1,2);
    // FVM::ScalarField T(mesh);
    //mesh.save_vtk("test2");
    // FVM::SparseMatrixDIA A(9,{-1,0,1});
    // FVM::Vectorb b(9);
    // for (int i = 0; i < 9;++i)
    // {
    //     A.addCoefficient(i,0,4);
    // }
    // // A.addCoefficient(2,0,4);
    // b.addValue(2,2);
    // FVM::ScalarField x(mesh);

    // FVM::GaussSeidelSolver solver;
    // solver.solve(A,b,x);


    FVM::Mesh2D mesh = FVM::uniformMeshing(4,4,1,2);
    mesh.addBoundaryPatch("bot",{0,1,2,3,4});
    mesh.addBoundaryPatch("top",{20,21,22,23,24});
    mesh.showBoundaryPatches();
    FVM::ScalarField T(mesh);
    FVM::SparseMatrixDIA A(T);
    A.print();


}
    