/*
Trabalho de Sistemas Operacionais
Parte01 - Criação de Threads
Grupo:
Rafael de Farias Lannes
Patricia Martins Rocca Crestani
Nicolas Atmatzides
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

void *masculino(void *);                    /*Declaração das funções dos rapazes e moças*/
void *feminino(void *);

sem_t vazio;                                /*Semaforo do banheiro 0 vazio e 1 ocupado*/
sem_t masculino_mutex;                      /*Mutex para masculino_contador*/
sem_t masculino_multiplex;                  /*Limita o numero de rapazes no banheiro*/
int masculino_contador = 0;                 /*Numero de rapazes no banheiro ou esperando*/
sem_t feminino_mutex;                       /*Mutex para feminino_contador*/
sem_t feminino_multiplex;                   /*Limita o numero de moças no banheiro*/
int feminino_contador = 0;                  /*Numero de moças no banheiro ou esperando*/
sem_t turnstile;                            /*Semáforo para limitar outras threads e resolver starvation */

void *masculino(void *param){
    int r=rand()%10;                        /*Atribui um valor aleatorio para r (para o tempo de cada thread no banheiro)*/
    sem_wait(&turnstile);                   /*"Roleta" para evitar que outras pessoas do genero oposto entre e ocorra starvation*/
    printf("Um rapaz é o proximo.\n");      /*Indica quem chegou na "roleta" primeiro*/
    sem_wait(&masculino_mutex);
    masculino_contador++;                   /*Incrementa o contador de rapazes*/
    if(masculino_contador == 1){
        sem_wait(&vazio);                   /*O banheiro fica livre, ou wait*/
    }
    sem_post(&turnstile);                   /*Libera a roleta para o próximo*/
    sem_post(&masculino_mutex);             /*Destrava o semáforo dos rapazes*/
    sem_wait(&masculino_multiplex);         /*Limita o numero de rapazes no banheiro*/
    printf("Rapaz entrou!\n");              /*Indica Que um Rapaz entrou no banheiro*/
    printf("Ele ficara %d segundos no banheiro. \n",r);   /*Indica o tempo que o rapaz gastará no banheiro (entre 0 e 10)*/
    sleep(r);                               /*Força a função esperar r segundos (definido aleatoriamente)*/
    printf("Rapaz Saiu!\n");                /*Indica que o rapaz saiu do banheiro*/
    sem_post(&masculino_multiplex);         /*Permite que o proximo entre*/
    sem_wait(&masculino_mutex);             /*Trava o semáforo dos rapazes*/
    masculino_contador--;                   /*Decrementa o contador de rapazes*/
    if (masculino_contador == 0){           /*Se o contador chegar a zero....*/
        sem_post(&vazio);                   /*... libera o banheiro para moças. */
    }
    sem_post(&masculino_mutex);             /*...senão destrava o semáforo para rapazes novamente*/
}

void *feminino(void *param){
    int r=rand()%10;
    sem_wait(&turnstile);
    printf("Uma moça é a proxima.\n");
    sem_wait(&feminino_mutex);
    feminino_contador++;
    if(feminino_contador == 1){
        sem_wait(&vazio);                   /*O banheiro fica livre , ou wait*/
    }
    sem_post(&turnstile);
    sem_post(&feminino_mutex);
    sem_wait(&feminino_multiplex);          /*Limita o numero de moças no banheiro*/
    printf("Moça entrou!\n");
    printf("Ela ficara %d segundos no banheiro. \n",r);
    sleep(r);
    printf("Moça saiu!\n");
    sem_post(&feminino_multiplex);          /*Permite que o proximo entre*/
    sem_wait(&feminino_mutex);
    feminino_contador--;
    if (feminino_contador == 0){
        sem_post(&vazio);                   /*Libera o banheiro para rapazes*/
    }
    sem_post(&feminino_mutex);
}

int main(void){
    int i;
    int x;
    int t;
    int a[100]={};                   /*Vetor que ira definir se as threads serao rapazes ou moças*/
    printf("Defina o numero de empregados que irao entrar no banheiro: ");
    scanf("%d",&t);                  /*t irá definir a quantidade de threads que o propgrama executará*/
    for(i=0;i<t;i++){                /*Laço for para definir o gênero de cada thread e definir situações desejadas*/
        printf("0 para Moça e 1 Para Rapaz:");
        scanf("%d",&a[i]);
    }
    for(i=0;i<t;i++){                /*Printa 0 para moças e 1 para rapazes apenas para controle */
        printf("%d", a[i]);
    }
    printf("\n");
    /*Inicializando os semaforos*/
    sem_init(&vazio, 0, 1);
    sem_init(&masculino_mutex, 0, 1);
    sem_init(&masculino_multiplex, 0, 3);
    sem_init(&feminino_mutex, 0, 1);
    sem_init(&feminino_multiplex, 0, 3);
    sem_init(&turnstile, 0, 1);
    /*Declarando e alocando as threads*/
    pthread_t tid[t];
    for(i=0;i<t;i++){               /*Laço para criar a thread t vezes e dependendo do valor do indice no vetor define o gênero*/
        if(a[i] == 0){
            pthread_create(&tid[i],NULL,feminino,NULL);
        }
        else{
            pthread_create(&tid[i],NULL,masculino,NULL);
        }
    }
    for(i=0;i<t;i++){               /*Laço para criar a função que espera terminar todas as threads */
        pthread_join(tid[i],NULL);
    }
    return(0);
}
/*Fim do programa*/
