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
#include <vector>
#include <iostream>
#include "robo.hpp"


/** @class Radio radio.h "radio.hpp"
 *  @brief Classe para a realizacao do envio dos dados para o arduino com o radio que manda as instrucoes para os robos.
 *
 *  A classe faz a configuracao da porta serial, em seguida faz a leitura dos valores de velocidade atual das rodas de todos
 *  os robos do time em campo, desloca os valores de velocidade 4 bits para a esquerda para que possam ser interpretados
 *  corretamente pelos robos e grava esses dados porta serial onde esta o arduino com o radio para que ele faca o envio dessas
 *  informacoes aos robos.
 *  @todo Futuramente tambem implementaremos o recebimento.
 */
class Radio {
	std::vector<Robo>& vector_robos; /**< referencia para o vector que contem os robos  */
	struct termios dispositivo_tty; /**< estrutura de configuracao da porta serial */
	int USB; /**< descritor da porta serial a ser lida */
	const char* caminho_dispositivo = "/dev/ttyUSB0"; /**< caminho para a porta a ser aberta para comunicao serial */

	public:
	 /** @fn Radio(std::vector<Robo>& v)
	  *  @brief Faz a configuracao da porta serial para efetuar a comunicao e a 'acoplagem' do vetor de robos.
	  *  @param std::vector<Robo>& v Vetor contendo os robos do time.
	  */
		Radio(std::vector<Robo>& v);

	 /** @fn ~Radio()
	  *  @brief Fecha a porta serial e termina a comunicao.
	  */
		~Radio();

		/** @fn enviaDados()
		 *  @brief Faz o envio dos valores de velocidade de estadoAtualRobo de cada robo em campo
		 */
		void enviaDados();

};

#endif /* RADIO_H */
