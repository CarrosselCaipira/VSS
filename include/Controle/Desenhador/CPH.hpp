#include "tipoEstruturas.hpp"
#include "robo.hpp"

#define MAX_X 43
#define MAX_Y 33			// Tem que ser 35 e deslocar 1 em todas as coordenadas em Y
#define DIV_CAMPO 4   // O que exatamente isso representa?
#define PRECISAO_CONVERGENCIA 0.00001			// PRECISÃO DE CONVERGÊNCIA
#define KF 0.5 //Constante da força aplicada pelo campo potencial
#define K_ALFA 0.07

struct campoPot {
	float matPot[MAX_X][MAX_Y]; // Valores pertencentes ao intervalo [0,1]
	bool matBoolPot[MAX_X][MAX_Y]; // true = obstáculo ou meta, false = espaço livre
};

class CPH {
	Robo& robo;
	std::vector<posXY>& posOstaculos /**< Vector contendo as posicoes dos obtaculos em campo (outros robos do time, robos da equipe adversaria, etc.), eh interessante que se use as posicoes previstas desses objetos, mas nada impede que as posicoes atuais sejam usadas. */;
	campoPot campoPotencial;

	private:

		/**
		 *  @fn inicializaObstMeta()
     	 *  @brief Função que inicializa a matriz de campo potenciais com os valores homogêneos
		 */
		void inicializaObstMeta();

		/**
		 *  @fn calculaCampoSOR()
     	 *  @brief Calcula Campo Potencial Harmônico utilizando método de relaxação/relaxamento SOR
		 */
		void calculaCampoSOR();

	public:

		/**
		 * 	@fn CPH(Robo& r, std::vector<posXY>& obs)
		 *  @brief Construtor da classe CPH. Armazena as referencias do robo a ser trasada a rota e dos obstaculos em campo
		 *  @param Referencia para um robo.
		 *  @param Referencia para um vetor de posicoes dos obstaculos
		 */
		CPH(Robo& r, std::vector<posXY>& obs);

		/**
		 * 	@fn calculaVelRodas()
		 *  @brief Calcula o valor de velocidade de cada roda
		 */
		void calculaVelRodas();
}
