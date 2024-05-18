#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstdlib>
#include "baralho.h"
using namespace std;

int main()
{
    srand(time(nullptr));
    
    carta cartas[52];
    
    baralho *deck;
    string naipe, aux;
    int n, k = 0, temp, rand1, rand2;
    
    inicializaLista(deck);
    
    // gera as cartas
    for (int i = 0; i < 4; i++)
    {
        if (i == 0)
        {
            naipe = " ouros";
        }else if (i == 1)
        {
            naipe = " paus";
        }else if (i ==2)
        {
            naipe = " espadas";
        }else if (i == 3)
        {
            naipe = " copas";
        }
        for (int j = 1; j < 14; j++, k++)
        {
            if (j >= 10)
            {
                n = 10;
                cartas[k].valor = n;
                cartas[k].naipe = naipe;
            }else{
                cartas[k].valor = j;
                cartas[k].naipe = naipe;
            }
        }
    }

    // randomiza
    for (int i = 0; i < 104; i++)
    {
        rand1 = rand() % 52;
        rand2 = rand() % 52;
                
        temp = cartas[rand1].valor;
        aux = cartas[rand1].naipe;
        
        cartas[rand1].naipe = cartas[rand2].naipe;
        cartas[rand2].naipe = aux;
        
        cartas[rand1].valor = cartas[rand2].valor;
        cartas[rand2].valor = temp;
    }

    for (int i = 0; i < 52; i++)
    {
        deck = PUSH(deck, cartas[i].valor, cartas[i].naipe);
    }    

    
    int n_jogadores;
    cout << "Quantidade de jogadores? ";
    cin >> n_jogadores;
    n_jogadores += 1;
    jogador player[n_jogadores];
    player[n_jogadores-1].nome = "Dealer";
    player[n_jogadores-1].total = 0;

    for (int i = 0; i < n_jogadores - 1; i++)
    {
        player[i].total = 0;
        cout << "Qual o nome do player " << i+1 << "? ";
        cin >> player[i].nome;
    }

    for (int i = 0; i < 2; i++)
    {
        int nj = n_jogadores;
        while (nj--)
        {
            compra(deck, &player[nj], i);
            deck = pop(deck);    
        }    
    }

    char resposta;

    for (int i = 0; i < n_jogadores; i++)
    {
        system("cls");
        print_mao(player[i], 2);
        cout << "Player " << player[i].nome << " ao terminar pressione qualquer tecla, em seguida 'enter' " << endl;
        cin >> resposta; 
    }


    while (player[n_jogadores-1].total < 17)
    {
        for (int i = 0; player[i].total < 21 && player[i].acao != 'p' && i < n_jogadores; i++)
        {
            print_mao(player[i], 3);
            cout << player[i].nome << "deseja para(p) ou comprar(c): ";  
            cin >> player[i].acao;
            if (player[i].acao == 'c')
            {
                
            }
            
        }
        
    }
    

    







    
    
    
}
