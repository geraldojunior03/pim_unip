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
    printf("\n\n\t\t\t\t\t\tAGRADECEMOS SUA VOTAÇÃO\n");
    printf("\t\t\t\tSEU GRAU DE SATISFAÇÃO COM AS OBRAS É MUITO IMPORTANTE\n\n");
    printf("========================================================================================================================");
    printf("========================================================================================================================\n\n");

    printf("Seu grau de satisfação com a obra que foi exposta foi: %s\n\n", satisfacao);
}

void atualizarSatisfacao(char *arquivo, char *satisfacao) {
    // Abrir o arquivo para leitura e escrita
    FILE *arquivoEntrada = fopen(arquivo, "a+");
    if (arquivoEntrada == NULL) {
        printf("Erro ao abrir o arquivo para leitura e escrita.\n");
        return;
    }

    // Verificar se o arquivo está vazio (não contém nenhuma linha)
    fseek(arquivoEntrada, 0, SEEK_END);
    if (ftell(arquivoEntrada) == 0) {
        // Se o arquivo estiver vazio, escrever as linhas iniciais
        fprintf(arquivoEntrada, "Muito Insatisfeito,0\n");
        fprintf(arquivoEntrada, "Insatisfeito,0\n");
        fprintf(arquivoEntrada, "Razoável,0\n");
        fprintf(arquivoEntrada, "Satisfeito,0\n");
        fprintf(arquivoEntrada, "Muito Satisfeito,0\n");
        fseek(arquivoEntrada, 0, SEEK_SET); // Voltar ao início do arquivo
    }

    // Criar um arquivo temporário para armazenar as alterações
    FILE *arquivoTemp = fopen("temp.csv", "w");
    if (arquivoTemp == NULL) {
        printf("Erro ao criar arquivo temporário.\n");
        fclose(arquivoEntrada);
        return;
    }

    char linha[100]; // Ajuste o tamanho conforme necessário

    // Loop através das linhas do arquivo
    while (fgets(linha, sizeof(linha), arquivoEntrada) != NULL) {
        char linhaAtual[100];
        strcpy(linhaAtual, linha);

        char *token = strtok(linha, ",");
        if (token != NULL && strcmp(token, satisfacao) == 0) {
            // Encontrou a linha, incrementar o valor numérico
            int valorNumerico;
            token = strtok(NULL, ",");
            if (token != NULL) {
                valorNumerico = atoi(token);
                valorNumerico++;
                fprintf(arquivoTemp, "%s,%d\n", satisfacao, valorNumerico);
            } else {
                // Se não houver número após a satisfação, copie a linha como está
                fprintf(arquivoTemp, "%s", linhaAtual);
            }
        } else {
            // Não é a linha desejada, copiar como está
            fprintf(arquivoTemp, "%s", linhaAtual);
        }
    }

    // Fechar os arquivos
    fclose(arquivoEntrada);
    fclose(arquivoTemp);

    // Remover o arquivo original
    remove(arquivo);

    // Renomear o arquivo temporário para o original
    rename("temp.csv", arquivo);

    agradecimentosVotacao(satisfacao);
}


void mensagemQuestionario(int obra) {
    printf("========================================================================================================================");
    printf("========================================================================================================================");
    printf("\n\n\t\t\t\t\t\tGRAU DE SATISFAÇÃO\n");
    printf("\t\t\t\tESCOLHA A OPÇÃO MEDIANTE À SATISFAÇÃO DESSA OBRA EXPOSTA\n\n");
    printf("========================================================================================================================");
    printf("========================================================================================================================\n\n");

    // Apresenta as opções de satisfação
    printf("1 - Muito Insatisfeito\n");
    printf("2 - Insatisfeito\n");
    printf("3 - Razoável\n");
    printf("4 - Satisfeito\n");
    printf("5 - Muito Satisfeito\n");

    // Solicitando a opção para validar satisfação
    printf("\nDigite a opção desejada: ");
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
        strcpy(satisfacao, "Razoável");
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
        printf("\t\t\t\t\tDIGITE A OPÇÃO QUE CORRESPONDE A OBRA EXPOSTA\n\n");
        printf("========================================================================================================================");
        printf("========================================================================================================================\n\n");
    }

    mensagemOpcoes();
    // Apresenta as opções
    printf("1 - Primeiro Jogo Olímpico\n");
    printf("2 - História da Tocha Olímpica\n");
    printf("3 - História dos Símbolos Olímpicos\n");
    printf("4 - Uniforme Koroebus\n");
    printf("5 - Homenagens aos Atletas\n");

    // Solicita a escolha do usuário
    printf("\nDigite a opção desejada: ");
    scanf("%d", &escolha);

    // Executa a opção escolhida
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
