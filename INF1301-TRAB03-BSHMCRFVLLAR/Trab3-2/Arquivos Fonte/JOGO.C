/***************************************************************************
*  $MCI Módulo de implementação: JGO Jogo de Xadrez
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

static JGO_tpCondRet JGO_MontarTabMod(TAB_tpTabuleiro ptabuleiro, PCA_tpVetPeca pecas);
static JGO_tpCondRet JGO_MontarTabPadrao(TAB_tpTabuleiro ptabuleiro, PCA_tpVetPeca pecas);
static void JGO_LerComando(TAB_tpTabuleiro ptabuleiro, int* linhaOrigem, char* colunaOrigem, int* linhaDestino, char* colunaDestinho);

/*****  Código das funções exportadas pelo módulo  *****/


/***************************************************************************
*
*  Função: TAB  &Iniciar Jogo
*
*  ****/
JGO_tpCondRet JGO_IniciarJogo(char * filename, PCA_tpVetPeca vetPecasPossiveis, TAB_tpTabuleiro pTabuleiro)
{
	JGO_tpCondRet CondRet;

	char resp = '\0';

	CondRet = TAB_CriarTabuleiro(pTabuleiro);
	if (CondRet != 0)
		return CondRet;

	CondRet = PCA_InicializarPecas(filename, &vetPecasPossiveis);
	if (CondRet != 0)
		return CondRet;

	printf("\nJogo Padrao? S:N\n");

	scanf(" %c", &resp);

	if (resp == 'S')
		return JGO_MontarTabPadrao(pTabuleiro, vetPecasPossiveis);//Sabrina
	else
		return JGO_MontarTabMod(pTabuleiro, vetPecasPossiveis);//RUDA 

	return JGO_CondRetOK;

}/* Fim função: TAB &Iniciar Jogo*/

/***************************************************************************
*
*  Função: TAB  &Mostrar Tabuleiro
*
*  ****/
JGO_tpCondRet JGO_MostrarTabuleiro(TAB_tpTabuleiro ptabuleiro)
{
	PCA_tpPeca peca;
	char nome, cor;
	int i;
	char j = 'A', lin;

	if (ptabuleiro == NULL)
		return JGO_CondRetTabuleiroNaoExiste;

	printf("\n ");

	for (j='A'; j<='H'; j++)
		printf("  %c   ", j);

	printf("\n");

	for (i = 1; i <= 8; i++){
		printf("|");
		for (j = 'A'; j <= 'H'; j++){
			TAB_ObterPeca(ptabuleiro, i, j, &peca);
			if (peca == NULL)
				printf("  v  |");
			else {
				PCA_ObterNome(peca, &nome);
				PCA_ObterCor(peca, &cor);
				printf(" %c-%c |", nome, cor);
			}
		}
		printf(" %d\n", i);
	}

	return JGO_CondRetOK;

}/* Fim função: TAB &Mostrar Tabuleiro*/

/***************************************************************************
*
*  Função: JGO  &Realizar movimento no Tabuleiro
*
*  ****/
JGO_tpCondRet JGO_RealizarMovimento(PCA_tpVetPeca vetPecasPossiveis, TAB_tpTabuleiro pTabuleiro)
{
	int linhaOrigem = 0, linhaDestino = 0;
	char colunaOrigem = '\0', colunaDestino = '\0';

	JGO_LerComando(pTabuleiro, &linhaOrigem, &colunaOrigem, &linhaDestino, &colunaDestino);

	return TAB_MoverPeca(pTabuleiro, linhaOrigem, colunaOrigem, linhaDestino, colunaDestino);

}/* Fim função: JGO &Realizar movimento no Tabuleiro */

/***************************************************************************
*
*  Função: JGO  &Verificar check
*
*  ****/
JGO_tpCondRet JGO_VerificaCheck(TAB_tpTabuleiro pTabuleiro, int * check, char pCor)
{
	int LIN, j, cont = 0;
	char COL;
	char nome;
	char cor, corp;
	PCA_tpPeca peca, p;
	LIS_tppLista ameacantes, ameacados;

	if (pTabuleiro == NULL)
		JGO_CondRetTabuleiroNaoExiste;

	for (LIN = 1; LIN <= 8; LIN++)
	{
		for (COL = 'A'; COL <= 'H'; COL++)
		{
			j = TAB_ObterPeca(pTabuleiro, LIN, COL, &peca);
			j = PCA_ObterNome(peca, &nome);
			j = PCA_ObterCor(peca, &cor);
			if (nome == 'R' && cor == pCor)
				break;
		}
	}
	TAB_ObterListaAmeacantes(pTabuleiro, LIN, COL, &ameacantes);
	if (ameacantes == NULL)
	{
		*check = 0;
	}

	if (ameacantes != NULL)
	{
		TAB_ObterListaAmeacados(pTabuleiro, LIN, COL, &ameacados);
		if (ameacados == NULL)
			*check = 1;

		TAB_ObterPeca(pTabuleiro, LIN + 1, COL, &p);
		PCA_ObterCor(p, &corp);
		if (corp != pCor)
			cont++;
		TAB_ObterPeca(pTabuleiro, LIN, COL + 1, &p);
		PCA_ObterCor(p, &corp);
		if (corp != pCor)
			cont++;
		TAB_ObterPeca(pTabuleiro, LIN + 1, COL + 1, &p);
		PCA_ObterCor(p, &corp);
		if (corp != pCor)
			cont++;
		TAB_ObterPeca(pTabuleiro, LIN, COL - 1, &p);
		PCA_ObterCor(p, &corp);
		if (corp != pCor)
			cont++;
		TAB_ObterPeca(pTabuleiro, LIN + 1, COL - 1, &p);
		PCA_ObterCor(p, &corp);
		if (corp != pCor)
			cont++;
		TAB_ObterPeca(pTabuleiro, LIN - 1, COL, &p);
		PCA_ObterCor(p, &corp);
		if (corp != pCor)
			cont++;
		TAB_ObterPeca(pTabuleiro, LIN - 1, COL + 1, &p);
		PCA_ObterCor(p, &corp);
		if (corp != pCor)
			cont++;
		TAB_ObterPeca(pTabuleiro, LIN - 1, COL - 1, &p);
		PCA_ObterCor(p, &corp);
		if (corp != pCor)
			cont++;

		if (cont >0)
			*check = 1;
		else if (cont == 0)
			*check = 2;


	}
	return JGO_CondRetOK;
}/* Fim função: JGO &Verificar check */


/***************************************************************************
*
*  Função: JGO  &Finalizar Jogo
*
*  ****/
JGO_tpCondRet JGO_FinalizarJogo(TAB_tpTabuleiro ptabuleiro)
{
	return (JGO_tpCondRet)TAB_DestruirTabuleiro(ptabuleiro);
}/* Fim função: JGO &Finalizar jogo */


/*****  Código das funções encapsuladas no módulo  *****/


/***************************************************************************
*
*  Função: TAB  &Ler Comando
*
*  ****/
void JGO_LerComando(TAB_tpTabuleiro ptabuleiro, int* linhaOrigem, char* colunaOrigem, int* linhaDestino, char* colunaDestinho)
{
	int linha = -1;
	char coluna = '\0';

	printf("\nInforme a linha da coordenada de Origem da peca:\n");

	scanf("%d", &linha);
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
}/* Fim função: JGO &Ler Comando */


/***************************************************************************
*
*  Função: TAB  &Montar Tabuleiro Modificado
*
*  ****/
JGO_tpCondRet JGO_MontarTabMod(TAB_tpTabuleiro ptabuleiro, PCA_tpVetPeca pecas)
{
	int i, CondRet,resp=-1;
	char  j, nome, cor;
	PCA_tpPeca *peca = (PCA_tpPeca *)malloc(sizeof(PCA_tpPeca));
		while (resp != 0)
		{
			do {
				printf("Qual é a peça?(Nome e cor)");
				scanf("%c %c", &nome, &cor);
				CondRet = PCA_PegarPecaDoVetor(pecas, peca, nome, cor);
				if (CondRet != 0)
				{
					printf("peça não existe tente novamente\n");
				}
			} while (CondRet != 0);
			
			printf("Onde por a peça");
			scanf("%d %c",&i,&j);
			
			CondRet = TAB_InserirPeca(ptabuleiro, i, j, peca);
			while (CondRet != 0) {
				if (CondRet == 1)
				{
					printf("casa ocupada tente novamente\n");
					scanf("%d %c", &i, &j);
					CondRet = TAB_InserirPeca(ptabuleiro, i, j, peca);
				}
				else if (CondRet == 4)
				{
					printf("coordenada nao existe tente novamente\n");
					scanf("%d %c", &i, &j);
					CondRet = TAB_InserirPeca(ptabuleiro, i, j, peca);
				}
			}
			printf("Digite 0, se NÃO quiser inserir mais peças \n");
			scanf("%d", &resp);

		}
	
	return  JGO_CondRetOK;
}/* Fim função: JGO &Montar Tabuleiro Modificado */

/***************************************************************************
*
*  Função: JGO  &Montar Tabuleiro Padrão
*
*  ****/
JGO_tpCondRet JGO_MontarTabPadrao(TAB_tpTabuleiro ptabuleiro, PCA_tpVetPeca pecas)
{
	int j;
	PCA_tpPeca peca;
	JGO_tpCondRet CondRet;
	//Insere todos os peões brancos
	CondRet = PCA_PegarPecaDoVetor(pecas, &peca, 'P', 'B');
	if (CondRet == JGO_CondRetOK)
	{
		for (j = 'A'; j < 'I'; j++)
		{
			TAB_InserirPeca(ptabuleiro, 2, j, peca);
		}
	}
	else
	{
		return CondRet;
	}

	//Insere todos os peões pretos
	CondRet = PCA_PegarPecaDoVetor(pecas, &peca, 'P', 'P');
	if (CondRet == JGO_CondRetOK)
	{
		for (j = 'A'; j < 'I'; j++)
		{
			TAB_InserirPeca(ptabuleiro, 7, j, peca);
		}
	}
	else
	{
		return CondRet;
	}

	//Insere todas as torres brancas
	CondRet = PCA_PegarPecaDoVetor(pecas, &peca, 'T', 'B');
	if (CondRet == JGO_CondRetOK)
	{
		TAB_InserirPeca(ptabuleiro, 1, 'A', peca);
		TAB_InserirPeca(ptabuleiro, 1, 'H', peca);
	}
	else
	{
		return CondRet;
	}
	//Insere todas as torres pretas
	CondRet = PCA_PegarPecaDoVetor(pecas, &peca, 'T', 'P');
	if (CondRet == JGO_CondRetOK)
	{
		TAB_InserirPeca(ptabuleiro, 8, 'A', peca);
		TAB_InserirPeca(ptabuleiro, 8, 'H', peca);
	}
	else
	{
		return CondRet;
	}

	//Insere todos os cavalos brancos
	CondRet = PCA_PegarPecaDoVetor(pecas, &peca, 'C', 'B');
	if (CondRet == JGO_CondRetOK)
	{
		TAB_InserirPeca(ptabuleiro, 1, 'B', peca);
		TAB_InserirPeca(ptabuleiro, 1, 'G', peca);
	}
	else
	{
		return CondRet;
	}
	//Insere todos os cavalos pretos
	CondRet = PCA_PegarPecaDoVetor(pecas, &peca, 'C', 'P');
	if (CondRet == JGO_CondRetOK)
	{
		TAB_InserirPeca(ptabuleiro, 8, 'B', peca);
		TAB_InserirPeca(ptabuleiro, 8, 'G', peca);
	}
	else
	{
		return CondRet;
	}
	//Insere todos os bispos brancos
	CondRet = PCA_PegarPecaDoVetor(pecas, &peca, 'B', 'B');
	if (CondRet == JGO_CondRetOK)
	{
		TAB_InserirPeca(ptabuleiro, 1, 'C', peca);
		TAB_InserirPeca(ptabuleiro, 1, 'F', peca);
	}
	else
	{
		return CondRet;
	}
	//Insere todos os bispos pretos
	CondRet = PCA_PegarPecaDoVetor(pecas, &peca, 'B', 'P');
	if (CondRet == JGO_CondRetOK)
	{
		TAB_InserirPeca(ptabuleiro, 8, 'C', peca);
		TAB_InserirPeca(ptabuleiro, 8, 'F', peca);
	}
	else
	{
		return CondRet;
	}
	//Insere a rainha branca
	CondRet = PCA_PegarPecaDoVetor(pecas, &peca, 'D', 'B');
	if (CondRet == JGO_CondRetOK)
	{
		TAB_InserirPeca(ptabuleiro, 1, 'E', peca);
	}
	else
	{
		return CondRet;
	}
	//Insere a rainha preta
	CondRet = PCA_PegarPecaDoVetor(pecas, &peca, 'D', 'P');
	if (CondRet == JGO_CondRetOK)
	{
		TAB_InserirPeca(ptabuleiro, 8, 'E', peca);
	}
	else
	{
		return CondRet;
	}
	//Insere o rei branco
	CondRet = PCA_PegarPecaDoVetor(pecas, &peca, 'R', 'B');
	if (CondRet == JGO_CondRetOK)
	{
		TAB_InserirPeca(ptabuleiro, 1, 'D', peca);
	}
	else
	{
		return CondRet;
	}
	//Insere o rei preto
	CondRet = PCA_PegarPecaDoVetor(pecas, &peca, 'R', 'P');
	if (CondRet == JGO_CondRetOK)
	{
		TAB_InserirPeca(ptabuleiro, 8, 'D', peca);
	}
	else
	{
		return CondRet;
	}

	return JGO_CondRetOK;

}/* Fim função: JGO &Montar Tabuleiro Padrão */


/********** Fim do módulo de implementação: JGO Jogo - Jogo de Xadrez  **********/
