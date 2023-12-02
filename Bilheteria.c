#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <locale.h>
#include <time.h>

char username[20], password[20];
int authenticated = 0; // Vari�vel para verificar se o usu�rio est� autenticado
int choice; // Vari�vel para realizar scanf de escolhas
double valorTotalTicket = 30.0;
time_t tempo_atual;

struct Pessoa {
    char nome[100], dataNasc[50], cpf[50], carteiraEstudante[50], estudante, celular[50];
    int dia, mes, ano, idade;
};

struct Ticket {
    char idTicket[50], idTransacao[50], dataCompra[20], statusTicket[3];
    double valorTicket;
};

struct Visitas {
    char razaoSocialInstituicao[50];
    char data[20];
    char cnpj[20];
    char telefone[50];
    char responsavel[100];
    int qtdePessoas;
};

void limparEspacos(const char *entrada, char *saida) {
    int i = 0, j = 0;
    while (entrada[i] != '\0') {
        if (!isspace(entrada[i])) {
            saida[j++] = entrada[i];
        }
        i++;
    }
    saida[j] = '\0';
}

void confirmarOperacao() {
    printf("========================================================================================================================");
    printf("========================================================================================================================");
    printf("\n\n\t\t\t\t\t\tCONFIRMAR OPERA��O\n");
    printf("\t\t\t\t\tPRESSIONE UMA DAS OP��ES ABAIXO PARA CONTINUAR!\n\n");
    printf("========================================================================================================================");
    printf("========================================================================================================================\n\n");
    printf("Para prosseguir com a opera��o, aperta F1\n");
    printf("Se n�o gostaria de prosseguir com a opera��o, pressione F2\n\n");
}

int operacaoSucesso() {
    system("cls");
    printf("========================================================================================================================");
    printf("========================================================================================================================");
    printf("\n\n\t\t\t\t\t OPERA��O REALIZADA COM SUCESSO\n");
    printf("\t\t\t\t    AGUARDE UM INSTANTE QUE VOC� SER� REDIRECIONADO\n\n");
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
                    password[i] = '\0'; // Define o �ltimo caractere como nulo
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
            authenticated = 2; // O usu�rio est� autenticado como admin
            telaOpcoesInicial();
        }
        else if (strcmp(username, "func") == 0 && strcmp(password, "func") == 0) {
            authenticated = 1; // O usu�rio est� autenticado como funcionario
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
    int mensagemInicial() {
        printf("========================================================================================================================");
        printf("========================================================================================================================");
        printf("\n\n\t\t\t\t\t\t\tMENU GLOBAL\n");
        printf("\t\t\t\t\t\tSEJA BEM-VINDO AO MENU GLOBAL\n\n");
        printf("========================================================================================================================");
        printf("========================================================================================================================\n\n");
    }

    int opcoes() {
            printf("1 - Novo Ticket\n");
            printf("2 - Consultar Ticket\n");
            printf("3 - Agendar visitas educativas\n");
            printf("4 - Consultar visitas educativas\n");
            printf("5 - Alterar data de visitas educativas\n");
            if (authenticated == 2) {
                printf("6 - Excluir visita\n");
                printf("7 - Estorno de ticket\n");
                printf("8 - Excluir ticket\n");
            }
            printf("0 - Fazer LogOut\n");
            printf("\nEscolha uma opcao: ");
            scanf("%d", &choice);
        }

    mensagemInicial();
    switch (authenticated) {
    case 1:
    case 2:
        opcoes();
        break;
    default:
        printf("Op��o n�o reconhecida.\n");
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
    case 3:
        system("cls");
        telaAgendarVisitas();
        break;
    case 4:
        system("cls");
        consultarVisitas();
        break;
    case 5:
        system("cls");
        alterarDataVisita();
        break;
    case 6:
        if(authenticated == 2) {
            system("cls");
            excluirVisita();
            break;
        }
        else {
            system("cls");
            printf("Op��o n�o reconhecida, tente novamente...\n");
            Sleep(2000);
            system("cls");
            telaOpcoesInicial();
            break;
        }
    case 7:
        if(authenticated == 2) {
            system("cls");
            estornarTicket();
            break;
        }
        else {
            system("cls");
            printf("Op��o n�o reconhecida, tente novamente...\n");
            Sleep(2000);
            system("cls");
            telaOpcoesInicial();
            break;
        }
    case 8:
        if(authenticated == 2) {
            system("cls");
            excluirVisita();
            break;
        }
        else {
            system("cls");
            printf("Op��o n�o reconhecida, tente novamente...\n");
            Sleep(2000);
            system("cls");
            telaOpcoesInicial();
            break;
        }
    default:
        system("cls");
        printf("Op��o n�o reconhecida, tente novamente...\n");
        Sleep(2000);
        system("cls");
        telaOpcoesInicial();
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
        // A fun��o strtok � usada para dividir a linha em campos usando ',' como delimitador
        char *nomeSalvo = strtok(linha, ",");
        char *dataNasc = strtok(NULL, ",");
        char *cpfSalvo = strtok(NULL, ",");
        if (nomeSalvo != NULL && cpfSalvo != NULL) {
            // Use a fun��o strstr para verificar se o nomeSalvo cont�m o nomeProcurado
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
                // Deixando o valor do celular inexistente para N/A quando impresso
                if (strcmp(celular, "000000000000") == 0) {
                    printf("Celular: N/A\n");
                }
                else {
                    printf("Celular: %s\n", celular);
                }

                // Deixando o valor da carteira de estudante inexistente para N/A quando impresso
                if (strcmp(carteiraEstudante, "000000000000") == 0) {
                    printf("Carteira de Estudante: N/A\n");
                }
                else {
                    printf("Carteira de Estudante: %s\n", carteiraEstudante);
                }

                printf("Valor do Ticket: R$%s,00\n", valorTicket);
                printf("ID do Ticket: %s\n", idTicket);
                printf("ID da Transa��o: %s\n", idTransacao);
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
        choice = getch(); // Obt�m a tecla pressionada

        if (choice == 0) {
            choice = getch();

            if (choice == 60) {
                system("cls");
                telaOpcoesInicial();
            }
            else {
                printf("\n\nDesculpe, op��o inv�lida.\n");
                printf("Pressione F2 para retornar ao menu inicial.");
            }
        }
    }
}

int consultarTicket() {
    int mensagemConsultarTicket() {
        printf("========================================================================================================================");
        printf("========================================================================================================================");
        printf("\n\n\t\t\t\t\t\tCONSULTA DE UM TICKET\n");
        printf("\t\t\t\t\tSEJA BEM-VINDO AO MENU DE CONSULTA DE TICKETS\n\n");
        printf("========================================================================================================================");
        printf("========================================================================================================================\n\n");
    }

    confirmarOperacao();

    while (1) {
        choice = getch(); // Obt�m a tecla pressionada

        if (choice == 0) {
            choice = getch();

            if (choice == 59) { // F1
                system("cls");
                char cpf[50]; // Aumente o tamanho para acomodar nome e sobrenome

                mensagemConsultarTicket();

                printf("Digite o CPF do visitante: ");
                scanf(" %[^\n]", cpf); // Use %[^\n] para ler toda a linha, incluindo espa�os
                consultarDadosPorNomeCompleto(cpf);
            }
            else if(choice == 60) {
                system("cls");
                printf("Retornando ao menu principal...\n");
                Sleep(2000);
                telaOpcoesInicial();
            }
            else {
                system("cls");
                confirmarOperacao();
                printf("Desculpe, mas essa tecla nao corresponde as opcoes, pressione:\n");
                printf("F1 - Prosseguir com o agendamento;\n");
                printf("F2 - Retornar ao menu global.\n");
            }
        }
    }
}

int telaNovoTicket() {
    int mensagemNovoTicket() {
        printf("========================================================================================================================");
        printf("========================================================================================================================");
        printf("\n\n\t\t\t\t\t\tCOMPRA DE UM TICKET\n");
        printf("\t\t\t\t\tSEJA BEM-VINDO AO MENU DE COMPRA DE TICKET\n\n");
        printf("========================================================================================================================");
        printf("========================================================================================================================\n\n");
    }

    struct Pessoa pessoa;
    struct Ticket ticket;
    tempo_atual = time(NULL);
    struct tm tm = *localtime(&tempo_atual);
    FILE *arquivo;

    int dia_atual = tm.tm_mday;
    int mes_atual = tm.tm_mon + 1;
    int ano_atual = tm.tm_year + 1900;

    int choice;
    confirmarOperacao();

    while (1) {
        choice = getch(); // Obt�m a tecla pressionada

        if (choice == 0) {
            choice = getch();

            if (choice == 59) { // F1
                system("cls");

                mensagemNovoTicket();

                arquivo = fopen("dados.csv", "a");
                if (arquivo == NULL) {
                    printf("N�o foi poss�vel abrir o arquivo.\n");
                    return 1;
                }

                printf("Nome: ");
                fflush(stdin);  // Limpa o buffer de entrada
                fgets(pessoa.nome, sizeof(pessoa.nome), stdin);
                pessoa.nome[strcspn(pessoa.nome, "\n")] = '\0';
                // Converte o nome para letras min�sculas
                int i = 0;
                while (pessoa.nome[i]) {
                    pessoa.nome[i] = tolower(pessoa.nome[i]);
                    i++;
                }
                printf("Data de nascimento (dd/mm/aaaa): ");
                scanf("%s", pessoa.dataNasc);
                // Fazendo valida��o para garantir que o usu�rio se adequa a regra de desconto
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

                else {
                    strcpy(pessoa.celular, "000000000000");
                }

                printf("Estudante (S/N): ");
                fflush(stdin);
                char pessoaEstudante;
                scanf(" %c", &pessoaEstudante);

                if(pessoaEstudante == 'S' || pessoaEstudante == 's') {
                    printf("Digite o c�digo da carteirinha: ");
                    scanf(" %s", &pessoa.carteiraEstudante);
                }

                else {
                    strcpy(pessoa.carteiraEstudante, "000000000000");
                }

                // Fazendo valida��o para pagamento de meia entrada
                if(pessoa.idade >= 2 && pessoa.idade <= 12 || pessoa.idade >= 60 ) {
                    ticket.valorTicket = valorTotalTicket / 2;
                }
                else if (pessoaEstudante == 'S' || pessoaEstudante == 's') {
                    ticket.valorTicket = valorTotalTicket / 2;
                }
                else {
                    ticket.valorTicket = valorTotalTicket;
                }

                //Gerando c�digo do ticket
                char codigo[12];  // 5 n�meros, 3 letras mai�sculas, 2 n�meros, mais o caractere nulo
                srand(time(NULL));

                // Gera 5 n�meros aleat�rios
                for (int i = 0; i < 5; i++) {
                    codigo[i] = '0' + rand() % 10;
                }

                // Gera 3 letras mai�sculas aleat�rias
                for (int i = 5; i < 8; i++) {
                    codigo[i] = 'A' + rand() % 26;
                }

                // Gera 2 n�meros aleat�rios
                for (int i = 8; i < 10; i++) {
                    codigo[i] = '0' + rand() % 10;
                }

                codigo[10] = '\0';
                strcpy(ticket.idTicket, codigo);
                strncpy(ticket.idTransacao, ticket.idTicket, 5);

                // Formate a data atual e armazene-a em dataAtual
                snprintf(ticket.dataCompra, sizeof(ticket.dataCompra), "%02d/%02d/%04d", dia_atual, mes_atual, ano_atual);
                ticket.statusTicket[0] = 'A';

                fprintf(arquivo, "%s,%s,%s,%s,%s,%.0f,%s,%s,%s,%s\n", pessoa.nome, pessoa.dataNasc, pessoa.cpf, pessoa.celular, pessoa.carteiraEstudante, ticket.valorTicket, ticket.idTicket, ticket.idTransacao, ticket.dataCompra, ticket.statusTicket);

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
                system("cls");
                confirmarOperacao();
                printf("Desculpe, mas essa tecla n�o corresponde as op��es, pressione:\n");
                printf("F1 - Prosseguir com a compra;\n");
                printf("F2 - Retornar ao menu global.\n");
            }
        }
    }
}

int telaAgendarVisitas() {
    void mensagemInicialVisitas() {
        printf("========================================================================================================================");
        printf("========================================================================================================================");
        printf("\n\n\t\t\t\t\t\tAGENDA DE VISITAS EDUCATIVAS\n");
        printf("\t\t\t\t\tSEJA BEM-VINDO AO MENU DE AGENDAMENTO DE VISITAS\n\n");
        printf("========================================================================================================================");
        printf("========================================================================================================================\n\n");
    }

    struct Visitas visitas;
    FILE *arquivo;

    confirmarOperacao();

    while (1) {
        choice = getch(); // Obt�m a tecla pressionada

        if (choice == 0) {
            choice = getch();

            if (choice == 59) { // F1
                system("cls");
                mensagemInicialVisitas();

                arquivo = fopen("visitas.csv", "a");
                if (arquivo == NULL) {
                    printf("Erro ao abrir o arquivo de visitas.\n");
                    return -1;
                }

                printf("Raz�o social: ");
                fflush(stdin);  // Limpa o buffer de entrada
                fgets(visitas.razaoSocialInstituicao, sizeof(visitas.razaoSocialInstituicao), stdin);
                visitas.razaoSocialInstituicao[strcspn(visitas.razaoSocialInstituicao, "\n")] = '\0';

                printf("Data da visita (dd/mm/aaaa): ");
                fgets(visitas.data, sizeof(visitas.data), stdin);
                visitas.data[strcspn(visitas.data, "\n")] = '\0';

                printf("CNPJ da Instituicao: ");
                fgets(visitas.cnpj, sizeof(visitas.cnpj), stdin);
                visitas.cnpj[strcspn(visitas.cnpj, "\n")] = '\0';

                printf("Nome do respons�vel: ");
                fgets(visitas.responsavel, sizeof(visitas.responsavel), stdin);
                visitas.responsavel[strcspn(visitas.responsavel, "\n")] = '\0';

                printf("Telefone para contato: ");
                fgets(visitas.telefone, sizeof(visitas.telefone), stdin);
                visitas.telefone[strcspn(visitas.telefone, "\n")] = '\0';

                fprintf(arquivo, "%s,%s,%s,%s,%s\n", visitas.razaoSocialInstituicao, visitas.data, visitas.cnpj,visitas.responsavel, visitas.telefone);
                fclose(arquivo);
                operacaoSucesso();
                Sleep(2000);
                system("cls");
                telaOpcoesInicial();
            } else if (choice == 60) { // F2
                system("cls");
                printf("Retornando ao menu principal...\n");
                Sleep(2000);
                telaOpcoesInicial();
            } else {
                system("cls");
                confirmarOperacao();
                printf("Desculpe, mas essa tecla nao corresponde as opcoes, pressione:\n");
                printf("F1 - Prosseguir com o agendamento;\n");
                printf("F2 - Retornar ao menu global.\n");
            }
        }
    }
}

int consultarVisitas(){
    int mensagemConsultarVisitas() {
        printf("========================================================================================================================");
        printf("========================================================================================================================");
        printf("\n\n\t\t\t\t\t\tCONSULTA DE VISITAS\n");
        printf("\t\t\t\t\tSEJA BEM-VINDO AO MENU DE CONSULTA DE VISITAS\n\n");
        printf("========================================================================================================================");
        printf("========================================================================================================================\n\n");
    }
    confirmarOperacao();

    while (1) {
        choice = getch(); // Obt�m a tecla pressionada

        if (choice == 0) {
            choice = getch();

            if (choice == 59) { // F1
                system("cls");
                char cnpjInstituicao[50]; // Aumente o tamanho para acomodar nome e sobrenome

                mensagemConsultarVisitas();

                printf("Digite o CNPJ da institui��o: ");
                scanf(" %[^\n]", cnpjInstituicao); // Use %[^\n] para ler toda a linha, incluindo espa�os

                consultarVisitasPorCNPJ(cnpjInstituicao);
            }

            else if (choice == 60) { // F2
                system("cls");
                printf("Retornando ao menu principal...\n");
                Sleep(2000);
                telaOpcoesInicial();
            }

            else {
                system("cls");
                confirmarOperacao();
                printf("Desculpe, mas essa tecla nao corresponde as opcoes, pressione:\n");
                printf("F1 - Prosseguir com o agendamento;\n");
                printf("F2 - Retornar ao menu global.\n");
            }
        }
    }
}

int consultarVisitasPorCNPJ(const char *cnpjInstituicaoProcurado) {
    FILE *arquivo = fopen("visitas.csv", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    char linha[256];

    printf("Estes foram todos os resultados para o CPF: \"%s\":\n\n", cnpjInstituicaoProcurado);

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        char *nomeSalvo = strtok(linha, ",");
        char *dataVisita = strtok(NULL, ",");
        char *cnpjSalvo = strtok(NULL, ",");
        char *responsavelSalvo = strtok(NULL, ",");
        char *telefoneSalvo = strtok(NULL, ",");

        if (nomeSalvo != NULL && cnpjSalvo != NULL) {
            // Use a fun��o strstr para verificar se o nomeSalvo cont�m o cnpjInstituicaoProcurado
            if (strstr(cnpjSalvo, cnpjInstituicaoProcurado) != NULL) {
                printf("Raz�o social: %s\n", nomeSalvo);
                printf("Data da visita: %s\n", dataVisita);
                printf("CPF: %s\n", cnpjSalvo);
                printf("Responsavel: %s\n", responsavelSalvo);
                printf("Telefone: %s\n", telefoneSalvo);
            }
        }
    }

    fclose(arquivo);

    printf("\n\n========================================================================================================================");
    printf("========================================================================================================================");
    printf("FIM DA LISTA :(\n");
    printf("Pressione F2 para retornar ao menu inicial.");

    int choice;

    while (1) {
        choice = getch(); // Obt�m a tecla pressionada

        if (choice == 0) {
            choice = getch();

            if (choice == 60) {
                system("cls");
                telaOpcoesInicial();
            } else {
                printf("\n\nDesculpe, op��o inv�lida.\n");
                printf("Pressione F2 para retornar ao menu inicial.");
            }
        }
    }
}

void alterarDataVisita() {
    int mensagemAlterar() {
        printf("========================================================================================================================");
        printf("========================================================================================================================");
        printf("\n\n\t\t\t\t\t\tALTERAR DATA DE VISITA\n");
        printf("\t\t\t\t\tSEJA BEM-VINDO AO MENU DE ALTERAR DATA!\n\n");
        printf("========================================================================================================================");
        printf("========================================================================================================================\n\n");
    }

    confirmarOperacao();
    while (1) {
        choice = getch(); // Obt�m a tecla pressionada

        if (choice == 0) {
            choice = getch();

            if (choice == 59) { // F1
                system("cls");
                FILE *arquivo = fopen("visitas.csv", "r");
                if (arquivo == NULL) {
                    printf("Erro ao abrir o arquivo.\n");
                    return;
                }

                char linha[256];
                char cnpjInstituicao[15];
                char novaData[20];
                int instituicaoEncontrada = 0;

                mensagemAlterar();

                printf("Digite o CNPJ da Institui��o para alterar a data da visita: ");
                scanf(" %[^\n]", cnpjInstituicao);

                // Crie um arquivo tempor�rio para armazenar as altera��es
                FILE *tempArquivo = fopen("tempFile.csv", "w");
                if (tempArquivo == NULL) {
                    printf("Erro ao criar arquivo tempor�rio.\n");
                    fclose(arquivo);
                    return;
                }

                int alteracaoRealizada = 0;

                while (fgets(linha, sizeof(linha), arquivo) != NULL) {
                    char nomeInstituicaoSalvo[50];
                    char dataVisitaSalva[20];
                    char cnpjSalvo[15];
                    char responsavelSalvo[100];
                    char telefoneSalvo[50];

                    if (sscanf(linha, "%49[^,],%19[^,],%14[^,],%99[^,],%49[^,]", nomeInstituicaoSalvo, dataVisitaSalva, cnpjSalvo, responsavelSalvo, telefoneSalvo) == 5) {
                        char cnpjSalvoSemEspacos[15];
                        limparEspacos(cnpjSalvo, cnpjSalvoSemEspacos);

                        // Compara��o direta do CNPJ
                        if (strcmp(cnpjSalvoSemEspacos, cnpjInstituicao) == 0) {
                            instituicaoEncontrada = 1;
                            printf("Estes foram todos os resultados para o CNPJ: \"%s\":\n\n", cnpjInstituicao);
                            printf("Nome: %s\n", nomeInstituicaoSalvo);
                            printf("Data de Visita: %s\n", dataVisitaSalva);
                            printf("CNPJ: %s\n", cnpjSalvo);
                            printf("Responsavel: %s\n", responsavelSalvo);
                            printf("Telefone: %s\n\n", telefoneSalvo);
                        }
                    }
                }

                if (!instituicaoEncontrada) {
                    printf("Institui��o n�o encontrada. Nenhuma altera��o realizada.\n");
                    fclose(arquivo);
                    fclose(tempArquivo);
                    return;
                }

                printf("Digite a nova data da visita (dd/mm/aaaa): ");
                scanf(" %s", novaData);

                novaData[strcspn(novaData, "\n")] = '\0'; // Remover o caractere de nova linha

                // Volte ao in�cio do arquivo para realizar a c�pia
                fseek(arquivo, 0, SEEK_SET);

                // Copia as linhas para o arquivo tempor�rio com as altera��es necess�rias
                while (fgets(linha, sizeof(linha), arquivo) != NULL) {
                    char nomeInstituicaoSalvo[50];
                    char dataVisita[20];
                    char cnpjSalvo[15];
                    char responsavelSalvo[100];
                    char telefoneSalvo[50];

                    if (sscanf(linha, "%49[^,],%19[^,],%14[^,],%99[^,],%49[^,]", nomeInstituicaoSalvo, dataVisita, cnpjSalvo, responsavelSalvo, telefoneSalvo) == 5) {
                        char cnpjSalvoSemEspacos[15];
                        limparEspacos(cnpjSalvo, cnpjSalvoSemEspacos);

                        if (strcmp(cnpjSalvoSemEspacos, cnpjInstituicao) == 0) {
                            // Se o CNPJ for encontrado, altera a data
                            fprintf(tempArquivo, "%s,%s,%s,%s,%s\n", nomeInstituicaoSalvo, novaData, cnpjSalvo, responsavelSalvo, telefoneSalvo);
                            alteracaoRealizada = 1;
                        } else {
                            // Se n�o for o CNPJ procurado, mant�m a linha inalterada
                            fprintf(tempArquivo, "%s,%s,%s,%s,%s\n", nomeInstituicaoSalvo, dataVisita, cnpjSalvo, responsavelSalvo, telefoneSalvo);
                        }
                    }
                }

                fclose(arquivo);
                fclose(tempArquivo);

                // Remove o arquivo original e renomeia o tempor�rio
                remove("visitas.csv");
                rename("tempFile.csv", "visitas.csv");

                if (alteracaoRealizada) {
                    printf("Data da visita alterada com sucesso.\n");
                    printf("Pressione F2 para retornar ao menu inicial.");
                } else {
                    printf("\nN�o foi poss�vel realizar altera��es.");
                    Sleep(2000);
                    system("cls");
                    alterarDataVisita();
                }
            } else if (choice == 60) { // F2
                system("cls");
                printf("Retornando ao menu principal...\n");
                Sleep(2000);
                telaOpcoesInicial();
            } else {
                system("cls");
                confirmarOperacao();
                printf("Desculpe, mas essa tecla n�o corresponde �s op��es, pressione:\n");
                printf("F1 - Prosseguir com o agendamento;\n");
                printf("F2 - Retornar ao menu global.\n");
            }
        }
    }
}

int excluirVisita() {
    int mensagemExcluirTicket() {
        printf("========================================================================================================================");
        printf("========================================================================================================================");
        printf("\n\n\t\t\t\t\t\tEXCLUS�O DE UMA VISITA\n");
        printf("\t\t\t\t\tSEJA BEM-VINDO AO MENU DE EXCLUS�O DE VISITAS\n\n");
        printf("========================================================================================================================");
        printf("========================================================================================================================\n\n");
    }

    confirmarOperacao();

    while (1) {
        choice = getch(); // Obt�m a tecla pressionada

        if (choice == 0) {
            choice = getch();

            if (choice == 59) { // F1
                system("cls");
                char cnpjInstituicao[50]; // Aumente o tamanho para acomodar nome e sobrenome

                mensagemExcluirTicket();

                printf("Digite o CNPJ da Institui��o para excluir: ");
                scanf(" %[^\n]", cnpjInstituicao); // Use %[^\n] para ler toda a linha, incluindo espa�os
                excluirLinhaVisita(cnpjInstituicao);
            }

            else if(choice == 60) {
                system("cls");
                printf("Retornando ao menu principal...\n");
                Sleep(2000);
                telaOpcoesInicial();
            }
            else {
                system("cls");
                confirmarOperacao();
                printf("Desculpe, mas essa tecla nao corresponde as opcoes, pressione:\n");
                printf("F1 - Prosseguir com o agendamento;\n");
                printf("F2 - Retornar ao menu global.\n");
            }
        }
    }
}

void excluirLinhaVisita(const char *cnpjInstituicaoExcluir) {
    FILE *arquivo = fopen("visitas.csv", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    FILE *tempArquivo = fopen("temp.csv", "w");
    if (tempArquivo == NULL) {
        printf("Erro ao criar arquivo tempor�rio.\n");
        fclose(arquivo);
        return;
    }

    char linha[256];
    int linhaEncontrada = 0;

    // Pergunta de confirma��o
    char confirmacao;

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        // Copia a linha original para manter os dados intactos
        char linhaTemp[256];
        strcpy(linhaTemp, linha);

        // Usa a fun��o strtok para separar os dados
        char *dados[5]; // Assumindo que h� no m�ximo 10 campos por linha
        int i = 0;
        char *token = strtok(linhaTemp, ",");
        while (token != NULL && i < 5) {
            dados[i++] = token;
            token = strtok(NULL, ",");
        }

        // Verifica se o ID do Ticket corresponde ao fornecido
        if (i >= 3 && strcmp(dados[2], cnpjInstituicaoExcluir) == 0) {
            linhaEncontrada = 1;

            // Exibe os dados da linha antes de exclu�-la
            printf("Estes s�o os dados da Instituicao com CNPJ %s:\n\n", cnpjInstituicaoExcluir);
            printf("Raz�o Social: %s\n", dados[0]);
            printf("Data da visita: %s\n", dados[1]);
            printf("CNPJ Institui��o: %s\n", dados[2]);
            printf("Respons�vel: %s\n", dados[3]);
            printf("Telefone: %s\n", dados[4]);

            printf("Deseja realmente excluir este Ticket? (S/N): ");
            scanf(" %c", &confirmacao);

            if (confirmacao == 'S' || confirmacao == 's') {
                // N�o copia a linha para o arquivo tempor�rio, efetivamente excluindo-a
            } else {
                // Mant�m as outras linhas no arquivo tempor�rio
                fprintf(tempArquivo, "%s", linha);
            }
        } else {
            // Mant�m as outras linhas no arquivo tempor�rio
            fprintf(tempArquivo, "%s", linha);
        }
    }

    fclose(arquivo);
    fclose(tempArquivo);

    if (linhaEncontrada) {
        // Remove o arquivo original e renomeia o tempor�rio
        remove("visitas.csv");
        rename("temp.csv", "visitas.csv");

        if (confirmacao == 'S' || confirmacao == 's') {
            printf("Linha exclu�da com sucesso.\n");
        }
        else {
            printf("Exclus�o cancelada.");
        }
        printf("\nPressione F2 para retornar ao menu inicial.");
        int choice;

        while (1) {
            choice = getch(); // Obt�m a tecla pressionada

            if (choice == 0) {
                choice = getch();

                if (choice == 60) {
                    system("cls");
                    printf("Retornando ao menu principal...");
                    Sleep(2000);
                    system("cls");
                    telaOpcoesInicial();
                } else {
                    printf("\n\nDesculpe, op��o inv�lida.\n");
                    printf("Pressione F2 para retornar ao menu inicial.");
                }
            }
        }

    } else {
        printf("ID do Ticket n�o encontrado. Nenhuma altera��o realizada.\n");
        remove("temp.csv"); // Remove o arquivo tempor�rio, pois n�o � necess�rio neste caso
    }
}

int estornarTicket() {
    int mensagemConsultarTicket() {
        printf("========================================================================================================================");
        printf("========================================================================================================================");
        printf("\n\n\t\t\t\t\t\tCONSULTA DE UM TICKET\n");
        printf("\t\t\t\t\tSEJA BEM-VINDO AO MENU DE CONSULTA DE TICKETS\n\n");
        printf("========================================================================================================================");
        printf("========================================================================================================================\n\n");
    }

    confirmarOperacao();

    while (1) {
        choice = getch(); // Obt�m a tecla pressionada

        if (choice == 0) {
            choice = getch();

            if (choice == 59) { // F1
                system("cls");
                char idTicket[50]; // Aumente o tamanho para acomodar nome e sobrenome

                mensagemConsultarTicket();

                printf("Digite o ID do Ticket para estorno: ");
                scanf(" %[^\n]", idTicket); // Use %[^\n] para ler toda a linha, incluindo espa�os
                consultarDadosPorIDTicket(idTicket);
            }
            else if(choice == 60) {
                system("cls");
                printf("Retornando ao menu principal...\n");
                Sleep(2000);
                telaOpcoesInicial();
            }
            else {
                system("cls");
                confirmarOperacao();
                printf("Desculpe, mas essa tecla nao corresponde as opcoes, pressione:\n");
                printf("F1 - Prosseguir com o agendamento;\n");
                printf("F2 - Retornar ao menu global.\n");
            }
        }
    }
}

void consultarDadosPorIDTicket(const char *idTicketProcurado) {
    FILE *arquivo = fopen("dados.csv", "r+");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    char linha[256];
    long posicaoInicial = -1;

    printf("Estes foram todos os resultados para o ID do Ticket: \"%s\":\n\n", idTicketProcurado);

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        char *nomeSalvo = strtok(linha, ",");
        char *dataNasc = strtok(NULL, ",");
        char *cpfSalvo = strtok(NULL, ",");
        char *celular = strtok(NULL, ",");
        char *carteiraEstudante = strtok(NULL, ",");
        char *valorTicket = strtok(NULL, ",");
        char *idTicket = strtok(NULL, ",");
        char *idTransacao = strtok(NULL, ",");
        char *dataCompra = strtok(NULL, ",");
        char *statusTicket = strtok(NULL, ",");

        if(strcmp(statusTicket, "E") == 0) {
            if (idTicket != NULL && strcmp(idTicket, idTicketProcurado) == 0) {
                // Ticket encontrado, exibe os dados
                printf("Nome: %s\n", nomeSalvo);
                printf("Data de Nascimento: %s\n", dataNasc);
                printf("CPF: %s\n", cpfSalvo);
                // Deixando o valor do celular inexistente para N/A quando impresso
                if (strcmp(celular, "000000000000") == 0) {
                    printf("Celular: N/A\n");
                }
                else {
                    printf("Celular: %s\n", celular);
                }

                // Deixando o valor da carteira de estudante inexistente para N/A quando impresso
                if (strcmp(carteiraEstudante, "000000000000") == 0) {
                    printf("Carteira de Estudante: N/A\n");
                }
                else {
                    printf("Carteira de Estudante: %s\n", carteiraEstudante);
                }
                printf("Valor do Ticket: R$%s,00\n", valorTicket);
                printf("ID do Ticket: %s\n", idTicket);
                printf("ID da Transa��o: %s\n", idTransacao);
                if (dataCompra != NULL) {
                    printf("Data da compra: %s\n", dataCompra);
                }
                if (statusTicket != NULL) {
                    printf("Status Ticket: %s\n", statusTicket);

                    printf("Para prosseguir com o estorno, aperta F1\n");
                    printf("Se n�o gostaria de prosseguir com o estorno, pressione F2\n\n");

                    int choice;
                    while (1) {
                        choice = getch(); // Obt�m a tecla pressionada

                        if (choice == 0) {
                            choice = getch();

                            if (choice == 59) { // F1
                                // Estornar o ticket
                                posicaoInicial = ftell(arquivo) - strlen(statusTicket) - 1;
                                fseek(arquivo, posicaoInicial, SEEK_SET);
                                fprintf(arquivo, "E");
                                printf("Ticket estornado com sucesso!\n");
                                break; // Sai do loop ap�s estornar o ticket
                            } else if (choice == 60) {
                                system("cls");
                                printf("Retornando ao menu principal...");
                                Sleep(2000);
                                system("cls");
                                telaOpcoesInicial();
                            } else {
                                printf("\nOp��o inv�lida. Pressione F1 para confirmar o estorno.\n");
                            }
                        }
                    }
                }
            // N�o � necess�rio continuar a busca ap�s encontrar o ticket
            break;
            }
        }
    }

    fclose(arquivo);
    printf("\n\n========================================================================================================================");
    printf("========================================================================================================================");
    printf("FIM DA LISTA :(\n");
    printf("Pressione F2 para retornar ao menu inicial.");
    int choice;

    while (1) {
        choice = getch(); // Obt�m a tecla pressionada

        if (choice == 0) {
            choice = getch();

            if (choice == 60) {
                system("cls");
                printf("Retornando ao menu principal...");
                Sleep(2000);
                system("cls");
                telaOpcoesInicial();
            } else {
                printf("\n\nDesculpe, op��o inv�lida.\n");
                printf("Pressione F2 para retornar ao menu inicial.");
            }
        }
    }
}

int excluirTicket() {
    int mensagemExcluirTicket() {
        printf("========================================================================================================================");
        printf("========================================================================================================================");
        printf("\n\n\t\t\t\t\t\tEXCLUS�O DE UM TICKET\n");
        printf("\t\t\t\t\tSEJA BEM-VINDO AO MENU DE EXCLUS�O DE TICKETS\n\n");
        printf("========================================================================================================================");
        printf("========================================================================================================================\n\n");
    }

    confirmarOperacao();

    while (1) {
        choice = getch(); // Obt�m a tecla pressionada

        if (choice == 0) {
            choice = getch();

            if (choice == 59) { // F1
                system("cls");
                char idTicket[50]; // Aumente o tamanho para acomodar nome e sobrenome

                mensagemExcluirTicket();

                printf("Digite o ID do Ticket para excluir: ");
                scanf(" %[^\n]", idTicket); // Use %[^\n] para ler toda a linha, incluindo espa�os
                excluirLinhaEExibirDados(idTicket);

            }

            else if(choice == 60) {
                system("cls");
                printf("Retornando ao menu principal...\n");
                Sleep(2000);
                telaOpcoesInicial();
            }
            else {
                system("cls");
                confirmarOperacao();
                printf("Desculpe, mas essa tecla nao corresponde as opcoes, pressione:\n");
                printf("F1 - Prosseguir com o agendamento;\n");
                printf("F2 - Retornar ao menu global.\n");
            }
        }
    }
}

void excluirLinhaEExibirDados(const char *idTicketExcluir) {
    FILE *arquivo = fopen("dados.csv", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    FILE *tempArquivo = fopen("temp.csv", "w");
    if (tempArquivo == NULL) {
        printf("Erro ao criar arquivo tempor�rio.\n");
        fclose(arquivo);
        return;
    }

    char linha[256];
    int linhaEncontrada = 0;

    // Pergunta de confirma��o
    char confirmacao;

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        // Copia a linha original para manter os dados intactos
        char linhaTemp[256];
        strcpy(linhaTemp, linha);

        // Usa a fun��o strtok para separar os dados
        char *dados[10]; // Assumindo que h� no m�ximo 10 campos por linha
        int i = 0;
        char *token = strtok(linhaTemp, ",");
        while (token != NULL && i < 10) {
            dados[i++] = token;
            token = strtok(NULL, ",");
        }

        // Verifica se o ID do Ticket corresponde ao fornecido
        if (i >= 7 && strcmp(dados[6], idTicketExcluir) == 0) {
            linhaEncontrada = 1;

            // Exibe os dados da linha antes de exclu�-la
            printf("Estes s�o os dados do Ticket com ID %s:\n\n", idTicketExcluir);
            printf("Nome: %s\n", dados[0]);
            printf("Data de Nascimento: %s\n", dados[1]);
            printf("CPF: %s\n", dados[2]);
            // Deixando o valor do celular inexistente para N/A quando impresso
            if (strcmp(dados[3], "000000000000") == 0) {
                printf("Celular: N/A\n");
            }
            else {
                printf("Celular: %s\n", dados[3]);
            }

            // Deixando o valor da carteira de estudante inexistente para N/A quando impresso
            if (strcmp(dados[4], "000000000000") == 0) {
                printf("Carteira de Estudante: N/A\n");
            }
            else {
                printf("Carteira de Estudante: %s\n", dados[4]);
            }
            printf("Valor do Ticket: R$%s,00\n", dados[5]);
            printf("ID do Ticket: %s\n", dados[6]);
            printf("ID da Transa��o: %s\n", dados[7]);
            if (dados[8] != NULL) {
                printf("Data da compra: %s\n", dados[8]);
            }
            if (dados[9] != NULL) {
                printf("Status Ticket: %s\n", dados[9]);
            }
            printf("Deseja realmente excluir este Ticket? (S/N): ");
            scanf(" %c", &confirmacao);

            if (confirmacao == 'S' || confirmacao == 's') {
                // N�o copia a linha para o arquivo tempor�rio, efetivamente excluindo-a
            } else {
                // Mant�m as outras linhas no arquivo tempor�rio
                fprintf(tempArquivo, "%s", linha);
            }
        } else {
            // Mant�m as outras linhas no arquivo tempor�rio
            fprintf(tempArquivo, "%s", linha);
        }
    }

    fclose(arquivo);
    fclose(tempArquivo);

    if (linhaEncontrada) {
        // Remove o arquivo original e renomeia o tempor�rio
        remove("dados.csv");
        rename("temp.csv", "dados.csv");

        if (confirmacao == 'S' || confirmacao == 's') {
            printf("Linha exclu�da com sucesso.\n");
        }
        else {
            printf("Exclus�o cancelada.");
        }
        printf("\nPressione F2 para retornar ao menu inicial.");
        int choice;

        while (1) {
            choice = getch(); // Obt�m a tecla pressionada

            if (choice == 0) {
                choice = getch();

                if (choice == 60) {
                    system("cls");
                    printf("Retornando ao menu principal...");
                    Sleep(2000);
                    system("cls");
                    telaOpcoesInicial();
                } else {
                    printf("\n\nDesculpe, op��o inv�lida.\n");
                    printf("Pressione F2 para retornar ao menu inicial.");
                }
            }
        }

    } else {
        printf("ID do Ticket n�o encontrado. Nenhuma altera��o realizada.\n");
        remove("temp.csv"); // Remove o arquivo tempor�rio, pois n�o � necess�rio neste caso
    }
}

int main() {
    setlocale(LC_ALL, "Portuguese");
    telaLogin();

    return 0;
}
