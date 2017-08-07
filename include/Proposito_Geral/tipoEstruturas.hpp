/* Header com todas os tipos de dados (estruturas) utilizados pelo verysmall size. */

#ifndef TIPOS_ESTRUTURAS_H
#define TIPOS_ESTRUTURAS_H

/**
 * @brief      Posicionamento em Campo.
 */
struct posXY {
	float x, y;
};

/**
 * @brief      Vetor de movimentacao, com relacao as componentes do vetor
 */
struct vetorSentido {
	float x, y;
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
	float angulo; // angulacao atual do robo com relacao a horizontal (linha imaginaria que liga um gol ao outro)
	float velocidadeAngular; // velocidade de rotacao do robo
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

#endif /* TIPOS_ESTRUTURAS_H */
