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
#include    "Lista.h"

#define PECA_OWN
#include "PECA.H"
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
} PCA_Mov;


/***** Protótipos das funções encapuladas no módulo *****/

void LiberarPeca (PCA_Peca * Peca);

int ComparaMov (PCA_Mov m1, PCA_Mov m2);

void LiberarMovimento (PCA_Mov * mov);

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: PCA  &Obter Peca
*
*  ************************************************************************/

PCA_tpCondRet PCA_PegarPecaDaLista (LIS_tppLista Possiveis, PCA_tpPeca * peca, char nome, char cor)
{
	PCA_tpCondRet CondRet=PCA_CondRetOK;
	PCA_Peca * aux;

	while (CondRet==0)
		CondRet = LIS_irAnt (Possiveis);

	if (CondRet!=LIS_CondRetNoCorrenteEhPrimeiro)
		return CondRet;
	
	do 
	{
		CondRet = LIS_ObterNo(Possiveis, &aux);
		if (CondRet!=0)
			return CondRet;

		if (aux->nomePeca == nome && aux->corPeca == cor){
			*peca=aux;
			return PCA_CondRetOK;
		}

		CondRet = LIS_IrProximoElemento (Possiveis);

	} while (CondRet==0);

	if (CondRet==LIS_CondRetNoCorrenteEhUltimo)
		return PCA_CondRetPecaNaoExiste;

	return CondRet;
}

/***************************************************************************
*
*  Função: PCA  &Obter Cor
*
*  ************************************************************************/

PCA_tpCondRet PCA_ObterCor (PCA_tpPeca peca, char* c)
{
	if (peca=NULL)
		return PCA_CondRetPecaNaoExiste;
	*c = peca->corPeca;
	return PCA_CondRetOK;
}

/***************************************************************************
*
*  Função: PCA  &Obter Nome
*
*  ************************************************************************/

PCA_tpCondRet PCA_ObterNome (PCA_tpPeca peca, char* n)
{
	if (peca=NULL)
		return PCA_CondRetPecaNaoExiste;
	*n = peca->corPeca;
	return PCA_CondRetOK;
}

/***************************************************************************
*
*  Função: PCA &Validar Movimento
*
*  ************************************************************************/

PCA_tpCondRet PCA_ValidarMovimento (PCA_tpPeca peca, int dx, int dy, int atk)
{
	PCA_tpCondRet CondRet=PCA_CondRetOK;
	PCA_Mov mov, *aux;

	if (peca=NULL)
		return PCA_CondRetPecaNaoExiste;

	mov.dx=dx;
	mov.dy=dy;
	mov.atk=atk;

	while (CondRet==0)
		CondRet = LIS_irAnt (peca->movValido);

	if (CondRet!=LIS_CondRetNoCorrenteEhPrimeiro)
		return CondRet;

	do 
	{
		CondRet = LIS_ObterNo(peca->movValido, &aux);
		if (CondRet!=0) return CondRet;

		if (ComparaMov(mov, *aux)) return PCA_CondRetOK;

		CondRet = LIS_IrProximoElemento (peca->movValido);

	} while (CondRet==0);

	if (CondRet==LIS_CondRetNoCorrenteEhUltimo) return PCA_CondRetMovimentoInvalido;

	return CondRet;
}

/***************************************************************************
*
*  Função: LIS  &Inicializar Pecas
*
*  ************************************************************************/

PCA_tpCondRet PCA_InicializarPecas (char* filename, LIS_tppLista * Possiveis){
	FILE* ArqPecasPossiveis;
	PCA_Peca *pecaTemp;
	PCA_Mov *movTemp;
	PCA_tpCondRet CondRet;
	int pecasRestantes, numLido;
	char charTemp;

	*Possiveis = LIS_AlocarLista ();
	CondRet = LIS_CriarLista (LiberarPeca , "PecasPossiveis", *Possiveis); /* Completar com a função que retira elemento*/ 
	if (CondRet!=0) return CondRet;

	ArqPecasPossiveis = fopen(filename, "r");
	numLido=fscanf(ArqPecasPossiveis ,"%d%c", &pecasRestantes, &charTemp);
	if (numLido!=2 || pecasRestantes<0 || charTemp != '\n') return PCA_CondRetErroNaLeituraDoArquivo;

	while (pecasRestantes--){

		pecaTemp = (PCA_Peca*) malloc (sizeof(PCA_Peca));
		if (pecaTemp == NULL) return PCA_CondRetFaltouMemoria;

		pecaTemp->movValido = LIS_AlocarLista();
		CondRet = LIS_CriarLista (LiberarMovimento , "MovimentosValidos", pecaTemp->movValido);
		if (CondRet!=0) return CondRet;

		numLido = fscanf(ArqPecasPossiveis, "%c",&charTemp);
		if (numLido != 1 || charTemp != '\n') return PCA_CondRetErroNaLeituraDoArquivo;

		numLido = fscanf(ArqPecasPossiveis, "%c%c%c", pecaTemp->nomePeca, &charTemp, pecaTemp->corPeca);
		if (numLido != 3 || charTemp != ' ') return PCA_CondRetErroNaLeituraDoArquivo;

		do {
			movTemp = (PCA_Mov*) malloc (sizeof(PCA_Mov));
			if (movTemp==NULL) return PCA_CondRetFaltouMemoria;

			numLido = fscanf(ArqPecasPossiveis, "%d%d%d%c", movTemp->dx, movTemp->dy, movTemp->atk, &charTemp);
			if (numLido != 3) return PCA_CondRetErroNaLeituraDoArquivo;

			LIS_InserirNo (pecaTemp->movValido, movTemp);

		} while (charTemp == ',');


		LIS_InserirNo (*Possiveis, pecaTemp);
	}

		
	return PCA_CondRetOK;
}


/*****  Código das funções encapsuladas no módulo  *****/

void LiberarMovimento (PCA_Mov * mov){
	free(mov);
}

void LiberarPeca (PCA_Peca * Peca){
	LIS_DestruirLista (Peca->movValido);
	free (Peca);
}

int ComparaMov (PCA_Mov m1, PCA_Mov m2)
{
	if (m1.dx==m2.dx && m1.dy==m2.dy && m1.atk==m2.atk)
		return 1;
	return 0;
}

/********** Fim do módulo de implementação: PCA Peça de Tabuleiro **********/
