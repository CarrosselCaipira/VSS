#ifndef COMPORTAMENTO_H
#define COMPORTAMENTO_H

#include "robo.hpp"
#include "propositoGeralAtuadores.hpp"

class Comportamento {
 public:

	/**
	 * @fn Comportamento::posicionaGolX(Robo& r)
	 * @brief Define o obj do robo como sendo o x do gol.
	 * @param Referencia para um robo
	 * @Author Rodrigo Bueno Dos Reis Rodrigues de Siqueira
	 */
	static void posicionaGolX(Robo& r);

	/**
	 * @fn Comportamento::posicionaCentroGolXY(Robo& r)
 	 * @brief Define o obj do robo como sendo o centro do nosso gol.
 	 * @param Referencia para um robo
 	 * @Author Danilo Weber Nunes
	 */
 	static void posicionaCentroGolXY(Robo& r);

	/**
	 * @fn Comportamento::posicionaCentroGolXYAdv(Robo& r)
 	 * @brief Define o obj do robo como sendo o centro do gol adversario.
 	 * @param Referencia para um robo
 	 * @Author Rodrigo Bueno Dos Reis Rodrigues de Siqueira
	 */
 	static void posicionaCentroGolXYAdv(Robo& r);

 	/**
	 * @fn Comportamento::tangenciaLinhaSuperiorAreaGol(Robo& r)
 	 * @brief Define o obj do robo como manter x e y de modo que tangencie a linha superior da area do gol.
 	 * @param Referencia para um robo
 	 * @Author Rodrigo Bueno Dos Reis Rodrigues de Siqueira
	 */
 	static void tangenciaLinhaSuperiorAreaGol(Robo& r);

 	/**
	 * @fn Comportamento::tangenciaLinhaInferiorAreaGol(Robo& r)
 	 * @brief Define o obj do robo como manter x e y de modo que tangencie a linha inferior da area do gol.
 	 * @param Referencia para um robo
 	 * @Author Rodrigo Bueno Dos Reis Rodrigues de Siqueira
	 */
 	static void tangenciaLinhaInferiorAreaGol(Robo& r);

 	/**
	 * @fn Comportamento::tangenciaLinhaFrenteAreaGol(Robo& r)
 	 * @brief Define o obj do robo como manter y e x de modo que tangencie a linha da frente da area do gol.
 	 * @param Referencia para um robo
 	 * @Author Rodrigo Bueno Dos Reis Rodrigues de Siqueira
	 */
 	static void tangenciaLinhaFrenteAreaGol(Robo& r);

 	/**
 	 * @fn Comportamento::posicionaTraveSuperior(Robo& r)
 	 * @brief Define como objetivo do robo a trave superior do gol do nosso lado.
 	 * @param Referencia para um robo
 	 * @Author Rodrigo Bueno Dos Reis Rodrigues de Siqueira
 	 */
 	static void posicionaTraveSuperior(Robo& r);

 	/**
 	 * @fn Comportamento::posicionaTraveInferior(Robo& r)
 	 * @brief Define como objetivo do robo a trave inferior do gol do nosso lado.
 	 * @param Referencia para um robo
 	 * @Author Rodrigo Bueno Dos Reis Rodrigues de Siqueira
 	 */
 	static void posicionaTraveInferior(Robo& r);

 	/**
 	 * @fn Comportamento::posiciona90Graus(Robo& r)
 	 * @brief Define como objetivo do robo de lado (90 graus).
 	 * @param Referencia para um robo
 	 * @Author Rodrigo Bueno Dos Reis Rodrigues de Siqueira
 	 */
 	static void posiciona90Graus(Robo& r);

 	/**
 	 * @fn Comportamento::posicionaPosBola(Robo& r, Bola& b)
 	 * @brief Define como objetivo do robo a posicao da bola.
 	 * @param Referencia para um robo
 	 * @param Referencia para a bola
 	 * @Author Rodrigo Bueno Dos Reis Rodrigues de Siqueira
 	 */
 	static void posicionaPosBola(Robo& r, Bola& b);

 	/**
 	 * @fn Comportamento::posicionaPosBolaEmX(Robo& r, Bola& b)
 	 * @brief Define como objetivo do robo a posicao da bola em x.
 	 * @param Referencia para um robo
 	 * @param Referencia para a bola
 	 * @Author Rodrigo Bueno Dos Reis Rodrigues de Siqueira
 	 */
 	static void posicionaPosBolaEmX(Robo& r, Bola& b);

 	/**
 	 * @fn Comportamento::posicionaPosBolaEmY(Robo& r, Bola& b)
 	 * @brief Define como objetivo do robo a posicao da bola em y.
 	 * @param Referencia para um robo
 	 * @param Referencia para a bola
 	 * @Author Rodrigo Bueno Dos Reis Rodrigues de Siqueira
 	 */
 	static void posicionaPosBolaEmY(Robo& r, Bola& b);

 	/**
 	 * @fn Comportamento::posicionaFaixaSuperior(Robo& r)
 	 * @brief Define como objetivo do robo a faixa superior do campo.
 	 * @param Referencia para um robo
 	 * @Author Rodrigo Bueno Dos Reis Rodrigues de Siqueira
 	 */
 	static void posicionaFaixaSuperior(Robo& r);

 	/**
 	 * @fn Comportamento::posicionaFaixaInferior(Robo& r)
 	 * @brief Define como objetivo do robo a faixa superior do campo.
 	 * @param Referencia para um robo
 	 * @Author Rodrigo Bueno Dos Reis Rodrigues de Siqueira
 	 */
 	static void posicionaFaixaInferior(Robo& r);

 	/**
 	 * @fn Comportamento::posicionaCentroCampoX(Robo& r)
 	 * @brief Define como objetivo do robo o centro do campo em X.
 	 * @param Referencia para um robo
 	 * @Author Rodrigo Bueno Dos Reis Rodrigues de Siqueira
 	 */
 	static void posicionaCentroCampoX(Robo& r);

 	/**
 	 * @fn Comportamento::posicionaCentroCampoY(Robo& r)
 	 * @brief Define como objetivo do robo o centro do campo em Y.
 	 * @param Referencia para um robo
 	 * @Author Rodrigo Bueno Dos Reis Rodrigues de Siqueira
 	 */
 	static void posicionaCentroCampoY(Robo& r);

 	/**
 	 * @fn Comportamento::permaneceNoEixoX(Robo& r)
 	 * @brief Define como objetivo do robo o mesmo objetivo anterior mas impedindo que ele se movimente no eixo X.
 	 * @param Referencia para um robo
 	 * @Author Rodrigo Bueno Dos Reis Rodrigues de Siqueira
 	 */
 	static void permaneceNoEixoX(Robo& r);

 	/**
 	 * @fn Comportamento::permaneceNoEixoY(Robo& r)
 	 * @brief Define como objetivo do robo o mesmo objetivo anterior mas impedindo que ele se movimente no eixo Y.
 	 * @param Referencia para um robo
 	 * @Author Rodrigo Bueno Dos Reis Rodrigues de Siqueira
 	 */
 	static void permaneceNoEixoY(Robo& r);

 	/**
 	 * @fn Comportamento::posicionaAbaixoBola(Robo& r,Bola& b)
 	 * @brief Define como objetivo do robo a posicao logo abaixo da bola (robo colado com a bola).
 	 * @param Referencia para um robo
 	 * @param Referencia para a bola
 	 * @Author Rodrigo Bueno Dos Reis Rodrigues de Siqueira
 	 */
 	static void posicionaAbaixoBola(Robo& r,Bola& b);

 	/**
 	 * @fn Comportamento::posicionaAcimaBola(Robo& r,Bola& b)
 	 * @brief Define como objetivo do robo a posicao logo acima da bola (robo colado com a bola).
 	 * @param Referencia para um robo
 	 * @param Referencia para a bola
 	 * @Author Rodrigo Bueno Dos Reis Rodrigues de Siqueira
 	 */
 	static void posicionaAcimaBola(Robo& r,Bola& b);

 	/**
 	 * @fn Comportamento::posicionaAtrasMeioCampoRobo& r)
 	 * @brief Define como objetivo do robo o meio de campo, mas sem tocar na linha de meio de campo, ficando atras da linha.
 	 * @param Referencia para um robo
 	 * @Author Rodrigo Bueno Dos Reis Rodrigues de Siqueira
 	 */
 	static void posicionaAtrasMeioCampo(Robo& r);

 	/**
 	 * @fn Comportamento::posicionaParedeInferior(Robo& r)
 	 * @brief Define como objetivo do robo, em y, a parede inferior do campo.
 	 * @param Referencia para um robo
 	 * @Author Rodrigo Bueno Dos Reis Rodrigues de Siqueira
 	 */
 	static void posicionaParedeInferior(Robo& r);

 	/**
 	 * @fn Comportamento::posicionaParedeSuperior(Robo& r)
 	 * @brief Define como objetivo do robo, em y, a parede superior do campo.
 	 * @param Referencia para um robo
 	 * @Author Rodrigo Bueno Dos Reis Rodrigues de Siqueira
 	 */
 	static void posicionaParedeSuperior(Robo& r);

 	/**
 	 * @fn Comportamento::segueBolaEmXFrente(Robo& r, Bola& b)
 	 * @brief Segue a bola em X mantendo uma distância de meio robô à frente.
 	 * @param Referencia para um robo
 	 * @param Referencia para a bola
 	 * @Author Luis Fernando Uzai
 	 */
 	static void segueBolaEmXFrente(Robo& r, Bola& b);

 };

 #endif /* COMPORTAMENTO_H */
