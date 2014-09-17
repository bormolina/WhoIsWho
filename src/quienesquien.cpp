/**
@title quienesquien.cpp
@brief Fichero con la funcion main del juego
@author Borja Molina Zea. borja.mz8@gmail.com
@date 31/05/2009
*/

#include"tablero.h"
#include"conjuntoPreguntas.h"
#include"botones.h"
#include"personajeOculto.h"
#include"terminal.h"

int main(int argc, char* argv[]){
	char nombreJugador[30]; //Variable en la que almacenamos el nombre del jugador (tercer parametro que pasamos por la terminal)
	
	//Monstramos mensaje de error si el número de parámetros proporcionados no es correcto	
	if(argc<2 || argc>3){
		cerr<<"Error en el número de parámetros. Deben de ser 2 o 3. Formato: NombrePrograma FicheroConfiguracion NombreJugador(opcional)";
		exit(1);
	}
	//Si no se especifica el nombre del jugador, lo llamamos Humano por defecto.
	if(argc==2)
		strcpy(nombreJugador,"Humano");
	if(argc==3){
		strcpy(nombreJugador,argv[2]);
	}
	
	//####### LECTURA Y MODIFICACION DE LOS FICHEROS DE CONFIGURACIÓN #########
	//Abrimos el fichero de configuración
	ifstream conComentarios(argv[1]);
	if(!conComentarios){cerr<<"Error al abrir el fichero "<<argv[1]<<endl;exit(1);}
	
	//Abrimos el fichero data/ConfigFile.txt donde guardaremos el fichero de configuración si comentarios y convenientemente formateado.
	ofstream sinComentarios("data/CofigFile.txt");
	if(!sinComentarios){cerr<<"Error al abrir/crear el fichero CofigFile.txt\n";exit(1);}
	
	//Quitamos los comentarios y cerramos el flujo hacia los ficheros.
	QuitarComentarios(conComentarios,sinComentarios);
	conComentarios.close();
	sinComentarios.close();
	
	//Abrimos el fichero de configuracion en modo de lectura
	ifstream config("data/CofigFile.txt");
	if(!config){cerr<<"Error al abrir el fichero data/cofigFile.txt\n";exit(1);}
	
	//####### DECLARACIÓN DE LAS VARIABLES  #########
	int ancho,alto,nFils,nCols,sepAlto,sepAncho,tiempo,x,y,cont,puntuacion=0;
	bool vencedor=false,humano,numeroCorrecto;
	char ruta[999]; //cadena dónde guardamos la ruta del personaje oculto
	char preguntaRealizada[999]; //Cadena dónde almacenamos la preguntas que se van realizando a lo largo del juego
	pregunta realizada;
	personaje pj;
	TTecla tecla=SDLK_UNKNOWN; TBotonRaton raton=SDLK_UNKNOWN;
	
	//####### DECLARACIÓN DE LOS OBJETOS Y LECTURA DE LOS MISMOS #########
	conjuntoRasgos rasgos;
	conjuntoPersonajes personajes;
	config>>rasgos>>personajes;
	config>>ancho>>alto>>nFils>>nCols>>sepAncho>>sepAlto;
	tablero tableroHumano(personajes,nFils,nCols,sepAlto,sepAncho); // Tablero del jugador humano
	config>>tableroHumano;
	conjuntoPreguntas preguntas(rasgos); // Todo el conjunto de preguntas posibles dado un conjunto de rasgos
	config>>preguntas;
	tablero tableroMaquina(personajes,nFils,nCols,sepAlto,sepAncho); //Tablero de la masquina
	config>>tableroMaquina;
	personajeOculto ocultoHumano(personajes,true); //El personaje oculto del jugador humano
	personajeOculto ocultoMaquina(personajes,false); //El personaje oculto del jugador máquina
	botones info; //Zona de botones, dónde están stop, restaurar, tiempo acumulado...
	terminal term;
	config>>ocultoHumano>>ocultoMaquina>>info>>term>>ruta>>tiempo;
	
	//Una vez leidos todos los datos cerramos el fichero de configuración
	config.close();
	
	term.setNombreJugador(nombreJugador);//Le pasamos a la terminal el nombre del jugador humano
	term.setNombreMaquina("Maquina");//Le pasamos a la terminal el nombre del jugador maquina
	info.setTiempo(tiempo);//Fijamos el tiempo para responder
	ocultoMaquina.setRuta(ruta);//Le decimos cual es la ruta de la imagen desconocido.bmp
	ocultoMaquina.ocultar();//Ocultamos (hacemos que salga la imagen de desconocido.bmp) del jugador oculto de la maquina
	tableroMaquina.setRuta(ruta);//Le decimos cual es la ruta de la imagen desconocido.bmp
	tableroMaquina.ocultar();//Ocultamos (hacemos que salga la imagen de desconocido.bmp) en el tablero de la máquina
		
	//Creamos la ventana y dibujamos los tableros, la zona de preguntas, la zona de botones, la terminal y los personajes ocultos.	
	CrearVentana(ancho,alto,"Quien es quien");
	tableroHumano.dibujar();
	preguntas.dibujar();
	tableroMaquina.dibujar();
	info.dibujar();
	ocultoHumano.dibujar();
	ocultoMaquina.dibujar();
	term.dibujar();
	//Establecemos si empieza a jugar la maquina o nosotros
	if(aleatorio(1)) humano=true;
	else humano=false;
	
	//CODIGO DEL DESARROLLO DEL JUEGO
	while(!vencedor){ //Mientras no haya vencedor
		if(tableroHumano.noDescartados()>1 && tableroMaquina.noDescartados()>1){ //Si queda mas de un personaje por descartar
			if(humano){//Si empieza jugando el jugador humano
				numeroCorrecto=false;
				cont=0;
				//Esperamos a que el jugador inserte el número de la pregunta que quiere formular
				for(int i=strlen(preguntaRealizada)-1;i>-1;i--)//Borramos la posible información que puediese haber en el buffer dónde almacenamos el número de pregunta realizada.
					preguntaRealizada[i]='\0';
				while(!numeroCorrecto){//Mientras que el numero tecleado no sea correcto.
					tecla=EsperarTecla();//Obtenemos la tecla pulsada
					//Si la tecla es la de algún número
					if(tecla==SDLK_1 || tecla==SDLK_2 || tecla==SDLK_3 || tecla==SDLK_4 || tecla==SDLK_5 || tecla==SDLK_6 || tecla==SDLK_7 || tecla==SDLK_8 || tecla==SDLK_9 || tecla==SDLK_0){
						preguntaRealizada[cont]=(char) tecla;//La insertamos como un char en nuestro buffer
						cont++;
					}
					if(tecla==SDLK_RETURN && preguntaRealizada[0]!='\0'){//Si la tecla pulsada es intro y hay algo en el buffer
						//Comprobamos que el número introducido esté asociado a alguna pregunta
						if(atoi(preguntaRealizada)<preguntas.tamanho() && atoi(preguntaRealizada)>-1) numeroCorrecto=true;
						else{//Si no es así mostramos un mensaje de error diciendo que el número ingresado no es correcto.
							term.mensajeError();
						 	cont=0;
						 	for(int i=strlen(preguntaRealizada)-1;i>-1;i--)//Y limpiamos nuestro buffer.
								preguntaRealizada[i]='\0';
						}
					}
				}	 
				realizada=preguntas.getPregunta(atoi(preguntaRealizada));//La pregunta realizada será la asociada al número que hayamos tecleado.
				term.insertarLinea(realizada.getEnunciado(),true);//Mostramos en la terminal el enunciado de la pregunta realizada.
			
			}
			else{//Si el turno es de la máquina
				realizada=preguntas.getAleatoria();//Hacemos que la máquina realiza una pregunta al azar.
				term.insertarLinea(realizada.getEnunciado(),false);//Mostramos  la pegunta realizada por la terminal.
			}
			
			//Establecemos cual será el personaje oculto sobre el que se hará la pregunta.
			if(humano) pj=ocultoMaquina.getPersonaje();//Si el turno es humano será sobre el de la máquina.
			else pj=ocultoHumano.getPersonaje();//Si el turno es de la maquina será sobre el del jugador humano.
			bool respuesta=preguntas.responder(pj,realizada);//Albergamos si la respuesta es positiva o negativa
			
			//Mostramos en el terminal "si" o "no", según proceda
			humano?humano=false:humano=true;
			respuesta?term.insertarLinea("Si",humano):term.insertarLinea("No",humano);
			humano?humano=false:humano=true;
			
			//### TIEMPO DE DESCARTE ###
			if(humano){//Si es el turno del humano
				CronometroInicio();//Iniciamos el crono.
				bool stop=false;
				while(CronometroValor()<tiempo && !stop){//Mientras que haya tiempo y el jugador no pulse el botón de stop
					ConsultarTeclaRaton(tecla, raton, x, y);//Consultamos el ratón
					if(raton==SDL_BUTTON_LEFT){//Si hace click con el botón izquierdo
						tableroHumano.descartar(x,y);//Comprobamos si hace click sobre un personaje del tablero
						if(info.stop(x,y)) stop=true;//Comprobamos si hace click el botón de stop
						if(info.restaurar(x,y)) tableroHumano.restaurar();//Comprobamos si hace click sobre el botón de restaurar.
					}
					info.actualizar(CronometroValor());//Actualizamos el cromometro con el tiempo que ha transcurrido.
				}
				puntuacion+=CronometroValor();
				info.sumarPuntuacion(puntuacion);//Añadimos los segundos transcurridos.
				info.resetCrono();//Ponemos el crono a cero de nuevo.
			}
			//Si el turno es de la máquina
			else tableroMaquina.descartarConjunto(realizada,respuesta);//Eliminamos todos los posibles personajes que cumplan o no (depende de si la respuesta es afirmativa o no) el rasgo y valor de la pregunta realizada.
			
			//Cambiamos el turno
			humano?humano=false:humano=true;
		}
		
		//Si ya solo queda un personaje por descartar
		else{ 
			if(tableroHumano.noDescartados()==1){ //Si el personaje es del tablero del humano
				personaje oculto=tableroHumano.ultimoPersonaje();
				term.preguntarPorPersonaje(oculto,true); //La terminal pregunta si ese es el personaje oculto
				if(ocultoMaquina==oculto){ //Si no nos hemos aquivocado, mostramos mensaje de victoria y acabamos el juego
					vencedor=true;
					term.mensajeVictoria();
				}
				else{//Si nos hemos aquivocado restauramos el tablero y mostramos mensaje de error.
					term.mensajeError2();
					tableroHumano.restaurar();
				}
			}
			else{// Si la maquina adivina antes que nosotros mostramos el mensaje de derrota y acabamos el juego
				vencedor=true;
				personaje oculto=tableroMaquina.ultimoPersonaje();
				term.preguntarPorPersonaje(oculto,false);//La terminal pregunta si ese es el personaje oculto
				term.mensajeDerrota();
			}
		}
	}
	EsperarTecla();
}
