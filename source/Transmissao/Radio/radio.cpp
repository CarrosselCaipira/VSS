#include "radio.hpp"

/* o trecho: vector_robos(v) serve para acoplar o vector com os robos a classe de transmissao */
Radio::Radio(const std::vector<Robo>& v) : vector_robos(v) {
	
	vector_robos = v;
	/* abrindo a porta serial para leitura e escrita */
	int USB = open(caminho_dispositivo, O_RDWR| O_NOCTTY | O_NDELAY);
	
	/* setando todos os campos de dispositivo_tty com 0 (vamos evitar surpresas...) */
	memset(&dispositivo_tty, 0, sizeof dispositivo_tty);

	/* Tratamento de Erros */
	/* Testado se foi possivel abrir a porta serial */
	if ( USB < 0 ) 
		std::cout << "Erro " << errno << " @open " << caminho_dispositivo << ": " << std::strerror (errno) << endl;

	/* Testando se a porta serial aberta esta apontando para um dispositivo TTY (nosso radio eh TTY) */
	if (isatty (USB) < 0)
		std::cout << "Erro " << errno << " @isatty: " << std::strerror(errno) << std::endl;

	/* Testando se a atual configuracao da porta serial pode ser lida */
	if ( tcgetattr( USB, &dispositivo_tty ) != 0 )
	   std::cout << "Erro " << errno << " @tcgetattr: " << std::strerror(errno) << std::endl;

	/* Setando a frequencia de input e output do radio em 115200 */
	if (cfsetspeed(&dispositivo_tty, (speed_t)B115200) < 0)
		std::cout << "Erro " << errno << " @cfsetospeed: " << std::strerror(errno) << std::endl;

	/* Setando outras configuracoes da porta */
	dispositivo_tty.c_iflag = IGNBRK | IGNPAR;
	dispositivo_tty.c_oflag = 0;
	dispositivo_tty.c_lflag = 0;
	dispositivo_tty.c_cflag = B115200 | CS8;

	dispositivo_tty.c_cc[VMIN] = 1; /* a leitura nao bloqueia o processo */
	dispositivo_tty.c_cc[VTIME] = 0; /* nao aguarda para fazer a leitura */

	/* descarta dos dados atualmente na porta */
	tcflush( USB, TCIFLUSH );
	/* Aplicando as configuracoes */
	if ( tcsetattr ( USB, TCSANOW, &dispositivo_tty ) < 0)
	   std::cout << "Error " << errno << " @tcsetattr" << std::strerror(errno) << std::endl;
}

Radio::~Radio() {
	close(dispositivo_tty);
}

void Radio::enviaDados() {
	unsigned char dados[vector_robos.size()];
}