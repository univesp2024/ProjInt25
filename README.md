# Sistema de Monitoramento Preditivo de Motores (ESP32 + MPU6050 + WebSocket + Dashboard)
Monitoramento de vibração em tempo real para manutenção preditiva no setor industrial. O dispositivo lê aceleração em três eixos, envia pacotes frequentes a um servidor que redistribui os dados para dashboards web, permitindo visualização ao vivo e criação de histórico para evolução a modelos de detecção de anomalia.

## Visão geral
- Objetivo: antecipar falhas em motores reduzindo paradas não planejadas, via telemetria contínua de vibração e visualização em tempo real.
- Escopo: motores trifásicos de médio porte, foco inicial em vibração; outras variáveis podem ser integradas em fases futuras.
- Stack: ESP32 + MPU6050 (coleta), canal contínuo para servidor (distribuição), dashboard web (visualização).

## Arquitetura
- Dispositivo: coleta aceleração em X/Y/Z e envia pacotes em alta frequência para garantir resposta visual rápida no dashboard.
- Servidor: recebe cada pacote e redistribui para todos os clientes conectados, permitindo múltiplos dashboards simultâneos.
- Dashboard: estabelece a conexão contínua com o servidor, interpreta os pacotes e atualiza as curvas em tempo real.

Fluxo: Dispositivo → Canal contínuo → Servidor → Dashboards.

## Requisitos
- Hardware: ESP32, MPU6050, cabos I2C, fonte/USB.
- Software (dispositivo): IDE Arduino/PlatformIO, bibliotecas para MPU6050 e comunicação.
- Software (servidor): Python 3.10+, framework web com suporte a canal contínuo e biblioteca de sockets, execução em 0.0.0.0:5000 por padrão.
- Front-end: navegador moderno para abrir index.html e dashboard.html.

## Instalação
1) Dispositivo
- Conecte o MPU6050 ao ESP32 via I2C.
- Abra o firmware do projeto e configure rede (SSID/senha) e o endereço do servidor.
- Compile e faça o upload para o ESP32.

2) Servidor
- Crie e ative um ambiente virtual Python.
- Instale as dependências listadas no projeto.
- Execute o servidor na máquina que receberá os dados, acessível pelo ESP32.

3) Front-end
- Coloque os arquivos HTML do projeto acessíveis pelo servidor ou abra localmente apontando para o endereço do servidor contínuo.

## Execução
- Inicie o servidor na porta padrão (5000).
- Alimente o ESP32 e aguarde as mensagens de conexão e o IP no monitor serial, indicando que a telemetria está fluindo.
- Abra o dashboard no navegador; movimentações leves no sensor devem se refletir instantaneamente nas curvas X/Y/Z.

## Uso
- Operação: o dispositivo envia pacotes de vibração em intervalos curtos; o servidor os repassa a todos os dashboards conectados.
- Diagnóstico: mensagens simples indicam estado do canal (conectado/desconectado), úteis para suporte em campo.
- Visualização: o dashboard atualiza as séries em tempo real e diferencia padrões normais de comportamentos anômalos.

## Estrutura do repositório
- Projeto_FInal_ESP32_MPU6050.ino — firmware do dispositivo (coleta, empacotamento e envio periódico).
- server.py — serviço que recebe e redistribui os pacotes aos clientes conectados.
- index.html — ponto de entrada do front-end.
- dashboard.html — visualização ao vivo das leituras em X, Y e Z.
- Relatorio_Final.docx — documento técnico do projeto (contexto, metodologia e resultados).

## Configuração
- Rede: defina SSID, senha e IP/host do servidor no firmware do ESP32.
- Porta: servidor padrão em 5000; ajuste conforme sua infraestrutura.
- Acesso: garanta que o ESP32 alcance o servidor pela rede (mesmo segmento ou roteamento configurado).
## Créditos
- Projeto acadêmico no contexto do Projeto Integrador, UNIVESP, com desenvolvimento do firmware, servidor e dashboard conforme descrito no relatório técnico.
