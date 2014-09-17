/**
@title imagen.h
@class imagen
@brief Clase para la gestión de imagenes .bmp
@author Borja Molina Zea. borja.mz8@gmail.com
@date 10/05/2009
*/

#ifndef _imagen
#define _imagen

#include"graficos.h"
#include<fstream>
#include<iostream>
using namespace graficos;
using namespace std;

class imagen{

	private:
		GRF_Imagen img;
		
	public:
		/**
		@brief Constructor si parametros. Crea una imagen "vacia"
		*/
		imagen();
		
		/**
		@brief Constructor con parámetros. Crea una imagen de un tamaño determinado por el usuario.
		@param alto. El alto de la imagen en pixeles.
		@param ancho. El ancho de la imagen en pixeles
		*/		
		imagen(int alto, int ancho);
		
		/**
		@brief Constructor con parametros. Crea una imagen a partir de otra ya existente leyendo la ruta donde se encuentra.
		@param ruta. Lugar del disco donde se encuentra la imagen a leer
		*/
		imagen(const char* ruta);
		
		/**
		@brief Constructor de copias de la clase
		*/
		imagen(const imagen& otra);
		
		/**
		@brief Destructor de la clase.
		*/
		~imagen();
		
		/**
		@brief Sobrecarga del operador de asignacion =
		*/
		imagen& operator=(const imagen& otra);
		
		/**
		@brief Devuelve el alto de la imagen en pixeles
		*/
		int alto() const;
		
		/**
		@brief Devuelve el ancho de la imagen en pixeles
		*/
		int ancho() const;
		
		/**
		@brief Lee una imagen desde una ruta especificada y la carga en la imagen implicita.
		@param ruta. Puntero a la cadena con el nombre de la ruta.
		*/
		void leer(const char* ruta);
		
		/**
		@brief Dibuja la imagen en pantalla en un punto (x,y).
		@param x. Coordenada en el eje de abcisas de la esquina superior izqda.
		@param y. Coordenada en el eje de ordenadas de la esquina superior izqda.
		*/
		void dibujar(int x, int y) const;
		
		/**
		@brief Limpia una imagen, dejando todo el espacio que ocupa en la pantalla en negro.
		*/
   		void limpiar();
};

/**
@brief Sobrecarga del operador <<. Nos permite leer fotos desde la consola o desde un fichero leyendo la ruta de la misma. La lectura uncluye la creación.
*/
istream& operator>>(istream& in, imagen& img);

#endif
