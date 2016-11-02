/***************************************************************************
*  $MCI Módulo de implementação: PCA  Peça de um tabuleiro de xadrez  
*
*  Arquivo gerado:              PECA.c
*  Letras identificadoras:      PCA
*
*  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\PECA.BSW
*
*  Projeto: INF 1301 / 1628 Automatização dos testes de módulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: avs
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
#include   "LISTA.H"

#define PECA_OWN
#include "PECA.h"
#undef PECA_OWN

/***********************************************************************
*
*  $TC Tipo de dados: LIS Descritor da Peça
*
*
***********************************************************************/

typedef struct PCA_peca
{
	char         nomePeca;
	char         corPeca;
	LIS_tppLista movValido;

}PCA_Peca;

typedef struct PCA_movimento
{
	int dx;
	int dy;
	int atk;
	int prim;
} PCA_Mov;


/***** Protótipos das funções encapuladas no módulo *****/

int ComparaMov (PCA_Mov m1, PCA_Mov m2);

/*****  Código das funções exportadas pelo módulo  *****/

PCA_tpCondRet PCA_ObterPeca (LIS_tppLista Possiveis, PCA_tpPeca * res, char nome)
{
	PCA_tpCondRet CondRet=0;
	PCA_Peca * aux;

	while (CondRet==0)                          /* Deve se começar a procura no início da lista de peças possiveis */
		CondRet = LIS_irAnt (Possiveis);

	if (CondRet!=LIS_CondRetNoCorrenteEhPrimeiro)
		return CondRet;
	
	do 
	{
		CondRet = LIS_ObterNo(Possiveis, &aux);
		if (CondRet!=0)
			return CondRet;

		if (aux->nomePeca==nome){
			*res=aux;
			return PCA_CondRetOK;
		}

		CondRet = LIS_IrProximoElemento (Possiveis);

	} while (CondRet!=LIS_CondRetNoCorrenteEhUltimo);

	return PCA_CondRetPecaNaoExiste;
}

PCA_tpCondRet PCA_ObterCor (PCA_tpPeca peca, char* c)
{
	if (peca=NULL)
		return PCA_CondRetPecaNaoExiste;
	*c = peca->corPeca;
	return PCA_CondRetOK;
}

PCA_tpCondRet PCA_ObterNome (PCA_tpPeca peca, char* n)
{
	if (peca=NULL)
		return PCA_CondRetPecaNaoExiste;
	*n = peca->corPeca;
	return PCA_CondRetOK;
}

PCA_tpCondRet PCA_ValidarMovimento (PCA_tpPeca peca, int dx, int dy, int atk, int prim)
{
	PCA_Mov mov;

	if (peca=NULL)
		return PCA_CondRetPecaNaoExiste;

	mov.dx=dx;
	mov.dy=dy;
	mov.atk=atk;
	mov.prim=prim;



	
	

}

PCA_tpCondRet InicializarPecas ();


/*****  Código das funções encapsuladas no módulo  *****/

int ComparaMov (PCA_Mov m1, PCA_Mov m2)
{
	if ()

/********** Fim do módulo de implementação: TAB  Tabuleiro - Matriz 8x8 casas  **********/
