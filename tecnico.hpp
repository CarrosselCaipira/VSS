#ifndef TECNICO_H
#define TECNICO_H

#include <vector>
#include "robo.hpp"
#include "bola.hpp"
#include "propositoGeralAtuadores.hpp"

/* Nesta abstracao, o tecnico define os roteiros dos jogadores em campo e os auxilia informando, por exemplo, a localizacao dos robos adversarios. O tecnico BASE na verdade atua orquestrando a passagem de informacoes e assim deve permanecer sendo, possuindo apenas metodos genericos para auxiliar os jogadores. A estrategia em si deve ser implementada pelos descendentes desta classe, como realizando o posicionamento dos jogadores, por exemplo, por este motivo esta eh uma classe abstrata (o metodo run() (puramente virtual pelo = 0) (e demais metodos virtuais) deve ser obrigatoriamente implementado em seus descendentes) */

/* Lembre-se tambem que ao criar classes herdeiras, eh necessario chamar explicitamente o construtor desta classe pela lista de inicializacao, assim como demostrado no tecnico exemplo 'TecnicoOfencivo'. */

/* Para  a criacao de metodos e estruturas nao-publicos cria-los dentro do 'escopo' "protected" visto que provavelmente deverao ser herdadas pela classe herdeira. */
class Tecnico {
  protected:
    std::vector<Robo>& robosTime; /* referencia para o vector que contem os robos do nosso time. */
    std::vector<Robo>& robosAdv; /* referencia para o vector que contem os robos do time aversario . */
    Bola& bola; /* referencia para a bola. */

    /* para simplificacoes que possam vir a ser necessarias, podemos abstratir os adaversarios e a bola, em um primeiro momento, como simples pontos. Note que esta nao eh a configuracao ideal e deve ser usada com foco para testes e implementacoes rapidas. */
    std::vector<posXY>& robosAdv_posXY; /* reprefencia para os robos adversarios, representados como pontos. */
    posXY& bola_posXY; /* referencia para a bola, presentada como um ponto. */

  public:
    /**
     * Contrutor do tecnico, apenas copiando as referencias dos componentes (initialization lists) necessarios para seu funcionamento e as armazenando internamente.
     * @param r    Referencia para vector dos robos do time.
     * @param rAdv Referencia para o vector de robos adversarios.
     * @param b    Referencia para a bola.
     */
    Tecnico(std::vector<Robo>& r, std::vector<Robo>& rAdv, Bola& b);

    /**
     * Contrutor do tecnico, apenas copiando as referencias dos componentes (initialization lists) necessarios para seu funcionamento e as armazenando internamente. Constrututor utilizado para usu exclusivo da simplificacao e da-se preferencia sempre ao Constrututor acima.
     * @param r    Referencia para vector dos robos do time.
     * @param rAdv Referencia para o vector de robos adversarios.
     * @param b    Referencia para a bola.
     */
    Tecnico(std::vector<Robo>& r, std::vector<posXY>& rAdv, posXY& b);

    /* metodo a ser implementado pelas classes descendentes, devera rodar os roteiros dos robos e realizar as demais atividades definidas para aquele tecnico. */
    virtual void run() = 0;
};


#endif /* TECNICO_H */
