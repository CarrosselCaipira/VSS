#!/usr/bin/env bash
g++ -c atacanteBasico.cpp -std=c++11
g++ -c camera.cpp -std=c++11
g++ -c comportamento.cpp -std=c++11
g++ -c CPH.cpp -std=c++11
g++ -c AEstrela.cpp -std=c++11
g++ -c gestorArq.cpp -std=c++11
g++ -c goleiroBasico.cpp -std=c++11
g++ -c propositoGeralAtuadores.cpp -std=c++11
g++ -c propositoGeralCamera.cpp -std=c++11
g++ -c radio.cpp -std=c++11
g++ -c robo.cpp -std=c++11
g++ -c volanteBasico.cpp -std=c++11
g++ -o MAIN MAIN.cpp atacanteBasico.o camera.o AEstrela.o comportamento.o CPH.o gestorArq.o goleiroBasico.o propositoGeralAtuadores.o propositoGeralCamera.o radio.o robo.o volanteBasico.o -std=c++11 `pkg-config --cflags --libs opencv`



# g++ -c atacanteBasico.cpp -std=c++11
# g++ -c camera.cpp -std=c++11
# g++ -c comportamento.cpp -std=c++11
# g++ -c CPH.cpp -std=c++11
# g++ -c gestorArq.cpp -std=c++11
# g++ -c goleiroBasico.cpp -std=c++11
# g++ -c propositoGeralAtuadores.cpp -std=c++11
# g++ -c propositoGeralCamera.cpp -std=c++11
# g++ -c radio.cpp -std=c++11
# g++ -c robo.cpp -std=c++11
# g++ -c volanteBasico.cpp -std=c++11
# g++ -o mainUzai mainUzai.cpp volanteBasico.o robo.o propositoGeralAtuadores.o goleiroBasico.o comportamento.o atacanteBasico.o -std=c++11
