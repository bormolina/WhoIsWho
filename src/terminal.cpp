#include"terminal.h"

terminal::terminal(){
		lineas=0;
		nMaxLineas=nLineas=0;
		x=y=x1=y1=ancho=alto=anchoMarco=altoMarco=tamFuente=0;
		ruta=nombreJugador=nombreMaquina=0;
		font=0;
		
		for(int i=0;i<3;i++)
			colorFondo[i]=colorMarco[i]=colorFuente[i]=0;
}

terminal::terminal(const terminal& otro){
	copiar(otro);
}

terminal& terminal::operator =(const terminal& otro){
	if(this!=&otro){
		liberarMemoria();
		copiar(otro);
	}	
	return *this;
}

terminal::~terminal(){
	liberarMemoria();
}
		
void terminal::dibujar(){
	DesactivarDibujo();
	
	RectanguloR(x, y, x+ancho, y+alto, colorFondo[0], colorFondo[1], colorFondo[2]);
	DibujarMarco(anchoMarco,altoMarco,x,y,x+ancho,y+alto,colorMarco);
	
	ActivarDibujo();
}

void terminal::insertarLinea(const char* text, bool human){
	char buffer[999];
	
	if(nLineas<nMaxLineas){//Si aún no se ha llegado a la ultima linia
		strcpy(lineas[nLineas].texto,text);
		lineas[nLineas].humano=human;
			
		if(lineas[nLineas].humano) strcpy(buffer,nombreJugador);
		else strcpy(buffer,nombreMaquina);
		
		strcat(buffer,">");
		strcat(buffer,lineas[nLineas].texto);
		
		//Copiams el texto sin necesidad de borrar las otras lineas e incrementamos la variable nLineas.
		EscribirTexto(x1,y1,buffer,font,colorFuente[0],colorFuente[1],colorFuente[2]);
		
		nLineas++;
		y1+=(alto-anchoMarco)/nMaxLineas;//Hayamos los pixeles del salto de linea, para que todo quede centrado
	}
	
	else{//Si la terminal ya esta llena
		//Hacemos que la linea i-esima ahora sea la linea i-esima-1, y la primera de todas desaparece de la terminal
		for(int i=0;i<nLineas-1;i++){
			lineas[i].humano=lineas[i+1].humano;
			strcpy(lineas[i].texto,lineas[i+1].texto);
		}
		//En la ultima linea ponemos el último texto en entrar
		strcpy(lineas[nLineas-1].texto,text);
		lineas[nLineas-1].humano=human;
		
		for(int i=0;i<nMaxLineas;i++)
			y1-=(alto-anchoMarco)/nMaxLineas;
		
		//Borramos lo que habia en la terminal
		RectanguloR(x+anchoMarco, y+altoMarco, x+ancho-anchoMarco, y+alto-altoMarco, colorFondo[0], colorFondo[1], colorFondo[2]);
		
		//Volvemos a dibujar todo con las posiciones actualizadas.
		for(int i=0;i<nMaxLineas;i++){
			if(lineas[i].humano) strcpy(buffer,nombreJugador);
			else strcpy(buffer,nombreMaquina);
		
			strcat(buffer,">");
			strcat(buffer,lineas[i].texto);
			EscribirTexto(x1,y1,buffer,font,colorFuente[0],colorFuente[1],colorFuente[2]);
			y1+=(alto-anchoMarco)/nMaxLineas;//Hayamos los pixeles del salto de linea, para que todo quede centrado
		}
	}
}
	
void terminal::preguntarPorPersonaje(personaje ultimo, bool human){
	char buffer[999]="¿Es ";
	strcat(buffer,ultimo.getNombre());
	strcat(buffer," el personaje oculto?");
	insertarLinea(buffer,human);	
}
	
void terminal::borrarLinea(){
	RectanguloR(x1, y1-AltoFuente(font)-altoMarco-1, x1+ancho-anchoMarco, y1, colorFondo[0], colorFondo[1], colorFondo[2]);	
	if(nLineas<nMaxLineas){
		nLineas--;
		y1-=(alto-anchoMarco)/nMaxLineas;
	}
}

void terminal::mensajeError(){
	insertarLinea("Ha tecleado un numero de pregunta inexistente, vuelva a teclear con mas cuidado y paciencia, no es tan difícil:",false);
}

void terminal::mensajeError2(){
	insertarLinea("¡Te has equivocado, ese no era el personaje oculto ¬¬!, a ver si tienes mas cuidado para la próxima vez",false);
}
		
void terminal::mensajeVictoria(){
	insertarLinea("...···¨¨¨SI---->Enhorabuena, tú ganas¨¨¨···...",false);
}

void terminal::mensajeDerrota(){
	insertarLinea("SI--->Lo siento, la máquina ha adivinado el personaje antes que tú.",false);
}
		
void terminal::setNombreJugador(const char* nombre){
	nombreJugador=new(nothrow) char[strlen(nombre)+1];
	if(!nombreJugador){cerr<<"Error en la reserva de memoria\n";exit(1);}
	strcpy(nombreJugador,nombre);
}

void terminal::setNombreMaquina(const char* nombre){
	nombreMaquina=new(nothrow) char[strlen(nombre)+1];
	if(!nombreMaquina){cerr<<"Error en la reserva de memoria\n";exit(1);}
	strcpy(nombreMaquina,nombre);
}
		
istream& operator>> (istream& in, terminal& otro){
	char buffer[999],buffer1[999],buffer2[999],buffer3[999];
	
	//Leemos los datos referentes a una terminal
	in.getline(buffer,999);
	DividirEnDos(buffer,buffer1,buffer2,Buscar(' ',1,buffer));
	otro.x=atoi(buffer1);
	otro.y=atoi(buffer2);
	
	in.getline(buffer,999);
	DividirEnDos(buffer,buffer1,buffer2,Buscar(' ',1,buffer));
	otro.ancho=atoi(buffer1);
	otro.alto=atoi(buffer2);
	
	in.getline(buffer,999);
	DividirEnTres(buffer,buffer1,buffer2,buffer3,Buscar(' ',1,buffer),Buscar(' ',2,buffer));
	otro.colorFondo[0]=atoi(buffer1);
	otro.colorFondo[1]=atoi(buffer2);
	otro.colorFondo[2]=atoi(buffer3);
	
	in.getline(buffer,999);
	DividirEnDos(buffer,buffer1,buffer2,Buscar(' ',1,buffer));
	otro.anchoMarco=atoi(buffer1);
	otro.altoMarco=atoi(buffer2);
	
	in.getline(buffer,999);
	DividirEnTres(buffer,buffer1,buffer2,buffer3,Buscar(' ',1,buffer),Buscar(' ',2,buffer));
	otro.colorMarco[0]=atoi(buffer1);
	otro.colorMarco[1]=atoi(buffer2);
	otro.colorMarco[2]=atoi(buffer3);
	
	in.getline(buffer,999);
	otro.ruta=new(nothrow) char[strlen(buffer)+1];
	if(!otro.ruta){cerr<<"Error en la reserva de memoria 8 de la clase conjuntoPreguntas\n";exit(1);}
	strcpy(otro.ruta,buffer);
	
	in.getline(buffer,999);
	otro.tamFuente=atoi(buffer);
	
	in.getline(buffer,999);
	DividirEnTres(buffer,buffer1,buffer2,buffer3,Buscar(' ',1,buffer),Buscar(' ',2,buffer));
	otro.colorFuente[0]=atoi(buffer1);
	otro.colorFuente[1]=atoi(buffer2);
	otro.colorFuente[2]=atoi(buffer3);
	
	in.getline(buffer,999);
	otro.nMaxLineas=atoi(buffer);
	
	otro.font=CargarFuente(otro.ruta, otro.tamFuente);
	
	otro.lineas=new (nothrow) LineaTexto[otro.nMaxLineas];
	if(!otro.lineas){cerr<<"Error en la reserva de memoria\n";exit(1);}
	
	otro.x1=otro.x+otro.anchoMarco;
	otro.y1=otro.y+otro.altoMarco;
	
	return in;
}

ostream& operator<< (ostream& out, const terminal& otro){
		out<<otro.x<<" "<<otro.y<<endl<<otro.ancho<<" "<<otro.alto<<endl;
	for(int i=0;i<3;i++)
		out<<otro.colorFondo[i]<<" ";
	out<<endl<<otro.anchoMarco<<" "<<otro.altoMarco<<endl;
	for(int i=0;i<3;i++)
		out<<otro.colorMarco[i]<<" ";
	out<<endl<<otro.ruta<<endl;
		
	return out;
}
	
void terminal::copiar(const terminal& otro){
	nMaxLineas=otro.nMaxLineas;
	nLineas=otro.nLineas;
	x1=otro.x1;
	y1=otro.y1;
	
	lineas=new(nothrow) LineaTexto[nMaxLineas];
	if(!lineas){cerr<<"Error en la reserva de memoria de la clase terminal\n";exit(1);}
	
	for(int i=0; i<nLineas; i++){
		strcpy(lineas[i].texto,otro.lineas[i].texto);
		lineas[i].humano=otro.lineas[i].humano;
	}
	
	x=otro.x;
	y=otro.y;
	ancho=otro.ancho;
	alto=otro.alto;
	anchoMarco=otro.anchoMarco;
	altoMarco=otro.altoMarco;
	tamFuente=otro.tamFuente;
	
	for(int i=0;i<3;i++){
		colorFondo[i]=otro.colorFondo[i];
		colorMarco[i]=otro.colorMarco[i];
		colorFuente[i]=otro.colorFuente[i];
	}
	
	if(otro.ruta){
		ruta=new(nothrow)char[strlen(otro.ruta)+1];
		if(!ruta){cerr<<"Error en la reserva de memoria de la clase terminal\n";exit(1);}
		strcpy(ruta,otro.ruta);
		font=CargarFuente(ruta,tamFuente);
	}
	
	else{
		ruta=0;
		font=0;
	}

	if(otro.nombreJugador){
		nombreJugador=new(nothrow)char[strlen(otro.nombreJugador)+1];
		if(!nombreJugador){cerr<<"Error en la reserva de memoria de la clase terminal\n";exit(1);}
		strcpy(nombreJugador,otro.nombreJugador);
	}
	
	else nombreJugador=0;
		
		
	if(otro.nombreMaquina){
		nombreMaquina=new(nothrow)char[strlen(otro.nombreMaquina)+1];
		if(!nombreMaquina){cerr<<"Error en la reserva de memoria de la clase terminal\n";exit(1);}
		strcpy(nombreMaquina,otro.nombreMaquina);
	}
	
	else nombreMaquina=0;
}

void terminal::liberarMemoria(){
	if(ruta) delete[] ruta;
	if(lineas) delete[] lineas;
	if(font) LiberarFuente(font);
	if(nombreJugador) delete[] nombreJugador;
	if(nombreMaquina) delete[] nombreMaquina;
}
