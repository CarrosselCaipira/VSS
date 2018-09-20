#include "roteiro.hpp"

void Roteiro::atacante(Robo& r, posXY& b){

    //Se a bola estiver no quadrado inutil e o robo estiver perto
    if(b.isInQuadradosInuteis() && r.getPosicaoAtualRobo().isInRaio(b, TAM_ROBO/2)){
        //Se estiver em algum quadrado inutil superior, chute girando horario
        if(b.isInQuadradoInutilCantoSuperiorDireito() || b.isInQuadradoInutilCantoSuperiorEsquerdo()){
            r.atributos.set(CHUTE_GIRANDO_HORARIO);
        }
        //Se estiver em algum quadrado inutil inferior, chute girando anti horario
        else{
            r.atributos.set(CHUTE_GIRANDO_ANTI_HORARIO);
        }
    } 

    //Se o robo estiver com a bola
    else if(r.isRoboEmPosseBola(b)){
        //Se a bola estiver logo em frente ao robo
        if(b.x >= r.getPosicaoAtualRobo().x){
            Comportamento::posicionaCentroGolXYAdv(r);
        }
        //senao, move o robo para um pouco atras da bola
        else{
            Comportamento::posicionaAntesBola(r, b); 
        }
    }
    
    //O atacante nao esta com a bola
    //Se a bola estiver no campo adversario
    else if (b.isInCampoAdv()){
        //O atacante volta para o meio de campo e depois avanca para cima da bola
        if(r.getPosicaoAtualRobo().x > TAM_X_CAMPO/2){
            Comportamento::posicionaCentroCampoX(r);
        }
        else{
            Comportamento::posicionaPosBola(r, b);
        }
    }
    
    //se a bola esta no nosso campo
    else if (b.isInCampoTime()){
        //O atacante avanca na bola, porem nao entra na nossa area
        if(b.isInAreaGolTime()){
            Comportamento::permaneceNoEixoX(r);
        }
        else{
            Comportamento::posicionaPosBola(r, b);
        }
    }
}