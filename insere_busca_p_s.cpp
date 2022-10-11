#include<stdio.h>
#include<conio.h>

int main() {
    FILE *fd;
    
    //////////////////////////////
    struct livro {
        char isbn[14];
        char titulo[50];
        char autor[50];
        char ano[5];
    } vet[5] = {{"3333333333333", "TiT-3", "Autor-A-1.3", "3333"},
                {"2222222222222", "TiT-2", "Autor-B", "2222"},                
                {"1111111111111", "TiT-1", "Autor-A-1.3", "1111"},                
                {"6666666666666", "Titulo-6", "Autor-A-1.3", "6666"},                
                {"5555555555555", "T-5", "Autor-B", "5555"},
                
                };
       
    fd = fopen("insere.bin", "w+b");
    fwrite(vet, sizeof(vet), 1, fd);
    fclose(fd);
    
    //////////////////////////////
	struct busca_p {
        char isbn[14];
    } vet_bp[7] = {{"3333333333333"},
                   {"2222222222222"},
                   {"7777777777777"},
                   {"2222222222222"},
                   {"6666666666666"},
                   {"2222222222222"},
                   {"6666666666666"}};
       
    fd = fopen("busca_p.bin", "w+b");
    fwrite(vet_bp, sizeof(vet_bp), 1, fd);
    fclose(fd);
    
    //////////////////////////////
	const int quantidade = 8;
    char nomes[quantidade][50] = {"Autor-A-1.3", "Autor-B", "Autor-A-1.3", "Autor-B", "Autor-X", "Autor-A-1.3", "Autor-B", "Autor-X"};
       
    fd = fopen("busca_s.bin", "w+b");
    for (int i=0; i<quantidade; i++)
       fwrite(nomes[i], sizeof(char), 50, fd);
    fclose(fd);
    
    /*char buffer[50];
    fd = fopen("busca_s.bin", "r+b");
    for (int i=0; i<quantidade; i++)
       {
         fread(buffer, sizeof(buffer), 1, fd);
         printf("\n%s",buffer);
       }
    fclose(fd);
    getch();*/
}
