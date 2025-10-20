
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
#include "FVM/Discretization/Schemes/GaussLaplacianScheme.h"
#include "FVM/I_O/VtkWriter.h"
#include <iostream>
#include <memory>
#include "FVM/Core/Constants.h"
#include "FVM/Discretization/SourceTerm/FunctionSource.h"

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

    size_t Nx{5};
    size_t Ny{5};
    double L{2.0};
    double H{2.0};

    // Génération du maillage.
    //FVM::Mesh2D mesh = FVM::uniformMeshing(Nx,Ny,L,H);
    FVM::Mesh2D mesh = FVM::cosMeshing(Nx,Ny,L,H);
    
    // Ajout des patch.
    std::vector<size_t> patchNodeListLeft,patchNodeListRight,patchNodeListUp,patchNodeListDown;
    for (int i = 0 ; i < Ny+1 ; ++i) // gauche 
    {
        
        int j = 0; 
        patchNodeListLeft.push_back(toLinearIndex(mesh,i,j));  
    }

    for (int i = 0 ; i < Ny+1 ; ++i) // droite
    {
        int j = Nx; 
        patchNodeListRight.push_back(toLinearIndex(mesh,i,j));  
    }

    for (int j = 1 ; j < Nx ; ++j) // haut
    {
        int i = Nx; 
        patchNodeListUp.push_back(toLinearIndex(mesh,i,j));  
    }

    for (int j = 1 ; j < Nx ; ++j) // bas
    {
        int i = 0; 
        patchNodeListDown.push_back(toLinearIndex(mesh,i,j));  
    }

    mesh.addBoundaryPatch("Left",patchNodeListLeft);
    mesh.addBoundaryPatch("Right",patchNodeListRight);
    mesh.addBoundaryPatch("Up",patchNodeListUp);
    mesh.addBoundaryPatch("Down",patchNodeListDown);

    // Affichage des patchs.
    mesh.showBoundaryPatches();

    // Création d'un champ attaché au maillage.
    FVM::ScalarPhysicalCellField T(mesh);

    // Création du système linéaire Ax = b.
    FVM::Vectorb b(T.getSize());
    FVM::SparseMatrixDIA A(T);

    // Création du therme source.
    FVM::FunctionSource([L](double x, double y) {
            return -2*(2*FVM::pi/L)*(2*FVM::pi/L)*std::cos(2*FVM::pi/L*x)*std::sin(2*FVM::pi/L*y);
        }).apply(A,b,T);
    

    // Ajout d'une CL.
    T.setBoundaryCondition("Right",std::make_shared<FVM::DirichletCondition>(0.1));
    T.setBoundaryCondition("Left",std::make_shared<FVM::DirichletCondition>(0.1));
    T.setBoundaryCondition("Up",std::make_shared<FVM::DirichletCondition>(0.1));
    T.setBoundaryCondition("Down",std::make_shared<FVM::DirichletCondition>(0.1));


    FVM::ScalarCellField test(mesh);
    FVM::PoissonEquation(T,test).assemble(A,b,T);
    
    // Affichage de A
    //A.print();
    std::cout << "====" << std::endl; 

    // Construction de l'équation de Poisson.
    // Affichage de A et b après construction.
    //A.print();
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
    FVM::GaussLaplacianScheme(-1.0,mesh).apply(A,b,T);
    //A.print();
    FVM::GaussSeidelSolver().solve(A,b,T);
    std::cout << "====" << std::endl; 
    //T.print();

    FVM::VtkWriter vtkWriter(std::make_shared<FVM::Mesh2D>(mesh));
    vtkWriter.addScalarField("Temp",std::make_shared<FVM::ScalarPhysicalCellField>(T));
    
    vtkWriter.write("testtt");
}
    