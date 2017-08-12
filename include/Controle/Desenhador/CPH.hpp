#include "tipoEstruturas.hpp"
#include "robo.hpp"

#define MAX_X 43
#define MAX_Y 33			// Tem que ser 35 e deslocar 1 em todas as coordenadas em Y

struct campoPot {
	float matPot[MAX_X][MAX_Y]; // Valores pertencentes ao intervalo [0,1]
	bool matBoolPot[MAX_X][MAX_Y]; // true = obstáculo ou meta, false = espaço livre
};

class CPH {
	private:
		Robo &robo;
		campoPot campoPotencial;
		void inicializa_obst_meta();

	public:
		CPH(Robo& r);
}
