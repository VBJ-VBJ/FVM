
/*
 * main.cpp (diffusion stationnaire)
 *
 *     Créé le : 28 octobre 2025
 *      Auteur : VBJ
 * Description : Cas test pour le calcul de la diffusion stationnaire 2D.
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
    size_t Ny{100};

    // Géométrie du milieu.
    double L{1.0};
    double H{1.0}; 

    // Génération du maillage.
    FVM::Mesh2D mesh = FVM::uniformMeshing(Nx,Ny,L,H);
    
    // Ajout des patch.
    mesh.addBoundaryPatch("gauche",FVM::getLeftNodes(mesh));
    mesh.addBoundaryPatch("droite",FVM::getRightNodes(mesh));
    mesh.addBoundaryPatch("haut",FVM::getTopNodes(mesh));
    mesh.addBoundaryPatch("bas",FVM::getBotNodes(mesh));
    mesh.addBoundaryPatch("coin",{0});
    // mesh.addBoundaryPatch("all",FVM::getBoundaryNodes(mesh));

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
    
    T.setBoundaryCondition("haut",std::make_shared<FVM::SpatialNeumannCondition>
        ([L](double x, double y) 
        {
            return -2*FVM::pi/L*std::cos(2*FVM::pi/L*x)*std::cos(2*FVM::pi/L*y);
        }
        ,-1));

    T.setBoundaryCondition("bas",std::make_shared<FVM::SpatialNeumannCondition>
        ([L](double x, double y) 
        {
            return +2*FVM::pi/L*std::cos(2*FVM::pi/L*x)*std::cos(2*FVM::pi/L*y);
        }
        ,-1));

    T.setBoundaryCondition("gauche",std::make_shared<FVM::SpatialNeumannCondition>
        ([L](double x, double y) 
        {
            return -2*FVM::pi/L*std::sin(2*FVM::pi/L*x)*std::sin(2*FVM::pi/L*y);
        }
        ,-1));

    T.setBoundaryCondition("droite",std::make_shared<FVM::SpatialNeumannCondition>
        ([L](double x, double y) 
        {
            return +2*FVM::pi/L*std::sin(2*FVM::pi/L*x)*std::sin(2*FVM::pi/L*y);
        }
        ,-1));

    T.setBoundaryCondition("coin",std::make_shared<FVM::SpatialDirichletCondition>
        ([L](double x, double y) 
        {
            return std::cos(2*FVM::pi/L*x)*std::sin(2*FVM::pi/L*y);
        }));

    
    // Discrétisation du laplacien.
    FVM::GaussLaplacianScheme(1.0,mesh).apply(A,b,T);

    // Application des conditions limites.
    FVM::applyBoundaryConditions(A,b,T);

    // Affichage de la matrice A ainsi que du vecteur b.
    

    // Résolution avec la méthode de Gauss-Seidel.
    FVM::GaussSeidelSolver(1000,1e-6,1.8).solve(A,b,T);

    // A.print();
    // b.print();

    // Ajout des champs et du maillage dans un fichier au format .vtk.
    FVM::VtkWriter vtkWriter(std::make_shared<FVM::Mesh2D>(mesh)); // Maillage.
    vtkWriter.addScalarField("Température",std::make_shared<FVM::ScalarPhysicalCellField>(T)); // Champ de température.
    
    // Ecriture dans le fichier au format vtk.
    vtkWriter.write("test_plaque");
   

}
    