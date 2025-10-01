// Solución al ejercicio del nº complementario

int digitoComp(int digito){
    return 9-digito;
}

// O(log10(n)) o lineal en el nº de digitos de n
int comp(int n){
    if (n <= 9) return digitoComp(n);
    int compResto = comp(n/10);
    return compResto*10 + (digitoComp(n%10));
}

// Version no-final devolviendo pair<int,int> con potencia de 10
// O(log10(n)) o lineal en el nº de digitos de n
pair<int,int> compInv(int n){
    if (n <= 9) return {digitoComp(n),10};
    else {
        auto [compResto,potResto] = compInv(n/10);
        return {potResto*(digitoComp(n%10)) + compResto, 10*potResto};
    }
}

// Version final con acumulador
// O(log10(n)) o lineal en el nº de digitos de n
int compInvFinal(int n, int acu) {
    if (n <= 9) return acu*10 + digitoComp(n);
    else {
        return compInvFinal(n/10, 10*acu + digitoComp(n%10));
    }
}