
#include <iostream>
#include <vector>
#include <string>
#include <cstdint>
#include <utility>

using namespace std;

struct Registro {

    string identificador;
    int nota;
};

class OrdenacaoEstavel {

private:

    vector<Registro> registros;

    uint64_t deslocamentos = 0;

public:

    explicit OrdenacaoEstavel(int n) {

        registros.resize(n);
    }

    void carregar() {

        for (auto &registro : registros) {

            cin >> registro.identificador
                >> registro.nota;
        }
    }

    void ordenar() {

        int n = static_cast<int>(registros.size());

        for (int i = 1; i < n; i++) {

            

            Registro chave = move(registros[i]);

            int j = i;

            

            while (
                j > 0 &&
                registros[j - 1].nota > chave.nota
            ) {

                registros[j] = move(registros[j - 1]);

                j--;

                deslocamentos++;
            }

           

            registros[j] = move(chave);
        }
    }

    void apresentar() const {

        for (const auto &registro : registros) {

            cout << registro.identificador
                 << ' '
                 << registro.nota
                 << '\n';
        }

        cout << "DESLOCAMENTOS "
             << deslocamentos
             << '\n';
    }
};

int main() {

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;

    if (!(cin >> n))
        return 0;

    OrdenacaoEstavel sistema(n);

    sistema.carregar();

    sistema.ordenar();

    sistema.apresentar();

    return 0;
}
