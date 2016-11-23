#if ! defined( TABULEIRO_ )
#define TABULEIRO_


#define LISTA_OWN
#include "LISTA.h"
#undef LISTA_OWN

/***************************************************************************
*
*  $MCD Módulo de definição: TAB  Tabuleiro genérico
*
*  Arquivo gerado:              TABULEIRO.h
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
*	 5	bshmc,rfv,llar  10/10/2016 implementação do muodulo de tabuleiro
*     4       avs   01/fev/2006 criar linguagem script simbólica
*     3       avs   08/dez/2004 uniformização dos exemplos
*     2       avs   07/jul/2003 unificação de todos os módulos em um só projeto
*     1       avs   16/abr/2003 início desenvolvimento
*
*  $ED Descrição do módulo
*		Implementa tabuleiros genéricos.
*		Podem existir n tabuleiros em operação simultaneamente.
*
*		Cada tabuleiro é homogêneo quanto ao tipo dos dados que armazena.
*		Cada elemento do tabuleiro é chamado de casa e cada casa possui informação da peça que contém, caso exista, e uma lista de peças ameaçantes e de peças de ameaçadas.
*
*		O controle da destruição da peça de uma casa a ser excluída
*       é realizado por uma função fornecida para o usuário.
*
*		Cado tabuleiro referencia uma função que determina como devem ser
*       desalocados os dados nela contidos.
*
*		A função de liberação dos valores contidos nos elementos deve
*       assegurar a liberação de todos os espaços referênciados pelo
*       valor contido em cada elemento.
*       Esta função é chamada antes de se desalocar um elemento
*       de um tabuleiro.
*       Caso não seja necessário desalocar o valor referenciado pelo
*       elemento, o ponteiro para a função de liberação poderá ser NULL .
*       Caso a casa do tabuleiro seja a única âncora do valor referenciado,
*       esta função deve promover a destruição (free) desse valor e
*       de todos os dados nele ancorados.
*
***************************************************************************/

#if defined( TABULEIRO_OWN )
#define TABULEIRO_EXT
#else
#define TABULEIRO_EXT extern
#endif

/***** Declarações exportadas pelo módulo *****/

/* Tipo referência para um tabuleiro */

typedef struct TAB_tabuleiro * TAB_tpTabuleiro;

/***********************************************************************
*
*  $TC Tipo de dados: TAB Condições de retorno
*
*
*  $ED Descrição do tipo
*		Condições de retorno das funções do tabuleiro
*
***********************************************************************/

typedef enum {

	TAB_CondRetOK = 0,
	/* Movimentação bem sucedida */

	TAB_CondRetCasaOcupada = 1,
	/* A casa do tabuleiro se encontra cheia, já ocupada */

	TAB_CondRetTabuleiroVazio = 2,
	/* O tabuleiro não contém peça em nenhuma casa */

	TAB_CondRetTabuleiroNaoExiste = 3,
	/* Tabuleiro não existe */

	TAB_CondRetCoordNaoExiste = 4,
	/* Coordenadas não existem no tabuleiro */

	TAB_CondRetPecaNaoExiste = 5,
	/* Não há peça na casa do tabuleiro ou a identificação da peça fornecida não existe */

	TAB_CondRetFaltouMemoria = 6,
	/* Faltou memória ao tentar criar um elemento do tabuleiro */

	TAB_CondRetCasaNaoExiste = 7,
	/* Casa não existe, está nula */

	TAB_CondRetListaAmeacanteVazia = 8,
	/* Lista de ameacante está nula*/
		
	TAB_CondRetMovimentoInvlaido = 9
	/*Movimento não foi Validado*/


} TAB_tpCondRet;

/***********************************************************************
*
*  $FC Função: TAB  &Inserir peça no tabuleiro
*
*  $ED Descrição da função
*		Insere uma peça no tabuleiro.
*
*  $AE Assertiva de Entrada
*		Deve existir um tabuleiro.
*		Deve existir a coordenada para a casa no tabuleiro (linha e coluna).
*		Deve existir uma peça a ser inserida no tabuleiro.
*
*  $AS Assertiva de Saida
*		São válidas as assertivas de entrada.
*		A casa ,cuja coordenada foi informada, é preenchida com o valor de identificação da peça.
*		Em caso de falta de memória, o ponteiro apontará para um ponteiro nulo.
*
*
*  $EP Parâmetros
*		ptabuleiro					- ponteiro para o tabuleiro
*		linha						- ponteiro para a coordenada linha da casa
*		coluna						- ponteiro para a coordenada coluna da casa
*		peca						- ponteiro para a peça
*
*  $FV Valor retornado
*		Se executou corretamente retorna o ponteiro para o tabuleiro e a condição de movimentação bem sucedida.
*		Este ponteiro será utilizado pelas funções que manipulem este tabuleiro.
*
*  $FV Valor retornado
*		TAB_CondRetOK					- criação de tabuleiro bem sucedida
*		TAB_CondRetTabuleiroNaoExiste	- tabuleiro não existe
*		TAB_CondRetCoordNaoExiste		- coordenadas não existem
*		TAB_CondRetCasaOcupada			- casa já está ocupada
*
***********************************************************************/

TAB_tpCondRet TAB_InserirPeca(TAB_tpTabuleiro ptabuleiro, int linha, char coluna, void * peca);

/***********************************************************************
*
*  $FC Função: TAB  &Obter Peça
*
*  $ED Descrição da função
*		Obtém a peça que se encontra nas coordenadas da casa do tabuleiro.
*
*  $AE Assertiva de Entrada
*		Deve existir um tabuleiro.
*		Devem existir coordenadas válidas referentes à casa no tabuleiro(linha e coluna).
*
*
*  $AS Assertiva de Saída
*		São válidas as assertivas de entrada.
*		Uma identificação de peça será obtida caso as informações da linha e coluna da casa
*		no tabuleiro sejam válidas e exista uma peça na respectiva casa.
*		Caso não exista peça na casa informada, será obtido da função um ponteiro nulo.
*
*
*  $EP Parâmetros
*		ptabuleiro					- ponteiro para o tabuleiro
*		linha						- ponteiro para a coordenada linha da casa
*		coluna						- ponteiro para a coordenada coluna da casa
*		peca						- ponteiro para a peça do tabuleiro
*
*
*  $FV Valor retornado
*		TAB_CondRetOK					- criação de tabuleiro bem sucedida
*		TAB_CondRetTabuleiroNaoExiste	- tabuleiro não existe
*		TAB_CondRetCoordNaoExiste		- coordenadas não existem
*
***********************************************************************/

TAB_tpCondRet TAB_ObterPeca(TAB_tpTabuleiro ptabuleiro, int linha, char coluna, void * peca);


/***********************************************************************
*
*  $FC Função: TAB &Retirar peça
*
*  $ED Descrição da função
*     Retira uma peça de uma coordenada do tabuleiro.
*     Qual o tipo de peça presente é desconhecido a priori.
*     Caso não exista peça nas coordenadas enviadas a função não retorna mensagem de erro.
*
*
*  $EP Parâmetros
*     t - Ponteiro para o tabuleiro a ser utilizado
*     i - Caracter que representa a linha na qual a função deve atuar
*         Varia entre '1' e '8'
*     j - Caracter que representa a coluna na qual a função deve atuar
*         Varia entre 'A' e 'H'
*
*  $AE Assertivas de entrada
*     O tabuleiro passado como parâmetro existe na memória
*     A coordenada passada como parâmetro faz parte do tabuleiro
*     Existe uma peça nas coordenadas passadas
*
*  $AS Assertivas de saída
*     O tabuleiro continua existindo
*     Coordenada passada como parâmetro está vazia
*     Nenhuma casa está ameaçada pela casa passada como parâmetro
*
*  $FV Valor retornado
*     TAB_CondRetOK              - retirada de peça bem sucedida
*     TAB_CondRetNaoExisteCoord  - coordenadas não existem
*     TAB_CondRetPecaNaoExiste   - coordenadas não possuem peça
*
***********************************************************************/
TAB_tpCondRet TAB_RetirarPeca(TAB_tpTabuleiro ptabuleiro, int i, char j);


/***********************************************************************
*
*  $FC Função: TAB &Criar tabuleiro
*
*  $ED Descrição da função
*     Obtem um ponteiro para um tabuleiro genérico.
*
*  $EP Parâmetros
*     ptabuleiro - ponteiro para o tabuleiro a ser criado
*
*  $AE Assertivas de entrada
*     O tabuleiro passado como parâmetro deve existir e estar alocado.
*
*  $AS Assertivas de saída
*     O tabuleiro é devidamente criado e suas casas iniciadas.
*
*  $FV Valor retornado
*     TAB_CondRetOK              - Tabuleiro criado de forma bem sucedida
*     TAB_CondRetFaltouMemoria   - faltou memória
*
***********************************************************************/
TAB_tpCondRet TAB_CriarTabuleiro(TAB_tpTabuleiro ptabuleiro);


/***********************************************************************
*
*  $FC Função: TAB &Destruir tabuleiro
*
*  $ED Descrição da função
*     Esvazia todas as casas de um tabuleiro e libera ele da memória.
*
*  $EP Parâmetros
*     ptabuleiro - ponteiro para o tabuleiro a ser destruído
*
*  $AE Assertivas de entrada
*     O tabuleiro passado como parâmetro deve existir e estar alocado.
*
*  $AS Assertivas de saída
*     O tabuleiro é devidamente destruído.
*
*  $FV Valor retornado
*     TAB_CondRetOK                   - Tabuleiro destruído sem problema
*     TAB_CondRetTabuleiroNaoExiste   - Tabuleiro passado não existe
*
***********************************************************************/
TAB_tpCondRet TAB_DestruirTabuleiro(TAB_tpTabuleiro * ptabuleiro);

/***********************************************************************
*
*  $FC Função: TAB &Alocar tabuleiro
*
*  $ED Descrição da função
*     Aloca devidamente um tabuleiro genérico.
*
*  $EP Parâmetros
*	  linha				- um número inteiro do total de linhas do tabuleiro
*	  coluna			- uma letra que informa o total de colunas do tabuleiro
*
*  $AE Assertivas de entrada
*     Deve existir a linha e a coluna que definem o tamanho do tabuleiro.
*
*  $AS Assertivas de saída
*     Um tabuleiro é criado com tamanho definidos pelos valores da coluna e da linha.
*
*  $FV Valor retornado
*     TAB_tpTabuleiro		- ponteiro para o tabuleiro
*
***********************************************************************/
TAB_tpTabuleiro TAB_AlocarTabuleiro(int linha, char coluna);






/***********************************************************************
   *
   *  $FC Função: TAB  &Obter Lista Ameacantes
   *
   *  $ED Descrição da função
   *		Obtém a lista em que se encontra a lista de casas ameacantes.
   *
   *  $AE Assertiva de Entrada
   *		Um tabuleiro alocado previamente deve existir.
   *		Devem existir coordenadas válidas referentes à casa no tabuleiro.
   *		Deve existir uma lista de amecantes valida;
   *
   *
   *  $AS Assertiva de Saída
   *		São válidas as assertivas de entrada.
   *		Uma lista contendo os ameacantes será passada por referencia usando um ponteiro para char
   *		Caso as coordenadas não sejam válidas não ocorrerá passagem por referentcia.
   *
   *
   *  $EP Parâmetros
   *		ptabuleiro					- ponteiro para o tabuleiro
   *		linha						- ponteiro para a coordenada linha da casa
   *		coluna						- ponteiro para a coordenada coluna da casa
   *		Ameacantes					- ponteiro para a retorno por referencia da lsita de Ameacantes
   *
   *
   *  $FV Valor retornado
   *		TAB_CondRetOK					- obteve a lista com sucesso
   *
   ***********************************************************************/

TAB_tpCondRet TAB_ObterListaAmeacantes (TAB_tpTabuleiro ptabuleiro, int i, char j, LIS_tppLista *Ameacantes);


/***********************************************************************
*
*  $FC Função: TAB &Obter lista de ameaçados
*
*  $ED Descrição da função
*     Obtem um ponteiro para a lista de casas ameacadas pela peça presente na coordenada informada 
*     Caso não exista uma peça nas coordenadas informadas a lista obtida estará vazia
*
*  $EP Parâmetros
*     ptabuleiro - ponteiro para o tabuleiro a ser utilizado
*     i - Caracter que representa a linha na qual a função deve atuar
*         Varia entre '1' e '8'
*     j - Caracter que representa a coluna na qual a função deve atuar
*         Varia entre 'A' e 'H'
*     Ameacados - Ponteiro para aonde deve ser guardado o endereço da lista de casas ameacadas
                  pela peça presente nas coordenadas informadas 
*
*  $AE Assertivas de entrada
*     O tabuleiro passado como parâmetro existe na memória
*     A coordenada passada como parâmetro faz parte do tabuleiro
*
*  $AS Assertivas de saída
*     O tabuleiro continua existindo
*     Coordenada passada como parâmetro está vazia
*     Lista obtida tem sentido lógico
*
*  $FV Valor retornado
*     TAB_CondRetOK              - lista obtida com sucesso
*
***********************************************************************/

TAB_tpCondRet TAB_ObterListaAmeacados (TAB_tpTabuleiro ptabuleiro, int i, char j, LIS_tppLista *Ameacados);

/***********************************************************************
*
*  $FC Função: TAB &Exibir lista de ameaçantes
*
*  $ED Descrição da função
*     Exibe a lista de casas que ameaçaam a casa pesquisada
*
*  $EP Parâmetros
*     ptabuleiro - ponteiro para o tabuleiro a ser utilizado
*     i - Caracter que representa a linha na qual a função deve atuar
*         Varia entre '1' e '8'
*     j - Caracter que representa a coluna na qual a função deve atuar
*         Varia entre 'A' e 'H' 
*
*  $AE Assertivas de entrada
*     O tabuleiro passado como parâmetro existe na memória
*     A coordenada passada como parâmetro faz parte do tabuleiro
*
*  $AS Assertivas de saída
*     O tabuleiro continua existindo
*     Coordenada passada como parâmetro está vazia
*     Lista obtida tem sentido lógico
*	  Lista é impressa
*
*  $FV Valor retornado
*     TAB_CondRetOK              - lista impressa com sucesso
*
***********************************************************************/

TAB_tpCondRet TAB_ExibirListaAmeacantes(TAB_tpTabuleiro ptabuleiro, int i, char j);
/***********************************************************************
*
*  $FC Função: TAB &Exibir lista de ameaçados
*
*  $ED Descrição da função
*     Exibe a lista de casas ameaçadas pela casa pesquisada
*
*  $EP Parâmetros
*     ptabuleiro - ponteiro para o tabuleiro a ser utilizado
*     i - Caracter que representa a linha na qual a função deve atuar
*         Varia entre '1' e '8'
*     j - Caracter que representa a coluna na qual a função deve atuar
*         Varia entre 'A' e 'H' 
*
*  $AE Assertivas de entrada
*     O tabuleiro passado como parâmetro existe na memória
*     A coordenada passada como parâmetro faz parte do tabuleiro
*
*  $AS Assertivas de saída
*     O tabuleiro continua existindo
*     Coordenada passada como parâmetro está vazia
*     Lista obtida tem sentido lógico
*	  Lista é impressa
*
*  $FV Valor retornado
*     TAB_CondRetOK              - lista impressa com sucesso
*
***********************************************************************/

TAB_tpCondRet TAB_ExibirListaAmeacados(TAB_tpTabuleiro ptabuleiro, int i, char j);



TAB_tpCondRet TAB_MoverPeca(TAB_tpTabuleiro t, int origemI, char origemJ, int destinoI, char destinoJ);

#undef TABULEIRO_EXT

/********** Fim do módulo de definição: TAB  Tabuleiro duplamente encadeada **********/

#else
#endif
