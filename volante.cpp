#include "roteiro.hpp"

//bool Tecnico.getAtacantePosse()
//posXY Tecnico.getPosAtualAtacante()
//int Tecnico.getEstrategiaVolante() => enum {ataque, defesa}
//void Tecnico.permutaRoteiroAtkVol(); => permuta os roteiros e reseta as variaveis dependentes dos roteiros

void Roteiro::volante(Robo& r, posXY& b) {



    // O atacante possui a posse da bola
    if (Tecnico.getAtacantePosse()) {
        
        // O volante se encontra ate 10cm atras do atacante e
        // o volante esta mais proximo do meio de campo do que o atacante
        // "Caso A" -> se posicionara a frente do atacante para escolta-lo
        // (posVolante = posAtacante.X + TAM_ROBO)
        // (posVolante = posAtacante.y (+-) TAM_ROBO). O volante se posiciona em Y mais proximo de meio de campo        
        if ((std::abs(r.getPosicaoAtualRobo().x - Tecnico.getPosAtualAtacante().x) <= 10) 
            && (std::abs(TAM_Y_CAMPO/2 - r.getPosicaoAtualRobo().y) < std::abs(TAM_Y_CAMPO/2 - Tecnico.getPosAtualAtacante().y))) {
            
            if(r.getPosicaoAtualRobo().y <= TAM_Y_AREA_GOL / 2) {
                // Volante esta abaixo do meio de campo em Y                    
                r.setPosicaoObj(Tecnico.getPosAtualAtacante().x + TAM_ROBO, Tecnico.getPosAtualAtacante().Y + TAM_ROBO);                                                                                                                                                                    
            }
            
            else{
                // Volante esta acima do meio de campo em Y
                r.setPosicaoObj(Tecnico.getPosAtualAtacante().x + TAM_ROBO, Tecnico.getPosAtualAtacante().Y - TAM_ROBO);                                                
            }
        }

        // O volante se encontra ate 10 cm atras do atacante e esta mais perto da lateral respectiva
        // ou o volante se encontra mais de 10cm atras do atacante                
        // "Caso B" ou "Caso C", respectivamente
        else {
            // O volante segue o atacante 20cm atras           
            r.setPosicaoObj(Tecnico.getPosAtualAtacante().x - 20, Tecnico.getPosAtualAtacante().Y);                                                
        }
    }
    
    // O atacante nao tem a posse da bola
    else {
        // O volante esta em posse da bola
        if(r.isRoboEmPosseBola(b)){
            Tecnico.permutaRoteiroAtkVol();
        }

        // Nao temos posse da bola -> volante fica defensivo
        else{

            // A bola esta no campo adversario
            if (b.isInCampoAdv()){
                Comportamento::posicionaPosBola(r, b);
                                                
            }
    
            // Se a bola esta no nosso campo
            else {

                // A bola esta em nossa area
                if(b.isInAreaGolTime()){
                    // O robo fica meio robo a frente da linha da área, seguindo a bola
                    Comportamento::posicionaPosBolaEmY(r, b);
                    r.setPosicaoObjX(TAM_X_AREA_GOL + TAM_ROBO);
                }

        
                // A bola nao esta em nossa area
                // A seguir sao calculos para evitar que o volante entre na area                                                                        
                else {

                    // A bola esta em uma faixa acima da area
                    if (b.y > TAM_Y_CAMPO / 2 + TAM_Y_AREA_GOL / 2){
                        r.setPosicaoObjY(TAM_Y_CAMPO / 2 + TAM_Y_AREA_GOL / 2 + TAM_ROBO / 2);

                        // A bola esta a frente da area
                        if (b.x > TAM_X_AREA_GOL){
                            // O robo fica na "quina da area"                                                                                        
                            r.setPosicaoObjX(TAM_X_AREA_GOL + TAM_ROBO / 2);
                        }
                        // A bola esta encima da area
                        else {
                            // O robo fica na linha superior da area
                            r.setPosicaoObjX(b.x);
                        }
                    }
                    // A bola esta em uma faixa abaixo da area
                    else if (b.y < TAM_Y_CAMPO / 2 - TAM_Y_AREA_GOL / 2) {

                        
                        r.setPosicaoObjY(TAM_Y_CAMPO / 2 - TAM_Y_AREA_GOL / 2 - TAM_ROBO / 2);
                        
                        // A bola esta a frente da area
                        if (b.x > TAM_X_AREA_GOL){
                            // O robo fica na "quina da area"
                            r.setPosicaoObjX(TAM_X_AREA_GOL + TAM_ROBO / 2);
                        }
                        // A bola esta embaixo da area
                        else {
                            // O robo fica na linha inferior da area
                            r.setPosicaoObjX(b.x);
                        }
                    }

                    // A bola esta exatamente a frente da area
                    else {
                        // O robo fica na linha de frente da area
                        Comportamento::posicionaPosBolaEmY(r, b);
                        r.setPosicaoObjX(TAM_X_AREA_GOL + TAM_ROBO / 2);                                                         
                    }
                }
            }
        }
    }
}