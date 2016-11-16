/***************************************************************************
*  $MCI Módulo de implementação: TAB  Tabuleiro genérico
*
*  Arquivo gerado:              TABULEIRO.c
*  Letras identificadoras:      TAB
*
*  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\TABULEIRO.BSW
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

#define TABULEIRO_OWN
#include "TABULEIRO.h"
#undef TABULEIRO_OWN


/***********************************************************************
*
*  $TC Tipo de dados: TAB Descritor da casa do tabuleiro
*
*
***********************************************************************/
typedef struct TAB_casa
{
	void * Peca;
	LIS_tppLista Ameacantes;
	LIS_tppLista Ameacados;
} TAB_Casa;


/***********************************************************************
*
*  $TC Tipo de dados: TAB Descritor do tabuleiro
*
*
***********************************************************************/

typedef struct TAB_tabuleiro
{
	TAB_Casa ** casa;
	int linha;
	char coluna;
}TAB_Tabuleiro;

/***** Protótipos das funções encapuladas no módulo *****/

static TAB_Casa TAB_IniciarCasa();
void DestruirValorLista(void * pValor);
void TAB_DestruirCasa(TAB_Casa *casa);

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: TAB  &Criar Tabuleiro
*  ****/
TAB_tpCondRet TAB_CriarTabuleiro(TAB_tpTabuleiro ptabuleiro)
{
	TAB_Tabuleiro * tempTab = ptabuleiro;
	TAB_Casa ** tempCasa;
	int i, j;
#ifdef _DEBUG
	assert(ptabuleiro != NULL);
#endif

	if (tempTab == NULL)
	{
		return TAB_CondRetFaltouMemoria;
	} /* if */

	tempCasa = (tempTab->casa);

	for (i = 0; i < tempTab->linha; i++)
	{
		for (j = 0; j < tempTab->coluna; j++)
		{
			tempCasa[i][j] = TAB_IniciarCasa();
		}
	}

	ptabuleiro->casa = tempCasa;

	return TAB_CondRetOK;
} /* Fim função: TAB  &Criar tabuleiro */

/***************************************************************************
*
*  Função: TAB  &Alocar Tabuleiro
*  ****/
TAB_tpTabuleiro TAB_AlocarTabuleiro(int linha, char coluna)
{
	int i;
	TAB_Casa ** tempCasa = (TAB_Casa**)malloc(linha * sizeof(TAB_Casa *));
	TAB_tpTabuleiro tempTab = (TAB_tpTabuleiro)malloc(sizeof(TAB_Tabuleiro));
	int col = coluna - '@';

	for (i = 0; i < linha; i++)
	{
		tempCasa[i] = (TAB_Casa*)malloc(col * sizeof(TAB_Casa));
	}

	tempTab->casa = tempCasa;
	tempTab->linha = linha;
	tempTab->coluna = col;

	return tempTab;
} /* Fim função: TAB  &Alocar tabuleiro */

/***************************************************************************
  *
  *  Função: TAB  &Mover Peca
  *  ****/

TAB_tpCondRet TAB_MoverPeca(TAB_tpTabuleiro t, int origemI, char origemJ, int destinoI, char destinoJ)
{
	TAB_tpCondRet CondRet;
	void * pecaOrigem = NULL;
	void * pecaDestino = NULL;
	


	// Testes de Ponteiro
	if (t == NULL)
	{
		return TAB_CondRetTabuleiroNaoExiste;
	}
	//*pecaOrigem = (void* )malloc(sizeof(t->casa[origemI][origemJ].Peca));
	//*pecaDestino = (void* )malloc(sizeof(t->casa[destinoI][destinoJ].Peca));

	//Mover Peça;
	CondRet = TAB_ObterPeca(t, origemI,origemJ, &pecaOrigem);
	if (CondRet != 0)
		return CondRet;
	if(pecaOrigem==NULL)
	{
		return TAB_CondRetPecaNaoExiste;
	}
	CondRet = TAB_ObterPeca(t, destinoI, destinoJ, &pecaDestino);
	if (CondRet != 0)
		return CondRet;
	if(pecaDestino!=NULL)
	{
		CondRet = TAB_RetirarPeca(t, destinoI, destinoJ);
		if (CondRet != 0)
			return CondRet;	
	}
	CondRet = TAB_RetirarPeca(t, origemI, origemJ);
	if (CondRet != 0)
		return CondRet;
	
	CondRet = TAB_InserirPeca(t,destinoI,destinoJ,pecaOrigem);
	if (CondRet != 0)
		return  CondRet;

	return TAB_CondRetOK;
	
}/* Fim função: TAB &Mover Peça*/


/***************************************************************************
*
*  Função: TAB  &Inserir Peça
*  ****/

TAB_tpCondRet TAB_InserirPeca(TAB_tpTabuleiro ptabuleiro, int linha, char coluna, void * peca)
{
	/* transforma a linha (A-H) fornecida em inteiro para poder acessar a casa corretamente */
	int lin = linha - 1;
	int col = coluna - 'A';

#ifdef _DEBUG
	assert(ptabuleiro != NULL);
#endif	
	/* trata o caso no qual o tabuleiro não existe */
	if (ptabuleiro == NULL)
	{
		return TAB_CondRetTabuleiroNaoExiste;
	}/* if */

	/* trata o caso no qual as coordenadas informadas não existem */
	if (lin<0 || lin >= ptabuleiro->linha || col<0 || col >= ptabuleiro->coluna)
		return TAB_CondRetCoordNaoExiste;


	if (ptabuleiro->casa[lin][col].Peca == NULL)
	{
		ptabuleiro->casa[lin][col].Peca = malloc(sizeof(peca));
		
		strcpy(ptabuleiro->casa[lin][col].Peca, peca);
	}
	else
	{
		return TAB_CondRetCasaOcupada;
	}

	return TAB_CondRetOK;
} /* Fim função: TAB  &Inserir peça */

/***************************************************************************
*
*  Função: TAB  &Obter Peça
*  ****/

TAB_tpCondRet TAB_ObterPeca(TAB_tpTabuleiro ptabuleiro, int linha, char coluna, void * peca)
{
	/* aloca memória para um ponteiro temporario receber o ptabuleiro */
	TAB_Tabuleiro * ptab = (TAB_Tabuleiro *)malloc(sizeof(TAB_Tabuleiro));

	/* transforma a linha fornecida em inteiro e acessa a casa corretamente */
	int lin = linha - 1;
	int col = coluna - 'A';

#ifdef _DEBUG
	assert(ptabuleiro != NULL);
#endif

	/* trata o caso no qual o tabuleiro não existe */
	if (ptabuleiro == NULL)
	{
		return TAB_CondRetTabuleiroNaoExiste;
	}/* if */

	/* trata o caso no qual as coordenadas informadas não existem */
	if (lin < 0 || lin >= ptabuleiro->linha || col < 0 || col >= ptabuleiro->coluna)
	{
		return TAB_CondRetCoordNaoExiste;
	}/* if */

	strcpy(peca, ptabuleiro->casa[lin][col].Peca);

	//peca = (ptabuleiro->casa[lin][col].Peca)


	return TAB_CondRetOK;
} /* Fim função: TAB  &Obter peça


/***************************************************************************
*
*  Função: TAB  &Retirar peça
*  ****/

TAB_tpCondRet TAB_RetirarPeca(TAB_tpTabuleiro ptabuleiro, int i, char j) {
	int lin = i - 1;
	int col = j - 'A';


	if (lin<0 || lin >= ptabuleiro->linha || col<0 || col >= ptabuleiro->coluna)
		return TAB_CondRetCoordNaoExiste;

	if (ptabuleiro->casa[lin][col].Peca == NULL)
		return TAB_CondRetPecaNaoExiste;

	ptabuleiro->casa[lin][col].Peca = NULL;

	return TAB_CondRetOK;

} /* Fim função: TAB  &Retirar peça */


/***************************************************************************
*
*  Função: TAB  &Destruir tabuleiro
*  ****/
TAB_tpCondRet TAB_DestruirTabuleiro(TAB_tpTabuleiro *ptabuleiro)
{
	int i, j;
	if (*ptabuleiro == NULL)
		return TAB_CondRetTabuleiroNaoExiste;

	for (i = 0; i<(*ptabuleiro)->linha; i++)
		for (j = 0; j < (*ptabuleiro)->coluna; j++) {
			TAB_RetirarPeca((*ptabuleiro), i + 1, j + 'A');
			TAB_DestruirCasa(&(*ptabuleiro)->casa[i][j]);
			
		}
	*(ptabuleiro) = NULL;
	free(*ptabuleiro);
	return TAB_CondRetOK;
} /* Fim função: TAB  &Destruir tabuleiro */

/***************************************************************************
*
*  Função: TAB  &Obter lista de ameaçados
*  ****/

TAB_tpCondRet TAB_ObterListaAmeacados (TAB_tpTabuleiro ptabuleiro, int i, char j, LIS_tppLista *Ameacados) {
	int lin  = i-1;
	char col = j-'A';

	*Ameacados = ptabuleiro->casa[lin][col].Ameacados;

	return TAB_CondRetOK;
} /* Fim função: TAB  &Obter lista de ameaçados */


/*  Função: TAB  &Obter lista de ameacantes
*  ****/

TAB_tpCondRet TAB_ObterListaAmeacantes (TAB_tpTabuleiro ptabuleiro, int i, char j, LIS_tppLista *Ameacantes) {
	int lin  = i-1;
	char col = j-'A';

	*Ameacantes = ptabuleiro->casa[lin][col].Ameacantes;

	return TAB_CondRetOK;
} /* Fim função: TAB  &Obter lista de ameaçantes */


/*****  Código das funções encapsuladas no módulo  *****/

/***************************************************************************
*
*  Função: TAB  &Iniciar Casa do Tabuleiro
*  ****/

TAB_Casa TAB_IniciarCasa()
{
	TAB_Casa casa;
	casa.Peca = NULL;
	casa.Ameacados = LIS_AlocarLista();
	LIS_CriarLista(DestruirValorLista, "Ameacados", casa.Ameacados);
	casa.Ameacantes = LIS_AlocarLista();
	LIS_CriarLista(DestruirValorLista, "Ameacantes", casa.Ameacantes);
	return casa;
} /* Fim função: TAB  &Iniciar casa do tabuleiro */

void DestruirValorLista(void * pValor)
{
	free(pValor);
} /* Fim função: TLIS -Destruir valor */

/***************************************************************************
*
*  Função: TAB  &Destruir Casa do Tabuleiro
*  ****/

void TAB_DestruirCasa(TAB_Casa *casa)
{

	LIS_DestruirLista(casa->Ameacados);
	LIS_DestruirLista(casa->Ameacantes);
	free(casa->Peca);
	//*casa = NULL;
} /* Fim função: TAB  &Destruir casa do tabuleiro */


/********** Fim do módulo de implementação: TAB  Tabuleiro - Matriz 8x8 casas  **********/
