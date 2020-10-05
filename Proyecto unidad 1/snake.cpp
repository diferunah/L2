#include<iostream>
#include<windows.h>
#include<conio.h>
#include<stdlib.h>
#include<time.h>

using namespace std;

#define ARRIBA 72
#define IZQUIERDA 75
#define ABAJO 80
#define DERECHA 77
#define ESC 27

int Puntos;
int cuerpo[200][2];
int n=1;
int tam = 3;
int x=10, y=12;
int dir=3;
int xc=30, yc=20;
int xxc= 40, yyc=18;
int d;
int dif;
double tiempo;

void inicializarArreglo() 
{
	for(int i = 0; i < 200; i++) {
		// inicializa los valores de cuerpo
		cuerpo[i][0]= 0;
		cuerpo[i][1] = 0;
	}
}

void dificultad() 
{
	cout<<"Snake \n elija una dificultad para alterar la velocidad \n 1: facil \n 2: media"<<endl;
	cin>>d;
	switch(d){
		case 1:
			dif=80;
			break;
		case 2:
		    dif=60;
			break;	
	}
	system("cls");
}

void gotoxySnake(int x,int y)
{
	HANDLE hCon;
	hCon=GetStdHandle(STD_OUTPUT_HANDLE);
	
	COORD dwPos;
	dwPos.X=x;
	dwPos.Y=y;
	
	SetConsoleCursorPosition(hCon,dwPos);
}

void pintar()
{
	for(int i=2; i<78;i++){
		gotoxySnake(i,3);cout<<(char)205;
		gotoxySnake(i,23);cout<<(char)205;	
	}
	for(int i=4;i<23;i++){
		gotoxySnake(2,i); cout<<(char)186;
		gotoxySnake(77,i); cout<<(char)186;
	}
	gotoxySnake(2,3);cout<<(char)201;
	gotoxySnake(2,23);cout<<(char)200;
	gotoxySnake(77,3);cout<<(char)187;
	gotoxySnake(77,23);cout<<(char)188;
	
}

void dibujarcuerpo()
{
	for(int i=1; i<tam;i++){
		gotoxySnake(cuerpo[i][0],cuerpo[i][1]); cout<<"O";
	}
}

void guardarposicion()
{
	cuerpo[n][0]=x;
	cuerpo[n][1]=y;
	n++;
	if (n==tam){n=1;}
	dibujarcuerpo();
}


void borrarcuerpo()
{
		gotoxySnake(cuerpo[n][0],cuerpo[n][1]); cout<<" ";
		guardarposicion();
	}

void Teclear(char &tecla)
{
	if (kbhit()){
		tecla=getch();
		switch(tecla){
			case ARRIBA:
			if (dir !=2){dir=1;}
			break;
			case ABAJO:
			if(dir != 1 ){dir=2;}
			break;
			case IZQUIERDA:
			if (dir != 3){dir=4;}
			break;
			case DERECHA:
			if (dir != 4){dir=3;}
			break;	
		}
	}

}

void comida()
{
	if (x==xc && y==yc) {
		srand((unsigned)time(NULL));
		xc=(rand()% 73)+4;
		srand((unsigned)time(NULL));
		yc=(rand()% 19)+4;
		tam++;
		gotoxySnake(xc,yc); cout<<(char)4;
		Puntos++;
		gotoxySnake(50,2);cout<<Puntos;
	}
	
}

bool gameover() 
{
	if (y==3 || y== 23 || x==2 || x==77){return false; }
	for (int j=tam-1; j>0;j--){
		if(cuerpo[j][0]==x && cuerpo [j][1]==y) {return false; }
	}
	return true;
}

void puntosx()
{
	tiempo=tiempo+0.05;
	int tiempo2=tiempo;
	gotoxySnake(35,2);cout<<tiempo;
	if (x==xxc && y== yyc){
		srand((unsigned)time(NULL));
		xxc=(rand()%73)+4;
		srand((unsigned)time(NULL));
		yyc=(rand()%19)+4;
		Puntos=Puntos+5;
        gotoxySnake(50,2);cout<<Puntos;
	}
	if (tiempo2 %10==0){
	    gotoxySnake(xxc,yyc); cout<<(char)6;	
	} else if (tiempo2 %15==0){
		gotoxySnake(xxc,yyc); cout<<" ";
		srand((unsigned)time(NULL));
		xxc=(rand()%73)+4;
		srand((unsigned)time(NULL));
		yyc=(rand()%19)+4;
	}
} 

void proceso(char &tecla, int &puntos)
{ 
	Puntos = puntos;
	borrarcuerpo();
	comida();
	puntosx();
	Teclear(tecla);
	Teclear(tecla);
	if (dir==1){y--;}
	if (dir==2){y++;}
	if (dir==3){x++;}
	if (dir==4){x--;}
	Sleep(dif);
}


int snake()
{
	char tecla;
	int puntos=0;
	int xPos=30, yPos=20;
	
	inicializarArreglo();
	dificultad();	
	gotoxySnake(50,2);
	cout << puntos;
	pintar();
	gotoxySnake(xPos, yPos);
        cout<<(char)4;	
	
	while(tecla != 27 && gameover() ){
	    proceso(tecla, puntos);
	}
	
	if ( !gameover()){
		MessageBox(NULL,"Has perdido","Perdedor", MB_OK);
		system("cls");
	}
	
	system("pause>NULL");
	return 0;
}