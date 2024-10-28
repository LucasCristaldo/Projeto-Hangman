#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "forca.h"

// VARIAVEIS GLOBAIS.

// Dizendo que meu array inicia com 20 espaços [0 até 19].
char palavrasecreta[TAMANHO_DA_PALAVRA];
// Criei um array vazio, com 26 espaço para todas as letras do alfabeto
char chutes[26];
// Toda vez que eu der um chute, a minha tentativa irá aumentar, por isso, scanf(" %c") na ordem, fica em ultimo antes de sair do loop,
// Ficando apenas na frente, chutes[tentativa] == meu_chute e tentativa++
int chutesdados = 0;

int qtd_palavra;


void abertura()
{
    printf("==================================\n");
    printf("=             Forca              =\n");
    printf("==================================\n");
}

// Ela me retorna algo, então tenho que específica o tipo da função.
int jachutou(char letra)
{
    int achou = 0;

    for (int j = 0; j < chutesdados; j++)
    {
                
        if (chutes[j] == letra)
        {
            achou = 1;
            break; 
        }
    }

    return achou;
}

// Um array já é um ponteiro de fabrica, printf("%d", chutes) -> exibe o endereço da memoria (do primeiro elemento)
void chuta()
{
        char chute;
        printf("\nDigite seu chute: ");
        scanf(" %c", &chute); // Quando for char, precisa de um espaço, senão o computador acha que o ENTER faz parte.

        chutes[chutesdados] = chute;
        chutesdados++;
        
}


void desenhaforca()
{
        for (int i = 0; i < strlen(palavrasecreta); i++)
        {
            
            
            int achou = jachutou(palavrasecreta[i]);

            if (achou)
            {
                printf("%c", palavrasecreta[i]);
            }
            else
            {
                printf("_");
            }
            

        }
        
        printf("\n");

}

void adicionapalavra()
{
    char quer;

    printf("Você deseja adicionar uma nova palavra no jogo ? [S/N]");
    scanf(" %c", &quer);

    if (quer == 'S')
    {
        char novapalavra[TAMANHO_DA_PALAVRA];
        printf("Qual é a nova palavra");
        scanf("%s", novapalavra);

        FILE* f;

        f = fopen("C:\\Users\\lucas\\ProjetoC\\C\\palavra.txt", "r+");

        if (f == 0)
        {
            printf("Desculpe, banco de dados nao disponivel\n\n");
            exit(1);
        }

        int qtd;
        fscanf(f, "%d", &qtd);
        qtd++;

        fseek(f, 0, SEEK_SET);
        fprintf(f, "%d", qtd);

        fseek(f, 0, SEEK_END);
        fprintf(f, "\n%s", novapalavra);

        fclose(f);

    }


}



void escolhepalavra()
{   
    // Ele me retorna o endereço, colocando o "*", retorna o que tem dentro.
    FILE* f;

    f = fopen("C:\\Users\\lucas\\ProjetoC\\C\\palavra.txt", "r");
    if (f == 0)
    {
        printf("Desculpe, banco de dados nao disponivel\n\n");
        exit(1);

    }


    int quantidadedepalavra;
    // Pego a quantidade de palavreas aqui, porque a primeira linha do meu arquivo é quantidade de palavras;
    fscanf(f, "%d", &quantidadedepalavra);

    qtd_palavra = quantidadedepalavra;

    srand(time(0));
    int randomico = rand() % quantidadedepalavra;

    for(int i = 0; i <= randomico; i++)
    {
        fscanf(f, "%s", palavrasecreta);
    }


    // Tudo que abre, tem que fechar.
    fclose(f);

    

    // Função para colocar char/string em um array
    //sprintf(palavrasecreta, "MELANCIA");

}

int enforcou()
{
    // Inicia valendo 0
    int erros = 0;

    for (int i = 0; i < chutesdados; i++)
    {
        int existe = 0;


        for (int j = 0; j < strlen(palavrasecreta); j++)
        {
            
            if (chutes[i] == palavrasecreta[j])
            {

                existe = 1;
                break;

            }

        }


        if (!existe) erros++;

    }

    // Ele retorna false ou true
    return erros >= 5;


}

/*int acertou()
{
    for (int i = 0; i < chutesdados; i++)
    {
        if (!jachutou(palavrasecreta[i]))
        {   
            // Testa todas as letras para ver se ja foram chutadas, senão foram, irá repetir o código até que o jogador perca ou ganhe
            return 0;
        }
    }

    // Quando todas as letras já foram testadas, irá retorna 1 [verdadeiro].
    return 1;
    
}*/

int acertou() {
    for (int i = 0; i < strlen(palavrasecreta); i++) 
    {
        if (!jachutou(palavrasecreta[i])) 
        {
            return 0; // Se encontrar uma letra da palavra secreta que não foi chutada
        }
    }
    return 1; // Se todas as letras foram chutadas
}



int main()
{


    // Palavra secreta recebe melancia | palavresecreta = melancia;
    //sprintf(palavrasecreta, "MELANCIA"); 
    // Foi para a função abaixo
    escolhepalavra();

    // Exibindo no terminal o que está dentro do array
    //printf("%s", palavrasecreta);

    // Viraram funções

    //int acertou = 0;
    //int enforcou = 0;

 

    abertura();
    
    // Do e While, Ele roda o loop pelo menos uma única vez. Enquanto o while pode passar batido.
    do
    {

        desenhaforca();

        // Captura um novo chute
        chuta();
        


        /*
        for (int i = 0; i < strlen(palavrasecreta); i++)
        {   // Strlen -> Pego o tamanho array de char/string.
            // Preicso da biblioteca string.h.

            if (palavrasecreta[i] == chute)
            {
                printf("\nNa posicao %d tem essa letra %d", i, chute);
            }
        }
        */

    // Se ele não acertou e se ele não errou o suficiente [5 vezes], ele poderá continuar tentando até acertar.
    } while (!acertou() && !enforcou());
    

    if (acertou())
    {
        printf("Parabens! Resposta correta era: %s\n\n", palavrasecreta);   
    } 
    else
    {
        printf("Errou! Resposta correta era: %s\n\n", palavrasecreta);   
    }

    

    printf("Obrigado por jogar!\n");
    printf("Quantidade de palavra: %d", qtd_palavra);

    adicionapalavra();

}