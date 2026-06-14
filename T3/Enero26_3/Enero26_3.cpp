/*

Ejercicio 3:

Qué has conseguido hacer y qué no:

Tupla solución: sol = (x0, x1, ..., x(n-1)) de "booleanos", donde 0 significa que no lo estudias, y 1 que si

Marcadores:
k - tema actual
horasAct - horas usadas
puntosAct - puntos acumulados
mejorSol - mejor puntuacion encontrada

Ejemplo de aplicación de poda por estimación:

Asumiríamos que podemos coger TODOS los temas restantes

estimacion = puntosAct + sumaRestante[k]

Si estimacion <= mejorSol se poda


Ejercicio 4:
------------

a) Estado del map tras insertar <7,a>, <10,b>, <2,c>, <5,d>, <4,e>, <8,a>:

nelems = 6
raiz  ->  <7,a>
         /     \
      <2,c>    <10,b>
        \         /  
       <5,d>   <8,a>
        /
     <4,e>

Estado del map tras ejecutar m.erase(7): se sustituye por el siguiente (en orden real)

nelems = 5
raiz  ->  <8,a>
         /     \
      <2,c>    <10,b>
        \         
       <5,d>  
        /
     <4,e>


b) Estado del unordered_map tras insertar <7,a>, <10,b>, <2,c>, <5,d>: 

Tiene una capacidad inicial de 5 (4 claves valor)
Ubicacion se calcula como: posición = (2* clave + 1) % capacidad

(2*7+1) % 5 = 0
(2*10+1) % 5 = 1
(2*2+1) % 5 = 0
(2*5+1) % 5 = 1

Se inserta al principio (algo como un push_front)

nelems / capacidad > 0.9? NO.

nelems = 4
array:
  -
0| | -> <2,c> -> <7,a>
  -
1| | -> <5,d> -> <10,b>
  -
2| | ->
  -
3| | ->
  -
4| | -> 
  -

Estado tras insertar también <4,e>, <8,a>:

nelems / capacidad > 0.9? SI

Buscamos siguiente primo. 2*5 (capacidad inicial) = 10, pero no es primo, asi que, el siguiente es 11

La nueva capacidad es 11

Ubicacion se calcula como: posición = (2* clave + 1) % capacidad

(2*7+1) % 11 = 4
(2*10+1) % 11 = 10
(2*2+1) % 11 = 5
(2*5+1) % 11 = 0
(2*4+1) % 11 = 9
(2*8+1) % 11 = 6

nelems = 11
array:
  -
0| | -> <5,d>
  -
1| | ->
  -
2| | ->
  -
3| | ->
  -
4| | -> <7,a>
  -
5| | -> <2,c>
  -
6| | -> <8,a>
  -
7| | ->
  -
8| | ->
  -
9| | -> <4,e>
  -
10| | -> <10,b>
  -

*/


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <climits>
using namespace std;


// Por si queréis imprimir algún vector en depuración
template <class T>
ostream& operator<<(ostream& out, vector<T> const& v) {
    for (auto e : v) out << e << " ";
    return out;
}


// función que resuelve el problema
void resolver(int k, int n, int h,
    vector<int> const& puntos,
    vector<int> const& horas,
    int puntosAct,      // puntos acumulados hasta ahora
    int horasAct,       // horas usadas hasta ahora
    int& mejorSol,      // mejor puntuacion encontrada
    vector<int> const& sumaRestante, // cota optimista
    vector<int>& sol,                // solución parcial (0/1)
    vector<int>& mejorSolVec)        // mejor solución encontrada
{

    // Caso base: hemos decidido sobre todos los temas
    if (k == n) {
        // si mejora la mejor solucion, la actualizamos
        if (puntosAct > mejorSol) {
            mejorSol = puntosAct;
            mejorSolVec = sol;
        }
        return;
    }

    // Poda por estimacion
    // Suponemos que cogemos TODOS los temas restantes
    // si no mejoramos, no seguimos
    if (puntosAct + sumaRestante[k] <= mejorSol)
        return;

    // Cogemos tema k
    if (horasAct + horas[k] <= h) {
        sol[k] = 1;
        resolver(k + 1, n, h, puntos, horas,
            puntosAct + puntos[k],
            horasAct + horas[k],
            mejorSol, sumaRestante, sol, mejorSolVec);
    }

    // No cogemos tema k
    sol[k] = 0;
    resolver(k + 1, n, h, puntos, horas,
        puntosAct,
        horasAct,
        mejorSol, sumaRestante, sol, mejorSolVec);
}


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    int n, h;
    cin >> n >> h;
    vector<int> puntos(n);
    vector<int> horas(n);
    for (int i = 0; i < n; ++i) cin >> puntos[i];
    for (int i = 0; i < n; ++i) cin >> horas[i];

    vector<int> sol(n, 0);
    vector<int> mejorSolVec(n, 0);

    int mejorSol = 0;

    vector<int> sumaRestante(n + 1);
    sumaRestante[n] = 0;
    for (int i = n - 1; i >= 0; i--)
    {
        sumaRestante[i] = sumaRestante[i + 1] + puntos[i];
    }

    resolver(0, n, h, puntos, horas, 0, 0, mejorSol, sumaRestante, sol, mejorSolVec);

    //cout << "Tupla Solucion: ";
    //for (int i = 0; i < n; i++) {
    //    cout << mejorSolVec[i] << " ";
    //}
    //cout << endl;

    //cout << "Temas elegidos: ";
    //for (int i = 0; i < n; i++) {
    //    if (mejorSolVec[i] == 1)
    //        cout << i << " ";
    //}
    //cout << endl;

    cout << mejorSol << endl;
}


//#define DOMJUDGE
int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif
    int numCasos;
    std::cin >> numCasos;
    for (int i = 0; i < numCasos; ++i)
        resuelveCaso();

    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    //system("PAUSE");
#endif

    return 0;
}
