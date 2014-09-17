#include"tablero.h"

tablero::tablero(conjuntoPersonajes& personajes, int nF, int nC, int sAlto,int sAncho){
	x=y=ancho=alto=anchoMarco=altoMarco=0;
	
	for(int i=0;i<3;i++)
		colorMarco[i]=colorFondo[i]=colorTachar[i]=0;
	
	nFilas=nF;
	nColumnas=nC;
	separacionAlto=sAlto;
	separacionAncho=sAncho;
	
	nFichas=sinDescartar=personajes.tamanho();
	oculto=false;
	ruta=0;
	
	fichas=new(nothrow) Ficha[nFichas];
	if(!fichas){cerr<<"Error en la reserva de memoria 1 de la clase tablero\n";exit(1);}
	
	//Insertamos los personajes del conjunto de personajes en nuestro tablero
	for(int i=0, c=0; i<nFichas; i++){
		fichas[i].PJ= personajes.get(i);
		fichas[i].descartado=false;
	}
}

tablero::tablero(const tablero& otro){
	copiar(otro);
}

tablero& tablero::operator =(const tablero& otro){
	if(this!=&otro){
		liberarMemoria();
		copiar(otro);
	}
	return *this;
}

tablero::~tablero(){
	liberarMemoria();	
}

void tablero::setRuta(const char* dir){
	if(ruta) delete[] ruta;
	ruta=new(nothrow) char[strlen(dir)+1];	
	if(!ruta){cerr<<"Error en la reserva de memoria 2 de la clase tablero\n";exit(1);}
	strcpy(ruta,dir);
}

int tablero::noDescartados(){
	return sinDescartar;
}

void tablero::ocultar(){
	oculto=true;
}

void tablero::dibujar(){
	RectanguloR(x, y, x+ancho, y+alto, colorFondo[0], colorFondo[1], colorFondo[2]);
	DibujarMarco(anchoMarco,altoMarco,x,y,x+ancho,y+alto,colorMarco);
	
	personaje temp=fichas[0].PJ;
	int anchura=temp.ancho();
	int altura=temp.alto();
	int x1=x+anchoMarco+anchura;
	int y1=y+altoMarco+altura;
	DesactivarDibujo();
	//Dibujamos uno por uno los personajes del tablero
	if(!oculto){//Si no están ocultos lo hacemos dibujando su imagen asociada
		for(int i=0;i<nFichas;i++){
			x1=fichas[i].x;
			y1=fichas[i].y;
			fichas[i].PJ.dibujar(x1,y1);
		}
	}

	else{//Si están ocultos lo hacemos dibujandolos con la imagen de jugador desconocido
		imagen fichaOculta(ruta);
		for(int i=0;i<nFichas;i++){
		x1=fichas[i].x;
		y1=fichas[i].y;
		fichaOculta.dibujar(x1,y1);
		}
	}
	ActivarDibujo();
}

void tablero::restaurar(){
	for(int i=0;i<nFichas;i++){
		fichas[i].descartado=false;//Ponemos todos los personajes como no descartados
	}
	sinDescartar=nFichas;
	dibujar();
}

personaje tablero::ultimoPersonaje(){
	personaje ultimo;
	if(sinDescartar==1){
		for(int i=0; i<nFichas; i++)
			if(fichas[i].descartado==false)
				ultimo=fichas[i].PJ;
	}
	return ultimo;
}

void tablero::descartar(int x1, int y1){
	if(!oculto){
		personaje temp;
		int anchura=fichas[0].PJ.ancho();
		int altura=fichas[0].PJ.alto();
		int x2,y2;
		for(int i=0;i<nFichas;i++){
			temp=fichas[i].PJ;
			x2=fichas[i].x;
			y2=fichas[i].y;
			//Comprobamos que donde se pinchó con el ratón fuese una ficha y que el personaje no estuviese previamente descartado.
			if(x1>=x2 && x1<=x2+anchura && y1>=y2 && y1<=y2+altura && fichas[i].descartado==false){
				fichas[i].descartado=true;
				sinDescartar--;
				RectanguloR(x2,y2,x2+anchura,y2+altura,colorTachar[0],colorTachar[1],colorTachar[2]);
			}
		}
	}
}

void tablero::descartarConjunto(pregunta realizada, bool respuesta){
	if(oculto){
		for(int i=0;i<nFichas; i++){
			personaje temp=fichas[i].PJ;
			int anchura=temp.ancho();
			int altura=temp.alto();
			int pos;
			//Encontramos la posicion del valor del rasgo asociado a la pregunta del personaje i-ésimo
			if(!fichas[i].descartado){
				for(int j=0;j<temp.getNRasgos();j++){
						if(!strcmp(realizada.getNombre(),temp.getRasgo(j)))
							pos=j;
					}
				//Si la respuesta es positiva, entonces descartamos aquellos personajes que no la cumplan. PE: ¿Es mujer? si, luego borramos todos aquello que no sean mujeres.
				if(respuesta){
					if(strcmp(realizada.getValor(),temp.getValor(pos))){
						fichas[i].descartado=true;
						sinDescartar--;
						RectanguloR(fichas[i].x,fichas[i].y,fichas[i].x+anchura,fichas[i].y+altura,colorTachar[0],colorTachar[1],colorTachar[2]);
					}
				}
				//Si la respuesta es negativa, entonces descartamos aquellos personajes que la cumplan. PE: ¿Es mujer? no, luego borramos todos aquellos que no sean mujeres.
				else{
					if(!strcmp(realizada.getValor(),temp.getValor(pos))){
						fichas[i].descartado=true;
						sinDescartar--;
						RectanguloR(fichas[i].x,fichas[i].y,fichas[i].x+anchura,fichas[i].y+altura,colorTachar[0],colorTachar[1],colorTachar[2]);
					}
				}
			}	
		}
		
	}
}
		
istream& operator >> (istream& in, tablero& otro){
	char buffer[999],buffer1[999],buffer2[999],buffer3[999];
	
	//Leemos los datos referentes a un tablero
	while(in.peek()=='\n' || in.peek()==' '){in.get();}// Se quitan los posibles ' ' y \n sobrantes
	/*Lo de quitar los \n y los ' ' lo hacemos porque en la lectura anterior de datos hemos usado el operador >>
	el cual no extrae del flujo los '\n', por lo tanto los quitamos "manuanlmente"*/
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
	DividirEnTres(buffer,buffer1,buffer2,buffer3,Buscar(' ',1,buffer),Buscar(' ',2,buffer));
	otro.colorTachar[0]=atoi(buffer1);
	otro.colorTachar[1]=atoi(buffer2);
	otro.colorTachar[2]=atoi(buffer3);
	
	int x1=otro.x+otro.anchoMarco;
	int y1=otro.y+otro.altoMarco;
	
	//En esta parte lo que establecemos es la posición de los personaje en el tablero.
	for(int i=0, c=0; i<otro.nFichas; i++){
		otro.fichas[i].x=x1;
		otro.fichas[i].y=y1;
		
		x1+=otro.separacionAncho+otro.fichas[i].PJ.ancho();
		c++;
		
		//Si llegamos al final de la fila, entonces incrementamos el valor de la coordenada y para cambiar a una nueva fila
		if(c%otro.nColumnas==0){
			c=0;
			x1=otro.x+otro.anchoMarco;
			y1+=otro.separacionAlto+otro.fichas[i].PJ.alto();
		}
	}	
	
	return in;	
}

ostream& operator << (ostream& out,const tablero& otro){
	out<<otro.x<<" "<<otro.y<<endl<<otro.ancho<<" "<<otro.alto<<endl;
	for(int i=0;i<3;i++)
		out<<otro.colorFondo[i]<<" ";
	out<<endl<<otro.anchoMarco<<" "<<otro.altoMarco<<endl;
	for(int i=0;i<3;i++)
		out<<otro.colorMarco[i]<<" ";
	out<<endl;
	for(int i=0;i<3;i++)
		out<<otro.colorTachar[i]<<" ";
	out<<endl;
	return out;
}

void tablero::copiar(const tablero& otro){
	x=otro.x; y=otro.y;
	ancho=otro.ancho; alto=otro.alto;
	anchoMarco=otro.anchoMarco; altoMarco=otro.altoMarco;
	nFilas=otro.nFilas; nColumnas=otro.nColumnas;
	separacionAlto=otro.separacionAlto; separacionAncho=otro.separacionAncho;
	nFichas=otro.nFichas; sinDescartar=otro.sinDescartar;
	oculto=otro.oculto;
	
	for(int i=0; i<3; i++){
		colorFondo[i]=otro.colorFondo[i];
		colorMarco[i]=otro.colorMarco[i];
		colorTachar[i]=otro.colorTachar[i];
	}
	
	if(otro.ruta){
		ruta=new (nothrow) char[strlen(otro.ruta)+1];
		strcpy(ruta,otro.ruta);	
	}
	
	else
		ruta=0;
}

void tablero::liberarMemoria(){
	if(ruta) delete[] ruta;
	if(fichas)	delete[] fichas;
}
