#include <iostream>
#include <cstdlib>
#include <vector>
#include <queue>
#include "player.h"
#include "environment.h"

using namespace std;

const double masinf=9999999999.0, menosinf=-9999999999.0;


// Constructor
Player::Player(int jug){
    jugador_=jug;
}

// Actualiza el estado del juego para el jugador
void Player::Perceive(const Environment & env){
    actual_=env;
}

/*double Puntuacion(int jugador, const Environment &estado){
    double suma=0;

    for (int i=0; i<7; i++)
      for (int j=0; j<7; j++){
         if (estado.See_Casilla(i,j)==jugador){
            if (j<3)
               suma += j;
            else
               suma += (6-j);
         }
      }

    return suma;
}


// Funcion de valoracion para testear Poda Alfabeta
double ValoracionTest(const Environment &estado, int jugador){
    int ganador = estado.RevisarTablero();

    if (ganador==jugador)
       return 99999999.0; // Gana el jugador que pide la valoracion
    else if (ganador!=0)
            return -99999999.0; // Pierde el jugador que pide la valoracion
    else if (estado.Get_Casillas_Libres()==0)
            return 0;  // Hay un empate global y se ha rellenado completamente el tablero
    else
          return Puntuacion(jugador,estado);
}
*/
// ------------------- Los tres metodos anteriores no se pueden modificar


// Funcion heuristica (ESTA ES LA QUE TENEIS QUE MODIFICAR)

double Heuristica(int jugador, const Environment &estado){
  double suma=0;
  char contrario=2;
  if (jugador==2) contrario=1;
  int contador_c=0;
  int contador_j=0;

  for (int i=0; i<7; i++){
    for (int j=0; j<7; j++){
      if(estado.See_Casilla(i,j)==contrario){
        contador_c++;
      }
      if (estado.See_Casilla(i,j)==jugador){
        contador_j++;
      }
    }
  }
  suma+=contador_c-contador_j;

  for (int i=0;i<7;++i){
    for (int j=0;j<7;++j){
      if (estado.See_Casilla(i,j)==jugador){
        if(j==3){suma-=1;}
        if(j==2 || j==4){suma-=(double)0.5;}
      }
      if (estado.See_Casilla(i,j)==contrario){
        if(j==3){suma+=1;}
        if(j==2 || j==4){suma+=(double)0.5;}
      }
    }
  }


  return suma;
}


double Valoracion(const Environment &estado, int jugador){
  int ganador = estado.RevisarTablero();

  if (ganador==jugador)
     return 99999999.0; // Gana el jugador que pide la valoracion
  else if (ganador!=0)
          return -99999999.0; // Pierde el jugador que pide la valoracion
  else if (estado.Get_Casillas_Libres()==0)
          return 0;  // Hay un empate global y se ha rellenado completamente el tablero
  else
        return Heuristica(jugador,estado);
}


// Esta funcion no se puede usar en la version entregable
// Aparece aqui solo para ILUSTRAR el comportamiento del juego
// ESTO NO IMPLEMENTA NI MINIMAX, NI PODA ALFABETA
/*void JuegoAleatorio(bool aplicables[], int opciones[], int &j){
    j=0;
    for (int i=0; i<8; i++){
        if (aplicables[i]){
           opciones[j]=i;
           j++;
        }
    }
}*/



Environment::ActionType toActionType(int x){
  Environment::ActionType accion;
  switch(x){
    case 0:
      accion=Environment::ActionType::PUT1;
      break;
    case 1:
      accion=Environment::ActionType::PUT2;
      break;
    case 2:
      accion=Environment::ActionType::PUT3;
      break;
    case 3:
      accion=Environment::ActionType::PUT4;
      break;
    case 4:
      accion=Environment::ActionType::PUT5;
      break;
    case 5:
      accion=Environment::ActionType::PUT6;
      break;
    case 6:
      accion=Environment::ActionType::PUT7;
      break;
    case 7:
      accion=Environment::ActionType::BOOM;
      break;
  }
  return accion;
}




//apuntes clase practica 24/5/19:
//obtener numero de nodos terminales

/*int n_terminales(const Environment &t, int prof, int limite){
  if(t.JuegoTerminado() || prof==limite){
    return 1;
  }
  Environment v[8];
  int n_hijos=t.GenerateAllMoves(v);
  int suma=0;
  for(int i=0;i<n_hijos;i++){
    suma+=n_terminales(v[i],prof+1,limite);
  }
  return suma;
}*/

//obtener valor maximo de un nodo terminal
/*double maxnodos(const Environment &t, int prof, int limite, int jugador){
  if(t.JuegoTerminado() || prof==limite){
    return ValoracionTest(t,jugador);
  }
  Environment v[8];
  int n_hijos=t.GenerateAllMoves(v);
  double maximo=menosinf;
  for(int i=0;i<n_hijos;i++){
    double aux=maxnodos(v[i],prof+1,limite,jugador);
    if (aux>maximo)
      maximo=aux;
  }
  return maximo;
}*/


//-------------------------------------------

double poda_alfa_beta(const Environment &t, int prof, int limite, int jugador,int &accion,double alfa, double beta){
  if(t.JuegoTerminado() || prof==limite){
    double valor=Valoracion(t,jugador);
    if(valor==99999999.0) valor-=prof;
    if(valor==-99999999.0) valor+=prof;
    return valor;
  }
  int act=-1;
  Environment hijo=t.GenerateNextMove(act);
  //double valor;
  while(act<8){
    //la accion kk no la queremos ya que solo necesitamos la accion de la raiz (accion a realizar)
    int kk;
    double aux=poda_alfa_beta(hijo,prof+1,limite,jugador, kk , alfa, beta);
    if (prof%2==0){
      if(aux>alfa)   {alfa=aux;  accion=act;}
      if(alfa>=beta) {return beta;}
    }
    if (prof%2==1){
      if(aux<beta)   {beta=aux;  accion=act;}
      if(beta<=alfa) {return alfa;}
    }
    if(prof==0) cout << "Disponible : " << hijo.ActionStr(toActionType(act)) << " con valor " <<
                aux/*<<"\t\tmaximo: "<<maximo << "\tminimo: " << minimo */<< endl;
    hijo=t.GenerateNextMove(act);

  }
  if (prof%2==0)  return alfa;
  if (prof%2==1)  return beta;
}


// Invoca el siguiente movimiento del jugador
Environment::ActionType Player::Think(){
    const int PROFUNDIDAD_MINIMAX = 6;  // Umbral maximo de profundidad para el metodo MiniMax
    const int PROFUNDIDAD_ALFABETA =8; // Umbral maximo de profundidad para la poda Alfa_Beta

    int accion; // acci�n que se va a devolver
    bool aplicables[8]; // Vector bool usado para obtener las acciones que son aplicables en el estado actual. La interpretacion es
                        // aplicables[0]==true si PUT1 es aplicable
                        // aplicables[1]==true si PUT2 es aplicable
                        // aplicables[2]==true si PUT3 es aplicable
                        // aplicables[3]==true si PUT4 es aplicable
                        // aplicables[4]==true si PUT5 es aplicable
                        // aplicables[5]==true si PUT6 es aplicable
                        // aplicables[6]==true si PUT7 es aplicable
                        // aplicables[7]==true si BOOM es aplicable



    double valor; // Almacena el valor con el que se etiqueta el estado tras el proceso de busqueda.
    double alfa, beta; // Cotas de la poda AlfaBeta

    int n_act; //Acciones posibles en el estado actual


    n_act = actual_.possible_actions(aplicables); // Obtengo las acciones aplicables al estado actual en "aplicables"
    int opciones[10];

    // Muestra por la consola las acciones aplicable para el jugador activo
    //actual_.PintaTablero();
    cout << "\nAcciones aplicables ";
    (jugador_==1) ? cout << "Verde: " : cout << "Azul: ";
    for (int t=0; t<8; t++)
      if (aplicables[t])
         cout << " " << actual_.ActionStr( static_cast< Environment::ActionType > (t)  );
    cout << endl;

    //--------------------- AQUI EMPIEZA LA PARTE A REALIZAR POR EL ALUMNO ------------------------------------------------

    // Opcion: Poda AlfaBeta
    // NOTA: La parametrizacion es solo orientativa
    cout << "\n";
    alfa=menosinf;
    beta=masinf;

    valor = poda_alfa_beta(actual_, 0, PROFUNDIDAD_ALFABETA,jugador_, accion,alfa,beta);
    cout << "Valor minimax: " << valor << "  Accion: " << actual_.ActionStr(toActionType(accion)) << endl;

    return toActionType(accion);
}
