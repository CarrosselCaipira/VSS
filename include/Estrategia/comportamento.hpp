#ifndef COMPORTAMENTO_H
#define COMPORTAMENTO_H

#include "robo.hpp"
#include "posicionameto.hpp"

class Comportamento {
 public:

	 /** @fn Comportamento::posicionaCentroGolXY(Robo& r)
 	 *  @brief Define o obj do robo como sendo o centro do gol adversario.
 	 *  @param Referencia para um robo
 	 *  @Author Danilo Weber Nunes
 	 */
 	static void posicionaCentroGolXY(Robo& r);

 };

 #endif /* COMPORTAMENTO_H */
