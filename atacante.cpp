#include "roteiro.hpp"
#include "tecnicoOfensivo.hpp"

//bool Tecnico.getEstrategiaAtacanteRetornou()
//bool Tecnico.setEstrategiaAtacanteRetornou() => muda uma variavel bool no tecnico
void Roteiro::atacante(Robo& r, Tecnico* tecnico) {

    if(tecnico == NULL) {
        std::cerr << "ERRO: @Roteiro::atacante. Ponteiro para tecnico nao definido. Saindo..." << '\n';
        exit(1);
    }

    TecnicoOfensivo* Tecnico = (TecnicoOfensivo*) tecnico; /* convertendo um tecnico generico em um TecnicoOfensivo. */
    posXY b = Tecnico->getPosAtualBola();

    // Se o atacante ja estiver realizando o chute girando no sentido horario
    if(r.atributos.test(CHUTE_GIRANDO_HORARIO)) {
	r.atributos.reset(CHUTE_GIRANDO_HORARIO);
	}

	// Se o atacante ja estiver realizando o chute girando no sentido anti horario
	else if(r.atributos.test(CHUTE_GIRANDO_ANTI_HORARIO)) {
		r.atributos.reset(CHUTE_GIRANDO_ANTI_HORARIO);
	}

    // Se a bola estiver no quadrado inutil e o robo estiver perto
    if(b.isInQuadradosInuteis() && r.getPosicaoAtualRobo().isInRaio(b, TAM_ROBO/2)){
        // Se estiver em algum quadrado inutil superior, chute girando horario
        if(b.isInQuadradoInutilCantoSuperiorDireito() || b.isInQuadradoInutilCantoSuperiorEsquerdo()){
            r.atributos.set(CHUTE_GIRANDO_HORARIO);
        }
        // Se estiver em algum quadrado inutil inferior, chute girando anti horario
        else{
            r.atributos.set(CHUTE_GIRANDO_ANTI_HORARIO);
        }
    }

    // Se o robo estiver com a bola
    else if(r.isRoboEmPosseBola(b)){
        // Seta o bitset para a posse da bola
        r.atributos.set(EM_POSSE_BOLA);

        // Se a bola estiver logo em frente ao robo
        if(b.x >= r.getPosicaoAtualRobo().x){
            Comportamento::posicionaCentroGolXYAdv(r);
        }
        // Senao, move o robo para um pouco atras da bola
        else{
            Comportamento::posicionaAntesBola(r, (b));
        }

        // Reseta a variavel "retornou"
        Tecnico->setEstrategiaAtacanteRetornou(false);
    }

    // O atacante nao esta com a bola
    // Se a bola estiver no campo adversario
    else if (b.isInCampoAdv()){
        // Reseta o bitset para a posse da bola
        r.atributos.reset(EM_POSSE_BOLA);

        // O atacante volta para o meio de campo e depois avanca para cima da bola
        if(r.getPosicaoAtualRobo().isInCampoAdv() && !Tecnico->getEstrategiaAtacanteRetornou()){
            Comportamento::posicionaCentroCampoX(r);
        }

        // O atacante passa a seguir a bola para tentar toma-la de volta
        else{
            Comportamento::posicionaPosBola(r, b);

            // A variavel "retornou" se torna verdadeira
            // Isto pois o atacante retornou ao meio de campo depois de perder a bola (ou nao tinha ela desde o inicio)
            // E passa a seguir a bola para recupera-la
            Tecnico->setEstrategiaAtacanteRetornou(true);
        }
    }

    // Se a bola esta no nosso campo
    else if (b.isInCampoTime()){
        // Reseta o bitset para a posse da bola
        r.atributos.reset(EM_POSSE_BOLA);

        // O atacante avanca na bola, porem nao entra na nossa area
        if(b.isInAreaGolTime()){
            Comportamento::permaneceNoEixoX(r);
        }
        else{
            Comportamento::posicionaPosBola(r, b);            
        }
    }
}
