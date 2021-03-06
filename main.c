#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>

#define DEFAULT_PAUSE 1
#define MILLISECOND 1000

struct process {
    int processPriority;
    int processSize;
    int completedUnits;
    float completedPerCent;
    int entryCounter;
    char processDescription[100];
    struct process *previousProcess;
    struct process *nextProcess;
};

typedef struct process *processPointer;

processPointer createProcess(char description[100]);
void presentation();
void menu(processPointer *processList);
void processCreationFunctionality(processPointer *processList);
void addProcess(processPointer *processList, processPointer newProcess);

int main() {

    processPointer processList = NULL;

    presentation();
    menu(&processList);

    return 0;
}

processPointer createProcess(char description[100]) {

    processPointer newProcess = (processPointer) malloc(sizeof(struct process));

    newProcess->processSize = rand() % 1000;
    newProcess->completedUnits = 0;
    newProcess->completedPerCent = 0;
    newProcess->entryCounter = 0;
    newProcess->previousProcess = NULL;
    newProcess->nextProcess = NULL;
    strcpy(newProcess->processDescription, description);

    return newProcess;
}


void presentation() {

    printf("----------------------------Simulador de escalonamento de processos -----------------------------\n");
    printf("---------------------------------------Seja Bem Vindo !!!----------------------------------------\n\n\n");
    system("cls");
    Sleep(DEFAULT_PAUSE * MILLISECOND);
}

void menu(processPointer *processList) {
    int menuSelectedOption = 0;

    system("cls");
    Sleep(DEFAULT_PAUSE * MILLISECOND);
    printf("----------------------------------------Menu de Opcoes----------------------------------------\n\n\n");
    printf("1 - Agendar Processos\n");
    printf("2 - Consultar Processos Agendados\n");
    printf("3 - Executar Processos Detalhadamente\n");
    printf("4 - Executar Processos Simplificadamente\n");
    printf("5 - Sair\n\n");
    printf("R: ");
    scanf("%d", &menuSelectedOption);
    printf("\n\n\n");

    switch (menuSelectedOption) {
        case 1 :
            processCreationFunctionality(processList);
            break;
        case 2:
            printf("Consulta de Processos Selecionada");
            break;
        case 3:
            printf("Execução Detalhada de Processos Selecionada");
            break;
        case 4:
            printf("Execução Simplificada de Processos Selecionada");
            break;
        case 5:
            printf("Saindo do Sistema ...");
            Sleep(DEFAULT_PAUSE * MILLISECOND);
            system("exit");
            break;
        default:
            printf("A opcao selecionada nao e valida.");
            Sleep(DEFAULT_PAUSE * MILLISECOND);
            menu(processList);
            break;
    }
}

void processCreationFunctionality(processPointer *processList){
    int processQuantity = 0;
    char processName[100];

    system("cls");

    Sleep(DEFAULT_PAUSE * MILLISECOND);

    printf("\n\nQual a quantidade de processos que voce deseja agendar ?\n\n");
    printf("R: ");
    scanf("%d", &processQuantity);

    if(processQuantity == 0){
        printf("A quantidade informada e nula, logo não serao agendados novos processos.\n\n");
        menu(processList);
    }

    while(processQuantity > 0){
        system("cls");

        printf("\n\nQual o nome do primeiro processo ?\n");
        printf("R: ");
        fgets(processName, sizeof(processName), stdin);

        processPointer p = createProcess(processName);

        addProcess(processList, p);

        printf("\n\nCriando processo ...");

        processQuantity--;
    }
}

void addProcess(processPointer *processList, processPointer newProcess) {
    processPointer aux = (*processList);

    if ((*processList) == NULL) {
        *processList = newProcess;
    } else {
        if (aux->nextProcess == NULL) {
            if (newProcess->processSize > aux->processSize) {
                newProcess->nextProcess = aux;
                aux->previousProcess = newProcess;
                (*processList) = newProcess;
            }
        } else {
            while (aux->nextProcess != NULL && aux->processSize > newProcess->processSize) {
                aux = aux->nextProcess;
            }

            newProcess->nextProcess = aux;
            newProcess->previousProcess = aux->previousProcess;
            aux->previousProcess = newProcess;
            (*processList) = newProcess;
        }
    }
}