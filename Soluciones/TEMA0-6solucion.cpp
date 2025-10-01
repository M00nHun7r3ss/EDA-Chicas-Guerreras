//  Funciones resolver y resuelveCaso para problema Tema0-6 (DupSecB)
// -------------------------------------------------------------------

void resolver(vector<int>& v) {
    for (int i = 0; i < v.size(); i++)
        v[i] *= 2;

    // Version más cómoda con range-based for
    //for (int& e : v) // Necesario el & para que el acceso a e sea por referencia 
    //    e *= 2; 
}


bool resuelveCaso() {
    // leer los datos de la entrada
    int n;
    cin >> n;
    if (n == -1) return false;
    vector<int> v(n);
    
    for (int i = 0; i < n; ++i) cin >> v[i];
    // Version más cómoda con range-based for
    /*for (int& e : v) // Necesario el & para que el acceso a e sea por referencia
        cin >> e;
    */

    resolver(v);

    // escribir sol
    //for (int i = 0; i < n; ++i) cout << v[i] << " ";
    // Version más cómoda con range-based for
    for (int e : v) cout << e << " ";
    cout << endl;
    return true;
}

//#define DOMJUDGE
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
     //system("PAUSE");
     #endif
    
    return 0;
}