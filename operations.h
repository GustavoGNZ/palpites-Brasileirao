#ifndef OPERATIONS_H
#define OPERATIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char nome[40];
    char p1[40];
    char p2[40];
    char p3[40];
    char p4[40];
    char p20[40];
    char p19[40];
    char p18[40];
    char p17[40];
    int pontuacao;
} Palpites;

typedef struct
{
    char p1[40];
    char p2[40];
    char p3[40];
    char p4[40];
    char p20[40];
    char p19[40];
    char p18[40];
    char p17[40];
} Tabela;

Palpites lerPalpites(const char *nomeArquivo);
void obterNomeUsuario(char *nomeUsuario);
void cadastrarPalpites(Palpites participantes[], int quantidade);
void carregarPalpites();
void atualizarTabela(Tabela *tabela);
void mostrarTabela(Tabela tabela);
void compararPalpites(Palpites participantes[], Tabela tabela);
int contarAcertosG4(Palpites participante, Tabela tabela);
int contarAcertosZ4(Palpites participante, Tabela tabela);
int contarPontosMaximo(Palpites participante, Tabela tabela);


#endif // OPERATIONS_H
