#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "operations.h"

#define NUM_PARTICIPANTES 2

int main()
{
    Palpites participantes[NUM_PARTICIPANTES];
    Tabela tabela;

    int opcao;

    // Carregar a tabela inicial
    atualizarTabela(&tabela);

    // Primeira vez utilizando o programa, cadastrar arquivo de palpites (caso ja tenha cadastro apenas remova)
    cadastrarPalpites(participantes, NUM_PARTICIPANTES);

    do
    {
        printf("\n=== MENU ===\n");
        printf("1. Mostrar palpites\n");
        printf("2. Mostrar tabela\n");
        printf("3. Atualizar tabela\n");
        printf("4. Ver pontuacao dos Participantes\n");
        printf("5. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            carregarPalpites();
            break;
        case 2:
            mostrarTabela(tabela);
            break;
        case 3:
            atualizarTabela(&tabela);
            printf("Tabela atualizada com sucesso!\n");
            break;
        case 4:
            compararPalpites(participantes, tabela);
            break;
        case 5:
            printf("Saindo...\n");
            break;
        default:
            printf("Opcao invalida!\n");
            break;
        }

        sleep(2);

    } while (opcao != 5);

    return 0;
}
