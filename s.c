#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define BUF_SIZE 1024

char **data;

int ModFile(char *name, _Bool Mode){
	FILE *f;
	char *s;
	if (Mode){
		if ((f = fopen(name,"r+")) != NULL){
			printf("For exit enter ""...""\n");
			s = (char*)malloc(BUF_SIZE);
			while (!feof(f))
				fgetc(f);
			while (strcmp(s,"...")){
				fputs(s,f);
				fputc('\n',f);
				printf(">>");
				scanf("%s",s);
			}
			free(s);
			return 0;
		}
		else{
			printf("file nof found!\n");
			return 2;
		}
	}
	return 0;
}

int decoding(char *n1, char *n2){
	FILE *f, *k, *d;
	char *name;
	int sym_d,sym_k;
	if (!((f = fopen(n1,"r")) == NULL) && !((k = fopen(n2,"r")) == NULL)){
		name=(char*)malloc(20);
		printf("Enter name your decoded file: >> ");
		scanf("%s",name);
		d = fopen(name,"w");
		free(name);
		while (EOF != (sym_d = fgetc(f))){
			sym_k=fgetc(k);
			sym_d=sym_d^sym_k;
			fputc(sym_d,d);
		}
		fclose(f);
		fclose(k);
		fclose(d);
		return 0;
	}
	else {
		printf("files not found!\n");
		return 2;
	}
}

void keygen(char *n,char *m,_Bool Mode){
	srand(time(NULL));
	if (!Mode){
		FILE *k, *f1,*e;
		int sym, key;
		k = fopen("key.txt","w+");
		f1 = fopen(n,"r");
		e = fopen(m,"w");
		while(EOF != (sym = fgetc(f1))){
			key = 0;
			while(key < 50){
				key = rand()%127;
			}
			sym = sym^key;
			fputc(key,k);
			fputc(sym,e);
		}
		fclose(f1);
		fclose(k);
		fclose(e);
		printf("file is encoded\nkey in file 'key.txt'\nencoded file in %s\n",m);
	}
	else{
		FILE *k;
		int size,i,sym;
		char *str;
		k = fopen(n,"w");
		printf("Enter size of your key:>> ");
		scanf("%d",&size);
		str=(char*)malloc(size);
		for (i=0;i<size;i++){
			sym = 0;
			while (sym<50){
				sym = rand()%127;
			}
			str[i]=(char)sym;
		}
		fputs(str,k);
		free(str);
		fclose(k);
	}
}

int encoding(char *n1, char *n2,_Bool Mode){
	FILE *f;
	if (Mode){
		if ((f = fopen(n1,"r"))==NULL){
			printf("file not found!\n");
			return 2;
		}
		else {
			keygen(n1,n2,0);
			fclose(f);
		}
		return 0;
	}
	else{
		FILE *k,*e;
		int S1,S2,sym,key;
		char *name;
		if (((f = fopen(n1,"r"))==NULL) || ((k = fopen(n2,"r"))==NULL)){
			printf("file not found!\n");
			return 2;
		}
		else{
			S1=S2=0;
			while(!feof(f)){
				fgetc(f);
				S1++;
			}
			while(!feof(k)){
				fgetc(k);
				S2++;
			}
			fclose(f);
			fclose(k);
			if (S1>=S2){
				printf("WARNING!\nsize of your key(%d) less your text(%d)! \nWante continue?(y/n): ",S2,S1);
				sym = getchar();
				if (sym != 'y')
					return 3;
				printf("wait realisation!");
			}
			else{
				f=fopen(n1,"r");
				k=fopen(n2,"r");
				name=(char*)malloc(20);
				printf("Enter name your encoding File(name<20 symbols): > ");
				scanf("%s",name);
				e = fopen(name,"w");
				free(name);
				while (EOF != (sym = fgetc(f))){
					key = fgetc(k);
					sym = sym^key;
					fputc(sym,e);
				}
				fclose(e);
				fclose(f);
				fclose(k);
			}
		}
		return 0;
	}
}

int pic(char *n){
	FILE *f;
	char buf[BUF_SIZE];
	if ((f = fopen(n,"r"))==NULL){
		printf("file not found");
		return 2;
	}
	else{
		while (!feof(f)){
			fgets(buf,sizeof(buf)-1, f);
			printf("%s",buf);
		}
		fclose(f);
		printf("\n");
	}
	return 0;
}

int cp(char *n1, char *n2){
	int i,len,count;
	char buffer[BUF_SIZE], *S;
	FILE *f;
	if ((f = fopen(n1,"r")) == NULL){
		printf("file not found!");
		return 2;
	}
	else {
		i=count=0;
		while(!feof(f)){
			fgets(buffer, sizeof(buffer)-1,f);
			len=strlen(buffer);
			S=(char*)malloc(len+1);
			strcpy(S,buffer);
			data=(char**)realloc(data,sizeof(char*));
			data[count]=S;
			count++;
		}
		fclose(f);
		f = fopen(n2,"w");
		for (i=0; i<count; i++){
			fputs(data[i],f);
			free(data[i]);
			}
		free(data);
		fclose(f);
	}
	printf("Success!\n");
	return 0;
}

int main(int argc, char **argv){
	if (argc == 1){
		printf("Soft by ghost\nver. 0.001\n\nremember, with great power comes great responsibility\n\nEnjoy!\nmore info: s -help(-h)\n");
		printf("email: romires2000@gmail.com\n");
		return 0;
	}
	if (!strcmp(argv[1],"-add")){
		int a,b;
		printf("your numbers: \nA\nB\nA + B = C\n");
		scanf("%d",&a);
		scanf("%d",&b);
		printf("\n%d + %d = %d\n",a,b,a+b);
		return 0;
	}
	if ((!strcmp(argv[1],"-help")) ||(!strcmp(argv[1],"-h"))){
		printf("s - [options]\n\t Options:\n");
		printf("\t TEST:\n\t-add - sum two numbers\n\t Veiw file:\n\t-i [file name] - open file\n\t Copy: \n\t-i [file name] - imput file\n\t-o [file name] - output file\n");
		printf("\t Encoder:\n\t-E [file name] [ecncoded file name] - encoding your file\n\t--E [file name] [key name] - encode use your key\n");
		printf("\t Decoder:\n\t-D [encoded file name] [name your key] - decoding your file\n\t-D [encoded file] - -//- use file key.txt\n");
		printf("\t Keygen:\n\t-k [name ypur key] - create key\n\t ModFile\n\t-M [name file] - add to file strings\n");
		return 0;
	}
	if (argc == 5){
		if (!strcmp(argv[1],"-i") && !strcmp(argv[3],"-o")){
			cp(argv[2],argv[4]);
			return 0;
		}
		printf("unknown parameters!\n");
		return 1;
	}
	if (argc == 3){
		if (!strcmp(argv[1],"-M")){
			ModFile(argv[2],1);
			return 0;
		}
		if (!strcmp(argv[1],"-k")){
			keygen(argv[2],NULL,1);
			return 0;
		}
		if (!strcmp(argv[1],"-i")){
			pic(argv[2]);
			return 0;
		}
		if (!strcmp(argv[1],"-D")){
			decoding(argv[2],"key.txt");
			return 0;
		}
		printf("unknown parameters!\n");
		return 1;
	}
	if (argc == 4){
		if (!strcmp(argv[1],"--E")){
			encoding(argv[2],argv[3],0);
			return 0;
		}
		if (!strcmp(argv[1],"-E")){
			encoding(argv[2],argv[3],1);
			return 0;
		}
		if (!strcmp(argv[1],"-D")){
			decoding(argv[2],argv[3]);
			return 0;
		}
	}
	printf("unknown parameters!\n");
	return 1;
}