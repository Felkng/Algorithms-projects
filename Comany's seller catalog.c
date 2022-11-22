#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct{
   char nome[60];
   float salarioBase;
   char dataDeNascimento[10]; 
   float totalVendido;
   char cpf[11];
   float comissao;
   char cpfFormato[14];
} vendedor;
vendedor *cadastrarVendedor(vendedor *vendedores, int *vendedor, int *primeiraVez);
void mostravendedores(vendedor *arrayVendedores, int quantidade);
vendedor *calculacomissao(vendedor *vendedores, int *quantidade);
vendedor *buscarVendedor(vendedor *vendedores, int *quantidade, int *limiteArray);
vendedor *alfabetizador(vendedor *array, int tamanhoDaArray);
void transformadorDeCPF(char *CPF, char *cpfFormatado);
void menu();
vendedor cadastrando(vendedor *array, int contador);
int buscaBinariaVendedor(char *input);
int comparadorDeCPF(char *cpf, char *cpfQueSeQuerComparar);
int comparadorDeNomes(char *nome, char *nomeQueSeQuerComparar);
char formatarNomes(char *nome);

int main() {
  vendedor *vendedores, *vendedoresBuscados;
  int *quantidadeDeVendedores,opcao, *prima, *quantidadeVendedoresBuscados;
  int variavelQuantidade,variavelPrima=1, variavelQuantidadeVendedoresBuscados;
  prima = &variavelPrima;
  quantidadeDeVendedores = &variavelQuantidade;
  quantidadeVendedoresBuscados = &variavelQuantidadeVendedoresBuscados;

  do{
    menu();
    scanf("%d",&opcao);
    fflush(stdin);
    switch(opcao){
      case 1:
          system("cls");
          vendedores = cadastrarVendedor(vendedores,quantidadeDeVendedores,prima);
        break;

      case 2:
          system("cls");
          mostravendedores(vendedores,variavelQuantidade);
        break;

      case 3:
          system("cls");
          vendedores = calculacomissao(vendedores,quantidadeDeVendedores);
        break;

      case 4:
          system("cls");
          vendedoresBuscados = buscarVendedor(vendedores, quantidadeDeVendedores, quantidadeVendedoresBuscados);
          if(vendedoresBuscados)
            mostravendedores(vendedoresBuscados, variavelQuantidadeVendedoresBuscados);
          free(vendedoresBuscados);
        break;

      case 0:
          free(vendedores);
        return 0;
    }
  }while(1);
  return 0;
}
//FUNÇÃO QUE ALOCA A MEMORIA PARA O CADASTRO DOS VENDEDORES
vendedor *cadastrarVendedor(vendedor *vendedores, int *quantidade, int *primeiraVez){
 int varQuantidade;
  if(*primeiraVez){
    *primeiraVez = 0;
    printf("\nDigite a quantidade de vendedores a serem cadastrados: ");
    scanf("%d",&varQuantidade);
    fflush(stdin);
    *quantidade = varQuantidade;
    vendedores = (vendedor*) calloc(varQuantidade,sizeof(vendedor));
    for(int i=0; i<varQuantidade; i++)
      vendedores[i] = cadastrando(vendedores, i);
  } else{
    printf("\nDigite a quantidade de vendedores a serem cadastrados: ");
    int x;
    scanf("%d",&x);
    fflush(stdin);
    vendedores = (vendedor*) realloc(vendedores,(*quantidade+x) * sizeof(vendedor));
    for(int i=*quantidade; i<(*quantidade+x); i++)
      vendedores[i] = cadastrando(vendedores, i);
    *quantidade += x;
  }

  //colocar em ordem alfabética
  varQuantidade = *quantidade;
  vendedores = alfabetizador(vendedores, varQuantidade);
    return vendedores;

}
//FUNÇÃO QUE EXIBE ARRAY DE VENDEDORES
void mostravendedores(vendedor *arrayVendedores, int quantidade){

  for(int i=0;i<quantidade;i++){
    printf("\nNome: %s",arrayVendedores[i].nome);
    printf("\nCPF: %s",arrayVendedores[i].cpfFormato);
    printf("\nData de Nascimento: %s",arrayVendedores[i].dataDeNascimento);
    printf("\nSalario Base: %.2f",arrayVendedores[i].salarioBase);
    printf("\nTotal vendido: %.2f",arrayVendedores[i].totalVendido);
    printf("\n\n*******************************************\n\n");
   }

}
//FUNÇÃO QUE CALCULA A COMISSAO
vendedor *calculacomissao(vendedor *vendedores,int *quantidade){


  for(int i=0;i<*quantidade;i++){
    vendedores[i].comissao = vendedores[i].totalVendido * 0.03;
  }
  for(int i=0;i<*quantidade;i++){
    printf("%s: R$ %.2f\n\n",vendedores[i].nome,vendedores[i].comissao);
  }
  return vendedores;
}

//FUNÇÃO QUE BUSCA OS VENDEDORES
vendedor *buscarVendedor(vendedor * vendedores, int *quantidade, int *limiteArray){
  char inputDoTeclado[60];
  int varQuantidade = *quantidade;
  int varLimite=0;
  vendedor *resultadosDaBusca;
  printf("\nInsira informacao do vendedor: ");
  scanf("%[^\n]",inputDoTeclado);
  fflush(stdin);
  if(buscaBinariaVendedor(inputDoTeclado)==0){
    for(int i=0;i<varQuantidade;i++){
      if(comparadorDeNomes(vendedores[i].nome,inputDoTeclado))
        varLimite+=1;
    }
    resultadosDaBusca = (vendedor*)calloc(varLimite,sizeof(vendedor));
    varLimite=0;
    for(int i=0;i<varQuantidade;i++){
      if(comparadorDeNomes(vendedores[i].nome,inputDoTeclado)){
        resultadosDaBusca[varLimite] = vendedores[i];
        varLimite+=1;
      }
    }
    *limiteArray = varLimite;
  }
  else if(buscaBinariaVendedor(inputDoTeclado)==1){
    for(int i=0;i<varQuantidade;i++){
      if(comparadorDeCPF(inputDoTeclado,vendedores[i].cpf))
        varLimite+=1;
    }
      resultadosDaBusca = (vendedor*)calloc(varLimite,sizeof(vendedor));
      varLimite=0;
      for(int i=0;i<varQuantidade;i++){
        if(comparadorDeCPF(inputDoTeclado,vendedores[i].cpf)){
            resultadosDaBusca[varLimite] = vendedores[i];
            varLimite+=1;
        }
     }
     *limiteArray = varLimite;
  }
  else if(buscaBinariaVendedor(inputDoTeclado)==-1){
    for(int i=0;i<varQuantidade;i++){
      if(strcmp(vendedores[i].dataDeNascimento,inputDoTeclado)==0){
        varLimite+=1;
      }
    }
    resultadosDaBusca = (vendedor*)calloc(varLimite,sizeof(vendedor));
    varLimite=0;
    for(int i=0;i<varQuantidade;i++){
      if(strcmp(vendedores[i].dataDeNascimento,inputDoTeclado)==0){
        resultadosDaBusca[varLimite] = vendedores[i];
        varLimite+=1;
      }
    }
    *limiteArray = varLimite;
  }
  if(varLimite==0){
    printf("\nVENDEDOR NAO ENCONTRADO!");
    *limiteArray = 1;
    return NULL;
  }
  return resultadosDaBusca;


}

//FUNÇÃO QUE ORGANIZA A ARRAY DE VENDEDORES EM ORDEM ALFABÉTICA
vendedor *alfabetizador(vendedor *array, int tamanhoDaArray){
  vendedor trocaNomes;
  for(int i=0;i<tamanhoDaArray;i++){
    for(int j=i; j<tamanhoDaArray; j++){
      for(int z=0, n=0; array[i].nome[z] != '\0' || array[j].nome[n] != '\0' ;z++,n++){
        if(array[i].nome[z] == ' ')
          z++;
        if(array[j].nome[n] == ' ')
          n++;
        if(toupper(array[i].nome[z])<toupper(array[j].nome[n])){
            break;
        }

        else if(toupper(array[i].nome[z])>toupper(array[j].nome[n])){
            trocaNomes = array[j];
            array[j] = array[i];
            array[i] = trocaNomes;
            break;
        }
      }
    }
  }
  return array;
}

//FUNÇÃO QUE EXIBE O MENU
void menu(){
  printf("\n\n\n*******************************************\n");
  printf("O que deseja fazer? Digite a opcao Desejada:\n");
  printf("Cadastrar Novos Vendedores (1)\n");
  printf("Mostrar os dados de todos os Vendedores Cadastrados (2)\n");
  printf("calcular comissoes (3)\n");
  printf("Mostrar dados de um vendedor especifico (4)\n");
  printf("Sair do Programa (0)\n*******************************************\n");

}
//função que faz o cadastro
vendedor cadastrando(vendedor *array, int contador){
    vendedor esqueleto;
  fflush(stdin);
  printf("\nNome do vendedor: ");
  scanf("%[^\n]",array[contador].nome);
  fflush(stdin);
  formatarNomes(array[contador].nome);
  printf("CPF do vendedor: ");
  while(1){
    scanf("%[^\n]",array[contador].cpf);
    fflush(stdin);
    if(strlen(array[contador].cpf) != 11 )
      printf("CPF incorreto, porfavor, digite novamente: ");
    else
      break;
  }
  transformadorDeCPF(array[contador].cpf,array[contador].cpfFormato);
  printf("Data de nascimento do vendedor: ");
  scanf("%[^\n]",array[contador].dataDeNascimento);
  fflush(stdin);
  printf("Salario base do vendedor: ");
  scanf("%f",&array[contador].salarioBase);
  fflush(stdin);
  printf("Total vendido do vendedor: ");
  scanf("%f",&array[contador].totalVendido);
  fflush(stdin);
  esqueleto = array[contador];
  return esqueleto;
}
//FUNÇÃO QUE TOMA A DECISÃO NA BUSCA
int buscaBinariaVendedor(char *input){
    fflush(stdin);
  if(input[0]>='A' || input[0]==' ')
    return 0; //É UM NOME
  if(strlen(input)==11)
    return 1; //É UM CPF
  return -1; //É A DATA
}
//FUNÇÃO QUE FORMATA O CPF
void transformadorDeCPF(char *CPF, char *cpfFormatado){
    cpfFormatado[0] = CPF[0];
    cpfFormatado[1] = CPF[1];
    cpfFormatado[2] = CPF[2];
    cpfFormatado[3] = '.';
    cpfFormatado[4] = CPF[3];
    cpfFormatado[5] = CPF[4];
    cpfFormatado[6] = CPF[5];
    cpfFormatado[7] = '.';
    cpfFormatado[8] = CPF[6];
    cpfFormatado[9] = CPF[7];
    cpfFormatado[10] = CPF[8];
    cpfFormatado[11] = '-';
    cpfFormatado[12] = CPF[9];
    cpfFormatado[13] = CPF[10];
    cpfFormatado[14] = CPF[11];
}
//FUNÇÃO QUE COMPARA OS CPF
int comparadorDeCPF(char *cpf, char *cpfQueSeQuerComparar){
    int comparator;
    comparator = strcmp(cpf,cpfQueSeQuerComparar);
    if(comparator==0)
        return 1;
    return 0;
}
//FUNÇÃO QUE COMPARA OS NOMES
int comparadorDeNomes(char *nome, char *nomeQueSeQuerComparar){
    char *subString;
    formatarNomes(nomeQueSeQuerComparar);
    subString = strstr(nome,nomeQueSeQuerComparar);
    if(subString)
        return 1;
    return 0;
}
//FUNÇÃO QUE FORMATA OS NOMES
char formatarNomes(char *nome){
  for(int i=0; nome[i] != '\0'; i++){
    nome[i] = toupper(nome[i]);
  }
  return *nome;
}
