
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>

using namespace std;

class ArvoreAVL {

private:

    struct No {

        int chave;

        int frequencia = 1;

        int altura = 0;

        int totalSubarvore = 1;

        unique_ptr<No> esquerdo;
        unique_ptr<No> direito;

        explicit No(int valor)
            : chave(valor) {}
    };

    unique_ptr<No> raiz;

    

    int altura(const unique_ptr<No> &no) const {

        return no ? no->altura : -1;
    }

    int quantidade(const unique_ptr<No> &no) const {

        return no ? no->totalSubarvore : 0;
    }

    

    void atualizar(No *no) {

        if (!no)
            return;

        no->altura = 1 + max(
            altura(no->esquerdo),
            altura(no->direito)
        );

        no->totalSubarvore =
            no->frequencia +
            quantidade(no->esquerdo) +
            quantidade(no->direito);
    }

    int fatorBalanceamento(const No *no) const {

        if (!no)
            return 0;

        return altura(no->esquerdo) -
               altura(no->direito);
    }

    

    unique_ptr<No> rotacionarDireita(
        unique_ptr<No> y
    ) {

        auto x = move(y->esquerdo);

        y->esquerdo = move(x->direito);

        atualizar(y.get());

        x->direito = move(y);

        atualizar(x.get());

        return x;
    }

    

    unique_ptr<No> rotacionarEsquerda(
        unique_ptr<No> x
    ) {

        auto y = move(x->direito);

        x->direito = move(y->esquerdo);

        atualizar(x.get());

        y->esquerdo = move(x);

        atualizar(y.get());

        return y;
    }

    

    unique_ptr<No> rebalancear(
        unique_ptr<No> no
    ) {

        if (!no)
            return no;

        atualizar(no.get());

        int fator = fatorBalanceamento(no.get());

        

        if (fator > 1) {

            if (
                fatorBalanceamento(no->esquerdo.get()) < 0
            ) {

                no->esquerdo = rotacionarEsquerda(
                    move(no->esquerdo)
                );
            }

            return rotacionarDireita(move(no));
        }

       

        if (fator < -1) {

            if (
                fatorBalanceamento(no->direito.get()) > 0
            ) {

                no->direito = rotacionarDireita(
                    move(no->direito)
                );
            }

            return rotacionarEsquerda(move(no));
        }

        return no;
    }

    

    unique_ptr<No> inserir(
        unique_ptr<No> no,
        int valor
    ) {

        if (!no)
            return make_unique<No>(valor);

        if (valor == no->chave) {

            no->frequencia++;

            return rebalancear(move(no));
        }

        if (valor < no->chave) {

            no->esquerdo = inserir(
                move(no->esquerdo),
                valor
            );

        } else {

            no->direito = inserir(
                move(no->direito),
                valor
            );
        }

        return rebalancear(move(no));
    }

    No* encontrarMinimo(No *no) const {

        while (no && no->esquerdo) {

            no = no->esquerdo.get();
        }

        return no;
    }

    

    unique_ptr<No> removerEstrutural(
        unique_ptr<No> no,
        int valor
    ) {

        if (!no)
            return nullptr;

        if (valor < no->chave) {

            no->esquerdo = removerEstrutural(
                move(no->esquerdo),
                valor
            );

        } else if (valor > no->chave) {

            no->direito = removerEstrutural(
                move(no->direito),
                valor
            );

        } else {

            if (!no->esquerdo)
                return move(no->direito);

            if (!no->direito)
                return move(no->esquerdo);

            No *sucessor =
                encontrarMinimo(no->direito.get());

            no->chave = sucessor->chave;

            no->frequencia = sucessor->frequencia;

            no->direito = removerEstrutural(
                move(no->direito),
                sucessor->chave
            );
        }

        return rebalancear(move(no));
    }

    

    unique_ptr<No> remover(
        unique_ptr<No> no,
        int valor
    ) {

        if (!no)
            return nullptr;

        if (valor < no->chave) {

            no->esquerdo = remover(
                move(no->esquerdo),
                valor
            );

        } else if (valor > no->chave) {

            no->direito = remover(
                move(no->direito),
                valor
            );

        } else {

            

            if (no->frequencia > 1) {

                no->frequencia--;

                return rebalancear(move(no));
            }

            

            if (!no->esquerdo)
                return move(no->direito);

            if (!no->direito)
                return move(no->esquerdo);

            

            No *sucessor =
                encontrarMinimo(no->direito.get());

            no->chave = sucessor->chave;

            no->frequencia = sucessor->frequencia;

            

            no->direito = removerEstrutural(
                move(no->direito),
                sucessor->chave
            );
        }

        return rebalancear(move(no));
    }

    

    int selecionar(const No *no, int k) const {

        if (!no)
            return 0;

        int esquerda = no->esquerdo
            ? no->esquerdo->totalSubarvore
            : 0;

        if (k <= esquerda) {

            return selecionar(
                no->esquerdo.get(),
                k
            );
        }

        if (k <= esquerda + no->frequencia) {

            return no->chave;
        }

        return selecionar(
            no->direito.get(),
            k - esquerda - no->frequencia
        );
    }

    

    void listar(
        const No *no,
        vector<int> &resultado
    ) const {

        if (!no)
            return;

        listar(no->esquerdo.get(), resultado);

        for (int i = 0; i < no->frequencia; i++) {

            resultado.push_back(no->chave);
        }

        listar(no->direito.get(), resultado);
    }

public:

    void inserir(int valor) {

        raiz = inserir(move(raiz), valor);
    }

    void remover(int valor) {

        raiz = remover(move(raiz), valor);
    }

    int totalElementos() const {

        return quantidade(raiz);
    }

    bool consultarK(int k, int &resultado) const {

        if (k < 1 || k > totalElementos())
            return false;

        resultado = selecionar(raiz.get(), k);

        return true;
    }

    vector<int> obterOrdenados() const {

        vector<int> resultado;

        resultado.reserve(totalElementos());

        listar(raiz.get(), resultado);

        return resultado;
    }
};

int main() {

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int q;

    if (!(cin >> q))
        return 0;

    ArvoreAVL central;

    while (q--) {

        char comando;

        cin >> comando;

        if (comando == 'I') {

            int x;

            cin >> x;

            central.inserir(x);
        }

        else if (comando == 'R') {

            int x;

            cin >> x;

            central.remover(x);
        }

        else if (comando == 'K') {

            int k;

            cin >> k;

            int resultado;

            if (central.consultarK(k, resultado)) {

                cout << resultado << '\n';

            } else {

                cout << "INVALIDO\n";
            }
        }

        else if (comando == 'L') {

            vector<int> elementos =
                central.obterOrdenados();

            if (elementos.empty()) {

                cout << "VAZIA";

            } else {

                for (
                    size_t i = 0;
                    i < elementos.size();
                    i++
                ) {

                    if (i > 0)
                        cout << ' ';

                    cout << elementos[i];
                }
            }

            cout << '\n';
        }
    }

    return 0;
}
