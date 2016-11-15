#if ! defined( TABULEIRO_ )
#define TABULEIRO_


#define LISTA_OWN
#include "LISTA.h"
#undef LISTA_OWN

/***************************************************************************
*
*  $MCD M�dulo de defini��o: TAB  Tabuleiro gen�rico
*
*  Arquivo gerado:              TABULEIRO.h
*  Letras identificadoras:      TAB
*
*  Nome da base de software:    Arcabou�o para a automa��o de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\TABULEIRO.BSW
*
*  Projeto: INF 1301 / 1628 Automatiza��o dos testes de m�dulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: avs, bshmc, rfv, llar
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    Data     Observa��es
*	 5	bshmc,rfv,llar  10/10/2016 implementa��o do muodulo de tabuleiro
*     4       avs   01/fev/2006 criar linguagem script simb�lica
*     3       avs   08/dez/2004 uniformiza��o dos exemplos
*     2       avs   07/jul/2003 unifica��o de todos os m�dulos em um s� projeto
*     1       avs   16/abr/2003 in�cio desenvolvimento
*
*  $ED Descri��o do m�dulo
*		Implementa tabuleiros gen�ricos.
*		Podem existir n tabuleiros em opera��o simultaneamente.
*
*		Cada tabuleiro � homog�neo quanto ao tipo dos dados que armazena.
*		Cada elemento do tabuleiro � chamado de casa e cada casa possui informa��o da pe�a que cont�m, caso exista, e uma lista de pe�as amea�antes e de pe�as de amea�adas.
*
*		O controle da destrui��o da pe�a de uma casa a ser exclu�da
*       � realizado por uma fun��o fornecida para o usu�rio.
*
*		Cado tabuleiro referencia uma fun��o que determina como devem ser
*       desalocados os dados nela contidos.
*
*		A fun��o de libera��o dos valores contidos nos elementos deve
*       assegurar a libera��o de todos os espa�os refer�nciados pelo
*       valor contido em cada elemento.
*       Esta fun��o � chamada antes de se desalocar um elemento
*       de um tabuleiro.
*       Caso n�o seja necess�rio desalocar o valor referenciado pelo
*       elemento, o ponteiro para a fun��o de libera��o poder� ser NULL .
*       Caso a casa do tabuleiro seja a �nica �ncora do valor referenciado,
*       esta fun��o deve promover a destrui��o (free) desse valor e
*       de todos os dados nele ancorados.
*
***************************************************************************/

#if defined( TABULEIRO_OWN )
#define TABULEIRO_EXT
#else
#define TABULEIRO_EXT extern
#endif

/***** Declara��es exportadas pelo m�dulo *****/

/* Tipo refer�ncia para um tabuleiro */

typedef struct TAB_tabuleiro * TAB_tpTabuleiro;

/***********************************************************************
*
*  $TC Tipo de dados: TAB Condi��es de retorno
*
*
*  $ED Descri��o do tipo
*		Condi��es de retorno das fun��es do tabuleiro
*
***********************************************************************/

typedef enum {

	TAB_CondRetOK = 0,
	/* Movimenta��o bem sucedida */

	TAB_CondRetCasaOcupada = 1,
	/* A casa do tabuleiro se encontra cheia, j� ocupada */

	TAB_CondRetTabuleiroVazio = 2,
	/* O tabuleiro n�o cont�m pe�a em nenhuma casa */

	TAB_CondRetTabuleiroNaoExiste = 3,
	/* Tabuleiro n�o existe */

	TAB_CondRetCoordNaoExiste = 4,
	/* Coordenadas n�o existem no tabuleiro */

	TAB_CondRetPecaNaoExiste = 5,
	/* N�o h� pe�a na casa do tabuleiro ou a identifica��o da pe�a fornecida n�o existe */

	TAB_CondRetFaltouMemoria = 6,
	/* Faltou mem�ria ao tentar criar um elemento do tabuleiro */

	TAB_CondRetCasaNaoExiste = 7
	/* Casa n�o existe, est� nula */


} TAB_tpCondRet;

/***********************************************************************
*
*  $FC Fun��o: TAB  &Inserir pe�a no tabuleiro
*
*  $ED Descri��o da fun��o
*		Insere uma pe�a no tabuleiro.
*
*  $AE Assertiva de Entrada
*		Deve existir um tabuleiro.
*		Deve existir a coordenada para a casa no tabuleiro (linha e coluna).
*		Deve existir uma pe�a a ser inserida no tabuleiro.
*
*  $AS Assertiva de Saida
*		S�o v�lidas as assertivas de entrada.
*		A casa ,cuja coordenada foi informada, � preenchida com o valor de identifica��o da pe�a.
*		Em caso de falta de mem�ria, o ponteiro apontar� para um ponteiro nulo.
*
*
*  $EP Par�metros
*		ptabuleiro					- ponteiro para o tabuleiro
*		linha						- ponteiro para a coordenada linha da casa
*		coluna						- ponteiro para a coordenada coluna da casa
*		peca						- ponteiro para a pe�a
*
*  $FV Valor retornado
*		Se executou corretamente retorna o ponteiro para o tabuleiro e a condi��o de movimenta��o bem sucedida.
*		Este ponteiro ser� utilizado pelas fun��es que manipulem este tabuleiro.
*
*  $FV Valor retornado
*		TAB_CondRetOK					- cria��o de tabuleiro bem sucedida
*		TAB_CondRetTabuleiroNaoExiste	- tabuleiro n�o existe
*		TAB_CondRetCoordNaoExiste		- coordenadas n�o existem
*		TAB_CondRetCasaOcupada			- casa j� est� ocupada
*
***********************************************************************/

TAB_tpCondRet TAB_InserirPeca(TAB_tpTabuleiro ptabuleiro, int linha, char coluna, void * peca);

/***********************************************************************
*
*  $FC Fun��o: TAB  &Obter Pe�a
*
*  $ED Descri��o da fun��o
*		Obt�m a pe�a que se encontra nas coordenadas da casa do tabuleiro.
*
*  $AE Assertiva de Entrada
*		Deve existir um tabuleiro.
*		Devem existir coordenadas v�lidas referentes � casa no tabuleiro(linha e coluna).
*
*
*  $AS Assertiva de Sa�da
*		S�o v�lidas as assertivas de entrada.
*		Uma identifica��o de pe�a ser� obtida caso as informa��es da linha e coluna da casa
*		no tabuleiro sejam v�lidas e exista uma pe�a na respectiva casa.
*		Caso n�o exista pe�a na casa informada, ser� obtido da fun��o um ponteiro nulo.
*
*
*  $EP Par�metros
*		ptabuleiro					- ponteiro para o tabuleiro
*		linha						- ponteiro para a coordenada linha da casa
*		coluna						- ponteiro para a coordenada coluna da casa
*		peca						- ponteiro para a pe�a do tabuleiro
*
*
*  $FV Valor retornado
*		TAB_CondRetOK					- cria��o de tabuleiro bem sucedida
*		TAB_CondRetTabuleiroNaoExiste	- tabuleiro n�o existe
*		TAB_CondRetCoordNaoExiste		- coordenadas n�o existem
*
***********************************************************************/

TAB_tpCondRet TAB_ObterPeca(TAB_tpTabuleiro ptabuleiro, int linha, char coluna, void * peca);


/***********************************************************************
*
*  $FC Fun��o: TAB &Retirar pe�a
*
*  $ED Descri��o da fun��o
*     Retira uma pe�a de uma coordenada do tabuleiro.
*     Qual o tipo de pe�a presente � desconhecido a priori.
*     Caso n�o exista pe�a nas coordenadas enviadas a fun��o n�o retorna mensagem de erro.
*
*
*  $EP Par�metros
*     t - Ponteiro para o tabuleiro a ser utilizado
*     i - Caracter que representa a linha na qual a fun��o deve atuar
*         Varia entre '1' e '8'
*     j - Caracter que representa a coluna na qual a fun��o deve atuar
*         Varia entre 'A' e 'H'
*
*  $AE Assertivas de entrada
*     O tabuleiro passado como par�metro existe na mem�ria
*     A coordenada passada como par�metro faz parte do tabuleiro
*     Existe uma pe�a nas coordenadas passadas
*
*  $AS Assertivas de sa�da
*     O tabuleiro continua existindo
*     Coordenada passada como par�metro est� vazia
*     Nenhuma casa est� amea�ada pela casa passada como par�metro
*
*  $FV Valor retornado
*     TAB_CondRetOK              - retirada de pe�a bem sucedida
*     TAB_CondRetNaoExisteCoord  - coordenadas n�o existem
*     TAB_CondRetPecaNaoExiste   - coordenadas n�o possuem pe�a
*
***********************************************************************/
TAB_tpCondRet TAB_RetirarPeca(TAB_tpTabuleiro ptabuleiro, int i, char j);


/***********************************************************************
*
*  $FC Fun��o: TAB &Criar tabuleiro
*
*  $ED Descri��o da fun��o
*     Obtem um ponteiro para um tabuleiro gen�rico.
*
*  $EP Par�metros
*     ptabuleiro - ponteiro para o tabuleiro a ser criado
*
*  $AE Assertivas de entrada
*     O tabuleiro passado como par�metro deve existir e estar alocado.
*
*  $AS Assertivas de sa�da
*     O tabuleiro � devidamente criado e suas casas iniciadas.
*
*  $FV Valor retornado
*     TAB_CondRetOK              - Tabuleiro criado de forma bem sucedida
*     TAB_CondRetFaltouMemoria   - faltou mem�ria
*
***********************************************************************/
TAB_tpCondRet TAB_CriarTabuleiro(TAB_tpTabuleiro ptabuleiro);


/***********************************************************************
*
*  $FC Fun��o: TAB &Destruir tabuleiro
*
*  $ED Descri��o da fun��o
*     Esvazia todas as casas de um tabuleiro e libera ele da mem�ria.
*
*  $EP Par�metros
*     ptabuleiro - ponteiro para o tabuleiro a ser destru�do
*
*  $AE Assertivas de entrada
*     O tabuleiro passado como par�metro deve existir e estar alocado.
*
*  $AS Assertivas de sa�da
*     O tabuleiro � devidamente destru�do.
*
*  $FV Valor retornado
*     TAB_CondRetOK                   - Tabuleiro destru�do sem problema
*     TAB_CondRetTabuleiroNaoExiste   - Tabuleiro passado n�o existe
*
***********************************************************************/
TAB_tpCondRet TAB_DestruirTabuleiro(TAB_tpTabuleiro *ptabuleiro);

/***********************************************************************
*
*  $FC Fun��o: TAB &Alocar tabuleiro
*
*  $ED Descri��o da fun��o
*     Aloca devidamente um tabuleiro gen�rico.
*
*  $EP Par�metros
*	  linha				- um n�mero inteiro do total de linhas do tabuleiro
*	  coluna			- uma letra que informa o total de colunas do tabuleiro
*
*  $AE Assertivas de entrada
*     Deve existir a linha e a coluna que definem o tamanho do tabuleiro.
*
*  $AS Assertivas de sa�da
*     Um tabuleiro � criado com tamanho definidos pelos valores da coluna e da linha.
*
*  $FV Valor retornado
*     TAB_tpTabuleiro		- ponteiro para o tabuleiro
*
***********************************************************************/
TAB_tpTabuleiro TAB_AlocarTabuleiro(int linha, char coluna);


#undef TABULEIRO_EXT

/********** Fim do m�dulo de defini��o: TAB  Tabuleiro duplamente encadeada **********/

#else
#endif