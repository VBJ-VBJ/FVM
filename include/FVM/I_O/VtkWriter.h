/*
 * VtkWriter.h
 *
 *     Créé le : 20 octobre 2025
 *      Auteur : VBJ
 * Description : Classe responsable de l'écriture du maillage ainsi que des champs dans un fichier au format .vtk.
*/

#ifndef INCLUDE_FVM_I_O_VTKWRITER_H
#define INCLUDE_FVM_I_O_VTKWRITER_H

/*    Inclusion des bibliothèques   */
#include <memory>
#include <unordered_map>

/* Inclusion des fichiers d'en-tête */



namespace FVM{

    template <typename T>
    class CellField;

    using ScalarCellField = CellField<double>; 

    class Mesh2D;

    class VtkWriter {
    public:
        
        VtkWriter(std::shared_ptr<const Mesh2D> mesh) : mesh_(mesh) {}

        /**
        * @brief Ajoute un champ aux mailles pour l'écriture.
        * @param field Le pointeur partagé vers les données.
        * @param fieldName Le nom du champ tel qu'il doit apparaître dans le fichier VTK.
        */
        void addScalarField(const std::string& fieldName , std::shared_ptr<const ScalarCellField> field);

        bool write(std::string const& name, std::string const& path = "") const; 

    private:
        std::unordered_map<std::string, std::shared_ptr<const ScalarCellField>> ScalarfieldList_;
        std::shared_ptr<const Mesh2D> mesh_;


    };



}











#endif // INCLUDE_FVM_I_O_VTKWRITER_H