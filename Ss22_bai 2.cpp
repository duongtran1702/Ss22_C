#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct{
	char username[50];
	char password[20];
}Accounts;

int check_acc(Accounts *acc,int n,char *username){
	for(int i=0;i<n;i++){
		if(strcmp(acc[i].username,username)==0){
			return i;
			break;
		}
	}
	return -1;
}
void register_acc(Accounts *account,int *n){
	printf("Enter username:");
	char username[50];
	fgets(username,50,stdin);
	username[strcspn(username,"\n")]='\0';
	int check=check_acc(account,*n,username);
	if(check==-1){
		strcpy(account[*n].username,username);
	}
	if(check!=-1){
		printf("Account already exists!\n");
		return;
	}
	printf("Enter password:");
	char pass_1[20];
	char pass_2[20];
	fgets(pass_1,20,stdin);
	pass_1[strcspn(pass_1,"\n")]='\0';
	do{
	printf("Enter password again:");
	fgets(pass_2,20,stdin);
	pass_2[strcspn(pass_2,"\n")]='\0';
	}while(strcmp(pass_1,pass_2)!=0);
	strcpy(account[*n].password,pass_1);
	*n+=1;
}
void writeToFile(Accounts *acc,int n) {
	FILE*f=fopen("account.bin","wb");
	if(f==NULL){
		printf("Can not open file!\n");
		return;
	}
	fwrite(acc,sizeof(Accounts),n,f);
	fclose(f);
}
void Load_File(Accounts *acc,int *n){
	FILE*f=fopen("account.bin","rb");
	if(f==NULL){
		printf("Can not open file!\n");
		return;
	}
	fseek(f,0,SEEK_END);
	int size=ftell(f);
	if(size==0){
	//	printf("File is empty!\n");
		*n=0;
		fclose(f);
		return;
	}
	*n=size/sizeof(Accounts);
	rewind(f);
	fread(acc,sizeof(Accounts),*n,f);
	fclose(f);
}
void clearFile() {
    FILE *f = fopen("account.bin", "wb"); 
    if (f == NULL) {
        printf("Cannot open file to clear!\n");
        return;
    }
    fclose(f);
}

void login(Accounts *acc,int n){
	printf("Enter username:");
	char username[50];
	char password[20];
	fgets(username,50,stdin);
	username[strcspn(username,"\n")]='\0';
	int check=check_acc(acc,n,username);
	if(check!=-1){
		do{
		printf("Enter password:");
		fgets(password,20,stdin);
		password[strcspn(password,"\n")]='\0';
		}while(strcmp(acc[check].password,password)!=0);
		printf("Login successfully!\n");
	}
	if(check==-1){
		printf("Account already exists!\n");
		return;
	}
}
void print_list_acc(Accounts *acc,int n){
	printf("List:\n");
	printf("------------------------------------\n");
	for(int i=0;i<n;i++){
		printf("User name: %s\n",acc[i].username);
		printf("Password: %s\n",acc[i].password);
		printf("------------------------------------\n");
	}
}
int main(){
	Accounts acc[100];
	int n=0;
	//	clearFile();
	do{
		int choice;
		printf("Enter your choice :");
		scanf("%d",&choice);
		getchar();
		if(choice==1){
			Load_File(acc,&n);
		//	print_list_acc(acc,n);
			if(n==0){
				printf("List account is empty!\n");
				continue;
			}
			login(acc,n);
		}
		else if(choice==2){
			Load_File(acc,&n);
			register_acc(acc,&n);
			writeToFile(acc,n);
		}
		else if(choice==3){
			printf("Exit !");
			return 0;
		}
		else {
			printf("Invalid choice !\n");
		}
	}while(1);
	return 0;
}