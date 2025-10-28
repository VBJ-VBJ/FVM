/*
 * Utils.cpp
 *
*/

/* Inclusion du fichier d'en tête  */
#include "FVM/Core/Utils.h"

/*    Inclusion des bibliothèques   */
#include <cassert>
#include <memory>
#include "FVM/BoundaryConditions/SpatialDirichletCondition.h"

/*    Autres fichiers d'en-tête     */

/**
 * @brief Convertit les index (ligne,colonne) en un index unique k.
 */
size_t FVM::toLinearIndex(const FVM::Mesh2D& mesh, size_t i, size_t j)
{
    if (i > mesh.getNy() || j > mesh.getNx()) {
        throw std::out_of_range("Indices de ligne ou de colonne hors des limites de la matrice.");
    }
    return i * (mesh.getNx() + 1) + j;
}


size_t FVM::toLinearIndex(size_t Nx, size_t Ny, size_t i, size_t j)
{
    if (i > Ny || j > Nx) {
        throw std::out_of_range("Indices de ligne ou de colonne hors des limites de la matrice.");
    }
    return i * Nx + j;
}


std::pair<size_t, size_t> FVM::toMatrixIndices(size_t Nx, size_t Ny, size_t k)
{
    const size_t step = Nx + 1;
    size_t i = k / step;
    size_t j = k % step;
    if (i > Ny) {
        throw std::out_of_range("L'indice linéaire k est hors des limites de la grille (Ny, Nx).");
    }
    return {i, j};
}


std::vector<size_t> FVM::getTopNodes(const Mesh2D& mesh)
{
    std::vector<size_t> nodeList(mesh.getNx()+1);
    for (int j = 0 ; j < mesh.getNx()+1 ; ++j)
    {
        int i = mesh.getNy(); 
        nodeList[j] = toLinearIndex(mesh,i,j); 
    }
    return nodeList;
}


std::vector<size_t> FVM::getBotNodes(const Mesh2D& mesh)
{
    std::vector<size_t> nodeList(mesh.getNx()+1);
    for (int j = 0 ; j < mesh.getNx()+1 ; ++j)
    {
        int i = 0; 
        nodeList[j] = toLinearIndex(mesh,i,j); 
    }
    return nodeList;
}

std::vector<size_t> FVM::getLeftNodes(const Mesh2D& mesh)
{
    std::vector<size_t> nodeList(mesh.getNy()+1);
    for (int i = 0 ; i < mesh.getNy()+1 ; ++i)
    {
        int j = 0; 
        nodeList[i] = toLinearIndex(mesh,i,j); 
    }
    return nodeList;
}

std::vector<size_t> FVM::getRightNodes(const Mesh2D& mesh)
{
    std::vector<size_t> nodeList(mesh.getNy()+1);
    for (int i = 0 ; i < mesh.getNy()+1 ; ++i)
    {
        
        int j = mesh.getNx(); 
        nodeList[i] = toLinearIndex(mesh,i,j); 
    }
    return nodeList;
}


std::vector<size_t> FVM::getBoundaryNodes(const Mesh2D& mesh)
{
    const auto& topNodes  = getTopNodes(mesh);
    const auto& botNodes  = getBotNodes(mesh);
    const auto& leftNodes = getLeftNodes(mesh);
    const auto& rightNodes= getRightNodes(mesh);

    size_t total_size = topNodes.size() + botNodes.size() + leftNodes.size() + rightNodes.size();
    
    std::vector<size_t> boundaryNodes; 
    boundaryNodes.reserve(total_size); 

    boundaryNodes.insert(boundaryNodes.end(), topNodes.begin(), topNodes.end());
    boundaryNodes.insert(boundaryNodes.end(), botNodes.begin(), botNodes.end());
    boundaryNodes.insert(boundaryNodes.end(), leftNodes.begin(), leftNodes.end());
    boundaryNodes.insert(boundaryNodes.end(), rightNodes.begin(), rightNodes.end());
    
    return boundaryNodes;
}

void FVM::applyBoundaryConditions(SparseMatrixDIA& A, Vectorb& b, const ScalarPhysicalCellField& phi)
{
    for (const auto& pair : phi.getBoundaryConditions())
    {
        if (dynamic_cast<DirichletCondition*>(pair.second.get()) == nullptr || dynamic_cast<SpatialDirichletCondition*>(pair.second.get()) == nullptr)  
        {
            std::cout << "Appli (Passe 1 - non-Dirichlet) Patch " << pair.first << std::endl;
            for (const auto& index : phi.getMesh().getBoundaryPatchesNodes(pair.first) )
            {       
                pair.second->apply(A,b,index,phi);
            }
        }
    }
    
    for (const auto& pair : phi.getBoundaryConditions())
    {
        if (dynamic_cast<DirichletCondition*>(pair.second.get()) != nullptr || dynamic_cast<SpatialDirichletCondition*>(pair.second.get()) != nullptr)
        {
            std::cout << "Appli (Passe 2 - Dirichlet) Patch " << pair.first << std::endl;
            for (const auto& index : phi.getMesh().getBoundaryPatchesNodes(pair.first) )
            {            
                pair.second->apply(A,b,index,phi);
            }
        }
    }
}