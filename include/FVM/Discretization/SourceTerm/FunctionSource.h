/*
 * FunctionSource.h
 *
 *     Créé le : 20 octobre 2025
 *      Auteur : VBJ
 * Description : Construit le terme source de l'équation.
*/

#ifndef INCLUDE_FVM_DISCRETISATION_SOURCETERM_FUNCTIONSOURCE_H 
#define INCLUDE_FVM_DISCRETISATION_SOURCETERM_FUNCTIONSOURCE_H 

/*    Inclusion des bibliothèques   */
#include <functional>

/* Inclusion des fichiers d'en-tête */
#include "SourceTerm.h"

namespace FVM{

    using SpatialFunction = std::function<double(double,double)>;

    class FunctionSource : public SourceTerm {
    public:

        FunctionSource(SpatialFunction function) : functionSource_(function) {}
        
        virtual void apply(SparseMatrixDIA& A,Vectorb& b,const ScalarCellField& field) const override;
    
    private: 

        /** @brief Fonction source. */
        SpatialFunction functionSource_;

    };

}

#endif // INCLUDE_FVM_DISCRETISATION_SOURCETERM_FUNCTIONSOURCE_H 