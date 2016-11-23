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

Regras:
1 - Grupos compostos por 4 integrantes.
2 - Cada grupo deverב enviar um email para rguerra@ic.uff.br informando:
+ o nome completo de cada integrante
+ nתmero de matrםcula e email de cada um dos integrantes
+ prazo para enviar este email י FIM DE SETEMBRO.

3 - Mudanças de grupo serדo aceitas apenas caso integrantes originais abandonem a disciplina e deverדo ser notificadas antes da entrega do trabalho.

4 - Os cףdigos fontes, executבveis (compilados com gcc no linux) e a linha de comando utilizada para compilar o programa deverדo ser enviados por e-mail atי o dia 25 DE NOVEMBRO.

5 - Os trabalhos serדo apresentados na minha sala no dia 02 DE DEZEMBRO. Cada grupo receberב um slot de 15min que serב enviado por email. 

6 - Eu olharei o código com o grupo e avaliarei o programa sendo compilado e rodando. Estejam preparados, pois a nota dependerב da qualidade da apresentaחדo.
+ NֳO SE ATRASEM!!! 15min é pouco tempo.
+ A NOTA SERֱÁ INDIVIDUAL, E CADA INTEGRANTE DO GRUPO DEVERֱ CONHECER O CÓDIGO TODO.



Apresentação: 20:00h

Grupo:
Rafael de Farias Lannes 
Patrícia Martins Rocca Crestani 
Nicolas Nascimento Atmatzides
No-starve unisex bathroom problem

Texto do email enviado dia 23 nov 2016 para o professor Raphael Guerra (uff):
Olá Professor , segue em anexo os arquivos do trabalho de Sistemas operacionais. Também segue um arquivo txt com as linhas de comando juntamente com o executável e o código .c .

O Trabalho está dividido em duas partes , a parte1 se refere ao trabalho de implementação de threads e suas ids enquanto a parte2 se refere a implementação do problema de semáforos escolhido: No-starve unisex bathroom problem.

Esperamos que esteja tudo ok e aguardamos uma confirmação de recebimento se possível. 

Obrigado e tenha uma boa tarde.

Trabalho de Sistemas Operacionais
Parte01 - Criação de Threads
Parte02 - No-starve unisex bathroom problem
Grupo:
Rafael de Farias Lannes 
Patricia Martins Rocca Crestani 
Nicolas Atmatzides 
