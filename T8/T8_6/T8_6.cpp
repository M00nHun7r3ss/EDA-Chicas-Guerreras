#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <map>
#include <list>
#include <cassert>
#include <stdexcept>
using namespace std;

using cancion = std::string;
using artista = std::string;

struct datos_Cancion {
    artista artist;
    int duration;
};

class iPud {
private:
    map<string, datos_Cancion> songs;

    list<string> playlist;
    map<string, list<string>::iterator> posPlaylist;

    list<string> recent;
    map<string, list<string>::iterator> posRecent;

    int time = 0;

public:

    void addSong(string const& s, string const& a, int d) {
        //Ya existe la cancion
        if (songs.count(s))
            throw invalid_argument("addSong");

        //con artista y duracion
        songs[s] = { a, d };
    }

    void addToPlaylist(string const& s) {
        //No existe la cancion
        if (!songs.count(s))
            throw invalid_argument("addToPlaylist");

        //Esta ya en la playlist
        if (posPlaylist.count(s)) return;

        //La aniadimos al final
        playlist.push_back(s);
        posPlaylist[s] = --playlist.end();

        //Sumamos duracion en la playlist
        time += songs[s].duration;
    }

    string current() const {
        //No hay canciones
        if (playlist.empty())
            throw invalid_argument("current");

        //La primera de la lista
        return playlist.front();
    }

    void play() {
        //No hay canciones
        if (playlist.empty()) return;

        //La primera cancion la quitamos
        string s = playlist.front();
        playlist.pop_front();

        posPlaylist.erase(s);
        //Reducimos el tiempo
        time -= songs[s].duration;

        //Si ha sido reciente, la borramos
        if (posRecent.count(s))
            recent.erase(posRecent[s]);

        //Si no ha sido reciente, ahora si
        recent.push_front(s);
        posRecent[s] = recent.begin();
    }

    int totalTime() const {
        return time;
    }

    vector<string> recentSong(int N) const {
        //Saca en un vector las canciones recientes
        vector<string> res;
        auto it = recent.begin();

        //Itera de inicio a fin
        while (it != recent.end() && N--) {
            res.push_back(*it);
            ++it;
        }

        return res;
    }

    void deleteSong(string const& s) {

        if (!songs.count(s)) return;

        // borramos de la playlist
        if (posPlaylist.count(s)) {
            time -= songs[s].duration;
            playlist.erase(posPlaylist[s]);
            posPlaylist.erase(s);
        }

        // borramos de recent
        if (posRecent.count(s)) {
            recent.erase(posRecent[s]);
            posRecent.erase(s);
        }

        // la quitamos de canciones
        songs.erase(s);
    }
};

bool resuelve() {
    string operacion;
    cin >> operacion;
    if (!cin)
        return false;
    cancion tit; artista aut; int dur;
    iPud ipud;
    while (operacion != "FIN") {
        try {
            if (operacion == "addSong") {
                cin >> tit >> aut >> dur;
                ipud.addSong(tit, aut, dur);
            }
            else if (operacion == "addToPlaylist") {
                cin >> tit;
                ipud.addToPlaylist(tit);
            }
            else if (operacion == "current") {
                tit = ipud.current(); // aunque no se hace nada, puede producir error
            }
            else if (operacion == "play") {
                try {
                    string tocando = ipud.current(); // para saber si la lista es vacía
                    ipud.play();
                    cout << "Sonando " << tocando << '\n';
                }
                catch (invalid_argument e) {
                    cout << "No hay canciones en la lista\n";
                }
            }
            else if (operacion == "totalTime") {
                cout << "Tiempo total " << ipud.totalTime() << '\n';
            }
            else if (operacion == "recent") {
                int N;
                cin >> N;
                auto lista = ipud.recentSong(N);
                if (lista.empty())
                    cout << "No hay canciones recientes\n";
                else {
                    cout << "Las " << lista.size() << " mas recientes\n";
                    for (auto const& s : lista)
                        cout << "    " << s << '\n';
                }
            }
            else if (operacion == "deleteSong") {
                cin >> tit;
                ipud.deleteSong(tit);
            }
            else { // operacion desconocida
                assert(false);
            }
        }
        catch (invalid_argument e) {
            cout << "ERROR " << e.what() << '\n';
        }
        cin >> operacion;
    }
    cout << "---\n";
    return true;
}

int main() {
    // ajuste para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
   // _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    std::ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (resuelve());

    // restablecimiento de cin
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    //system("pause");
#endif
    return 0;
}
