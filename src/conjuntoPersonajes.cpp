#include"conjuntoPersonajes.h"

conjuntoPersonajes::conjuntoPersonajes(){
	tam=0;
	datos=0;
}

conjuntoPersonajes::conjuntoPersonajes(const conjuntoPersonajes& otro){
	copiar(otro);
}

conjuntoPersonajes& conjuntoPersonajes::conjuntoPersonajes::operator= (const conjuntoPersonajes& otro){
	if(this!=&otro){
		liberarMemoria();
		copiar(otro);
	}
	return *this;
}

conjuntoPersonajes::~conjuntoPersonajes(){
	liberarMemoria();
}

personaje conjuntoPersonajes::get(int i){
	return datos[i];
}

int conjuntoPersonajes::tamanho(){
	return tam;	
}
		
istream& operator>> (istream& in, conjuntoPersonajes& otro){
	char buffer[999];
	
	//Leemos el tamaño del cjto.
	in.getline(buffer,999);
	otro.tam=atoi(buffer);
	otro.datos=new(nothrow) personaje[otro.tam];
	
	if(!otro.datos){cerr<<"Error en la reserva de memoria 2\n";exit(1);}
	
	//Leemos ahora personaje a personaje
	for(int i=0;i<otro.tam;i++)
			in>>otro.datos[i];
		
	return in;	
}

ostream& operator<< (ostream& out, const conjuntoPersonajes& otro){
	out<<otro.tam<<endl;
	for(int i=0;i<otro.tam;i++)
		out<<otro.datos[i];
	return out;
}
		
void conjuntoPersonajes::crear(int n){
	tam=n;
	datos=new(nothrow) personaje[tam];
	if(!datos){cerr<<"Error en la reserva de memoria 1\n";exit(1);}
}

void conjuntoPersonajes::copiar(const conjuntoPersonajes& otro){
	crear(otro.tam);
	for(int i=0;i<otro.tam;i++)		
		datos[i]=otro.datos[i];
}
			
void conjuntoPersonajes::liberarMemoria(){
	delete[] datos;
}
