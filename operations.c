#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "operations.h"

#define NUM_PARTICIPANTES 2

Palpites lerPalpites(const char *nomeArquivo)
{
    Palpites palpite;
    FILE *arq;
    arq = fopen(nomeArquivo, "r");
    if (arq == NULL)
    {
        printf("Erro ao abrir o arquivo\n");
        exit(1);
    }

    // Loop para ler os 8 palpites
    for (int i = 0; i < 8; i++)
    {
        char buffer[400]; // Buffer para armazenar o palpite atual
        // Ler uma linha do arquivo
        if (fgets(buffer, sizeof(buffer), arq) == NULL)
        {
            printf("Erro ao ler o arquivo\n");
            exit(1);
        }
        // Remover o caractere de nova linha, se houver
        if (strchr(buffer, '\n') == NULL)
        {
            printf("Tamanho do buffer insuficiente\n");
            exit(1);
        }
        *strchr(buffer, '\n') = '\0'; // Substituir '\n' por '\0'

        // Armazenar o palpite no campo correspondente
        switch (i)
        {
        case 0:
            strcpy(palpite.p1, buffer);
            break;
        case 1:
            strcpy(palpite.p2, buffer);
            break;
        case 2:
            strcpy(palpite.p3, buffer);
            break;
        case 3:
            strcpy(palpite.p4, buffer);
            break;
        case 4:
            strcpy(palpite.p17, buffer);
            break;
        case 5:
            strcpy(palpite.p18, buffer);
            break;
        case 6:
            strcpy(palpite.p19, buffer);
            break;
        case 7:
            strcpy(palpite.p20, buffer);
            break;
        default:
            break; // Não deve ocorrer
        }
    }

    fclose(arq);

    return palpite;
}

void obterNomeUsuario(char *nomeUsuario)
{
    printf("Digite o seu nome: ");
    fgets(nomeUsuario, 40, stdin);                  // Usar fgets para ler o nome do participante
    nomeUsuario[strcspn(nomeUsuario, "\n")] = '\0'; // Remover o caractere de nova linha
}

void cadastrarPalpites(Palpites participantes[], int quantidade)
{
    char nomeUsuario[40]; // Variável para armazenar o nome do usuário
    char nomeArquivo[50]; // Cria uma string para o nome do arquivo com base no nome do usuário

    // Salvar os dados em um arquivo
    FILE *arq = fopen("dados_participantes.txt", "wb");
    if (arq == NULL)
    {
        printf("Erro ao abrir o arquivo para salvar os dados\n");
        exit(1);
    }

    for (int i = 0; i < quantidade; i++)
    {
        obterNomeUsuario(nomeUsuario);
        sprintf(nomeArquivo, "%s.txt", nomeUsuario);
        participantes[i] = lerPalpites(nomeArquivo);
        strcpy(participantes[i].nome, nomeUsuario);
        participantes[i].pontuacao = 0;
    }

    fwrite(participantes, sizeof(Palpites), NUM_PARTICIPANTES, arq);
    fclose(arq);
}

void carregarPalpites()
{
    Palpites participantes[NUM_PARTICIPANTES];

    // Carregar os dados do arquivo
    FILE *arq = fopen("dados_participantes.txt", "rb");
    if (arq == NULL)
    {
        printf("Erro ao abrir o arquivo para carregar os dados\n");
        exit(1);
    }
    fread(participantes, sizeof(Palpites), NUM_PARTICIPANTES, arq);
    fclose(arq);

    for (int i = 0; i < NUM_PARTICIPANTES; i++)
    {
        // Ler o nome do participante do arquivo
        fscanf(arq, "Participante: %[^\n]\n", participantes[i].nome);

        // Ler os palpites do participante do arquivo
        fread(&participantes[i], sizeof(Palpites), 1, arq);

        // Utilizar os dados carregados
        printf("Participante %s:\n", participantes[i].nome);
        printf("\n");
        printf("Palpite 1: %s\n", participantes[i].p1);
        printf("Palpite 2: %s\n", participantes[i].p2);
        printf("Palpite 3: %s\n", participantes[i].p3);
        printf("Palpite 4: %s\n", participantes[i].p4);
        printf("Palpite 17: %s\n", participantes[i].p17);
        printf("Palpite 18: %s\n", participantes[i].p18);
        printf("Palpite 19: %s\n", participantes[i].p19);
        printf("Palpite 20: %s\n", participantes[i].p20);
        printf("\n");
    }
}

void atualizarTabela(Tabela *tabela)
{

    strcpy(tabela->p1, "santos");
    strcpy(tabela->p2, "sao paulo");
    strcpy(tabela->p3, "palmeiras");
    strcpy(tabela->p4, "corinthians");
    strcpy(tabela->p17, "flamengo");
    strcpy(tabela->p18, "vasco");
    strcpy(tabela->p19, "inter");
    strcpy(tabela->p20, "gremio");
}

void mostrarTabela(Tabela tabela)
{

    printf("TABELA:\n");

    printf("G4\n");

    printf("1o Lugar: %s\n", tabela.p1);
    printf("2o Lugar: %s\n", tabela.p2);
    printf("3o Lugar: %s\n", tabela.p3);
    printf("4o Lugar: %s\n", tabela.p4);

    printf("Z4\n");

    printf("17o Lugar: %s\n", tabela.p17);
    printf("18o Lugar: %s\n", tabela.p18);
    printf("19o Lugar: %s\n", tabela.p19);
    printf("20o Lugar: %s\n", tabela.p20);
}

int contarAcertosG4(Palpites participante, Tabela tabela)
{
    int acertosG4 = 0;

    // Verificar se os palpites estão no G4 e incrementar acertos se estiverem presentes em qualquer posição

    if (strcmp(tabela.p1, participante.p1) == 0)
    {
        acertosG4 += 2;
    }
    else if (strstr(tabela.p2, participante.p1) != NULL || strstr(tabela.p3, participante.p1) != NULL || strstr(tabela.p4, participante.p1) != NULL)
    {
        acertosG4++;
    }

    if (strcmp(tabela.p2, participante.p2) == 0)
    {
        acertosG4 += 2;
    }
    else if (strstr(tabela.p1, participante.p2) != NULL || strstr(tabela.p3, participante.p2) != NULL || strstr(tabela.p4, participante.p2) != NULL)
    {
        acertosG4++;
    }

    if (strcmp(tabela.p3, participante.p3) == 0)
    {
        acertosG4 += 2;
    }
    else if (strstr(tabela.p1, participante.p3) != NULL || strstr(tabela.p2, participante.p3) != NULL || strstr(tabela.p4, participante.p3) != NULL)
    {
        acertosG4++;
    }

    if (strcmp(tabela.p4, participante.p4) == 0)
    {
        acertosG4 += 2;
    }
    else if (strstr(tabela.p1, participante.p4) != NULL || strstr(tabela.p2, participante.p4) != NULL || strstr(tabela.p3, participante.p4) != NULL)
    {
        acertosG4++;
    }

    return acertosG4;
}

int contarAcertosZ4(Palpites participante, Tabela tabela)
{
    int acertosZ4 = 0;

    // Verificar se os palpites estão no Z4 e incrementar acertos se estiverem presentes em qualquer posição

    if (strcmp(tabela.p17, participante.p17) == 0)
    {
        acertosZ4 += 2;
    }
    else if (strstr(tabela.p18, participante.p17) != NULL || strstr(tabela.p19, participante.p17) != NULL || strstr(tabela.p20, participante.p17) != NULL)
    {
        acertosZ4++;
    }

    if (strcmp(tabela.p18, participante.p18) == 0)
    {
        acertosZ4 += 2;
    }
    else if (strstr(tabela.p17, participante.p18) != NULL || strstr(tabela.p19, participante.p18) != NULL || strstr(tabela.p20, participante.p18) != NULL)
    {
        acertosZ4++;
    }

    if (strcmp(tabela.p19, participante.p19) == 0)
    {
        acertosZ4 += 2;
    }
    else if (strstr(tabela.p17, participante.p19) != NULL || strstr(tabela.p18, participante.p19) != NULL || strstr(tabela.p20, participante.p19) != NULL)
    {
        acertosZ4++;
    }

    if (strcmp(tabela.p20, participante.p20) == 0)
    {
        acertosZ4 += 2;
    }
    else if (strstr(tabela.p17, participante.p20) != NULL || strstr(tabela.p18, participante.p20) != NULL || strstr(tabela.p19, participante.p20) != NULL)
    {
        acertosZ4++;
    }

    return acertosZ4;
}

int contarPontosMaximo(Palpites participantes, Tabela tabela)
{
    int pontos = 0;

    if (strcmp(participantes.p1, tabela.p1) == 0 && strcmp(participantes.p2, tabela.p2) == 0 && strcmp(participantes.p3, tabela.p3) == 0 && strcmp(participantes.p4, tabela.p4) == 0)
    {
        pontos += 10;
    }

    if (strcmp(participantes.p17, tabela.p17) == 0 && strcmp(participantes.p18, tabela.p18) == 0 && strcmp(participantes.p19, tabela.p19) == 0 && strcmp(participantes.p20, tabela.p20) == 0)
    {
        pontos += 10;
    }

    return pontos;
}

void compararPalpites(Palpites participantes[], Tabela tabela)
{
    for (int i = 0; i < NUM_PARTICIPANTES; i++)
    {
        int pontos = contarPontosMaximo(participantes[i], tabela);
        int acertosG4 = 0;
        int acertosZ4 = 0;

        if (pontos == 20)
        {
            participantes[i].pontuacao = pontos;
        }
        else if (pontos == 10)
        {
            acertosG4 = contarAcertosG4(participantes[i], tabela);
            acertosZ4 = contarAcertosZ4(participantes[i], tabela);

            if (acertosG4 == 8)
            {
                participantes[i].pontuacao = pontos + acertosZ4;
            }
            else if (acertosZ4 == 8)
            {
                participantes[i].pontuacao = pontos + acertosG4;
            }
        }
        else
        {
            acertosG4 = contarAcertosG4(participantes[i], tabela);
            acertosZ4 = contarAcertosZ4(participantes[i], tabela);
            participantes[i].pontuacao = acertosG4 + acertosZ4;
        }

        // Exibir os pontos do participante
        printf("\n");
        printf("Participante %s Pontos: %d \n", participantes[i].nome, participantes[i].pontuacao);
    }
}
