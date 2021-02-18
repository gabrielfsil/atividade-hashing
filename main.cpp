#include <string>
#include <iostream>
#include <fstream>
#include "Diretorio.h"

using namespace std;

string converteDecimalEmBinario(int valor)
{

    string binario = "";
    int bits = 0;

    while (valor / 2 != 0 || valor % 2 != 0)
    {

        binario = to_string(valor % 2) + binario;
        valor = valor / 2;
        bits++;
    }

    return binario;
}

void read_file(int input[], int tamanho, string filename)
{
    ifstream arq(filename);

    string line;
    int i = 0;

    if (arq.is_open())
    {
        while (!arq.eof() && i < tamanho)
        {
            getline(arq, line);
            input[i] = stoi(line);
            i++;
        }
    }

    arq.close();
}

void write_file(string dados, string filename)
{

    ofstream arq(filename);

    arq << dados;

    arq.close();
}

void embaralha(int vet[], int tamanho)
{
    srand(time(NULL));
    int aux;
    for (int i = 0; i < tamanho; i++)
    {
        int r = rand() % tamanho;

        aux = vet[i];
        vet[i] = vet[r];
        vet[r] = aux;
    }
}

int main()
{
    int n, m;

    cout << "============================" << endl
         << "     Hashing Extensível     " << endl
         << "      Módulo de Testes      " << endl
         << "============================" << endl
         << endl
         << endl
         << "Digite o tamanho M de cada balde: ";
    cin >> m;

    cout << "Digite a quantidade de registros que deseja inserir na tabela: ";
    cin >> n;

    string binario = converteDecimalEmBinario(n);

    int *entrada = new int[n];

    string dados;
    string dados_padronizados;
    for (int i = 0; i < n; i++)
    {
        entrada[i] = i;
    }

    embaralha(entrada, n);

    for (int i = 0; i < n; i++)
    {

        dados = dados + to_string(entrada[i]) + "\n";
        if (i > n / 2)
        {
            dados_padronizados = dados_padronizados + to_string(entrada[i]) + "\n";
            dados_padronizados = dados_padronizados + to_string(entrada[i]) + "\n";
        }
    }

    dados_padronizados.pop_back();

    // Remove quebra de linha no final
    dados.pop_back();

    write_file(dados, "input.txt");

    write_file(dados_padronizados, "input-padronizado.txt");

    srand(time(NULL));

    int bits = binario.size();

    Diretorio *diretorio = new Diretorio(m, bits);

    int resposta;

    cout << "============================" << endl
         << " Escolha uma opção digitando a tecla correspondente: " << endl
         << " [1] Inserir " << n << " registros aleatórios" << endl
         << " [2] Inserir " << n << " registros padronizados" << endl
         << " >> ";
    cin >> resposta;

    if (resposta == 1)
    {
        read_file(entrada, n, "input.txt");
    }
    else
    {
        read_file(entrada, n, "input-padronizado.txt");
    }

    for (int i = 0; i < n; i++)
    {

        diretorio->inserir(entrada[i]);
    }

    diretorio->imprimirDiretorio();

    delete diretorio;

    return 0;
}