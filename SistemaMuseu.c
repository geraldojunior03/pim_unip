#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <locale.h>
#include <time.h>

struct Pessoa {
    char nome[100], dataNasc[50], cpf[50], carteiraEstudante[50], estudante, celular[50];
    int dia, mes, ano, idade;
};

struct Ticket {
    char idTicket[50], idTransacao[50], dataCompra[20], statusTicket[3];
    double valorTicket;
};

char username[20], password[20];
int authenticated = 0; // Variável para verificar se o usuário está autenticado
int choice; // Variável para realizar scanf de escolhas
double valorTotalTicket = 30.0;
time_t tempo_atual;

int operacaoSucesso() {
    system("cls");
    printf("========================================================================================================================");
    printf("========================================================================================================================");
    printf("\n\n\t\t\t\t\t OPERAÇÃO REALIZADA COM SUCESSO\n");
    printf("\t\t\t\t    AGUARDE UM INSTANTE QUE VOCÊ SERÁ REDIRECIONADO\n\n");
    printf("========================================================================================================================");
    printf("========================================================================================================================\n");
}

int telaLogin() {
    printf("========================================================================================================================");
    printf("========================================================================================================================");
    printf("\n\t\t\t\t\t SEJA BEM-VINDO AO MUSEU UNIP\n");
    printf("\t\t\t\t    REALIZE O LOGIN PARA ACESSAR O SISTEMA\n\n");
    printf("========================================================================================================================");
    printf("========================================================================================================================\n");

    while (!authenticated) {
        printf("Usuario: ");
        scanf("%s", username);
        printf("Senha: ");

        int i = 0;
        while (1) {
            char ch = getch();
            if (ch == 13) {
                password[i] = '\0';
                break;
            }
            else if (ch == 8) {
                if(i > 0) {
                    i--;
                    password[i] = '\0'; // Define o último caractere como nulo
                    printf("\b \b"); // Apaga o caractere na tela
                }
            }
            else {
                password[i] = ch;
                putchar('*'); // Mostra '*' no lugar dos caracteres da senha
                i++;
            }
        }
        password[i] = '\0'; // Termina a string de senha

        // Limpa a tela
        system("cls");

        // Verifica as credenciais de logi
        if (strcmp(username, "admin") == 0 && strcmp(password, "admin") == 0) {
            authenticated = 2; // O usuário está autenticado como admin
            telaOpcoesInicial();
        }
        else if (strcmp(username, "func") == 0 && strcmp(password, "func") == 0) {
            authenticated = 1; // O usuário está autenticado como funcionario
            telaOpcoesInicial();
        }
        else {
            printf("========================================================================================================================");
            printf("========================================================================================================================");
            printf("\n\n\t\t\t\t  DESCULPE, MAS AS CREDENCIAIS SAO INVALIDAS\n");
            printf("\t\t\t\t    EM CASO DE ERRO, CHAME UM ADMINISTRADOR\n\n");
            printf("========================================================================================================================");
            printf("========================================================================================================================\n\n");
        }
    }
}

int telaOpcoesInicial() {
    printf("========================================================================================================================");
    printf("========================================================================================================================");
    printf("\n\n\t\t\t\t\t\t\tMENU GLOBAL\n");
    printf("\t\t\t\t\t\tSEJA BEM-VINDO AO MENU GLOBAL\n\n");
    printf("========================================================================================================================");
    printf("========================================================================================================================\n\n");

    switch (authenticated) {
    case 1:
    case 2:
        printf("1 - Novo Ticket\n");
        printf("2 - Consultar Ticket\n");
        printf("3 - Agendar visitas educativas\n");
        printf("4 - Alterar data de visitas educativas\n");
        printf("5 - Estorno de ticket\n");
        if (authenticated == 2) {
            printf("6 - Excluir ticket\n");
            printf("7 - Alterar ticket\n");
        }
        printf("0 - Fazer LogOut\n");
        printf("\nEscolha uma opcao: ");
        scanf("%d", &choice);
        break;
    default:
        printf("Opção não reconhecida.\n");
        break;
    }

    switch (choice) {
    case 0:
        authenticated = 0;
        system("cls");
        telaLogin();
        break;
    case 1:
        system("cls");
        telaNovoTicket();
        break;
    case 2:
        system("cls");
        consultarTicket();
        break;
    }
}

void consultarDadosPorNomeCompleto(const char *cpfProcurado) {
    FILE *arquivo = fopen("dados.csv", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    char linha[256];

    printf("Estes foram todos os resultados para o CPF: \"%s\":\n\n", cpfProcurado);

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        // A função strtok é usada para dividir a linha em campos usando ',' como delimitador
        char *nomeSalvo = strtok(linha, ",");
        char *dataNasc = strtok(NULL, ",");
        char *cpfSalvo = strtok(NULL, ",");
        if (nomeSalvo != NULL && cpfSalvo != NULL) {
            // Use a função strstr para verificar se o nomeSalvo contém o nomeProcurado
            if (strstr(cpfSalvo, cpfProcurado) != NULL) {

                printf("Nome: %s\n", nomeSalvo);
                printf("Data de Nascimento: %s\n", dataNasc);
                printf("CPF: %s\n", cpfSalvo);

                char *celular = strtok(NULL, ",");
                char *carteiraEstudante = strtok(NULL, ",");
                char *valorTicket = strtok(NULL, ",");
                char *idTicket = strtok(NULL, ",");
                char *idTransacao = strtok(NULL, ",");
                char *dataCompra = strtok(NULL, ",");
                char *statusTicket = strtok(NULL, ",");
                if (celular != NULL) {
                    printf("Celular: %s\n", celular);
                }
                if (carteiraEstudante != NULL) {
                    printf("Carteira de Estudante: %s\n", carteiraEstudante);
                }
                printf("Valor do Ticket: R$%s,00\n", valorTicket);
                printf("ID do Ticket: %s\n", idTicket);
                printf("ID da Transação: %s\n", idTransacao);
                if (dataCompra != NULL) {
                    printf("Data da compra: %s\n", dataCompra);
                }
                if (statusTicket != NULL) {
                    printf("Status Ticket: %s\n", statusTicket);
                }
            }
        }
    }

    fclose(arquivo);
    printf("\n\n========================================================================================================================");
    printf("========================================================================================================================");
    printf("FIM DA LISTA :(\n");
    printf("Pressione F2 para retornar ao menu inicial.");
    while (1) {
        choice = getch(); // Obtém a tecla pressionada

        if (choice == 0) {
            choice = getch();

            if (choice == 60) {
                system("cls");
                telaOpcoesInicial();
            }
            else {
                printf("\n\nDesculpe, opção inválida.\n");
                printf("Pressione F2 para retornar ao menu inicial.");
            }
        }
    }
}

int consultarTicket() {
    char cpf[50]; // Aumente o tamanho para acomodar nome e sobrenome

    printf("========================================================================================================================");
    printf("========================================================================================================================");
    printf("\n\n\t\t\t\t\t\tCONSULTA DE UM TICKET\n");
    printf("\t\t\t\t\tSEJA BEM-VINDO AO MENU DE CONSULTA DE TICKETS\n\n");
    printf("========================================================================================================================");
    printf("========================================================================================================================\n\n");

    printf("Digite o CPF do visitante: ");
    scanf(" %[^\n]", cpf); // Use %[^\n] para ler toda a linha, incluindo espaços

    consultarDadosPorNomeCompleto(cpf);
}

int telaNovoTicket() {
    struct Pessoa pessoa;
    struct Ticket ticket;
    tempo_atual = time(NULL);
    struct tm tm = *localtime(&tempo_atual);
    FILE *arquivo;

    int dia_atual = tm.tm_mday;
    int mes_atual = tm.tm_mon + 1;
    int ano_atual = tm.tm_year + 1900;

    int choice;
    int mensagemInicialTicket() {
        printf("========================================================================================================================");
        printf("========================================================================================================================");
        printf("\n\n\t\t\t\t\t\tCOMPRA DE UM TICKET\n");
        printf("\t\t\t\t\tSEJA BEM-VINDO AO MENU DE COMPRA DE TICKET\n\n");
        printf("========================================================================================================================");
        printf("========================================================================================================================\n\n");
    }

    mensagemInicialTicket();

    printf("Para prosseguir com a compra, aperta F1\n");
    printf("Se não gostaria de prosseguir com a compra, pressione F2\n\n");

    while (1) {
        choice = getch(); // Obtém a tecla pressionada

        if (choice == 0) {
            choice = getch();

            if (choice == 59) { // F1
                system("cls");
                mensagemInicialTicket();

                arquivo = fopen("dados.csv", "a");
                if (arquivo == NULL) {
                    printf("Não foi possível abrir o arquivo.\n");
                    return 1;
                }

                printf("Nome: ");
                fflush(stdin);  // Limpa o buffer de entrada
                fgets(pessoa.nome, sizeof(pessoa.nome), stdin);
                pessoa.nome[strcspn(pessoa.nome, "\n")] = '\0';
                // Converte o nome para letras minúsculas
                int i = 0;
                while (pessoa.nome[i]) {
                    pessoa.nome[i] = tolower(pessoa.nome[i]);
                    i++;
                }
                printf("Data de nascimento (dd/mm/aaaa): ");
                scanf("%s", pessoa.dataNasc);
                // Fazendo validação para garantir que o usuário se adequa a regra de desconto
                if (sscanf(pessoa.dataNasc, "%2d/%2d/%4d", &pessoa.dia, &pessoa.mes, &pessoa.ano) == 3) {
                    if(pessoa.mes > mes_atual) {
                        pessoa.idade = (ano_atual - pessoa.ano) - 1;
                    }
                    else if(pessoa.mes == mes_atual && pessoa.dia > dia_atual) {
                        pessoa.idade = (ano_atual - pessoa.ano) - 1;
                    }
                    else {
                        pessoa.idade = (ano_atual - pessoa.ano);
                    }
                }

                printf("CPF (apenas numeros): ");
                fflush(stdin);  // Limpa o buffer de entrada
                fgets(pessoa.cpf, sizeof(pessoa.cpf), stdin);
                pessoa.cpf[strcspn(pessoa.cpf, "\n")] = '\0';

                printf("Tem celular? (S/N): ");
                fflush(stdin);
                char temCelular;
                scanf(" %c", &temCelular);

                if (temCelular == 'S' || temCelular == 's') {
                    printf("Celular para contato (COM DDD): ");
                    scanf("%s", pessoa.celular);
                }

                printf("Estudante (S/N): ");
                fflush(stdin);
                char pessoaEstudante;
                scanf(" %c", &pessoaEstudante);

                if(pessoaEstudante == 'S' || pessoaEstudante == 's') {
                    printf("Digite o código da carteirinha: ");
                    scanf(" %s", &pessoa.carteiraEstudante);
                }

                // Fazendo validação para pagamento de meia entrada
                if(pessoa.idade >= 2 && pessoa.idade <= 12 || pessoa.idade >= 60 ) {
                    ticket.valorTicket = valorTotalTicket / 2;
                }
                else if (pessoaEstudante == 'S' || pessoaEstudante == 's') {
                    ticket.valorTicket = valorTotalTicket / 2;
                }
                else {
                    ticket.valorTicket = valorTotalTicket;
                }

                //Gerando código do ticket
                char codigo[12];  // 5 números, 3 letras maiúsculas, 2 números, mais o caractere nulo
                srand(time(NULL));

                // Gera 5 números aleatórios
                for (int i = 0; i < 5; i++) {
                    codigo[i] = '0' + rand() % 10;
                }

                // Gera 3 letras maiúsculas aleatórias
                for (int i = 5; i < 8; i++) {
                    codigo[i] = 'A' + rand() % 26;
                }

                // Gera 2 números aleatórios
                for (int i = 8; i < 10; i++) {
                    codigo[i] = '0' + rand() % 10;
                }

                codigo[10] = '\0';
                strcpy(ticket.idTicket, codigo);
                strncpy(ticket.idTransacao, ticket.idTicket, 5);

                // Formate a data atual e armazene-a em dataAtual
                snprintf(ticket.dataCompra, sizeof(ticket.dataCompra), "%02d/%02d/%04d", dia_atual, mes_atual, ano_atual);
                ticket.statusTicket[0] = 'A';

                if((pessoaEstudante == 'S' || pessoaEstudante == 's') && (temCelular == 'S' || temCelular == 's')) {
                    fprintf(arquivo, "%s,%s,%s,%s,%s,%.0f,%s,%s,%s,%s\n", pessoa.nome, pessoa.dataNasc, pessoa.cpf, pessoa.celular, pessoa.carteiraEstudante, ticket.valorTicket, ticket.idTicket, ticket.idTransacao, ticket.dataCompra, ticket.statusTicket);
                }
                else {
                    fprintf(arquivo, "%s,%s,%s,%.0f,%s,%s,%s,%s\n", pessoa.nome, pessoa.dataNasc, pessoa.cpf, ticket.valorTicket, ticket.idTicket, ticket.idTransacao, ticket.dataCompra, ticket.statusTicket);
                }
                operacaoSucesso();
                Sleep(2000);
                fclose(arquivo);
                system("cls");
                telaOpcoesInicial();
            }
            else if (choice == 60) { // F2
                system("cls");
                printf("Retornando ao menu principal...\n");
                Sleep(2000);
                system("cls");
                telaOpcoesInicial();
            }
            else {
                printf("Desculpe, mas essa tecla não corresponde as opções, pressione:\n");
                printf("F1 - Prosseguir com a compra;\n");
                printf("F2 - Retornar ao menu global.\n");
            }
        }
    }
}

int main() {
    setlocale(LC_ALL, "Portuguese");
    telaLogin();

    return 0;
}
