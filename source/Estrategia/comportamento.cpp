#include "comportamento.hpp"

void Comportamento::posicionaCentroGolXY(Robo& r) {

	r.setPosicaoObj(TAM_X_GOL, CENTRO_Y_GOL);
}

// define como objetivo do robo a trave superior do gol do nosso lado
// SET ERRADO
void posicionaTraveSupeior() {
	yObj = (TAM_Y_CAMPO - 40)/2 + TAM_Y_GOL;
	xObj = TAM_X_GOL;
}

// define como objetivo do robo a trave inferior do gol do nosso lado
// SET ERRADO
void posicionaTraveInferio() {
	yObj = (TAM_Y_CAMPO - 40)/2;
	xObj = TAM_X_GOL;
}

// define como objetivo do robo de lado (90 graus)
// SET ERRADO
void posiciona90Graus(){
	this->setAnguloAtualRobo(90);
}

// define como objetivo do robo a posicao prevista para a chegada da bola
// necessario utilizar o vetor sentido, calculando o ponto onde a bola ira atigir o gol(mesmo que muito distante), nao a prosicao prevista da bola
void posiciona_pos_bola(Bola bola){
   this->setPosicaoObj(bola.getPosicaoPrevistoBola());
}

// define como objetivo do robo a faixa superior do campo
// @see posicionamento.hpp
void posiciona_faixa_superior(){
	PosXY p;
	p.x = this->getPosicaoAtualRobo().x;
	p.y = TAM_Y_CAMPO - (TAM_Y_CAMPO - TAM_Y_DO_GOL) / 2 + TAM_ROBO * 2;
	this->setPosicaoObj(p);
}

// define como objetivo do robo a faixa superior do campo
// @see posicionamento.hpp
void posiciona_faixa_inferior(){
	PosXY p;
	p.x = this->getPosicaoAtualRobo().x;
	p.y = (TAM_Y_CAMPO - TAMANHO_DO_GOL)/2 - TAM_ROBO*2;
	this->setPosicaoObj(p);
}

// define como objetivo do robo o centro do campo em X
void posicionaCentroCampoX (){
	xObj = TAM_X_CAMPO/2;
}

// define como objetivo do robo o centro do campo em Y
void posicionaCentroCampoY () {
	yObj = TAM_Y_CAMPO/2;
}

// define como objetivo do robo o mesmo objetivo anterior mas impedindo que ele se movimente no eixo X
void comportamento::permanece_no_eixoX(Robo& r){
	posXY atual, objetivo;
	objetivo = getPosicaoObj();
	atual = getPosicaoAtualRobo();
	objetivo.x = atual.x;
	r.setPosicaoObj(objetivo);
}

// define como objetivo do robo o mesmo objetivo anterior mas impedindo que ele se movimente no eixo Y
void comportamento::permanece_no_eixoY(Robo& r){
	posXY atual, objetivo;
	objetivo = getPosicaoObj();
	atual = getPosicaoAtualRobo();
	objetivo.y = atual.y;
	r.setPosicaoObj(objetivo);
}

// define como objetivo do robo a posicao logo abaixo da bola (robo colado com a bola)
void comportamento::posiciona_abaixo_da_bola(Robo& r){
	posXY bola,obj;	//objetivo inicial e posicao da bola
	posXY p;		//objetivo final
	obj = getPosicaoObj();
	bola = getPosicaoAtualBola();
	p.x = obj.x;
	p.y = bola.y - TAM_ROBO/2;
	r.SetPosicaoObj(p);
}

// define como objetivo do robo a posicao logo acima da bola (robo colado com a bola)
void comportamento::posiciona_acima_da_bola(Robo& r){
	posXY bola,obj;	//objetivo inicial e posicao da bola
	posXY p;		//objetivo final
	obj = getPosicaoObj();
	bola = getPosicaoAtualBola();
	p.x = obj.x;
	p.y = bola.y + TAM_ROBO/2;
	r.SetPosicaoObj(p);
}

// define como objetivo do robo o meio de campo, mas sem tocar na linha de meio de campo, ficando atras da linha.
void comportamento::posiciona_atras_do_meio_campo(Robo& r){
	posXY p;
	p = getPosicaoObj();
	p.x = (TAM_X_CAMPO-TAM_ROBO)/2 // TAM_X_CAMPO/2 - TAM_ROBO/2
	r.setPosicaoObj(p);
}

// define como objetivo do robo a posicao prevista da bola
void comportamento::posiciona_espera_bola(Robo& r){
	posXY p;
	p = estadoPrevistoBola();
	r.setPosicaoObj(p);
}

// define como objetivo do robo
// REESCRITA
void comportamento::posiciona_abaixo_bola(Robo& r){
	posXY destino, bola;
	bola = getPosicaoAtualBola();
	destino.y = bola.y - TAM_ROBO;
	destino.x = getPosicaoAtualRobo().x;
	r.setPosicaoObj(destino);
}

// define como objetivo do robo
// REESCRITA
void comportamento::posiciona_acima_bola(Robo& r){
	posXY destino, bola;
	bola = getPosicaoAtualBola();
	destino.y = bola.y + TAM_ROBO;
	destino.x = getPosicaoAtualRobo().x;
	r.setPosicaoObj(destino);
}

// define como objetivo do robo, em y, a parede inferior do campo.
void comportamento::posiciona_borda_inferior(Robo& r){
   float y = TAM_ROBO / 2;
   float x = getPosicaoAtualRobo().x;
   r.setPosicaoObj(x, y);
}

// define como objetivo do robo, em y, a parede superior do campo.
void comportamento::posiciona_borda_superior(Robo& r){
   float y = TAM_Y_CAMPO - TAM_ROBO / 2;
   float x = getPosicaoAtualRobo().x;
   r.setPosicaoObj(x, y);
}

// define como objetivo do robo
void comportamento::posiciona_segue_bola(Robo& r){
   posXY p;
   p = getPosicaoAtualBola();

   r.setPosicaoObj(p);
}
