
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <cstdint>

using namespace std;

class QuickSortTridimensional {

private:

    vector<long long> &dados;

    mt19937_64 gerador;

    pair<int, int> particionar(int inicio, int fim) {

        uniform_int_distribution<int> distribuicao(
            inicio, fim
        );

        

        long long pivo = dados[distribuicao(gerador)];

        int menor = inicio;
        int atual = inicio;
        int maior = fim;

       

        while (atual <= maior) {

            if (dados[atual] < pivo) {

                swap(dados[menor], dados[atual]);

                menor++;
                atual++;

            } else if (dados[atual] > pivo) {

                swap(dados[atual], dados[maior]);

                maior--;

            } else {

                atual++;
            }
        }

        return {menor, maior};
    }

    void executar(int inicio, int fim) {

        while (inicio < fim) {

            auto [limiteMenor, limiteMaior] =
                particionar(inicio, fim);

            int tamanhoEsquerda =
                limiteMenor - inicio;

            int tamanhoDireita =
                fim - limiteMaior;

            

            if (tamanhoEsquerda < tamanhoDireita) {

                if (inicio < limiteMenor - 1) {

                    executar(inicio, limiteMenor - 1);
                }

                

                inicio = limiteMaior + 1;

            } else {

                if (limiteMaior + 1 < fim) {

                    executar(limiteMaior + 1, fim);
                }

                fim = limiteMenor - 1;
            }
        }
    }

public:

    explicit QuickSortTridimensional(
        vector<long long> &vetor,
        uint64_t semente
    )
        : dados(vetor), gerador(semente) {}

    void ordenar() {

        if (!dados.empty()) {

            executar(
                0,
                static_cast<int>(dados.size()) - 1
            );
        }
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

    

    constexpr uint64_t SEMENTE = 0xC0FFEE2026ULL;

    QuickSortTridimensional algoritmo(
        valores,
        SEMENTE
    );

    algoritmo.ordenar();

    for (size_t i = 0; i < valores.size(); i++) {

        if (i > 0)
            cout << ' ';

        cout << valores[i];
    }

    cout << '\n';

    return 0;
}
