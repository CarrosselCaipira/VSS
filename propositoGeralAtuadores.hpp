/* Header com todas os tipos de dados (estruturas) utilizados pelo verysmall size. */

#ifndef PROPOSITO_GERAL_ATUADORES_H
#define PROPOSITO_GERAL_ATUADORES_H

#include <cmath>

#define TAM_X_GOL 10	// em cemtimetros
#define TAM_Y_GOL 40
#define TAM_X_CAMPO_SEM_GOL 150	// em cemtimetros
#define TAM_X_CAMPO 170
#define TAM_Y_CAMPO 130	// em cemtimetros
#define TAM_X_AREA_GOL 15
#define TAM_Y_AREA_GOL 70
#define CENTRO_X_GOL_ADV 160
#define CENTRO_Y_GOL 65
#define ESPACO_CHUTE_GIRANDO 6
#define TAM_QUADRADO_INUTIL 7
#define RAIO_ATAQUE 6


/**
 * @struct posXY
 * @brief      Posicionamento em Campo.
 */
struct posXY {
	double x, y;

	/* calcula o ponto medio entre dois pontos */
	posXY getPontoMedio(const posXY pos);

	/** @fn double getDistEucliana(const posXY pos)
	 *  @brief Calcula a distancia euclidiana de um ponto(objeto) a outro
	 *  @param pos Posicao do outro objeto que se deseja calcular a distancia
	 *  @return A distancia euclidiana entre os dois pontos
	 */
	double getDistEucliana(const posXY pos);

	/** @fn double getDistX(const posXY pos)
	 *  @brief Calcula a distancia com relacao a componete x do ponto(objeto). Operacao realizada: This->x - pos.x
	 *  @param pos Posicao do outro ponto(objeto) que se deseja calcular a distancia
	 *  @return A distancia, com relacao ao eixo X, entre os dois pontos. Se o valor retornadado for positivo, significa que o ponto(objeto) que evocou esta rotina esta a frente do ponto(objeto) passado por parametro.
	 */
	double getDistX(const posXY pos);

	/** @fn double getDistY(const posXY pos)
	 *  @brief Calcula a distancia com relacao a componete Y do ponto(objeto). Operacao realizada: This->y - pos.y
	 *  @param pos Posicao do outro ponto(objeto) que se deseja calcular a distancia
	 *  @return A distancia, com relacao ao eixo Y, entre os dois pontos. Se o valor retornadado for positivo, significa que o ponto(objeto) que evocou esta rotina esta acima do ponto(objeto) passado por parametro.
	 */
	double getDistY(const posXY pos);

	bool isInCampoTime();
	bool isInCampoAdv();
	bool isInCampoMetadeSuperior();
	bool isInCampoMetadeInferior();
	bool isInFaixaSuperior();
	bool isInFaixaInferior();
	bool isInFaixaCentral();
	bool isInFaixaXDaAreaGolTime();
	bool isInFaixaXDaAreaGolAdv();
	bool isInCampoSemAreaGolTime();
	bool isInCampoSemAreaGolAdv();
	bool isInAreaEscanteioSuperiorTime();
	bool isInAreaEscanteioInferiorTime();
	bool isInAreaEscanteioSuperiorAdv();
	bool isInAreaEscanteioInferiorAdv();
	bool isInFrenteAreaGolCentroTime();
	bool isInFrenteAreaGolCentroAdv();
	bool isInQuinaSuperiorAreaGolTime();
	bool isInQuinaInferiorAreaGolTime();
	bool isInQuinaSuperiorAreaGolAdv();
	bool isInQuinaInferiorAreaGolAdv();
	bool isInAreaGolTime();
	bool isInAreaGolAdv();
	bool isInFaixaSuperiorChuteGirando();
	bool isInFaixaInferiorChuteGirando();
	bool isInFaixaChuteGirandoTime();
	bool isInFaixaChuteGirandoAdv();

	//criar isInCampo - checar se o ponto está dentro do campo

	// Area definida pelo quadrado inútil no canto superior esquerdo.
	bool isInQuadradoInutilCantoSuperiorEsquerdo();
	// Area definida pelo quadrado inútil no canto inferior esquerdo.
	bool isInQuadradoInutilCantoInferiorEsquerdo();
	// Area definida pelo quadrado inútil no canto superior direito.
	bool isInQuadradoInutilCantoSuperiorDireito();
	// Area definida pelo quadrado inútil no canto inferior direito.
	bool isInQuadradoInutilCantoInferiorDireito();
	// Area definida por qualquer dos quadrados inuteis.
	bool isInQuadradosInuteis ();
	// Checa se a bola está no raio de ataque dado, baseando-se na posição do robô.
	bool isInRaio (posXY posicao, int raio);
	// Checa se a bola está na área de ataque do volante
	bool isInAreaAtaqueVolante ();


	/** @fn posXY& operator=(const int i)
	 *  @brief Operador de atribuicao sobrecarregado para que, quando um posXY eh igualado a um inteiro, tanto a componente x quando a y serao iguais ao valor inteiro. A funcao retorna um endereco de posXY apenas para propositos de atribuicao sequencial (exemplo posXY p, p1; p1 = p = -1;), para atribucoes simples se o retorno fosse void nao seria um problema
	 *  @param i inteiro a ser atribuido a posicao
	 *  @return Endereco de um posXY para atribuicao sequencial
	 */
	posXY& operator=(const int i);

	/* quando um numero multiplica um objeto posXY suas duas componentes sao multiplicas pelo valor*/
	posXY& operator*(const double i);

	// fazer sobrecarga soma e subtração de posXY
};

/**
 * @struct vetorSentido
 * @brief      Vetor de movimentacao, com relacao as componentes do vetor
 */
struct vetorSentido {
	double x, y;
};

/**
 * @brief      velocidade de cada roda dos robos (0 a 127 (primeiro bit indica o sentido da rotacao)).
 */
struct velocidadeRobo {
	unsigned char rodaEsq, rodaDir;
};

/**
 * @brief      Todas as informacoes sobre os robos.
 */
struct estadoRobo {
	float angulo; /** angulacao atual do robo com relacao a horizontal (linha imaginaria que liga um gol ao outro) */
	float velocidadeAngular; /** velocidade de rotacao do robo */
	velocidadeRobo velocidade;
	posXY posicao;
	vetorSentido direcao;
};

/**
 * @brief      Todas as informacoes sobre a bola
 */
struct estadoBola {
	float velocidade;
	posXY posicao;
	vetorSentido direcao;
};

#endif /* PROPOSITO_GERAL_ATUADORES_H */
