//JOSÉ ARMANDO COSTA

#include<stdio.h>
#include<stdlib.h>
#include<windows.h>

typedef struct sCelula{
  char info;// Armazena o caracter da posição da linha do editor
  struct sCelula *esq;//Ponteiro de celula para apontar para o nó esquerdo
  struct sCelula *dir;//Ponteiro de celula para apontar para o nó direito
}CARACTER;

void gotoxy(int x, int y)//Controla a posição do cursor na tela utilizando as coordenadas x e y.
{
     SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),(COORD){x-1, y-1});
}

CARACTER* getNode()//cria uma novo no
{
  return (CARACTER*) malloc(sizeof(CARACTER));
}
void freeNode(CARACTER *C)//libera um novo no
{
    free(C);
}
void inicializa(CARACTER **C)//inicializa
{
     (*C)->info = -1;
     (*C)->esq = *C;
     (*C)->dir = *C;
}
int vazia(CARACTER *C)
{
    if(((C->esq)->info == -1)&&(C->dir)->info == -1)
      return 1;
    return 0;
}
void imprime(CARACTER *C)//imprimir na tela caracter
{
     CARACTER *aux;
     aux = C->dir;

     while(aux->info != -1)
     {
       printf("%c", aux->info);
       aux = aux->dir;
     }
}
void insere(CARACTER **C, char c)//inserir caracter
{
     CARACTER *novo;

     novo = getNode();
     if(novo != NULL)
     {
       novo->info = c;
       novo->esq = (*C)->esq;
       novo->dir = *C;
       ((*C)->esq)->dir = novo;
       (*C)->esq = novo;
     }
}
void delete(CARACTER **C)//apagar caracter
{
     CARACTER *aux;

     if(!vazia(*C))
     {
         aux = (*C)->esq;
         (*C)->esq = aux->esq;
         (aux->esq)->dir = (*C);
         freeNode(aux);
         system("cls");
         imprime(*C);
     }
}
void altera(CARACTER **C, char c, int contador)
{
     CARACTER *aux;
     int i=0;
     aux = (*C)->dir;

     while(i < contador)
     {
       aux = aux->dir;
       i++;
     }
     aux->info = c;
}
void deletar(CARACTER **C, int contador)
{
     CARACTER *aux;
     int i=0;
     aux = (*C)->dir;

     while(i < contador)
     {
       aux = aux->dir;
       i++;
     }
     (aux->esq)->dir = aux->dir;
     (aux->dir)->esq = aux->esq;
     freeNode(aux);
     system("cls");
     imprime(*C);
}
void digita(CARACTER **C)
{
   CARACTER *aux;
   aux = *C;
   char c, s;
   int linha=1, coluna=1, nroLinha=1, nroColuna=1;
   int insert = 0;
   FILE *arquivo;


   while(c != 27)
   {
      c = getche();
      if((c!=8)&&(c!=-32)&&(c!=13)&&(c!=0))
      {
         if(insert == 0)
         {
            if(linha < 25)
            {
                insere(C, c);
                system("cls");
                imprime(*C);
                coluna = nroColuna;
                linha = nroLinha;
                if(nroColuna == 80)
                {
                  nroColuna = 1;
                  nroLinha++;
                }
                else
                  nroColuna++;

                if(coluna == 80)
                {
                  coluna = 1;
                  linha++;
                }
                else
                  coluna++;
            }
         }
         else
         {
            altera(C,c,(80*(linha-1))+(coluna-1));
            insert = 0;
         }
      }
      else
      {
        if(c == 0)
        {
          c = getche();
          if(c == 59)
          {
            if((arquivo = fopen("Sobre.txt","r")) != NULL)
            {
              system("cls");
              do{
                 s = fgetc(arquivo);
                 printf("%c", s);
              }while(s != EOF);
              do{
                c = getche();
              }while(c != 27);
              system("cls");
              imprime(*C);
              c = 13;
            }
          }
          if(c == 60)
          {
            if((arquivo = fopen("Arquivo.txt","w+")) != NULL)
            {
              aux = (*C)->dir;
              while(aux->info != -1)
              {
                fputc(aux->info, arquivo);
                aux = aux->dir;
              }
              fclose(arquivo);
            }
          }
          if(c == 68)
          {
            if((arquivo = fopen("Arquivo.txt","r")) != NULL)
            {
                do{
                    c = fgetc(arquivo);
                    printf("%c", c);
                    insere(C, c);
                    system("cls");
                    imprime(*C);
                    coluna = nroColuna;
                    linha = nroLinha;
                    if(nroColuna == 80)
                    {
                      nroColuna = 1;
                      nroLinha++;
                    }
                    else
                      nroColuna++;

                    if(coluna == 80)
                    {
                      coluna = 1;
                      linha++;
                    }
                    else
                      coluna++;
                }while(c != EOF);
            }
            fclose(arquivo);
          }
        }
        if(c == 8)
        {
          system("cls");
          imprime(*C);
          if(linha > 0)
          {
            delete(C);
            if(nroColuna == 1)
            {
              nroColuna = 80;
              nroLinha--;
            }
            else
              nroColuna--;


            if(coluna == 1)
            {
              coluna = 80;
              linha--;
            }
            else
              coluna--;
          }
        }
        if(c == -32)
        {
          system("cls");
          imprime(*C);
          c = getche();
          if(c == 72)
          {
            if(linha > 1)
               linha--;
            gotoxy(coluna,linha);
          }
          if(c == 75)
          {
            if(coluna > 1)
              coluna--;
            gotoxy(coluna,linha);
          }
          if(c == 77)
          {
            if(coluna <= 80 && coluna<nroColuna)
              coluna++;
            gotoxy(coluna, linha);
          }
          if(c == 80)
          {
            if(linha <= 25 && linha<nroLinha)
              linha++;
            gotoxy(coluna, linha);
          }
          if(c == 71)
          {
            coluna = 1;
            gotoxy(coluna, linha);
          }
          if(c == 79)
          {
            if(linha >= nroLinha)
              coluna = nroColuna;
            else
              coluna = 80;
            gotoxy(coluna, linha);
          }
          if(c == 73)
          {
            linha = 1;
            gotoxy(coluna, linha);
          }
          if(c == 81)
          {
            linha = nroLinha;
            gotoxy(coluna, linha);
          }
          if(c == 82)
          {
            if((linha != nroLinha)||(coluna != nroColuna))
            {
               gotoxy(coluna,linha);
               insert = 1;
            }
          }
          if(c == 83)
          {
            if((linha != nroLinha)||(coluna != nroColuna))
            {
               gotoxy(coluna,linha);
               deletar(C, (80*(linha-1))+(coluna-1));
            }
          }
          if(c == -122)
          {
              system("cls");
              printf("Informacoes sobre o grupo");
              do{
                c = getch();
              }while(c != 27);
              system("cls");
              imprime(*C);
              c = 13;
          }
        }
      }
   }
}

int main(void)
{
    CARACTER *caracteres;
    int arq = 0;
    FILE *arquivo;
    char c;

    caracteres = getNode();
    if(caracteres == NULL)
      exit(0);
    inicializa(&caracteres);
    digita(&caracteres);
    printf("\n\n\n\n");
    imprime(caracteres);
    printf("\n\n\n\n");

    system("PAUSE");
    return 0;
}
