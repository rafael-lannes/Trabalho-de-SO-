# Trabalho-de-SO-
Trabalho de Sistemas Operacionais 2016.2 UFF
__________________________________________________________________________________________________________________________________________
Regras do Trabalho:
parte 1

1 - Faça um programa que crie N threads (N é um dado de entrada lido do teclado). A primeira thread criada é a "thread01", a segunda é a "thread02", e assim por diante. Cada thread, quando executar, deverá imprimir na tela "Eu sou a threadXX e meu ID é YY", onde YY é o ID que o sistema operacional dá para a thread (tipo pthread_t, primeiro campo da função pthread_create). Explique as saídas do programa quando este é executado. NãO USE VARIáVEIS GLOBAIS!!!

Dica 1: para imprimir uma variável do tipo pthread_t use %u.  
Dica 2: quando criar uma thread "threadXX", passe este valor como parâmetro para ela.
Dica 3: pegue a ID da thread usando a função pthread_self().

2 - Tanto pthread_self() quanto gettid() retornam o ID da thread. Altere o programa do exercício 1 para imprimir a ID da thread usando ambas funções. Elas retornam o mesmo valor? Se não, pesquise qual a diferença entre elas.
__________________________________________________________________________________________________________________________________________
parte 2
>Envolverá Criar threads em C no linux com biblioteca “pthreads”
>Material sobre pthreads no site e no google
>Criar processos 
>Fazer alguns experimentos

Problema escolhido foi:
+ No-starve unisex bathroom problem

From little book of semaphores(Página 170 - Solução na página 177):
I wrote this problem when a friend of mine left her position teaching physics at Colby College and took a job at Xerox. She was working in a cubicle in the basement of a concrete monolith, and the nearest women’s bathroom was two ﬂoors up. She proposed to the Uberboss that they convert the men’s bathroom on her ﬂoor to a unisex bathroom, sort of like on Ally McBeal. The Uberboss agreed, provided that the following synchronization constraints can be maintained:
• There cannot be men and women in the bathroom at the same time.
• There should never be more than three employees squandering company time in the bathroom.

#　　　　/)─―ヘ/) 
#　　＿／　　　　＼ 
#　／　　　　●　　●丶 
#｜　　　　　　　▼　| 
#｜　　　　　　　亠ノ 　 
#U￣U￣￣￣￣U￣
