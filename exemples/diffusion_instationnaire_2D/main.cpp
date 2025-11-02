
/*
 * main.cpp (diffusion instationnaire)
 *
 *     Créé le : 1 novembre 2025
 *      Auteur : VBJ
 * Description : Cas test pour le calcul de la diffusion instationnaire 2D.
*/

#include "FVM/LinearSolver/Vectorb.h"
#include "FVM/LinearSolver/SparseMatrixDIA.h"
#include "FVM/LinearSolver/GaussSeidelSolver.h"
#include "FVM/Core/PhysicalCellField.h"
#include "FVM/Core/CellField.h"
#include "FVM/I_O/MeshFactory.h"
#include "FVM/Core/Mesh2D.h"
#include "FVM/Core/Utils.h"
#include "FVM/Equations/DiffusionEquation.h"
#include "FVM/Interpolation/CDSScheme.h"
#include "FVM/Core/SurfaceField.h"
#include "FVM/Discretization/Schemes/GaussLaplacianScheme.h"
#include "FVM/I_O/VtkWriter.h"
#include <iostream>
#include <memory>
#include "FVM/Core/Constants.h"
#include "FVM/Discretization/SourceTerm/FunctionSource.h"
#include "FVM/BoundaryConditions/DirichletCondition.h"
#include "FVM/BoundaryConditions/NeumannCondition.h"
#include "FVM/Discretization/TimeScheme/EulerImplicitTimeScheme.h"

int main()
{
    // Taille du maillage.
    size_t Nx{50};
    size_t Ny{50};

    // Géométrie du milieu.
    double L{1.0};
    double H{1.0}; 

    // Temps de simulation.
    double Tsim{0.005}; 

    // Pas detemps.
    double dt{0.0001};

    // Nom du fichier.
    std::string fileName{"diffusion_point"};

    // Génération du maillage.
    FVM::Mesh2D mesh = FVM::uniformMeshing(Nx,Ny,L,H);
    
    // Ajout des patch.
    mesh.addBoundaryPatch("coin",{0});
    mesh.addBoundaryPatch("haut",FVM::getTopNodes(mesh));
    mesh.addBoundaryPatch("bas",FVM::getBotNodes(mesh));
    mesh.addBoundaryPatch("droite",FVM::getRightNodes(mesh));
    mesh.addBoundaryPatch("gauche",FVM::getLeftNodes(mesh));

    // Affichage des patchs.
    mesh.showBoundaryPatches();

    // Création d'un champ attaché au maillage.
    FVM::ScalarPhysicalCellField T(mesh);

    // Création du système linéaire Ax = b.
    FVM::Vectorb b(T.getSize());
    FVM::SparseMatrixDIA A(T);
    
    // Définition des conditions limites.
    T.setBoundaryCondition("haut",std::make_shared<FVM::NeumannCondition>(0,-1));
    T.setBoundaryCondition("bas",std::make_shared<FVM::NeumannCondition>(0,-1));
    T.setBoundaryCondition("gauche",std::make_shared<FVM::NeumannCondition>(0,-1));
    T.setBoundaryCondition("droite",std::make_shared<FVM::DirichletCondition>(1));
    //T.setBoundaryCondition("all",std::make_shared<FVM::NeumannCondition>(0,-1));
    //T.setBoundaryCondition("coin",std::make_shared<FVM::DirichletCondition>(0));

    // Champ initial.
    //T.setField( static_cast<int>((Nx+1)*(Ny+1)/2),1);

    // Application des conditions limites.
    FVM::applyBoundaryConditions(A,b,T);

    // Instanciation du writer .vtk.
    FVM::VtkWriter vtkWriter(std::make_shared<FVM::Mesh2D>(mesh)); 
    vtkWriter.addScalarField("Température",std::make_shared<FVM::ScalarPhysicalCellField>(T));
    vtkWriter.write(fileName+"_0");

    // Enregistrement de l'état initial.

    auto Tnext = T;
    size_t cp{1};
    // Boucle temporelle
    for (double time = 0.0 ; time < Tsim ; time += dt)
    {
        A.setAllZero();
        b.setAllZero();

        // Discrétisation du laplacien.
        FVM::GaussLaplacianScheme(-1.0,mesh).apply(A,b,Tnext);

        // Application du schéma temporel (EulerImplicite).
        FVM::EulerImplicitTimeScheme(FVM::ScalarCellField(mesh,1.0),FVM::ScalarCellField(mesh,1.0)).executeTimeStep(A,b,T,dt);

        // Application des conditions limites.
        FVM::applyBoundaryConditions(A,b,Tnext);

        // Résolution avec la méthode de Gauss-Seidel.
        FVM::GaussSeidelSolver(1000,1e-6,1).solve(A,b,Tnext);
        vtkWriter.addScalarField("Température",std::make_shared<FVM::ScalarPhysicalCellField>(T));
        vtkWriter.write(fileName+"_"+std::to_string(cp));
        ++cp;
        T = Tnext;

    }

}
    