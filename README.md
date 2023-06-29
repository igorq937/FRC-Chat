# FRC-Chat
Este projeto foi desenvolvido como entrega para a matéria de Fundamentos de Redes de Computadores, da Faculdade do Gama, da Universidade de Brasília.

# Sobre o projeto
Este projeto tem como objetivo permitir que o aluno compreenda a arquitetura de aplicações de rede (segundo arquitetura TCP/IP) que envolvam gerência de diálogo. Para isso, deve construir uma aplicação que disponibilize salas de bate-papo virtuais, nas quais os clientes podem ingressar e interagir.

## Informações
Linguagem utilizada: C <br>
Sistema Operacional: Linux

# Funcionalidades da aplicação
- Criação de salas virtuais de bate-papo com nome da sala e limite de participantes;
- Listar participantes de uma determinada sala;
- Permitir ingresso de clientes, com um identificador, em uma sala existente, de acordo com o limite
admitido para a sala;
- Saída de clientes de uma sala em que estava participando;
- Diálogo entre os clientes das salas.

# Instruções de uso
## 
1. Para ter a aplicação disponível em sua máquina, é necessário clonar o repositório em uma pasta do computador:

    ```bash
    git clone https://github.com/igorq937/FRC-Chat.git
    ```

2. Posteriormente, deve-se abrir o terminal, entrar no diretório clonado e executar os seguintes comandos:

- Para compilar o programa
    ```bash
    make all
    ```

- Para executar a aplicação
    ```bash
    ./bin <IP> <Porta>
    ```

- Para limpar a compilação
    ```bash
    make clean
    ```

3. Para estabelecer a conexão, basta utilizar o comando ```telnet <IP> <Porta>```. <br><br>

**Obs:** Caso necessite de alguma orientação, basta executar o comando ```/help```.