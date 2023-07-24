# Vector_Lib_C
Criando uma biblioteca em C que implementa o Vector utilizado no C++ para fins de estudo.

O Vector foi implementado de duas formas diferentes, uma utilizando array estático e outra utilizando lista duplamenta ligada. Cada uma das implementações possui uma pasta respectiva para si, cada pasta possui um arquivo cabeçalho .h responsável pelas assinaturas da função, um .c que possui a implementação das funções e um arquivo main.c que foi utilizado para fins de testes. Juntamente, foi adicionado um arquivo na linguagem C++ que foi utilizado para criar diversos arquivos de testes. 

Para compilar o código, utilizamos o comando:
```c
gcc -Wall -o "nomeDoExecutavel" "nomeDoArquivo.c" "main.c"
```

Como exemplo, utilizaremos a parta da lista duplamente ligada:
```c
gcc -Wall -o testeListaLigado vetorDinamicoLL.c main.c
```
