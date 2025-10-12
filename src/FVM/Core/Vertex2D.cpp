/*
 * Vertex2D.cpp
 *
*/

/* Inclusion du fichier d'en tête  */
#include "FVM/Core/Vertex2D.h"

/*    Inclusion des bibliothèques   */
#include <fstream>

/*    Autres fichiers d'en-tête     */


namespace FVM {

    std::ostream& operator<<(std::ostream& os, Vertex2D const& vertex)
    {
        os << "(" << vertex.getX() << "," << vertex.getY() << "," << 0 << ")";
        return os;  
    }


    std::ofstream& operator<<(std::ofstream& os, Vertex2D const& vertex)
    {
        os << vertex.getX() << " " << vertex.getY() << " " << 0 << "\n";
        return os;
    }

} 