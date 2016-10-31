/***************************************************************************
*  $MCI Módulo de implementação: LIS  Lista duplamente encadeada
*
*  Arquivo gerado:              LISTA.c
*  Letras identificadoras:      LIS
*
*  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\LISTA.BSW
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
*  $TC Tipo de dados: LIS Descritor da cabeça de lista
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
	/* Número de elementos da lista */

	char * idLista;
	/* Caracteres que identificam a lista */

	void(*ExcluirValor) (char * pValor);
	/* Ponteiro para a função de destruição do valor contido em um elemento */

} LIS_tpLista;

/***** Protótipos das funções encapuladas no módulo *****/

static void LiberarElemento(LIS_tppLista   pLista,
	tpElemLista  * pElem);

static tpElemLista * CriarElemento(LIS_tppLista pLista,
	char *       pValor);

static void LimparCabeca(LIS_tppLista pLista);

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: LIS  &Criar lista
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

} /* Fim função: LIS  &Criar lista */

/***************************************************************************
*
*	Função: LIS &Ir Próximo elemento
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

} /* Fim função: LIS &Ir Próximo elemento */


/***************************************************************************
*
*  Função: LIS  &Destruir lista
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
} /* Fim função: LIS  &Destruir lista */

/***************************************************************************
*
*  Função: LIS  &Alocar lista
*  ****/

LIS_tppLista LIS_AlocarLista()
{
	LIS_tppLista plista = (LIS_tppLista)malloc(sizeof(LIS_tpLista));
	return plista;
}

/***************************************************************************
*
*  Função: LIS  &Esvaziar lista
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

} /* Fim função: LIS  &Esvaziar lista */

/*****  Código das funções encapsuladas no módulo  *****/


/***********************************************************************
*
*  $FC Função: LIS  -Liberar elemento da lista
*
*  $ED Descrição da função
*     Elimina os espaços apontados pelo valor do elemento e o
*     próprio elemento.
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

} /* Fim função: LIS  -Liberar elemento da lista */


/***********************************************************************
*
*  $FC Função: LIS  -Criar o elemento
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

} /* Fim função: LIS  -Criar o elemento */


/***********************************************************************
*
*  $FC Função: LIS  -Limpar a cabeça da lista
*
***********************************************************************/

void LimparCabeca(LIS_tppLista pLista)
{

	pLista->pOrigemLista = NULL;
	pLista->pFimLista = NULL;
	pLista->pElemCorr = NULL;
	pLista->numElem = 0;
	pLista->idLista = NULL;

} /* Fim função: LIS  -Limpar a cabeça da lista */

/********** Fim do módulo de implementação: LIS  Lista duplamente encadeada **********/

