#include "propositoGeralAtuadores.hpp"
#include <iostream>
posXY posXY::getPontoMedio(const posXY pos) {
	posXY resu;

	resu.x = (this->x + pos.x) / 2;
	resu.y = (this->y + pos.y) / 2;

	return resu;
}

double posXY::getDistEucliana(const posXY pos) {
	double dist;

	dist = pow(this->x - pos.x, 2) + pow(this->y - pos.y, 2);

	return sqrt(dist);
}

double posXY::getDistX(const posXY pos) {
	return (this->x - pos.x);
}

double posXY::getDistY(const posXY pos) {
	return (this->y - pos.y);
}

bool posXY::isInCampoTime() {
  return this->x < (TAM_X_CAMPO/2);
}

bool posXY::isInCampoAdv() {
	return this->x > TAM_X_CAMPO/2;
}

bool posXY::isInCampoMetadeSuperior() {
	return this->y > (TAM_Y_CAMPO/2);
}

bool posXY::isInCampoMetadeInferior() {
	return this->y <= (TAM_Y_CAMPO/2);
}

bool posXY::isInFaixaSuperior() {
  return this->y > (TAM_Y_CAMPO/2 + TAM_Y_GOL/2);
}

bool posXY::isInFaixaInferior() {
  return this->y < (TAM_Y_CAMPO/2 - TAM_Y_GOL/2);
}

bool posXY::isInFaixaCentral() {
  return (!posXY::isInFaixaSuperior() && !posXY::isInFaixaInferior());
}

bool posXY::isInFaixaXDaAreaGolTime() {
  return this->x < (TAM_X_GOL + TAM_X_AREA_GOL);
}

bool posXY::isInFaixaXDaAreaGolAdv() {
  return this->x > (TAM_X_CAMPO - TAM_X_GOL - TAM_X_AREA_GOL);
}

bool posXY::isInCampoSemAreaGolTime() {
  return (posXY::isInCampoTime() && !posXY::isInFaixaXDaAreaGolTime());
}

bool posXY::isInCampoSemAreaGolAdv() {
  return (posXY::isInCampoAdv() && !posXY::isInFaixaXDaAreaGolAdv());
}

bool posXY::isInAreaEscanteioSuperiorTime() {
  return (posXY::isInFaixaSuperior() && posXY::isInFaixaXDaAreaGolTime());
}

bool posXY::isInAreaEscanteioInferiorTime() {
  return (posXY::isInFaixaInferior() && posXY::isInFaixaXDaAreaGolTime());
}

bool posXY::isInAreaEscanteioSuperiorAdv() {
  return (posXY::isInFaixaSuperior() && posXY::isInFaixaXDaAreaGolAdv());
}

bool posXY::isInAreaEscanteioInferiorAdv() {
  return (posXY::isInFaixaInferior() && posXY::isInFaixaXDaAreaGolAdv());
}

bool posXY::isInFrenteAreaGolCentroTime() {
  return (posXY::isInCampoTime() && !posXY::isInFaixaXDaAreaGolTime() && posXY::isInFaixaCentral());
}

bool posXY::isInFrenteAreaGolCentroAdv() {
  return (posXY::isInCampoAdv() && !posXY::isInFaixaXDaAreaGolAdv() && posXY::isInFaixaCentral());
}

bool posXY::isInQuinaSuperiorAreaGolTime() {
  return ((this->y < (TAM_Y_CAMPO/2 + TAM_Y_GOL/2 + 10)) && posXY::isInFaixaSuperior() && posXY::isInFaixaXDaAreaGolTime());
}

bool posXY::isInQuinaInferiorAreaGolTime() {
  return ((this->y > (TAM_Y_CAMPO/2 - TAM_Y_GOL/2 - 10)) && posXY::isInFaixaInferior() && posXY::isInFaixaXDaAreaGolTime());
}

bool posXY::isInQuinaSuperiorAreaGolAdv() {
  return ((this->y < (TAM_Y_CAMPO/2 + TAM_Y_GOL/2 + 10)) && posXY::isInFaixaSuperior() && posXY::isInFaixaXDaAreaGolAdv());
}

bool posXY::isInQuinaInferiorAreaGolAdv() {
  return ((this->y > (TAM_Y_CAMPO/2 - TAM_Y_GOL/2 - 10)) && posXY::isInFaixaInferior() && posXY::isInFaixaXDaAreaGolAdv());
}

bool posXY::isInAreaGolTime() {
  return ((posXY::isInQuinaSuperiorAreaGolTime() || posXY::isInFaixaCentral()  || posXY::isInQuinaInferiorAreaGolTime()) && posXY::isInFaixaXDaAreaGolTime());
}

bool posXY::isInAreaGolAdv() {
  return ((posXY::isInQuinaSuperiorAreaGolAdv() || posXY::isInFaixaCentral()  || posXY::isInQuinaInferiorAreaGolAdv()) && posXY::isInFaixaXDaAreaGolAdv());
}

bool posXY::isInFaixaSuperiorChuteGirando() { //Sujeito à alterações por implicar uma estratégia dentro de propositoGeralAtuadores
  return (this->y > (TAM_Y_CAMPO - ESPACO_CHUTE_GIRANDO));
}

/*Sugestão - Talvez deixar genérico para poder enviar algum valor mais adequado para a respectiva estratégia

bool posXY::isInFaixaSuperiorChuteGirando(int faixa = TAM_Y_CAMPO - ESPACO_CHUTE_GIRANDO) {
  return (this->y > faixa);
}
*/

bool posXY::isInFaixaInferiorChuteGirando() { //Sujeito à alterações por implicar uma estratégia dentro de propositoGeralAtuadores
  return (this->y < ESPACO_CHUTE_GIRANDO);
}

/*Sugestão - Talvez deixar genérico para poder enviar algum valor mais adequado para a respectiva estratégia

bool posXY::isInFaixaInferiorChuteGirando(int faixa = ESPACO_CHUTE_GIRANDO) {
  return (this->y < faixa);
}
*/

bool posXY::isInFaixaChuteGirandoTime() {
  return (!posXY::isInFaixaCentral() && this->x < (TAM_X_GOL + 6));
}

bool posXY::isInFaixaChuteGirandoAdv() {
  return (!posXY::isInFaixaCentral() && this->x < (TAM_X_CAMPO - TAM_X_GOL - 6));
}

bool inInCampoX() {
  return (this->x < TAM_X_CAMPO && this->x > 0);
}

bool inInCampoY() {
  return (this->y < TAM_Y_CAMPO && this->y > 0);
}

bool inInCampo() {
  return (posXY::isInCampoX() && posXY::isInCampoY());
}

bool posXY::isInQuadradoInutilCantoSuperiorEsquerdo() {
  return ((this->x > TAM_X_GOL && this->x < TAM_X_GOL + TAM_QUADRADO_INUTIL ) && ( this->y > TAM_Y_CAMPO - TAM_QUADRADO_INUTIL && this->y < TAM_Y_CAMPO));
}

bool posXY::isInQuadradoInutilCantoInferiorEsquerdo() {
  return ((this->x > TAM_X_GOL && this->x < TAM_X_GOL + TAM_QUADRADO_INUTIL ) && ( this->y > 0 && this->y < TAM_QUADRADO_INUTIL));
}

bool posXY::isInQuadradoInutilCantoSuperiorDireito() {
  return ((this->x > TAM_X_CAMPO - TAM_X_GOL - TAM_QUADRADO_INUTIL && this->x < (TAM_X_CAMPO + TAM_X_GOL)) && ( this->y > TAM_Y_CAMPO - TAM_QUADRADO_INUTIL && this->y < TAM_Y_CAMPO));
}

bool posXY::isInQuadradoInutilCantoInferiorDireito() {
  return ((this->x > TAM_X_CAMPO - TAM_X_GOL - TAM_QUADRADO_INUTIL && this->x < (TAM_X_CAMPO + TAM_X_GOL)) && ( this->y > 0 && this->y < TAM_QUADRADO_INUTIL));
}

bool posXY::isInQuadradosInuteis () {
	return (posXY::isInQuadradoInutilCantoSuperiorDireito() || posXY::isInQuadradoInutilCantoInferiorDireito() || posXY::isInQuadradoInutilCantoSuperiorEsquerdo() || posXY::isInQuadradoInutilCantoInferiorEsquerdo());
}

bool posXY::isInRaio (posXY posicao, int raio){
  return (posXY::getDistEucliana(posicao) <= raio);
}

bool posXY::isInAreaAtaqueVolante (){ //Sujeito à alterações por implicar uma estratégia dentro de propositoGeralAtuadores
  return (this->x < TAM_X_CAMPO*0.6);
}

posXY& posXY::operator=(const int i) {
	this->x = i;
	this->y = i;

	return *this;
}

posXY& posXY::operator*(const double i) {
	this->x *= i;
	this->y *= i;

	return *this;
}

posXY& posXY::operator+(const posXY& p) {
  this->x += p.x;
	this->y += p.y;

	return *this;
}

posXY& posXY::operator-(const posXY& p) {
  this->x -= p.x;
	this->y -= p.y;

	return *this;
}
