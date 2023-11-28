#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <locale.h>
#include <time.h>

char username[20], password[20];
int authenticated = 0; // Variável para verificar se o usuário está autenticado
int choice; // Variável para realizar scanf de escolhas
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
    char nomeInstituicao[50];
    char data[20];
    char cnpj[20];
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
    printf("\n\n\t\t\t\t\t\tCONFIRMAR OPERAÇÃO\n");
    printf("\t\t\t\t\tPRESSIONE UMA DAS OPÇÕES ABAIXO PARA CONTINUAR!\n\n");
    printf("========================================================================================================================");
    printf("========================================================================================================================\n\n");
    printf("Para prosseguir com a operação, aperta F1\n");
    printf("Se não gostaria de prosseguir com a operação, pressione F2\n\n");
}

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
                printf("6 - Estorno de ticket\n");
                printf("7 - Excluir ticket\n");
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
        system("cls");
        estornarTicket();
        break;
    case 7:
        system("cls");
        excluirTicket();
        break;
    default:
        system("cls");
        printf("Opção não reconhecida, tente novamente...\n");
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
        choice = getch(); // Obtém a tecla pressionada

        if (choice == 0) {
            choice = getch();

            if (choice == 59) { // F1
                system("cls");
                char cpf[50]; // Aumente o tamanho para acomodar nome e sobrenome

                mensagemConsultarTicket();

                printf("Digite o CPF do visitante: ");
                scanf(" %[^\n]", cpf); // Use %[^\n] para ler toda a linha, incluindo espaços
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
        choice = getch(); // Obtém a tecla pressionada

        if (choice == 0) {
            choice = getch();

            if (choice == 59) { // F1
                system("cls");

                mensagemNovoTicket();

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

                else {
                    strcpy(pessoa.celular, "000000000000");
                }

                printf("Estudante (S/N): ");
                fflush(stdin);
                char pessoaEstudante;
                scanf(" %c", &pessoaEstudante);

                if(pessoaEstudante == 'S' || pessoaEstudante == 's') {
                    printf("Digite o código da carteirinha: ");
                    scanf(" %s", &pessoa.carteiraEstudante);
                }

                else {
                    strcpy(pessoa.carteiraEstudante, "000000000000");
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
                printf("Desculpe, mas essa tecla não corresponde as opções, pressione:\n");
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
        choice = getch(); // Obtém a tecla pressionada

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

                printf("Nome instituicao: ");
                fflush(stdin);  // Limpa o buffer de entrada
                fgets(visitas.nomeInstituicao, sizeof(visitas.nomeInstituicao), stdin);
                visitas.nomeInstituicao[strcspn(visitas.nomeInstituicao, "\n")] = '\0';

                printf("Data da visita (dd/mm/aaaa): ");
                fgets(visitas.data, sizeof(visitas.data), stdin);
                visitas.data[strcspn(visitas.data, "\n")] = '\0';

                printf("CNPJ da instituicao: ");
                fgets(visitas.cnpj, sizeof(visitas.cnpj), stdin);
                visitas.cnpj[strcspn(visitas.cnpj, "\n")] = '\0';

                fprintf(arquivo, "%s,%s,%s\n", visitas.nomeInstituicao, visitas.data, visitas.cnpj);
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
        choice = getch(); // Obtém a tecla pressionada

        if (choice == 0) {
            choice = getch();

            if (choice == 59) { // F1
                system("cls");
                char cnpjInstituicao[50]; // Aumente o tamanho para acomodar nome e sobrenome

                mensagemConsultarVisitas();

                printf("Digite o CNPJ da instituição: ");
                scanf(" %[^\n]", cnpjInstituicao); // Use %[^\n] para ler toda a linha, incluindo espaços

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

        if (nomeSalvo != NULL && cnpjSalvo != NULL) {
            // Use a função strstr para verificar se o nomeSalvo contém o cnpjInstituicaoProcurado
            if (strstr(cnpjSalvo, cnpjInstituicaoProcurado) != NULL) {
                printf("Nome: %s\n", nomeSalvo);
                printf("Data da visita: %s\n", dataVisita);
                printf("CPF: %s\n", cnpjSalvo);
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
        choice = getch(); // Obtém a tecla pressionada

        if (choice == 0) {
            choice = getch();

            if (choice == 60) {
                system("cls");
                telaOpcoesInicial();
            } else {
                printf("\n\nDesculpe, opção inválida.\n");
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
        choice = getch(); // Obtém a tecla pressionada

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

                printf("Digite o CNPJ da Instituição para alterar a data da visita: ");
                scanf(" %[^\n]", cnpjInstituicao);

                // Crie um arquivo temporário para armazenar as alterações
                FILE *tempArquivo = fopen("tempFile.csv", "w");
                if (tempArquivo == NULL) {
                    printf("Erro ao criar arquivo temporário.\n");
                    fclose(arquivo);
                    return;
                }

                int alteracaoRealizada = 0;

                while (fgets(linha, sizeof(linha), arquivo) != NULL) {
                    char nomeInstituicaoSalvo[50];
                    char dataVisitaSalva[20];
                    char cnpjSalvo[15];

                    if (sscanf(linha, "%49[^,],%19[^,],%14[^,]", nomeInstituicaoSalvo, dataVisitaSalva, cnpjSalvo) == 3) {
                        char cnpjSalvoSemEspacos[15];
                        limparEspacos(cnpjSalvo, cnpjSalvoSemEspacos);

                        // Comparação direta do CNPJ
                        if (strcmp(cnpjSalvoSemEspacos, cnpjInstituicao) == 0) {
                            instituicaoEncontrada = 1;
                            printf("Estes foram todos os resultados para o CNPJ: \"%s\":\n\n", cnpjInstituicao);
                            printf("Nome: %s\n", nomeInstituicaoSalvo);
                            printf("Data de Visita: %s\n", dataVisitaSalva);
                            printf("CNPJ: %s\n\n", cnpjSalvo);
                        }
                    }
                }

                if (!instituicaoEncontrada) {
                    printf("Instituição não encontrada. Nenhuma alteração realizada.\n");
                    fclose(arquivo);
                    fclose(tempArquivo);
                    return;
                }

                printf("Digite a nova data da visita (dd/mm/aaaa): ");
                scanf(" %s", novaData);

                novaData[strcspn(novaData, "\n")] = '\0'; // Remover o caractere de nova linha

                // Volte ao início do arquivo para realizar a cópia
                fseek(arquivo, 0, SEEK_SET);

                // Copia as linhas para o arquivo temporário com as alterações necessárias
                while (fgets(linha, sizeof(linha), arquivo) != NULL) {
                    char cnpjSalvo[15];
                    char nomeInstituicaoSalvo[50];
                    char dataVisita[20];

                    if (sscanf(linha, "%49[^,],%19[^,],%14[^,]", nomeInstituicaoSalvo, dataVisita, cnpjSalvo) == 3) {
                        char cnpjSalvoSemEspacos[15];
                        limparEspacos(cnpjSalvo, cnpjSalvoSemEspacos);

                        if (strcmp(cnpjSalvoSemEspacos, cnpjInstituicao) == 0) {
                            // Se o CNPJ for encontrado, altera a data
                            fprintf(tempArquivo, "%s,%s,%s\n", nomeInstituicaoSalvo, novaData, cnpjSalvo);
                            alteracaoRealizada = 1;
                        } else {
                            // Se não for o CNPJ procurado, mantém a linha inalterada
                            fprintf(tempArquivo, "%s,%s,%s\n", nomeInstituicaoSalvo, dataVisita, cnpjSalvo);
                        }
                    }
                }

                fclose(arquivo);
                fclose(tempArquivo);

                // Remove o arquivo original e renomeia o temporário
                remove("visitas.csv");
                rename("tempFile.csv", "visitas.csv");

                if (alteracaoRealizada) {
                    printf("Data da visita alterada com sucesso.\n");
                } else {
                    printf("Nenhuma alteração realizada.\n");
                }
            } else if (choice == 60) { // F2
                system("cls");
                printf("Retornando ao menu principal...\n");
                Sleep(2000);
                telaOpcoesInicial();
            } else {
                system("cls");
                confirmarOperacao();
                printf("Desculpe, mas essa tecla não corresponde às opções, pressione:\n");
                printf("F1 - Prosseguir com o agendamento;\n");
                printf("F2 - Retornar ao menu global.\n");
            }
        }
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
        choice = getch(); // Obtém a tecla pressionada

        if (choice == 0) {
            choice = getch();

            if (choice == 59) { // F1
                system("cls");
                char idTicket[50]; // Aumente o tamanho para acomodar nome e sobrenome

                mensagemConsultarTicket();

                printf("Digite o ID do Ticket para estorno: ");
                scanf(" %[^\n]", idTicket); // Use %[^\n] para ler toda a linha, incluindo espaços
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
            printf("ID da Transação: %s\n", idTransacao);
            if (dataCompra != NULL) {
                printf("Data da compra: %s\n", dataCompra);
            }
            if (statusTicket != NULL) {
                printf("Status Ticket: %s\n", statusTicket);

                printf("Para prosseguir com o estorno, aperta F1\n");
                printf("Se não gostaria de prosseguir com o estorno, pressione F2\n\n");

                int choice;
                while (1) {
                    choice = getch(); // Obtém a tecla pressionada

                    if (choice == 0) {
                        choice = getch();

                        if (choice == 59) { // F1
                            // Estornar o ticket
                            posicaoInicial = ftell(arquivo) - strlen(statusTicket) - 1;
                            fseek(arquivo, posicaoInicial, SEEK_SET);
                            fprintf(arquivo, "E");
                            printf("Ticket estornado com sucesso!\n");
                            break; // Sai do loop após estornar o ticket
                        } else if (choice == 60) {
                            system("cls");
                            printf("Retornando ao menu principal...");
                            Sleep(2000);
                            system("cls");
                            telaOpcoesInicial();
                        } else {
                            printf("\nOpção inválida. Pressione F1 para confirmar o estorno.\n");
                        }
                    }
                }
            }
            // Não é necessário continuar a busca após encontrar o ticket
            break;
        }
    }

    fclose(arquivo);
    printf("\n\n========================================================================================================================");
    printf("========================================================================================================================");
    printf("FIM DA LISTA :(\n");
    printf("Pressione F2 para retornar ao menu inicial.");
    int choice;

    while (1) {
        choice = getch(); // Obtém a tecla pressionada

        if (choice == 0) {
            choice = getch();

            if (choice == 60) {
                system("cls");
                printf("Retornando ao menu principal...");
                Sleep(2000);
                system("cls");
                telaOpcoesInicial();
            } else {
                printf("\n\nDesculpe, opção inválida.\n");
                printf("Pressione F2 para retornar ao menu inicial.");
            }
        }
    }
}

int excluirTicket() {
    int mensagemExcluirTicket() {
        printf("========================================================================================================================");
        printf("========================================================================================================================");
        printf("\n\n\t\t\t\t\t\tEXCLUSÃO DE UM TICKET\n");
        printf("\t\t\t\t\tSEJA BEM-VINDO AO MENU DE EXCLUSÃO DE TICKETS\n\n");
        printf("========================================================================================================================");
        printf("========================================================================================================================\n\n");
    }

    confirmarOperacao();

    while (1) {
        choice = getch(); // Obtém a tecla pressionada

        if (choice == 0) {
            choice = getch();

            if (choice == 59) { // F1
                system("cls");
                char idTicket[50]; // Aumente o tamanho para acomodar nome e sobrenome

                mensagemExcluirTicket();

                printf("Digite o ID do Ticket para excluir: ");
                scanf(" %[^\n]", idTicket); // Use %[^\n] para ler toda a linha, incluindo espaços
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
        printf("Erro ao criar arquivo temporário.\n");
        fclose(arquivo);
        return;
    }

    char linha[256];
    int linhaEncontrada = 0;

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        // Copia a linha original para manter os dados intactos
        char linhaTemp[256];
        strcpy(linhaTemp, linha);

        // Usa a função strtok para separar os dados
        char *dados[10]; // Assumindo que há no máximo 10 campos por linha
        int i = 0;
        char *token = strtok(linhaTemp, ",");
        while (token != NULL && i < 10) {
            dados[i++] = token;
            token = strtok(NULL, ",");
        }

        // Verifica se o ID do Ticket corresponde ao fornecido
        if (i >= 7 && strcmp(dados[6], idTicketExcluir) == 0) {
            linhaEncontrada = 1;

            // Exibe os dados da linha antes de excluí-la
            printf("Estes são os dados do Ticket com ID %s:\n\n", idTicketExcluir);
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
            printf("ID da Transação: %s\n", dados[7]);
            if (dados[8] != NULL) {
                printf("Data da compra: %s\n", dados[8]);
            }
            if (dados[9] != NULL) {
                printf("Status Ticket: %s\n", dados[9]);
            }

            // Pergunta de confirmação
            char confirmacao;
            printf("Deseja realmente excluir este Ticket? (S/N): ");
            scanf(" %c", &confirmacao);

            if (confirmacao == 'S' || confirmacao == 's') {
                // Não copia a linha para o arquivo temporário, efetivamente excluindo-a
            } else {
                // Mantém as outras linhas no arquivo temporário
                fprintf(tempArquivo, "%s", linha);
            }
        } else {
            // Mantém as outras linhas no arquivo temporário
            fprintf(tempArquivo, "%s", linha);
        }
    }

    fclose(arquivo);
    fclose(tempArquivo);

    if (linhaEncontrada) {
        // Remove o arquivo original e renomeia o temporário
        remove("dados.csv");
        rename("temp.csv", "dados.csv");

        printf("Linha excluída com sucesso.\n");
        printf("\nPressione F2 para retornar ao menu inicial.");
        int choice;

        while (1) {
            choice = getch(); // Obtém a tecla pressionada

            if (choice == 0) {
                choice = getch();

                if (choice == 60) {
                    system("cls");
                    printf("Retornando ao menu principal...");
                    Sleep(2000);
                    system("cls");
                    telaOpcoesInicial();
                } else {
                    printf("\n\nDesculpe, opção inválida.\n");
                    printf("Pressione F2 para retornar ao menu inicial.");
                }
            }
        }

    } else {
        printf("ID do Ticket não encontrado. Nenhuma alteração realizada.\n");
        remove("temp.csv"); // Remove o arquivo temporário, pois não é necessário neste caso
    }
}

int main() {
    setlocale(LC_ALL, "Portuguese");
    telaLogin();

    return 0;
}
