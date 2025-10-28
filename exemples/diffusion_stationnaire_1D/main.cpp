
/*
 * main.cpp (diffusion stationnaire)
 *
 *     Créé le : 11 octobre 2025
 *      Auteur : VBJ
 * Description : Cas test pour le calcul de la diffusion stationnaire 1D.
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
#include "FVM/BoundaryConditions/SpatialDirichletCondition.h"
#include "FVM/BoundaryConditions/SpatialNeumannCondition.h"

int main()
{
    // Taille du maillage.
    size_t Nx{100};
    size_t Ny{0};

    // Géométrie du milieu.
    double L{1.0};
    double H{0.1}; // Sert uniquement à la génération du maillage, pas pris en compte 
                   // dans le calcul VF.

    // Génération du maillage.
    FVM::Mesh2D mesh = FVM::uniformMeshing(Nx,Ny,L,H);
    
    // Ajout des patch.
    mesh.addBoundaryPatch("left",FVM::getLeftNodes(mesh));
    mesh.addBoundaryPatch("right",FVM::getRightNodes(mesh));

    // Affichage des patchs.
    mesh.showBoundaryPatches();

    // Création d'un champ attaché au maillage.
    FVM::ScalarPhysicalCellField T(mesh);

    // Création du système linéaire Ax = b.
    FVM::Vectorb b(T.getSize());
    FVM::SparseMatrixDIA A(T);
    
    // Ajout des CL associées aux patchs.
    T.setBoundaryCondition("left",std::make_shared<FVM::DirichletCondition>(0.0));
    T.setBoundaryCondition("right",std::make_shared<FVM::DirichletCondition>(1.0));
    
    // Discrétisation du laplacien.
    FVM::GaussLaplacianScheme(-1.0,mesh).apply(A,b,T);

    // Application des conditions limites.
    FVM::applyBoundaryConditions(A,b,T);

    // Affichage de la matrice A ainsi que du vecteur b.
    // A.print();
    // b.print();

    // Résolution avec la méthode de Gauss-Seidel.
    FVM::GaussSeidelSolver(1000,1e-6,1.9).solve(A,b,T);

    // Ajout des champs et du maillage dans un fichier au format .vtk.
    FVM::VtkWriter vtkWriter(std::make_shared<FVM::Mesh2D>(mesh)); // Maillage.
    vtkWriter.addScalarField("Température",std::make_shared<FVM::ScalarPhysicalCellField>(T)); // Champ de température.
    
    // Ecriture dans le fichier au format vtk.
    vtkWriter.write("test_barreau");
}
    