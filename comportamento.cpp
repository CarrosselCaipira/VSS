#include "comportamento.hpp"

void Comportamento::posicionaGolX(Robo& r) {

	r.setPosicaoObj(TAM_X_GOL, r.getPosicaoAtualRobo().y);
}

void Comportamento::posicionaCentroGolXY(Robo& r) {

	r.setPosicaoObj(TAM_X_GOL, CENTRO_Y_GOL);
}

void Comportamento::posicionaCentroGolXYAdv(Robo& r) {

	r.setPosicaoObj(TAM_X_GOL + TAM_X_CAMPO, CENTRO_Y_GOL);
}

void Comportamento::tangenciaLinhaSuperiorAreaGol(Robo& r) {

	r.setPosicaoObj(r.getPosicaoAtualRobo().x, TAM_Y_CAMPO/2 + TAM_Y_AREA_GOL/2 + TAM_ROBO/2);
}

void Comportamento::tangenciaLinhaInferiorAreaGol(Robo& r) {

	r.setPosicaoObj(r.getPosicaoAtualRobo().x, TAM_Y_CAMPO/2 - TAM_Y_AREA_GOL/2 - TAM_ROBO/2);
}

void Comportamento::tangenciaLinhaFrenteAreaGol(Robo& r) {

	r.setPosicaoObj(TAM_X_GOL + TAM_X_AREA_GOL + TAM_ROBO/2, r.getPosicaoAtualRobo().y);
}


void Comportamento::posicionaTraveSuperior(Robo& r) {

	r.setPosicaoObj(TAM_X_GOL, TAM_Y_CAMPO/2 + TAM_Y_GOL/2);
}

void Comportamento::posicionaTraveInferior(Robo& r) {

	r.setPosicaoObj(TAM_X_GOL, TAM_Y_CAMPO/2 - TAM_Y_GOL/2);
}

void Comportamento::posiciona90Graus(Robo& r){

	r.setAnguloAtualRobo(90);
}

void Comportamento::posicionaPosBola(Robo& r, posXY& b){

   r.setPosicaoObj(b.x, b.y);
}

void Comportamento::posicionaPosBolaEmX(Robo& r, posXY& b){

   r.setPosicaoObj(b.x, r.getPosicaoAtualRobo().y);
}

void Comportamento::posicionaPosBolaEmY(Robo& r, posXY& b){

   r.setPosicaoObj(r.getPosicaoAtualRobo().x, b.y);
}

void Comportamento::posicionaFaixaSuperior(Robo& r){

	r.setPosicaoObj(r.getPosicaoAtualRobo().x, TAM_Y_CAMPO/2 + TAM_Y_GOL/2);
}

void Comportamento::posicionaFaixaInferior(Robo& r){

	r.setPosicaoObj(r.getPosicaoAtualRobo().x, TAM_Y_CAMPO/2 - TAM_Y_GOL/2);
}

void Comportamento::posicionaCentroCampoX(Robo& r){

	r.setPosicaoObj(TAM_X_CAMPO/2, r.getPosicaoAtualRobo().y);
}

void Comportamento::posicionaCentroCampoY (Robo& r) {

	r.setPosicaoObj(r.getPosicaoAtualRobo().x, TAM_Y_CAMPO/2);
}

void Comportamento::permaneceNoEixoX(Robo& r){

	r.setPosicaoObj(r.getPosicaoAtualRobo().x, r.getPosicaoObj().y);
}

void Comportamento::permaneceNoEixoY(Robo& r){

	r.setPosicaoObj(r.getPosicaoObj().x, r.getPosicaoAtualRobo().y);
}

void Comportamento::posicionaAbaixoBola(Robo& r,posXY& b){

	r.setPosicaoObj(b.x, b.y - TAM_ROBO/2);
}

void Comportamento::posicionaAcimaBola(Robo& r,posXY& b){

	r.setPosicaoObj(b.x, b.y + TAM_ROBO/2);
}

void Comportamento::posicionaAtrasMeioCampo(Robo& r){

	r.setPosicaoObj(TAM_X_CAMPO/2 - TAM_ROBO/2, r.getPosicaoAtualRobo().y);
}

void Comportamento::posicionaParedeInferior(Robo& r){

	r.setPosicaoObj(r.getPosicaoAtualRobo().x, TAM_ROBO/2);
}

void Comportamento::posicionaParedeSuperior(Robo& r){

   r.setPosicaoObj(r.getPosicaoAtualRobo().x, TAM_Y_CAMPO - TAM_ROBO/2);
}

void Comportamento::segueBolaEmXFrente(Robo& r, posXY& b){
	std::cout << b.x - TAM_ROBO << '\n';
   r.setPosicaoObj(b.x - TAM_ROBO, r.getPosicaoAtualRobo().y);
	//  std::cout << "erro aqui" << '\n';
}
