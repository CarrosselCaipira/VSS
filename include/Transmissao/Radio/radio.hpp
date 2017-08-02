/* Texto usado como base para este codigo disponivel em: https://en.wikibooks.org/wiki/Serial_Programming/termios 
 * e em https://stackoverflow.com/questions/18108932/linux-c-serial-port-reading-writing
 * 
 * Algumas informacoes uteis: 
 * O_RDONLY: abrindo porta para apenas leitura.
 * O_NOCTTY: A porta nunca se torna o terminal de controle do processo.
 * O_NDELAY: utilizando comunicao nao bloqueante. 
 */

#ifndef RADIO_H
#define RADIO_H

#include <stdio.h> 
#include <stdlib.h>
#include <cstring>   // Para uso da rotina memset 
#include <unistd.h> // Definicoes de funcao padrao do UNIX
#include <fcntl.h> // Para o uso das constantes utilizadas em 'open(...)' ex.: O_RDWR, O_RDONLY, etc. Para mais informacoes, va para Docs/tcntl.pdf
#include <cerrno> // Para o uso da rotina de indicacao de erro strerror() e da constante errno  
#include <termios.h> // Definicoes de controle de terminal POSIX


/* No momento faremos apenas o envio de dados. Mas futuramente tambem implementaremos o recebimento. */
class Radio {
	/* referencia para o vector que contem os robos */
	const std::vector<Robo>& vector_robos;
	/* estrutura de configuracao da porta serial */
	struct termios dispositivo_tty;
	/* descritor da porta serial a ser lida */
	int USB;
	/* caminho para a porta a ser aberta para comunicao serial */
	const char* caminho_dispositivo = "/dev/ttyUSB0";

	public:
		/**
		 * @brief      Faz a configuracao da porta serial para efetuar a comunicao e a 'acoplagem' do vetor de robos.
		 */
		Radio(std::vector<Robo>& v);
		/**
		 * @brief      Fecha a porta serial e termina a comunicao.
		 */
		~Radio();

		/**
		 * @brief      Faz o envio dos valores de velocidade de estadoAtualRobo de cada robo em campo
		 */
		void enviaDados();
	
};

#endif /* RADIO_H */