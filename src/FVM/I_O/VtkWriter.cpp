/*
 * VtkWriter.cpp
 *
*/

/* Inclusion du fichier d'en tête  */
#include "FVM/I_O/VtkWriter.h"

/*    Inclusion des bibliothèques   */
#include <fstream>
#include <iostream>

/*    Autres fichiers d'en-tête     */
#include "FVM/Core/Mesh2D.h"
#include "FVM/Core/CellField.h"


namespace FVM{

    void VtkWriter::addScalarField(const std::string& fieldName , std::shared_ptr<const ScalarCellField> field) {
                ScalarfieldList_[fieldName] = field; 
            }

    bool VtkWriter::write(std::string const& name, std::string const& path) const
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
            return false; 
        }
        else
        {
            // header du fichier .vtk : 
            file << "# vtk DataFile Version 2.0 \n";
            file << "Maillage centre - face avec donnees de cellules \n";
            file << "ASCII \n";
            file << "DATASET STRUCTURED_GRID \n";
            file << "DIMENSIONS " << mesh_->getNx() + 1 << " " << mesh_->getNy() + 1 << " " << 1 << std::endl;
            file << "POINTS " << (mesh_->getNx() + 1)*(mesh_->getNy() + 1) << " double" << std::endl;
            for (auto& vertex : mesh_->getVertexList())
            {
                file << vertex;
            }
            if (!ScalarfieldList_.empty())
            {
                file << "POINT_DATA " << (mesh_->getNx() + 1)*(mesh_->getNy() + 1) << std::endl;
                for (auto const& [scalarFieldName,scalarField] : ScalarfieldList_)
                {
                    file << "SCALARS " << scalarFieldName << " double" << std::endl ; 
                    file << "LOOKUP_TABLE default" << std::endl ; 
                    for (size_t i = 0 ; i < scalarField->getSize() ; ++i)
                    {
                        file << scalarField->getField(i) << std::endl;
                    }
                }
            }
            file.close();
        }
        std::cout << "Le fichier a correctement ete enregistre." << std::endl;
        return true;
    }       

}