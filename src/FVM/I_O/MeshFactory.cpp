/*
 * MeshFactory.cpp
 *
*/

/* Inclusion du fichier d'en tête  */
#include "FVM/I_O/MeshFactory.h"

/*    Inclusion des bibliothèques   */
#include <cmath> // Pour std::cos.

/*    Autres fichiers d'en-tête     */
#include "FVM/Core/Constants.h"


FVM::Mesh2D FVM::uniformMeshing(size_t Nx, size_t Ny,double L, double H)
{
	FVM::VertexList vertexList((Nx + 1) * (Ny + 1));
	double deltax{ L / Nx };
	double deltay{ H / Ny };
	size_t id{ 0 };
	for (size_t i=0; i <= Ny; ++i)
	{
		for (size_t ii = 0; ii <= Nx; ++ii)
		{
			vertexList[id].setX(double(ii)*deltax);
			vertexList[id].setY(double(i)*deltay);
			++id; 
		}
	}
	return FVM::Mesh2D(Nx, Ny, vertexList);
}


FVM::Mesh2D FVM::cosMeshing(size_t Nx, size_t Ny,double L, double H)
{
    FVM::VertexList vertexList((Nx + 1) * (Ny + 1));
	size_t id{ 0 };
	for (size_t i = 0; i <= Ny; ++i)
	{
		for (size_t ii = 0; ii <= Nx; ++ii)
		{
			vertexList[id].setX(0.5 * L * (1 - std::cos(ii * FVM::pi / Nx)));
			vertexList[id].setY(0.5 * H * (1 - std::cos(i * FVM::pi / Ny)));
			++id;
		}
	}
	return FVM::Mesh2D(Nx, Ny, vertexList);
}

