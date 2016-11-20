/***************************************************************************
*  $MCI Módulo de implementação: JGO jogo de xadrez
*
*  Arquivo gerado:              JOGO.c
*  Letras identificadoras:      JGO
*
*  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\JOGO.BSW
*
*  Projeto: INF 1301 / 1628 Automatização dos testes de módulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: avs, bshmc, rfv, llar
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*     4       avs   01/fev/2006 criar linguagem script simbólica
*     3       avs   08/dez/2004 uniformização dos exemplos
*     2       avs   07/jul/2003 unificação de todos os módulos em um só projeto
*     1       avs   16/abr/2003 início desenvolvimento
*
***************************************************************************/

#include   <stdio.h>
#include   <string.h>
#include   <memory.h>
#include   <malloc.h>
#include   <assert.h>
#include   <stdlib.h>
#include "TABULEIRO.H"
#include "PECA.H"

#define JOGO_OWN
#include "JOGO.h"
#undef JOGO_OWN

/***** Protótipos das funções encapuladas no módulo *****/

/*****  Código das funções exportadas pelo módulo  *****/


/***************************************************************************
*
*  Função: TAB  &Iniciar Jogo
*  ****/

JGO_tpCondRet JGO_IniciarJogo (char* filename, LIS_tppLista listaPecasPossiveis, TAB_tpTabuleiro pTabuleiro){

	char resp;
	LIS_tppLista listaPecasPossiveis;
	TAB_tpTabuleiro pTabuleiro;

	pTabuleiro = TAB_AlocarTabuleiro(8, 'H');
	TAB_CriarTabuleiro (pTabuleiro);

	PCA_InicializarPecas(filename, &listaPecasPossiveis);
	printf("Padrão? S:N");
	scanf("%d", resp);
	if (resp == 'S')
		JGO_MontarTabPadrao();//Sabrina
	else
		JGO_MontarTabMod();//RUDA 

}/* Fim função: TAB &Iniciar Jogo*/

/***************************************************************************
*
*  Função: TAB  &Mostrar Tabuleiro
*  ****/

JGO_tpCondRet JGO_MostrarTabuleiro (TAB_tpTabuleiro ptabuleiro)
{
	PCA_tpPeca peca;
	char nome, cor;
	int i;
	char j;


	for (i=1; i<=8; i++){
		printf("|");
		for (j='A'; j<='H'; j++){
			TAB_ObterPeca(ptabuleiro, i, j, &peca);
			if (peca==NULL)
				printf(" --- |");
			else {
				PCA_ObterNome(peca, &nome);
				PCA_ObterCor(peca, &cor);
				printf(" %c-%c |", nome, cor);
			}
		}
		printf("\n");
	}
}/* Fim função: TAB &Mostrar Tabuleiro*/

/***************************************************************************
*
*  Função: TAB  &Montar Tabuleiro Modificado
*  ****/

void JGO_MontarTabMod(TAB_tpTabuleiro ptabuleiro, LIS_tppLista pecas)
{
	int i,k;
	char  j, nome, cor;
	PCA_tpPeca *peca = (PCA_tpPeca*)malloc(PCA_tpPeca);

	

	while (pecas!=NULL)
	{
		LIS_ObterNo(pecas, peca);
		PCA_ObterCor(peca,&cor);
		PCA_ObterNome(peca,&nome);
		while (peca != NULL)
		{
			printf("onde por a peça %c de cor %c", cor, nome);
			scanf("%d %c", &i, &j);
			k = TAB_InserirPeca(ptabuleiro, i, j, peca);
			while (k != 0) {
				if (k == 1)
				{
					printf("casa ocupada tente novamente\n");
					scanf("%d %c", &i, &j);
					k = TAB_InserirPeca(ptabuleiro, i, j, peca);
				}
				else if (k == 4)
				{
					printf("coordenada nao existe tente novamente\n");
					scanf("%d %c", &i &j);
					k = TAB_InserirPeca(ptabuleiro, i, j, peca);
				}
			}
		}
		LIS_IrProximoElemento(pecas);

	}
}/* Fim função: TAB &Montar Tabuleiro Modificado*/

/*****  Código das funções encapsuladas no módulo  *****/

/********** Fim do módulo de implementação: JGO Jogo - Jogo de Xadrez  **********/
