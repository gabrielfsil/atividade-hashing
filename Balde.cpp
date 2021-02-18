#include "Balde.h"
#include <string>
#include <iostream>

Balde::Balde()
{
    pseudochave = new string[1];
    indice = 0;
    tamanho = 1;
    profundidade = 1;
    cout << "Construindo balde" << endl;
}

Balde::Balde(int m)
{

    pseudochave = new string[m];
    indice = 0;
    tamanho = m;
    profundidade = 1;
}

Balde::~Balde()
{

    delete[] pseudochave;
}

int Balde::getProfundidade()
{
    return profundidade;
}

void Balde::setProfundidade(int profundidade)
{
    Balde::profundidade = profundidade;
}

bool Balde::estaCheio()
{

    if (indice == tamanho)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Balde::estaVazio()
{

    if (indice == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int Balde::buscar(string chave)
{

    for (int i = 0; i < indice; i++)
    {

        if (chave == pseudochave[i])
        {
            return i;
        }
    }

    // Chave não está no balde
    return -1;
}

string Balde::getChave(int i)
{

    return pseudochave[i];
}

bool Balde::inserir(string chave)
{

    if (!estaCheio())
    {

        pseudochave[indice] = chave;
        indice++;

        // Inserção concluída
        return true;
    }
    else
    {

        // Balde está cheio
        // Não foi possível inserir a chave
        return false;
    }
}

bool Balde::verificaChave(string chave)
{

    string dBitsChave, dBitsBalde;

    for (int i = 0; i < profundidade; i++)
    {
        dBitsChave = dBitsChave + chave[i];
        dBitsBalde = dBitsBalde + pseudochave[0][i];
    }

    if (dBitsBalde == dBitsChave)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Balde::remover(string chave)
{

    bool moveParaEquerda = false;

    for (int i = 0; i < indice; i++)
    {

        if (pseudochave[i] == chave)
        {
            pseudochave[i] = "";
            moveParaEquerda = true;
        }

        if (moveParaEquerda && i < indice - 1)
        {
            pseudochave[i] = pseudochave[i + 1];
        }
    }

    // Coloca uma string vazia na posição que ficou repetida no balde
    if (moveParaEquerda)
        pseudochave[indice - 1] = "";

    indice--;
}

string Balde::converteEmBinario(int valor)
{

    string binario = "";
    int bits = 0;
    int maxBits = profundidade;

    while (valor / 2 != 0 || valor % 2 != 0)
    {

        binario = to_string(valor % 2) + binario;
        valor = valor / 2;
        bits++;
    }

    for (int i = 0; i < maxBits - bits; i++)
    {

        binario = "0" + binario;
    }

    return binario;
}

void Balde::imprimiBalde()
{
    cout << "       Profundidade: " << profundidade << endl;
    for (int i = 0; i < tamanho; i++)
    {
        cout << "       " << i << " - " << pseudochave[i] << endl;
    }
}