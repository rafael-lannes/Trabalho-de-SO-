#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <semaphore.h>


void *male(void *);                         /*Declaração das funções dos rapazes e moças*/
void *female(void *);

sem_t empty;                                /*Semaforo do banheiro 0 vazio e 1 ocupado*/
sem_t male_mutex;                           /* mutex for male_counter*/
sem_t male_multiplex;                       /* limita o numero de rapazes no banheiro*/
int male_counter = 0;                       /* numero de rapazes no banheiro ou esperando*/
sem_t female_mutex;                         /* mutex for female_counter*/
sem_t female_multiplex;                     /* limits o numero de moças no banheiro*/
int female_counter = 0;                     /* numero de moças no banheiro ou esperando*/
sem_t turnstile;                            /* Semáforo para limitar outras threads e resolver starvation*/

void *male(void *param){
    int r=rand()%10;                        /*Atribui um valor aleatorio para r (para o tempo de cada thread no banheiro*/
    sem_wait(&turnstile);                   /*"Roleta" para evitar que outras pessoas do genero oposto entre e ocorra starvation*/
    printf("Um rapaz é o proximo.\n");      /*Indica quem chegou na "roleta" primeiro*/
    sem_wait(&male_mutex);
    male_counter++;                         /*Incrementa o contador de rapazes*/
    if(male_counter == 1){
        sem_wait(&empty);                   /* O banheiro fica livre , ou wait*/
    }
    sem_post(&turnstile);                   /*Libera a roleta para o próximo*/
    sem_post(&male_mutex);                  /* Destrava o semáforo dos rapazes*/
    sem_wait(&male_multiplex);              /* Limita o numero de rapazes no banheiro*/
    printf("Rapaz entrou!\n");              /*Indica Que um Rapaz entrou no banheiro*/
    printf("Ele ficara %d segundos no banheiro. \n",r);   /* Indica o tempo que o rapaz gastará no banheiro (entre 0 e 10) */
    sleep(r);                               /*Força a função esperar r segundos (definido aleatoriamente)*/
    printf("Rapaz Saiu!\n");                /*Indica que o rapaz saiu do banheiro*/
    sem_post(&male_multiplex);              /* Permite que o proximo entre.*/
    sem_wait(&male_mutex);                  /* Trava o semáforo dos rapazes*/
    male_counter--;                         /* Decrementa o contador de rapazes*/
    if (male_counter == 0){                 /*Se o contador chegar a zero....*/
        sem_post(&empty);                   /*... libera o banheiro para moças. */
    }
    sem_post(&male_mutex);                  /*...Senão destrava o semáforo para rapazes novamente*/
}

void *female(void *param){
    int r=rand()%10;
    sem_wait(&turnstile);
    printf("Uma moça é a proxima.\n");
    sem_wait(&female_mutex);
    female_counter++;
    if(female_counter == 1){

        sem_wait(&empty);                   /*O banheiro fica livre , ou wait. */

    }
    sem_post(&turnstile);

    sem_post(&female_mutex);

    sem_wait(&female_multiplex);               /* Limita o numero de moças no banheiro.*/
    printf("Moça entrou!\n");
    printf("Ela ficara %d segundos no banheiro. \n",r);
    sleep(r);
    printf("Moça saiu!\n");
    sem_post(&female_multiplex);              /* Permite que o proximo entre.*/

    sem_wait(&female_mutex);
    female_counter--;
    if (female_counter == 0){
        sem_post(&empty);                   /* ibera o banheiro para rapazes.*/
    }
    sem_post(&female_mutex);
}

int main(void){
    int i;
    int x;
    int t;

    /*srand(time(NULL));*/
    int a[100]={};    /*vetor que ira definir se as threads serao rapazes ou moças */
    printf("Defina o numero de empregados que irao entrar no banheiro: ");
    scanf("%d",&t);  /* t irá definir a quantidade de threads que o propgrama executará */

    for(i=0;i<t;i++){  /*Laço for para definir o gênero de cada thread e definir situações desejadas */
        printf("0 para Moça e 1 Para Rapaz:");
        scanf("%d",&a[i]);
    }

    for(i=0;i<t;i++){ /*Printa 0 para moças e 1 para rapazes apenas para controle */
        printf("%d", a[i]);
    }
    printf("\n");
    /*Inicializando os semaforos */
    sem_init(&empty, 0, 1);
    sem_init(&male_mutex, 0, 1);
    sem_init(&male_multiplex, 0, 3);
    sem_init(&female_mutex, 0, 1);
    sem_init(&female_multiplex, 0, 3);
    sem_init(&turnstile, 0,1);

    /*Declarando e alocando as threads */
    pthread_t *tid;
    tid = malloc(80*sizeof(pthread_t));

    for(i=0;i<t;i++){                               /*Laço para criar a thread t vezes e dependendo do valor do indice no vetor define o gênero */
        if(a[i] == 0){
            pthread_create(&tid[i],NULL,female,NULL);
        }
        else{
            pthread_create(&tid[i],NULL,male,NULL);
        }
    }

    for(i=0;i<t;i++){                               /*Laço para criar a função que espera terminar todas as threads */
        pthread_join(tid[i],NULL);
    }

    return(0);
}
/*Fim do programa*/
