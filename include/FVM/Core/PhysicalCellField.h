/*
 * PhysicalCellField.h
 *
 *     Créé le : 16 octobre 2025
 *      Auteur : VBJ
 * Description : Classe représentant un champ de valeur physique quelconque (scalaire ou vecteur) aux noeuds (c'est à dire dans le volume de contrôle).
*/

#ifndef INCLUDE_FVM_CORE_PHYSICALCELLFIELD_H
#define INCLUDE_FVM_CORE_PHYSICALCELLFIELD_H

/*    Inclusion des bibliothèques   */
#include <vector>
#include <iostream>
#include <cassert>
#include <cmath>
#include <memory>
#include <map>

/* Inclusion des fichiers d'en-tête */
#include "CellField.h"

namespace FVM{

    template <typename T>
    class PhysicalCellField : public CellField<T>
    {
    public : 

        /**
         * @brief Construction du champ à partir d'un mesh.
         * @note Les conditions limites associées aux patchs définis dans le mesh sont fixées comme Dirichlet de 0 par défaut.
         */
        PhysicalCellField(const Mesh2D& mesh) : CellField<T>(mesh) 
        {
            auto defaultCondition = std::make_shared<DirichletCondition>(0.0);
            for (const auto& it : mesh.getBoundaryPatches())
            {
                boundaryConditions_.emplace(it.first, defaultCondition);
            }
        }


        /**
        * @return Les conditions limites associées au patch.
        */
        std::map<std::string,std::shared_ptr<BoundaryCondition>> getBoundaryConditions() const 
        {
            return boundaryConditions_;
        }


        /** 
         * @brief Définit une condition limite
         * @param patchName Nom du patch.
         * @param BC Condition limite.
         */
       void setBoundaryCondition(const std::string& patchName,std::shared_ptr<BoundaryCondition> newBoundaryCondition)
        {
            if (boundaryConditions_.count(patchName) == 0)
                throw std::runtime_error("Erreur, il n'existe pas de patch nommé : "+patchName);
            else 
                boundaryConditions_[patchName] = newBoundaryCondition;
        }
    
    private : 
        
        /** @brief Condition limites associées au patch. */
        std::map<std::string,std::shared_ptr<BoundaryCondition>> boundaryConditions_;

    };

    using ScalarPhysicalCellField=PhysicalCellField<double>;

}

#endif // INCLUDE_FVM_CORE_PHYSICALCELLFIELD_H