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
*		Implementa um jogo de xadrez num tabuleiro 8x8.
*		Este tabuleiro possui 64 casas.
*		Sendo as linhas representadas por n�meros de 1-8.
*		E as colunas representadas por caracteres de A-H.
*		A contagem para as coordenadas come�a na posi��o linha 1 coluna A,
*		que ser� representada exatamente na parte inferior esquerda, sendo assim,
*		a posi��o linha 8 coluna H ser� representada na parte superior direita.
*
*
***************************************************************************/
#include "LISTA.H"
#include "TABULEIRO.H"
#include "PECA.H"

#if defined( JOGO_OWN )
#define JOGO_EXT
#else
#define JOGO_EXT extern
#endif

/***********************************************************************
*
*  $TC Tipo de dados: JGO Condi��es de retorno de um jogo
*
*
*  $ED Descri��o do tipo
*		Condi��es de retorno das fun��es do jogo
*
***********************************************************************/

typedef enum {

	JGO_CondRetOK = 0,
	/* Concluiu corretamente */

	JGO_CondRetNoNaoExiste = 1,
	/* Tabuleiro n�o existe */

	JGO_CondRetListaVazia = 2,
	/* A lista est� vazia */

	JGO_CondRetTabuleiroNaoExiste = 3,
	/* Tabuleiro n�o existe*/

	JGO_CondRetListaNaoExiste = 4,
	/* Lista n�o existe */

	JGO_CondRetNoCorrenteEhPrimeiro = 5,
	/* N� corrente � o primeiro elemento da jogo*/

	JGO_CondRetFaltouMemoria = 6
	/* Faltou mem�ria ao tentar criar um elemento de jogo */

} JGO_tpCondRet;

/***********************************************************************
*
*  $FC Fun��o: JGO  &Iniciar Jogo
*
*  $ED Descri��o da fun��o
*		D� inicio ao jogo, criando o tabuleiro e posicionando as pe�as nas casas corretamente.
*
*
*  $AE Assertiva de Entrada
*		N� corrente deve apontar para pelo menos um elemento anterior ao �ltimo.
*		Caso contr�rio, n� corrente aponta para �ltimo elemento da jogo.
*		Valem as assertivas estruturais de jogo duplamente encadeada com cabe�a.
*
*  $AS Assertiva de Saida
*		Valem as assertivas de tabuleiro e de lista duplamente encadeada.
*		Uma lista de pe�as dispon�veis estar� dispon�vel para o jogador.
*		Um arquivo com as pe�as e seus movimentos ser� disponibilizado pelo parametro filename.
*		Um tabuleiro estar� preenchido para iniciar o jogo.
*
*
*  $EP Par�metros
*		filename						- nome do arquivo que cont�m as informa��es das pe�as e seus movimentos.
*		listaPecasPossiveis				- vetor com as pe�as dispon�veis para o jogo.
*		pTabuleiro						- ponteiro para o tabuleiro do jogo
*
*  $FV Valor retornado
*		CondRetOK						- movimenta��o bem sucedida
*		CondRetJogoVazia				- jogo vazia
*		CondRetNoCorrenteEhUltimo		- n� corrente � o �ltimo
*
***********************************************************************/

JGO_tpCondRet JGO_IniciarJogo(char * filename, PCA_tpVetPeca listaPecasPossiveis, TAB_tpTabuleiro pTabuleiro);


/***********************************************************************
*
*  $FC Fun��o: JGO  &Finalizar jogo
*
*  $ED Descri��o da fun��o
*		Finaliza o jogo de tabuleiro.
*		O par�metro ponteiro para o tabuleiro n�o � modificado.
*		Se ocorrer algum erro durante a destrui��o, o tabuleiro resultar�
*		estruturalmente incorreto.
*		OBS. n�o existe previs�o para poss�veis falhas de execu��o.
*
*  $AE Assertiva de Entrada
*		Pode existir um tabuleiro.
*		Caso contr�rio o ponteiro para jogo n�o deve ser tratado para destrui��o.
*
*  $AS Assertiva de Saida
*		As pe�as e casa do tabuleiro s�o liberados e o tabuleiro destru�do.
*
*  $EP Par�metros
*		ptabuleiro  - ponteiro para o tabuleiro a ser manipulado
*
*  $FV Valor retornado
*		JGO_CondRetOK				- exclus�o OK
*		JGO_CondRetJogoNaExiste	- jogo n�o existe
*
***********************************************************************/

JGO_tpCondRet JGO_FinalizarJogo(TAB_tpTabuleiro ptabuleiro);

/***********************************************************************
*
*  $FC Fun��o: JGO  &Verifica se o jogo est� em check
*
*  $ED Descri��o da fun��o
*     Verifica se o jogo est� check ou check mate.
*
*
*  $AE Assertiva de Entrada
*		Deve existir um tabuleiro v�lido.
*		Valem as assertivas estruturais de tabuleiro.
*
*  $AS Assertiva de Saida
*		Valem as assertivas estruturais de tabuleiro.
*		Ser� obtida informa��o de check(1), check mate(2) ou nulo(0) em rela��o ao estado do jogo.
*
*
*  $EP Par�metros
*		pTabuleiro			- ponteiro para o tabuleiro
*		check				- ponteiro para informa��o de check(1), check mate(2) ou nulo(0)
*
***********************************************************************/

JGO_tpCondRet JGO_VerificaCheck(TAB_tpTabuleiro pTabuleiro, int * check);

/***********************************************************************
*
*  $FC Fun��o: JGO  &Realizar o movimento do jogo no Tabuleiro
*
*  $ED Descri��o da fun��o
*     O m�dulo de jogo ir� obter do jogador informa��o do movimento que ele deseja e
*	  realizar o movimento caso o movimento seja v�lido.
*
*
*  $AE Assertiva de Entrada
*		Deve existir uma lista de pe�as dispon�veis no jogo.
*		Deve existir um tabuleiro v�lido.
*		Valem as assertivas estruturais de tabuleiro e de lista.
*
*  $AS Assertiva de Saida
*		Valem as assertivas estruturais de tabuleiro e de lista.
*		Um movimento pode ser ou n�o realizado.
*
*
*  $EP Par�metros
*		listaPecasDisponiveis	- vetor com as pe�as dispon�veis
*		pTabuleiro				- ponteiro para o tabuleiro do jogo
*
***********************************************************************/

JGO_tpCondRet JGO_RealizarMovimento(PCA_tpVetPeca listaPecasDisponiveis, TAB_tpTabuleiro pTabuleiro);


/***********************************************************************
*
*  $FC Fun��o: JGO  &Mostrar Tabuleiro padr�o
*
*  $ED Descri��o da fun��o
*     Apresenta, na tela do jogador, o estado atual do tabuleiro do jogo.
*
*
*  $AE Assertiva de Entrada
*		Ou tabuleiro existe ou � nulo.
*		Valem as assertivas estruturais de tabuleiro.
*
*  $AS Assertiva de Saida
*		Valem as assertivas estruturais de tabuleiro.
*		Pode ou n�o ser exibido um tabuleiro na tela do jogador.
*
*
*  $EP Par�metros
*        ptabuleiro - ponteiro para o tabuleiro do jogo.
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
