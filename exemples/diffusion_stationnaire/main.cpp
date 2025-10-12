
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
#include <iostream>


int main()
{
    FVM::Mesh2D mesh = FVM::uniformMeshing(10, 10, 1.0, 1.0);
    mesh.save_vtk("mesh_uniform");
    mesh.show();

}
    