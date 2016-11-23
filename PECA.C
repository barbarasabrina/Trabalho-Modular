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

#define PECA_OWN
#include "PECA.H"
#undef PECA_OWN

/***********************************************************************
*
*  $TC Tipo de dados: LIS Descritor da Peça
*
*
***********************************************************************/
typedef struct PCA_movimento
{
	int dx;
	int dy;
	int atk;
} PCA_Mov;

typedef struct PCA_peca
{
	char		nomePeca;
	char		corPeca;
	int			nMov;
	PCA_Mov*	movValido;

}PCA_Peca;

typedef struct PCA_vetPeca
{
	int n;
	PCA_Peca * peca;
} PCA_VetPeca;


/***** Protótipos das funções encapuladas no módulo *****/

void LiberarPeca (void * Peca);

int ComparaMov (PCA_Mov m1, PCA_Mov m2);

void LiberarMovimento (PCA_Mov * mov);

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: PCA  &Obter Peca
*
*  ************************************************************************/

PCA_tpCondRet PCA_PegarPecaDoVetor (PCA_VetPeca * Possiveis, PCA_tpPeca * peca, char nome, char cor)
{
	int i;

	if (Possiveis == NULL || Possiveis->peca == NULL)
		return PCA_CondRetPecaNaoExiste;
	
	for (i=0; i<Possiveis->n; i++)
		if (Possiveis->peca[i].nomePeca == nome && Possiveis->peca[i].corPeca == cor){
			*peca = &Possiveis->peca[i];
			return PCA_CondRetOK;
		}

	return PCA_CondRetPecaNaoExiste;
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
	PCA_Mov mov, *aux;
	int i;

	if (peca=NULL)
		return PCA_CondRetPecaNaoExiste;

	mov.dx=dx;
	mov.dy=dy;
	mov.atk=atk;

	for (i=0; i<peca->nMov; i++)
		if ( ComparaMov(mov, peca->movValido[i]) )
			return PCA_CondRetOK;
	return PCA_CondRetMovimentoInvalido;
}


/***************************************************************************
*
*  Função: LIS  &Inicializar Pecas
*
*  ************************************************************************/

PCA_tpCondRet PCA_InicializarPecas (char* filename, PCA_tpVetPeca *Possiveis, FILE * teste){
	FILE* ArqPecasPossiveis;
	PCA_tpCondRet CondRet;
	int i, j, numLido;
	char charTemp;
	PCA_tpVetPeca vetTemp;
	
	vetTemp = (PCA_tpVetPeca)malloc(sizeof(PCA_VetPeca));

	ArqPecasPossiveis = fopen(filename, "r");
	numLido = fscanf(ArqPecasPossiveis, "%d%c", &vetTemp->n, &charTemp  ); /* Ler numero de pecas */

	if (teste!=NULL) fprintf(teste, "Leu a primeira linha do arquivo, Total de pecas:%d\n", vetTemp->n);
	if (numLido!=2 || vetTemp->n<=0 || charTemp != '\n') return PCA_CondRetErroNaLeituraDoArquivo;

	vetTemp->peca= (PCA_Peca*)malloc(vetTemp->n*sizeof(PCA_Peca));
	if (vetTemp->peca==NULL) return PCA_CondRetFaltouMemoria;


	for (i=0; i<vetTemp->n; i++){	/* Para cada peca */

		numLido = fscanf(ArqPecasPossiveis, "%c",&charTemp);																	/* Ler separador de pecas (\n) */
		if (teste!=NULL) fprintf(teste, "Leu o enter %d\n", charTemp);
		if (numLido != 1 || charTemp != '\n') return PCA_CondRetErroNaLeituraDoArquivo;

		numLido = fscanf(ArqPecasPossiveis, "%c%c%c", &vetTemp->peca[i].nomePeca, &charTemp, &vetTemp->peca[i].corPeca);	/* Ler nome e cor da peca */
		if (teste!=NULL) fprintf(teste, "Leu o nome (%c), o espaco (%c) e cor da peca (%c)\n", vetTemp->peca[i].nomePeca, charTemp, vetTemp->peca[i].corPeca);
		if (numLido != 3 || charTemp != ' ') return PCA_CondRetErroNaLeituraDoArquivo;

		numLido = fscanf(ArqPecasPossiveis, "%c%d", &charTemp, &vetTemp->peca[i].nMov);										/* Ler quantidade de movimentos da peca */
		if (teste!=NULL) fprintf(teste, "Leu o espaco (%c), e o numero de movimentos (%d)\n", charTemp, vetTemp->peca[i].nMov);
		if (numLido != 2 || charTemp != ' ') return PCA_CondRetErroNaLeituraDoArquivo;

		vetTemp->peca[i].movValido = (PCA_Mov*) malloc (vetTemp->peca[i].nMov * sizeof(PCA_Mov));
		if (vetTemp->peca[i].movValido==NULL) return PCA_CondRetFaltouMemoria;

		for (j=0; j<vetTemp->peca[i].nMov; j++){	/* Para cada movimento da peca */
			
			numLido = fscanf(ArqPecasPossiveis, "%d%d%d%c", &vetTemp->peca[i].movValido[j].dx, &vetTemp->peca[i].movValido[j].dy, &vetTemp->peca[i].movValido[j].atk, &charTemp);	/* Ler movimento */
			if (teste!=NULL) fprintf(teste, "Leu o movimento (%d %d %d) e o charTemp(%c)\n", vetTemp->peca[i].movValido[j].dx, vetTemp->peca[i].movValido[j].dy, vetTemp->peca[i].movValido[j].atk, charTemp);
			if (numLido != 4) return PCA_CondRetErroNaLeituraDoArquivo;

		}
	}		
	fclose(ArqPecasPossiveis);
	*Possiveis = vetTemp;
	return PCA_CondRetOK;
}


/***************************************************************************
*
*  Função: LIS  &Destruir Vetor de Pecas
*
*  ************************************************************************/

PCA_tpCondRet PCA_DestruirVetPecas (PCA_VetPeca *Possiveis) {
	int i, j;

	for (i=0; i<Possiveis->n; i++)
		free(Possiveis->peca[i].movValido);
	free (Possiveis);

	return PCA_CondRetOK;

}


/*****  Código das funções encapsuladas no módulo  *****/

void LiberarMovimento (PCA_Mov * mov){
	free(mov);
}

void LiberarPeca (PCA_Peca* peca){
	free(peca->movValido);
	free(peca);
}


int ComparaMov (PCA_Mov m1, PCA_Mov m2)
{
	if (m1.dx==m2.dx && m1.dy==m2.dy && m1.atk==m2.atk)
		return 1;
	return 0;
}

/********** Fim do módulo de implementação: PCA Peça de Tabuleiro **********/
