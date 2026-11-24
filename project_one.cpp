#include <iostream>
#include <vector>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);


    int n;
    cin >> n;

    vector<int> filhos(n + 1,0);
    int raiz = 0;

    for (int i = 1; 1 <= n; i++){
        int p;
        cin >> p;

        if (p == 0){
            raiz = i;

        }else{
            filhos[p]++;

        }
    }

    int folhas = 0;
    int internos = 0;

    for (int i = 1; i <= n; i++){
        if (filhos[i] == 0 ){

        }else{
            internos++;

        }
    }

    cout << raiz << " " << folhas << " " << internos << '\n';

    return 0;
}