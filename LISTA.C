/***************************************************************************
*  $MCI M�dulo de implementa��o: LIS  Lista duplamente encadeada
*
*  Arquivo gerado:              LISTA.c
*  Letras identificadoras:      LIS
*
*  Nome da base de software:    Arcabou�o para a automa��o de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\LISTA.BSW
*
*  Projeto: INF 1301 / 1628 Automatiza��o dos testes de m�dulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: avs
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    Data     Observa��es
*     4       avs   01/fev/2006 criar linguagem script simb�lica
*     3       avs   08/dez/2004 uniformiza��o dos exemplos
*     2       avs   07/jul/2003 unifica��o de todos os m�dulos em um s� projeto
*     1       avs   16/abr/2003 in�cio desenvolvimento
*
***************************************************************************/

#include   <stdio.h>
#include   <string.h>
#include   <memory.h>
#include   <malloc.h>
#include   <assert.h>

#define LISTA_OWN
#include "LISTA.h"
#undef LISTA_OWN

/***********************************************************************
*
*  $TC Tipo de dados: LIS Elemento da lista
*
*
***********************************************************************/

typedef struct tagElemLista {

	char * pValor;
	/* Ponteiro para o valor contido no elemento */

	struct tagElemLista * pAnt;
	/* Ponteiro para o elemento predecessor */

	struct tagElemLista * pProx;
	/* Ponteiro para o elemento sucessor */

} tpElemLista;

/***********************************************************************
*
*  $TC Tipo de dados: LIS Descritor da cabe�a de lista
*
*
***********************************************************************/

typedef struct LIS_tagLista {

	tpElemLista * pOrigemLista;
	/* Ponteiro para a origem da lista */

	tpElemLista * pFimLista;
	/* Ponteiro para o final da lista */

	tpElemLista * pElemCorr;
	/* Ponteiro para o elemento corrente da lista */

	int numElem;
	/* N�mero de elementos da lista */

	char * idLista;
	/* Caracteres que identificam a lista */

	void(*ExcluirValor) (char * pValor);
	/* Ponteiro para a fun��o de destrui��o do valor contido em um elemento */

} LIS_tpLista;

/***** Prot�tipos das fun��es encapuladas no m�dulo *****/

static void LiberarElemento(LIS_tppLista   pLista,
	tpElemLista  * pElem);

static tpElemLista * CriarElemento(LIS_tppLista pLista,
	char *       pValor);

static void LimparCabeca(LIS_tppLista pLista);

/*****  C�digo das fun��es exportadas pelo m�dulo  *****/

/***************************************************************************
*
*  Fun��o: LIS  &Criar lista
*  ****/

LIS_tpCondRet LIS_CriarLista(void(*ExcluirValor)(char * pValor),
	char * idLista, LIS_tppLista pLista)
{
	if (pLista == NULL)
	{
		return LIS_CondRetFaltouMemoria;
	} /* if */

	LimparCabeca(pLista);

	pLista->ExcluirValor = ExcluirValor;

	pLista->idLista = (char *)malloc(sizeof(idLista) + 1);

	strcpy(pLista->idLista, idLista);

	return LIS_CondRetOK;

} /* Fim fun��o: LIS  &Criar lista */

/***************************************************************************
*
*	Fun��o: LIS &Ir Pr�ximo elemento
*	*****/

LIS_tpCondRet LIS_IrProximoElemento(LIS_tppLista pLista)
{
	tpElemLista * pElem;
#ifdef _DEBUG
	assert(pLista != NULL);
#endif
	
	/* Tratar lista vazia */
	pElem = pLista->pElemCorr;
	
	if (pElem == NULL)
	{
		return LIS_CondRetListaVazia;
	} /* fim ativa: Tratar lista vazia */

	pElem = pElem->pProx;

	if (pElem != NULL)
	{
		pLista->pElemCorr = pElem;
		return LIS_CondRetOK;
	} /* if */

	pLista->pElemCorr = pLista->pFimLista;
	return LIS_CondRetNoCorrenteEhUltimo;

} /* Fim fun��o: LIS &Ir Pr�ximo elemento */


/***************************************************************************
*
*  Fun��o: LIS  &Destruir lista
*  ****/

LIS_tpCondRet LIS_DestruirLista(LIS_tppLista pLista)
{

#ifdef _DEBUG
	assert( pLista != NULL ) ;
#endif

	if (pLista == NULL)
	{
		return LIS_CondRetListaNaoExiste;
	}
	
	LIS_EsvaziarLista(pLista);
	
	free(pLista);

	return LIS_CondRetOK;
} /* Fim fun��o: LIS  &Destruir lista */

/***************************************************************************
*
*  Fun��o: LIS  &Alocar lista
*  ****/

LIS_tppLista LIS_AlocarLista()
{
	LIS_tppLista plista = (LIS_tppLista)malloc(sizeof(LIS_tpLista));
	return plista;
}

/***************************************************************************
*
*  Fun��o: LIS  &Esvaziar lista
*  ****/

void LIS_EsvaziarLista(LIS_tppLista pLista)
{

	tpElemLista * pElem;
	tpElemLista * pProx;

#ifdef _DEBUG
	assert( pLista != NULL ) ;
#endif

	pElem = pLista->pOrigemLista;
	while (pElem != NULL)
	{
		pProx = pElem->pProx;
		LiberarElemento(pLista, pElem);
		pElem = pProx;
	} /* while */

	LimparCabeca(pLista);

} /* Fim fun��o: LIS  &Esvaziar lista */

/*****  C�digo das fun��es encapsuladas no m�dulo  *****/


/***********************************************************************
*
*  $FC Fun��o: LIS  -Liberar elemento da lista
*
*  $ED Descri��o da fun��o
*     Elimina os espa�os apontados pelo valor do elemento e o
*     pr�prio elemento.
*
***********************************************************************/

void LiberarElemento(LIS_tppLista   pLista,
	tpElemLista  * pElem)
{

	if ((pLista->ExcluirValor != NULL)
		&& (pElem->pValor != NULL))
	{
		pLista->ExcluirValor(pElem->pValor);
	} /* if */

	free(pElem);

	pLista->numElem--;

} /* Fim fun��o: LIS  -Liberar elemento da lista */


/***********************************************************************
*
*  $FC Fun��o: LIS  -Criar o elemento
*
***********************************************************************/

tpElemLista * CriarElemento(LIS_tppLista pLista,
	char *       pValor)
{

	tpElemLista * pElem;

	pElem = (tpElemLista *)malloc(sizeof(tpElemLista));
	if (pElem == NULL)
	{
		return NULL;
	} /* if */

	pElem->pValor = pValor;
	pElem->pAnt = NULL;
	pElem->pProx = NULL;

	pLista->numElem++;

	return pElem;

} /* Fim fun��o: LIS  -Criar o elemento */


/***********************************************************************
*
*  $FC Fun��o: LIS  -Limpar a cabe�a da lista
*
***********************************************************************/

void LimparCabeca(LIS_tppLista pLista)
{

	pLista->pOrigemLista = NULL;
	pLista->pFimLista = NULL;
	pLista->pElemCorr = NULL;
	pLista->numElem = 0;
	pLista->idLista = NULL;

} /* Fim fun��o: LIS  -Limpar a cabe�a da lista */

/********** Fim do m�dulo de implementa��o: LIS  Lista duplamente encadeada **********/
