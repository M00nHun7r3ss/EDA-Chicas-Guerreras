/*
Nombre completo: Denisa Juarranz Berindea 
Usuario del juez: EDA_GDV36
*/

#include <iostream>
#include <stdexcept>
#include <fstream>
#include <cassert>
#include <utility>
#include <unordered_map>
#include <list>
#include <set>


using namespace std;


using paciente = string;
using gravedad = int;

class urgencias {
private:
    //Listas para almacenar a los pacientes de cada gravedad
    list<paciente> grave;  
    list<paciente> media;
    list<paciente> leve;

    //Registro de pacientes y su gravedad
    unordered_map<paciente, int> paciente_gravedad;

    //Registro de pacientes recuperados
    set<paciente> recuperado;

    //Busca el paciente en una lista y lo quita de ella
    //coste: O(n) siendo n el numero de elementos de la lista
    void quita_paciente(list<string>& L, const string& p) {
        //Recorre la lista //(O) n siendo n el numero total de elementos de la lista
        for (auto it = L.begin(); it != L.end(); ++it) {
            //Si lo encuentra
            if (*it == p) {
                //lo borra //O(1)
                L.erase(it);
                return;
            }
        }
    }

public:

    // coste: O(1). Se introduce al paciente y ya, no hay recorridos ni nada
    void nuevo_paciente(paciente p, gravedad g) {

        //Si ya esta dicho paciente
        if (paciente_gravedad.find(p) != paciente_gravedad.end()) //O(1)
            //paciente_gravedad.count(p)
        {
        	throw domain_error("Paciente repetido");
        }
        //Si la gravedad no es valida
        if (g < 1 || g > 3)
        {
            throw domain_error("Gravedad incorrecta");
        }

        //Si hemos llegado aqui, valen el paciente y su gravedad //O(1)
        paciente_gravedad[p] = g;

        //Lo metemos ademas en las colas //O(1)
        if (g == 3) grave.push_back(p);
        else if (g == 2) media.push_back(p);
        else leve.push_back(p);
    }

    // coste: O(1)
    int gravedad_actual(paciente p) const {
        //Buscamos al paciente pedido //O(1)
        unordered_map<string, int>::const_iterator it = paciente_gravedad.find(p);

        //Si no esta en la lista 
        if (it == paciente_gravedad.end())
        {
            throw domain_error("Paciente inexistente");
        }

        //Si hemos llegado aqui, el paciente existe, y por tanto, devolvemos su complejidad //O(1)
        return it->second;
    }

    // coste: O(1)
    paciente siguiente() {
        paciente p;

        //Usaremos front, para tener en cuenta el orden de llegada
        //Empezamos con los graves //O(1)
        if (!grave.empty()) {
            p = grave.front();
            grave.pop_front();
        }
        //Si no hay graves pasamos a los de media gravedad //O(1)
        else if (!media.empty()) {
            p = media.front();
            media.pop_front();
        }
        //Y si no hay de media gravedad, pasamos a los leves //O(1)
        else if (!leve.empty()) {
            p = leve.front();
            leve.pop_front();
        }
        //Y si hemos llegado aqui, es que ya no hay pacientes
        else{
            throw domain_error("No hay pacientes");
        }

        //Borramos el paciente del registro, porque lo vamos a atender ya //O(1)
        paciente_gravedad.erase(p);

        //Lo devolvemos para llamarle a ser atendido //O(1)
        return p;
    }

    // coste: O(n) donde n es el tamanio de la lista de donde quitamos los pacientes
    void mejora(paciente p) {

        //Buscamos el paciente //O(1)
        unordered_map<string, int>::iterator it = paciente_gravedad.find(p);
        //Si no existe
        if (it == paciente_gravedad.end())
            throw domain_error("Paciente inexistente");

        //Si hemos llegado aqui, analizamos su gravedad
        int g = it->second;

        //Los quitamos de su lista actual con el metodo privado quita_paciente //O(n) siendo n el tamanio de cada lista de donde quitamos
        if (g == 3) quita_paciente(grave, p);
        else if (g == 2) quita_paciente(media, p);
        //Ademas, si es leve
        else if (g == 1) {
            quita_paciente(leve, p);
            //Lo quitamos de la lista de pacientes en espera //O(1)
            paciente_gravedad.erase(p);
            //Y lo ponemos en la de recuperados //O(log n) siendo n el numero de recuperados actual
            recuperado.insert(p);
            return;
        }

        //Baja la gravedad
        int nueva_g = g - 1;
        //Y se la cambia al paciente //O(1)
        paciente_gravedad[p] = nueva_g;

        //Y los insertamos al principio, porque han venido de una gravedad mayor //O(1)
        if (nueva_g == 2) media.push_front(p);
        else if (nueva_g == 1) leve.push_front(p);
    }

    // coste: O(n) donde n es el numero de recuperados del set
    list<paciente> recuperados() const {

        //Lo cuardaremos en una lista
        list<paciente> recs;
        //Recorremos el set de pacientes recuperados //O(n) donde n es el numero de recuperados del set
        for (const paciente& p : recuperado)
        {
            //Y lo cuardamos en la lista //O(1)
            recs.push_back(p);
        }

        //Devolvemos la lista 
        return recs;
    }
};

bool resuelveCaso() { // No tocar esta función
    string orden, pac;
    int grav;
    cin >> orden;
    if (!cin) return false;

    urgencias sala;

    while (orden != "FIN") {
        try {
            if (orden == "nuevo_paciente") {
                cin >> pac >> grav;
                sala.nuevo_paciente(pac, grav);
            }
            else if (orden == "gravedad_actual") {
                cin >> pac;
                int g = sala.gravedad_actual(pac);
                cout << "La gravedad de " << pac << " es " << g << '\n';
            }
            else if (orden == "siguiente") {
                string p = sala.siguiente();
                cout << "Siguiente paciente: " << p << '\n';
            }
            else if (orden == "recuperados") {
                auto lista = sala.recuperados();
                cout << "Lista de recuperados:";
                for (auto& p : lista)
                    cout << ' ' << p;
                cout << '\n';
            }
            else if (orden == "mejora") {
                cin >> pac;
                sala.mejora(pac);
            }
        }
        catch (std::domain_error e) {
            std::cout << "ERROR: " << e.what() << '\n';
        }
        std::cin >> orden;
    }
    std::cout << "---\n";
    return true;
}

//#define DOMJUDGE
int main() {
#ifndef DOMJUDGE
    ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif

    while (resuelveCaso()) {}

#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
#endif
    return 0;
}
