/*
 * Mesh2D.h
 *
 *     Créé le : 12 octobre 2025
 *      Auteur : VBJ
 * Description : Classe représentant un maillage 2D quadratique ordonné.
*/

#ifndef INCLUDE_FVM_CORE_MESH2D_H
#define INCLUDE_FVM_CORE_MESH2D_H

/*    Inclusion des bibliothèques   */
#include <map>

/* Inclusion des fichiers d'en-tête */
#include "Vertex2D.h"


namespace FVM {

	/** 
	* @class Maillage2D
	* @brief Represente un maillage 2D non-uniforme type "vertex centered".
	*/
	class Mesh2D {
	public:
		/**
		 * @brief Constructeur par défaut.
		 */
		Mesh2D() = default;

		/**
		 * @brief Constructeur par défaut.
		 */
		Mesh2D(size_t Nx,size_t Ny,VertexList VertexList) : Nx_(Nx),Ny_(Ny),vertexList_(VertexList) {}

		/**
		 * @brief Sauvegarde le maillage dans un fichier au format VTK (Paraview).
		 * @param name Le nom du fichier de sortie (sans l'extension).
		 * @param path Le chemin du dossier où enregistrer le fichier. Par défaut, le fichier est enregistré dans le répertoire courant.
		 */
		void save_vtk(std::string const& name, std::string const& path = "") const; 

		/**
		 * @brief Renvoie l'intervalle entre le sommet donné par l'index et le sommet dans une direction donnée.
		 * @param index Index du sommet.
		 * @return L'intervalle entre le sommet donné par l'index et le sommet dans une direction donnée.
		 * @note Les directions sont :
		 * - deltax_w : direction ouest (gauche).
		 * - deltax_e : direction est (droite).
		 * - deltay_n : direction nord (haut).
		 * - deltay_s : direction sud (bas).
		 */
		double getdeltax_w(size_t const& index) const; 

		/**
         * @copydoc getdeltax_w(size_t const& index) const
         */
		double getdeltay_n(size_t const& index) const;

		/**
         * @copydoc getdeltax_w(size_t const& index) const
         */
		double getdeltax_e(size_t const& index) const;

		/**
         * @copydoc getdeltax_w(size_t const& index) const
         */
		double getdeltay_s(size_t const& index) const;

		/**
		 * @brief Renvoie la largeur du volume de contrôle associé au sommet donné par l'index.
		 * @param index Index du sommet.
		 * @return La largeur du volume de contrôle.
		 */
		double getDeltax(size_t const& index) const;

		/**
		 * @brief Renvoie la hauteur du volume de contrôle associé au sommet donné par l'index.
		 * @param index Index du sommet.
		 * @return La hauteur du volume de contrôle.
		 */
		double getDeltay(size_t const& index) const;

		/**
		 * @brief Renvoie la liste des sommets du maillage.
		 */
		VertexList getVertexList() const;

		/**
		 * @brief Renvoie le nombre de mailles dans la direction x.
		 */
		size_t getNx() const;

		/**
		 * @brief Renvoie le nombre de mailles dans la direction y.
		 */
		size_t getNy() const;

		/**
		 * @brief Affiche tous les sommets du maillage sur la console (debug).
		 */
		void show() const; 

		/**
		 * @brief Ajoute un patch.
		 * @param name Nom du patch.
		 * @param vertexIDList Liste de l'indice des sommets où s'applique la CL.
		 */
		void addBoundaryPatch(const std::string& name, const std::vector<size_t>& verticesIDList);

		/**
		 * @brief Affiche les patchs (Debug).
		 */
		void showBoundaryPatches();

		/**
		 * @return Les patchs pour les CL.
		 */
		std::map<std::string,std::vector<size_t>> getBoundaryPatches() const;
		
	private:
		/** @brief Nombre de mailles par lignes. */
		size_t Nx_{ 0 };

		/** @brief Nombre de mailles par colonnes. */
		size_t Ny_{ 0 };

		/** @brief Liste des sommets du maillage. */
		VertexList vertexList_; 

		/** @brief Sélections nommées du maillage. */
		std::map<std::string, std::vector<size_t>> boundaryPatches_;
	};

}

#endif // INCLUDE_FVM_CORE_MESH2D_H