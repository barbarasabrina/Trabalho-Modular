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

static void JGO_MontarTabMod(TAB_tpTabuleiro ptabuleiro, LIS_tppLista pecas);
static void JGO_LerComando(TAB_tpTabuleiro ptabuleiro, int* linhaOrigem, char* colunaOrigem, int* linhaDestino, char* colunaDestinho);
static void JGO_MontarTabPadrao(TAB_tpTabuleiro ptabuleiro, LIS_tppLista pecas);


/*****  Código das funções exportadas pelo módulo  *****/


/***************************************************************************
*
*  Função: TAB  &Iniciar Jogo
*  ****/

JGO_tpCondRet JGO_IniciarJogo (char* filename, LIS_tppLista listaPecasPossiveis, TAB_tpTabuleiro pTabuleiro){

	char resp = '\0';

	pTabuleiro = TAB_AlocarTabuleiro(8, 'H');
	TAB_CriarTabuleiro (pTabuleiro);

	PCA_InicializarPecas(filename, &listaPecasPossiveis, NULL);
	printf("Padrão? S:N");
	scanf("%d", resp);
	if (resp == 'S')
		JGO_MontarTabPadrao(pTabuleiro, listaPecasPossiveis);//Sabrina
	else
		JGO_MontarTabMod(pTabuleiro, listaPecasPossiveis);//RUDA 

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
	
	if (ptabuleiro == NULL)
		return JGO_CondRetTabuleiroNaoExiste;

	for (i=1; i<=8; i++){
		printf("|");
		for (j='A'; j<='H'; j++){
			TAB_ObterPeca(ptabuleiro, i, j, &peca);
			if (peca==NULL)
				printf("  v  |");
			else {
				PCA_ObterNome(peca, &nome);
				PCA_ObterCor(peca, &cor);
				printf(" %c-%c |", nome, cor);
			}
		}
		printf("\n");
	}
	
	return JGO_CondRetOK;
		
}/* Fim função: TAB &Mostrar Tabuleiro*/

/***************************************************************************
*
*  Função: TAB  &Montar Tabuleiro Modificado
*  ****/

void JGO_MontarTabMod(TAB_tpTabuleiro ptabuleiro, LIS_tppLista pecas)
{
	int i,k;
	char  j, nome, cor;
	PCA_tpPeca *peca = (PCA_tpPeca *)malloc(sizeof(PCA_tpPeca));	

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
					scanf("%d %c", &i, &j);
					k = TAB_InserirPeca(ptabuleiro, i, j, peca);
				}
			}
		}
		LIS_IrProximoElemento(pecas);

	}
}/* Fim função: JGO &Montar Tabuleiro Modificado*/


/***************************************************************************
*
*  Função: JGO  &Realizar movimento no Tabuleiro
*  ****/

JGO_tpCondRet JGO_RealizarMovimento(LIS_tppLista listaPecasPossiveis, TAB_tpTabuleiro pTabuleiro)
{
	int linhaOrigem = 0, linhaDestino = 0;
	char colunaOrigem = '\0', colunaDestino = '\0';

	JGO_LerComando(pTabuleiro, &linhaOrigem, &colunaOrigem, &linhaDestino, &colunaDestino);

	return TAB_MoverPeca(pTabuleiro, linhaOrigem, colunaOrigem, linhaDestino, colunaDestino);

}/* Fim função: JGO &Realizar movimento no Tabuleiro */


/***************************************************************************
*
*  Função: TAB  &Montar Tabuleiro Modificado
*  ****/

void JGO_LerComando(TAB_tpTabuleiro ptabuleiro, int* linhaOrigem, char* colunaOrigem, int* linhaDestino, char* colunaDestinho)
{
	int linha = -1;
	char coluna = '\0';

	printf("\nInforme a linha da coordenada de Origem da peca:\n");

	scanf(" %d", &linha);
	*linhaOrigem = linha;

	printf("\nInforme a coluna da coordenada de Origem da peca:\n");

	scanf(" %c", &coluna);
	*colunaOrigem = coluna;

	printf("\nInforme a linha da coordenada de Destino da peca:\n");

	scanf("%d", &linha);
	*linhaDestino = linha;

	printf("\nInforme a coluna da coordenada de Destino da peca:\n");

	scanf(" %c", &coluna);
	*colunaDestinho = coluna;

	system("PAUSE");
}

/***************************************************************************
*
*  Função: JGO  &Montar Tabuleiro Padrão
*  ****/

void JGO_MontarTabPadrao(TAB_tpTabuleiro ptabuleiro, LIS_tppLista pecas)
{
	int j;
	PCA_tpPeca * peca = (PCA_tpPeca*)malloc(sizeof(PCA_tpPeca));

	//Insere todos os peões brancos
	PCA_PegarPecaDaLista(pecas, peca, 'P', 'B');
	for (j = 'A'; j < 'I';j++)
	{
		TAB_InserirPeca(ptabuleiro, 2, j, peca);
	}

	//Insere todos os peões pretos
	PCA_PegarPecaDaLista(pecas, peca, 'P', 'P');
	for (j = 'A'; j < 'I'; j++)
	{
		TAB_InserirPeca(ptabuleiro, 7, j, peca);
	}

	//Insere todas as torres brancas
	PCA_PegarPecaDaLista(pecas, peca, 'T', 'B');
	TAB_InserirPeca(ptabuleiro, 1, 'A', peca);
	TAB_InserirPeca(ptabuleiro, 1, 'H', peca);

	//Insere todas as torres pretas
	PCA_PegarPecaDaLista(pecas, peca, 'T', 'P');
	TAB_InserirPeca(ptabuleiro, 8, 'A', peca);
	TAB_InserirPeca(ptabuleiro, 8, 'H', peca);

	//Insere todos os cavalos brancos
	PCA_PegarPecaDaLista(pecas, peca, 'C', 'B');
	TAB_InserirPeca(ptabuleiro, 1, 'B', peca);
	TAB_InserirPeca(ptabuleiro, 1, 'G', peca);

	//Insere todos os cavalos pretos
	PCA_PegarPecaDaLista(pecas, peca, 'C', 'P');
	TAB_InserirPeca(ptabuleiro, 8, 'B', peca);
	TAB_InserirPeca(ptabuleiro, 8, 'G', peca);

	//Insere todos os bispos brancos
	PCA_PegarPecaDaLista(pecas, peca, 'B', 'B');
	TAB_InserirPeca(ptabuleiro, 1, 'C', peca);
	TAB_InserirPeca(ptabuleiro, 1, 'F', peca);

	//Insere todos os bispos pretos
	PCA_PegarPecaDaLista(pecas, peca, 'B', 'P');
	TAB_InserirPeca(ptabuleiro, 8, 'C', peca);
	TAB_InserirPeca(ptabuleiro, 8, 'F', peca);

	//Insere a rainha branca
	PCA_PegarPecaDaLista(pecas, peca, 'D', 'B');
	TAB_InserirPeca(ptabuleiro, 1, 'E', peca);

	//Insere a rainha preta
	PCA_PegarPecaDaLista(pecas, peca, 'D', 'P');
	TAB_InserirPeca(ptabuleiro, 8, 'E', peca);

	//Insere o rei branco
	PCA_PegarPecaDaLista(pecas, peca, 'R', 'B');
	TAB_InserirPeca(ptabuleiro, 1, 'D', peca);

	//Insere o rei preto
	PCA_PegarPecaDaLista(pecas, peca, 'R', 'P');
	TAB_InserirPeca(ptabuleiro, 8, 'D', peca);		
}/* Fim função: JGO &Montar Tabuleiro Padrão */

JGO_tpCondRet JGO_VerificaCheck(TAB_tpTabuleiro pTabuleiro, int * check,char *pCor)
{
	int LIN,j,cont=0;
	char COL;
	char *nome;
	char * cor,*corp;
	PCA_tpPeca *peca, *p;
	LIS_tppLista *ameacantes, *ameacados;

	if(pTabuleiro==NULL)
		JGO_CondRetTabuleiroNaoExiste;

	for(LIN=1;LIN<=8;LIN++)
	{
		for(COL = 'A';COL<='H';COL++)
		{
			j=TAB_ObterPeca(pTabuleiro,LIN,COL,peca);
			j = PCA_ObterNome((*peca), nome);
			j = PCA_ObterCor((*peca),cor);
			if(nome == "R" && cor == pCor)
			break;
		}
	}
	TAB_ObterListaAmeacantes(pTabuleiro,LIN,COL,ameacantes);
	if(ameacantes == NULL)
	{
		*check = 0;
	}

	if(ameacantes != NULL)
	{
		TAB_ObterListaAmeacados(pTabuleiro,LIN,COL,ameacados);
		if(ameacados == NULL)
			*check = 1;

			TAB_ObterPeca(pTabuleiro,LIN+1,COL,p);
			PCA_ObterCor((*p),corp);
			if(corp != pCor)
				cont++;
			TAB_ObterPeca(pTabuleiro,LIN,COL+1,p);
			PCA_ObterCor((*p),corp);
			if(corp != pCor)
				cont++;
			TAB_ObterPeca(pTabuleiro,LIN+1,COL+1,p);
			PCA_ObterCor((*p),corp);
			if(corp != pCor)
				cont++;
			TAB_ObterPeca(pTabuleiro,LIN,COL-1,p);
			PCA_ObterCor((*p),corp);
			if(corp != pCor)
				cont++;
			TAB_ObterPeca(pTabuleiro,LIN+1,COL-1,p);
			PCA_ObterCor((*p),corp);
			if(corp != pCor)
				cont++;
			TAB_ObterPeca(pTabuleiro,LIN-1,COL,p);
			PCA_ObterCor((*p),corp);
			if(corp != pCor)
				cont++;
			TAB_ObterPeca(pTabuleiro,LIN-1,COL+1,p);
			PCA_ObterCor((*p),corp);
			if(corp != pCor)
				cont++;
			TAB_ObterPeca(pTabuleiro,LIN-1,COL-1,p);
			PCA_ObterCor((*p),corp);
			if(corp != pCor)
				cont++;

			if(cont >0)
				*check = 1;
			else if (cont==0)
				*check = 2;
		

	}

	
	return JGO_CondRetOK;
}

JGO_tpCondRet JGO_FinalizarJogo(JGO_tppJogo pJogo)
{

}


/*****  Código das funções encapsuladas no módulo  *****/

/********** Fim do módulo de implementação: JGO Jogo - Jogo de Xadrez  **********/
