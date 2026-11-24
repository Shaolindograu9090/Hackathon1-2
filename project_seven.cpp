
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <stack>

using namespace std;

class ArvoreBinaria {

private:

    struct No {
        int esquerdo = 0;
        int direito = 0;
    };

    struct Resultado {
        int altura = -1;
        int maiorDesequilibrio = 0;
        bool balanceada = true;
    };

    vector<No> nos;
    vector<Resultado> resultados;

    int raiz;
    int quantidade;

public:

    ArvoreBinaria(int n, int r)
        : quantidade(n), raiz(r) {

        nos.resize(n + 1);
        resultados.resize(n + 1);
    }

    void construir() {

        for (int i = 1; i <= quantidade; i++) {

            cin >> nos[i].esquerdo
                >> nos[i].direito;
        }
    }

    void diagnosticar() {

        if (quantidade == 0) {
            cout << "SIM\n0\n";
            return;
        }

        

        stack<pair<int, bool>> percurso;

        percurso.push({raiz, false});

        while (!percurso.empty()) {

            auto [atual, processado] = percurso.top();

            percurso.pop();

            if (atual == 0)
                continue;

            if (!processado) {

                

                percurso.push({atual, true});

                percurso.push({
                    nos[atual].direito, false
                });

                percurso.push({
                    nos[atual].esquerdo, false
                });

                continue;
            }

            

            Resultado esquerda =
                nos[atual].esquerdo != 0
                ? resultados[nos[atual].esquerdo]
                : Resultado{};

            Resultado direita =
                nos[atual].direito != 0
                ? resultados[nos[atual].direito]
                : Resultado{};

            

            int diferenca = abs(
                esquerda.altura - direita.altura
            );

            

            resultados[atual].altura =
                1 + max(
                    esquerda.altura,
                    direita.altura
                );

            .

            resultados[atual].maiorDesequilibrio =
                max({
                    diferenca,
                    esquerda.maiorDesequilibrio,
                    direita.maiorDesequilibrio
                });

            

            resultados[atual].balanceada =
                diferenca <= 1 &&
                esquerda.balanceada &&
                direita.balanceada;
        }

       .

        const Resultado &resposta = resultados[raiz];

        cout << (resposta.balanceada ? "SIM" : "NAO")
             << '\n';

        cout << resposta.maiorDesequilibrio
             << '\n';
    }
};

int main() {

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, raiz;

    if (!(cin >> n >> raiz))
        return 0;

    ArvoreBinaria arvore(n, raiz);

    arvore.construir();

    arvore.diagnosticar();

    return 0;
}
