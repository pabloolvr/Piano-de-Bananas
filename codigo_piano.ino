const int limiarPressionado = 400; //limite de detecc'ao para saber quando a tecla esta precionada
const int limiarSolto = 500; //ponto mi'nimo pra averiguac'ao se a tecla esta' solta
const byte numPinos = 6;


const byte pinosEntrada[numPinos] = {A0, A1, A2, A3, A4, A5}; //identificac'ao dos pinos analo'gios
const char teclas[numPinos] = {'t', 'y', 'u', 'i', 'o', 'p'}; //teclas a serem precionadas


//struct que conte'm a entrada dos pinos analo'gicos e teclas
struct estruturaEntrada
{
  byte pinoAnalogico; //identificaca'o do pino de entrada
  char tecla; 
  movingAvg filtro = movingAvg(20); //filtro de ca'lculo de me'dia da leitura considerando 20 pontos de dados
  boolean pressionado = false; //boolean pra verificar se a tecla esta pressionada ou nao
};


estruturaEntrada pinos[numPinos]; //numero total de pinos


void setup()
{
  Serial.begin(115200); //inicializaca'o da comunicaca'o serial
 
  for (int i = 0; i < numPinos; i++)
  {
    //inicializaca'o das estruturas com os valores dos vetores
    pinos[i].pinoAnalogico = pinosEntrada[i];
    pinos[i].tecla = teclas[i];

    //inicializaca'o do ca'lculo de variaca'o me'dia analo'gica
    pinos[i].filtro.begin(); 
  }
}

void loop()
{
  //varredura do vetor de pinos
  for (int i = 0; i < numPinos; i++)
  {
    float mediaAtual = pinos[i].filtro.reading(analogRead(pinos[i].pinoAnalogico)); //leitura me'dia do pino de entrada da estrutura
    boolean estadoAnterior = pinos[i].pressionado; //registra o estado anterior
    boolean estadoAtual = estadoAnterior; //registra o estado atual, que ainda e' igual ao anterior
    Serial.print(mediaAtual); //exibe o valor lido pelo sensor
    Serial.print("\t");

    if (mediaAtual < limiarPressionado)
    {
      estadoAtual = true;      // Tecla pressionada
    }
    else if  (mediaAtual > limiarSolto)
    {
      estadoAtual = false;      // Tecla solta
    }

    //verificacao de mudanca de estado
    if (estadoAtual != estadoAnterior)
    {
      if (estadoAtual)
        Keyboard.press(pinos[i].tecla); //se a entrada for ativa, pressiona a tecla equivalente
      else
        Keyboard.release(pinos[i].tecla); //se a entrada for inativa, solta a tecla equivalente
    }
    pinos[i].pressionado = estadoAtual; //armazena o estado atual na estrutura
  }
  Serial.println();
}
