#ifndef ROTEIRO_H
#define ROTEIRO_H

enum ROTEIROS {
	INDEFINIDO,
	ATACANTE,
	VOLANTE,
	GOLEIRO,
	ATACANTE_BASICO,
	VOLANTE_BASICO,
	GOLEIRO_BASICO
};

#include "robo.hpp"
#include "comportamento.hpp"
#include "propositoGeralAtuadores.hpp"

class Roteiro {
	public:
		// static void atacante(Robo& r);
		// static void volante(Robo& r);
		// static void goleiro(Robo& r);
		static void atacanteBasico(Robo& r, posXY& b);
		static void volanteBasico(Robo& r, posXY& b);
		static void goleiroBasico(Robo& r, posXY& b);

};

#endif /* ROTEIRO_H */
