
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
#include "FVM/Core/PhysicalCellField.h"
#include "FVM/Core/CellField.h"
#include "FVM/I_O/MeshFactory.h"
#include "FVM/Core/Mesh2D.h"
#include "FVM/Core/Utils.h"
#include "FVM/Equations/PoissonEquation.h"
#include "FVM/Interpolation/CDSScheme.h"
#include "FVM/Core/SurfaceField.h"
#include <iostream>
#include <memory>

// nombre aléatoires
#include <random>
#include <ctime> // Pour l'initialisation basée sur le temps


int main()
{
    // FVM::Mesh2D mesh = FVM::uniformMeshing(10,10,1,2);
    // FVM::ScalarPhysicalCellField T(mesh);
    //mesh.save_vtk("test2");
    // FVM::SparseMatrixDIA A(9,{-1,0,1});
    // FVM::Vectorb b(9);
    // for (int i = 0; i < 9;++i)
    // {
    //     A.addCoefficient(i,0,4);
    // }
    // // A.addCoefficient(2,0,4);
    // b.addValue(2,2);
    // FVM::ScalarPhysicalCellField x(mesh);

    // FVM::GaussSeidelSolver solver;
    // solver.solve(A,b,x);



    // Génération du maillage.
    FVM::Mesh2D mesh = FVM::uniformMeshing(3,3,1,2);
    
    // Ajout des patch.
    mesh.addBoundaryPatch("bot",{0,1,2,3,4});
    

    // Affichage des patchs.
    mesh.showBoundaryPatches();

    // Création d'un champ attaché au maillage.
    FVM::ScalarPhysicalCellField T(mesh);

    // Création du système linéaire Ax = b.
    FVM::Vectorb b(T.getSize());
    FVM::SparseMatrixDIA A(T);

    // Création du therme source (vide ici).
    FVM::ScalarCellField Source(mesh);

    // Ajout d'une CL.
    T.setBoundaryCondition("bot",std::make_shared<FVM::DirichletCondition>(5.0));

    
    // Affichage de A
    A.print();
    std::cout << "====" << std::endl; 

    // Construction de l'équation de Poisson.
    FVM::PoissonEquation eq(T,Source);
    eq.assemble(A,b,T);

    // Affichage de A et b après construction.
    A.print();
    b.print();

    std::cout << "====" << std::endl; 

    // std::mt19937 generator(std::time(nullptr));
    // int min_val = 1;
    // int max_val = 100;
    // std::uniform_int_distribution<int> distribution(min_val, max_val);
    
    // FVM::ScalarCellField cellField(mesh);

    // for (size_t i = 0 ; i < cellField.getSize() ; ++i)
    // {
    //     cellField.setField(i,distribution(generator));
    // }
    // cellField.print();


    // FVM::ScalarSurfaceField surfaceField = FVM::CDSScheme(mesh).interpolate(cellField);
    // surfaceField.print();
}
    