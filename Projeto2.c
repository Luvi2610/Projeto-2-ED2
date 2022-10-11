#include <stdio.h>
#include <string.h>

struct t_livro {
    char isbn[14];
    char titulo[50];
    char autor[50];
    char ano[5];
};

//Marcadores de posição de leitura dos respectivos arquivos
struct t_header { 
    int insere;
    int busca_p;
    int busca_s;
};

struct t_indice_p {
    char isbn[14];
    int offset;
};

struct t_indice_s1 {
    char autor[50];
    int offset;
};

struct t_indice_s2 {
    char isbn[14];
    struct t_indice_s2 prox;
};

void Insere(FILE *p_ins, FILE *p_reg);

int main() {
    struct t_header header;
    int op;
    FILE *p_ins,*p_reg;

    //Inicialização dos marcadores
    header.insere = 0;
    header.busca_p = 0;
    header.busca_s = 0;
    //Inicializacao do arquivo
    p_reg = fopen("registros.bin","wb"); //arquivo de registros criado
        fwrite(&header,sizeof(struct t_header),1,p_reg);
    fclose(p_reg);

    do
    {  
        printf("Selecione uma opcao:\n1-Inserir novo registro\n");  
        scanf("%d",&op);
        switch (op)
        {
            case 1: Insere(p_ins,p_reg);  break;
            case 0: break;
        
        default: printf("Opcao invalida\n");
            break;
        }
    } while (op != 0);
}

void Insere(FILE *p_ins, FILE *p_reg) {
    struct t_livro ins;

    p_reg = fopen("registros.bin","rb");
    if(p_reg == NULL) {
        printf("Não foi possível abrir o arquivo\n");
        return;
    }

    p_ins = fopen("insere.bin","rb");
    if(p_ins == NULL) {
        printf("Não foi possível abrir o arquivo\n");
        return;
    }
    //1 - Carregar o arquivo insere em memória (vetor de struct)
        //Começar a ler do registro seguinte a marcação 

    
}