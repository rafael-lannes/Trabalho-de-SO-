#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <semaphore.h>


void *male(void *);
void *female(void *);

sem_t empty;                                /*controls access to the bathroom*/
sem_t male_mutex;                           /* mutex for male_counter*/
sem_t male_multiplex;                       /* limits # of men in the bathroom*/
int male_counter = 0;                       /* # of men in bathroom or waiting*/
sem_t female_mutex;                         /* mutex for female_counter*/
sem_t female_multiplex;                     /* limits # of women in the bathroom*/
int female_counter = 0;                     /* # of women in bathroom or waiting*/

void *male(void *param){
    int r=rand()%10;

    sem_wait(&male_mutex);
    male_counter++;
    if(male_counter == 1){
        sem_wait(&empty);                   /* make this a male bathroom or wait*/
    }
    sem_post(&male_mutex);

    sem_wait(&male_multiplex);               /* limit # of people in the bathroom*/
    printf("Rapaz entrou!\n");
    printf("Ele ficara %d segundos no banheiro. \n",r);
    sleep(r);
    printf("Rapaz Saiu!\n");
    sem_post(&male_multiplex);              /* let the next one in*/

    sem_wait(&male_mutex);
    male_counter--;
    if (male_counter == 0){
        sem_post(&empty);                   /* may become female bathroom now*/
    }
    sem_post(&male_mutex);
}

void *female(void *param){
    int r=rand()%10;

    sem_wait(&female_mutex);
    female_counter++;
    if(female_counter == 1){
        sem_wait(&empty);                   /*make this a female bathroom or wait*/
    }
    sem_post(&female_mutex);

    sem_wait(&female_multiplex);               /* limit # of people in the bathroom*/
    printf("Moça entrou!\n");
    printf("Ela ficara %d segundos no banheiro. \n",r);
    sleep(r);
    printf("Moça saiu!\n");
    sem_post(&female_multiplex);              /* let the next one in*/

    sem_wait(&female_mutex);
    female_counter--;
    if (female_counter == 0){
        sem_post(&empty);                   /* may become male bathroom now*/
    }
    sem_post(&female_mutex);
}

int main(void){
    int i;
    int x;
    int t;

    srand(time(NULL));
    int a[100]={};
    printf("Defina o numero de empregados que irao entrar no banheiro: ");
    scanf("%d",&t);

    for(i=0;i<t;i++){
        printf("0 para Moças e 1 Para Rapazes:");
        scanf("%d",&a[i]);
    }

    for(i=0;i<t;i++){
        printf("%d", a[i]);
    }
    printf("\n");

    sem_init(&empty, 0, 1);
    sem_init(&male_mutex, 0, 1);
    sem_init(&male_multiplex, 0, 3);
    sem_init(&female_mutex, 0, 1);
    sem_init(&female_multiplex, 0, 3);

    pthread_t *tid;
    tid = malloc(80*sizeof(pthread_t));

    for(i=0;i<t;i++){

        if(a[i] == 0){
            pthread_create(&tid[i],NULL,female,NULL);
        }
        else{
            pthread_create(&tid[i],NULL,male,NULL);
        }
    }

    for(i=0;i<t;i++){
        pthread_join(tid[i],NULL);
    }

    return(0);
}
