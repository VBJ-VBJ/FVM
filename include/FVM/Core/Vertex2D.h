/*
 * Vertex2D.h
 *
 *     Créé le : 12 octobre 2025
 *      Auteur : VBJ
 * Description : Classe représentant un sommet dans un espace 2D.
*/

#ifndef FVM_CORE_VERTEX2D_H 
#define FVM_CORE_VERTEX2D_H

/*    Inclusion des bibliothèques   */
#include <vector>
#include <iostream> 

/* Inclusion des fichiers d'en-tête */


namespace FVM {

	/**
	 * @class Vertex2D
	 * @brief Représente un point ou un vecteur en 2D et supporte les opérations vectorielles.
	 */
	class Vertex2D {
	public:
		/**
		 * @brief Constructeur par défaut (0,0).
		 */
		Vertex2D() = default; 

		/**
		 * @brief Constructeur avec coordonnées (x,y) du sommet.
		 * @param x Coordonnée x.
		 * @param y Coordonnée y.
		 */
		Vertex2D(double x, double y) : x_(x), y_(y) {}

		/**
		 * @return Coordonnée x.
		 */
		double getX() const { return x_; }

		/**
		 * @return Coordonnée y.
		 */
		double getY() const { return y_; }

		/**
		 * @brief Modifie la coordonnée x.
		 * @param x Nouvelle coordonnée x.
		 */
		void setX(double x) { x_ = x; }

		/**
		 * @brief Modifie la coordonnée y.
		 * @param y Nouvelle coordonnée y.
		 */
		void setY(double y) { y_ = y; }

	private:
		double x_ = 0.0;
		double y_ = 0.0;
	};

	/**
	 * @alias VertexList
	 * @brief Représente une liste de sommets 2D.
	 */
	using VertexList = std::vector<Vertex2D>;

	std::ostream& operator<<(std::ostream& os, FVM::Vertex2D const& vertex);
	std::ofstream& operator<<(std::ofstream& os, FVM::Vertex2D const& vertex);
} 

#endif // FVM_CORE_VERTEX2D_H