#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <stdlib.h>

// Variaveis global
int escolha, escolhaSatisfacao;
char satisfacao[20];

void agradecimentosVotacao(char *satisfacao) {
    system("cls");

    printf("========================================================================================================================");
    printf("========================================================================================================================");
    printf("\n\n\t\t\t\t\t\tAGRADECEMOS SUA VOTA��O\n");
    printf("\t\t\t\tSEU GRAU DE SATISFA��O COM AS OBRAS � MUITO IMPORTANTE\n\n");
    printf("========================================================================================================================");
    printf("========================================================================================================================\n\n");

    printf("Seu grau de satisfa��o com a obra que foi exposta foi: %s\n\n", satisfacao);
}

void atualizarSatisfacao(char *arquivo, char *satisfacao) {
    // Abrir o arquivo para leitura e escrita
    FILE *arquivoEntrada = fopen(arquivo, "a+");
    if (arquivoEntrada == NULL) {
        printf("Erro ao abrir o arquivo para leitura e escrita.\n");
        return;
    }

    // Verificar se o arquivo est� vazio (n�o cont�m nenhuma linha)
    fseek(arquivoEntrada, 0, SEEK_END);
    if (ftell(arquivoEntrada) == 0) {
        // Se o arquivo estiver vazio, escrever as linhas iniciais
        fprintf(arquivoEntrada, "Muito Insatisfeito,0\n");
        fprintf(arquivoEntrada, "Insatisfeito,0\n");
        fprintf(arquivoEntrada, "Razo�vel,0\n");
        fprintf(arquivoEntrada, "Satisfeito,0\n");
        fprintf(arquivoEntrada, "Muito Satisfeito,0\n");
        fseek(arquivoEntrada, 0, SEEK_SET); // Voltar ao in�cio do arquivo
    }

    // Criar um arquivo tempor�rio para armazenar as altera��es
    FILE *arquivoTemp = fopen("temp.csv", "w");
    if (arquivoTemp == NULL) {
        printf("Erro ao criar arquivo tempor�rio.\n");
        fclose(arquivoEntrada);
        return;
    }

    char linha[100]; // Ajuste o tamanho conforme necess�rio

    // Loop atrav�s das linhas do arquivo
    while (fgets(linha, sizeof(linha), arquivoEntrada) != NULL) {
        char linhaAtual[100];
        strcpy(linhaAtual, linha);

        char *token = strtok(linha, ",");
        if (token != NULL && strcmp(token, satisfacao) == 0) {
            // Encontrou a linha, incrementar o valor num�rico
            int valorNumerico;
            token = strtok(NULL, ",");
            if (token != NULL) {
                valorNumerico = atoi(token);
                valorNumerico++;
                fprintf(arquivoTemp, "%s,%d\n", satisfacao, valorNumerico);
            } else {
                // Se n�o houver n�mero ap�s a satisfa��o, copie a linha como est�
                fprintf(arquivoTemp, "%s", linhaAtual);
            }
        } else {
            // N�o � a linha desejada, copiar como est�
            fprintf(arquivoTemp, "%s", linhaAtual);
        }
    }

    // Fechar os arquivos
    fclose(arquivoEntrada);
    fclose(arquivoTemp);

    // Remover o arquivo original
    remove(arquivo);

    // Renomear o arquivo tempor�rio para o original
    rename("temp.csv", arquivo);

    agradecimentosVotacao(satisfacao);
}


void mensagemQuestionario(int obra) {
    printf("========================================================================================================================");
    printf("========================================================================================================================");
    printf("\n\n\t\t\t\t\t\tGRAU DE SATISFA��O\n");
    printf("\t\t\t\tESCOLHA A OP��O MEDIANTE � SATISFA��O DESSA OBRA EXPOSTA\n\n");
    printf("========================================================================================================================");
    printf("========================================================================================================================\n\n");

    // Apresenta as op��es de satisfa��o
    printf("1 - Muito Insatisfeito\n");
    printf("2 - Insatisfeito\n");
    printf("3 - Razo�vel\n");
    printf("4 - Satisfeito\n");
    printf("5 - Muito Satisfeito\n");

    // Solicitando a op��o para validar satisfa��o
    printf("\nDigite a op��o desejada: ");
    scanf("%d", &escolhaSatisfacao);

    FILE *arquivo;

    switch (escolhaSatisfacao) {
    case 1:
        strcpy(satisfacao, "Muito Insatisfeito");
        break;
    case 2:
        strcpy(satisfacao, "Insatisfeito");
        break;
    case 3:
        strcpy(satisfacao, "Razo�vel");
        break;
    case 4:
        strcpy(satisfacao, "Satisfeito");
        break;
    case 5:
        strcpy(satisfacao, "Muito Satisfeito");
        break;
    }

    switch (obra) {
    case 1:
        atualizarSatisfacao("satisfacoes/satisfacao_primeiro_jogo.csv", satisfacao);
        break;
    case 2:
        atualizarSatisfacao("satisfacoes/satisfacao_historia_tocha.csv", satisfacao);
        break;
    case 3:
        atualizarSatisfacao("satisfacoes/satisfacao_historia_simbolos.csv", satisfacao);
        break;
    case 4:
        atualizarSatisfacao("satisfacoes/satisfacao_uniforme_koroebus.csv", satisfacao);
        break;
    case 5:
        atualizarSatisfacao("satisfacoes/satisfacao_homenagem_atletas.csv", satisfacao);
        break;
    }
}

void primeiroJogo() {
    mensagemQuestionario(1);
}

void historiaTocha() {
    mensagemQuestionario(2);
}

void historiaSimbolos() {
    mensagemQuestionario(3);
}

void uniformeKoroebus() {
    mensagemQuestionario(4);
}

void homenagemAtletas() {
    mensagemQuestionario(5);
}

void telaOpcoes() {
    int mensagemOpcoes() {
        printf("========================================================================================================================");
        printf("========================================================================================================================");
        printf("\n\n\t\t\t\t\t\tSELECIONE A OBRA EXPOSTA\n");
        printf("\t\t\t\t\tDIGITE A OP��O QUE CORRESPONDE A OBRA EXPOSTA\n\n");
        printf("========================================================================================================================");
        printf("========================================================================================================================\n\n");
    }

    mensagemOpcoes();
    // Apresenta as op��es
    printf("1 - Primeiro Jogo Ol�mpico\n");
    printf("2 - Hist�ria da Tocha Ol�mpica\n");
    printf("3 - Hist�ria dos S�mbolos Ol�mpicos\n");
    printf("4 - Uniforme Koroebus\n");
    printf("5 - Homenagens aos Atletas\n");

    // Solicita a escolha do usu�rio
    printf("\nDigite a op��o desejada: ");
    scanf("%d", &escolha);

    // Executa a op��o escolhida
    switch (escolha) {
        case 1:
            system("cls");
            primeiroJogo();
            break;
        case 2:
            system("cls");
            historiaTocha();
            break;
        case 3:
            system("cls");
            historiaSimbolos();
            break;
        case 4:
            system("cls");
            uniformeKoroebus();
            break;
        case 5:
            system("cls");
            homenagemAtletas();
            break;
        default:
            telaOpcoes();
            break;
    }
}

int main() {
    setlocale(LC_ALL, "Portuguese");
    telaOpcoes();

    return 0;
}
