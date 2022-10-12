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
    int offset;
};

int vet = 5;
void Insere(FILE *p_ins, FILE *p_reg,FILE *p_indice_p,FILE *p_indice_s1, FILE *p_indice_s2);

int main() {
    struct t_header header;
    int op;
    FILE *p_ins,*p_reg,*p_indice_p,*p_indice_s1,*p_indice_s2,*busca_p,*busca_s;

    //Inicialização dos marcadores
    header.insere = 1;
    header.busca_p = 1;
    header.busca_s = 1;
    //Inicializacao do arquivo

    p_reg = fopen("registros.bin","r+b"); 
    if(p_reg == NULL) {
        p_reg = fopen("registros.bin","wb");
        fwrite(&header,sizeof(struct t_header),1,p_reg); //Adiciona o header
    }
    fclose(p_reg);
    
    p_indice_p = fopen("indice_p.bin","r+b"); 
    if(p_indice_p == NULL) 
       p_indice_p = fopen("indice_p.bin","wb"); 
    fclose(p_indice_p);
    
    p_indice_s1 = fopen("indice_s1.bin","r+b"); 
    if(p_indice_s1 == NULL) 
        p_indice_s1 = fopen("indice_s1.bin","wb");
    fclose(p_indice_s1);
    
    p_indice_s2 = fopen("indice_s2.bin","r+b"); 
    if(p_indice_s2 == NULL) 
        p_indice_s2 = fopen("indice_s2.bin","wb");
    fclose(p_indice_s2);

    do
    {  
        printf("Selecione uma opcao:\n1-Inserir novo registro\n0-Sair\n");  
        scanf(" %d",&op);
        switch (op)
        {
            case 1: Insere(p_ins,p_reg,p_indice_p,p_indice_s1,p_indice_s2);  break;
            case 0: break;
        
        default: printf("Opcao invalida\n");
            break;
        }
    } while (op != 0);
}

void Insere(FILE *p_ins, FILE *p_reg,FILE *p_indice_p,FILE *p_indice_s1, FILE *p_indice_s2) {
    struct t_livro ins[vet];
    struct t_header header;
    struct t_indice_s1 indice_s1;
    struct t_indice_s2 indice_s2;

    char formatado[118],autor[50];
    int i,pos_ant,tam,existe=0,pos_fin;

    p_reg = fopen("registros.bin","r+b");
    p_ins = fopen("insere.bin","rb");
    p_indice_p = fopen("p_indice_p.bin","r+b");
    p_indice_s1 = fopen("p_indice_p.bin","r+b");
    p_indice_s2 = fopen("p_indice_p.bin","r+b");

    fread(&header,sizeof(header),1,p_reg);
    i = header.insere - 1;
    fread(&ins,sizeof(ins),1,p_ins);

    
    sprintf(formatado,"%s#%s#%s#%s",ins[i].isbn,ins[i].titulo,ins[i].autor,ins[i].ano);
    tam = strlen(formatado);

    //Insere no arquivo de registros
    fseek(p_reg,1,SEEK_END); 
    fwrite(&tam,sizeof(int),1,p_reg);
    fwrite(formatado,strlen(formatado),1,p_reg);
    
    //Insere no arquivo de chaves primárias
    fseek(p_indice_p,1,SEEK_END); 
    fwrite(ins[i].isbn,sizeof(ins[i].isbn),1,p_indice_p);
    fwrite(&i,sizeof(int),1,p_indice_p);

    //Insere no arquivo de autores
    while(fread(&indice_s1,sizeof(indice_s1),1,p_indice_s1)) {
        if(strcmp(indice_s1.autor,ins[i].autor) == 0) {
            fseek(p_indice_s2,indice_s1.offset,SEEK_SET);

            fread(&indice_s2,sizeof(indice_s2),1,p_indice_s2);
            while (indice_s2.offset != -1){
                fseek(p_indice_s2,indice_s2.offset,SEEK_SET);
                fread(&indice_s2,sizeof(indice_s2),1,p_indice_s2);
            }
            pos_ant = ftell(p_indice_s2);
            fseek(p_indice_s2,1,SEEK_END);

            fwrite(ins[i].isbn,sizeof(ins[i].isbn),1,p_indice_s2); 
            fwrite(-1,sizeof(int),1,p_indice_s2);
            fseek(p_indice_s2,-sizeof(indice_s2),SEEK_CUR);
            pos_fin = ftell(p_indice_s2);

            fseek(p_indice_s2,pos_ant,SEEK_SET);
            fseek(p_indice_s2,-sizeof(int),SEEK_CUR);
            fwrite(pos_fin,sizeof(int),1,p_indice_s2);

            existe = 1;
            break;
        }

    }

    if(!existe) {
        fseek(p_indice_s1,1,SEEK_END); //Vai até o final do arquivo de autores
        fwrite(ins[i].autor,sizeof(autor),1,p_indice_s1);

        fseek(p_indice_s2,1,SEEK_END); //Vai até o final do arquivo de listas de obras
        fwrite(ins[i].isbn,sizeof(int),1,p_indice_s2);
        fwrite(-1,sizeof(int),1,p_indice_s2);

        fwrite(ftell(p_indice_s2),sizeof(int),1,p_indice_s1);//Adiciona a cabeça da lista de obras depois do autor
    }   
    

    //Insere na lista ligada de obras 


    //Ordena os arquivos de indice com Keysorting 
    
    fclose(p_reg);
    fclose(p_ins);
}