#include"conjuntoPreguntas.h"

conjuntoPreguntas::conjuntoPreguntas (conjuntoRasgos& rasgos){
	tipoFuente=0;
	tam=tamFuente=0;
	ruta=0;	
	rasgo temp;
	for(int i=0; i<rasgos.tamanho();i++){
		temp=rasgos.get(i);
		//Vemos si la pregunta es del tipo Si/No PE: ¿Tiene bigote? o por el contrario es del tipo, ¿Tiene el pelo *?, para ello vemos si en su patron de encuentra el caracter *
		if(Buscar('*',1,temp.getPatron())!=-1)
			tam+=temp.getNValores();
		else
			tam++;
	}
	
	preguntas=new (nothrow) pregunta[tam];
	if(!preguntas){cerr<<"Error en reserva memoria\n";exit(1);}
	
	realizadas=new (nothrow) bool[tam];
	if(!realizadas){cerr<<"Error en reserva memoria\n";exit(1);}
	
	for(int i=0;i<tam;i++)
		realizadas[i]=false;
	
	int nPregunta=0;
	bool fin=false;
	for(int i=0; i<rasgos.tamanho(); i++){
		fin=false;
		temp=rasgos.get(i);
		for(int j=0; j<temp.getNValores() && ! fin;j++){
			preguntas[nPregunta].set(temp,j);
			//Si la pregunta no tiene * en el patron paramos antes el bucle. Ya que solo se genera una PE: ¿Tienes barba?, en el caso contrario se han de generar tantas como número de valores PE: ¿Tiene el pelo negro?, ¿Tiene el pelo rubio?...
			if(Buscar('*',1,temp.getPatron())==-1)
				fin=true;
		nPregunta++;
		}	
	}
}

conjuntoPreguntas::conjuntoPreguntas(const conjuntoPreguntas& otro){
	copiar(otro);
}

conjuntoPreguntas& conjuntoPreguntas::operator=(const conjuntoPreguntas& otro){
	if(this!=&otro){
		liberarMemoria();
		copiar(otro);
	}	
	return *this;
}
conjuntoPreguntas::~conjuntoPreguntas(){
	liberarMemoria();
}
		
int conjuntoPreguntas::tamanho(){
	return tam;	
}
pregunta conjuntoPreguntas::getPregunta(int n){
	return preguntas[n];		
}

pregunta conjuntoPreguntas::getAleatoria(){
	int nPreguntasSinRealizar=0;
	//Primero vemos cuantas preguntas no han sido aún ralizadas.
	for(int i=0; i<tam; i++)
		if(!realizadas[i])
			nPreguntasSinRealizar++;
	
	//Insertamos en un array de enteros el numemro de pregunta de aquellas preguntas que aún no hayan sido formuladas.
	int* posiblesValores=new(nothrow) int[nPreguntasSinRealizar];
	if(!posiblesValores){cerr<<"Error en la reserva de memoria 7 de la clase conjuntoPreguntas\n";exit(1);}
	for(int i=0, j=0; i<tam; i++){
		if(!realizadas[i]){
			posiblesValores[j]=i;
			j++;
		}
	}
	//Generamos un número aleatorio, a partir del array que contine el número de las preguntas aún no realizadas.
	int rand=aleatorio(posiblesValores,nPreguntasSinRealizar);
	realizadas[rand]=true;
	delete[] posiblesValores;
	return preguntas[rand];			
}
		
bool conjuntoPreguntas::responder(personaje& pj, pregunta& realizada){
	int lugar=-1;
	bool fin=false;
	
	//En primer lugar nos aseguramos que el personaje tenga ese rasgo.
	for(int i=0;i<pj.getNRasgos() && !fin;i++){
		if(!strcmp(realizada.getNombre(),pj.getRasgo(i))){
			fin=true;
			lugar=i;	
		}
	}
	char PreguntaRealizada[999], rasgoElegido[999];
	
	//Si lo tiene, respondemos a la pregunta
	if(lugar!=-1)
		return !strcmp(realizada.getValor(),pj.getValor(lugar));
	
	//Sino mostramos un mensaje de error
	else{
		cerr<<"Error, rasgo no encontrado en el personaje\n";
		return 0;
	}
}

void conjuntoPreguntas::dibujar(){
	DesactivarDibujo();
	
	RectanguloR(x, y, x+ancho, y+alto, colorFondo[0], colorFondo[1], colorFondo[2]);
	DibujarMarco(anchoMarco,altoMarco,x,y,x+ancho,y+alto,colorMarco);
	
	int x1=x+anchoMarco+1;
	int y1=y+altoMarco+1;
	
	EscribirTexto(x1,y1,"PREGUNTAS:",tipoFuente,colorFuente[0],colorFuente[1],colorFuente[2]);
	y1+=25;
	char numeros[4];//Aqui albergamos el número de la pregunta.
	int temp1,temp2;
	for(int i=0;i<tam;i++){
		EnteroACadena(numeros,i);
		int tam=strlen(numeros);//pasamos el numero de pregunta a cadena de caracteres.
		numeros[tam]='.';
		numeros[tam+1]='\0';
		//Escribimos el numero de pregunta seguido de un '.'
		EscribirTexto(x1,y1,numeros,tipoFuente,colorFuente[0],colorFuente[1],colorFuente[2]);
		
		TamanoTexto(tipoFuente,numeros,temp1,temp2);
		x1+=temp1;
		
		//Ahora escribimos el enunciado de la pregunta
		EscribirTexto(x1,y1,preguntas[i].getEnunciado(),tipoFuente,colorFuente[0],colorFuente[1],colorFuente[2]);	
		y1+=AltoFuente(tipoFuente)+3;
		x1-=temp1;
	}
	ActivarDibujo();
}
		
istream& operator>>(istream& in, conjuntoPreguntas& otro){
	char buffer[999],buffer1[999],buffer2[999],buffer3[999];
	
	//Leemos del fichero de configuracion todos los datos relativos al conjunto de preguntas.
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
	
	otro.tipoFuente=CargarFuente(otro.ruta, otro.tamFuente);
	
	return in;
}

ostream& operator<<(ostream& out, const conjuntoPreguntas& otro){
	out<<otro.x<<" "<<otro.y<<endl<<otro.ancho<<" "<<otro.alto<<endl;
	for(int i=0;i<3;i++)
		out<<otro.colorFondo[i]<<" ";
	out<<endl<<otro.anchoMarco<<" "<<otro.altoMarco<<endl;
	for(int i=0;i<3;i++)
		out<<otro.colorMarco[i]<<" ";
	out<<endl<<otro.ruta<<endl<<otro.tam<<endl;
	for(int i=0;i<otro.tam;i++)
		out<<i<<"."<<otro.preguntas[i].getEnunciado()<<endl;
	
	return out;
}
	
void conjuntoPreguntas::copiar(const conjuntoPreguntas& otro){
	if(otro.ruta!=0){
		x=otro.x;
		y=otro.y;
		ancho=otro.ancho;
		alto=otro.alto;
	
		for(int i=0;i<3;i++)
			colorFondo[i]=otro.colorFondo[i];
	
		anchoMarco=otro.anchoMarco;
		altoMarco=otro.altoMarco;
	
		for(int i=0;i<3;i++)
			colorMarco[i]=otro.colorMarco[i];
	
		ruta=new(nothrow) char[strlen(otro.ruta)+1];
		if(!ruta){cerr<<"Error en la reserva de memoria 3 de la clase conjuntoPreguntas\n";exit(1);}
		strcpy(ruta,otro.ruta);
	
		tamFuente=otro.tamFuente;
		tipoFuente=CargarFuente(ruta,tamFuente);
			
		for(int i=0;i<3;i++)
			colorFuente[i]=otro.colorFuente[i];
	
		tam=otro.tam;
			
		preguntas=new(nothrow) pregunta[tam];
		if(!preguntas){cerr<<"Error en la reserva de memoria 4 de la clase conjuntoPreguntas\n";exit(1);}
		for(int i=0;i<tam;i++)
			preguntas[i]=otro.preguntas[i];
	
		realizadas = new(nothrow) bool[tam];
		if(!realizadas){cerr<<"Error en la reserva de memoria 5 de la clase conjuntoPreguntas\n";exit(1);}
		for(int i=0;i<tam;i++)
			realizadas[i]=otro.realizadas[i];
	
		}

	else{
		tipoFuente=0;
		tam=tamFuente=0;
		ruta=0;	
		tam=otro.tam;
			
		preguntas=new(nothrow) pregunta[tam];
		if(!preguntas){cerr<<"Error en la reserva de memoria 4 de la clase conjuntoPreguntas\n";exit(1);}
		for(int i=0;i<tam;i++)
			preguntas[i]=otro.preguntas[i];
	
		realizadas = new(nothrow) bool[tam];
		if(!realizadas){cerr<<"Error en la reserva de memoria 5 de la clase conjuntoPreguntas\n";exit(1);}
		for(int i=0;i<tam;i++)
			realizadas[i]=otro.realizadas[i];
	
	}
}

void conjuntoPreguntas::liberarMemoria(){
	delete[] ruta;
	delete[] realizadas;
	delete[] preguntas;
	if(tipoFuente)
		LiberarFuente(tipoFuente);
}	
