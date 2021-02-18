#ifndef BALDE_H
#define BALDE_H
#include <string>

using namespace std;

class Balde{

public:
    Balde();
    Balde(int m);
    ~Balde();
    bool inserir(string chave);
    bool remover(string chave);
    int buscar(string chave);
    string getChave(int i);
    int getProfundidade();
    void setProfundidade(int profundidade);
    bool estaCheio();
    bool estaVazio();
    bool verificaChave(string chave);
    void imprimiBalde();

private:
    string *pseudochave;
    int profundidade;
    int indice;
    int tamanho;
    string converteEmBinario(int valor);
};

#endif // BALDE_H