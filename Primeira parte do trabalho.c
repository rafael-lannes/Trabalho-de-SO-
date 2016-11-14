#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/syscall.h>

void *info(int n){
    int id,id2;/* variavel que recebe a id da thread de ambas funções*/
    n=n+1;/*recebe o numero i do laço for e soma 1 para dizer o numero da thread*/
    id=pthread_self();/*função que fornece o id atribuido pela implemengtação*/
    id2=syscall(SYS_gettid);/*função que fornece o id atribuido pelo kernel*/
    printf("Eu sou thread %i e meu ID(pthread_self) é %u e meu ID (gettid) é %u \n",n,id,id2);
    return 0;
}


int main(){
    int i;
    int q; /*numero de threads*/
    printf("Insira a quantidade de threads que deseja criar:\n");
    scanf("%i",&q);/*recebe o numero de threads*/
    pthread_t tid[q];/*Declara as threads na quantidade desejada q*/
    for(i=0;i<q;i++){/*Laço For para criar N threads*/
        pthread_create(&tid[i],NULL,info,i);/*Cria a Thread*/
        pthread_join(tid[i],NULL);/*espera o fim da thread*/
    }
 /*   for(i=0;i<q;i++){
        pthread_join(tid[i],NULL);
    }*/
    return 0;
}
