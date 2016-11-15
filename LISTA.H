#if ! defined( LISTA_ )
#define LISTA_
/***************************************************************************
*
*  $MCD M�dulo de defini��o: LIS  Lista duplamente encadeada
*
*  Arquivo gerado:              LISTA.h
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
*  $ED Descri��o do m�dulo
*		Implementa listas gen�ricas duplamente encadeadas.
*		Podem existir n listas em opera��o simultaneamente.
*		As listas possuem uma cabe�a encapsulando o seu estado.
*
*		Cada lista � homog�nea quanto ao tipo dos dados que armazena.
*		Cada elemento da lista referencia o valor que cont�m.
*
*		Os ponteiros para os dados s�o copiados para elementos da lista.
*       N�o � copiado o valor apontado por estes ponteiros.
*
*		O controle da destrui��o do valor de um elemento a ser exclu�do
*       � realizado por uma fun��o fornecida pelo usu�rio.
*
*		Cada lista referencia uma fun��o que determina como devem ser
*       desalocados os dados nela contidos.
*
*		A fun��o de libera��o dos valores contidos nos elementos deve
*       assegurar a libera��o de todos os espa�os refer�nciados pelo
*       valor contido em um elemento.
*       Esta fun��o � chamada antes de se desalocar um elemento
*       de uma lista.
*       Caso n�o seja necess�rio desalocar o valor referenciado pelo
*       elemento, o ponteiro para a fun��o de libera��o poder� ser NULL .
*       Caso o elemento da lista seja a �nica �ncora do valor referenciado,
*       esta fun��o deve promover a destrui��o (free) desse valor e
*       de todos os dados nele ancorados.
*
***************************************************************************/
 
#if defined( LISTA_OWN )
   #define LISTA_EXT
#else
   #define LISTA_EXT extern
#endif

/***** Declara��es exportadas pelo m�dulo *****/

/* Tipo refer�ncia para uma lista */

typedef struct LIS_tagLista * LIS_tppLista ;

/***********************************************************************
*
*  $TC Tipo de dados: LIS Condi��es de retorno
*
*
*  $ED Descri��o do tipo
*		Condi��es de retorno das fun��es da lista
*
***********************************************************************/

   typedef enum {

         LIS_CondRetOK = 0,
               /* Concluiu corretamente */

         LIS_CondRetNoNaoExiste = 1,
               /* N� n�o existe na lista */

		 LIS_CondRetListaVazia = 2,
			  /* A lista n�o cont�m elementos */

         LIS_CondRetListaNaoExiste = 3,
               /* Lista n�o existe*/

		 LIS_CondRetNoCorrenteEhUltimo = 4,
				/* N� corrente � o ultimo elemento da lista*/
		
		 LIS_CondRetNoCorrenteEhPrimeiro = 5,
				/* N� corrente � o primeiro elemento da lista*/

         LIS_CondRetFaltouMemoria = 6
               /* Faltou mem�ria ao tentar criar um elemento de lista */

   } LIS_tpCondRet ;


/***********************************************************************
*
*  $FC Fun��o: LIS  &Criar lista
*
*  $ED Descri��o da fun��o
*		Cria uma lista gen�rica duplamente encadeada.
*		Os poss�veis tipos s�o desconhecidos a priori.
*		A tipagem � implicita.
*		N�o existe identificador de tipo associado � lista.
*
*  $AS Assertiva de Saida
*		O ponteiro para lista fornecida como parametro passa a apontar para a lista criada 
*		cujo identificador s�o os caracteres que foram fornecidos tamb�m como parametro.
*		Em caso de falta de mem�ria, o ponteiro apontar� para um ponteiro nulo.
*
*  $EP Par�metros
*		ExcluirValor  - ponteiro para a fun��o que processa a
*                     exclus�o do valor referenciado pelo elemento
*                     a ser exclu�do.
*                     Ver descri��o do m�dulo.
*
*  $FV Valor retornado
*		Se executou corretamente retorna o ponteiro para a lista.
*		Este ponteiro ser� utilizado pelas fun��es que manipulem esta lista.
*
*		Se ocorreu algum erro, por exemplo falta de mem�ria ou dados errados,
*		a fun��o retornar� NULL.
*		N�o ser� dada mais informa��o quanto ao problema ocorrido.
*
*  $FV Valor retornado
*		LIS_CondRetOK				- cria��o de lista bem sucedida
*		LIS_CondRetFaltouMemoria	- faltou memoria
*
***********************************************************************/

   LIS_tpCondRet LIS_CriarLista(
	   void(*ExcluirValor) (char * pDado), char * idLista, LIS_tppLista pLista);

/***********************************************************************
*
*  $FC Fun��o: LIS  &Ir pr�ximo elemento
*
*  $ED Descri��o da fun��o
*		Avan�a o elemento corrente para o pr�ximo elemento na lista
*		Se existir um pr�ximo elemento, o ponteiro corrente avan�a.
*		Se n�o existir um pr�ximo elemento, o ponteiro corrente permanece como ultimo
*		Se n� corrente n�o existir, a lista est� vazia
*
*  $AE Assertiva de Entrada
*		A lista existe. 
*		A lista deve ter pelo menos um elemento. 
*		Caso contr�rio, a lista est� vazia.
*		N� corrente deve apontar para pelo menos um elemento anterior ao �ltimo.
*		Caso contr�rio, n� corrente aponta para �ltimo elemento da lista.
*		Valem as assertivas estruturais de lista duplamente encadeada com cabe�a.
*
*  $AS Assertiva de Saida
*		Valem as assertivas estruturais de lista duplamente encadeada com cabe�a.		
*		Nos casos onde h� mais de um elemento na lista e o n� estiver em qualquer posi��o 
*		exceto o �ltimo, a movimenta��o foi bem sucedida.
*		Caso esteja no �ltimo elemento ou a lista apenas possuia um elemento, n�o houve movimenta��o
*		e n� � o �ltimo elemento da lista.
*		Caso n�o possua elementos, a lista estava vazia e tamb�m n�o houve movimenta��o.
*
*
*  $EP Par�metros
*		pLista  - ponteiro para a lista a ser manipulada
*		numElem - o n�mero de elementos a andar
*
*  $FV Valor retornado
*		CondRetOK						- movimenta��o bem sucedida
*		CondRetListaVazia				- lista vazia
*		CondRetNoCorrenteEhUltimo		- n� corrente � o �ltimo
*
***********************************************************************/

   LIS_tpCondRet LIS_IrProximoElemento(LIS_tppLista pLista);

   
/***********************************************************************
*
*  $FC Fun��o: LIS  &Destruir lista
*
*  $ED Descri��o da fun��o
*		Destr�i a lista fornecida.
*		O par�metro ponteiro para a lista n�o � modificado.
*		Se ocorrer algum erro durante a destrui��o, a lista resultar�
*		estruturalmente incorreta.
*		OBS. n�o existe previs�o para poss�veis falhas de execu��o.
*
*  $AE Assertiva de Entrada
*		O ponteiro para a lista fornecida como parametro deve conter uma lista para ser excluida.
*		Caso contr�rio o ponteiro para lista n�o deve ser tratado para destrui��o.
*
*  $AS Assertiva de Saida
*		A lista fornecida como parametro se existia, foi destru�da. Caso contr�rio, 
*		a lista j� n�o existe.
*
*  $EP Par�metros
*		pLista  - ponteiro para a lista a ser manipulada
*
*  $FV Valor retornado
*		LIS_CondRetOK				- exclus�o OK
*		LIS_CondRetListaNaExiste	- lista n�o existe
*
***********************************************************************/

   LIS_tpCondRet LIS_DestruirLista( LIS_tppLista pLista ) ;

 
/***********************************************************************
*
*  $FC Fun��o: LIS  &Alocar memoria para lista
*
*  $ED Descri��o da fun��o
*		Aloca mem�ria para uma lista duplamente encadeada com cabe�a
*
*  $AS Assertiva de Saida
*		Uma lista devidamente alocada � retornada.
*
*  $FV Valor retornado
*		LIS_tppLista	-ponteiro para a lista devidamente alocada
*
***********************************************************************/

   LIS_tppLista LIS_AlocarLista();


/***********************************************************************
*
*  $FC Fun��o: LIS  &Esvaziar lista
*
*  $ED Descri��o da fun��o
*     Elimina todos os elementos, sem contudo eliminar a lista
*
*  $EP Par�metros
*     pLista - ponteiro para a lista a ser esvaziada
*
***********************************************************************/

   void LIS_EsvaziarLista(LIS_tppLista pLista);


#undef LISTA_EXT

/********** Fim do m�dulo de defini��o: LIS  Lista duplamente encadeada **********/

#else
#endif