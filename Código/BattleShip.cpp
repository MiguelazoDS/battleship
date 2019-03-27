/* 
   Primer Parcial de Algoritmos y Estructuras de Datos
   
   Integrantes: 
		       	Cazajous  Miguel 
				Sosa Ludueña Gabriel 
				Tacconi Nicolas
				Molinero Martin

   
   La Estrategia que utilizamos para desarrollar el tema es:
      Validar ubicacion de los barcos para que esten separados de agua.
      Rodear de disparos un barco hundido para minimizar disparos.
      Verificar los limites del tablero antes de crear las colas.
      Verificar si hay disparos realizados antes de crear las colas.

*/
#include<iostream>
#include<string.h>
#include <cstdlib>
#include<stdlib.h>
#include<stdio.h>
#define MAX 10

char T[MAX][MAX];// Tablero

using namespace std;

typedef int tipolista;

class Barco{
    private: 
        int PB[4][2];//Posiciones
        string I;//Indicador que señala el tipo de barco
        Barco *next;
    public:
        Barco();
        Barco(int, string);
        string get_I(){return I;};
        void set_I(string nI){I=nI;};
        void set_next(Barco *n) {next=n; };
        void set_PB(int fi, int co){PB[0][0]=fi; PB[0][1]=co;};
        Barco *get_next() {return next; };
        bool es_vacio() {return next==NULL;}
        void marcar(int l);
        void mostrar();
        void verif_hov(char*);
        void verif_pos(int*, int*, int*, char*);
        bool validacion(int,int,int,char);
        void posicionar(int, char='H');
        
};

Barco:: Barco()
{
   next=NULL;
}
Barco:: Barco(int l, string TB)
{
   char HoV;
   for(int i=0; i<4; i++){
   for(int j=0;j<2;j++){PB[i][j]=99;}}
   I=TB;
   if(I!="SUBMARINO")
   {
      cout<<"Indique H para posicionar el "<<I<<"\nhorizontalmente o V para posicionarlo verticalmente: ";
      cin>>HoV; verif_hov(&HoV);
      cout<<"Indique la posicion (fila y columna) del "<<I<<" : "<<endl;
	  posicionar(l, HoV); 
   }
   
   else
   {
      cout<<"Indique la posicion (fila y columna) del "<<I<<" : "<<endl;
	  posicionar(l, HoV); 
   }
   marcar(l);
}

void Barco::verif_hov(char *hov)
{
	if(*hov=='s' || *hov=='S'){exit(1);}
	while(*hov != 'V' && *hov!='v' && *hov!='H' && *hov !='h')
			{
				cout<<"\n\nError el caracter es incorrecto. Vuelva a intentarlo\n";
				cin>>hov;
			}
}
void Barco::verif_pos(int *f, int *c, int *l, char *hov)
{
	bool posicion=false;
	posicion=validacion(*f,*c,*l,*hov);
	while(posicion)
	{
		cout<<"\nVuelva a intentarlo :\n";
		cout<<"Fila: "; cin>>*f; cout<<"Columna: "; cin>>*c;
		posicion=validacion(*f,*c,*l,*hov);
	}
	
	set_PB(*f,*c);
}

/*
   Validacion( ) : Este metodo verifica que el barco este posicionado dentro de 
                   los limites del tablero y que cumpla la consigna de estar 
                   rodeado de agua.  No admite dos barcos juntos.

*/

bool Barco::validacion(int x, int y, int L, char o)
{
     bool valid=true, vert=true, horiz=true, alred = false, superp=true;

     if(o=='v'|| o=='V')
     {    horiz=false;
          for(int i=0;i<L;i++)
               { 
                    if(y-1>=0){if(T[x+i][y-1] != '~') alred=true;}
                    if(y+1<10){if(T[x+i][y+1] != '~') alred=true;}
                    if(x-1>=0){if(T[x-1][y] != '~') alred=true;}                                    
                    if(x+L<10){if(T[x+L][y] != '~') alred=true;} 
                    if(x-1>=0&&y-1>=0){if(T[x-1][y-1] != '~') alred=true;}
                    if(x-1>=0&&y+1<10){if(T[x-1][y+1] != '~') alred=true;}
                    if(x+L<10&&y-1>=0){if(T[x+L][y-1] != '~') alred=true;}
                    if(x+L<10&&y+1<10){if(T[x+L][y+1] != '~') alred=true;}                                                                                                                                               
               }                            
     }
     else
     {
          vert=false;
          for(int i=0;i<L;i++)
               {
                    if(x-1>=0){if(T[x-1][y+i] != '~') alred=true;}                                    
                    if(x+1<10){if(T[x+1][y+i] != '~') alred=true;}  
                    if(y-1>=0){if(T[x][y-1] != '~') alred=true;}                                 
                    if(y+L<10){if(T[x][y+L] != '~') alred=true;}
                    if(x-1>=0&&y-1>=0){if(T[x-1][y-1] != '~') alred=true;}
                    if(x+1<10&&y-1>=0){if(T[x+1][y+1] != '~') alred=true;}
                    if(x-1>=0&&y+L<10){if(T[x-1][y+L] != '~') alred=true;}
                    if(x+1<10&&y+L<10){if(T[x+1][y+L] != '~') alred=true;}                                                  
               }
     }
     
               if(T[x][y]!='~')
               ;
               else
               superp=false;
                                          
     if(x>9||x<0||y>9||y<0||x-1+L>9&&vert||y-1+L>9&&horiz||alred||superp)
     {
          cout<<"\nNo se permiten coordenadas negativas ni mayores a 9, verifique que el lugar no este ocupado" 
              <<"\ny asegurese de que la unidad dispone de espacio para ubicarse"<<endl;          
     }       
     else
     valid=false;
     
     return valid;     
}

void Barco:: posicionar(int l, char HoV)
{
	int C=0; int F=0;
	for(int i =0; i<l; i ++)
      {
         for(int j=0; j<2; j++)
         {
            if(j==0 && i==0)
            {
               cout<<"Fila: ";
               cin>>F;
               PB[i][j]=F;
            }
            if(j==1 && i==0)
            {
                cout<<"Columna: ";
                cin>>C;
				verif_pos(&F,&C,&l,&HoV);
                PB[i][j]=C;
            }
			if(j==1 && i>0 && (HoV=='H' || HoV=='h'))
			{
				C++;
				PB[i][j]=C;
			}
			if(j==1 && i>0 && (HoV=='V' || HoV=='v'))
			{
				PB[i][j]=C;
			}
			if(j==0 && i>0 && (HoV=='H' || HoV=='h'))
			{
				PB[i][j]=F;
			}
			if(j==0 && i>0 && (HoV=='V' || HoV=='v'))
			{
				F++;
				PB[i][j]=F;
			}
         }
      }
}

void Barco:: marcar(int l)
{
    for(int i=0; i<l; i++)
    {
       for(int j=0; j<2; j++)
       {
          T[PB[i][j]][PB[i][j+1]]='x';
          break;
       }
    }
}

void Barco::mostrar()
{
	cout<<"Barco "<<I<<" en las posiciones ";
	for(int i=0; i<4; i++)
	for(int j=0;j<2;j++){
				if(PB[i][j]!=99){cout<<" ("<<PB[i][j]<<", "<<PB[i][j+1]<<")"; break;}}
	cout<<"\n\n";
}

class List{
    private: Barco *czo;
    public:
            List() {czo=new Barco();};
            List(Barco *n) {czo=n;};
            //~Lista(void);
            void add(int l, string TB);
            bool esvacia(void);
            string cabeza(void);
            List *resto(void);  
            void del(void);
            void mostrar_barcos();
};

void List::add(int l, string TB)
{  
     Barco *nuevo=new Barco(l, TB);
     nuevo->set_next(czo);
     czo=nuevo;
}
bool List::esvacia(void)
{   
    return czo->es_vacio();
}

string List::cabeza(void)
{ 
  if(esvacia()){
                cout<<" Error, Cabeza de lista vacia";
                return ""; 
  }
  return czo->get_I();
}

void List::del(void)
{
     Barco * aux;
     aux= czo;
     czo=czo->get_next();
     delete aux;
}

List *List::resto(void)
{ 
      List *l=new List(czo->get_next());
      return (l);
}

void List::mostrar_barcos()
{
	Barco *aux=new Barco();
	aux=czo;
	while(aux->es_vacio()==false)
	{
		aux->mostrar();
		aux=aux->get_next();
	}
}

//Nodo que utiliza la clase Lista del tipo Cola
class Nodo{
    protected: 
		int f;
		int c;
        tipolista dato[2];
        Nodo *next;
    public:
        Nodo() {next=NULL;};
        Nodo(int a, int b) {f=a; c=b; next=NULL;};
        void set_fc(int a, int b) {f=a; c=b; };
        void set_next(Nodo *n) {next=n; };
        tipolista get_dato() {return dato[2]; };
        int get_f(){return f;};
        int get_c(){return c;};
        void set_dato();
        Nodo *get_next() {return next; };
        bool es_vacio() {return next==NULL;};
        void mostrar(int=0);
        int prox_df();
        
        
};

void Nodo:: set_dato()
{
	dato[0]=f;
	dato[1]=c;
	
}

void Nodo:: mostrar(int m)
{
	if(m==0){
	cout<<"("<<f<<", ";
	cout<<c<<") ";}
}

class Lista{
    protected: Nodo *czo;
    public:
            Lista() {czo=new Nodo();};
            Lista(Nodo *n) {czo=n;};
            void del(void);
            void add(int, int);
            bool esvacia(void);
            tipolista cabeza(void);
            Lista *resto(void);
            Nodo *get_czo(void){return czo;}
            void mostrar(){czo->mostrar();};
};

void Lista::del(void)
{    Nodo *aux;
     aux=czo;
     czo=czo->get_next();
     delete aux;
}
void Lista::add(int a, int b)
{  
     Nodo *nuevo=new Nodo(a,b);
     nuevo->set_dato();
     nuevo->set_next(czo);
     czo=nuevo;
}
bool Lista::esvacia(void)
{   
    return czo->es_vacio();
}

tipolista Lista::cabeza(void)
{ 
  if(esvacia()){
                cout<<" Error, Cabeza de lista vacia";
                return -1; 
  }
  return czo->get_dato();
}

Lista *Lista::resto(void)
{ 
      Lista *l=new Lista(czo->get_next());
      return (l);
}

//------------------------------------------------------------------------

class Cola{
      private:
              Lista *l;
              Nodo *czoq;
              void update_start(Lista *l,Nodo *p);
              void do_desencolar(Nodo *p,Nodo *s);
      public:
      Cola(void){l=new Lista();update_start(l,NULL);};
      ~Cola(void) {delete(l);};
      int tope();
      int colavacia() { return l->esvacia();};
      void encolar(int, int) ;
      void desencolar();
      void mostrar();
      int prox_d(int=0);
};
int Cola::tope() {
           if (colavacia()){
              cout<<"Error: Cola vacia"<<endl;
              return -1;
           } 
           else
              return czoq->get_dato();
}

void Cola::encolar(int a, int b) {
     l->add(a,b);
     if (czoq==NULL) {
        update_start(l,czoq);
     }
}

void Cola::desencolar() {
           if (colavacia())
              cout<<"Error: Cola vacia"<<endl;
           else {
              do_desencolar(l->get_czo(),NULL);
              update_start(l,NULL);
           }
}

void Cola::do_desencolar(Nodo *p,Nodo *s){
     if (p->get_next()==NULL) {
         if (s!=NULL) {
            s->set_next(NULL);
         }
         delete(p);
     }else {
         this->do_desencolar(p->get_next(),p);
     }
}
void Cola::update_start(Lista *l,Nodo *p){
     if (l->esvacia()) {
          czoq=p;
     }else {
          this->update_start(l->resto(),l->get_czo());
     }
}

void Cola:: mostrar()
{
	l->mostrar();
}

int Cola:: prox_d(int l)
{
	if(l==0){
	return czoq->get_f();}
	else{return czoq->get_c();}
}

// Nodo que utiliza la clase Pila
class NodoP{
    protected: 
        Cola *P;
        NodoP *next;
    public:
        NodoP() {next=NULL;};
        NodoP(Cola *a) {P=a; next=NULL;};
        void set_dato(Cola *a) {P=a; };
        void set_next(NodoP *n) {next=n; };
        Cola *get_dato() {return P; };
        NodoP *get_next() {return next; };
        bool es_vacio() {return next==NULL;}
};

class Pila{
    protected: NodoP *czo;
    public:
            Pila() {czo=new NodoP();};
            Pila(NodoP *n) {czo=n;};
            void del(void);
            void add(Cola *d);
            bool esvacia(void);
            Cola *cabeza(void);
            void borrar_todo();
		};
void Pila::del(void)
{    NodoP *aux;
     aux=czo;
     czo=czo->get_next();
     delete aux;
}
void Pila::add(Cola *d)
{  
     NodoP *nuevo=new NodoP(d);
     nuevo->set_next(czo);
     czo=nuevo;
}
bool Pila::esvacia(void)
{   
    return czo->es_vacio();
}

Cola* Pila::cabeza(void)
{ 
  if(esvacia()){
                cout<<" Error, Cabeza de lista vacia";
                czo->es_vacio(); 
  }
  return czo->get_dato();
}

void Pila::borrar_todo()
{
	while(esvacia()==false)
	{
		del();
	}
}

//Funciones del int main()
void Tablero(char TA[][MAX], int t)
{
	if(t==0){
	cout<<"\n";
	cout<<"   0  1  2  3  4  5  6  7  8  9\n";
	for(int i=0; i<MAX; i++)
	{
	    cout<<endl<<i;
		for(int j=0; j<MAX; j++)
	    {
			cout<<"  "<<TA[i][j];
		}
	} cout<<"\n\n";
	}
	if(t==1)
	{
		cout<<"\n";
		cout<<"   0  1  2  3  4  5  6  7  8  9\n";
		for(int i=0; i<MAX; i++)
		{
	    	cout<<endl<<i;
			for(int j=0; j<MAX; j++)
	    	{
				cout<<"  "<<T[i][j];
			}
		}cout<<"\n\n";
	}
	if(t!=0 && t!=1)
	{
		cout<<"\n";
		cout<<"   0  1  2  3  4  5  6  7  8  9\t\t   0  1  2  3  4  5  6  7  8  9\n";
		for(int i=0; i<MAX; i++)
		{
	    	cout<<endl<<i;
			for(int j=0; j<MAX; j++)
	    	{
				cout<<"  "<<TA[i][j];
			}
			
			for(int j=0; j<MAX; j++)
	    	{
				if(j==0){cout<<"\t\t"<<i;}
				cout<<"  "<<T[i][j];
			}
		}cout<<"\n\n";
	}
}

void crear_pila_de_colas(Pila *p, int *dis0, int *dis1)
{
	int aux,i=0;
	Cola *D;
	Cola *I;
	Cola *N;
	Cola *S;
	D=new Cola;
	I=new Cola;
	N=new Cola;
	S=new Cola;
	
		   cout<<"\nLas colas de disparo son:\n\n";
		   aux=*dis1 +1;
		   cout<<"Derecha: ";
           while(aux < 10 && aux>=0 && i<3){
		   D->encolar(*dis0, aux);
		   D->mostrar();
		   aux=aux+1; i++;
		   }
		   
		   aux=*dis1 -1; i=0;
		   cout<<endl;
		   cout<<"Izquierda: ";
		   while(aux>=0 && aux<10 && i<3){
				I->encolar(*dis0,aux);
				I->mostrar();
				aux=aux-1; i++;
		   }
		   cout<<endl;
		   
		   aux=*dis0 -1; i=0;
		   cout<<"Arriba: ";
		   while(aux>=0 && aux<10 && i<3){
		   		N->encolar(aux,*dis1);
		   		N->mostrar();
		   		aux=aux-1; i++;}
		   		cout<<endl;
		   		
		   aux=*dis0 +1; i=0;
		   cout<<"Abajo: ";
		   while(aux<10 && aux>=0 && i<3){
		   		S->encolar(aux,*dis1);
		   		S->mostrar();
		   		aux=aux+1; i++;}
		   		
		   cout<<"\n"<<endl;
		   
		   if(I->colavacia()==false){p->add(I);}
		   if(S->colavacia()==false){p->add(S);}
		   if(D->colavacia()==false){p->add(D);}
		   if(N->colavacia()==false){p->add(N);}
}

bool fin_del_juego(char TA[][MAX])
{
	for(int i=0; i<MAX; i++)
		{
	    	for(int j=0; j<MAX; j++)
	    	{
				if(T[i][j] != TA[i][j]){return false;}
			}
		}
		
		return true;
}

void verif_resp(char *r)
{
	if(*r=='s' || *r=='S'){exit(1);}
	while( *r!='A' && *r!='H' && *r!='V' && *r!='v' && *r!='a' && *r!='h')
	{
		cout<<"\n\n Error caracter incorrecto. Vuelva a intentarlo\n\n";
		cin>>r;
	}
}

void rodear(char TA[][MAX], int arregloX[4], int arregloY[4], int d, int j) // rodea un barco hundido de tiros
{
    if(j<=d){ //Condicion de Corte.
    int dis0=arregloX[j];
    int dis1=arregloY[j];
    
    //Para los costados
	if((dis1+1)<MAX){if((TA[dis0][dis1 +1])=='x'){} else{TA[dis0][dis1 +1]='a';T[dis0][dis1 +1]='a';}}
	if((dis1-1)>=0){if((TA[dis0][dis1 -1])=='x'){}else{TA[dis0][dis1-1]='a'; T[dis0][dis1-1]='a';}}
	if((dis0+1)<MAX){if((TA[dis0+1][dis1])=='x'){}else{TA[dis0+1][dis1]='a'; T[dis0+1][dis1]='a';}}
	if((dis0-1)>=0){if((TA[dis0-1][dis1])=='x'){}else{TA[dis0-1][dis1]='a'; T[dis0-1][dis1]='a';}}
	
	//Rodea la diagonal
	//Para arrbia
	if((dis1+1)<MAX && (dis0+1)<MAX){if((TA[dis0+1][dis1 +1])=='x'){} else{TA[dis0+1][dis1 +1]='a';T[dis0+1][dis1 +1]='a';}}
	if((dis1-1)>=0 && (dis0+1)<MAX){if((TA[dis0+1][dis1 -1])=='x'){}else{TA[dis0+1][dis1-1]='a'; T[dis0+1][dis1-1]='a';}}
	//Para abajo
	if((dis1+1)<MAX && (dis0-1)>=0){if((TA[dis0-1][dis1 +1])=='x'){} else{TA[dis0-1][dis1 +1]='a';T[dis0-1][dis1 +1]='a';}}
	if((dis1-1)>=0 && (dis0-1)>=0){if((TA[dis0-1][dis1 -1])=='x'){}else{TA[dis0-1][dis1-1]='a'; T[dis0-1][dis1-1]='a';}}
	
	rodear(TA,arregloX,arregloY,d,++j);// FORma REcursiva
    }	

}

int main()
{   
    int dis[2]={0};
    int ni=0;//Numero de intentos
    char TA[MAX][MAX];
    char r='a';
    bool fin=false;
    bool flag=false;// Marca cuando se crean la pila de colas
    int i=0, j=0;
    Pila *p;
    p=new Pila;
    
    for(int i=0;i<MAX;i++) 
	for(int j=0;j<MAX;j++){
	T[i][j]='~'; TA[i][j]='~';}

    cout<<"\n\n\t\t     <<<Bienvenido a la Batalla Naval>>>\n\n"<<endl;
    List *l = new List();
    
    
    l->add(4,"DESTRUCTOR4");
    Tablero(TA, 1); // Muestra tablero con posiciones
    l->add(3,"CRUCERO");
    Tablero(TA, 1);
    l->add(3,"CRUCERO");
    Tablero(TA, 1);
    l->add(2,"DESTRUCTOR2");
    Tablero(TA, 1);
    l->add(2,"DESTRUCTOR2");
    Tablero(TA, 1);
    l->add(2,"DESTRUCTOR2");
    Tablero(TA, 1);
    l->add(1,"SUBMARINO");
    Tablero(TA, 1);
    l->add(1,"SUBMARINO");
    Tablero(TA, 1);
    l->add(1,"SUBMARINO");
    Tablero(TA, 1);
    l->add(1,"SUBMARINO");//*/
    
    cout<<"\n\nSus barcos se encuentran en las siguientes posiciones.\n";
    cout<<"Y seran buscados desde un tablero inicial como sigue:\n\n";
    cout<<"\t Tablero inicial\t\t        Tablero a encontrar\n";
	Tablero(TA, 2);//Muestra tablero q usa la PC con tiros realizados =a a la par del tablero a encontrar
	
	while((r!='v'||r!='V') && fin==false && ni<100)
    {            
       int d=0; //contador para el funcion RODEADOR de agua
       int arregloX[5]={99,99,99,99,99}, arregloY[5]={99,99,99,99,99};//arreglos para el funcion RODEADOR de agua, donde se van a guardar los tiros
                        
       dis[i]=rand()%10;
       dis[i+1]=rand()%10;
       //El while proximo verifica que el tiro no se hizo antes
       while(TA[dis[0]][dis[1]] != 'x' && TA[dis[0]][dis[1]] != 'a' && fin==false && ni<100){
       cout<<"Disparo en (fila, columna) ("<<dis[0]<<", "<<dis[1]<<") :"<<endl;
       ni++;
       cin>>r; verif_resp(&r);
       if(r=='v'||r=='V')//Si pasa se crean las Colas
       {
		   flag=true;
		   TA[dis[0]][dis[1]]='x';
		   crear_pila_de_colas(p,&dis[0],&dis[1]);   
		   Tablero(TA,2);
		   arregloX[d]=dis[0];//guardo la posicion del tiro, para el RODEADOR
		   arregloY[d]=dis[1];//guardo la posicion del tiro, para el RODEADOR
		   d++;//incremento el contador del RODEADOR
       }
       
       if(r=='h' ||r=='H')
       {
			TA[dis[0]][dis[1]]='x';
			arregloX[d]=dis[0];//guardo la posicion del tiro, para el RODEADOR
		    arregloY[d]=dis[1];//guardo la posicion del tiro, para el RODEADOR
			rodear(TA,arregloX,arregloY,d,0);
			Tablero(TA,2);
			cout<<"\n      \t\tBarco hundido!!! en la posicion ("<<dis[0]<<", "<<dis[1]<<") \n\n";
	   }
	   
	   if((r=='a'||r=='A') && flag==false)
	   {
			TA[dis[0]][dis[1]]='a';
			T[dis[0]][dis[1]]='a';
			Tablero(TA,2);
			dis[0]=rand()%10;
       		dis[1]=rand()%10;
	   }
	   
	   //Proximos tiros: solo cuando se cree la pila de colas
	   while((r=='v'||r=='V') && p->esvacia()==false && flag==true)
		{                     
			if(p->cabeza()->colavacia()==true)
				{cout<<"\nError cola de tiros vacia.\n"
				<<"Ha indicado incorrectamente la posicion y puede que el numero de intentos no sea el correcto.\n";
				p->del();}
				
			dis[0]=p->cabeza()->prox_d(0);
			dis[1]=p->cabeza()->prox_d(1);
			
			while((TA[dis[0]][dis[1]]=='a'|| TA[dis[0]][dis[1]]=='x')&& (r=='v'||r=='V')){
				p->del();
				dis[0]=p->cabeza()->prox_d(0);
			    dis[1]=p->cabeza()->prox_d(1);
				if(p->cabeza()->colavacia()==true){p->del();}
				if(p->esvacia()==true){r='a';break;}
				}
				
			if((TA[dis[0]][dis[1]]!='a'|| TA[dis[0]][dis[1]]!='x') && (r=='v' || r=='V')){
			cout<<"Disparo en (fila, columna) ("<<dis[0]<<", "<<dis[1]<<"):\n";
			ni++;
			cin>>r; verif_resp(&r);
			if(r=='v' ||r=='V')
			{
				TA[dis[0]][dis[1]]='x';
				Tablero(TA,2);
				p->cabeza()->desencolar();
				arregloX[d]=dis[0];//guardo la posicion del tiro, para el RODEADOR
		        arregloY[d]=dis[1];//guardo la posicion del tiro, para el RODEADOR
		        d++;//incremento el contador del RODEADOR
			}
			if(r=='a' ||r=='A')
			{
				TA[dis[0]][dis[1]]='a';
				T[dis[0]][dis[1]]='a';
				Tablero(TA,2);
				p->del();
				if(p->esvacia()==false){r='v';}
				else{r='a';}
			}
			if(r=='h'||r=='H')
			{
				TA[dis[0]][dis[1]]='x';
				arregloX[d]=dis[0];//guardo la posicion del tiro, para el RODEADOR
		        arregloY[d]=dis[1];//guardo la posicion del tiro, para el RODEADOR
				rodear(TA,arregloX,arregloY,d,0);
				Tablero(TA,2);
				cout<<"\n\tBarco hundido, en las posiciones";
				for(int i=0;i<4;i++){
				if(arregloX[i]!=99 &&arregloY[i]!=99){cout<<" ("<<arregloX[i]<<", "<<arregloY[i]<<")";}}
				cout<<"!!!\n\n";
				p->borrar_todo();
				flag=false;
				r='a';
			}
		}}
		flag=false;
		fin=fin_del_juego(TA);
		}
    }
    cout<<"Se han encontrado sus 10 barcos escondidos en las siguientes posiciones:\n\n";
    l->mostrar_barcos();
    
    
    cout<<"\n\n\t\t    El exito se logro con un total de "<<ni<<" intentos.\n"<<endl;
	cout<<"\n\t\t              <<<Fin del juego>>>\n\n\n";
    
        
    system("pause");
    
   	return EXIT_SUCCESS;
}
