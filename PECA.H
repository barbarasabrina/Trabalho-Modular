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

/* Tipo referência para uma peça */

typedef struct PCA_Peca * PCA_tpPeca;


#undef PECA_EXT

/********** Fim do módulo de definição: PCA  Peça de tabuleiro **********/

#else
#endif