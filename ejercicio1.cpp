#include <iostream>
#include <string>
#include "TADS/avl.h"
using namespace std;

// ------------------ Jugadores ------------------
struct JugadorPorId {
    int id;
    string nombre;
    int puntaje;

    bool operator<(JugadorPorId other) { return id < other.id; }
    bool operator>(JugadorPorId other) { return id > other.id; }
    bool operator==(JugadorPorId other) { return id == other.id; }
};

struct JugadorPorPuntaje {
    int id;
    string nombre;
    int puntaje;

    bool operator<(JugadorPorPuntaje other) {
        if (puntaje == other.puntaje) return id < other.id;
        return puntaje < other.puntaje;
    }
    bool operator>(JugadorPorPuntaje other) {
        if (puntaje == other.puntaje) return id > other.id;
        return puntaje > other.puntaje;
    }
    bool operator==(JugadorPorPuntaje other) {
        return puntaje == other.puntaje && id == other.id;
    }
};

// ------------------ Main ------------------
int main() {
    int N;
    cin >> N;

    if (N < 1 || N > 100000) {
        cout << "N fuera de rango" << endl;
        return 0;
    }

    avl<JugadorPorId> porId;
    avl<JugadorPorPuntaje> porPuntaje;

    for (int i = 0; i < N; i++) {
        string op;
        cin >> op;

        if (op == "ADD") {
            int id ;
            int puntaje;
            string nombre;
            cin >> id >> nombre >> puntaje;
            if (id < 1 || id > 1000000) {
                cout << "id fuera de rango" << endl;
            return 0;
            }
            if (puntaje < 0 || puntaje > 100000) {
                cout << "puntaje fuera de rango" << endl;
            return 0;
            }
            if (nombre.size() > 50) {
                cout << "nombre invalido" << endl;
            }
            JugadorPorId nuevoId{id, nombre, puntaje};
            JugadorPorPuntaje nuevoPuntaje{id, nombre, puntaje};

            if (!porId.contains(nuevoId)) {
                porId.insert(nuevoId);
                porPuntaje.insert(nuevoPuntaje);
            }
        }
        else if (op == "FIND") {
            int id;
            cin >> id;
            if (id < 1 || id > 1000000) {
                cout << "id fuera de rango" << endl;
            return 0;
            }
            JugadorPorId buscado{id, "", 0};

            if (porId.contains(buscado)) {
                JugadorPorId j = porId.get(buscado);
                cout << j.nombre << " " << j.puntaje << endl;
            } else {
                cout << "jugador_no_encontrado" << endl;
            }
        }
        else if (op == "COUNT") {
            cout << porId.size() << endl;
        }
        else if (op == "TOP1") {
            if (porPuntaje.size() == 0) {
                cout << "sin_jugadores" << endl;
            } else {
                JugadorPorPuntaje top = porPuntaje.max();
                cout << top.nombre << " " << top.puntaje << endl;
            }
        }
        else if (op == "RANK") {
            int k;
            cin >> k;
            cout << porPuntaje.contarMayoresIguales(k) << endl;
        }
    }

    return 0;
}
