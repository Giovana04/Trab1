#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

struct carta
{
    string naipe;
    int valor;
};
struct jogador
{
	char acao;
	carta mao[22];
	int total;
	string nome;
	int vitorias;
	int perdas;
};
struct baralho
{
    int valor;
    string nipe;
    baralho *link;
};

baralho *inicializaLista(baralho *L) {
	return NULL;
};

baralho *PUSH(baralho *L, int v, string x) {
	baralho *N;

	N = new baralho;
	N->valor = v;
	N->nipe = x;

    N->link = L;
	
	L = N;
	return (L);
}

baralho *pop(baralho *l)
{
	baralho *temp;
	if (l != nullptr)
	{
		temp = l;
		l = l->link;
		delete temp;
	}
	return(l);		
}

void puts(baralho* dek) {
	baralho *P;
	P = dek;

	while(P != NULL) {
		printf("carta : %d %s \n", P->valor, (P->nipe).c_str());
		P = P->link;
	}	
}


void compra(baralho *D, jogador *j, int i)
{
	(*j).mao[i].valor = D->valor;
	(*j).mao[i].naipe = D->nipe;
	(*j).total += D->valor;
	
}

void print_mao(jogador j, int size)
{
    for (int i = 0; i < size; i++)
    {
        cout << j.nome << ": " << j.mao[i].valor << j.mao[i].naipe << endl; 
    }
	cout << "total: " << j.total << endl << endl;
    
}

bool desejaComprarMais(jogador& player) {
    char resposta;
    cout << player.nome << ", deseja comprar mais uma carta? (s/n): ";
    cin >> resposta;
    return resposta == 's' || resposta == 'S';
}
