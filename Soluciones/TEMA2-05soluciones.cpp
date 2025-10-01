// Solución ejercicio vectores caucásicos

// O(v.size()). Usando la plantilla de reducción por división tenemos a=2, b=2, k=1 -> O(n)
bool caucasico(vector<int>& v, int ini, int fin, int& numPares){
    int n = fin-ini;
    if (n == 0){
        numPares = 0;
        return true;
    } 
    if (n == 1) {   
        numPares = (v[ini]%2 == 0);
        return true;
    } else{
        int numParesIz, numParesDr;
        int mitad = (ini+fin)/2;
        if (caucasico(v,ini,mitad,numParesIz)) {
            if (caucasico(v, mitad, fin, numParesDr)) {
                numPares = numParesIz + numParesDr;
                return (abs(numParesIz - numParesDr) <= 2);
            }
        }
        return false;
    }
}