#!/usr/bin/env bash

# COMPILACAO UTILIZANDO O GCC
# g++ -c atacanteBasico.cpp -std=c++11 -stdlib=libstdc++
# g++ -c camera.cpp -std=c++11 -stdlib=libstdc++
# g++ -c comportamento.cpp -std=c++11 -stdlib=libstdc++
# g++ -c CPH.cpp -std=c++11 -stdlib=libstdc++
# g++ -c AEstrela.cpp -std=c++11 -stdlib=libstdc++
# g++ -c gestorArq.cpp -std=c++11 -stdlib=libstdc++
# g++ -c goleiroBasico.cpp -std=c++11 -stdlib=libstdc++
# g++ -c propositoGeralAtuadores.cpp -std=c++11 -stdlib=libstdc++
# g++ -c propositoGeralCamera.cpp -std=c++11 -stdlib=libstdc++
# g++ -c radio.cpp -std=c++11 -stdlib=libstdc++
# g++ -c robo.cpp -std=c++11 -stdlib=libstdc++
# g++ -c volanteBasico.cpp -std=c++11 -stdlib=libstdc++
# g++ -o MAIN MAIN.cpp atacanteBasico.o camera.o AEstrela.o comportamento.o CPH.o gestorArq.o goleiroBasico.o propositoGeralAtuadores.o propositoGeralCamera.o radio.o robo.o volanteBasico.o -std=c++11 `pkg-config --cflags --libs opencv`

# COMPILACAO UTILIZANDO O CLANG
clang++ -c atacanteBasico.cpp -std=c++11
clang++ -c camera.cpp -std=c++11
clang++ -c comportamento.cpp -std=c++11
clang++ -c CPH.cpp -std=c++11
clang++ -c AEstrela.cpp -std=c++11
clang++ -c gestorArq.cpp -std=c++11
clang++ -c goleiroBasico.cpp -std=c++11
clang++ -c propositoGeralAtuadores.cpp -std=c++11
clang++ -c propositoGeralCamera.cpp -std=c++11
clang++ -c radio.cpp -std=c++11
clang++ -c robo.cpp -std=c++11
clang++ -c volanteBasico.cpp -std=c++11
clang++ -o MAIN MAIN.cpp atacanteBasico.o camera.o AEstrela.o comportamento.o CPH.o gestorArq.o goleiroBasico.o propositoGeralAtuadores.o propositoGeralCamera.o radio.o robo.o volanteBasico.o -std=c++11 `pkg-config --cflags --libs opencv`




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
