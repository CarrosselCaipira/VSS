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
#include "tecnico.hpp"

class Roteiro {
  /*

  ATENCAO: Caso seu roteiro utilize algum tecnico, eh recomendado o teste, nas primeiras linhas do roteiro, se tecnico == NULL, isto eh uma boa pratica e facilitara no debug futuro.

  Caso seu roteiro utilize funcoes especificas de um roteiro, eh necessario fazer o cast do Tecnico para uma das classes descendentes. Exemplo, caso o atacante utilize funcoes especificas do TecnicoOfensivo, eh necessario, logo no inicio, apos realizar o teste acima, fazer: TecnicoOfensivo* Tecnico =  (TecnicoOfensivo*) tecnico; e utilizar as funcoes normalmente.

  */

	public:
		 static void atacante(Robo& r, Tecnico* tecnico);
		 static void volante(Robo& r, Tecnico* tecnico);
		 static void goleiro(Robo& r, Tecnico* tecnico);
		//static void atacanteBasico(Robo& r, posXY& b);
		//static void volanteBasico(Robo& r, posXY& b);
		//static void goleiroBasico(Robo& r, posXY& b);

};

#endif /* ROTEIRO_H */
