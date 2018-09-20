#include "robo.hpp"
#include <iostream>

/*************************** CONSTRUTOR *************************/
Robo::Robo() {
	/* zerando todas as componentes do robo */
	std::memset(&estadoAtualRobo, 0, sizeof(estadoRobo));
	std::memset(&estadoPrevRobo, 0, sizeof(estadoRobo));
	std::memset(&estadoObjRobo, 0, sizeof(estadoRobo));

	/* o roteiro do robo eh inicializado como INDEFINIDO */
	tipoJogador = INDEFINIDO;

	/* definindo todos os atributos inicialmente como zero */
	atributos.reset();
}
/****************************************************************/

/***************************** GETTERS **************************/

/************************ POSICAO ATUAL ROBO ********************/
posXY Robo::getPosicaoAtualRobo () {
	return estadoAtualRobo.posicao;
}

vetorSentido Robo::getVetorSentidoAtualRobo () {
	return estadoAtualRobo.direcao;
}

float Robo::getAnguloAtualRobo () {
	return estadoAtualRobo.angulo;
}

velocidadeRobo Robo::getVelocidadeAtualRobo () {
	return estadoAtualRobo.velocidade;
}
/****************************************************************/

/********************* POSICAO PREVISTA ROBO ********************/
posXY Robo::getPosicaoPrevRobo () {
	return estadoPrevRobo.posicao;
}

vetorSentido Robo::getVetorSentidoPrevRobo () {
	return estadoPrevRobo.direcao;
}

float Robo::getAnguloPrevRobo () {
	return estadoPrevRobo.angulo;
}

velocidadeRobo Robo::getVelocidadePrevRobo () {
	return estadoPrevRobo.velocidade;
}
/****************************************************************/

/************************ OBJETIVO DO ROBO **********************/
velocidadeRobo Robo::getVelocidadeObj () {
	return estadoObjRobo.velocidade;
}

posXY Robo::getPosicaoObj () {
	return estadoObjRobo.posicao;
}

float Robo::getAnguloObj () {
	return estadoObjRobo.angulo;
}
/****************************************************************/

/*********************** FUNCAO ROTEIRO *************************/
ROTEIROS Robo::getRoteiro() {
	return tipoJogador;
}
/****************************************************************/

/*********************** CALCULO DISTANCIAS *************************/
posXY Robo::getDistObjRobo() {
	posXY dist;

	dist.x = estadoObjRobo.posicao.x - estadoAtualRobo.posicao.x;
	dist.y = estadoObjRobo.posicao.y - estadoAtualRobo.posicao.y;

	return dist;
}

void Robo::getDistObjRobo(posXY& dist) {
	dist.x = estadoObjRobo.posicao.x - estadoAtualRobo.posicao.x;
	dist.y = estadoObjRobo.posicao.y - estadoAtualRobo.posicao.y;
}

double Robo::getDistEuclianaObjRobo() {
	return this->estadoAtualRobo.posicao.getDistEucliana(this->estadoObjRobo.posicao);
}

bool Robo::isRoboComBola(const posXY posicao, int raio) { //Considerar alteração da forma como identificamos se o robo está com a bola
	return (this->estadoAtualRobo.posicao.isInRaio(posicao, raio) && (posicao.x >= (this->estadoAtualRobo.posicao.x + TAM_ROBO / 2)));
}

bool Robo::isBolaNoIntervaloYRobo(const posXY posicao) {
	return (this->estadoAtualRobo.posicao.y <= (posicao.y - TAM_ROBO / 2) && this->estadoAtualRobo.posicao.y >= (posicao.y + TAM_ROBO / 2));
}

bool Robo::isRoboEmPosseBola(const posXY bola){
	vetorSentido sentido;
	vetorSentido robobola;

	sentido = estadoAtualRobo.direcao;
	robobola.x = bola.x - estadoAtualRobo.posicao.x;
	robobola.y = bola.y - estadoAtualRobo.posicao.y;

	//Formula de encontrar angulo entre dois vetores
	//Resultado deve ser menor do que PI/4 (0.785398163397448309616) para a posse ser considerada
	return ((std::acos((sentido.x * robobola.x + sentido.y * robobola.y)/(sqrt(pow(sentido.x, 2) + pow(sentido.y, 2)) * sqrt(pow(robobola.x, 2) + pow(robobola.y, 2)))) < 0.785398163397448309616) 
			&& (this->estadoAtualRobo.posicao.getDistEucliana(bola) <= TAM_ROBO));
}

/****************************************************************/

/***************************** SETTERS **************************/

/************************ POSICAO ATUAL ROBO ********************/
/* CAGADAS COM BOLA */
void Robo::setPosicaoAtualBola(const posXY posicao){
	this->bola = posicao;
}

posXY Robo::getPosicaoAtualBola() {
	return this->bola;
}


void Robo::setPosicaoAtualRobo (const posXY posicao) {
	if(posicao.x <= 0 || posicao.y <= 0 )
	std::cerr << "Erro " << "@Robo->setPosicaoAtualRobo " << "Nao eh possivel definir posicoes negativas ou iguais a zero" << std::endl;
	estadoAtualRobo.posicao = posicao;
}

void Robo::setPosicaoAtualRobo (const float x, const float y) {
	if(x <= 0 || y <= 0 )
	std::cerr << "Erro " << "@Robo->setPosicaoAtualRobo " << "Nao eh possivel definir posicoes negativas ou iguais a zero" << std::endl;
	estadoAtualRobo.posicao.x = x;
	estadoAtualRobo.posicao.y = y;
}

void Robo::setVetorSentidoAtualRobo(const vetorSentido vetor) {
	estadoAtualRobo.direcao = vetor;
}

void Robo::setVetorSentidoAtualRobo(const float vetorX, const float vetorY) {
	estadoAtualRobo.direcao.x = vetorX;
	estadoAtualRobo.direcao.y = vetorY;
}

void Robo::setAnguloAtualRobo (const float angulo) {
	estadoAtualRobo.angulo = angulo;
}

void Robo::setVelocidadeAtualRobo (const velocidadeRobo velocidade) {
	estadoAtualRobo.velocidade = velocidade;
}

void Robo::setVelocidadeAtualRobo (const unsigned char velRodaEsq, const unsigned char velRodaDir) {
	estadoAtualRobo.velocidade.rodaEsq = velRodaEsq;
	estadoAtualRobo.velocidade.rodaDir = velRodaDir;
}
/****************************************************************/

/********************* POSICAO PREVISTA ROBO ********************/
void Robo::setPosicaoPrevRobo (const posXY posicao) {
	if(posicao.x <= 0 || posicao.y <= 0 )
	std::cerr << "Erro " << "@Robo->setPosicaoPrevRobo " << "Nao eh possivel definir posicoes negativas ou iguais a zero" << std::endl;
	estadoPrevRobo.posicao = posicao;
}

void Robo::setPosicaoPrevRobo (const float x, const float y) {
	if(x <= 0 || y <= 0 )
	std::cerr << "Erro " << "@Robo->setPosicaoPrevRobo " << "Nao eh possivel definir posicoes negativas ou iguais a zero" << std::endl;
	estadoPrevRobo.posicao.x = x;
	estadoPrevRobo.posicao.y = y;
}

void Robo::setVetorSentidoPrevRobo(const vetorSentido vetor) {
	estadoPrevRobo.direcao.x = vetor.x;
	estadoPrevRobo.direcao.y = vetor.y;
}

void Robo::setVetorSentidoPrevRobo(const float x, const float y) {
	estadoPrevRobo.direcao.x = x;
	estadoPrevRobo.direcao.y = y;
}

void Robo::setAnguloPrevRobo (const float angulo) {
	estadoPrevRobo.angulo = angulo;
}

void Robo::setVelocidadePrevRobo (const velocidadeRobo velocidade) {
	estadoPrevRobo.velocidade = velocidade;
}

void Robo::setVelocidadePrevRobo (const unsigned char velRodaEsq, const unsigned char velRodaDir) {
	estadoPrevRobo.velocidade.rodaEsq = velRodaEsq;
	estadoPrevRobo.velocidade.rodaDir = velRodaDir;
}
/****************************************************************/

/************************ OBJETIVO DO ROBO **********************/
void Robo::setPosicaoObj (const posXY posicao) {
	if(posicao.x <= 0 || posicao.y <= 0 )
	std::cerr << "Erro " << "@Robo->setPosicaoObj " << "Nao eh possivel definir posicoes negativas ou iguais a zero" << std::endl;
	estadoObjRobo.posicao = posicao;
}

void Robo::setPosicaoObj (const float x, const float y) {
	if(x <= 0 || y <= 0 )
	std::cerr << "Erro " << "@Robo->setPosicaoObj " << "Nao eh possivel definir posicoes negativas ou iguais a zero" << std::endl;
	estadoObjRobo.posicao.x = x;
	estadoObjRobo.posicao.y = y;
}

void Robo::setPosicaoObjX(const float x) {
	if(x <= 0)
	std::cerr << "Erro " << "@Robo->setPosicaoObj " << "Nao eh possivel definir posicoes negativas ou iguais a zero" << std::endl;
	estadoObjRobo.posicao.x = x;
}

void Robo::setPosicaoObjY (const float y) {
	if(y <= 0)
	std::cerr << "Erro " << "@Robo->setPosicaoObj " << "Nao eh possivel definir posicoes negativas ou iguais a zero" << std::endl;
	estadoObjRobo.posicao.y = y;
}

void Robo::setAnguloObj (const float angulo) {
	estadoObjRobo.angulo = angulo;
}

void Robo::setVelocidadeObj (const velocidadeRobo vel){
	estadoObjRobo.velocidade = vel;
}

void Robo::setVelocidadeObj (const unsigned char velRodaEsq, const unsigned char velRodaDir) {
	estadoObjRobo.velocidade.rodaEsq = velRodaEsq;
	estadoObjRobo.velocidade.rodaDir = velRodaDir;
}
/****************************************************************/

/*********************** FUNCAO ROTEIRO *************************/
void Robo::setRoteiro(ROTEIROS r) {
	tipoJogador = r;
}
/****************************************************************/

/*********************** ESTADOS DO ROBO *************************/
void Robo::setEstadoAtualComoEstadoPrev(){
	std::memcpy(&(this->estadoAtualRobo), &(this->estadoPrevRobo), sizeof(estadoRobo));
}

void Robo::setEstadoAtualComoEstadoObj(){
	std::memcpy(&(this->estadoAtualRobo), &(this->estadoObjRobo), sizeof(estadoRobo));
}

void Robo::setEstadoPrevComoEstadoAtual(){
	std::memcpy(&(this->estadoPrevRobo), &(this->estadoAtualRobo), sizeof(estadoRobo));
}

void Robo::setEstadoPrevComoEstadoObj(){
	std::memcpy(&(this->estadoPrevRobo), &(this->estadoObjRobo), sizeof(estadoRobo));
}
/****************************************************************/

void Robo::run() {
	switch (tipoJogador) {
		 case ATACANTE:
		   Roteiro::atacante(*this, bola);
		   break;
		
		 case VOLANTE:
		   Roteiro::volante(*this, bola);
		   break;
		
		 case GOLEIRO:
		   Roteiro::goleiro(*this, bola);
		   break;

		//case ATACANTE_BASICO:
		//	std::cout << "@Robo: Roteiro do atacante rodando" << '\n';
		//	Roteiro::atacanteBasico(*this, bola);
		//break;
		//
		//case VOLANTE_BASICO:
		//	std::cout << "@Robo: Roteiro do volante rodando" << '\n';
		//	Roteiro::volanteBasico(*this, bola);
		//break;
		//
		//case GOLEIRO_BASICO:
		//	std::cout << "@Robo: Roteiro do goleiro rodando" << '\n';
		//	Roteiro::goleiroBasico(*this, bola);
		//break;
	}
}
