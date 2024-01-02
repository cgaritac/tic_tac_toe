//Universidad: UNED
//Curso:       Introducci�n a la programaci�n
//Tema:        Proyecto Final, juego "3 en l�nea"
//Estudiante:  Carlos Garita Campos
//Periodo:     III Cuatrimestre 2019

#include <iostream>
#include <locale>
#include <bits/stdc++.h>
#include <stdlib.h>
#include <fstream>

using namespace std;
using std::cout;
using std::cin;
using std::endl;

//Definici�n de funciones
void encabezado(char[][5]);
void menu();
void imprimirTablero(char[][5]);
void solicitarNombres();
void iniciarPartida();
void sustituir(int , char);
void limpiarTablero();
void guardarArchivo(string[],int[],string);
void leerArchivo();
int leerEntero();
bool pruebaAvance();

// Declaraci�n de variables y asignaci�n de valores
char tablero[5][5]= {'1','|','2','|','3','-','-','-','-','-','4','|','5','|','6','-','-','-','-','-','7','|','8','|','9'};
string jugadores[2];

int main()
{
    // Establece el idioma a espa�ol
    setlocale(LC_CTYPE,"Spanish");

    //Llama a la funci�n encabezado
    encabezado(tablero);

    //Llama a la funci�n menu
    menu();

    return 0;
}

//Funci�n que imprime un encabezado en pantalla
void encabezado(char tablero[][5])
{
    // Se imprime informaci�n del encabezado en pantalla
    cout << "Universidad: Universidad Estatal a Distancia" << endl;
    cout << "Curso:       Introducci�n a la programaci�n" << endl;
    cout << "Tema:        Proyecto Final" << endl;
    cout << "Estudiante:  Carlos Garita Campos" << endl;
    cout << "Periodo:     III Cuatrimestre" << endl;
    cout << "________________________________________________" << endl;
    cout << "\n           Juego 3 en l�nea" << endl;
    cout << "________________________________________________\n" << endl;

    //Llama a la funci�n para imprimir el tablero en pantalla
    imprimirTablero(tablero);
}

//Funci�n que imprime el men� en pantalla
void menu()
{
    cout << "\nMen� de opciones" << endl;
    cout << "1. Iniciar partida" << endl;
    cout << "2. Ver marcadores" << endl;
    cout << "3. Salir" << endl;
    cout << "\nElija la opci�n que desee e introduzca el n�mero correspondiente para continuar:" << endl;

    //Switch para ejecutar la opci�n seleccionada por el usuario que llama a la funci�n leerEntero para el ingreso y validaci�n del n�mero de opci�n
    //seleccionada por el usuario
    switch (leerEntero())
    {
    case 1:
        //Llama a la funci�n solicitarNombres
        solicitarNombres();
        break;
    case 2:
        //Llama a la funci�n leerArchivo
        leerArchivo();
        //Llama a la funci�n menu
        menu();
        break;
    case 3:
        break;
    default:
        cout << "\nOpci�n no v�lida!" << endl;
        //Llama a la funci�n menu
        menu();
        break;
    }
}

//Funci�n para imprimir el tablero en pantalla
void imprimirTablero(char tablero[][5])
{
    //Ciclo que recorre las filas y columnas de la matriz para introducir los respectivos valores num�ricos en la misma
    for (int i = 0; i < 5; i++)
    {
        cout << "              ";

        for (int j = 0; j < 5; j++)
        {
            cout << tablero[i][j] << " ";
        }

        cout << endl;
    }
}

//Funci�n para solicitar los nombres de los jugadores
void solicitarNombres()
{
    cout << "\nIngrese el nombre del jugador que utilizar� la X" << endl;
    cin >> jugadores[0];

    cout << "\nIngrese el nombre del jugador que utilizar� el O" << endl;
    cin >> jugadores[1];

    cout << "\n" << jugadores[0] << " utilizar� la X y " << jugadores[1] << " utilizar� el O\n" << endl;

    cout << "Suerte!, y que gane el mejor!" << endl;
    cout << "________________________________________________\n" << endl;

    //Llama a la funci�n iniciarPartida
    iniciarPartida();
}

//Funci�n para llevar a cabo las diferentes rondas de la partida
void iniciarPartida()
{
    // Declaraci�n de variables y asignaci�n de valores
    int numero = 0, movimiento = 0, ronda = 1;
    int puntaje[2] = {0,0};
    char jugador = ' ';
    string resultado = "";
    bool ganador[2] = {false, false};

    //Ciclo que se lleva a cabo hasta que se cumpla con las 4 rondas que se juegan en cada partida entre ambos jugadores
    do
    {
        cout << "        ********** RONDA " << ronda <<" **********" << endl;

        //Llama a la funci�n imprimir tablero
        imprimirTablero(tablero);

        //Ciclo que se ejecuta hasta que alguno de los jugadores gane o se llene por completo el tablero sin un ganador
        do
        {
            cout << "\n" << jugadores[0] << " seleccione el n�mero del tablero en donde desea colocar la X" << endl;
            numero = leerEntero(); //Llama a la funci�n leerEntero y asigna su valor a la variable numero

            jugador = 'A'; //asigna el valor "A" a la variable jugador

            sustituir(numero, jugador); //Llama a la funci�n sustituir

            imprimirTablero(tablero); //Llama a la funci�n imprimirTablero

            movimiento++; //suma un 1 al valor de la variable movimiento

            //Condicional para terminar el ciclo en caso de que gane el primer jugador o este complete el tablero
            if (pruebaAvance() || movimiento == 9)
            {
                break;
            }

            cout << "\n" << jugadores[1] << " seleccione el n�mero del tablero en donde desea colocar el O" << endl;
            numero = leerEntero(); //Llama a la funci�n leerEntero y asigna su valor a la variable numero

            jugador = 'B'; //asigna el valor "A" a la variable jugador

            sustituir(numero, jugador); //Llama a la funci�n sustituir

            imprimirTablero(tablero); //Llama a la funci�n imprimirTablero

            movimiento++; //suma un 1 al valor de la variable movimiento

            //Condicional para terminar el ciclo en caso de que gane el segundo jugador
            if (pruebaAvance())
            {
                break;
            }

        }while(movimiento < 9 ); //Condici�n del ciclo do-while

        //Condicional para definir si hubo empate entre ambos jugadores en la ronda correspondiente
        if (movimiento = 9 & pruebaAvance() == false)
        {
            puntaje[0] = puntaje[0] + 2; //Asignaci�n de puntaje al primer jugador por empate
            puntaje[1] = puntaje[1] + 2; //Asignaci�n de puntaje al segundo jugador por empate
            cout << "\nEmpate entre ambos jugadores!, suman 2 puntos cada uno\n" << endl;
        }
        else
        {
            //Condicional para definir si gan� el primer jugador en la ronda correspondiente
            if (jugador == 'A' & pruebaAvance())
            {
                puntaje[0] = puntaje[0] + 5; //Asignaci�n de puntaje al primer jugador por gane
                cout << "\n" << jugadores[0] << " gana la partida!, suma 5 puntos\n" << endl;

            }
            else
            {
                puntaje[1] = puntaje[1] + 5; //Asignaci�n de puntaje al segundo jugador por gane
                cout << "\n" << jugadores[1] << " gana la partida!, suma 5 puntos\n" << endl;
            }
        }

    ronda++; //suma un 1 al valor de la variable ronda

    //Llama a la funci�n limpiarTablero
    limpiarTablero();

    }while(ronda < 5); //Condici�n del ciclo do-while

    cout << "\n        ********** Resultados Finales **********\n" << endl;

    //Condicional para definir si hubo empate entre ambos jugadores al final de las 4 rondas
    if (puntaje[0] == puntaje[1])
    {
        cout << "\nPuntaje final obtenido: " << jugadores[0] << " y " << jugadores[1] << " "<< puntaje[0] << " puntos\n" << endl;
        cout << "\nResultado final: Empate entre ambos jugadores, felicidades a ambos!\n" << endl;
        resultado = "Empate";
        guardarArchivo(jugadores, puntaje, resultado);
    }

    //Condicional para definir si gan� el primer jugador al final de las 4 rondas
    if (puntaje[0] > puntaje[1])
    {
        cout << "\n---- Puntaje final obtenido por " << jugadores[0] << ": " << puntaje[0] << " puntos" << endl;
        cout << "\n---- Puntaje final obtenido por " << jugadores[1] << ": " << puntaje[1] << " puntos\n" << endl;
        cout << "\n---- Resultado final: " << jugadores[0] << " gana la ronda de juegos, felicidades!\n" << endl;
        resultado = "Ganador";
        guardarArchivo(jugadores, puntaje, resultado);
    }

    //Condicional para definir si gan� el segundo jugador al final de las 4 rondas
    if (puntaje[0] < puntaje[1])
    {
        cout << "\nPuntaje final obtenido por " << jugadores[0] << ": " << puntaje[0] << " puntos\n" << endl;
        cout << "\nPuntaje final obtenido por " << jugadores[1] << ": " << puntaje[1] << " puntos\n" << endl;
        cout << "\nResultado final: " << jugadores[1] << " gana la ronda de juegos, felicidades!\n" << endl;
        resultado = "Ganador";
        guardarArchivo(jugadores, puntaje, resultado);
    }

    cout << "\n        ****************************************\n" << endl;

    //Llama a la funci�n menu
    menu();
}

//Funci�n para sustituir la X o el O en el tablero conforme van participando ambos jugadores
void sustituir(int num, char jug)
{
    char marca;

    //Condicional para definir si el valor a sustituir en el tablero en una X o un O
    if (jug == 'A')
    {
        marca = 'X';
    }
    else
    {
        marca = 'O';
    }

    //Switc para sustituir el valor la X o el O en la posici�n correspondiente en el tablero
    switch (num)
    {
    case 1:
        //Condicional para validar que la posici�n seleccionada por el jugador no haya sido seleccionada anteriormente durante
        //la partida que se est� llevando a cabo
        if (tablero[0][0] == 'X' || tablero[0][0] == 'O')
        {
            cout << "Esa posici�n ya fue seleccionada, por favor seleccione otra posici�n" << endl;
            num = leerEntero(); //Llama a la funci�n leerEntero y asigna su valor a la variable num
            sustituir(num,jug); //Llama a la funci�n sustituir nuevamente con el nuevp valor ingresado por el jugador
        }
        else
        {
            tablero[0][0]= marca; //Asigna la X o el O a la posici�n en correspondiente en el tablero
        }
        break;
    case 2:
        //Condicional para validar que la posici�n seleccionada por el jugador no haya sido seleccionada anteriormente durante
        //la partida que se est� llevando a cabo
        if (tablero[0][2] == 'X' || tablero[0][2] == 'O')
        {
            cout << "Esa posici�n ya fue seleccionada, por favor seleccione otra posici�n" << endl;
            num = leerEntero(); //Llama a la funci�n leerEntero y asigna su valor a la variable num
            sustituir(num,jug); //Llama a la funci�n sustituir nuevamente con el nuevp valor ingresado por el jugador
        }
        else
        {
            tablero[0][2]= marca; //Asigna la X o el O a la posici�n en correspondiente en el tablero
        }
        break;
    case 3:
        //Condicional para validar que la posici�n seleccionada por el jugador no haya sido seleccionada anteriormente durante
        //la partida que se est� llevando a cabo
        if (tablero[0][4] == 'X' || tablero[0][4] == 'O')
        {
            cout << "Esa posici�n ya fue seleccionada, por favor seleccione otra posici�n" << endl;
            num = leerEntero(); //Llama a la funci�n leerEntero y asigna su valor a la variable num
            sustituir(num,jug); //Llama a la funci�n sustituir nuevamente con el nuevp valor ingresado por el jugador
        }
        else
        {
            tablero[0][4]= marca; //Asigna la X o el O a la posici�n en correspondiente en el tablero
        }
        break;
    case 4:
        //Condicional para validar que la posici�n seleccionada por el jugador no haya sido seleccionada anteriormente durante
        //la partida que se est� llevando a cabo
        if (tablero[2][0] == 'X' || tablero[2][0] == 'O')
        {
            cout << "Esa posici�n ya fue seleccionada, por favor seleccione otra posici�n" << endl;
            num = leerEntero(); //Llama a la funci�n leerEntero y asigna su valor a la variable num
            sustituir(num,jug); //Llama a la funci�n sustituir nuevamente con el nuevp valor ingresado por el jugador
        }
        else
        {
            tablero[2][0]= marca; //Asigna la X o el O a la posici�n en correspondiente en el tablero
        }
        break;
    case 5:
        //Condicional para validar que la posici�n seleccionada por el jugador no haya sido seleccionada anteriormente durante
        //la partida que se est� llevando a cabo
        if (tablero[2][2] == 'X' || tablero[2][2] == 'O')
        {
            cout << "Esa posici�n ya fue seleccionada, por favor seleccione otra posici�n" << endl;
            num = leerEntero(); //Llama a la funci�n leerEntero y asigna su valor a la variable num
            sustituir(num,jug); //Llama a la funci�n sustituir nuevamente con el nuevp valor ingresado por el jugador
        }
        else
        {
            tablero[2][2]= marca; //Asigna la X o el O a la posici�n en correspondiente en el tablero
        }
        break;
    case 6:
        //Condicional para validar que la posici�n seleccionada por el jugador no haya sido seleccionada anteriormente durante
        //la partida que se est� llevando a cabo
        if (tablero[2][4] == 'X' || tablero[2][4] == 'O')
        {
            cout << "Esa posici�n ya fue seleccionada, por favor seleccione otra posici�n" << endl;
            num = leerEntero(); //Llama a la funci�n leerEntero y asigna su valor a la variable num
            sustituir(num,jug); //Llama a la funci�n sustituir nuevamente con el nuevp valor ingresado por el jugador
        }
        else
        {
            tablero[2][4]= marca; //Asigna la X o el O a la posici�n en correspondiente en el tablero
        }
        break;
    case 7:
        //Condicional para validar que la posici�n seleccionada por el jugador no haya sido seleccionada anteriormente durante
        //la partida que se est� llevando a cabo
        if (tablero[4][0] == 'X' || tablero[4][0] == 'O')
        {
            cout << "Esa posici�n ya fue seleccionada, por favor seleccione otra posici�n" << endl;
            num = leerEntero(); //Llama a la funci�n leerEntero y asigna su valor a la variable num
            sustituir(num,jug); //Llama a la funci�n sustituir nuevamente con el nuevp valor ingresado por el jugador
        }
        else
        {
            tablero[4][0]= marca; //Asigna la X o el O a la posici�n en correspondiente en el tablero
        }
        break;
    case 8:
        //Condicional para validar que la posici�n seleccionada por el jugador no haya sido seleccionada anteriormente durante
        //la partida que se est� llevando a cabo
        if (tablero[4][2] == 'X' || tablero[4][2] == 'O')
        {
            cout << "Esa posici�n ya fue seleccionada, por favor seleccione otra posici�n" << endl;
            num = leerEntero(); //Llama a la funci�n leerEntero y asigna su valor a la variable num
            sustituir(num,jug); //Llama a la funci�n sustituir nuevamente con el nuevp valor ingresado por el jugador
        }
        else
        {
            tablero[4][2]= marca; //Asigna la X o el O a la posici�n en correspondiente en el tablero
        }
        break;
    case 9:
        //Condicional para validar que la posici�n seleccionada por el jugador no haya sido seleccionada anteriormente durante
        //la partida que se est� llevando a cabo
        if (tablero[4][4] == 'X' || tablero[4][4] == 'O')
        {
            cout << "Esa posici�n ya fue seleccionada, por favor seleccione otra posici�n" << endl;
            num = leerEntero(); //Llama a la funci�n leerEntero y asigna su valor a la variable num
            sustituir(num,jug); //Llama a la funci�n sustituir nuevamente con el nuevp valor ingresado por el jugador
        }
        else
        {
            tablero[4][4]= marca; //Asigna la X o el O a la posici�n en correspondiente en el tablero
        }
        break;
    }
}

//Funci�n para determinar si con el avance del juego que se lleva, alg�n ya alg�n jugador gan� la partida
bool pruebaAvance()
{
    bool gana = false;

    //Prueba de las filas
    if (tablero[0][0] == tablero[0][2] & tablero[0][0] == tablero[0][4])
    {
        gana = true;
    }

    if (tablero[2][0] == tablero[2][2] & tablero[2][0] == tablero[2][4])
    {
        gana = true;
    }

    if (tablero[4][0] == tablero[4][2] & tablero[4][0] == tablero[4][4])
    {
        gana = true;
    }

    //Prueba de las columnas

    if (tablero[0][0] == tablero[2][0] & tablero[0][0] == tablero[4][0])
    {
        gana = true;
    }

    if (tablero[0][2] == tablero[2][2] & tablero[0][2] == tablero[4][2])
    {
        gana = true;
    }

    if (tablero[0][4] == tablero[2][4] & tablero[0][4] == tablero[4][4])
    {
        gana = true;
    }

    //Prueba de las diagonales

     if (tablero[0][0] == tablero[2][2] & tablero[0][0] == tablero[4][4])
    {
        gana = true;
    }

    if (tablero[4][0] == tablero[2][2] & tablero[4][0] == tablero[0][4])
    {
        gana = true;
    }

    return gana; //Regresa un valor booleano
}

//Funci�n para devolver el tablero a sus valores iniciales
void limpiarTablero ()
{
    tablero[0][0]= '1'; //Asigna un 1 a la posici�n correspondiente en el tablero
    tablero[0][2]= '2'; //Asigna un 2 a la posici�n correspondiente en el tablero
    tablero[0][4]= '3'; //Asigna un 3 a la posici�n correspondiente en el tablero
    tablero[2][0]= '4'; //Asigna un 4 a la posici�n correspondiente en el tablero
    tablero[2][2]= '5'; //Asigna un 5 a la posici�n correspondiente en el tablero
    tablero[2][4]= '6'; //Asigna un 6 a la posici�n correspondiente en el tablero
    tablero[4][0]= '7'; //Asigna un 7 a la posici�n correspondiente en el tablero
    tablero[4][2]= '8'; //Asigna un 8 a la posici�n correspondiente en el tablero
    tablero[4][4]= '9'; //Asigna un 9 a la posici�n correspondiente en el tablero
}

// Funci�n que se encarga de leer y validar el dato ingresado por el usuario devuelve un entero o un mensaje de error en caso de que
// no se ingrese un entero
int leerEntero()
{
    // Declaraci�n de variables y asignaci�n de valores
  	int numero, i = 0, longitud;
  	bool prueba;
  	char valor[50] = "";

  	// Ciclo do-while que se encargar� de repetir la validaci�n del dato ingresado por el usuario hasta que el valor de la variable "prueba"
  	// sea diferente de "false"
    do{
        // Asignaci�n del valor "true" en la variable prueba
        prueba = true;

        // Asignaci�n del dato ingresado por el usuario como caracteres en el arreglo "valor"
        cin >> valor;

        // Obtenci�n de la longitud de la cadena de caracteres ingresados en el arreglo "valor"
        longitud = strlen(valor);

        // Condicional para determinar si el n�mero ingresado es superior a 9
        if(longitud > 1)
        {
            cout << "\nError!, favor ingrese un n�mero entero positivo v�lido:" << endl;
            prueba = false;
        }
        else
        {
            // Ciclo while que se encarga de repetir el recorrido del arreglo hasta que "i" sea mayor que la longitud obtenida de la cadena o
            // prueba sea igual a false
            while (i < longitud && prueba == true)
                {
                    // Condicional que valora si el dato en la posici�n "i" del arreglo es igual a cada uno de los n�meros del "1" al 9
                    if (valor[i] == '1' or valor[i] == '2' or valor[i] == '3' or valor[i] == '4' or valor[i] == '5' or valor[i] == '6' or valor[i] == '7' or valor[i] == '8' or valor[i] == '9')
                    {
                        i++; // Suma "1" al valor que posea la variable "i"
                    }else
                    {
                        prueba = false; // Asignaci�n del valor "false" en la variable prueba
                    }
                }

            // Condicional que valora si la variable "prueba" es igual a "true" y si la variable "longitud" es diferentes de "0"
            if (prueba == true && longitud != 0)
            {
                numero = atoi(valor); // Convierte la cadena de caracteres que se encuentra en el arreglo a n�mero y lo asigna a la variable "n�mero"
                return numero; // Devuelve el valor de la variable "n�mero" para la funci�n "leerEntero"
            }else
            {
            cout << "\nError!, favor ingrese un n�mero entero positivo v�lido:" << endl;
            }
        }
    }while (prueba == false); //Condici�n del ciclo do-while

}

//Funci�n para crear y/o guardar los datos del ganador o del empate en un archivo de texto
void guardarArchivo(string jug[2], int punt[2], string result)
{
    ofstream archivo; //Se define archivo

    archivo.open("Resultados.txt",ios::out); //Se crea y/o abre el archivo

    //Condicional para definir si hubo problemas abriendo el archivo
    if(archivo.fail())
    {
        cout << "\nError!, no se pudo abrir el archivo\n" << endl;
        exit(1);
    }

    //Condicional para definir al final de las 4 rondas hubo empate y guardar los datos correspondientes
    if(result == "Empate")
    {
        archivo << "Resultado final: Empate de puntos\n";
        archivo << "Puntaje final de " << jug[0] << ": " << punt[0] << " puntos\n";
        archivo << "Puntaje final de " << jug[1] << ": " << punt[1] << " puntos";
    }
    else
    {
        //Condicional para definir al final de las 4 rondas gan� el primer jugador y guardar los datos correspondientes
        if(punt[0] > punt[1])
        {
            archivo << "Resultado final: " << jug[0] << " gan� con el puntaje m�s alto\n"; //Escribe el texto en el archivo
            archivo << "Puntaje final de " << jug[0] << ": " << punt[0] << " puntos"; //Escribe el texto en el archivo
        }

        //Condicional para definir al final de las 4 rondas gan� el segundo jugador y guardar los datos correspondientes
        if(punt[0] < punt[1])
        {
            archivo << "Resultado final: " << jug[1] << " gan� con el puntaje m�s alto\n"; //Escribe el texto en el archivo
            archivo << "Puntaje final de " << jug[1] << ": " << punt[1] << " puntos"; //Escribe el texto en el archivo
        }
    }
    archivo.close(); //Cierra el archivo
}

//Funci�n para leer los datos del ganador o del empate guardados en un archivo de texto
void leerArchivo()
{
    //Definici�n de variables
    ifstream archivo;
    string resultados;

    archivo.open("Resultados.txt",ios::in); //Se abre el archivo

    //Condicional para definir si hubo problemas abriendo el archivo
    if(archivo.fail())
    {
        cout << "\nError!, a�n no se tienen resultados para desplegar\n" << endl;
        //Llama a la funci�n menu
        menu();
        exit(1);
    }

    //Ciclo while para leer el texto que tiene el archivo
    while(!archivo.eof())
    {
        getline(archivo,resultados);
        cout << "\n" << resultados << endl;
    }
    archivo.close(); //Cierra el archivo
}

