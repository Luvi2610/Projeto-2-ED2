#include <stdio.h>
#include <string.h>

struct t_livro {
    char isbn[14];
    char titulo[50];
    char autor[50];
    char ano[5];
} livro;

void Insere(FILE *p_ins, FILE *p_reg);
// void Remove();
// void Compacta();

int main() {
    int header = -1;
    int op;
    FILE *p_ins,*p_reg,*p_rem;
    
    //Inicializacao do arquivo
    p_reg = fopen("registros.bin","wb"); //arquivo de registros criado
        fwrite(&header,sizeof(int),1,p_reg);
    fclose(p_reg);


    do
    {  
        printf("Selecione uma opcao:\n1-Inserir novo registro\n2-Remover registro\n3-Compactar o arquivo\n");  
        scanf("%d",&op);
        switch (op)
        {
            case 1: Insere(p_ins,p_reg);  break;
            //case 2: Remove(); break;
            //case 3: Compacta(); break;
            case 0: break;
        
        default: printf("Opcao invalida\n");
            break;
        }
    } while (op != 0);
}

void Insere(FILE *p_ins, FILE *p_reg) {
    char formatado[118];
    int header;
    int tam;

    //Abre o arquivo registros.bin
    p_reg = fopen("registros.bin","rb");
    if(p_reg == NULL) {
        printf("Não foi possível abrir o arquivo\n");
        return;
    }

    fread(&header,sizeof(int),1,p_ins); //Guarda o valor do header em memória

    p_ins = fopen("insere.bin","rb");
    if(p_ins == NULL) {
        printf("Não foi possível abrir o arquivo\n");
        return;
    }

    fread(&livro,sizeof(livro),1,p_ins); 
    sprintf(formatado,"%s#%s#%s#%s",livro.isbn,livro.titulo,livro.autor,livro.ano);

    if(header == -1) {

    }

    //Condicional envolvendo o header do registros
    //Se o mesmo for -1, ele insere no final, caso contrário add no offset correspondente

    

    printf("%s",formatado);
    
    tam = strlen(formatado) + 1;

    fclose(p_ins);
    p_ins = fopen("registros.bin","wb");

    fseek(p_ins,sizeof(int),0);

    fprintf(p_ins,"%d",tam);
    fprintf(p_ins,"%s",formatado);

    fclose(p_ins);
    
    
}