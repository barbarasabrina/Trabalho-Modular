#include "jogo.h"
#define CHECK 1
#define CHECKMATE 2



JGO_tpCondRet JGO_IniciarJogo (char* filename, LIS_tppLista listaPecasPossiveis, TAB_tpTabuleiro pTabuleiro){

	char resp;
	LIS_tppLista listaPecasPossiveis;
	TAB_tpTabuleiro pTabuleiro;

	pTabuleiro = TAB_AlocarTabuleiro(8, 'H');
	TAB_CriarTabuleiro (pTabuleiro);

	PCA_InicializarPecas(filename, &listaPecasPossiveis);
	printf("Padrão? S:N");
	scanf("%d", resp);
	if (resp == 'S')
		montarTabPadrao();
	else
		montarTabMod();

}

int main (void){
	int check;
	char* ArqPecasPossiveis = "PecasPossiveis.txt";
	LIS_tppLista listaPecasPossiveis;
	TAB_tpTabuleiro pTabuleiro;

	JGO_IniciarJogo (ArqPecasPossiveis, listaPecasPossiveis, pTabuleiro);

	do {
		JGO_MostrarTabuleiro (pTabuleiro);
		JGO_RealizarMovimento(listaPecasPossiveis, pTabuleiro);
		JGO_VerificaCheck(pTabuleiro, &check );

	}while (check != CHECKMATE);

	JGO_FinalizarJogo(listaPecasPossiveis, pTabuleiro);

	return 0;
}
