#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>


#define TAMANHO 100


struct aluno {
    char nome[30];
    char curso[30];
    int ano_de_nascimento;
    int matricula;
};


int ano_atual() {
    char year[4];
    setenv("TZ", "/usr/share/zoneinfo/America/Belem", 1); // especifico de POSIX
    // Ex: Tue Mar  3 14:54:12 2020
    struct tm tm = *localtime(&(time_t){time(NULL)});

    int i;
    for (i=0; i<4; i++) {
        year[i] = asctime(&tm)[20 + i];
    }

    // atoi transforma string em int
    return atoi(year);
}




int main(void) {
    int choice;
    int alunos_cadastrados = 0;
    int matricula;
    char curso[30];
    int i;
    struct aluno *aluno;
    struct aluno lista[TAMANHO];

    printf(".--------- Escolha uma Opcao ---------.\n");
    printf("| [1] Inserir aluno                   |\n");
    printf("| [2] Buscar por matricula            |\n");
    printf("| [3] Maiores de 18                   |\n");
    printf("| [4] Listar por curso                |\n");
    printf("'-------------------------------------'\n\n");

    while (true) {

        printf("\nSua escolha: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                aluno = malloc(sizeof(struct aluno));

                printf("Insira o nome: ");
                scanf("%s", aluno->nome);
                printf("Insira o curso: ");
                scanf("%s", aluno->curso);
                printf("Insira a matricula: ");
                scanf("%d", &aluno->matricula);
                printf("Insira a ano de nascimento: ");
                scanf("%d", &aluno->ano_de_nascimento);

                lista[alunos_cadastrados] = *aluno;
                free(aluno);
                alunos_cadastrados++;
                break;
            case 2:
                printf("Insira o numero da matricula: ");
                scanf("%d", &matricula);

                for (i=0; i<TAMANHO; i++) {
                    aluno = &lista[i];
                    if (aluno->matricula == matricula)
                        printf("Aluno encontrado: %s\n", aluno->nome);
                }
                break;
            case 3:
                for (i=0; i<alunos_cadastrados; i++) {
                    aluno = &lista[i];
                    if (ano_atual() - aluno->ano_de_nascimento >= 18)
                        printf("%s\n", aluno->nome);
                }
                break;
            case 4:
                printf("Insira o nome do curso: ");
                scanf("%s", &curso);

                for (i=0; i<TAMANHO; i++) {
                    aluno = &lista[i];
                    if (*aluno->curso == *curso)
                        printf("%s\n", aluno->nome);
                }
                break;
        }
    }

    return 0;
}
