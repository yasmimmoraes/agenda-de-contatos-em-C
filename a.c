#include <windows.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

bool isRunning = true;
void Menu();
void AdicionarNovoContato(); 
void MostrarTodosOsContatos();
void ProcurarContato();
void EditarContato();
void ExcluirContato();
void DigitarLinhaComEspaco(char *Nome[20],char InfoContato);
void MostrarNumeroComEspaco(char *Telefone[20]);
void MostrarIdComEspaco(char *Id[30]);
void ErroReiniciar(char *erro[100]);
bool JaExiste(char *DadaLinha[30],char InfoContato); 
void SairOuVoltar();
void Sair(); 

int main(){ 
    int i;
    printf("\t\t");
    char Iniciando[100] = "Iniciando....";
    for(i=0;i<strlen(Iniciando);i++){
        printf("%c",Iniciando[i]);
        Sleep(40);
    }
    system("cls");


    while(isRunning == true){
        Menu();
        char *str[100];
        char option;
        scanf("%s",&str);
        option = str[0];
        switch(option){
            case '0':
                Sair();
                break;
            case '1':
                AdicionarNovoContato();
                break;
            case '4':
                MostrarTodosOsContatos();
                break;
            case '5':
                ProcurarContato();
                break;
            case '3':
                EditarContato();
                break;
            case '2':
                ExcluirContato();
                break;
            default:
                ErroReiniciar("Opcao nao encontrada!");
                break;
        }
    }

    return 0;
}

void Menu(){
    printf("\n\t --- Agenda de Contatos ---\n");
    printf("\n\t\t\tMenu Inicial\n");
    printf("\t\t=====================\n");
    printf("\t\t[1] Incluir um novo contato\n"); // 1
    printf("\t\t[2] Excluir um contato existente\n"); // 2
    printf("\t\t[3] Alterar um contato existente\n"); // 3
    printf("\t\t[4] Listar todos os contatos cadastrados\n"); // 4
    printf("\t\t[5] Localizar um contato\n"); // 5
    printf("\t\t[0] Sair\n\t\t=================\n\t\t");
    printf("Escolha uma opcao: ");
}

void AdicionarNovoContato(){
    system("cls");
    printf("\n\t\t **** Adicionar novo contato ****\n\n");
    char Nome[20];
    char Telefone[20];
    char Id[30];
    char NovoContato[100];
    NovoContato[0] = 0;
    printf("*Deve ter no maximo 20 caracteres.\n");
    printf("Insira o nome: ");
    scanf(" %[^\n]s",Nome);
    if(strlen(Nome) > 20){
        ErroReiniciar("!!!!Erro, o nome deve ter no maximo 20 caracteres!!!");
        return;
    }
    if(JaExiste(Nome,'n') == 1){
        ErroReiniciar("!!!!Erro, o nome ja existe!!!");
        return;
    }
    printf("\n*O numero deve ter no maximo 20 caracteres..\n");
    printf("Digite o numero de telefone: ");
    scanf("%s",Telefone);
    if(strlen(Telefone) > 20){
        ErroReiniciar("!!!!Erro, numero de caracteres ultrapassado!!!!");
        return;
    }
    if(JaExiste(Telefone,'p') == 1){
        ErroReiniciar("!!!!Erro, numero ja existe!!!");
        return;
    }
    printf("\n*Identificador deve ser unico e ter no maximo 30 caracteres..\n");
    printf("Digite o identificador: ");
    scanf("%s",Id);
    if(strlen(Id) > 30){
        ErroReiniciar("!!!!Erro, numero de caracteres ultrapassado!!!!");
        return;
    }
    if(JaExiste(Id,'e') == 1){
        ErroReiniciar("!!!!Erro, identificador ja existe!!!");
        return;
    }
    strcat(NovoContato,Nome);
    strcat(NovoContato,"\n");
    strcat(NovoContato,Telefone);
    strcat(NovoContato,"\n");
    strcat(NovoContato,Id);
    strcat(NovoContato,"\n");

    FILE *allContactTxtFile = fopen("All-Contact.txt","a"); 
    fprintf(allContactTxtFile,NovoContato); 
    fclose(allContactTxtFile); 
    printf("\nContato adicionado!\n");
    SairOuVoltar();
}

void MostrarTodosOsContatos(){
    system("cls");
    printf("\n\t\t **** Todos os contatos ****\n\n");
    FILE* AllContactTextFile;
    int TamanhoLinha = 300;
    char Linha[TamanhoLinha];

    printf("|====================|====================|==============================|\n");
    printf("|        Nome        |    Telefone        |          Identificador       |\n");
    printf("|====================|====================|==============================|\n");

    AllContactTextFile = fopen("All-Contact.txt", "r");
    int ContatoTotal = 0;
    int ContadorDeLinhas = 0;
    while(fgets(Linha, TamanhoLinha, AllContactTextFile)) {
        ContadorDeLinhas++;
        if(ContadorDeLinhas==1){
            // nome
            DigitarLinhaComEspaco(Linha,'n');
        }else if(ContadorDeLinhas == 2){
            // Telefone
           DigitarLinhaComEspaco(Linha,'p');
        }else if(ContadorDeLinhas == 3){
            // Id
            DigitarLinhaComEspaco(Linha,'e');
            ContadorDeLinhas=0;
            ContatoTotal++;
        }
    }
    printf("Voce tem um total de %d Contatos.\n\n",ContatoTotal);
    fclose(AllContactTextFile);
    SairOuVoltar();
}

void DigitarLinhaComEspaco(char *Nome[20],char InfoContato){
    int i;
    char *NomeFormatado = NULL;
    NomeFormatado = strdup(Nome);
    int NomeFormatadoTamanho = strlen(NomeFormatado);

    int TotalSpace = 0;
    if(InfoContato == 'n'){
        TotalSpace = 20 - NomeFormatadoTamanho; // nome
    }else if(InfoContato == 'p'){
        TotalSpace = 20 - NomeFormatadoTamanho; // Telefone
    }else if(InfoContato == 'e'){
        TotalSpace = 30 - NomeFormatadoTamanho; // Id
    }

    printf("|");
    for(i=0;i<NomeFormatadoTamanho-1;i++){
        printf("%c",NomeFormatado[i]);
    }

    for(i=0;i<=TotalSpace;i++){
        printf(" ");
    }

    if(InfoContato == 'e'){
        printf("|\n");
        printf("|--------------------|--------------------|------------------------------|\n");
    }
}

void ProcurarContato(){
    system("cls");
    printf("\n\t\t **** Localizar um contato ****\n\n");

    int ContatoEncontrado = 0;
    char Nome[100];
    printf("*O nome deve ter no maximo 20 caracteres.\n");
    printf("Digite o nome do contato: ");
    scanf(" %[^\n]s",Nome);
    if(strlen(Nome) > 20){
        ErroReiniciar("!!!Erro, numero de caracteres ultrapassado!!!");
        return;
    }
    strcat(Nome,"\n");

    FILE* TodasLinhasContato;
    int TamanhoLinha = 255;
    char Linha[TamanhoLinha];
    TodasLinhasContato = fopen("All-Contact.txt", "r");
    int ContadorDeLinhas = 0;
    int PrintLinha = 0;
    while(fgets(Linha, TamanhoLinha, TodasLinhasContato)) {
       ContadorDeLinhas++;
        if(ContadorDeLinhas == 1 && strcmp(Nome, Linha) == 0){
            ContatoEncontrado = 1;
            PrintLinha = 3;
        }
        if(PrintLinha > 0){
            if(ContadorDeLinhas==1){
                printf("\nInformacoes de %s",Nome);
                printf("\nNome: %s",Linha);
                PrintLinha = 2;
            }else if(ContadorDeLinhas == 2){
                printf("Telefone: %s",Linha);
                PrintLinha = 1;
            }else if(ContadorDeLinhas == 3){
                printf("Identificador: %s\n",Linha);
                PrintLinha = 0;
            }
        }
        if(ContadorDeLinhas == 3){
            ContadorDeLinhas=0;
        }
    }
    fclose(TodasLinhasContato);
    if(ContatoEncontrado == 0){
        printf("\nDesculpa contato nao encontrado %s\n",Nome);
    }
    SairOuVoltar();
}

void EditarContato(){
    system("cls");
    printf("\n\t\t **** Editar Contato  ****\n\n");

    int ContadorDeLinhas = 0;
    int ContatoEncontrado = 0;
    int PularLinhas = 0;
    char DadoONome[100];
    char NovoNome[100];
    char NovoTelefone[20];
    char NovoId[100];
    char NovoContatoDif[300];
    NovoContatoDif[0] = 0;
    printf("*O numero de caracteres nao deve ultrapassar 20.\n");
    printf("Digite o nome de qual contato devera ser editado: ");
    scanf(" %[^\n]s",DadoONome);
    if(strlen(DadoONome) > 20){
        ErroReiniciar("!!!Erro, numero de caracteres ultrapassado!!!");
        return;
    }

    strcat(DadoONome,"\n");

    FILE* OurExistingFile;
    FILE* NewTempFile;
    int TamanhoLinha = 255;
    char Linha[TamanhoLinha];
    OurExistingFile = fopen("All-Contact.txt", "r");
    NewTempFile = fopen("temp-file.txt", "w");
    while(fgets(Linha, TamanhoLinha, OurExistingFile)) {
        ContadorDeLinhas++;

        if(ContadorDeLinhas == 1 && strcmp(DadoONome, Linha) == 0){
            ContatoEncontrado = 1;
            PularLinhas = 3;
        }

        if(PularLinhas > 0){
            if(ContadorDeLinhas == 1){
                printf("\n*O novo nome deve ter no maximo 20 caracteres.\n");
                printf("O nome antigo era: %s",Linha);
                printf("Novo nome(digite 0 para pular): ");
                scanf(" %[^\n]s",NovoNome);
                if(strcmp(NovoNome, "0") == 0){
                    strcat(NovoContatoDif,Linha);
                }else{
                    if(strlen(NovoNome) > 20){
                        ErroReiniciar("!!!!Erro, numero de caracteres ultrapassado!!!");
                        return;
                    }
                    if(JaExiste(NovoNome,'n') == 1){
                        ErroReiniciar("!!!!Erro, nome ja existe!!!");
                        return;
                    }
                    strcat(NovoContatoDif,NovoNome);
                    strcat(NovoContatoDif,"\n");
                }
                PularLinhas = 2;
            }else if(ContadorDeLinhas == 2){
                printf("\n*O novo telefone deve ter no maximo 20 caracteres..\n");
                printf("O telefone antigo era: %s",Linha);
                printf("Novo telefone(digite 0 para pular): ");
                scanf("%s",NovoTelefone);
                if(strcmp(NovoTelefone, "0") == 0){
                    strcat(NovoContatoDif,Linha);
                }else{
                    if(strlen(NovoTelefone) > 20){
                        ErroReiniciar("!!!!Erro, numero de caracteres ultrapassado!!!");
                        return;
                    }
                    if(JaExiste(NovoTelefone,'p') == 1){
                        ErroReiniciar("!!!!Erro, numero ja existe!!!");
                        return;
                    }
                    strcat(NovoContatoDif,NovoTelefone);
                    strcat(NovoContatoDif,"\n");
                }
                PularLinhas = 1;
            }else if(ContadorDeLinhas == 3){
                printf("\n*O novo identificador deve ter no maximo 20 caracteres..\n");
                printf("O identificador era: %s",Linha);
                printf("Novo identificador(digite 0 para pular): ");
                scanf("%s",NovoId);

                if(strcmp(NovoId, "0") == 0){
                    strcat(NovoContatoDif,Linha);
                }else{
                    if(strlen(NovoId) > 30){
                        ErroReiniciar("!!!Erro, numero de caracteres ultrapassado!!!!");
                        return;
                    }
                    if(JaExiste(NovoId,'e') == 1){
                        ErroReiniciar("!!!Erro, identificador ja existe!!!");
                        return;
                    }
                    strcat(NovoContatoDif,NovoId);
                    strcat(NovoContatoDif,"\n");
                }
                PularLinhas = 0;
                fprintf(NewTempFile,NovoContatoDif);
            }
        }else{
            fprintf(NewTempFile,Linha);
        }

        if(ContadorDeLinhas == 3){
            ContadorDeLinhas = 0;
        }
    }
    fclose(NewTempFile);
    fclose(OurExistingFile);

    if(ContatoEncontrado == 0){
        printf("Contato nao encontrado!\n");
        remove("temp-file.txt");
    }else{
        printf("\nContato atualizado com sucesso!\n\n");
        remove("All-Contact.txt");
        rename("temp-file.txt", "All-Contact.txt");
    }
    SairOuVoltar();
}

void ExcluirContato(){

    system("cls");
    printf("\n\t\t **** Deletar contato ****\n\n");

    int ContadorDeLinhas = 0;
    int EncontrarOContato = 0;
    int PularLinhas = 0;
    char DadoONome[100];
    printf("\n*O nome nao deve ultrapassar 20 caracteres.\n");
    printf("Digite o nome de qual contato quer deletar:  ");
    scanf(" %[^\n]s",DadoONome);
    if(strlen(DadoONome) > 20){
        ErroReiniciar("!!!!Erro, numero de caracteres ultrapassado!!!");
    }
    strcat(DadoONome,"\n");

    FILE* OurExistingFile;
    FILE* NewTempFile;
    int TamanhoLinha = 300;
    char Linha[TamanhoLinha];
    OurExistingFile = fopen("All-Contact.txt", "r");
    NewTempFile = fopen("temp-file.txt", "w");
    while(fgets(Linha, TamanhoLinha, OurExistingFile)) {
        ContadorDeLinhas++;

        if(ContadorDeLinhas == 1 && strcmp(DadoONome, Linha) == 0){
            EncontrarOContato = 1;
            PularLinhas = 3;
        }

        if(PularLinhas > 0){
            PularLinhas--;
        }else{
            fprintf(NewTempFile,Linha);
        }

        if(ContadorDeLinhas == 3){
            ContadorDeLinhas = 0;
        }
    }
    fclose(NewTempFile);
    fclose(OurExistingFile);

    if(EncontrarOContato == 0){
        printf("\nContato nao encontrado!\n\n");
        remove("temp-file.txt");
    }else{
        printf("\nContato atualizado com sucesso!\n\n");
        remove("All-Contact.txt");
        rename("temp-file.txt", "All-Contact.txt");
    }
    SairOuVoltar();
}

bool JaExiste(char *DadaLinha[30],char InfoContato){
    char *EssaLinha[35];
    EssaLinha[0] = 0;
    strcat(EssaLinha,DadaLinha);
    strcat(EssaLinha,"\n");
    int ArquivoLinhaNumero = 0;
    if(InfoContato == 'n'){
        ArquivoLinhaNumero = 1; // Nome
    }else if(InfoContato == 'p'){
        ArquivoLinhaNumero = 2; // Telefone
    }else if(InfoContato == 'e'){
        ArquivoLinhaNumero = 3; // Id
    }


    FILE* TodasLinhasContato;
    int TamanhoLinha = 300;
    char Linha[TamanhoLinha];
    TodasLinhasContato = fopen("All-Contact.txt", "r");
    int ContadorDeLinhas = 0;
    int ContatoTotal = 0;
    int Encontrado = 0;
    while(fgets(Linha, TamanhoLinha, TodasLinhasContato)) {
       ContadorDeLinhas++;
        if(ContadorDeLinhas == ArquivoLinhaNumero && strcmp(EssaLinha, Linha) == 0){
            Encontrado = 1;
        }
        if(ContadorDeLinhas == 3){
            ContadorDeLinhas = 0;
        }
    }
    fclose(TodasLinhasContato);
    if(Encontrado == 1){
        return true;
    }else{
        return false;
    }
}

void ErroReiniciar(char *erro[100]){
    printf("%s\n",erro);
    int i = 0;
    printf("Reiniciando o programa: ");
    for(i=0;i<10;i++){
        printf(".");
        Sleep(500);
    }
    system("cls");
    main();
}

void SairOuVoltar(){
    char option;
    getchar();
    printf("Voltar(v)? ou sair(0)?");
    scanf("%c",&option);
    if(option=='0'){
        Sair();
    }else{
        system("cls");
    }
}

void Sair(){ //sair 
    getchar();
    printf("Tem certeza que deseja sair? (S,N): ");
    char SimOuNao;
    scanf("%c",&SimOuNao);
    if(SimOuNao == 'S' || SimOuNao == 's'){
        system("cls");

        char Obrigado[100] = "=====Obrigado por utilizar o programa!!!=====\n";
        char FeitoPor[100] = "=====Feito por Isabelle Keiser e Yasmim Moraes=====\n";
        int i=0;
        for(i=0;i<strlen(Obrigado);i++){
            printf("%c",Obrigado[i]);
            Sleep(40);
        }
        for(i=0;i<strlen(FeitoPor);i++){
            printf("%c",FeitoPor[i]);
            Sleep(40);
        }
        isRunning =  false;
    }
}