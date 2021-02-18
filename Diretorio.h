#include "Balde.h"
#include <string>

using namespace std;

class Diretorio
{
public:
    Diretorio(int m, int b);
    ~Diretorio();
    void inserir(int valor);
    void buscar(int valor);
    void remover(int valor);
    int getProfundidade();
    void setProfundidade(int profundidade);
    void imprimirDiretorio();

private:
    int profundidade;
    int tamanho;
    Balde **diretorio;
    int m;
    int bits;

    void duplicarDiretorio();
    void dividirBalde(string chave);
    int hashing(int k);
    int encontraBalde(string chave);
    string converteEmBinario(int valor);
    string converteEmBinario(int valor, int tamanho);
    bool verificaChave(string chave, string dBitsBalde);
    void redistribuir(int balde, int novoBalde, string chave);
};