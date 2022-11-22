#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
typedef struct{
    char usuario[21];
    char senha[11];
}login; 

typedef struct{
    char crm[7];
    char nome[51];
    char telefone[12]; 
    char especialidade[21];
    char valorHoraTrabalho[11];
    char dataDeNascimento[11]; 
} medico; 

typedef struct{
    char cpf[12];
    char nome[31];
    char telefone[12]; 
    char dataDeNascimento[11]; 
} paciente; 

typedef struct {
    char crmMedico[7];
    char cpfPaciente[12];
    char data[11];
    char sintoma[101];
    char encaminhamentos[101];
} consulta; 

login *cadastrarNovoUsuario(login *cadastro); 
int verificarLogin(login *acesso); 
int verificaCadastro(void *cadastro, char *definicao); 
medico *NovoMedico(medico *a); 
medico *buscarMedico(char *dadoRequisitado, int desejo); 
medico *alterarDadosMedico(medico *alvo); 
void listarDadosMedico(medico *a); 
paciente *NovoPaciente(paciente *p); 
paciente *buscarPaciente( char *dadoRequisitado, int desejo); 
paciente *alterarDadosPaciente(paciente *alvo); 
consulta *NovaConsulta(consulta *c);
void listarConsultas(char *definicao);
int comparadorDeStrings(char *stringQueSeQuerComparar, char *stringAserComparada);
void CPFformatado(char *cpf);
void formatadorDeStrings(char *palavra);
void formatarNumero(char *telefone);
void menuInicial();
void menuClinica();
void menuMedico();
void menuPaciente();
void menuConsultas();

int main(){
    int opcao=0,dentro=0;
    char buscador[30];
    FILE *dataBaseClinica;
    paciente *registroPaciente;
    medico *registroMedico;
    consulta *registroConsulta;
    login *registroLogin;
    login *entrada;
    for(;;){
        menuInicial();
        scanf("%d%*c",&opcao);
        switch(opcao){
            case 1: //efetuar login
                dentro = verificarLogin(entrada);
                system("cls");
                for(;;){
                    if(dentro){
                        menuClinica();
                        scanf("%d%*c",&opcao);
                        switch(opcao){
                            case 1: //pacientes
                                menuPaciente();
                                scanf("%d%*c",&opcao);
                                for(int i=0;i<1;){
                                    switch(opcao){
                                        case 1: //cadastrar novo paciente
                                            system("cls");
                                            registroPaciente = NovoPaciente(registroPaciente);
                                            free(registroPaciente);
                                            i=1;
                                            break;
                                        case 2: //buscar paciente
                                            system("cls");
                                            printf("\nDigite dado do paciente: ");
                                            scanf("%[^\n]s",buscador);
                                            fflush(stdin);
                                            registroPaciente = buscarPaciente(buscador,1);
                                            free(registroPaciente);
                                            i=1;
                                            break;
                                        case 3: //alterar dados paciente
                                            system("cls");
                                            registroPaciente = alterarDadosPaciente(registroPaciente);
                                            free(registroPaciente);
                                            i=1;
                                            break;
                                        case 0: //retorno
                                            i=1;
                                            break;
                                    }
                                }
                            break;
                            case 2: //medicos
                                menuMedico();
                                scanf("%d%*c",&opcao);
                                for(int i=0;i<1;){
                                    switch(opcao){
                                        case 1: //cadastrar novo medico
                                            system("cls");
                                            registroMedico = NovoMedico(registroMedico);
                                            free(registroMedico);
                                            i=1;
                                            break;
                                        case 2: //buscar medico
                                            system("cls");
                                            printf("\nDigite dado do medico: ");
                                            scanf("%[^\n]s",buscador);
                                            fflush(stdin);
                                            registroMedico = buscarMedico(buscador,1);
                                            free(registroMedico);
                                            i=1;
                                            break;
                                        case 3: //listar dados medico
                                            system("cls");
                                            listarDadosMedico(registroMedico);
                                            free(registroMedico);
                                            i=1;
                                            break;
                                        case 4: //alterar dados medico
                                            system("cls");
                                            registroMedico = alterarDadosMedico(registroMedico);
                                            free(registroMedico);
                                            i=1;
                                            break;
                                        case 0: //retorno
                                            i=1;
                                            break;
                                    }
                                }
                            break;
                            case 3: //consulta
                                 menuConsultas();
                                 scanf("%d%*c",&opcao);
                                 for(int i=0;i<1;){
                                        switch(opcao){
                                            case 1: //agendar consulta
                                                system("cls");
                                                registroConsulta = NovaConsulta(registroConsulta);
                                                free(registroConsulta);
                                                i=1;
                                                break;
                                            case 2: //listar consulta do medico
                                                system("cls");
                                                listarConsultas("medico");
                                                i=1;
                                                break;
                                            case 3: //listar consulta do paciente
                                                system("cls");
                                                listarConsultas("paciente");
                                                i=1;
                                                break;
                                            case 0: //retorno
                                                i=1;
                                                break;
                                        }
                                 }
                            break;
                            default: //sair do programa
                                return 0;
                        }
                    }
                    else
                        return 0;
                }

            break;
            case 2: //cadastrar login
                registroLogin = cadastrarNovoUsuario(registroLogin);
            break;
            default: //sair do programa
                return 0;
        }
    }
}

//retorna 1 se usuario encontrado // retorna 0 se não encontrado
int verificarLogin(login *acesso){
    acesso = (login*)calloc(1,sizeof(login));
    FILE *dataBaseClinica;
    login *dataRAM, varData;
    int totalDeLogins=0;
    dataBaseClinica = fopen("dados/dataBaseClinicaLogins.bin", "rb");
    if(dataBaseClinica == NULL){
        fclose(dataBaseClinica);
        dataBaseClinica = fopen("dados/dataBaseClinicaLogins.bin","w+b");
        fclose(dataBaseClinica);
        dataBaseClinica = fopen("dados/dataBaseClinicaLogins.bin", "rb");
    }
    while(fread(&varData,sizeof(login),1,dataBaseClinica))
            totalDeLogins++; //descobre quantos logins tem o arquivo binario
    dataRAM = (login*) calloc(totalDeLogins,sizeof(login)); //aloca memoria de acordo com o tamanho do arquivo
    fseek(dataBaseClinica,0,SEEK_SET);
    fread(dataRAM,sizeof(login),totalDeLogins,dataBaseClinica); //escreve no vetor dataRAM os logins do arquivo
    fclose(dataBaseClinica);
    printf("\nDigite o nome do usuario: ");
    scanf("%[^\n]s",acesso[0].usuario);
    fflush(stdin);
    printf("Digite a senha: ");
    scanf("%[^\n]s",acesso[0].senha);
    fflush(stdin);
    for(int i=0; i<totalDeLogins; i++){
        if(strcmp(acesso[0].usuario, dataRAM[i].usuario) == 0 ){ //compara nome
            if(strcmp(acesso[0].senha, dataRAM[i].senha) == 0){ //compara senha
            free(dataRAM);
                return 1;
            }else{
                for(int j=0; j<2 ; j++){
                    printf("\nsenha errada, tente novamente!\n(tentativas restantes : %d)",2-j);
                    printf("\nDigite a senha novamente: ");
                    scanf("%[^\n]s",acesso[0].senha);
                    fflush(stdin);
                    if(strcmp(acesso[0].senha, dataRAM[i].senha) == 0){
                        free(dataRAM);
                        return 1;
                    }
                }
            }
        }
    }
    printf("\nUsuario nao encontrado!");
    free(dataRAM);
    return 0;
}

//retorna 2 se for medico(e ele estiver no banco de dados) // retorna 1 se for paciente (e ele estiver no banco de dados) // retorna 0 se não achar nada // retorna 3 se for login
int verificaCadastro(void *cadastro, char *definicao){
    medico *cadastroMedico;
    paciente *cadastroPaciente;
    login*cadastroLogin;
    FILE *dataBaseClinica;
    medico *dataRAMmedicos, varDataM;
    paciente *dataRAMpacientes, varDataP;
    login *dataRAMlogins, varDataL;
    int totalDeCadastro = 0;
    if(strcmp(definicao,"medico") == 0){
        cadastroMedico = (medico*)calloc(1,sizeof(medico));
        cadastroMedico = (medico*) cadastro;
        dataBaseClinica = fopen("dados/dataBaseClinicaMedicos.bin", "rb");
        if(dataBaseClinica == NULL){
            fclose(dataBaseClinica);
            dataBaseClinica = fopen("dados/dataBaseClinicaMedicos.bin","w+b");
            fclose(dataBaseClinica);
            dataBaseClinica = fopen("dados/dataBaseClinicaMedicos.bin","rb");
        }
        while(fread(&varDataM,sizeof(medico),1,dataBaseClinica))
            totalDeCadastro++;
        dataRAMmedicos = (medico*) calloc(1,sizeof(medico));
        fseek(dataBaseClinica,0,SEEK_SET);
        for(int i=0; i<totalDeCadastro; i++){
            fread(&dataRAMmedicos[0],sizeof(medico),1,dataBaseClinica);
            if(strcmp(cadastroMedico[0].crm, dataRAMmedicos[0].crm) == 0){ //busca pelo crm já cadastrado
                free(dataRAMmedicos);
                fclose(dataBaseClinica);
                return 2; //retorna 2 se encontrar o medico
            }
        }
        free(dataRAMmedicos);
    }
    else if(strcmp(definicao,"paciente") == 0){
        cadastroPaciente = (paciente*)calloc(1,sizeof(paciente));
        cadastroPaciente = (paciente*) cadastro;
        dataBaseClinica = fopen("dados/dataBaseClinicaPacientes.bin", "rb");
        if(dataBaseClinica == NULL){
            fclose(dataBaseClinica);
            dataBaseClinica = fopen("dados/dataBaseClinicaPacientes.bin","w+b");
            fclose(dataBaseClinica);
            dataBaseClinica = fopen("dados/dataBaseClinicaPacientes.bin","rb");
        }
        while(fread(&varDataP,sizeof(paciente),1,dataBaseClinica))
            totalDeCadastro++;
        dataRAMpacientes = (paciente*) calloc(1,sizeof(paciente));
        fseek(dataBaseClinica,0,SEEK_SET);
        for(int i=0; i<totalDeCadastro; i++){
            fread(&dataRAMpacientes[0],sizeof(paciente),1,dataBaseClinica);
            if(strcmp(cadastroPaciente[0].cpf, dataRAMpacientes[0].cpf) == 0){ //busca pelo cpf já cadastrado
                free(dataRAMpacientes);
                fclose(dataBaseClinica);
                return 1; //retorna 1 se encontrar o paciente
            }
        }
        free(dataRAMpacientes);
    }
    else if(strcmp(definicao,"usuario") == 0){
        cadastroLogin = (login*)calloc(1,sizeof(login));
        cadastroLogin = (login*)cadastro;
        dataBaseClinica = fopen("dados/dataBaseClinicaLogins.bin","rb");
        if(dataBaseClinica == NULL){
            fclose(dataBaseClinica);
            dataBaseClinica = fopen("dados/dataBaseClinicaLogins.bin","w+b");
            fclose(dataBaseClinica);
            dataBaseClinica = fopen("dados/dataBaseClinicaLogins.bin","rb");
        }
        while(fread(&varDataL,sizeof(login),1,dataBaseClinica))
            totalDeCadastro ++;
        dataRAMlogins = (login*) calloc(1, sizeof(login));
        fseek(dataBaseClinica,0,SEEK_SET);
        for(int i=0; i<totalDeCadastro; i++){
            fread(&dataRAMlogins[0],sizeof(login),1,dataBaseClinica);
            if(strcmp(cadastroLogin[0].usuario,dataRAMlogins[0].usuario) == 0){
                free(dataRAMlogins);
                fclose(dataBaseClinica);
                return 3;// retorna 3 se encontrar o login
            }
        }
        free(dataRAMlogins);
    }
    fclose(dataBaseClinica);
    return 0; //retorna 0 se não achar
}

//cadastra nova secretária
login *cadastrarNovoUsuario(login *cadastro){
    cadastro = (login*)calloc(1,sizeof(login));
    FILE *dataBaseClinica;
    int inscrito = 1;
    printf("\nDigite o nome do Usuario: ");
    scanf("%[^\n]s",cadastro[0].usuario);
    fflush(stdin);
    if(verificaCadastro(cadastro,"usuario") == 0){
        dataBaseClinica = fopen("dados/dataBaseClinicaLogins.bin", "ab");
        printf("\nDigite a senha do Usuario: ");
        scanf("%[^\n]s",cadastro[0].senha);
        fflush(stdin);
        fwrite(&cadastro[0],sizeof(login),1,dataBaseClinica);
        fclose(dataBaseClinica);
    }
    return cadastro;
}

//cadastra novos pacientes
paciente *NovoPaciente(paciente *p){
    int nP;
    FILE *dataBaseClinica;
    printf ("\nQuantos pacientes voce deseja cadastrar? ");
    scanf ("%d%*c",&nP);
    p = (paciente*) calloc (nP,sizeof(paciente));
    for (int i=0;i<nP;i++){
        if(i>0)
            printf("\n\nProximo cadastro: \n\n");
        printf ("\nDigite o CPF:\n");
        while(strlen(p[i].cpf)!= 11){
            scanf ("%[^\n]s",p[i].cpf);
            fflush(stdin);
            if(strlen(p[i].cpf)!= 11)
                printf("\nCPF invalido, digite novamente: ");
        }
        if(verificaCadastro(&p[i],"paciente")==0){
            printf("\nDigite o Nome do Paciente:\n");
            scanf("%[^\n]s",p[i].nome);
            fflush(stdin);
            formatadorDeStrings(p[i].nome);

            printf("\nDigite a data de nascimento:\n");
            scanf("%[^\n]s",p[i].dataDeNascimento);
            fflush(stdin);

            printf ("\nDigite telefone de contato:\n");
            scanf("%[^\n]s",p[i].telefone);
            fflush(stdin);
        }
        else{
            printf("\nCPF ja cadastrado!!!");
            free(p);
            return NULL;
        }
    }
    dataBaseClinica = fopen("dados/dataBaseClinicaPacientes.bin", "ab");
    fwrite(p,sizeof(paciente),nP,dataBaseClinica);
    fclose(dataBaseClinica);
    free(p);
    return p;
}

//cadastra novos medicos
medico *NovoMedico(medico *a){
    int nM;
    FILE *dataBaseClinica;
    printf ("\nQuantos medicos deseja cadastrar? ");
    scanf("%d%*c",&nM);
    a = (medico*) calloc (nM,sizeof(medico));
    for(int i=0;i<nM;i++){
        if(i>0)
            printf("\n\nProximo cadastro: \n\n");
        printf ("\nDigite o CRM:\n");
        while(strlen(a[i].crm)!= 6){
            scanf ("%[^\n]s",a[i].crm);
            fflush(stdin);
            if(strlen(a[i].crm)!= 6)
                printf("\nCRM invalido!\nDigite novamente: ");
        }
        if(verificaCadastro(&a[i],"medico") == 0){
            printf("Digite o Nome do Medico:\n");
            scanf("%[^\n]s",a[i].nome);
            fflush(stdin);
            formatadorDeStrings(a[i].nome);

            printf("Digite a Especialidade:\n");
            scanf("%[^\n]s",a[i].especialidade);
            fflush(stdin);
            formatadorDeStrings(a[i].especialidade);

            printf("Digite a data de nascimento:\n");
            scanf("%[^\n]s",a[i].dataDeNascimento);
            fflush(stdin);

            printf ("Digite telefone de contato:\n");
            scanf("%[^\n]s",a[i].telefone);
            fflush(stdin);

            printf("Digite o valor a receber por consulta:\n");
            scanf("%[^\n]s",a[i].valorHoraTrabalho);
            fflush(stdin);
        }
        else{
            printf("\nCRM ja cadastrada!!!");
            free(a);
            return NULL;
        }
    }
    dataBaseClinica = fopen("dados/dataBaseClinicaMedicos.bin","ab");
    fwrite(a,sizeof(medico),nM,dataBaseClinica);
    fclose(dataBaseClinica);
    free(a);
    return a;
}

//Agenda Nova Consulta
consulta *NovaConsulta(consulta *c){
    c = (consulta*)calloc(1,sizeof(consulta));
    int r;
    FILE *dataBaseClinica;
    dataBaseClinica = fopen("dados/dataBaseClinicaConsultas.bin", "ab");
    printf("\nDigite o CRM do medico: ");
    scanf("%[^\n]s",c[0].crmMedico);
    fflush(stdin);
    if(buscarMedico(c[0].crmMedico,0)){
        printf("\nDigite o CPF do paciente: ");
        scanf("%[^\n]s",c[0].cpfPaciente);
        fflush(stdin);
        if(buscarPaciente(c[0].cpfPaciente,0)){
            printf("\nDigite a Data: ");
            scanf("%[^\n]s",c[0].data);
            fflush(stdin);

            printf("\nDigite quais sao os sintomas: ");
            scanf("%[^\n]s",c[0].sintoma);
            fflush(stdin);

            printf("\nEncaminhamento: ");
            scanf("%[^\n]s",c[0].encaminhamentos);
            fflush(stdin);
            fwrite(&c[0],sizeof(consulta),1,dataBaseClinica);
        }else{
            printf("\nPaciente nao encontrado!");
            fclose(dataBaseClinica);
            return NULL;
        }
    }else{
        printf("\nMedico nao encontrado!");
        fclose(dataBaseClinica);
        return NULL;
    }
    fclose(dataBaseClinica);
    return c;
}

//retorna array de medico com o dado buscado e printa a array // retorna NULL se nao encontrar
medico *buscarMedico(char *dadoRequisitado, int desejo){
    formatadorDeStrings(dadoRequisitado);
    medico *dataRAMmedicos, *resultadoDaBusca, varData;
    FILE *dataBaseClinica;
    int totalDeMedicos=0, totalDeMedicosAchados=0;
    dataBaseClinica = fopen("dados/dataBaseClinicaMedicos.bin", "rb");
    if(dataBaseClinica == NULL){
            fclose(dataBaseClinica);
            dataBaseClinica = fopen("dados/dataBaseClinicaMedicos.bin","w+b");
            fclose(dataBaseClinica);
            dataBaseClinica = fopen("dados/dataBaseClinicaMedicos.bin","rb");
        }
    while(fread(&varData,sizeof(medico),1,dataBaseClinica))
        totalDeMedicos++;
    dataRAMmedicos = (medico*)calloc(1,sizeof(medico));
    fseek(dataBaseClinica,0,SEEK_SET);
    for(int i=0; i<totalDeMedicos; i++){
        fread(&dataRAMmedicos[0],sizeof(medico),1,dataBaseClinica);
        if(comparadorDeStrings(dataRAMmedicos[0].crm,dadoRequisitado))
            totalDeMedicosAchados++;
        else if(comparadorDeStrings(dataRAMmedicos[0].dataDeNascimento,dadoRequisitado))
            totalDeMedicosAchados++;
        else if(comparadorDeStrings(dataRAMmedicos[0].especialidade,dadoRequisitado))
            totalDeMedicosAchados++;
        else if(comparadorDeStrings(dataRAMmedicos[0].nome,dadoRequisitado))
            totalDeMedicosAchados++;
    }
    resultadoDaBusca = (medico*) calloc(totalDeMedicosAchados,sizeof(medico));
    if(totalDeMedicosAchados == 0){
        printf("\nMedico nao encontrado!");
        free(dataRAMmedicos);
        return NULL;
    }
    fseek(dataBaseClinica,0,SEEK_SET);
    for(int i=0; fread(&dataRAMmedicos[0],sizeof(medico),1,dataBaseClinica);){
        if(comparadorDeStrings(dataRAMmedicos[0].crm,dadoRequisitado)){
            resultadoDaBusca[i] = dataRAMmedicos[0];
            i++;
        }   
        else if(comparadorDeStrings(dataRAMmedicos[0].dataDeNascimento,dadoRequisitado)){
            resultadoDaBusca[i] = dataRAMmedicos[0];
            i++;
        }
        else if(comparadorDeStrings(dataRAMmedicos[0].nome,dadoRequisitado)){
            resultadoDaBusca[i] = dataRAMmedicos[0];
            i++;
        }   
    }
    free(dataRAMmedicos);
    if(desejo==1){
        for(int i=0;i<totalDeMedicosAchados;i++){
            printf("\n\nNome: %s",resultadoDaBusca[i].nome);
            printf("\nCRM: %s",resultadoDaBusca[i].crm);
            printf("\nData de Nascimento: %s",resultadoDaBusca[i].dataDeNascimento);
            printf("\nEspecialidade: %s",resultadoDaBusca[i].especialidade);
            formatarNumero(resultadoDaBusca[i].telefone);
            printf("\nValor por consulta: R$%s",resultadoDaBusca[i].valorHoraTrabalho);
        }
    }
    return resultadoDaBusca;
}

//retorna array de pacientes com o dado buscado e printa a array // retorna NULL se nao encontrar
paciente *buscarPaciente( char *dadoRequisitado, int desejo){
    formatadorDeStrings(dadoRequisitado);
    paciente VarData;
    paciente *dataRAMpacientes, *resultadoDaBusca;
    FILE *dataBaseClinica;
    int totalDePacientes=0, totalDePacientesAchados=0;
    dataBaseClinica = fopen("dados/dataBaseClinicaPacientes.bin", "rb");
    if(dataBaseClinica == NULL){
            fclose(dataBaseClinica);
            dataBaseClinica = fopen("dados/dataBaseClinicaPacientes.bin","w+b");
            fclose(dataBaseClinica);
            dataBaseClinica = fopen("dados/dataBaseClinicaPacientes.bin","rb");
        }
    while(fread(&VarData,sizeof(paciente),1,dataBaseClinica))
        totalDePacientes++;
    dataRAMpacientes = (paciente*)calloc(1,sizeof(paciente));
    fseek(dataBaseClinica,0,SEEK_SET);
    for(int i=0; i<totalDePacientes; i++){
        fread(&dataRAMpacientes[0],sizeof(paciente),1,dataBaseClinica);
        if(comparadorDeStrings(dataRAMpacientes[0].cpf,dadoRequisitado))
            totalDePacientesAchados++;
        else if(comparadorDeStrings(dataRAMpacientes[0].dataDeNascimento,dadoRequisitado))
            totalDePacientesAchados++;
        else if(comparadorDeStrings(dataRAMpacientes[0].nome,dadoRequisitado))
            totalDePacientesAchados++;
    }
    resultadoDaBusca = (paciente*) calloc(totalDePacientesAchados,sizeof(paciente));
    if(totalDePacientesAchados == 0){
        printf("\n\nPaciente nao encontrado!");
        free(dataRAMpacientes);
        return NULL;
    }
    fseek(dataBaseClinica,0,SEEK_SET);
    for(int i=0; fread(&dataRAMpacientes[0],sizeof(paciente),1,dataBaseClinica);){
        if(comparadorDeStrings(dataRAMpacientes[0].cpf,dadoRequisitado)){
            resultadoDaBusca[i] = dataRAMpacientes[0];
            i++;
        }   
        else if(comparadorDeStrings(dataRAMpacientes[0].dataDeNascimento,dadoRequisitado)){
            resultadoDaBusca[i] = dataRAMpacientes[0];
            i++;
        }
        else if(comparadorDeStrings(dataRAMpacientes[0].nome,dadoRequisitado)){
            resultadoDaBusca[i] = dataRAMpacientes[0];
            i++;
        }   
    }
    free(dataRAMpacientes);
    if(desejo == 1){
        for(int i=0; i<totalDePacientesAchados;i++){
            printf("\n\nNome: %s\n",resultadoDaBusca[i].nome);
            CPFformatado(resultadoDaBusca[i].cpf);
            printf("\nData de Nascimento: %s",resultadoDaBusca[i].dataDeNascimento);
            formatarNumero(resultadoDaBusca[i].telefone);
        }
    }
    return resultadoDaBusca;
}

//função auxiliar na busca de informações
int comparadorDeStrings(char *stringQueSeQuerComparar, char *stringAserComparada){
    char *ponteiroSubString;
    ponteiroSubString = strstr(stringQueSeQuerComparar,stringAserComparada);
    if(ponteiroSubString)
        return 1;
    return 0;
}

//altera dados paciente dentro do arquivo 
paciente *alterarDadosPaciente(paciente *alvo){
    int ct=0, achou=0;
    char cpfRequest[12];
    paciente *dataRAMPaciente;
    FILE *dataBaseClinica;
    printf("\nDigite o CPF do paciente: ");
    scanf("%[^\n]s",cpfRequest);
    fflush(stdin);
    dataBaseClinica = fopen("dados/dataBaseClinicaPacientes.bin","r+b");
    dataRAMPaciente = (paciente*) calloc(1,sizeof(paciente));
    alvo = (paciente*) calloc(1,sizeof(paciente));
    while(fread(&dataRAMPaciente[0],1,sizeof(paciente),dataBaseClinica)){
        if(comparadorDeStrings(dataRAMPaciente[0].cpf,cpfRequest)){
            printf("\n\nDados encontrados!\n\n");
            printf("\nNome: %s\n",dataRAMPaciente[0].nome);
            CPFformatado(dataRAMPaciente[0].cpf);
            printf("\nData de nascimento: %s",dataRAMPaciente[0].dataDeNascimento);
            formatarNumero(dataRAMPaciente[0].telefone);
            achou = 1;
            break;
        }
        ct++;
    }
    if(achou){
        printf("\n\nDigite os novos dados: \n");
        printf("\nNome:");
        scanf("%[^\n]s",alvo[0].nome);
        fflush(stdin);
        formatadorDeStrings(alvo[0].nome);
        printf("\nCPF:");
        while(strlen(alvo[0].cpf)!=11){
            scanf("%[^\n]s",alvo[0].cpf);
            fflush(stdin);
            if(strlen(alvo[0].cpf)!=11)
                printf("\nCPF invalido, tente novamente: ");
        }
        printf("\nDataDeNascimento:");
        scanf("%[^\n]s",alvo[0].dataDeNascimento);
        fflush(stdin);
        printf("\nTelefone:");
        scanf("%[^\n]s",alvo[0].telefone);
        fflush(stdin);
        fseek(dataBaseClinica,(ct)*sizeof(paciente),SEEK_SET);
        fwrite(&alvo[0],1,sizeof(paciente),dataBaseClinica);
    }else{
        printf("\nPaciente nao encontrado!!!");
        fclose(dataBaseClinica);
        return NULL;
    }
    fclose(dataBaseClinica);
    return alvo;
}

//altera dados medico dentro do arquivo
medico *alterarDadosMedico(medico *alvo){
    int ct=0, achou=0;
    char crmRequest[7];
    medico *dataRAMmedico;
    FILE *dataBaseClinica;
    printf("\nDigite o CRM do Medico: ");
    scanf("%[^\n]s",crmRequest);
    fflush(stdin);
    dataBaseClinica = fopen("dados/dataBaseClinicaMedicos.bin","r+b");
    dataRAMmedico = (medico*) calloc(1,sizeof(medico));
    alvo = (medico*) calloc(1,sizeof(medico));
    while(fread(&dataRAMmedico[0],1,sizeof(medico),dataBaseClinica)){
        if(strcmp(dataRAMmedico[0].crm,crmRequest)==0){
            printf("\n\nDados encontrados!\n\n");
            printf("\nNome: %s",dataRAMmedico[0].nome);
            printf("\nCRM: %s",dataRAMmedico[0].crm);
            printf("\nData de nascimento: %s",dataRAMmedico[0].dataDeNascimento);
            printf("\nEspecialidade: %s",dataRAMmedico[0].especialidade);
            printf("\nValor por consulta: R$%s",dataRAMmedico[0].valorHoraTrabalho);
            formatarNumero(dataRAMmedico[0].telefone);
            achou = 1;
            break;
        }
        ct++;
    }
    if(achou){
        printf("\n\nDigite os novos dados: \n");
        printf("\nNome:");
        scanf("%[^\n]s",alvo[0].nome);
        fflush(stdin);
        formatadorDeStrings(alvo[0].nome);
        printf("\nCRM:");
        while(strlen(alvo[0].crm)!=6){
            scanf("%[^\n]s",alvo[0].crm);
            fflush(stdin);
            if(strlen(alvo[0].crm)!=6)
                printf("\nCRM invalido, tente novamente: ");
        }
        printf("\nDataDeNascimento:");
        scanf("%[^\n]s",alvo[0].dataDeNascimento);
        fflush(stdin);
        printf("\nTelefone:");
        scanf("%[^\n]s",alvo[0].telefone);
        fflush(stdin);
        printf("\nEspecialidade: ");
        scanf("%[^\n]s",alvo[0].especialidade);
        fflush(stdin);
        formatadorDeStrings(alvo[0].especialidade);
        printf("\nValor por consulta: ");
        scanf("%[^\n]s",alvo[0].valorHoraTrabalho);
        fflush(stdin);
        fseek(dataBaseClinica,(ct)*sizeof(medico),SEEK_SET);
        fwrite(&alvo[0],1,sizeof(medico),dataBaseClinica);
    }else{
        printf("\nMedico nao encontrado!!!");
        return NULL;
    }
    fclose(dataBaseClinica);
    return alvo;
}


//printa todos os medicos de uma mesma especialidade
void listarDadosMedico(medico *dataRAMmedicos){
    FILE *dataBaseClinica;
    int numerodemedicos=0;
    dataBaseClinica =fopen("dados/dataBaseClinicaMedicos.bin", "rb");
    if(dataBaseClinica == NULL){
        fclose(dataBaseClinica);
        dataBaseClinica = fopen("dados/dataBaseClinicaMedicos.bin","w+b");
        fclose(dataBaseClinica);
        dataBaseClinica = fopen("dados/dataBaseClinicaMedicos.bin","rb");
    }
    dataRAMmedicos = (medico*)calloc(1,sizeof(medico));
    printf("\nQual a especialidade? ");
    char especialidade[20];
    scanf("%[^\n]s",especialidade);
    fflush(stdin);
    formatadorDeStrings(especialidade);
    while(fread(&dataRAMmedicos[0],1,sizeof(medico),dataBaseClinica)){
        if(comparadorDeStrings(especialidade,dataRAMmedicos[0].especialidade)){
            printf("\n\nCRM: %s",dataRAMmedicos[0].crm);
            printf("\nNome: %s",dataRAMmedicos[0].nome);
            printf("\nData de nascimento: %s",dataRAMmedicos[0].dataDeNascimento);
            formatarNumero(dataRAMmedicos[0].telefone);
            printf("\nValor por consulta: R$%s",dataRAMmedicos[0].valorHoraTrabalho);
        }
    }
}

//retorna array e printa consultas de paciente e medico
void listarConsultas(char *definicao){
    FILE *dataBaseClinica;
    consulta *dataRAMConsulta;
    consulta *resultadoDaListagem;
    paciente *pacienteConsulta;
    medico *medicoConsulta;
    pacienteConsulta = (paciente*)calloc(1,sizeof(paciente));
    medicoConsulta = (medico*)calloc(1,sizeof(medico));
    int totalDeConsultas=0, ct=0;
    dataBaseClinica = fopen("dados/dataBaseClinicaConsultas.bin", "rb");
    if(dataBaseClinica == NULL){
        fclose(dataBaseClinica);
        dataBaseClinica = fopen("dados/dataBaseClinicaConsultas.bin","w+b");
        fclose(dataBaseClinica);
        dataBaseClinica = fopen("dados/dataBaseClinicaConsultas.bin","rb");
    }
    if(strcmp(definicao,"paciente") == 0){
        printf("\nDigite o CPF do paciente: ");
        char cpf[12];
        scanf("%[^\n]s",cpf);
        fflush(stdin);
        dataRAMConsulta = (consulta*) calloc(1,sizeof(consulta));
        while(fread(&dataRAMConsulta[0],1,sizeof(consulta),dataBaseClinica)){
            if(strcmp(dataRAMConsulta[0].cpfPaciente,cpf) == 0)
                totalDeConsultas++;
        }    
        fseek(dataBaseClinica,0,SEEK_SET);
        resultadoDaListagem = (consulta*) calloc(totalDeConsultas,sizeof(consulta));
        for(int i=0; fread(&dataRAMConsulta[0],1,sizeof(consulta),dataBaseClinica); i++){
            if(strcmp(dataRAMConsulta[0].cpfPaciente,cpf) == 0){
                resultadoDaListagem[ct] = dataRAMConsulta[0];
                printf("\n*****************************************\n");
                CPFformatado(resultadoDaListagem[ct].cpfPaciente);
                pacienteConsulta = buscarPaciente(resultadoDaListagem[ct].cpfPaciente,0);
                printf("\nNome do Paciente: %s",pacienteConsulta[0].nome);
                printf("\nCRM do Medico: %s",resultadoDaListagem[ct].crmMedico);
                medicoConsulta = buscarMedico(resultadoDaListagem[ct].crmMedico,0);
                printf("\nNome do Medico: %s",medicoConsulta[0].nome);
                printf("\nData da consulta: %s",resultadoDaListagem[ct].data);
                printf("\nEncaminhamentos: %s",resultadoDaListagem[ct].encaminhamentos);
                printf("\nSintomas: %s",resultadoDaListagem[ct].sintoma);
                printf("\n*****************************************\n");
                ct++;
            }
        }
    }else if(strcmp(definicao,"medico") == 0){
        printf("\nDigite o CRM do medico: ");
        char crm[7];
        scanf("%[^\n]s",crm);
        fflush(stdin);
        dataRAMConsulta = (consulta*) calloc(1,sizeof(consulta));
        while(fread(&dataRAMConsulta[0],1,sizeof(consulta),dataBaseClinica)){
            if(strcmp(dataRAMConsulta[0].crmMedico,crm) == 0)
                totalDeConsultas++;
        }    
        fseek(dataBaseClinica,0,SEEK_SET);
        resultadoDaListagem = (consulta*) calloc(totalDeConsultas,sizeof(consulta));
        for(int i=0; fread(&dataRAMConsulta[0],1,sizeof(consulta),dataBaseClinica); i++){
            if(strcmp(dataRAMConsulta[0].crmMedico,crm) == 0){
                resultadoDaListagem[ct] = dataRAMConsulta[0];
                printf("\n*****************************************\n");
                medicoConsulta = buscarMedico(resultadoDaListagem[ct].crmMedico,0);
                printf("\nCRM do Medico: %s",resultadoDaListagem[ct].crmMedico);
                printf("\nNome do Medico: %s\n",medicoConsulta[0].nome);
                CPFformatado(resultadoDaListagem[ct].cpfPaciente);
                pacienteConsulta = buscarPaciente(resultadoDaListagem[ct].cpfPaciente,0);
                printf("\nNome do paciente: %s",pacienteConsulta[0].nome);
                printf("\nData da consulta: %s",resultadoDaListagem[ct].data);
                printf("\nEncaminhamentos: %s",resultadoDaListagem[ct].encaminhamentos);
                printf("\nSintomas: %s",resultadoDaListagem[ct].sintoma);
                printf("\n*****************************************\n");
                ct++;
            }
        }
    } else{
        printf("\nConsulta nao encontrada!");
    }
    fclose(dataBaseClinica);
}

void menuInicial(){
    system("cls");
    printf("\n*****************************************\n");
    printf("\nDigite o que deseja fazer: ");
    printf("\n(1) Fazer Login");
    printf("\n(2) Cadastrar novo Usuario:");
    printf("\n(0) Encerrar programa.");
    printf("\n*****************************************\n");
}

void menuClinica(){
    printf("\n*****************************************\n");
    printf("\nDigite o que deseja fazer: ");
    printf("\n(1) Pacientes: ");
    printf("\n(2) Medicos: ");
    printf("\n(3) Consultas: ");
    printf("\n(0) Encerrar programa.");
    printf("\n*****************************************\n");
}


void menuMedico(){
    system("cls");
    printf("\n*****************************************\n");
    printf("\nDigite o que deseja fazer: ");
    printf("\n(1) Cadastrar novo Medico.");
    printf("\n(2) Buscar Medicos.");
    printf("\n(3) Listar Medicos.");
    printf("\n(4) Alterar dados medico.");
    printf("\n(0) Retornar.");
    printf("\n*****************************************\n");
}


void menuPaciente(){
    system("cls");
    printf("\n*****************************************\n");
    printf("\nDigite o que deseja fazer: ");
    printf("\n(1) Cadastrar novo Paciente.");
    printf("\n(2) Buscar Paciente.");
    printf("\n(3) Alterar dados paciente.");
    printf("\n(0) Retornar.");
    printf("\n*****************************************\n");
}


void menuConsultas(){
    system("cls");
    printf("\n*****************************************\n");
    printf("\nDigite o que deseja fazer: ");
    printf("\n(1) Agendar consulta.");
    printf("\n(2) Listar consultas medico.");
    printf("\n(3) Listar consultas paciente.");
    printf("\n(0) Retornar.");
    printf("\n*****************************************\n");
}

//função que formata cpf
void CPFformatado(char *cpf){
    printf("CPF: %c%c%c.",cpf[0],cpf[1],cpf[2]);
    printf("%c%c%c.",cpf[3],cpf[4],cpf[5]);
    printf("%c%c%c-",cpf[6],cpf[7],cpf[8]);
    printf("%c%c",cpf[9],cpf[10]);
}

void formatarNumero(char *telefone){
   printf("\nTelefone: (%c%c)",telefone[0],telefone[1]);
   printf("%c%c%c%c%c-",telefone[2],telefone[3],telefone[4],telefone[5],telefone[6]);
   printf("%c%c%c%c",telefone[7],telefone[8],telefone[9],telefone[10]);
}

void formatadorDeStrings(char *palavra){
    for(int i=0; i <strlen(palavra); i++)
        palavra[i] = toupper(palavra[i]);
}
