/**
@title conjuntoPreguntas .h
@class tablero
@brief Clase para gestión del tablero de juego del quien es quien.
@author Borja Molina Zea. borja.mz8@gmail.com
@date 25/05/2009
*/

#ifndef _tablero
#define _tablero

#include"conjuntoPersonajes.h"
#include"funcionesAuxiliares.h"
#include"pregunta.h"

//Estructura ficha. Representa una ficha del tablero de juego. Contiene el personaje, si está descartado y su posición  en el tablero
struct Ficha{
	personaje PJ; //Personaje de la ficha
	bool descartado;//Indica si la ficha esta descartada o no
	int x,y;//Posicion de la ficha en el tablero
};

class tablero{
	private:
		//Variables acerca del posicionamiento en pantalla y tamaño del tablero
		int x,y;
		int ancho, alto;
		int colorFondo[3];
		int anchoMarco, altoMarco;
		int colorMarco[3];
		int colorTachar[3];
		int nFilas, nColumnas;
		int separacionAlto, separacionAncho;
		
		int nFichas;//Número total de fichas del tablero
		int sinDescartar;//Indica el número de fichas sin descartar
		bool oculto;//Indica si el tablero oculto o no. Es bandera estará a true si se trate del tablero de la máquina y a false si se trate del tablero del jugador humano.
		char* ruta;//Ruta de la imagen para ocultar las fichas del tablero de la máquina
		Ficha* fichas;//Puntero al conjunto de fichas que forman un tablero
	public:
		/**
		@brief Crea un tablero a partir de un conjunto de personajes.
		@param personajes. Conjunto de personajes a partir del cual se crearan las fichas del tablero.
		@param nF. Número de filas del tablero
		@param nC. Número de columnas del tablero
		@param sAlto. Separación entre ficha y ficha(alto)
		@param sAlto. Separación entre ficha y ficha(ancho)
		*/
		tablero(conjuntoPersonajes& personajes, int nF, int nC, int sAlto,int sAncho);
		
		/**
		@brief Constructor de copias de la clase.
		@param otro. Objeto a copiar.
		*/
		tablero(const tablero& otro);
		
		/**
		@brief Sobrecarga del operador =
		@param otro. Objeto a igualar.
		*/
		tablero& operator= (const tablero& otro);
		
		/**
		@brief Destructor de la clase. Libera los recursos asociados a un tablero.
		*/
		~tablero();
		
		/**
		@brief Establece la ruta de la imagen para ocultar las fichas del tablero. Este método solo se le aplicará al tablero del jugador máquina.
		@param rutaImagen La ruta de la imagen en dico
		*/
		void setRuta(const char* dir);
		
		/**
		@return Número de fichas no descartadas.
		*/
		int noDescartados();
		
		/**
		@brief Establece como oculto el tablero. Este método solo se le aplicará al tablero del jugador máquina.
		*/
		void ocultar();
		
		/**
		@brief Dibuja en pantalla un conjunto de botones
		*/
		void dibujar();
		
		/**
		@brief Restaura el tablero. Poniendo a todas las fichas como no descartadas.
		*/
		void restaurar();
		
		/**
		@return El último personaje del tablero sin descartar.
		*/
		personaje ultimoPersonaje();
		
		/**
		@brief Comprueba si el ratón pulsó algún personaje sin descartar, y si así es entonces lo descarta.
		@param x. Coordenada x en la que se pulsó con el ratón.
		@param y. Coordenada y en la que se pulsó con el ratón.
		*/
		void descartar(int x1, int y1);
		
		/**
		@brief Descarta un conjunto de personajes dada una pregunta y una respuesta. PE: ralizada=¿Es hombre?, respuesta=true -> Borra a todas las mujeres del tablero. Método solo usado en el tablero de la máquina.
		@param realizada. Pregunta que se ha realizado.
		@param respuesta. Respuesta a la pregunta realizada.
		*/
		void descartarConjunto(pregunta realizada, bool respuesta);
		
		/**
		@brief Sobrecarga del operador de insercción >>
		*/
		friend istream& operator >> (istream& in, tablero& otro);
		
		/**
		@brief Sobrecarga del operador de insercción >>
		*/
		friend ostream& operator << (ostream& out,const tablero& otro);
	private:
		/**
		@brief Copia un tablero en otro.
		@param otro. Tablero a copiar.
		*/
		void copiar(const tablero& otro);
		
		/**
		@brief Libera los recursos asociados a un tablero.
		*/
		void liberarMemoria();
};

#endif
