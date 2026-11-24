
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdint>

using namespace std;

class MergeInversion {

private:

    vector<long long> dados;
    vector<long long> auxiliar;

    uint64_t inversoes = 0;

    void dividir(int inicio, int fim) {

        if (fim - inicio < 2)
            return;

        int meio = inicio + (fim - inicio) / 2;

        dividir(inicio, meio);

        dividir(meio, fim);

        intercalar(inicio, meio, fim);
    }

    void intercalar(int inicio, int meio, int fim) {

        int esquerda = inicio;
        int direita = meio;
        int posicao = inicio;

        while (
            esquerda < meio &&
            direita < fim
        ) {

            if (dados[esquerda] <= dados[direita]) {

                auxiliar[posicao++] = dados[esquerda++];

            } else {

                auxiliar[posicao++] = dados[direita++];

               

                inversoes += static_cast<uint64_t>(
                    meio - esquerda
                );
            }
        }

        while (esquerda < meio) {

            auxiliar[posicao++] = dados[esquerda++];
        }

        while (direita < fim) {

            auxiliar[posicao++] = dados[direita++];
        }

        

        copy(
            auxiliar.begin() + inicio,
            auxiliar.begin() + fim,
            dados.begin() + inicio
        );
    }

public:

    explicit MergeInversion(vector<long long> valores)
        : dados(move(valores)),
          auxiliar(dados.size()) {}

    void ordenar() {

        dividir(0, static_cast<int>(dados.size()));
    }

    void apresentar() const {

        for (size_t i = 0; i < dados.size(); i++) {

            if (i > 0)
                cout << ' ';

            cout << dados[i];
        }

        cout << '\n';

        cout << inversoes << '\n';
    }
};

int main() {

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;

    if (!(cin >> n))
        return 0;

    vector<long long> valores(n);

    for (auto &x : valores)
        cin >> x;

    MergeInversion algoritmo(move(valores));

    algoritmo.ordenar();

    algoritmo.apresentar();

    return 0;
}
