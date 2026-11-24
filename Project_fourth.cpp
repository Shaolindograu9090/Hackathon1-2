#include <iostream>
using namespace std;

struct No {
    int chave;
    No* esq;
    No* dir;


    No(int valor){
        chave = valor;
        esq = nullptr;
        dir = nullptr;
    }
};

void inserir(No*& raiz, int valor) {
    if (raiz == nullptr) {
        raiz = new No(valor);
    return;
}

No* atual = raiz;

while (true) {
    if (valor < atual->chave) {
        if (atual->esq == nullptr) {
            atual->esq = new No(valor);
            return;
        }
        atual = atual->esq;
    } else if (valor > atual->chave) {
        if (atual->dir == nullptr) {
            atual->dir = new No(valor);
            return;
        }
    }
    atual = atual->dir;
     } else {
            return;
        }
    }
}

int buscar(No* raiz, int valor) {
    int profundidade = 0;
    No* atual = raiz;

    while (atual != nullptr){

        if (valor == atual->chave) {
            return profundidade;
        } else if (valor < atual->chave) {
            atual = atual->esq;
        } else {
            atual = atual->dir;
        }
        profundidade++;
    }

    return -1; 

}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    No* raiz = nullptr;

    for (int i = 0; i < n; ++i) {
        int valor;
        cin >> valor;
        inserir(raiz, valor);
    }

    int q;
    cin >> q;

    for (int i = 0; i < q; ++i) {
        int valor;
        cin >> valor;
        int profundidade = buscar(raiz, valor);
        cout << profundidade << '\n';
    }

    return 0;
}