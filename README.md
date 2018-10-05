# VSS
Repositório do software de controle, estratégia e visão do time Carrossel Caipira

## Compilação
Para compilar, no presente momento, utilize o script `compile.sh` através do comando `./compile.sh`.

Este script contém instruções para dois compiladores, o `CLANG` e o `GCC`.

## Compiladores
Teoricamente todos os compiladores que estão capazes de utilizar o padrão `c++11` são suportados.

Até o momento, foram estados os seguintes compiladores:
- `CLANG`;
- `GCC`;

## OpenCV
### Instalação
Para que o código seja compilado é necessário possuir o OpenCV corretamente instalado em seu computador.
(futuramente - criar passo a passa para instalação do opencv em diversas plataformas.)

### Verificação da instalação
Para verificar se sua instalação do OpenCV está correta digite o comando: `pkg-config opencv --libs`, caso receba um retorno parecido com este:

`-L/usr//usr/lib64 -lopencv_face -lopencv_ml -lopencv_objdetect -lopencv_shape -lopencv_stitching -lopencv_superres -lopencv_tracking -lopencv_dnn -lopencv_plot -lopencv_videostab -lopencv_calib3d -lopencv_features2d -lopencv_highgui -lopencv_videoio -lopencv_imgcodecs -lopencv_video -lopencv_photo -lopencv_imgproc -lopencv_flann -lopencv_core`

significa que sua instalação está correta.
