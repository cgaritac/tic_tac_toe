//Universidad: UNED
//Curso:       Introducción a la programación
//Tema:        Proyecto Final, juego "3 en línea"
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

//Definición de funciones
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

// Declaración de variables y asignación de valores
char tablero[5][5]= {'1','|','2','|','3','-','-','-','-','-','4','|','5','|','6','-','-','-','-','-','7','|','8','|','9'};
string jugadores[2];

int main()
{
    // Establece el idioma a español
    setlocale(LC_CTYPE,"Spanish");

    //Llama a la función encabezado
    encabezado(tablero);

    //Llama a la función menu
    menu();

    return 0;
}

//Función que imprime un encabezado en pantalla
void encabezado(char tablero[][5])
{
    // Se imprime información del encabezado en pantalla
    cout << "Universidad: Universidad Estatal a Distancia" << endl;
    cout << "Curso:       Introducción a la programación" << endl;
    cout << "Tema:        Proyecto Final" << endl;
    cout << "Estudiante:  Carlos Garita Campos" << endl;
    cout << "Periodo:     III Cuatrimestre" << endl;
    cout << "________________________________________________" << endl;
    cout << "\n           Juego 3 en línea" << endl;
    cout << "________________________________________________\n" << endl;

    //Llama a la función para imprimir el tablero en pantalla
    imprimirTablero(tablero);
}

//Función que imprime el menú en pantalla
void menu()
{
    cout << "\nMenú de opciones" << endl;
    cout << "1. Iniciar partida" << endl;
    cout << "2. Ver marcadores" << endl;
    cout << "3. Salir" << endl;
    cout << "\nElija la opción que desee e introduzca el número correspondiente para continuar:" << endl;

    //Switch para ejecutar la opción seleccionada por el usuario que llama a la función leerEntero para el ingreso y validación del número de opción
    //seleccionada por el usuario
    switch (leerEntero())
    {
    case 1:
        //Llama a la función solicitarNombres
        solicitarNombres();
        break;
    case 2:
        //Llama a la función leerArchivo
        leerArchivo();
        //Llama a la función menu
        menu();
        break;
    case 3:
        break;
    default:
        cout << "\nOpción no válida!" << endl;
        //Llama a la función menu
        menu();
        break;
    }
}

//Función para imprimir el tablero en pantalla
void imprimirTablero(char tablero[][5])
{
    //Ciclo que recorre las filas y columnas de la matriz para introducir los respectivos valores numéricos en la misma
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

//Función para solicitar los nombres de los jugadores
void solicitarNombres()
{
    cout << "\nIngrese el nombre del jugador que utilizará la X" << endl;
    cin >> jugadores[0];

    cout << "\nIngrese el nombre del jugador que utilizará el O" << endl;
    cin >> jugadores[1];

    cout << "\n" << jugadores[0] << " utilizará la X y " << jugadores[1] << " utilizará el O\n" << endl;

    cout << "Suerte!, y que gane el mejor!" << endl;
    cout << "________________________________________________\n" << endl;

    //Llama a la función iniciarPartida
    iniciarPartida();
}

//Función para llevar a cabo las diferentes rondas de la partida
void iniciarPartida()
{
    // Declaración de variables y asignación de valores
    int numero = 0, movimiento = 0, ronda = 1;
    int puntaje[2] = {0,0};
    char jugador = ' ';
    string resultado = "";
    bool ganador[2] = {false, false};

    //Ciclo que se lleva a cabo hasta que se cumpla con las 4 rondas que se juegan en cada partida entre ambos jugadores
    do
    {
        cout << "        ********** RONDA " << ronda <<" **********" << endl;

        //Llama a la función imprimir tablero
        imprimirTablero(tablero);

        //Ciclo que se ejecuta hasta que alguno de los jugadores gane o se llene por completo el tablero sin un ganador
        do
        {
            cout << "\n" << jugadores[0] << " seleccione el número del tablero en donde desea colocar la X" << endl;
            numero = leerEntero(); //Llama a la función leerEntero y asigna su valor a la variable numero

            jugador = 'A'; //asigna el valor "A" a la variable jugador

            sustituir(numero, jugador); //Llama a la función sustituir

            imprimirTablero(tablero); //Llama a la función imprimirTablero

            movimiento++; //suma un 1 al valor de la variable movimiento

            //Condicional para terminar el ciclo en caso de que gane el primer jugador o este complete el tablero
            if (pruebaAvance() || movimiento == 9)
            {
                break;
            }

            cout << "\n" << jugadores[1] << " seleccione el número del tablero en donde desea colocar el O" << endl;
            numero = leerEntero(); //Llama a la función leerEntero y asigna su valor a la variable numero

            jugador = 'B'; //asigna el valor "A" a la variable jugador

            sustituir(numero, jugador); //Llama a la función sustituir

            imprimirTablero(tablero); //Llama a la función imprimirTablero

            movimiento++; //suma un 1 al valor de la variable movimiento

            //Condicional para terminar el ciclo en caso de que gane el segundo jugador
            if (pruebaAvance())
            {
                break;
            }

        }while(movimiento < 9 ); //Condición del ciclo do-while

        //Condicional para definir si hubo empate entre ambos jugadores en la ronda correspondiente
        if (movimiento = 9 & pruebaAvance() == false)
        {
            puntaje[0] = puntaje[0] + 2; //Asignación de puntaje al primer jugador por empate
            puntaje[1] = puntaje[1] + 2; //Asignación de puntaje al segundo jugador por empate
            cout << "\nEmpate entre ambos jugadores!, suman 2 puntos cada uno\n" << endl;
        }
        else
        {
            //Condicional para definir si ganó el primer jugador en la ronda correspondiente
            if (jugador == 'A' & pruebaAvance())
            {
                puntaje[0] = puntaje[0] + 5; //Asignación de puntaje al primer jugador por gane
                cout << "\n" << jugadores[0] << " gana la partida!, suma 5 puntos\n" << endl;

            }
            else
            {
                puntaje[1] = puntaje[1] + 5; //Asignación de puntaje al segundo jugador por gane
                cout << "\n" << jugadores[1] << " gana la partida!, suma 5 puntos\n" << endl;
            }
        }

    ronda++; //suma un 1 al valor de la variable ronda

    //Llama a la función limpiarTablero
    limpiarTablero();

    }while(ronda < 5); //Condición del ciclo do-while

    cout << "\n        ********** Resultados Finales **********\n" << endl;

    //Condicional para definir si hubo empate entre ambos jugadores al final de las 4 rondas
    if (puntaje[0] == puntaje[1])
    {
        cout << "\nPuntaje final obtenido: " << jugadores[0] << " y " << jugadores[1] << " "<< puntaje[0] << " puntos\n" << endl;
        cout << "\nResultado final: Empate entre ambos jugadores, felicidades a ambos!\n" << endl;
        resultado = "Empate";
        guardarArchivo(jugadores, puntaje, resultado);
    }

    //Condicional para definir si ganó el primer jugador al final de las 4 rondas
    if (puntaje[0] > puntaje[1])
    {
        cout << "\n---- Puntaje final obtenido por " << jugadores[0] << ": " << puntaje[0] << " puntos" << endl;
        cout << "\n---- Puntaje final obtenido por " << jugadores[1] << ": " << puntaje[1] << " puntos\n" << endl;
        cout << "\n---- Resultado final: " << jugadores[0] << " gana la ronda de juegos, felicidades!\n" << endl;
        resultado = "Ganador";
        guardarArchivo(jugadores, puntaje, resultado);
    }

    //Condicional para definir si ganó el segundo jugador al final de las 4 rondas
    if (puntaje[0] < puntaje[1])
    {
        cout << "\nPuntaje final obtenido por " << jugadores[0] << ": " << puntaje[0] << " puntos\n" << endl;
        cout << "\nPuntaje final obtenido por " << jugadores[1] << ": " << puntaje[1] << " puntos\n" << endl;
        cout << "\nResultado final: " << jugadores[1] << " gana la ronda de juegos, felicidades!\n" << endl;
        resultado = "Ganador";
        guardarArchivo(jugadores, puntaje, resultado);
    }

    cout << "\n        ****************************************\n" << endl;

    //Llama a la función menu
    menu();
}

//Función para sustituir la X o el O en el tablero conforme van participando ambos jugadores
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

    //Switc para sustituir el valor la X o el O en la posición correspondiente en el tablero
    switch (num)
    {
    case 1:
        //Condicional para validar que la posición seleccionada por el jugador no haya sido seleccionada anteriormente durante
        //la partida que se está llevando a cabo
        if (tablero[0][0] == 'X' || tablero[0][0] == 'O')
        {
            cout << "Esa posición ya fue seleccionada, por favor seleccione otra posición" << endl;
            num = leerEntero(); //Llama a la función leerEntero y asigna su valor a la variable num
            sustituir(num,jug); //Llama a la función sustituir nuevamente con el nuevp valor ingresado por el jugador
        }
        else
        {
            tablero[0][0]= marca; //Asigna la X o el O a la posición en correspondiente en el tablero
        }
        break;
    case 2:
        //Condicional para validar que la posición seleccionada por el jugador no haya sido seleccionada anteriormente durante
        //la partida que se está llevando a cabo
        if (tablero[0][2] == 'X' || tablero[0][2] == 'O')
        {
            cout << "Esa posición ya fue seleccionada, por favor seleccione otra posición" << endl;
            num = leerEntero(); //Llama a la función leerEntero y asigna su valor a la variable num
            sustituir(num,jug); //Llama a la función sustituir nuevamente con el nuevp valor ingresado por el jugador
        }
        else
        {
            tablero[0][2]= marca; //Asigna la X o el O a la posición en correspondiente en el tablero
        }
        break;
    case 3:
        //Condicional para validar que la posición seleccionada por el jugador no haya sido seleccionada anteriormente durante
        //la partida que se está llevando a cabo
        if (tablero[0][4] == 'X' || tablero[0][4] == 'O')
        {
            cout << "Esa posición ya fue seleccionada, por favor seleccione otra posición" << endl;
            num = leerEntero(); //Llama a la función leerEntero y asigna su valor a la variable num
            sustituir(num,jug); //Llama a la función sustituir nuevamente con el nuevp valor ingresado por el jugador
        }
        else
        {
            tablero[0][4]= marca; //Asigna la X o el O a la posición en correspondiente en el tablero
        }
        break;
    case 4:
        //Condicional para validar que la posición seleccionada por el jugador no haya sido seleccionada anteriormente durante
        //la partida que se está llevando a cabo
        if (tablero[2][0] == 'X' || tablero[2][0] == 'O')
        {
            cout << "Esa posición ya fue seleccionada, por favor seleccione otra posición" << endl;
            num = leerEntero(); //Llama a la función leerEntero y asigna su valor a la variable num
            sustituir(num,jug); //Llama a la función sustituir nuevamente con el nuevp valor ingresado por el jugador
        }
        else
        {
            tablero[2][0]= marca; //Asigna la X o el O a la posición en correspondiente en el tablero
        }
        break;
    case 5:
        //Condicional para validar que la posición seleccionada por el jugador no haya sido seleccionada anteriormente durante
        //la partida que se está llevando a cabo
        if (tablero[2][2] == 'X' || tablero[2][2] == 'O')
        {
            cout << "Esa posición ya fue seleccionada, por favor seleccione otra posición" << endl;
            num = leerEntero(); //Llama a la función leerEntero y asigna su valor a la variable num
            sustituir(num,jug); //Llama a la función sustituir nuevamente con el nuevp valor ingresado por el jugador
        }
        else
        {
            tablero[2][2]= marca; //Asigna la X o el O a la posición en correspondiente en el tablero
        }
        break;
    case 6:
        //Condicional para validar que la posición seleccionada por el jugador no haya sido seleccionada anteriormente durante
        //la partida que se está llevando a cabo
        if (tablero[2][4] == 'X' || tablero[2][4] == 'O')
        {
            cout << "Esa posición ya fue seleccionada, por favor seleccione otra posición" << endl;
            num = leerEntero(); //Llama a la función leerEntero y asigna su valor a la variable num
            sustituir(num,jug); //Llama a la función sustituir nuevamente con el nuevp valor ingresado por el jugador
        }
        else
        {
            tablero[2][4]= marca; //Asigna la X o el O a la posición en correspondiente en el tablero
        }
        break;
    case 7:
        //Condicional para validar que la posición seleccionada por el jugador no haya sido seleccionada anteriormente durante
        //la partida que se está llevando a cabo
        if (tablero[4][0] == 'X' || tablero[4][0] == 'O')
        {
            cout << "Esa posición ya fue seleccionada, por favor seleccione otra posición" << endl;
            num = leerEntero(); //Llama a la función leerEntero y asigna su valor a la variable num
            sustituir(num,jug); //Llama a la función sustituir nuevamente con el nuevp valor ingresado por el jugador
        }
        else
        {
            tablero[4][0]= marca; //Asigna la X o el O a la posición en correspondiente en el tablero
        }
        break;
    case 8:
        //Condicional para validar que la posición seleccionada por el jugador no haya sido seleccionada anteriormente durante
        //la partida que se está llevando a cabo
        if (tablero[4][2] == 'X' || tablero[4][2] == 'O')
        {
            cout << "Esa posición ya fue seleccionada, por favor seleccione otra posición" << endl;
            num = leerEntero(); //Llama a la función leerEntero y asigna su valor a la variable num
            sustituir(num,jug); //Llama a la función sustituir nuevamente con el nuevp valor ingresado por el jugador
        }
        else
        {
            tablero[4][2]= marca; //Asigna la X o el O a la posición en correspondiente en el tablero
        }
        break;
    case 9:
        //Condicional para validar que la posición seleccionada por el jugador no haya sido seleccionada anteriormente durante
        //la partida que se está llevando a cabo
        if (tablero[4][4] == 'X' || tablero[4][4] == 'O')
        {
            cout << "Esa posición ya fue seleccionada, por favor seleccione otra posición" << endl;
            num = leerEntero(); //Llama a la función leerEntero y asigna su valor a la variable num
            sustituir(num,jug); //Llama a la función sustituir nuevamente con el nuevp valor ingresado por el jugador
        }
        else
        {
            tablero[4][4]= marca; //Asigna la X o el O a la posición en correspondiente en el tablero
        }
        break;
    }
}

//Función para determinar si con el avance del juego que se lleva, algún ya algún jugador ganó la partida
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

//Función para devolver el tablero a sus valores iniciales
void limpiarTablero ()
{
    tablero[0][0]= '1'; //Asigna un 1 a la posición correspondiente en el tablero
    tablero[0][2]= '2'; //Asigna un 2 a la posición correspondiente en el tablero
    tablero[0][4]= '3'; //Asigna un 3 a la posición correspondiente en el tablero
    tablero[2][0]= '4'; //Asigna un 4 a la posición correspondiente en el tablero
    tablero[2][2]= '5'; //Asigna un 5 a la posición correspondiente en el tablero
    tablero[2][4]= '6'; //Asigna un 6 a la posición correspondiente en el tablero
    tablero[4][0]= '7'; //Asigna un 7 a la posición correspondiente en el tablero
    tablero[4][2]= '8'; //Asigna un 8 a la posición correspondiente en el tablero
    tablero[4][4]= '9'; //Asigna un 9 a la posición correspondiente en el tablero
}

// Función que se encarga de leer y validar el dato ingresado por el usuario devuelve un entero o un mensaje de error en caso de que
// no se ingrese un entero
int leerEntero()
{
    // Declaración de variables y asignación de valores
  	int numero, i = 0, longitud;
  	bool prueba;
  	char valor[50] = "";

  	// Ciclo do-while que se encargará de repetir la validación del dato ingresado por el usuario hasta que el valor de la variable "prueba"
  	// sea diferente de "false"
    do{
        // Asignación del valor "true" en la variable prueba
        prueba = true;

        // Asignación del dato ingresado por el usuario como caracteres en el arreglo "valor"
        cin >> valor;

        // Obtención de la longitud de la cadena de caracteres ingresados en el arreglo "valor"
        longitud = strlen(valor);

        // Condicional para determinar si el número ingresado es superior a 9
        if(longitud > 1)
        {
            cout << "\nError!, favor ingrese un número entero positivo válido:" << endl;
            prueba = false;
        }
        else
        {
            // Ciclo while que se encarga de repetir el recorrido del arreglo hasta que "i" sea mayor que la longitud obtenida de la cadena o
            // prueba sea igual a false
            while (i < longitud && prueba == true)
                {
                    // Condicional que valora si el dato en la posición "i" del arreglo es igual a cada uno de los números del "1" al 9
                    if (valor[i] == '1' or valor[i] == '2' or valor[i] == '3' or valor[i] == '4' or valor[i] == '5' or valor[i] == '6' or valor[i] == '7' or valor[i] == '8' or valor[i] == '9')
                    {
                        i++; // Suma "1" al valor que posea la variable "i"
                    }else
                    {
                        prueba = false; // Asignación del valor "false" en la variable prueba
                    }
                }

            // Condicional que valora si la variable "prueba" es igual a "true" y si la variable "longitud" es diferentes de "0"
            if (prueba == true && longitud != 0)
            {
                numero = atoi(valor); // Convierte la cadena de caracteres que se encuentra en el arreglo a número y lo asigna a la variable "número"
                return numero; // Devuelve el valor de la variable "número" para la función "leerEntero"
            }else
            {
            cout << "\nError!, favor ingrese un número entero positivo válido:" << endl;
            }
        }
    }while (prueba == false); //Condición del ciclo do-while

}

//Función para crear y/o guardar los datos del ganador o del empate en un archivo de texto
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
        //Condicional para definir al final de las 4 rondas ganó el primer jugador y guardar los datos correspondientes
        if(punt[0] > punt[1])
        {
            archivo << "Resultado final: " << jug[0] << " ganó con el puntaje más alto\n"; //Escribe el texto en el archivo
            archivo << "Puntaje final de " << jug[0] << ": " << punt[0] << " puntos"; //Escribe el texto en el archivo
        }

        //Condicional para definir al final de las 4 rondas ganó el segundo jugador y guardar los datos correspondientes
        if(punt[0] < punt[1])
        {
            archivo << "Resultado final: " << jug[1] << " ganó con el puntaje más alto\n"; //Escribe el texto en el archivo
            archivo << "Puntaje final de " << jug[1] << ": " << punt[1] << " puntos"; //Escribe el texto en el archivo
        }
    }
    archivo.close(); //Cierra el archivo
}

//Función para leer los datos del ganador o del empate guardados en un archivo de texto
void leerArchivo()
{
    //Definición de variables
    ifstream archivo;
    string resultados;

    archivo.open("Resultados.txt",ios::in); //Se abre el archivo

    //Condicional para definir si hubo problemas abriendo el archivo
    if(archivo.fail())
    {
        cout << "\nError!, aún no se tienen resultados para desplegar\n" << endl;
        //Llama a la función menu
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

