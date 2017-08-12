#include "radio.hpp"

/* o trecho: vector_robos(v) serve para acoplar o vector com os robos a classe de transmissao */
Radio::Radio(std::vector<Robo>& v) : vector_robos(v) {

	/* abrindo a porta serial para leitura e escrita */
	USB = open(caminho_dispositivo, O_RDWR| O_NOCTTY | O_NDELAY);

	/* setando todos os campos de dispositivo_tty com 0 (vamos evitar surpresas...) */
	memset(&dispositivo_tty, 0, sizeof dispositivo_tty);

	/* Tratamento de Erros */
	/* Testado se foi possivel abrir a porta serial */
	if (USB < 0)
		std::cout << "Erro " << errno << " @Radio->open " << caminho_dispositivo << ": " << std::strerror (errno) << std::endl;

	/* Testando se a porta serial aberta esta apontando para um dispositivo TTY (nosso radio eh TTY) */
	if (isatty (USB) < 0)
		std::cout << "Erro " << errno << " @Radio->isatty: " << std::strerror(errno) << std::endl;

	/* Testando se a atual configuracao da porta serial pode ser lida */
	if (tcgetattr(USB, &dispositivo_tty) != 0 )
	   std::cout << "Erro " << errno << " @Radio->tcgetattr: " << std::strerror(errno) << std::endl;

	/* Setando a frequencia de input e output do radio em 115200 */
	if (cfsetspeed(&dispositivo_tty, (speed_t)B115200) < 0)
		std::cout << "Erro " << errno << " @Radio->cfsetospeed: " << std::strerror(errno) << std::endl;

	/* Setando outras configuracoes da porta (no momento: aceite que funciona)*/
	dispositivo_tty.c_iflag = IGNBRK | IGNPAR;
	dispositivo_tty.c_oflag = 0;
	dispositivo_tty.c_lflag = 0;
	dispositivo_tty.c_cflag = B115200 | CS8;

	/* Setagem para realizar a 'leitura contada', a leitura da porta serial eh efetuada apenas se o buffer de recebimento possui VMIN bytes(chars) */
	dispositivo_tty.c_cc[VMIN] = 1; /* aguarda que seja recebido 1 byte (char) para efetuar a leitura. Senao tiverem chego, bloqueia o processo. */
	dispositivo_tty.c_cc[VTIME] = 0; /* nao ha timing para fazer a leitura da porta */

	/* descarta dos dados atualmente na porta ('lixo' de memoria)*/
	tcflush( USB, TCIOFLUSH);
	/* Aplicando as configuracoes.
	 * TCSANOW = aplica instantaneamente as configuracoes.
	 */
	if ( tcsetattr(USB, TCSANOW, &dispositivo_tty ) < 0)
	   std::cout << "Error " << errno << " @Radio->tcsetattr " << std::strerror(errno) << std::endl;
}

Radio::~Radio() {
	close(USB);
}

/* enviando um byte para cada roda. Futuramente armazenaremos em um byte os valores de velocidade de ambas as rodas >> necessario corrigir robo.hpp robo.cpp tipoEstruturas.hpp e os codigos do arduino. */
void Radio::enviaDados() {
	/* aparentemente desnecessario, descomentar em caso de problemas */
	/* descarta dos dados atualmente na porta ('lixo' de memoria) */
	// tcflush( USB, TCIOFLUSH);

	/* o primeiro eh o valor de velocidade do motor da roda esquerda do primeiro robo */
	/* o segundo eh o valor de velocidade do motor da roda direita do primeiro robo */
	/* o terceiro eh o valor de velocidade do motor da roda esquerda do segundo robo */
	/* o quarto eh o valor de velocidade do motor da roda direita do segundo robo */
	/* e assim por diante para todos os robos do time em campo */
	/* os ultimos dois elementos do vetor(bytes) correspondem ao caractere zero */
	unsigned char dados[2 * vector_robos.size() + 2];

	/* envia 0x80 como primeiro sinal (sera interpretado pelos robos) */
	unsigned char caractere_inicial = 0x80;
	write(USB, &caractere_inicial, 1);

	/* preenchendo o vetor de dados das rodas com os valores de velocidade dos robos */
	for(int i = 0; i < vector_robos.size(); i++) {
		/* deslocamos para esquerda os ultimos 4 bits para que eles sejam os primeiros do byte. Para os robos que receberao, apenas os primeiros 4 bytes sao importantes para os robos. */
		dados[2 * i] = vector_robos[i].getVelocidadeAtualRobo().rodaEsq << 4;
		dados[2 * i + 1] = vector_robos[i].getVelocidadeAtualRobo().rodaDir << 4;
	}
	dados[2 * vector_robos.size()] = '0';
	dados[2 * vector_robos.size() + 1] = '0';

	/* faz o envio das velocidades de cada roda para a porta serial */
	if(write(USB, dados, 8) < 0)
		std::cout << "Error " << errno << " @enviaDados->write " << std::strerror(errno) << std::endl;
}
