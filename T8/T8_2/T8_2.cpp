// Plantilla para el ejercicio del Consultorio Médico

#include <iostream>
#include <stdexcept>
#include <fstream>
#include <vector>
#include <iomanip>
#include <string>
#include <cassert>
#include <map>


using namespace std;

using medico = string;
using paciente = string;

//cosas de la fecha que he cogido del ejercicio JUNIO 23 - 3
class Fecha {
    int _dia, _hora, _minuto;

public:
    Fecha(int d = 0, int h = 0, int m = 0) : _dia(d), _hora(h), _minuto(m) {}

    int dia() const { return _dia; }
    int hora() const { return _hora; }
    int minuto() const { return _minuto; }

    bool operator<(Fecha const& o) const {
        if (_dia != o._dia) return _dia < o._dia;
        if (_hora != o._hora) return _hora < o._hora;
        return _minuto < o._minuto;
    }
};

inline std::istream& operator>>(std::istream& entrada, Fecha& h) {
    int d, m, s; char c;
    std::cin >> d >> c >> m >> c >> s;
    h = Fecha(d, m, s);
    return entrada;
}

inline std::ostream& operator<<(std::ostream& out, Fecha const& f) {
    out << std::setfill('0') << std::setw(2) << f.hora()
        << ":"
        << std::setfill('0') << std::setw(2) << f.minuto();
    return out;
}

class Consultorio {
private:

    map<medico, map<Fecha, paciente>> datos;

public:

    void nuevoMedico(medico const& m) {
        //Si existia previamente, no inserta nada
        datos.insert({ m, {} });
    }

    void pideConsulta(paciente const& p, medico const& m, Fecha const& f) {

        //Si ese medico no existe, nada
        if (!datos.count(m))
            throw invalid_argument("Medico no existente");

        //vemos la agenda del medico concreto
        auto& agenda = datos[m];

        //Si esta ocupoada la fecha nada
        if (agenda.count(f))
            throw invalid_argument("Fecha ocupada");

        //Si no esta ocupada, aniadimos al paciente
        agenda[f] = p;
    }

    paciente siguientePaciente(medico const& m) {
        //Si ese medico no existe, nada
        if (!datos.count(m))
            throw invalid_argument("Medico no existente");

        //Vemos la agenda del medico
        auto const& agenda = datos.at(m);

        //Si esta vacia, pues nada
        if (agenda.empty())
            throw invalid_argument("No hay pacientes");

        //El primero con la primera fecha
        return agenda.begin()->second;
    }

    void atiendeConsulta(medico const& m) {
        //Si ese medico no existe, nada
        if (!datos.count(m))
            throw invalid_argument("Medico no existente");

        //Vemos la agenda del medico
        auto& agenda = datos[m];

        //Si esta vacia, pues nada
        if (agenda.empty())
            throw invalid_argument("No hay pacientes");

        //Ateinde al primer paciente
        agenda.erase(agenda.begin()); 
    }


    vector<pair<Fecha, paciente>> listaPacientes(medico const& m, Fecha const& f) {
        //Si ese medico no existe, nada
        if (!datos.count(m))
            throw invalid_argument("Medico no existente");

        //La lista de pacientes con su fecha
        vector<pair<Fecha, paciente>> res;

        //Vemos la agenda del medico
        auto const& agenda = datos.at(m);

        //Sacamos paciente y fecha
        for (auto const& par : agenda) {
            if (par.first.dia() == f.dia()) {
                res.push_back({ par.first, par.second });
            }
        }

        return res;
    }
};

int casos = 0;

bool resuelve() {

    int N;
    cin >> N;
    if (!cin) return false;

    string inst; medico med; paciente pac; int d, h, m; char c;
    Consultorio con;

    for (int i = 0; i < N; ++i) {
        try {
            cin >> inst;
            if (inst == "nuevoMedico") {
                cin >> med;
                con.nuevoMedico(med);
            }
            else if (inst == "pideConsulta") {
                cin >> pac >> med >> d >> h >> c >> m;
                con.pideConsulta(pac, med, Fecha(d, h, m));
            }
            else if (inst == "siguientePaciente") {
                cin >> med;
                pac = con.siguientePaciente(med);
                cout << "Siguiente paciente doctor " << med << '\n';
                cout << pac << '\n';
            }
            else if (inst == "atiendeConsulta") {
                cin >> med;
                con.atiendeConsulta(med);
            }
            else if (inst == "listaPacientes") {
                cin >> med >> d;
                auto vec = con.listaPacientes(med, Fecha(d, 0, 0));
                cout << "Doctor " << med << " dia " << d << '\n';
                for (auto p : vec) {
                    cout << p.second << ' ' << p.first << '\n';
                }
            }
            else
                assert(false);
        }
        catch (invalid_argument e) { cout << e.what() << '\n'; }
    }
    cout << "---\n";

    return true;
}

int main() {
#ifndef DOMJUDGE
    ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (resuelve()) {}

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    return 0;
}
