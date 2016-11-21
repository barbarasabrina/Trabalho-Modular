#if ! defined( JOGO_ )
#define JOGO_
/***************************************************************************
*
*  $MCD M�dulo de defini��o: JGO  Jogo
*
*  Arquivo gerado:              JOGO.h
*  Letras identificadoras:      JGO
*
*  Nome da base de software:    Arcabou�o para a automa��o de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\JOGO.BSW
*
*  Projeto: INF 1301 / 1628 Automatiza��o dos testes de m�dulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: avs , rfv, bshmc, llar
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    Data     Observa��es
*   5     bshmc,rfv,llar 10/10/2016		modifica��es do modulo de jogo
*     4       avs   01/fev/2006 criar linguagem script simb�lica
*     3       avs   08/dez/2004 uniformiza��o dos exemplos
*     2       avs   07/jul/2003 unifica��o de todos os m�dulos em um s� projeto
*     1       avs   16/abr/2003 in�cio desenvolvimento
*
*  $ED Descri��o do m�dulo
*		Implementa jogos de tabuleiro.
*		Podem existir n jogos em opera��o simultaneamente.
*		As jogos possuem uma cabe�a encapsulando o seu estado.
*
*		Cada jogo � homog�neo quanto ao tipo dos dados que armazena.
*		Cada elemento da jogo referencia o valor que cont�m.
*
*		Os ponteiros para os dados s�o copiados para elementos da jogo.
*       N�o � copiado o valor apontado por estes ponteiros.
*
*		O controle da destrui��o do valor de um elemento a ser exclu�do
*       � realizado por uma fun��o fornecida pelo usu�rio.
*
*		Cada jogo referencia uma fun��o que determina como devem ser
*       desalocados os dados nela contidos.
*
*		A fun��o de libera��o dos valores contidos nos elementos deve
*       assegurar a libera��o de todos os espa�os refer�nciados pelo
*       valor contido em um elemento.
*       Esta fun��o � chamada antes de se desalocar um elemento
*       de uma jogo.
*       Caso n�o seja necess�rio desalocar o valor referenciado pelo
*       elemento, o ponteiro para a fun��o de libera��o poder� ser NULL .
*       Caso o elemento da jogo seja a �nica �ncora do valor referenciado,
*       esta fun��o deve promover a destrui��o (free) desse valor e
*       de todos os dados nele ancorados.
*
***************************************************************************/

#if defined( JOGO_OWN )
#define JOGO_EXT
#else
#define JOGO_EXT extern
#endif

/***** Declara��es exportadas pelo m�dulo *****/

/* Tipo refer�ncia para uma jogo */

typedef struct JGO_tagJogo * JGO_tppJogo;

/***********************************************************************
*
*  $TC Tipo de dados: JGO Condi��es de retorno
*
*
*  $ED Descri��o do tipo
*		Condi��es de retorno das fun��es da jogo
*
***********************************************************************/

typedef enum {

	JGO_CondRetOK = 0,
	/* Concluiu corretamente */

	JGO_CondRetNoNaoExiste = 1,
	/* Foi atingido o fim de jogo */

	JGO_CondRetJogoVazia = 2,
	/* A jogo n�o cont�m elementos */

	JGO_CondRetJogoNaoExiste = 3,
	/* Jogo n�o existe*/

	JGO_CondRetNoCorrenteEhUltimo = 4,
	/* N� corrente � o ultimo elemento da jogo*/

	JGO_CondRetNoCorrenteEhPrimeiro = 5,
	/* N� corrente � o primeiro elemento da jogo*/

	JGO_CondRetFaltouMemoria = 6
	/* Faltou mem�ria ao tentar criar um elemento de jogo */

} JGO_tpCondRet;


/***********************************************************************
*
*  $FC Fun��o: JGO  &Criar jogo
*
*  $ED Descri��o da fun��o
*		Cria uma jogo duplamente encadeada.
*		� fornecido um identificador e este � associado � jogo.
*
*  $AS Assertiva de Saida
*		O ponteiro para jogo fornecida como parametro passa a apontar para a jogo criada
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
*		Se executou corretamente retorna o ponteiro para a jogo e a condi��o de retorno de movimenta��o bem sucedida.
*		Este ponteiro ser� utilizado pelas fun��es que manipulem esta jogo.
*
*		Se ocorreu algum erro, por exemplo falta de mem�ria ou dados errados,
*		a fun��o retornar� NULL e a condi��o de retorno faltou mem�ria.
*		N�o ser� dada mais informa��o quanto ao problema ocorrido.
*
*  $FV Valor retornado
*		JGO_CondRetOK				- cria��o de jogo bem sucedida
*		JGO_CondRetFaltouMemoria	- faltou memoria
*
***********************************************************************/

JGO_tpCondRet JGO_CriarJogo(
	void(*ExcluirValor) (char * pDado), char * idJogo, JGO_tppJogo pJogo);

/***********************************************************************
*
*  $FC Fun��o: JGO  &Iniciar Jogo
*
*  $ED Descri��o da fun��o
*		Avan�a o elemento corrente para o pr�ximo elemento na jogo
*		Se existir um pr�ximo elemento, o ponteiro corrente avan�a.
*		Se n�o existir um pr�ximo elemento, o ponteiro corrente permanece como ultimo
*		Se n� corrente n�o existir, a jogo est� vazia
*
*  $AE Assertiva de Entrada
*		A jogo existe.
*		A jogo deve ter pelo menos um elemento.
*		Caso contr�rio, a jogo est� vazia.
*		N� corrente deve apontar para pelo menos um elemento anterior ao �ltimo.
*		Caso contr�rio, n� corrente aponta para �ltimo elemento da jogo.
*		Valem as assertivas estruturais de jogo duplamente encadeada com cabe�a.
*
*  $AS Assertiva de Saida
*		Valem as assertivas estruturais de jogo duplamente encadeada com cabe�a.
*		Nos casos onde h� mais de um elemento na jogo e o n� estiver em qualquer posi��o
*		exceto o �ltimo, a movimenta��o foi bem sucedida.
*		Caso esteja no �ltimo elemento ou a jogo apenas possuia um elemento, n�o houve movimenta��o
*		e n� � o �ltimo elemento da jogo.
*		Caso n�o possua elementos, a jogo estava vazia e tamb�m n�o houve movimenta��o.
*
*
*  $EP Par�metros
*		pJogo  - ponteiro para a jogo a ser manipulada
*		numElem - o n�mero de elementos a andar
*
*  $FV Valor retornado
*		CondRetOK						- movimenta��o bem sucedida
*		CondRetJogoVazia				- jogo vazia
*		CondRetNoCorrenteEhUltimo		- n� corrente � o �ltimo
*
***********************************************************************/

JGO_tpCondRet JGO_IniciarJogo(char* filename, LIS_tppLista listaPecasPossiveis, TAB_tpTabuleiro pTabuleiro);


/***********************************************************************
*
*  $FC Fun��o: JGO  &Finalizar jogo
*
*  $ED Descri��o da fun��o
*		Destr�i o jogo fornecido.
*		O par�metro ponteiro para a jogo n�o � modificado.
*		Se ocorrer algum erro durante a destrui��o, a jogo resultar�
*		estruturalmente incorreta.
*		OBS. n�o existe previs�o para poss�veis falhas de execu��o.
*
*  $AE Assertiva de Entrada
*		O ponteiro para a jogo fornecida como parametro deve conter uma jogo para ser excluida.
*		Caso contr�rio o ponteiro para jogo n�o deve ser tratado para destrui��o.
*
*  $AS Assertiva de Saida
*		A jogo fornecida como parametro se existia, foi destru�da. Caso contr�rio,
*		a jogo j� n�o existe.
*
*  $EP Par�metros
*		pJogo  - ponteiro para a jogo a ser manipulada
*
*  $FV Valor retornado
*		JGO_CondRetOK				- exclus�o OK
*		JGO_CondRetJogoNaExiste	- jogo n�o existe
*
***********************************************************************/

JGO_tpCondRet JGO_FinalizarJogo(JGO_tppJogo pJogo);

/***********************************************************************
*
*  $FC Fun��o: JGO  &Verifica se o jogo est� em check
*
*  $ED Descri��o da fun��o
*     Elimina todos os elementos, sem contudo eliminar a jogo
*
*  $EP Par�metros
*     pJogo - ponteiro para a jogo a ser esvaziada
*
***********************************************************************/

JGO_tpCondRet JGO_VerificaCheck(TAB_tpTabuleiro pTabuleiro, char * check);

/***********************************************************************
*
*  $FC Fun��o: JGO  &Realizar o movimento do jogo no Tabuleiro
*
*  $ED Descri��o da fun��o
*     Elimina todos os elementos, sem contudo eliminar a jogo
*
*  $EP Par�metros
*     pJogo - ponteiro para a jogo a ser esvaziada
*
***********************************************************************/

JGO_tpCondRet JGO_RealizarMovimento(LIS_tppLista listaPecasPossiveis, TAB_tpTabuleiro pTabuleiro);


/***********************************************************************
*
*  $FC Fun��o: JGO  &Mostrar Tabuleiro padr�o
*
*  $ED Descri��o da fun��o
*     Apresenta, na tela do jogador, o tabuleiro.
*
*
*  $AE Assertiva de Entrada
*		Um tabuleiro existe.
*		Valem as assertivas estruturais de tabuleiro.
*
*  $AS Assertiva de Saida
*		Valem as assertivas estruturais de tabuleiro.
*		Ser� exibido um tabuleiro na tela do jogador.
*       
*
*  $EP Par�metros
*        ptabuleiro - ponteiro para o tabuleiro do jogo (?PODE SER NULL?)
*
*
*  $FV Valor retornado
*		JGO_CondRetOK					- apresenta��o bem sucedida
*		JGO_CondRetNaoExisteTabuleiro	- n�o existe tabuleiro
*
***********************************************************************/

JGO_tpCondRet JGO_MostrarTabuleiro(TAB_tpTabuleiro ptabuleiro);


#undef JOGO_EXT

/********** Fim do m�dulo de defini��o: JGO  Jogo de tabuleiro **********/

#else
#endif