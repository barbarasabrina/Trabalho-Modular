#define CHECK 1
#define CHECKMATE 2


int main (void)
{
	int check;
	char* ArqPecasPossiveis = "PecasPossiveis.txt";
	LIS_tppLista listaPecasPossiveis;
	TAB_tpTabuleiro pTabuleiro;

	JGO_IniciarJogo (ArqPecasPossiveis, listaPecasPossiveis, pTabuleiro);

	do {
		JGO_MostrarTabuleiro (pTabuleiro);//mostrar na tela - Leo
		JGO_RealizarMovimento(listaPecasPossiveis, pTabuleiro);//Perguntar pro usuario qual o movimento e realizar o movimento - Sabrina
		JGO_VerificaCheck(pTabuleiro, &check );//Verificar se está em check ou check mate - Ruda

	}while (check != CHECKMATE);

	JGO_FinalizarJogo(listaPecasPossiveis, pTabuleiro);//destruir tabuleiro e mandar mensagem dizendo quem venceu

	return 0;
}
