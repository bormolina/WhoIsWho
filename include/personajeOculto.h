/**
@title personajeOculto.h
@class personajeOculto
@brief Clase para la gestión del TDA personaje oculto.
@author Borja Molina Zea. borja.mz8@gmail.com
@date 20/05/2009
*/

#ifndef _personajeOculto
#define _personajeOculto

#include "conjuntoPersonajes.h"
#include "funcionesAuxiliares.h"

class personajeOculto{
	private:
		personaje PJoculto; //Personaje oculto, se elige al azar de un cjto de personajes.
		
		//Variables acerca del posicionamiento en pantalla y tamaño del personaje oculto
		int x,y; 
		int ancho, alto; 
		int colorFondo[3];
		int anchoMarco, altoMarco;
		int colorMarco[3];
		
		char ruta[999]; //Ruta de la imagen para ocultar al personaje
		imagen oculto; //Imagen para ocultar
		bool ocultado; //Indica si el pj es oculto(que pertenece a la maquina) o si es visible(pertenece al jugador humano)

	public:
		/**
		@brief Crea un personaje oculto cogiendo un personaje de forma aleatoria de un conjunto de personajes
		@param fichas. Conjunto de personaje del que se extraerá el personaje oculto
		@modo Indica el modo en el que el personaje sera elegido. Existen dos modos. Los dos aleatorios.
		*/
		personajeOculto(conjuntoPersonajes& fichas, bool modo);
		
		/**
		@brief Constructor de copias de la clase.
		@param otro. Objeto a copiar.
		*/
		personajeOculto(const personajeOculto&  otro);
		
		/**
		@brief Sobrecarga del operador =
		@param otro. Objeto a igualar.
		*/
		personajeOculto& operator= (const personajeOculto& otro);
		
		/**
		@brief Destructor de la clase. No hace falta implementarlo, debido a que todos los tipos de datos de su parte privada o son tipos de datos elementales como int, char... o ya tienen su destructor implementado como la clase imagen de la que se hace uso
		*/
		//~personajeOculto();
		
		/**
		@brief Operador lógico ==. Compara dos personajes. La comparación se hace entre un personaje oculto y otro normal.
		@return true sin los dos personajes son iguales. False en otro caso.
		*/
		bool operator== (personaje& otro);
		
		/**
		@brief Operador lógico !=. Compara dos personajes. La comparación se hace entre un personaje oculto y otro normal.
		@return true si los dos personajes son distintos. False en otro caso.
		*/
		bool operator!= (personaje& otro);
		
		/**
		@brief Obtiene un personaje oculto
		@return El personaje oculto.
		*/
		personaje getPersonaje();
		
		/**
		@brief Establece como oculto el personaje. Es decir hace que el jugador humano no pueda visualizarlo porque al pintarlo se hara con la imagen especial de desconocido.bmp. Este método solo se emplea con el personaje oculto de la máquina, nunca con el del jugador humano.
		*/
		void ocultar();
		
		/**
		@brief Establece la ruta de la imagen para ocultar al personaje
		@param rutaImagen La ruta de la imagen en dico
		*/
		void setRuta(const char* rutaImagen);
		
		/**
		@brief Dibuja en pantalla el personaje oculto
		*/
		void dibujar();
	
		/**
		@brief Sobrecarga del operador de insercción >>
		*/
		friend istream& operator>>(istream& in, personajeOculto& otro);
		
		/**
		@brief Sobrecarga del operador de extración <<
		*/
		friend ostream& operator<<(ostream& out,const personajeOculto& otro);
	private:
		/**
		@brief Copia un personaje oculto en otro
		@param otro Objeto de la clase que se copiara
		*/
		void copiar(const personajeOculto& otro);
};

#endif
