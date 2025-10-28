/*
 * Mesh2D.cpp
 *
*/

/* Inclusion du fichier d'en tête  */
#include "FVM/Core/Mesh2D.h"

/*    Inclusion des bibliothèques   */
#include <fstream>
#include <cassert>

/*    Autres fichiers d'en-tête     */
#include "FVM/Core/Utils.h"


FVM::VertexList FVM::Mesh2D::getVertexList() const
{
	return vertexList_;
	
}


void FVM::Mesh2D::show() const
{

	for (auto& vertex: vertexList_)
	{
		std::cout << vertex << std::endl;
	}
}


double FVM::Mesh2D::getdeltax_w(size_t const& index) const
{
	if (index - (index / (Nx_ + 1)) * (Nx_ + 1) == 0)
	{
		return 0.0; // Bord gauche du domaine.
	}
	return vertexList_[index].getX() - vertexList_[index - 1].getX();
}


double FVM::Mesh2D::getdeltay_n(size_t const& index) const
{
	if (index >= (Nx_ + 1) * Ny_)
	{
		return 0.0; // Bord haut du domaine.
	}
	return vertexList_[index + (Nx_ + 1)].getY() - vertexList_[index].getY();
}


double FVM::Mesh2D::getdeltax_e(size_t const& index) const
{
	if (index - (index / (Nx_ + 1)) * (Nx_ + 1) - Nx_ == 0)
	{
		return 0.0; // Bord droit du domaine.
	}
	return vertexList_[index + 1].getX() - vertexList_[index].getX();
}


double FVM::Mesh2D::getdeltay_s(size_t const& index) const
{
	if (index < (Nx_ + 1))
	{
		return 0.0; // Bord bas du domaine.
	}
	return vertexList_[index].getY() - vertexList_[index - (Nx_ + 1)].getY();
}


double FVM::Mesh2D::getDeltax(size_t const& index) const
{
	if (this->getNx()==0) // Cas 1D.
		return 1.0 ;
	else 
		return (getdeltax_w(index) + getdeltax_e(index)) / 2;
}


double FVM::Mesh2D::getDeltay(size_t const& index) const
{
	if (this->getNy()==0) // Cas 1D.
		return 1.0;
	else 
		return (getdeltay_n(index) + getdeltay_s(index)) / 2;
}


size_t FVM::Mesh2D::getNx() const
{
	return Nx_;
}


size_t FVM::Mesh2D::getNy() const
{
	return Ny_;
}


void FVM::Mesh2D::save_vtk(std::string const& name, std::string const& path) const
{
	std::ofstream file;
	if (!path.empty())
	{
		file.open(path+name + ".vtk");
	}
	else
	{ 
		file.open(name + ".vtk");
	}
	
	if (!file.is_open())
	{
		std::cerr << "Impossible d'ecrire dans le fichier de sortie." << std::endl; 
	}
	else
	{
		// header du fichier .vtk : 
		file << "# vtk DataFile Version 2.0 \n";
		file << "Maillage centre - face avec donnees de cellules \n";
		file << "ASCII \n";
		file << "DATASET STRUCTURED_GRID \n";
		file << "DIMENSIONS " << Nx_ + 1 << " " << Ny_ + 1 << " " << 1 << std::endl;
		file << "POINTS " << vertexList_.size() << " double" << std::endl;
		for (auto& vertex : vertexList_)
		{
			file << vertex;
		}
		file.close();
	}
	std::cout << "Le fichier a correctement ete enregistre." << std::endl;
}


void FVM::Mesh2D::addBoundaryPatch(const std::string& name, const std::vector<size_t>& verticesIDList){
	boundaryPatches_.insert({name, verticesIDList});
}


void FVM::Mesh2D::showBoundaryPatches(){
	for (const auto& [patchName, verticesIDList] : boundaryPatches_) {
        
        std::cout << "--- Patch : " << patchName << " ---" << std::endl;
        
        std::cout << "Points : { ";
        for (size_t point : verticesIDList) {
            std::cout << point << " ";
        }
        std::cout << "}" << std::endl;
    }
    std::cout << "------------------------------------" << std::endl;
}


std::map<std::string,std::vector<size_t>> FVM::Mesh2D::getBoundaryPatches() const
{
	return boundaryPatches_;
}


std::vector<size_t> FVM::Mesh2D::getBoundaryPatchesNodes(const std::string& patchName) const 
{
	if (boundaryPatches_.count(patchName) == 0)
		throw std::runtime_error("Erreur, il n'existe pas de patch nommé : "+patchName);
	else 
		return boundaryPatches_.at(patchName);
}

size_t FVM::Mesh2D::getWestFaceId(size_t nodeId) const
{
	const auto [i, j] = toMatrixIndices(Nx_,Ny_,nodeId);
	assert(j != 0);
	return toLinearIndex(Nx_,Ny_+1, i,j-1);
}

size_t FVM::Mesh2D::getEastFaceId(size_t nodeId) const
{
	const auto [i, j] = toMatrixIndices(Nx_,Ny_,nodeId);
	assert(j != Nx_);
	return toLinearIndex(Nx_,Ny_+1, i,j);
}

size_t FVM::Mesh2D::getNorthFaceId(size_t nodeId) const
{
	const auto [i, j] = toMatrixIndices(Nx_,Ny_,nodeId);
	assert(i != Ny_);
	return Nx_*(Ny_+1)+toLinearIndex(Nx_+1,Ny_, i,j);
}

size_t FVM::Mesh2D::getSouthFaceId(size_t nodeId) const
{
	const auto [i, j] = toMatrixIndices(Nx_,Ny_,nodeId);
	assert(i != 0);
	return Nx_*(Ny_+1)+toLinearIndex(Nx_+1,Ny_, i-1,j);
}

FVM::Vertex2D FVM::Mesh2D::getNode(size_t nodeId) const
{
	return vertexList_[nodeId];
}