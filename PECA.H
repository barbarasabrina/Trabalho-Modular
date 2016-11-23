#if ! defined( PECA_ )
#define PECA_
/***************************************************************************
*
*  $MCD Módulo de definição: PCA  Peça de tabuleiro
*
*  Arquivo gerado:              PECA.h
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
*  $ED Descrição do módulo
*		Implementa uma peça de tabuleiro.
*		Podem existir n peças em operação simultaneamente.
*
*		Cada peça é homogênea quanto ao tipo dos dados que armazena.
*		Cada elemento de peça possui um nome e uma cor.
*
*		Os ponteiros para os dados são copiados para as peças do tabuleiro.
*
*		O controle da destruição da peça de uma casa a ser excluída
*       é realizado por uma função fornecida para o usuário.
*
*		A função de liberação dos valores contidos nos elementos deve
*       assegurar a liberação de todos os espaços referênciados pelo
*       valor contido em cada elemento.
*       Esta função é chamada antes de se desalocar um elemento
*       de uma peça do tabuleiro.
*       Caso não seja necessário desalocar o valor referenciado pelo
*       elemento, o ponteiro para a função de liberação poderá ser NULL .
*       Caso a peça do tabuleiro seja a única âncora do valor referenciado,
*       esta função deve promover a destruição (free) desse valor e
*       de todos os dados nela ancorados.
*
***************************************************************************/

#if defined( PECA_OWN )
#define PECA_EXT
#else
#define PECA_EXT extern
#endif

/***** Declarações exportadas pelo módulo *****/

/* Tipo referência para uma peca */

typedef struct PCA_peca * PCA_tpPeca ;
typedef struct PCA_vetPeca * PCA_tpVetPeca ;

/***********************************************************************
*
*  $TC Tipo de dados: PCA Condições de retorno
*
*
*  $ED Descrição do tipo
*		Condições de retorno das funções do módulo peca
*
***********************************************************************/

typedef enum {

	PCA_CondRetOK = 0,
	/* Concluiu corretamente */

	PCA_CondRetPecaNaoExiste = 1,
	/* Peca passada como parâmetro não existe */

	PCA_CondRetErroNaLeituraDoArquivo = 2,
	/* Arquivo com todas as peças possíveis não está no formato certo */

	PCA_CondRetFaltouMemoria = 3,
	/* Faltou espaço na memórica dinâmica */

	PCA_CondRetMovimentoInvalido = 4
	/* Peca passada como parametro não pode realizar o movimento pedido */


} PCA_tpCondRet ;

/***********************************************************************
*
*  $FC Função: PCA  &Pegar Peca do Vetor de Pecas possiveis
*
*  $ED Descrição da função
*		Obtem peça que possui nome e cor iguais aos passados como parametro
*
*  $AE Assertiva de Entrada
*
*
*  $AS Assertiva de Saida
*		Caso a peça exista, a mesma é armazenada no endereço passado pela função anterior
*       Caso contrário, é retornado uma condição de erro apropriada
*
*  $EP Parâmetros
*		Possiveis - vetor com todas as pecas possiveis
*       resp      - endereço aonde a função deve guardar a peca
*       nome      - nome da peca desejada
*       cor       - cor da peca desejada
*
*  $FV Valor retornado
*		PCA_CondRetOK				- Executou OK
*		PCA_CondRetPecaNaExiste  	- Peca não existe
*
***********************************************************************/

PCA_tpCondRet PCA_PegarPecaDoVetor (PCA_tpVetPeca Possiveis, PCA_tpPeca * peca, char nome, char cor);

/***********************************************************************
*
*  $FC Função: PCA  &Obter Cor
*
*  $ED Descrição da função
*		Obtem cor da peca passada como parâmetro
*
*  $AE Assertiva de Entrada
*
*
*  $AS Assertiva de Saida
*		Caso a peça exista, a cor da mesma é armazenada no endereço passado pela função anterior
*       Caso contrário, é retornado uma condição de erro apropriada
*
*  $EP Parâmetros
*		peca - peca a ser analizada
*       c    - endereço aonde a função deve guardar a cor da peca
*
*  $FV Valor retornado
*		PCA_CondRetOK				- Executou OK
*		PCA_CondRetPecaNaExiste  	- Peca não existe
*
***********************************************************************/

PCA_tpCondRet PCA_ObterCor (PCA_tpPeca peca, char* c);


/***********************************************************************
*
*  $FC Função: PCA  &Obter Nome
*
*  $ED Descrição da função
*		Obtem nome da peca passada como parâmetro
*
*  $AE Assertiva de Entrada
*
*
*  $AS Assertiva de Saida
*		Caso a peça exista, a cor da mesma é armazenada no endereço passado pela função anterior
*       Caso contrário, é retornado uma condição de erro apropriada
*
*  $EP Parâmetros
*		peca - peca a ser analizada
*       n    - endereço aonde a função deve guardar o nome da peca
*
*  $FV Valor retornado
*		PCA_CondRetOK				- Executou OK
*		PCA_CondRetPecaNaExiste	    - Peca não existe
*
***********************************************************************/

PCA_tpCondRet PCA_ObterNome (PCA_tpPeca peca, char* n);


/***********************************************************************
*
*  $FC Função: PCA  &Validar Movimento
*
*  $ED Descrição da função
*		Confirma se a peca passada como parâmetro pode realizar o movimento também passado como parâmetro
*
*  $AE Assertiva de Entrada
*
*
*  $AS Assertiva de Saida
*		Caso a peça exista, e possa realizar o movimnto descrito a função deve retornar OK
*       Caso contrário, é retornado uma condição de erro apropriada
*
*  $EP Parâmetros
*		peca - peca a ser analizada
*       dx   - deslocamento horizontal da peca no movimento
*       dy   - deslocamento vertical da peca no movimento
*       atk  - representa se a peca está atacando outra ou não
*
*  $FV Valor retornado
*		PCA_CondRetOK				 - Executou OK
*		PCA_CondRetPecaNaExiste	     - Peca não existe
*       PCA_CondRetMovimentoInvalido - Peca não pode realizar o movimento pedido
*
***********************************************************************/

PCA_tpCondRet PCA_ValidarMovimento (PCA_tpPeca peca, int dx, int dy, int atk);


/***********************************************************************
*
*  $FC Função: PCA  &InicializarPecas
*
*  $ED Descrição da função
*		Inicializa todas as peças contidas no arquivo cujo nome foi passsado como parâmetro
*       e os coloca num vetor, cujo endereço é passado como parâmetro
*
*  $AE Assertiva de Entrada
*       O endereço passado como parametro não contém informação útil e pode ser sobrescrito
*
*  $AS Assertiva de Saida
*		Caso o arquivo exista e esteja no formato descrito no LEIAME.TXT,essa função deve
passar para a anterior uma lista devidamente alocada e preenchida com todas as pecas contidas no arquivo
*       Caso contrário, é retornado uma condição de erro apropriada
*
*  $EP Parâmetros
*		filename  - nome do arquivo de texto no qual se encontram as descrições das peças
*       Possiveis - endereço aonde deve ser retornada o vetor de pecas possiveis
*
*  $FV Valor retornado
*		PCA_CondRetOK				      - Executou OK
*		PCA_CondRetFaltouMemoria	      - Nao ouve espaço suficiente para gerar no vetor
*       PCA_CondRetErroNaLeituraDoArquivo - O arquivo nao existe ou nao esta organizado de forma correta
*
***********************************************************************/

PCA_tpCondRet PCA_InicializarPecas (char* filename, PCA_tpVetPeca *Possiveis, FILE * teste);

/***********************************************************************
*
*  $FC Função: PCA  &Destruir Vetor de Pecas
*
*  $ED Descrição da função
*		Libera um vetor de pecas
*
*  $AE Assertiva de Entrada
*       O endereço passado como parâmetro é um vetor de pecas devidamente alocado
*
*  $AS Assertiva de Saida
*		O vetor é devidamente liberado, junto com todas as pecas que se encontram dentro do mesmo
*
*  $EP Parâmetros
*       Possiveis - endereço do vetor que deve ser destruído
*
*  $FV Valor retornado
*		PCA_CondRetOK				      - Executou OK
*
***********************************************************************/

PCA_tpCondRet PCA_DestruirVetPecas (PCA_tpVetPeca Possiveis);

#undef PECA_EXT

/********** Fim do módulo de definição: PCA  Peça de tabuleiro **********/

#else
#endif
