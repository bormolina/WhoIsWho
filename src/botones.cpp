#include"botones.h"

botones::botones(){
	//Inicializmos todas las variables a 0.
	x=y=ancho=alto=anchoMarco=altoMarco=0;
	xTiempo=yTiempo=anchoTiempo=altoTiempo=anchoMarcoTiempo=altoMarcoTiempo=0;
	xCrono=yCrono=anchoCrono=altoCrono=anchoMarcoCrono=altoMarcoCrono=0;
	xRestaurar=yRestaurar=anchoRestaurar=altoRestaurar=anchoMarcoRestaurar=altoMarcoRestaurar=0;
	
	ruta=0;
	font=0;
	
	tamFuente=tiempo=tTranscurrido=0;
	
	for(int i=0;i<3;i++){
		colorFondo[i]=colorMarco[i]=colorFondoTiempo[i]=colorMarcoTiempo[i]=0;
		colorFondoStop[i]=colorMarcoStop[i]=colorFondoCrono[i]=colorMarcoCrono[i]=0;
		colorFondoRestaurar[i]=colorMarcoRestaurar[i]=colorCrono[i]=colorFuente[i]=0;
	}
}
		
botones::botones(const botones& otro){
	copiar(otro);
}

botones& botones::operator=(const botones& otro){
	if(this!=&otro){
		liberarMemoria();
		copiar(otro);
	}
	return *this;
}

botones::~botones(){
	liberarMemoria();
}
		
void botones::dibujar(){
	DesactivarDibujo();
	
	//Dibujamos el recuadro donde se siturarán los botones
	RectanguloR(x, y, x+ancho, y+alto, colorFondo[0], colorFondo[1], colorFondo[2]);
	DibujarMarco(anchoMarco,altoMarco,x,y,x+ancho,y+alto,colorMarco);

	//Dibujamos el recuadro del tiempo acumulado.
	RectanguloR(xTiempo, yTiempo, xTiempo+anchoTiempo, yTiempo+altoTiempo, colorFondoTiempo[0], colorFondoTiempo[1], colorFondoTiempo[2]);
	DibujarMarco(anchoMarcoTiempo,altoMarcoTiempo,xTiempo,yTiempo,xTiempo+anchoTiempo,yTiempo+altoTiempo,colorMarcoTiempo);
	
	//Dibujamos el recuadro de stop.
	RectanguloR(xStop, yStop, xStop+anchoStop, yStop+altoStop, colorFondoStop[0], colorFondoStop[1], colorFondoStop[2]);
	DibujarMarco(anchoMarcoStop,altoMarcoStop,xStop,yStop,xStop+anchoStop,yStop+altoStop,colorMarcoStop);
	
	//Dibujamos el crono.
	RectanguloR(xCrono, yCrono, xCrono+anchoCrono, yCrono+altoCrono, colorFondoCrono[0], colorFondoCrono[1], colorFondoCrono[2]);
	DibujarMarco(anchoMarcoCrono,altoMarcoCrono,xCrono,yCrono,xCrono+anchoCrono,yCrono+altoCrono,colorMarcoCrono);
	
	//Dibujamos el recuadro de restaurar.
	RectanguloR(xRestaurar, yRestaurar, xRestaurar+anchoRestaurar, yRestaurar+altoRestaurar, colorFondoRestaurar[0], colorFondoRestaurar[1], colorFondoRestaurar[2]);
	DibujarMarco(anchoMarcoRestaurar,altoMarcoRestaurar,xRestaurar,yRestaurar,xRestaurar+anchoRestaurar,yRestaurar+altoRestaurar,colorMarcoRestaurar);
	
	//Escribimos el nombre de los recuadros
	EscribirTexto(xTiempo+(anchoTiempo/4),yTiempo+(altoTiempo/3),"0",font,colorFuente[0],colorFuente[1],colorFuente[2]);
	
	EscribirTexto(xRestaurar+(anchoRestaurar/4),yRestaurar+(altoRestaurar/3),"RESTAURAR",font,colorFuente[0],colorFuente[1],colorFuente[2]);
	
	EscribirTexto(xStop+(anchoStop/3),yStop+(altoStop/3),"STOP",font,colorFuente[0],colorFuente[1],colorFuente[2]);
	
	GRF_Fuente font2=CargarFuente(ruta,tamFuente,TTF_STYLE_BOLD);
	EscribirTexto(xCrono,yCrono-25,"CRONOMETRO:",font2,colorFuente[0],colorFuente[1],colorFuente[2]);
	LiberarFuente(font2);
	
	ActivarDibujo();
}
	
void botones::actualizar(long tiempoTrasncurrido){
	//Hacemos una sencilla regla de tres para averiguar como de grande debe de ser la barra de progreso del crono según el tiempo haya que hara pasado, el tiempo total y el ancho de la misma
	int factor=(tiempoTrasncurrido*(anchoCrono-anchoMarcoCrono*2))/tiempo;
	
	//Dibujamos un rectángulo acorde a la cantidad de tiempo que haya pasado
	RectanguloR(xCrono+anchoMarcoCrono,yCrono+altoMarcoCrono,xCrono+anchoMarcoCrono+factor,yCrono+altoCrono-altoMarcoCrono,colorCrono[0],colorCrono[1],colorCrono[2]);
}
		
void botones::sumarPuntuacion(int t){
	char buffer[5];
	tTranscurrido+=t;
	EnteroACadena(buffer,t);//Pasamos el tiempo trasncurrido a cadena
	
	DesactivarDibujo();
	RectanguloR(xTiempo, yTiempo, xTiempo+anchoTiempo, yTiempo+altoTiempo, colorFondoTiempo[0], colorFondoTiempo[1], colorFondoTiempo[2]);
	DibujarMarco(anchoMarcoTiempo,altoMarcoTiempo,xTiempo,yTiempo,xTiempo+anchoTiempo,yTiempo+altoTiempo,colorMarcoTiempo);
	//Escribimos en su recuadro el tiempo total transcurrido.
	EscribirTexto(xTiempo+(anchoTiempo/4),yTiempo+(altoTiempo/3),buffer,font,colorFuente[0],colorFuente[1],colorFuente[2]);
	ActivarDibujo();
}
		
bool botones::stop(int x, int y){
	//Comprobamos si x e y están en los dominios del recuadro de stop
	if(x<=xStop+anchoStop && x>=xStop && y<=yStop+altoStop && y>=yStop)
		return true;
	else
		return false;
}

bool botones::restaurar(int x, int y){
	//Comprobamos si x e y están en los dominios del recuadro de restaurar
	if(x<=xRestaurar+anchoRestaurar && x>=xRestaurar && y<=yRestaurar+altoRestaurar && y>=yRestaurar)
		return true;
	else
		return false;
}

void botones::resetCrono(){
	//Ponemos el crono a 0. Para ello borramos la barra de progreso, volviendo a dibujar el crono es su estado inicial
	RectanguloR(xCrono, yCrono, xCrono+anchoCrono, yCrono+altoCrono, colorFondoCrono[0], colorFondoCrono[1], colorFondoCrono[2]);
	DibujarMarco(anchoMarcoCrono,altoMarcoCrono,xCrono,yCrono,xCrono+anchoCrono,yCrono+altoCrono,colorMarcoCrono);

}

void botones::setTiempo(int t){
	tiempo=t;
}

istream& operator>>(istream& in, botones& otro){
	char buffer[999],buffer1[999],buffer2[999],buffer3[999];
	
	//Leemos la posición x,y de la la zona de botones
	in.getline(buffer,999);
	DividirEnDos(buffer,buffer1,buffer2,Buscar(' ',1,buffer));
	otro.x=atoi(buffer1);
	otro.y=atoi(buffer2);
	
	//Leemos el ancho y alto de la la zona de botones
	in.getline(buffer,999);
	DividirEnDos(buffer,buffer1,buffer2,Buscar(' ',1,buffer));
	otro.ancho=atoi(buffer1);
	otro.alto=atoi(buffer2);
	
	//Leemos el color de la la zona de botones
	in.getline(buffer,999);
	DividirEnTres(buffer,buffer1,buffer2,buffer3,Buscar(' ',1,buffer),Buscar(' ',2,buffer));
	otro.colorFondo[0]=atoi(buffer1);
	otro.colorFondo[1]=atoi(buffer2);
	otro.colorFondo[2]=atoi(buffer3);

	//Leemos el ancho y alto del marco de la la zona de botones
	in.getline(buffer,999);
	DividirEnDos(buffer,buffer1,buffer2,Buscar(' ',1,buffer));
	otro.anchoMarco=atoi(buffer1);
	otro.altoMarco=atoi(buffer2);

	//Leemos el color del marco de la la zona de botones
	in.getline(buffer,999);
	DividirEnTres(buffer,buffer1,buffer2,buffer3,Buscar(' ',1,buffer),Buscar(' ',2,buffer));
	otro.colorMarco[0]=atoi(buffer1);
	otro.colorMarco[1]=atoi(buffer2);
	otro.colorMarco[2]=atoi(buffer3);

	//Leemos la posición x,y del boton de puntuación
	in.getline(buffer,999);
	DividirEnDos(buffer,buffer1,buffer2,Buscar(' ',1,buffer));
	otro.xTiempo=atoi(buffer1);
	otro.yTiempo=atoi(buffer2);

	//Leemos el ancho y alto del botón de puntuación
	in.getline(buffer,999);
	DividirEnDos(buffer,buffer1,buffer2,Buscar(' ',1,buffer));
	otro.anchoTiempo=atoi(buffer1);
	otro.altoTiempo=atoi(buffer2);

	//Leemos el color del botón de puntuación
	in.getline(buffer,999);
	DividirEnTres(buffer,buffer1,buffer2,buffer3,Buscar(' ',1,buffer),Buscar(' ',2,buffer));
	otro.colorFondoTiempo[0]=atoi(buffer1);
	otro.colorFondoTiempo[1]=atoi(buffer2);
	otro.colorFondoTiempo[2]=atoi(buffer3);

	//Leemos el ancho y alto del marco del botón de puntuación.
	in.getline(buffer,999);
	DividirEnDos(buffer,buffer1,buffer2,Buscar(' ',1,buffer));
	otro.anchoMarcoTiempo=atoi(buffer1);
	otro.altoMarcoTiempo=atoi(buffer2);
	
	//Leemos el color del marco del botón de puntuación.
	in.getline(buffer,999);
	DividirEnTres(buffer,buffer1,buffer2,buffer3,Buscar(' ',1,buffer),Buscar(' ',2,buffer));
	otro.colorMarcoTiempo[0]=atoi(buffer1);
	otro.colorMarcoTiempo[1]=atoi(buffer2);
	otro.colorMarcoTiempo[2]=atoi(buffer3);
	
	//Leemos la pos x,y del botón de stop
	in.getline(buffer,999);
	DividirEnDos(buffer,buffer1,buffer2,Buscar(' ',1,buffer));
	otro.xStop=atoi(buffer1);
	otro.yStop=atoi(buffer2);

	//Leemos el ancho y alto del botón de stop
	in.getline(buffer,999);
	DividirEnDos(buffer,buffer1,buffer2,Buscar(' ',1,buffer));
	otro.anchoStop=atoi(buffer1);
	otro.altoStop=atoi(buffer2);

	//Leemos color de fondo del botón de stop
	in.getline(buffer,999);
	DividirEnTres(buffer,buffer1,buffer2,buffer3,Buscar(' ',1,buffer),Buscar(' ',2,buffer));
	otro.colorFondoStop[0]=atoi(buffer1);
	otro.colorFondoStop[1]=atoi(buffer2);
	otro.colorFondoStop[2]=atoi(buffer3);

	//Leemos el ancho y alto del botón de stop
	in.getline(buffer,999);
	DividirEnDos(buffer,buffer1,buffer2,Buscar(' ',1,buffer));
	otro.anchoMarcoStop=atoi(buffer1);
	otro.altoMarcoStop=atoi(buffer2);

	//Leemos el color del marco del botón de stop
	in.getline(buffer,999);
	DividirEnTres(buffer,buffer1,buffer2,buffer3,Buscar(' ',1,buffer),Buscar(' ',2,buffer));
	otro.colorMarcoStop[0]=atoi(buffer1);
	otro.colorMarcoStop[1]=atoi(buffer2);
	otro.colorMarcoStop[2]=atoi(buffer3);
	
	//Ahora leemos todos los datos referentes al crono.
	in.getline(buffer,999);
	DividirEnDos(buffer,buffer1,buffer2,Buscar(' ',1,buffer));
	otro.xCrono=atoi(buffer1);
	otro.yCrono=atoi(buffer2);

	in.getline(buffer,999);
	DividirEnDos(buffer,buffer1,buffer2,Buscar(' ',1,buffer));
	otro.anchoCrono=atoi(buffer1);
	otro.altoCrono=atoi(buffer2);

	in.getline(buffer,999);
	DividirEnTres(buffer,buffer1,buffer2,buffer3,Buscar(' ',1,buffer),Buscar(' ',2,buffer));
	otro.colorFondoCrono[0]=atoi(buffer1);
	otro.colorFondoCrono[1]=atoi(buffer2);
	otro.colorFondoCrono[2]=atoi(buffer3);

	in.getline(buffer,999);
	DividirEnDos(buffer,buffer1,buffer2,Buscar(' ',1,buffer));
	otro.anchoMarcoCrono=atoi(buffer1);
	otro.altoMarcoCrono=atoi(buffer2);

	in.getline(buffer,999);
	DividirEnTres(buffer,buffer1,buffer2,buffer3,Buscar(' ',1,buffer),Buscar(' ',2,buffer));
	otro.colorMarcoCrono[0]=atoi(buffer1);
	otro.colorMarcoCrono[1]=atoi(buffer2);
	otro.colorMarcoCrono[2]=atoi(buffer3);
	
	//Ahora leemos todos los datos referentes al botón de restaurar.
	in.getline(buffer,999);
	DividirEnDos(buffer,buffer1,buffer2,Buscar(' ',1,buffer));
	otro.xRestaurar=atoi(buffer1);
	otro.yRestaurar=atoi(buffer2);

	in.getline(buffer,999);
	DividirEnDos(buffer,buffer1,buffer2,Buscar(' ',1,buffer));
	otro.anchoRestaurar=atoi(buffer1);
	otro.altoRestaurar=atoi(buffer2);

	in.getline(buffer,999);
	DividirEnTres(buffer,buffer1,buffer2,buffer3,Buscar(' ',1,buffer),Buscar(' ',2,buffer));
	otro.colorFondoRestaurar[0]=atoi(buffer1);
	otro.colorFondoRestaurar[1]=atoi(buffer2);
	otro.colorFondoRestaurar[2]=atoi(buffer3);

	in.getline(buffer,999);
	DividirEnDos(buffer,buffer1,buffer2,Buscar(' ',1,buffer));
	otro.anchoMarcoRestaurar=atoi(buffer1);
	otro.altoMarcoRestaurar=atoi(buffer2);

	in.getline(buffer,999);
	DividirEnTres(buffer,buffer1,buffer2,buffer3,Buscar(' ',1,buffer),Buscar(' ',2,buffer));
	otro.colorMarcoRestaurar[0]=atoi(buffer1);
	otro.colorMarcoRestaurar[1]=atoi(buffer2);
	otro.colorMarcoRestaurar[2]=atoi(buffer3);
	
	in.getline(buffer,999);
	DividirEnTres(buffer,buffer1,buffer2,buffer3,Buscar(' ',1,buffer),Buscar(' ',2,buffer));
	otro.colorCrono[0]=atoi(buffer1);
	otro.colorCrono[1]=atoi(buffer2);
	otro.colorCrono[2]=atoi(buffer3);
	
	//Leemos la ruta de la fuente
	in.getline(buffer,999);
	otro.ruta=new(nothrow) char[strlen(buffer)+1];
	if(!otro.ruta){cerr<<"Error en la reserva de memoria 8 de la clase conjuntoPreguntas\n";exit(1);}
	strcpy(otro.ruta,buffer);
		
	//Leemos el tamaño de la fuente
	in.getline(buffer,999);
	otro.tamFuente=atoi(buffer);
	
	otro.font=CargarFuente(otro.ruta,otro.tamFuente);
	
	//Leemos el color de la fuente
	in.getline(buffer,999);
	DividirEnTres(buffer,buffer1,buffer2,buffer3,Buscar(' ',1,buffer),Buscar(' ',2,buffer));
	otro.colorFuente[0]=atoi(buffer1);
	otro.colorFuente[1]=atoi(buffer2);
	otro.colorFuente[2]=atoi(buffer3);
	
	return in;
}

ostream& operator<<(ostream& out, const botones& otro){
	out<<otro.x<<" "<<otro.y<<endl;
	out<<otro.ancho<<" "<<otro.alto<<endl;
	for(int i=0;i<3;i++)
		out<<otro.colorFondo[i]<<" ";
	out<<endl;
	out<<otro.anchoMarco<<' '<<otro.altoMarco;
	for(int i=0;i<3;i++)
		out<<otro.colorMarco[i]<<" ";
	out<<otro.ruta<<endl;
	return out;
}
		
void botones::copiar(const botones& otro){
	x=otro.x; y=otro.y; ancho=otro.ancho; alto=otro.alto; anchoMarco=otro.anchoMarco; altoMarco=otro.altoMarco;
	xTiempo=otro.xTiempo; yTiempo=otro.yTiempo; anchoTiempo=otro.anchoTiempo; altoTiempo=otro.altoTiempo; anchoMarcoTiempo=otro.anchoMarcoTiempo; altoMarcoTiempo=otro.altoMarcoTiempo;
	xStop=otro.xStop; yStop=otro.yStop; anchoStop=otro.anchoStop; altoStop=otro.altoStop; anchoMarcoStop=otro.anchoMarcoStop; altoMarcoStop=otro.altoMarcoStop;
	xCrono=otro.xCrono; yCrono=otro.yCrono; anchoCrono=otro.anchoCrono; altoCrono=otro.altoCrono; anchoMarcoCrono=otro.anchoMarcoCrono; altoMarcoCrono=otro.altoMarcoCrono;
	xRestaurar=otro.xRestaurar; yRestaurar=otro.yRestaurar; anchoRestaurar=otro.anchoRestaurar; altoRestaurar=otro.altoRestaurar; anchoMarcoRestaurar=otro.anchoMarcoRestaurar; altoMarcoRestaurar=otro.altoMarcoRestaurar;

	if(otro.ruta){
		ruta=new(nothrow)char[strlen(otro.ruta)+1];
		if(!ruta){cerr<<"Error el la reserva de memoria 1 de la clase botones\n";exit(1);}
		strcpy(ruta,otro.ruta);
	}
	
	else ruta=0;
	
	tamFuente=otro.tamFuente;
	tiempo=otro.tiempo;
	tTranscurrido=otro.tTranscurrido;
	
	if(ruta) font=CargarFuente(ruta,tamFuente);
	else font=0;
	
	for(int i=0;i<3;i++){
		colorFondo[i]=otro.colorFondo[i];
		colorMarco[i]=otro.colorMarco[i];
		
		colorFondoTiempo[i]=otro.colorFondoTiempo[i];
		colorMarcoTiempo[i]=otro.colorMarcoTiempo[i];
		
		colorFondoStop[i]=otro.colorFondoStop[i];
		colorMarcoStop[i]=otro.colorMarcoStop[i];
		
		colorFondoCrono[i]=otro.colorFondoCrono[i];
		colorMarcoCrono[i]=otro.colorMarcoCrono[i];
		
		colorFondoRestaurar[i]=otro.colorFondoRestaurar[i];
		colorMarcoRestaurar[i]=otro.colorMarcoRestaurar[i];
		
		colorFuente[i]=otro.colorFuente[i];
		colorCrono[i]=otro.colorCrono[i];
	}
}

void botones::liberarMemoria(){
	if(ruta) delete[] ruta;
	if(font) LiberarFuente(font);
}
