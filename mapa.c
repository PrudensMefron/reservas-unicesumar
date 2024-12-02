#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <wchar.h>

/***** ÁREA DOS PROTÓTIPOS *****/
void imprimir_menu(void);
int interagir_menu(wchar_t *info_menu[], int info_menu_index);
int inserir_reserva();
int listar_reserva();
int deletar_reserva();
int listar_por_dia();

/***** ESTRUTURA PARA RESERVAS *****/

typedef struct {
    wchar_t nome[100];
    wchar_t cpf[15];
    int diaReserva;
    int numeroPessoas;
} Reserva;

/* Define o máximo de reservas permitadas como 100 */
#define MAX_RESERVAS 100
Reserva reservas[MAX_RESERVAS];
int totalReservas = 0;


/* Array de variáveis para armazenar o nome dos dias da semana */
wchar_t *diasSemana[4] = {L"Quinta-feira", L"Sexta-feira", L"Sábado", L"Domingo"};

/***** FIM DAS ESTRUTURAS *****/


 /***** FUNÇÃO PRINCIPAL *****/
int main(void) {
    /* Definindo o locale para o padrão do usuário*/
    setlocale(LC_ALL, "");

    /* Declarando variáveis auxiliares paraa navegação no menu*/
    int opcao_menu = 0;
    wchar_t *info_menu[2] = {L"Escolha uma opcao: ", L"Opção inválida\nPor favor, digite o NÚMERO da opção desejada: "};
    int info_menu_index = 0;

    /* Loop principal do programa */
    do {
        /* Chama o menu principal, e tem uma variável auxiliar para navegação avisando para escolher um número */
        /* quanto o usuário insere um número inválido ou um caracter não numérico */
        opcao_menu = interagir_menu(info_menu, info_menu_index);

        /* Switch para navegação no menu principal */
        /* cada case é uma das funções principais do programa */
        switch (opcao_menu) {
            case 1:
                system("cls");
                inserir_reserva();
                info_menu_index = 0;
                break;
            case 2:
                system("cls");
                listar_reserva();
                info_menu_index = 0;
                break;
            case 3:
                system("cls");
                deletar_reserva();
                info_menu_index = 0;
                break;
            case 4:
                system("cls");
                listar_por_dia();
                info_menu_index = 0;
                break;
            case 5:
                /* Encerra o programa */
                system("cls");
                wprintf(L"\nO programa está sendo encerrado agora!\n\n");
                system("pause");
                info_menu_index = 0;
                break;
            default:
                /* Aqui é uma função interessante para alterar a variável auxiliar */
                /* de navegação para que o usuário saiba que digitou um número errado */
                /* ou que digitou um caracter não numérico, enquanto ainda vê o menu */
                info_menu_index = 1;
                break;
        }
    }

    /* Aqui a condição de encerramento do loop principal */
    while (opcao_menu != 5);


    return 0;
}

/***** ÁREA DAS FUNÇÕES *****/

/* Função de impressão do menu principal */
void imprimir_menu(void) {

    /* Aqui um detalhe interessante e apenas cosmético */
    /* uma alteração para imprimir corretamente a barra de divisão */
    /* do menu de acordo com a quantidade de reservas atuais */

    wprintf(L"============================================\n");
    wprintf(L"|              MENU PRINCIPAL              |\n");
    wprintf(L"============================================\n");
    if (totalReservas > 0) {
            wprintf(L"| Reservas atuais: %d                       |\n", totalReservas);
    } else if (totalReservas > 9)
    {
            wprintf(L"| Reservas atuais: %d                      |\n", totalReservas);
    }
    wprintf(L"| 1 - Fazer reserva                        |\n");
    wprintf(L"| 2 - Listar reservas                      |\n");
    wprintf(L"| 3 - Cancelar reserva                     |\n");	
    wprintf(L"| 4 - Reservas por dia                     |\n");
    wprintf(L"| 5 - Sair                                 |\n");
    wprintf(L"============================================\n");
}

/* Função de navegação no menu principal */
int interagir_menu(wchar_t *info_menu[], int info_menu_index) {
    system("cls");

    /* Chamada para impressão do menu */
    imprimir_menu();
    setlocale(LC_ALL, "");
    int opcao_menu;

    /* Variável de navegação no menu */
    wprintf(L"%ls", info_menu[info_menu_index]);

    /* Leitura da opção escolhida pelo usuário */
    scanf("%d", &opcao_menu);
    fflush(stdin);

    /* Retorna a escolha para a variável de navegação*/
    return opcao_menu;
}

/* Função para inserir uma reserva */
int inserir_reserva() {
    /* Verifica se o total de reservas está dentro do máximo permitido */
    if (totalReservas < MAX_RESERVAS) {
        /* Cria uma nova reserva */
        Reserva novaReserva;
        wprintf(L"Digite o nome da reserva: ");
        wscanf(L"%ls", &novaReserva.nome);
        system("cls");
        wprintf(L"Digite o CPF da reserva (ATENÇÃO: APENAS NÚMEROS): ");
        wscanf(L"%ls", &novaReserva.cpf);
        system("cls");        
        wprintf(L"As reservas estão disponíveis para os seguintes dias:\n1 - Quinta-Feira\n2 - Sexta-Feira\n3 - Sábado\n4 - Domingo\n\nDigite o número relativo ao dia da semana desejado para a reserva: ");
        scanf("%d", &novaReserva.diaReserva);
        system("cls");
        wprintf(L"Digite o número de pessoas nesta reserva: ");
        scanf("%d", &novaReserva.numeroPessoas);
        system("cls");
        /* Aqui o total de reservas é incrementado e a nova reserva adicionada ao array */
        reservas[totalReservas] = novaReserva;
        totalReservas++;
        wprintf(L"Reserva adicionada com sucesso!\n\n");
    } else {
        wprintf(L"Capacidade máxima de reservas atingida!\n\n");
    }
    system("pause");
    system("cls");
    return 0;
}

/* Função para listar reservas */
int listar_reserva() {
    system("cls");
    /* Variáveis auxiliares */
    int listarTudo = 0;
    int reservaRestante = 0;
    /* Verifica se o total de reservas é maior que 0*/
    if (totalReservas > 0) {
        /* Sub-menu para escolher o tipo de visualização: */
        /* Listar todas as reservas de uma vez, ou uma a uma */
        wprintf(L"Listar todas as reservas, ou uma a uma?\n1 - Listar uma a uma;\n2 - Listar todas;\n\nDigite o número da visualização que você deseja: ");
        scanf("%d", &listarTudo);
        system("cls");
        /* Loop para contagem da quantidade de reservas */
        for (int i = 0; i < totalReservas; i++) {
            switch (listarTudo)
            {
            case 1:
            /* Imprime as reservas uma a uma */
            wprintf(L"Número de reservas total: %d\n\n", totalReservas);
            wprintf(L"Reserva N° %d\n", i+1);
            wprintf(L"Nome: %ls\n", reservas[i].nome);
            wprintf(L"CPF: %ls\n", reservas[i].cpf);
            wprintf(L"Dia: %d, %ls\n", reservas[i].diaReserva, diasSemana[reservas[i].diaReserva-1]);
            wprintf(L"Número de pessoas: %d\n", reservas[i].numeroPessoas);
            wprintf(L"===============================\n\n");
            /* Aqui mostra quantas reservas ainda restam */
            /* durante as exibições uma a uma */
            reservaRestante = totalReservas-i;
            wprintf(L"\nNúmero de reservas restante: %d\n\n", reservaRestante-1);
            system("pause");
            system("cls");
                break;
            
            case 2:
            /* Aqui mostram todas as reservas de uma vez **/
            wprintf(L"Reserva N° %d\n", i+1);
            wprintf(L"Nome: %ls\n", reservas[i].nome);
            wprintf(L"CPF: %ls\n", reservas[i].cpf);
            wprintf(L"Dia: %d, %ls\n", reservas[i].diaReserva, diasSemana[reservas[i].diaReserva-1]);
            wprintf(L"Número de pessoas: %d\n", reservas[i].numeroPessoas);
            wprintf(L"===============================\n\n");
                break;
            default:
            /* Caso o usuário digite uma opção inválida */
                wprintf(L"Opção inválida!\n\n");
                wprintf(L"Retornando ao menu principal.\n\n");
                system("pause");
                break;
            }
        }
        if (listarTudo  == 2) {
            /* Caso o usuário digite 2, ele volta ao menu principal */
            /* Após a listagem de todas as reservas */
            wprintf(L"Retornando ao menu principal.\n\n");
            system("pause");
        }
    } else {
        /* Caso nenhuma reserva seja cadastrada */
        /* essa mensagem aparece na tela */
        wprintf(L"Nenhuma reserva cadastrada!\n\n");
        system("pause");
    }
    return 0;
}

/* Função para cancelar uma reserva */
int deletar_reserva() {
    int opcaoCancelamento = 0;
    system("cls");
    /* Sub-menu para escolher o tipo de cancelamento: */
    wprintf(L"Você deseja apagar uma reserva?\n\n1 - Apagar reserva pelo NOME da reserva;\n2 - Apagar reserva pelo CPF da reserva;\n3 - Voltar ao menu principal;\n\nDigite o número da opção desejada: ");
    scanf("%d", &opcaoCancelamento);
    system("cls");
    switch (opcaoCancelamento) {
        /* Caso o usuário digite 1, ele apaga uma reserva pelo nome */
        case 1:
            wprintf(L"Digite o nome da reserva que deseja apagar: ");
            /* Leitura do nome da reserva */
            wchar_t nome[100];
            wscanf(L"%ls", &nome);
            /* Loop para procurar a reserva pelo nome */
            for (int i = 0; i < totalReservas; i++) {
                if (wcscmp(reservas[i].nome, nome) == 0) {
                    int confirmacao = 0;
                    /* Confirmação da exclusão da reserva */
                    wprintf(L"Tem certeza que deseja apagar a reserva em nome de %ls?\n1 - Sim;\n2 - Não;\n\nDigite o número da opção desejada: ", nome);
                    scanf("%d", &confirmacao);
                    system("cls");
                    /* Switch para confirmação da exclusão */
                    switch (confirmacao)
                    {
                    case 1:
                        for (int j = i; j < totalReservas; j++) {
                            reservas[j] = reservas[j+1];
                        }
                        totalReservas--;
                        wprintf(L"Reserva apagada com sucesso!\n\n");
                        system("pause");
                        break;
                    case 2:
                        wprintf(L"Reserva foi mantida. Retornando ao menu principal.\n\n");
                        system("pause");
                        break;
                    default:
                        /* Caso não seja encontrada a reserva pelo nome */
                        wprintf(L"Reserva não encontrada!\n\nRetornando ao menu principal.\n\n");
                        system("pause");
                        break;
                    }
                }
            }
            break;
        case 2:
            /* Caso o usuário digite 2, ele apaga uma reserva pelo CPF */
            wprintf(L"Digite o CPF da reserva que deseja apagar: ");
            /* leitura do CPF da reserva*/
            wchar_t cpf[15];
            wscanf(L"%ls", &cpf);
            /* Loop para procurar a reserva pelo CPF */
            for (int i = 0; i < totalReservas; i++) {
                if (wcscmp(reservas[i].cpf, cpf) == 0) {
                    /* Confirmação da exclusão da reserva */
                    int confirmacao = 0;
                    /* Essa confirmação apresenta o nome da pessoa, fazendo a busca pelo CPF*/
                    wprintf(L"Tem certeza que deseja apagar a reserva em nome de %ls?\n1 - Sim;\n2 - Não;\n\nDigite o número da opção desejada: ", reservas[i].nome);
                    scanf("%d", &confirmacao);
                    system("cls");
                    /* Switch para confirmação da exclusão */
                    switch (confirmacao)
                    {
                    case 1:
                        for (int j = i; j < totalReservas; j++) {
                            reservas[j] = reservas[j+1];
                        }
                        totalReservas--;
                        wprintf(L"Reserva apagada com sucesso!\n\n");
                        system("pause");
                        break;
                    case 2:
                        wprintf(L"Reserva foi mantida. Retornando ao menu principal.\n\n");
                        system("pause");
                        break;
                    default:
                        /* Caso não seja encontrada a reserva pelo CPF */
                        wprintf(L"Reserva não encontrada!\n\nRetornando ao menu principal.\n\n");
                        system("pause");
                        break;
                    }
                }
            }
            break;
    }
}

/* Função para listar as reservas por dia */
int listar_por_dia() {
    system("cls");
    /* Variáveis auxiliares */
    int diaListagem = 0;
    int reservasNoDia = 0;
    int pessoasNaReserva = 0;
    int index = 0;
    /* Varivável auxiliar para imprimir o plural corretamente */
    wchar_t *plural[2] = {L"pessoa", L"pessoas"};
    /* Sub-menu para selecionar o dia para listar as reservas */
    wprintf(L"Para verificar as reservas marcadas por dia, primeiro selecione o dia:\n\n1 - Quinta-Feira;\n2 - Sexta-Feira;\n3 - Sábado;\n4 - Domingo;\n\nDigite o número da opção desejada: ");
    scanf("%d", &diaListagem);
    /* Switch para escolher o dia */
    switch (diaListagem)
    {
    case 1: /* Listagem para Quinta-Feira */
        for (int i = 0; i < totalReservas; i++) {
        /* Loop para contar quantas reservas foram marcadas no dia */
            if (reservas[i].diaReserva == 1) {
                /* Adiciona +1 a contagem de reservas no dia, e a quantidade de pessoas na reserva*/
                reservasNoDia++;
                pessoasNaReserva += reservas[i].numeroPessoas;
            }
        }
        system("cls");
            /* Index usado para imprimir o plural corretamente */
            if (pessoasNaReserva >= 1) {
                index = 1;
            }
        switch (reservasNoDia) {
            case 1: /* Caso haja UMA reserva marcada no dia */
                wprintf(L"Um total de %d reserva marcada na %ls para %d %ls!\n\n", reservasNoDia, diasSemana[diaListagem-1], pessoasNaReserva, plural[index]);
                system("pause");
                break;
            case 0: /* Caso não haja reserva marcadas no dia */
                wprintf(L"Nenhuma reserva marcada na %ls!\n\n", diasSemana[diaListagem-1]);
                system("pause");
                break;
            default: /* Caso haja mais de uma reserva marcada no dia */
                wprintf(L"Um total de %d reservas marcadas na %ls para %d %ls!\n\n", reservasNoDia, diasSemana[diaListagem-1], pessoasNaReserva, plural[index]);
                system("pause");
                break;
        }
        break;

    /* Aqui repetem-se os padrões de código do case 1 até o case 4 */
    case 2:
        for (int i = 0; i < totalReservas; i++) {
            if (reservas[i].diaReserva == 2) {
                reservasNoDia++;
                pessoasNaReserva += reservas[i].numeroPessoas;
            }
        }
        system("cls");
        if (pessoasNaReserva >= 1) {
            index = 1;
        }
        switch (reservasNoDia) {
            case 1:
                wprintf(L"Um total de %d reserva marcada na %ls para %d %ls!\n\n", reservasNoDia, diasSemana[diaListagem-1], pessoasNaReserva, plural[index]);
                system("pause");
                break;
            case 0:
                wprintf(L"Nenhuma reserva marcada na %ls!\n\n", diasSemana[diaListagem-1]);
                system("pause");
                break;
            default:
                wprintf(L"Um total de %d reservas marcadas na %ls para %d %ls!\n\n", reservasNoDia, diasSemana[diaListagem-1], pessoasNaReserva, plural[index]);
                system("pause");
                break;
        }
        break;
    case 3:
        for (int i = 0; i < totalReservas; i++) {
            if (reservas[i].diaReserva == 3) {
                reservasNoDia++;
                pessoasNaReserva += reservas[i].numeroPessoas;
            }
        }
        system("cls");
        if (pessoasNaReserva >= 1) {
            index = 1;
        }
        switch (reservasNoDia) {
            case 1:
                wprintf(L"Um total de %d reserva marcada no %ls para %d %ls!\n\n", reservasNoDia, diasSemana[diaListagem-1], pessoasNaReserva, plural[index]);
                system("pause");
                break;
            case 0:
                wprintf(L"Nenhuma reserva marcada no %ls!\n\n", diasSemana[diaListagem-1]);
                system("pause");
                break;
            default:
                wprintf(L"Um total de %d reservas marcadas no %ls para %d %ls!\n\n", reservasNoDia, diasSemana[diaListagem-1], pessoasNaReserva, plural[index]);
                system("pause");
                break;
        }
        break;
    case 4:
        for (int i = 0; i < totalReservas; i++) {
            if (reservas[i].diaReserva == 4) {
                reservasNoDia++;
                pessoasNaReserva += reservas[i].numeroPessoas;
            }
        }
        system("cls");
        if (pessoasNaReserva >= 1) {
            index = 1;
        }
        switch (reservasNoDia) {
            case 1:
                wprintf(L"Um total de %d reserva marcada na %ls para %d %ls!\n\n", reservasNoDia, diasSemana[diaListagem-1], pessoasNaReserva, plural[index]);
                system("pause");
                break;
            case 0:
                wprintf(L"Nenhuma reserva marcada na %ls!\n\n", diasSemana[diaListagem-1]);
                system("pause");
                break;
            default:
                wprintf(L"Um total de %d reservas marcadas na %ls para %d %ls!\n\n", reservasNoDia, diasSemana[diaListagem-1], pessoasNaReserva, plural[index]);
                system("pause");
                break;
        }
        break;
    default: /* Aqui avisa caso o usuário tenha inserido uma opção inválida */
        wprintf(L"Opção inválida!\n\nRetornando ao menu principal.\n\n");
        system("pause");
        break;
    }
}

/***** FIM DAS FUNÇÕES *****/