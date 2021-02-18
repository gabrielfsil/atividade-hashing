#include "Diretorio.h"
#include "Balde.h"
#include <math.h>
#include <iostream>

Diretorio::Diretorio(int m, int b)
{

    cout << "Contruindo diretório" << endl;
    // Cria diretório com uma posições
    diretorio = new Balde *[2];
    cout << "Diretorio construido" << endl;

    // Cria o primeiro balde
    Balde *primeiro = new Balde(m);
    Balde *segundo = new Balde(m);

    // Aponta a posição do diretório para o primeiro balde
    diretorio[0] = primeiro;
    diretorio[1] = segundo;

    // Define profundidade global igual a 1
    profundidade = 1;
    Diretorio::m = m;
    tamanho = 2;
    bits = b;
}

Diretorio::~Diretorio()
{
    for (int i = 0; i < tamanho; i++)
    {
        // delete[] diretorio[i];
    }

    delete[] diretorio;
}

void Diretorio::inserir(int valor)
{

    // Aplica a função hashing
    int chave = hashing(valor);
    string pseudochave = converteEmBinario(chave, bits);

    // Obtém profundidade do diretório
    // Obtém os d bits mais a esquerda da pseudochave
    string dBits = "";

    for (int i = 0; i < profundidade; i++)
    {
        dBits = dBits + pseudochave[i];
    }

    // Acessa o balde assossiado aos d bits obtidos
    int indiceBalde = encontraBalde(dBits);
    if (indiceBalde != -1)
    {
        // Se há espaço no Balde
        if (!diretorio[indiceBalde]->estaCheio())
        {
            // Insere a pseudochave
            diretorio[indiceBalde]->inserir(pseudochave);
            
        }
        // Senão
        else
        {
            int profundidadeLocal = diretorio[indiceBalde]->getProfundidade();

            // Se D global = D local
            if (profundidade == profundidadeLocal && profundidade <= bits - 1)
            {

                // Duplica o tamanho do diretório
                duplicarDiretorio();
            }

            // Se D local < D global
            dividirBalde(pseudochave);
        }
    }else{
        cout << "Erro na Inserção!" << endl;
    }
}

void Diretorio::buscar(int valor)
{

    // Aplica a função h(k) sobre a chave k

    // Obtém a profundidade d do diretório

    // Obtém os d bits mais à esquerda da pseudochave h(k)

    // Acessa o balde associado aos d bits obtidos

    // Busca a pseudochave no balde, retornando verdadeiro caso ela seja encontrada, ou falso em caso contrário
}

void Diretorio::remover(int valor)
{
}

void Diretorio::duplicarDiretorio()
{
    // Cria um novo vetor com o dobro do tamanho
    Balde **novoDiretorio;

    novoDiretorio = new Balde *[tamanho * 2];

    // Ajusta ponteiros
    for (int a = 0; a < tamanho * 2; a++)
    {
        string dBits = converteEmBinario(a);

        int balde = encontraBalde(dBits);

        if (balde != -1)
        {
            novoDiretorio[a] = diretorio[balde];
        }
    }

    // Ajusta Profundidade
    profundidade++;

    //  Ajusta tamanho
    tamanho = tamanho * 2;

    // delete[] diretorio;

    // Atualiza o diretório;
    diretorio = novoDiretorio;
}

void Diretorio::dividirBalde(string chave)
{
    Balde *novoBalde = new Balde(m);

    // Encontra a outra posição que aponta para o mesmo balde
    string dBits = "";

    for (int i = 0; i < profundidade; i++)
    {
        dBits = dBits + chave[i];
    }

    int indiceBalde = encontraBalde(dBits);
    int indiceOutroBalde;

    for (int i = 0; i < tamanho; i++)
    {

        if (indiceBalde != i && diretorio[i] == diretorio[indiceBalde])
        {
            indiceOutroBalde = i;
            break;
        }
    }

    int profundidadeLocal = diretorio[indiceBalde]->getProfundidade();

    // Aponta para o novo balde
    diretorio[indiceOutroBalde] = novoBalde;

    // Acrescenta na profundidade local
    diretorio[indiceBalde]->setProfundidade(profundidadeLocal + 1);

    diretorio[indiceOutroBalde]->setProfundidade(profundidadeLocal + 1);

    // Redistribuir chaves
    redistribuir(indiceBalde, indiceOutroBalde, chave);
}

void Diretorio::redistribuir(int balde, int novoBalde, string chave)
{

    string dBitsBalde = converteEmBinario(balde, profundidade);
    string dBitsNovoBalde = converteEmBinario(novoBalde, profundidade);

    string *removerChaves = new string[m];

    int indiceRemver = 0;

    for (int i = 0; i < m; i++)
    {
        // Chave presente no balde antigo
        string pseudochave = diretorio[balde]->getChave(i);

        // Verifica se deve ser movida para o novo balde
        if (verificaChave(pseudochave, dBitsNovoBalde))
        {
            // Insere no novo balde
            if (diretorio[novoBalde]->inserir(pseudochave))
            {
                removerChaves[indiceRemver] = pseudochave;
                indiceRemver++;
            }
        }
    }

    for (int i = 0; i < indiceRemver; i++)
    {

        // Remove do balde antigo
        diretorio[balde]->remover(removerChaves[i]);
    }

    if (verificaChave(chave, dBitsNovoBalde))
    {
        diretorio[novoBalde]->inserir(chave);
        
    }
    else
    {
        diretorio[balde]->inserir(chave);
        
    }

    delete[] removerChaves;
}

int Diretorio::encontraBalde(string chave)
{
    for (int i = 0; i < tamanho; i++)
    {
        // cout << "Verifica balde: " << converteEmBinario(i) << " == " << chave << endl;
        if (converteEmBinario(i, profundidade) == chave)
        {
            return i;
        }
    }

    return -1;
}

int Diretorio::getProfundidade()
{
    return profundidade;
}

int Diretorio::hashing(int k)
{

    float a = (sqrt(5) - 1) / 2;
    float intPart;
    int chave = floor(m * modf(a * k, &intPart));

    return k;
}

string Diretorio::converteEmBinario(int valor)
{

    string binario = "";
    int bits = 0;
    int maxBits = profundidade + 1;

    while (valor / 2 != 0 || valor % 2 != 0)
    {

        binario = to_string(valor % 2) + binario;
        valor = valor / 2;
        bits++;
    }

    if (bits > maxBits)
    {
        for (int i = bits; i > bits - maxBits; i--)
        {

            binario.pop_back();
        }
    }
    else
    {

        for (int i = 0; i < maxBits - bits; i++)
        {

            binario = "0" + binario;
        }
    }

    // cout << binario << endl;

    for (int i = 0; i < maxBits - profundidade; i++)
    {
        binario.pop_back();
    }

    return binario;
}

string Diretorio::converteEmBinario(int valor, int tamanho)
{

    string binario = "";
    int bits = 0;
    int maxBits = tamanho;

    while (valor / 2 != 0 || valor % 2 != 0)
    {

        binario = to_string(valor % 2) + binario;
        valor = valor / 2;
        bits++;
    }

    if (bits > maxBits)
    {
        for (int i = bits; i > bits - maxBits; i--)
        {

            binario.pop_back();
        }
    }
    else
    {

        for (int i = 0; i < maxBits - bits; i++)
        {

            binario = "0" + binario;
        }
    }

    // for (int i = 0; i < maxBits - profundidade; i++)
    // {
    //     binario.pop_back();
    // }

    return binario;
}

bool Diretorio::verificaChave(string chave, string dBitsBalde)
{
    string dBits;

    for (int i = 0; i < profundidade; i++)
    {
        dBits = dBits + chave[i];
    }

    if (dBitsBalde == dBits)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Diretorio::imprimirDiretorio()
{
    cout << endl
         << "===================================" << endl
         << "             Diretório             " << endl
         << " Tamanho: " << tamanho << endl
         << " Profundidade: " << profundidade << endl
         << endl;

    for (int i = 0; i < tamanho; i++)
    {
        cout << converteEmBinario(i, profundidade) << " | " << diretorio[i] << endl;
        diretorio[i]->imprimiBalde();
    }
}