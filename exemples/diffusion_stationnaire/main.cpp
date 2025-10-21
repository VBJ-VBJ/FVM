
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
#include "FVM/BoundaryConditions/SpatialDirichletCondition.h"

// nombre aléatoires
#include <random>
#include <ctime> // Pour l'initialisation basée sur le temps


int main()
{
    // Taille du maillage.
    size_t Nx{5};
    size_t Ny{5};

    // Géométrie du milieu.
    double L{1.0};
    double H{1.0};

    // Génération du maillage.
    FVM::Mesh2D mesh = FVM::uniformMeshing(Nx,Ny,L,H);
    //FVM::Mesh2D mesh = FVM::cosMeshing(Nx,Ny,L,H);
    
    // Ajout des patch.
    mesh.addBoundaryPatch("BC",FVM::getBoundaryNodes(mesh));

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
    T.setBoundaryCondition("BC",std::make_shared<FVM::SpatialDirichletCondition>([L](double x, double y) {
            return std::cos(2*FVM::pi/L*x)*std::sin(2*FVM::pi/L*y);
        }));

    FVM::ScalarCellField test(mesh);
    FVM::PoissonEquation(T,test).assemble(A,b,T);

    FVM::GaussLaplacianScheme(-1.0,mesh).apply(A,b,T);

    FVM::GaussSeidelSolver().solve(A,b,T);

    FVM::VtkWriter vtkWriter(std::make_shared<FVM::Mesh2D>(mesh));
    vtkWriter.addScalarField("Temp",std::make_shared<FVM::ScalarPhysicalCellField>(T));
    
    vtkWriter.write("testtt");
}
    