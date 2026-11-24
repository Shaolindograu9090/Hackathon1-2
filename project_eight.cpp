
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdint>

using namespace std;

class OrdenadorSelecao {

private:

    vector<long long> dados;

    uint64_t comparacoes = 0;
    uint64_t trocas = 0;

public:

    explicit OrdenadorSelecao(int tamanho) {
        dados.resize(tamanho);
    }

    void receberDados() {

        for (auto &valor : dados)
            cin >> valor;
    }

    void executar() {

        const int n = static_cast<int>(dados.size());

        for (int i = 0; i < n - 1; i++) {

            int indiceMenor = i;

            // Procura o menor elemento da região não ordenada.

            for (int j = i + 1; j < n; j++) {

                comparacoes++;

                if (dados[j] < dados[indiceMenor]) {

                    indiceMenor = j;
                }
            }

            // Troca somente quando o mínimo não está na posição atual.

            if (indiceMenor != i) {

                swap(
                    dados[i],
                    dados[indiceMenor]
                );

                trocas++;
            }
        }
    }

    void imprimirResultado() const {

        for (size_t i = 0; i < dados.size(); i++) {

            if (i > 0)
                cout << ' ';

            cout << dados[i];
        }

        cout << '\n';

        cout << comparacoes
             << ' '
             << trocas
             << '\n';
    }
};

int main() {

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;

    if (!(cin >> n))
        return 0;

    OrdenadorSelecao algoritmo(n);

    algoritmo.receberDados();

    algoritmo.executar();

    algoritmo.imprimirResultado();

    return 0;
}