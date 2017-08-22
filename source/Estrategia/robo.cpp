#include "robo.hpp"

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
    double soma;
    int i;

		soma = pow(estadoObjRobo.posicao.x - estadoAtualRobo.posicao.x, 2);
    soma += pow(estadoObjRobo.posicao.y - estadoAtualRobo.posicao.y, 2);

    return sqrt(soma);
}
/****************************************************************/

/***************************** SETTERS **************************/

/************************ POSICAO ATUAL ROBO ********************/
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
void Robo::set_roteiro(ROTEIROS r) {
  tipoJogador = r;
}
/****************************************************************/

/*********************** ESTADOS DO ROBO *************************/
void Robo::setEstadoAtualComoEstadoPrev(){
	std::memcpy(this->estadoAtualRobo, this->estadoPrevRobo, sizeof(estadoRobo));
}

void Robo::setEstadoAtualComoEstadoObj(){
	std::memcpy(this->estadoAtualRobo, this->estadoObjRobo, sizeof(estadoRobo));
}

void Robo::setEstadoPrevComoEstadoAtual(){
	std::memcpy(this->estadoPrevRobo, this->estadoAtualRobo, sizeof(estadoRobo));
}

void Robo::setEstadoPrevComoEstadoObj(){
	std::memcpy(this->estadPrevRobo, this->estadoObjRobo, sizeof(estadoRobo));
}
/****************************************************************/

void Robo::run() {
  switch (tipoJogador) {
    case ATACANTE:
      Roteiro::atacante(*this);
      break;

    case VOLANTE:
      Roteiro::volante(*this);
      break;

    case GOLEIRO:
      Roteiro::goleiro(*this);
      break;
  }
}
