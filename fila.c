#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct requisicao
{
  char prioridade;
  char ip[11];
  struct requisicao *prox;
} Requisicao;

typedef struct requisicao *Fila;
typedef struct requisicao RequisicaoImpressao;

Fila *cria_fila()
{
  Fila *fila = (Fila *)malloc(sizeof(Fila)); //reservar memoria para o primeiro no da lista
  if (fila != NULL)
  {
    *fila = NULL; //Dando ao ultimo elemento da lista o valor de null
    printf("Fila criada com sucesso!.\n\n");
    return fila;
  }
}

int insere_requisicoes_fila(Fila *fila, char prioridade[1], char ip[11])
{

  if (fila == NULL)
    return 0;

  RequisicaoImpressao *no = (RequisicaoImpressao *)malloc(sizeof(RequisicaoImpressao));
  no->prioridade = prioridade;
  strcpy(no->ip, ip);
  no->prioridade = prioridade;

  if ((*fila) == NULL)
  {
    *fila = no;
  }
  else
  {
    RequisicaoImpressao *aux = *fila; //SEMPRE percorrer a lista com um aux, nunca com o inicio da lista
    while (aux->prox != NULL)
    {
      aux = aux->prox;
    }
    aux->prox = no; //insere no final o novo no
  }

  printf("Inserindo: Prioridade->%c, Ip->%s\n", no->prioridade, no->ip);

  return 1;
}

void imprime_fila(Fila *fila)
{

  RequisicaoImpressao *req = *fila;
  while (req != NULL)
  {
    printf("Vendo: Prioridade->%c, Ip->%s\n", req->prioridade, req->ip);
    req = req->prox;
  }
}

int main()
{

  FILE *arq;
  int result;
  char AuxStr[17];
  struct Fila *fila = cria_fila();

  int i = 1;
  arq = fopen("fila.txt", "rt");

  if (arq == NULL)
  {
    printf("Problemas na CRIACAO do arquivo\n");
    return;
  }
  else
  {
    printf("Fila de Entrada:\n");
    while (i <= 50)
    {

      result = fgets(AuxStr, 17, arq);
      if (result)
      {
        char *str = malloc(strlen(AuxStr));

        insere_requisicoes_fila(fila, AuxStr[1], strncpy(str, AuxStr + 4, 11));

        i++;
      }
    }

    imprime_fila(fila);

    fclose(arq);
  }
}