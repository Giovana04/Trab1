#include <iostream>
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
    bool jogar = true;

    inicializaLista(deck);

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
        player[i].vitorias = 0;
        player[i].perdas = 0;
    }

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

    while(jogar == true){

        system("cls");
        
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

        for (int i = 0; i < n_jogadores; i++)
        {
            for (int j = 0; j < 22; j++)
            {
                player[i].mao[j].valor = 0;
                player[i].mao[j].naipe = '0';
                player[i].total = 0;
            }
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

        system("cls");
        for (int i = 0; i < n_jogadores; i++)
        {
            
            if (i == n_jogadores - 1)
            {
                cout << player[i].nome << ": " << player[i].mao[0].valor << player[i].mao[0].naipe << endl << endl;
                cout << "Esta e uma das cartas do Dealer, " << " ao terminar de ver pressione qualquer tecla, em seguida 'enter' " << endl;
                cin >> resposta;
            }

            else{
                print_mao(player[i], 2);
                cout << "Player " << player[i].nome << ", ao terminar pressione qualquer tecla, em seguida 'enter' " << endl;
                cin >> resposta; 
            }
            system("cls");
        }

        // Loop para permitir que os jogadores comprem mais cartas ou parem
        for (int i = 0; i < n_jogadores - 1; i++) {
            int j = 0;
            system("cls");
            print_mao(player[i], 2);
            while (player[i].total <= 21 && desejaComprarMais(player[i]) == true) {
                system("cls");
                j++;
                compra(deck, &player[i], 1+j);
                print_mao(player[i], 2+j);
                deck = pop(deck);
            }
        }

        if (player[n_jogadores-1].total < 17)
        {
            if (player[n_jogadores-1].total < 10)
            {
                compra(deck, &player[n_jogadores-1], n_jogadores-1);
            }
            compra(deck, &player[n_jogadores-1], n_jogadores-1);
        }
        
        system("cls");

        for (int i = 0; i < n_jogadores - 1; i++)
        {

            cout << "Dealer: " << player[n_jogadores-1].total << endl << endl << player[i].nome << ": " << player[i].total << endl << endl;
            if (player[i].total > 21) {
                player[i].perdas += 1;
                cout << player[i].nome << " ultrapassou 21 e perdeu!" << endl << endl << "                 -----------------------------" << endl;
            }
            else if(player[i].total < player[n_jogadores-1].total && player[n_jogadores-1].total <= 21){
                player[i].perdas += 1;
                cout << player[i].nome << " nao alcancou o valor minimo e perdeu!" << endl << endl << "                 -----------------------------" << endl;
            }
            else{
                player[i].vitorias += 1;
                cout << "Parabens!" << endl << endl << "                 -----------------------------" << endl << endl;
            }
        }

        cout << "Mao do Dealer: " << endl << endl;
        int i = 0;
        while (player[n_jogadores-1].mao[i].valor != 0;)
        {
            print_mao(player[n_jogadores-1], 0+i);
        }
        
        

        cout << "Placar! " << endl << endl;
        for (int i = 0; i < n_jogadores - 1; i++)
        {
            cout << player[i].nome << endl << "Vitorias: " << player[i].vitorias << endl <<  "Derrotas: " << player[i].perdas << endl << endl;
        }

        char jo;
        cout << " Deseja jogar de novo? (s/n) ";
        cin >> jo;
        if (jo == 's' || jo == 'S')
        {
            jogar = true;
        }
        else{
            jogar = false;
        }

        
    }

}
