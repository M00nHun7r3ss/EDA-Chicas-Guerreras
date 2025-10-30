// Carmen Gómez Becerra
// EDA-GDV29

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

#include "deque_eda.h"

// Complejidad O(n), n = nelems de la queue.
deque<int> ordenaMenorMayor(int n, std::vector<int> nums){
    deque<int> rQueue;

    for (int i = 0; i < n; i++){
	    if (nums[i] > 0){
            rQueue.push_front(nums[i]); // O(1)
	    }
        else if (nums[i] <= 0){
            rQueue.push_back(nums[i]); // O(1)
        }
    }

    // como for() es O(n) y lo de dentro O(1)...
    // for(O(1)) -> O(n) * O(1) -> O(n)

    return rQueue;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int n, m;
    std::cin >> n;

    if (n == 0)
        return false;

    std::vector<int> nums;
    for (int i = 0; i < n; i++){
        std::cin >> m;
        nums.push_back(m);
    }

    // escribir sol
    deque<int> sol = ordenaMenorMayor(n, nums);
    for (int i = 0; i < n; i++){
		std::cout << sol.back() << " "; // O(1)
        sol.pop_back(); // O(1)
    }

    std::cout << std::endl;

    return true;
}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif 


    while (resuelveCaso())
        ;


    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}