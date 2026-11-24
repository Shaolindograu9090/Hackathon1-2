
#include <iostream>
#include <memory>
#include <vector>

using namespace std;

class CatalogoBST {

private:

    struct No {

        int chave;

        unique_ptr<No> esquerdo;
        unique_ptr<No> direito;

        explicit No(int valor)
            : chave(valor) {}
    };

    unique_ptr<No> raiz;

    bool buscar(const No *atual, int valor) const {

        while (atual != nullptr) {

            if (valor == atual->chave)
                return true;

            if (valor < atual->chave) {

                atual = atual->esquerdo.get();

            } else {

                atual = atual->direito.get();
            }
        }

        return false;
    }

    void inserir(
        unique_ptr<No> &atual,
        int valor
    ) {

        if (!atual) {

            atual = make_unique<No>(valor);

            return;
        }

        if (valor < atual->chave) {

            inserir(atual->esquerdo, valor);

        } else if (valor > atual->chave) {

            inserir(atual->direito, valor);
        }
    }

    No* encontrarMinimo(No *atual) const {

        while (atual && atual->esquerdo) {

            atual = atual->esquerdo.get();
        }

        return atual;
    }

    void remover(
        unique_ptr<No> &atual,
        int valor
    ) {

        if (!atual)
            return;

        if (valor < atual->chave) {

            remover(atual->esquerdo, valor);

        } else if (valor > atual->chave) {

            remover(atual->direito, valor);

        } else {

            

            if (!atual->esquerdo) {

                atual = move(atual->direito);

            }

            

            else if (!atual->direito) {

                atual = move(atual->esquerdo);

            }

            

            else {

                No *sucessor =
                    encontrarMinimo(atual->direito.get());

                atual->chave = sucessor->chave;

                remover(
                    atual->direito,
                    sucessor->chave
                );
            }
        }
    }

    void consultarFaixa(
        const No *atual,
        int inicio,
        int fim,
        vector<int> &resultado
    ) const {

        if (!atual)
            return;

        

        if (atual->chave > inicio) {

            consultarFaixa(
                atual->esquerdo.get(),
                inicio,
                fim,
                resultado
            );
        }

       

        if (
            atual->chave >= inicio &&
            atual->chave <= fim
        ) {

            resultado.push_back(atual->chave);
        }

        

        if (atual->chave < fim) {

            consultarFaixa(
                atual->direito.get(),
                inicio,
                fim,
                resultado
            );
        }
    }

public:

    void inserir(int valor) {

        inserir(raiz, valor);
    }

    void remover(int valor) {

        remover(raiz, valor);
    }

    bool existe(int valor) const {

        return buscar(raiz.get(), valor);
    }

    vector<int> faixa(int inicio, int fim) const {

        vector<int> resultado;

        consultarFaixa(
            raiz.get(),
            inicio,
            fim,
            resultado
        );

        return resultado;
    }
};

int main() {

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int q;

    if (!(cin >> q))
        return 0;

    CatalogoBST catalogo;

    while (q--) {

        char comando;

        cin >> comando;

        if (comando == 'I') {

            int x;

            cin >> x;

            catalogo.inserir(x);
        }

        else if (comando == 'R') {

            int x;

            cin >> x;

            catalogo.remover(x);
        }

        else if (comando == 'B') {

            int x;

            cin >> x;

            cout << (
                catalogo.existe(x) ? "SIM" : "NAO"
            ) << '\n';
        }

        else if (comando == 'F') {

            int a, b;

            cin >> a >> b;

            vector<int> resultado =
                catalogo.faixa(a, b);

            if (resultado.empty()) {

                cout << "VAZIA";

            } else {

                for (size_t i = 0; i < resultado.size(); i++) {

                    if (i > 0)
                        cout << ' ';

                    cout << resultado[i];
                }
            }

            cout << '\n';
        }
    }

    return 0;
}
