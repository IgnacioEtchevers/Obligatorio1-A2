#include <cassert>
#include <string>
#include <iostream>

#include "TADS/avl.cpp"

using namespace std;

// ------------------ Jugadores ------------------
struct JugadorPorId {
    int id;
    string nombre;
    int puntaje;

    bool operator<(JugadorPorId other) { 
        return id < other.id; 
    }
    bool operator>(JugadorPorId other) { 
        return id > other.id; 
    }
    bool operator==(JugadorPorId other) { 
        return id == other.id; 
    }
};

struct JugadorPorPuntaje {
    int id;
    string nombre;
    int puntaje;

    bool operator<(JugadorPorPuntaje other) {
        if (puntaje == other.puntaje) {
            return id < other.id;
        };
        return puntaje < other.puntaje;
    }
    bool operator>(JugadorPorPuntaje other) {
        if (puntaje == other.puntaje) {
            return id > other.id;
        };
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

    avl<JugadorPorId> porId;
    avl<JugadorPorPuntaje> porPuntaje;

    for (int i = 0; i < N; i++) {
        string op;
        cin >> op;

        if (op == "ADD") {
            int id, puntaje;
            string nombre;
            cin >> id >> nombre >> puntaje;

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
                
                cout << porPuntaje.ELMEJORNOMBRE() << " " << porPuntaje.ELMEJOR() << endl;
            }
        }
        else if (op == "RANK") {
            if (porPuntaje.size() != 0) {
                int punt;
                cin >> punt;
                int contRet=0;
                int cantidad = porPuntaje.contarMayoresIguales(punt,contRet);
                cout << cantidad << endl;
            }
            
        }
    }
}