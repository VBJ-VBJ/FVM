/*
 * CDSScheme.cpp
 *
*/

/* Inclusion du fichier d'en tête  */
#include "FVM/Interpolation/CDSScheme.h"

/*    Inclusion des bibliothèques   */


/*    Autres fichiers d'en-tête     */
#include "FVM/Core/SurfaceField.h"
#include "FVM/Core/Utils.h"
#include "FVM/Core/CellField.h"

namespace FVM{

    ScalarSurfaceField CDSScheme::interpolate(const ScalarCellField& cellField) const 
    {
        ScalarSurfaceField surfaceField(this->mesh_);
        size_t surfaceId{0};

        // Faces verticales.
        for (size_t i = 0 ; i < mesh_.getNy()+1 ; ++i)
        {
            for (size_t j = 0 ; j < mesh_.getNx() ; ++j)
            {
                size_t nodeId = toLinearIndex(mesh_,i,j);
                surfaceField.setField(surfaceId,0.5*(cellField.getField(nodeId)+cellField.getField(nodeId+1))) ; // Car les faces sont centrées entre les noeuds.
                ++surfaceId;              
            }
        }

        // Faces horizontales.
        for (size_t i = 0 ; i < mesh_.getNy() ; ++i)
        {
            for (size_t j = 0 ; j < mesh_.getNx()+1 ; ++j)
            {
                size_t nodeId = toLinearIndex(mesh_,i,j);
                surfaceField.setField(surfaceId,0.5*(cellField.getField(nodeId)+cellField.getField(nodeId+mesh_.getNx()+1))) ; // Car les faces sont centrées entre les noeuds.
                ++surfaceId;            
            }
        }

        return surfaceField;
    }

}



