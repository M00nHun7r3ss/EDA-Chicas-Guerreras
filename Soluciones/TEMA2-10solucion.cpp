/*

Solución ejercicio "Solo un impar" (Tema2-10)

Ejemplos generales:

busca([2,4,6,8,10,11,12])  [2,_,_,8,_,_,12]  -> busca([10,11,12])

busca([2,3,4,6,8,10,12])   [2,_,_,6,_,_,12]  -> busca([2,3,4])

busca([2,4,6,7,8,10,12])   [2,_,_,7,_,_,12]  -> busca([2,4,6])

Ejemplos pequeños:

busca([3]) -> 3

busca([2,3]) -> 3 (por caso particular)

busca([3,4]) -> busca([3]) -> 3

busca([3,4,6]) -> busca([3]) -> 3

busca([2,3,4]) -> 3 (por caso particular)

busca([2,4,5]) -> busca([5]) -> 5

*/

// Complejidad: O(log n) n=fin-ini
int buscaImpar(vector<int> const& v, int ini, int fin) {
    int n = fin - ini;
    if (n == 1) return v[ini];
    //if (n == 2) ... // Ya no necesario al incluir el caso particular de impar en mitad
    int mitad = (ini+fin)/2;
    if (v[mitad]%2 == 1) return v[mitad];
    if (v[ini] + 2*(mitad-ini) != v[mitad]) return buscaImpar(v, ini, mitad);
    else return buscaImpar(v, mitad+1, fin);
}