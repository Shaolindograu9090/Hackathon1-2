
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>

using namespace std;

class OrdenadorMerge {

private:

    vector<int> dados;
    vector<int> auxiliar;

    void dividir(int inicio, int fim) {

        if (fim - inicio < 2)
            return;

        int meio = inicio + (fim - inicio) / 2;

        dividir(inicio, meio);

        dividir(meio, fim);

        intercalar(inicio, meio, fim);
    }

    void intercalar(int inicio, int meio, int fim) {

        int i = inicio;
        int j = meio;
        int k = inicio;

        while (i < meio && j < fim) {

            if (dados[i] <= dados[j]) {

                auxiliar[k++] = dados[i++];

            } else {

                auxiliar[k++] = dados[j++];
            }
        }

        while (i < meio)
            auxiliar[k++] = dados[i++];

        while (j < fim)
            auxiliar[k++] = dados[j++];

        copy(
            auxiliar.begin() + inicio,
            auxiliar.begin() + fim,
            dados.begin() + inicio
        );
    }

public:

    explicit OrdenadorMerge(vector<int> valores)
        : dados(move(valores)),
          auxiliar(dados.size()) {}

    void ordenar() {

        dividir(
            0,
            static_cast<int>(dados.size())
        );
    }

    const vector<int>& obterDados() const {

        return dados;
    }
};

struct No {

    int chave;
    int tamanhoSubarvore;

    unique_ptr<No> esquerdo;
    unique_ptr<No> direito;

    No(int valor, int tamanho)
        : chave(valor),
          tamanhoSubarvore(tamanho) {}
};

class IndiceRanking {

private:

    unique_ptr<No> raiz;

    unique_ptr<No> construir(
        const vector<int> &dados,
        int inicio,
        int fim
    ) {

        if (inicio >= fim)
            return nullptr;

        

        int meio = inicio + (fim - inicio - 1) / 2;

        auto atual = make_unique<No>(
            dados[meio],
            fim - inicio
        );

        atual->esquerdo = construir(
            dados,
            inicio,
            meio
        );

        atual->direito = construir(
            dados,
            meio + 1,
            fim
        );

        return atual;
    }

    int consultar(const No *atual, int valor) const {

        int anteriores = 0;

        while (atual != nullptr) {

            int tamanhoEsquerdo =
                atual->esquerdo
                ? atual->esquerdo->tamanhoSubarvore
                : 0;

            if (valor == atual->chave) {

                return anteriores + tamanhoEsquerdo + 1;
            }

            if (valor < atual->chave) {

                atual = atual->esquerdo.get();

            } else {

                

                anteriores += tamanhoEsquerdo + 1;

                atual = atual->direito.get();
            }
        }

        return -1;
    }

public:

    explicit IndiceRanking(const vector<int> &dados) {

        raiz = construir(
            dados,
            0,
            static_cast<int>(dados.size())
        );
    }

    int posicao(int pontuacao) const {

        return consultar(
            raiz.get(),
            pontuacao
        );
    }
};

int main() {

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;

    if (!(cin >> n))
        return 0;

    vector<int> pontuacoes(n);

    for (auto &valor : pontuacoes)
        cin >> valor;

   

    OrdenadorMerge ordenador(
        move(pontuacoes)
    );

    ordenador.ordenar();

   

    IndiceRanking ranking(
        ordenador.obterDados()
    );

    

    int q;

    cin >> q;

    while (q--) {

        int consulta;

        cin >> consulta;

        cout << ranking.posicao(consulta) << '\n';
    }

    return 0;
}
