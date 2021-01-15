#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#define MAX_WORD 32
#define MAX_TEXT_LENGTH 100000


typedef struct word {
char *str;
int fre;
struct word *pNext;
} Word;


Word* laskeSanat(char *word);

Word *aAlku = NULL;

int uniqc = 0;



struct word* vaihto(struct word* ptr1, struct word* ptr2)
{
    struct word* tmp = ptr2->pNext;
    ptr2->pNext = ptr1;
    ptr1->pNext = tmp;
    return ptr2;
}

void sort(struct word** head, int count)
{
    struct word** h;
    int i, j, k;

    for(i = 0; i <= count; i++)
    {
        h = head;
        k = 0;

        for(j = 0; j < count - i - 1; j++)
        {
            struct word* p1 = *h;
            struct word* p2 = p1->pNext;

            if(p1->fre < p2->fre)
            {
                *h = vaihto(p1, p2);
                k = 1;
            }
            h = &(*h)->pNext;
        }
        if(k == 0)
        {
            break;
        }
    }
}


void print (Word *WordCalc)
{

  printf("\n%-30s   %5d", WordCalc->str, WordCalc->fre);

}


void add (char *word)
{
  Word *Calc = NULL;
  Word *pLast = NULL;

  if(aAlku == NULL)
  {
    aAlku = laskeSanat(word);
    return;
  }


  Calc = aAlku;
  while ( Calc != NULL)
  {
    if ( strcmp ( word, Calc -> str) == 0)
    {
      ++Calc -> fre;

      return;
    }
    pLast = Calc;
    Calc = Calc -> pNext;
  }


  pLast->pNext = laskeSanat(word);
}


Word* laskeSanat(char *word)
{
  Word *Calc = NULL;
  Calc = (Word*)malloc(sizeof(Word));
  Calc->str = (char*)malloc(strlen(word)+1);
  strcpy(Calc -> str, word);
  Calc->fre = 1;
  Calc->pNext = NULL;
  return Calc;
}


int etiSana(FILE *fp, char *buf, int bufsize) {
    char *p = buf;
    char c;



    do {
        c = fgetc(fp);
        if (c == EOF)
            return 0;
        } while (!isalpha(c) || c=='\'');


    do {
        if (p - buf < bufsize - 1)
        *p++ = toupper(c);
        c = fgetc(fp);
        } while (isalpha(c) || c=='\'');

        *p = '\0';
        return 1;
        }


int main ()
{
    time_t alku, loppu;
    FILE * fp;
    char filename[32];
    printf("Syota tekstitiedoston nimi: >");
    scanf("%s", filename);
    alku = clock();


    fp = fopen(filename,"r");

    if(fp == NULL)
    {
        perror("Error\n");
        exit(EXIT_FAILURE);
    }

    char buf[MAX_WORD];

    int size = MAX_TEXT_LENGTH;

    Word *Calc = NULL;

    while (etiSana(fp, buf, size)) {

        add(buf);
    }



    Calc = aAlku;
    while(Calc != NULL)
    {
        uniqc++;
        Calc = Calc->pNext;
    }

    sort(&aAlku, uniqc);

    printf("TIEDOSTON 100 YLEISINTA SANAA\nJarjestetty esiintymiskertojen mukaan");


    Calc = aAlku;
    int i = 0;
    while(i <= 99)
    {
        print(Calc);
        Calc = Calc->pNext;
        i++;
    }
    printf("\n");



    Calc = aAlku;
    while(Calc != NULL)
    {
        free(Calc->str);
        aAlku = Calc;
        Calc = Calc->pNext;
        free(aAlku);
    }

    fclose(fp);

    loppu = clock() - alku;
    double aika_kesto = ((double)loppu)/CLOCKS_PER_SEC;
    printf("\n\nOhjelma kesti %.3f sekuntia suorittaa\n", aika_kesto);
    return 0;

}

