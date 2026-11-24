
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>

using namespace std;

struct No {

    long long chave;

    unique_ptr<No> esquerdo;
    unique_ptr<No> direito;

    explicit No(long long valor)
        : chave(valor) {}
};

class ArvoreBST {

private:

    unique_ptr<No> raiz;

    void inserir(unique_ptr<No> &atual, long long valor) {

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

    int calcularAltura(const No *atual) const {

        if (!atual)
            return -1;

        return 1 + max(
            calcularAltura(atual->esquerdo.get()),
            calcularAltura(atual->direito.get())
        );
    }

    void percursoEmOrdem(
        const No *atual,
        vector<long long> &chaves
    ) const {

        if (!atual)
            return;

        percursoEmOrdem(
            atual->esquerdo.get(),
            chaves
        );

        chaves.push_back(atual->chave);

        percursoEmOrdem(
            atual->direito.get(),
            chaves
        );
    }

    void percursoPreOrdem(
        const No *atual,
        vector<long long> &resultado
    ) const {

        if (!atual)
            return;

        resultado.push_back(atual->chave);

        percursoPreOrdem(
            atual->esquerdo.get(),
            resultado
        );

        percursoPreOrdem(
            atual->direito.get(),
            resultado
        );
    }

    unique_ptr<No> reconstruir(
        const vector<long long> &chaves,
        int inicio,
        int fim
    ) {

        if (inicio > fim)
            return nullptr;

        

        int meio = inicio + (fim - inicio) / 2;

        auto novo = make_unique<No>(chaves[meio]);

        novo->esquerdo = reconstruir(
            chaves,
            inicio,
            meio - 1
        );

        novo->direito = reconstruir(
            chaves,
            meio + 1,
            fim
        );

        return novo;
    }

public:

    void inserir(long long valor) {

        inserir(raiz, valor);
    }

    int alturaOriginal() const {

        return calcularAltura(raiz.get());
    }

    vector<long long> obterChavesOrdenadas() const {

        vector<long long> chaves;

        percursoEmOrdem(raiz.get(), chaves);

        return chaves;
    }

    unique_ptr<No> construirBalanceada(
        const vector<long long> &chaves
    ) {

        return reconstruir(
            chaves,
            0,
            static_cast<int>(chaves.size()) - 1
        );
    }

    int alturaNova(const No *novaRaiz) const {

        return calcularAltura(novaRaiz);
    }

    vector<long long> obterPreOrdem(
        const No *novaRaiz
    ) const {

        vector<long long> resultado;

        percursoPreOrdem(
            novaRaiz,
            resultado
        );

        return resultado;
    }
};

int main() {

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;

    if (!(cin >> n))
        return 0;

    ArvoreBST arvore;

    for (int i = 0; i < n; i++) {

        long long valor;

        cin >> valor;

        arvore.inserir(valor);
    }

    

    int alturaAntiga = arvore.alturaOriginal();

    

    vector<long long> chaves =
        arvore.obterChavesOrdenadas();

    

    unique_ptr<No> novaRaiz =
        arvore.construirBalanceada(chaves);

    

    vector<long long> resultado =
        arvore.obterPreOrdem(novaRaiz.get());

    for (size_t i = 0; i < resultado.size(); i++) {

        if (i > 0)
            cout << ' ';

        cout << resultado[i];
    }

    cout << '\n';

    cout << alturaAntiga << ' '
         << arvore.alturaNova(novaRaiz.get())
         << '\n';

    return 0;
}
