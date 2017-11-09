#include "robo.hpp"
#include "comportamento.hpp"
#include "roteiro.hpp"
#include <unordered_set>
#include <queue>
#include <unordered_map> 
#include <vector>
#include <tuple>
#include <string>
#include <algorithm>

#define MAX_X 77
#define MAX_Y 67
#define NUM_VIZINHOS 8

using namespace std;

typedef tuple<int,int> Posicao;
typedef pair<Posicao, double> itemFilaPrioridade;
typedef unordered_map<Posicao, Posicao> Caminho;
typedef unordered_map<Posicao, double> 	Custo;

namespace std {
  template <>
  struct hash<tuple<int,int> > {
    inline size_t operator()(const tuple<int,int>& location) const {
      int x, y;
      tie (x, y) = location;
      return x * 1812433253 + y;
    }
  };
}

class GrafoEmGrade{

	private:

		// Estrutura de dados que guarda as posições dos vizinhos.
		vector<Posicao> vizinhos;

		// Variáveis que definem o tamanho da grade.
		int largura;
		int altura;

		// Estrutura de dados que atua como um conjunto, ou seja, não permite dados duplicados, utilizada para guardar posições com obstáculos.
		unordered_set<Posicao> obstaculos;

	public:

		/**
		 * 	@fn GrafoEmGrade(int larg, int alt).
		 *  @brief Construtor, apenas inicia a largura e altura da grade além de preparar o vector vizinhos para checagem.
		 *  @param Largura da grade em número de vértices.
		 *  @param Altura da grade em número de vértices.
		 */
		GrafoEmGrade(int larg, int alt);

		/**
		 * 	@fn emGrade(Posicao coordenada).
		 *  @brief Função para determinar se uma posição pertence à grade.
		 *  @param Coordenada que deseja-se checar.
		 */
		bool emGrade(Posicao coordenada);

		/**
		 * 	@fn isObstaculo(Posicao coordenada).
		 *  @brief Função que checa se uma posição é um obstáculo.
		 *  @param Coordenada que deseja-se checar.
		 */
		bool isObstaculo(Posicao coordenada);

  		// Função que retorna em um vector as coordenadas dos vizinhos de uma dada coordenada.
		vector<Posicao> retornaVizinhos(Posicao coordenada);

  		// Adiciona retangulos como obstáculos, serve para adicionar vários obstáculos de uma vez.
		void adicionaMultiplosObstaculos(Posicao coordenada, int larg, int alt);

		// Adiciona um único obstáculo.
		void adicionaUmObstaculo(Posicao obstaculo);

		// Calcula custo de um no a outro.
		int pesoNoNo (Posicao noInicial, Posicao noFinal);
};

class FilaPrioridades{

	private:

  		priority_queue<itemFilaPrioridade, vector<itemFilaPrioridade>,greater<itemFilaPrioridade>> fila;

  	public:
  		
  		bool isVazia();

  		void colocar(Posicao i, double p);

  		Posicao retirarPop();
};

class AEstrela {

	private:

		Robo& robo;
		std::vector<posXY>& posObstaculos;
		GrafoEmGrade *grafo = new GrafoEmGrade(MAX_X,MAX_Y);
  		Caminho tracado;
		Custo gasto;

		// Função que prepara o grafo e chama o algoritmo a*.
		GrafoEmGrade* preparaGrafo(GrafoEmGrade *grafo, vector<Posicao> obstaculos);

		double heuristica(Posicao a, Posicao b);

		void aEstrela (GrafoEmGrade *grafo, Posicao inicio, Posicao meta, Caminho& caminho, Custo& custo);

		vector<Posicao> reconstruirCaminho(Posicao inicio, Posicao fim, Caminho& caminho);

		//Temp
		vector<Posicao> posXYtoPosicao(vector<posXY> v);

  	public:
  		
  		AEstrela(Robo& r, std::vector<posXY>& obs);

  		/**
		 * 	@fn calculaVelRodas()
		 *  @brief Calcula o valor de velocidade de cada roda
		 */
		void calculaVelRodas();
};