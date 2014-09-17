#include"pregunta.h"

pregunta::pregunta(){
	nombre=valor=enunciado=0;
}
		
pregunta::pregunta(const pregunta& otro){
	copiar(otro);
}

pregunta& pregunta::operator=(const pregunta& otro){
	if(this!=&otro){
		liberarMemoria();
		copiar(otro);	
	}
	return *this;
}
		
pregunta::~pregunta(){
	liberarMemoria();
}

bool pregunta::operator==(const pregunta& otro){
	bool iguales=false;
	if(!strcmp(nombre,otro.nombre) && !strcmp(valor,otro.valor) && !strcmp(enunciado,otro.enunciado))
		iguales=true;
	return iguales;
}
bool pregunta::operator!=(const pregunta& otro){
	return !(*this==otro);
}

char* pregunta::getNombre(){
	return nombre;
}

char* pregunta::getValor(){
	return valor;
}
		
char* pregunta::getEnunciado(){
	return enunciado;	
}	

void pregunta::set(rasgo otro, int n){
		
	nombre= new(nothrow) char[strlen(otro.getNombre())+1];
	if(!nombre){cerr<<"Error en la reserva de memoria 1 de la clase pregunta\n";exit(1);}
	strcpy(nombre,otro.getNombre());

	valor= new(nothrow) char[strlen(otro.getValores(n))+1];
	if(!valor){cerr<<"Error en la reserva de memoria 2 de la clase pregunta\n";exit(1);}
	strcpy(valor,otro.getValores(n));
	
	//Si la pregunta es del tipo si/no PE ¿Tiene barba?, simplemente copiamos el patron de la misma como enunciado
	if(Buscar('*',1,otro.getPatron())==-1){
		enunciado=new(nothrow) char[strlen(otro.getPatron())+1];
		if(!enunciado){cerr<<"Error en la reserva de memoria 3.1 de la clase pregunta\n";exit(1);}
		strcpy(enunciado,otro.getPatron());
	}

	//Si la pregunta es del tipo ¿Tiene el pelo *?, es decir tiene * en su patrón
		else{
		int tamano=strlen(otro.getPatron())+strlen(otro.getValores(n));
		enunciado=new(nothrow) char[tamano];
		if(!enunciado){cerr<<"Error en la reserva de memoria 3.2 de la clase pregunta\n";exit(1);}
		int i;
		//La copiamos tal cual hasta el caracter *
		for(i=0;i<Buscar('*',1,otro.getPatron());i++)
			enunciado[i]=otro.getPatron()[i];
		int k=i+1;
		//Luego en la pos del caracter * ponemos el valor que corresponda. PE: negro, rubio, marrón...
		for(int j=0;j<strlen(otro.getValores(n));j++,i++)
			enunciado[i]=otro.getValores(n)[j];
		//Completamos la pregunta con lo que habia despues del *
		for(;i<tamano;k++,i++)
			enunciado[i]=otro.getPatron()[k];
	}
}

ostream& operator <<(ostream& out, const pregunta& otro){
	out<<otro.enunciado<<endl;
	
	return out;	
}

void pregunta::copiar(const pregunta& otro){
	nombre= new(nothrow) char[strlen(otro.nombre)+1];
	if(!nombre){cerr<<"Error en la reserva de memoria 1 de la clase pregunta\n";exit(1);}
	strcpy(nombre,otro.nombre);
	
	valor= new(nothrow) char[strlen(otro.valor)+1];
	if(!valor){cerr<<"Error en la reserva de memoria 2 de la clase pregunta\n";exit(1);}
	strcpy(valor,otro.valor);	
	
	enunciado= new(nothrow) char[strlen(otro.enunciado)+1];
	if(!enunciado){cerr<<"Error en la reserva de memoria 2 de la clase pregunta\n";exit(1);}
	strcpy(enunciado,otro.enunciado);	strcpy(enunciado,otro.enunciado);
}

void pregunta::liberarMemoria(){
	if(nombre)
		delete[] nombre;
	if(valor)
		delete[] valor;
	if(enunciado)
		delete[] enunciado;	
}
