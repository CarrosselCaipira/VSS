#ifndef PROPOSITO_GERAL_CAMERA_H
#define PROPOSITO_GERAL_CAMERA_H

#include "propositoGeralAtuadores.hpp"

/** @enum Cores
 *  @brief Enumeracao contendo as possiveis cores que podem aparecer em campo para facilitar a setagem e calibracao.
 */
enum Cores {
	AMARELO, /**< cor de identificao de TIME */
	AZUL, /**< cor de identificao de TIME */
	ALARANJADO, /**< cor de identificao da BOLA */
	ROSA, /**< cor de identificao de ROBO */
	ROXO, /**< cor de identificao de ROBO */
	VERDE, /**< cor de identificao de ROBO */

	/* Adicionar os novas cores antes de NUM_TOTAL_CORES */
	NUM_TOTAL_CORES, /**< Ultimo elemento serve de contagem para saber quantos elementos vieram anteriormente, logo o vetor de imagens binarizadas pode crescer mais facilmente */
	INDEFINIDA /**< representa que nao foi definida cor para a busca */
};

struct Retangulo {
	posXY posicao; /**< Posicao do retangulo na imagem. */
	double tamanhoArea; /**< Area ocupada do retangulo */

	/** @fn bool operator<(const Retangulo r)
	 *  @brief Sobrecarga do operador < para uso na funcao de ordenacao. A medida que eh levada em consideracao eh o tamanho da area do retangulo.
	 *  @param r Retangulo a ser comparado
	 *  @return True se a area do retangulo do lado esquerdo do operador for menor e False caso contrario.
	 */
	bool operator<(const Retangulo r);
};

/** @struct ParamHSV
 *  @brief Struct que armazena os valores de HSV min e max para cada cor e outras configuracoes
 */
struct ParamHSV {
	int H_MIN; /**< Hue minimo */
	int H_MAX; /**< Hue maximo */
	int S_MIN; /**< Saturacao minima */
	int S_MAX; /**< Saturacao maxima */
	int V_MIN; /**< Value(brilho) minimo */
	int V_MAX; /**< Value(brilho) maximo */
	int AreaMinima; /**< Area minima (inclusive) para uma regiao de destaque seja considerada o objeto em questao */
	int AreaMaxima; /**< Area maxima (inclusive) para uma regiao de destaque seja considerada o objeto em questao */
	int NumObjetosCor; /**< Numero de objetos que devem ser detectados da cor */
	int VezesErode; /**< Numero de vezes a imagem binarizada ira sofre erosao */
	int LarguraRetanguloErode; /**< Largura do retangulo de erosao */
	int AlturaRetanguloErode; /**< Altura do retangulo de erosao */
	int VezesDilatate; /**< "Numero de vezes a imagem binarizada ira sofre dilatacao */
	int LarguraRetanguloDilatate; /**< Largura do retangulo de dilatacao */
	int AlturaRetanguloDilatate; /**< Altura do retangulo de dilatacao */
};

#endif /* PROPOSITO_GERAL_CAMERA_H */
