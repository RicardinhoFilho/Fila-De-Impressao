#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct requisicao
{
    char prioridade;
    char ip[11];
    struct requisicao *prox;

} Requisicao;

typedef struct fila_requisicao
{

    struct requisicao *final;
    struct requisicao *inicio;
} Fila_Requisicao;

typedef struct requisicao *Fila;
typedef struct requisicao RequisicaoImpressao;

typedef struct fila_requisicao *Estrutura;

// Fila *cria_fila_nodo()
// {
//     Fila *fila = (Fila *)malloc(sizeof(Fila)); //reservar memoria para o primeiro no da lista
//     if (fila != NULL)
//     {
//         *fila = NULL; //Dando ao ultimo elemento da lista o valor de null
//         printf("Fila criada com sucesso!.\n\n");
//         return fila;
//     }
// }

Estrutura *cria_fila()
{
    Estrutura fila = (Estrutura *)malloc(sizeof(Estrutura)); //reservar memoria para o primeiro no da lista
    if (fila != NULL)
    {
        fila->final = NULL;
        fila->inicio = NULL;
        return fila;
    }
}

int insere_requisicoes_fila(Fila_Requisicao *fila, char prioridade[1], char ip[11])
{

    if (fila == NULL)
        return 0;

    RequisicaoImpressao *no = (RequisicaoImpressao *)malloc(sizeof(RequisicaoImpressao));

    no->prioridade = prioridade;
    strcpy(no->ip, ip);
    no->prioridade = prioridade;

    if (fila->inicio == NULL)
    {
        
        fila->inicio = no;
        fila->final = no;
        no->prox = NULL;
           printf("Inserindo: Prioridade->%c, Ip->%s\n", fila->inicio->prioridade, fila->inicio->ip);

    }
    else
    {
       fila->final->prox = no; 
    fila->final = no;
    
           printf("Inserindo: Prioridade->%c, Ip->%s\n", fila->inicio->prioridade, fila->inicio->ip);
    
    }

    return 1;
}

int remove_elem_fila(Estrutura fila)
{
    if (fila == NULL)
        return 0;

    if(fila->inicio == NULL){
        return 0;
    }  

    RequisicaoImpressao *no = fila->inicio;

    fila->inicio = fila->inicio->prox;

    if(fila->inicio == NULL){
        fila->final= NULL;
    }


    free(no);
    printf("ELEMENTO REMOVIDO!\n\n");
    return 1;
}

void imprime_fila(Estrutura fila)
{
    int cont = 0;
    RequisicaoImpressao *req =  fila->inicio;

    if(fila->inicio == NULL){
        printf("Esta fila está vazia!\n\n");
    }

    while (req != fila->final)
    {
        cont++;
        printf("%d-\n Prioridade:%c\n Ip:%s\n", cont, req->prioridade, req->ip);
        printf("----------------------------------------\n\n");
        req = req->prox;
    }
}

void rodada(Estrutura fila, Estrutura *fila0, Estrutura *fila1, Estrutura *fila2)
{printf("AQUI DEU \n\n\n\n\n\n");
    RequisicaoImpressao *req =  fila->inicio;
    printf("AQUI DEU \n\n\n\n\n\n");
    if (req->prioridade == '3')
    {
        insere_requisicoes_fila(fila0, req->prioridade, req->ip);
    }
    else if (req->prioridade == '3')
    {
        insere_requisicoes_fila(fila1, req->prioridade, req->ip);
    }
    else if (req->prioridade == '2')
    {
        insere_requisicoes_fila(fila2, req->prioridade, req->ip);
    }

    //remove_elem_fila(fila); //Comentei a linha de remover
}

void tenta(Estrutura fila, Fila *fila0, Fila *fila1, Fila *fila2)
{
    RequisicaoImpressao *req = fila->inicio;
    while (req != NULL)
    {
        printf("TESTE");
        printf("%c\n\n\n\n", req->prioridade);
        if (req->prioridade == '3')
        {
            insere_requisicoes_fila(fila0, req->prioridade, req->ip);
        }
        else if (req->prioridade == '2')
        {
            insere_requisicoes_fila(fila1, req->prioridade, req->ip);
        }
        else if (req->prioridade == '1')
        {
            insere_requisicoes_fila(fila2, req->prioridade, req->ip);
        }

        req = req->prox;
    }
}

int main()
{

    FILE *arq;
    int result;
    char AuxStr[17];
    struct Estrutura *fila = cria_fila();
    struct Estrutura *fila0 = cria_fila();
    struct Estrutura *fila1 = cria_fila();
    struct Estrutura *fila2 = cria_fila();

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

        tenta(fila, fila0, fila1, fila2);
        for (i = 0; i < 50; i++)
        {
            remove_elem_fila(fila);
        }

        printf("Fila Geral\n");
        imprime_fila(fila);

        printf("Fila 1\n");
        imprime_fila(fila0);

        printf("Fila 2\n");
        imprime_fila(fila1);

        printf("Fila 3\n");
        imprime_fila(fila2);

        fclose(arq);
    }
}