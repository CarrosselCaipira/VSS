#include "propositoGeralAtuadores.hpp"

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

bool posXY::isInCampoAdv(const posXY posicao) {
	return posicao.x >= (TAM_X_CAMPO/2);
}

bool posXY::isInCampoMetadeSuperior(const posXY posicao) {
	return posicao.y > (TAM_Y_CAMPO/2);
}

bool posXY::isInCampoMetadeInferior(const posXY posicao) {
	return posicao.y <= (TAM_Y_CAMPO/2);
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
  return (!posXY::isInCampoTime() && !posXY::isInFaixaXDaAreaGolAdv());
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

bool posXY::isInAreaAntesMetadeCampoTime() {
  return (posXY::isInCampoTime() && !posXY::isInFaixaXDaAreaGolTime() && posXY::isInFaixaCentral());
}

bool posXY::isInAreaAntesMetadeCampoAdv() {
  return (!posXY::isInCampoTime() && !posXY::isInFaixaXDaAreaGolAdv() && posXY::isInFaixaCentral());
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

bool posXY::isInFaixaSuperiorChuteGirando() {
  return (this->y > (TAM_Y_CAMPO - ESPACO_CHUTE_GIRANDO));
}

bool posXY::isInFaixaInferiorChuteGirando() {
  return (this->y < ESPACO_CHUTE_GIRANDO);
}

bool posXY::isInFaixaChuteGirandoTime() {
  return (!posXY::isInFaixaCentral() && this->x < (TAM_X_GOL + 6));
}

bool posXY::isInFaixaChuteGirandoAdv() {
  return (!posXY::isInFaixaCentral() && this->x < (TAM_X_CAMPO - TAM_X_GOL - 6));
}

bool posXY::isInQuadradoInutilCantoSuperiorEsquerdo() {
  return ((this->x > TAM_X_GOL && this->x < TAM_X_GOL + TAM_QUADRADO_INUTIL ) && ( this->y > TAM_Y_CAMPO - TAM_QUADRADO_INUTIL && posicao.y < TAM_Y_CAMPO));
}

bool posXY::isInQuadradoInutilCantoInferiorEsquerdo() {
  return ((this->x > TAM_X_GOL && this->x < TAM_X_GOL + TAM_QUADRADO_INUTIL ) && ( this->y > 0 && this->y < TAM_QUADRADO_INUTIL));
}

bool posXY::isInQuadradoInutilCantoSuperiorDireito() {
  return ((this->x > TAM_X_CAMPO - TAM_X_GOL - TAM_QUADRADO_INUTIL && this->x < TAM_X_CAMPO TAM_X_GOL) && ( this->y > TAM_Y_CAMPO - TAM_QUADRADO_INUTIL && this->y < TAM_Y_CAMPO));
}

bool posXY::isInQuadradoInutilCantoInferiorDireito() {
  return ((this->x > TAM_X_CAMPO - TAM_X_GOL - TAM_QUADRADO_INUTIL && this->x < TAM_X_CAMPO TAM_X_GOL) && ( this->y > 0 && this->y < TAM_QUADRADO_INUTIL));
}

bool posXY::isInQuadradosInuteis () {
	return (posXY::quadradoInutilCantoSuperiorDireito() || posXY::quadradoInutilCantoInferiorDireito() || posXY::quadradoInutilCantoSuperiorEsquerdo() || posXY::quadradoInutilCantoInferiorEsquerdo()
}

bool posXY::isInRaio (posXY posicao, int raio){
  return (posXY::getDistEucliana(posicao) <= raio);
}

posXY& posXY::operator=(const int i) {
	this->x = i;
	this->y = i;

	return *this;
}
