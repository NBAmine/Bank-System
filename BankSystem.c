#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<limits.h>
typedef struct date{
    int day,mth,yr;
}date;
typedef struct {
    char fname[30],lname[30],Id[10],adr[60],acc_type[15];
    int age;
    date birth;
    long long acc_no, phone;
    float credits;
}account;
long long llong_stdin(char*);
int int_stdin(char*);
void new_customer(void);
int menu(void);
void update_info(void);
int transactions(void);
int view_account(long long);
void view_list(void);
void dlt_acc(void);
void date_stdin(account*);
int main(int argc, char const *argv[]){
    int c,exist;    long long no;    char ch[200];
    do{
        system("cls");
        c = menu();
        system("cls");
        switch (c){
            case 0:
                printf("Closing the program...");
                break;
            case 1:
                new_customer();
                break;
            case 2:
                update_info();
                break;
            case 3:
                transactions();
                break;
            case 4:
                no = llong_stdin("Enter the account number : ");
                exist = view_account(no);
                if(!exist)
                    printf("There is no account registered with the number %lld!\n",no);
                break;
            case 5:
                dlt_acc();
                break;
            case 6:
                view_list();
                break;
            default:
                printf("Choice invalid!\n");
                break;
        }
        if(c!=0){
            do{
                c = int_stdin("\n\tEnter 1 to go back to menu, 0 to exit : ");
                if(c!=0 && c!=1){
                    system("cls");
                    printf("\t\t\tInvalide!");
                }
            }while(c!=0 && c!=1);
        }
    }while(c!=0);
    return 0;
}
int menu(){
    int c;char ch[10];
    printf("\tCUSTOMER ACCOUNT BANKING MANAGEMENT SYSTEM\n\n");
    printf("\t|||||||||||||||MAIN MENU|||||||||||||||\n\n");
    printf("\t1 . Create a new account\n");
    printf("\t2 . Update information of an existing account\n");
    printf("\t3 . Transactions\n");
    printf("\t4 . Check an existing account details\n");
    printf("\t5 . Removing an existing account\n");
    printf("\t6 . View customer's list\n");
    printf("\t0 . Exit\n");
    c = int_stdin("\n\t\tChoice : ");
    return c;
}
void new_customer(){
    FILE *f;
    account acc,new;    char ch[200];   int exist;
    f = fopen("data.txt","a+");
    if(f!=NULL){
        do{
            rewind(f);
            exist=0;
            new.acc_no = llong_stdin("Enter the account number : ");
            while(fscanf(f,"%lld-%[^-]-%[^-]-%[^-]-%[^-]-%[^-]-%f-%d-%d/%d/%d-%lld%*c",&acc.acc_no,acc.fname,acc.lname,acc.Id,acc.adr,acc.acc_type,&acc.credits,&acc.age,&acc.birth.day,&acc.birth.mth,&acc.birth.yr,&acc.phone)!=EOF){
                if(acc.acc_no==new.acc_no){
                    exist = 1;
                    printf("Account number %lld already in use!\n",new.acc_no);
                }
            }
        }while(exist!=0);
        printf("Enter the first name : ");
        fgets(new.fname,30,stdin);
        new.fname[strlen(new.fname)-1]='\0';
        printf("Enter the last name : ");
        fgets(new.lname,30,stdin);
        new.lname[strlen(new.lname)-1]='\0';
        printf("Enter the ID : ");
        fgets(new.Id,10,stdin);
        new.Id[strlen(new.Id)-1]='\0';
        printf("Enter the adresse : ");
        fgets(new.adr,50,stdin);
        new.adr[strlen(new.adr)-1]='\0';
        date_stdin(&new);
        new.age = int_stdin("Enter the age : ");
        new.phone = llong_stdin("Enter the phone number : ");
        printf("Enter account type (current/fixed/savings) : ");
        fgets(new.acc_type,30,stdin);
        new.acc_type[strlen(new.acc_type)-1]='\0';
        printf("Enter the amount to deposit : ");
        fgets(ch,100,stdin);
        new.credits = strtol(ch,NULL,0);
        fprintf(f,"%lld-%s-%s-%s-%s-%s-%f-%d-%d/%d/%d-%lld\n",new.acc_no,new.fname,new.lname,new.Id,new.adr,new.acc_type,new.credits,new.age,new.birth.day,new.birth.mth,new.birth.yr,new.phone);
    }else   
        printf("Error during the procedure!\n");
    fclose(f);
}
void update_info(){
    FILE *f,*new;   long long x;     account acc;    int found=0,c,rmv,rnm;      char ch[200];
    f = fopen("data.txt","a+");
    new = fopen("file.txt","w");
    if(f!=NULL && new!=NULL){
        x = llong_stdin("Enter the account number : ");
        while(fscanf(f,"%lld-%[^-]-%[^-]-%[^-]-%[^-]-%[^-]-%f-%d-%d/%d/%d-%lld%*c",&acc.acc_no,acc.fname,acc.lname,acc.Id,acc.adr,acc.acc_type,&acc.credits,&acc.age,&acc.birth.day,&acc.birth.mth,&acc.birth.yr,&acc.phone)!=EOF){ 
            if(acc.acc_no==x){
                found = 1;
                do{
                    system("cls");
                    printf("\t||||||Updating account No %lld info||||||\n\n",x);
                    printf("\t1 . Account number\n");
                    printf("\t2 . First name\n");
                    printf("\t3 . Last name\n");
                    printf("\t4 . Id\n");
                    printf("\t5 . Adresse\n");
                    printf("\t6 . Phone number\n");
                    printf("\t0 . Exit\n");
                    c = int_stdin("\n\t\tChoice : ");
                    system("cls");
                    switch (c){
                        case 0:
                            break;
                        case 1:
                            acc.acc_no = llong_stdin("Enter new account number : ");
                            break;
                        case 2:
                            printf("Enter the new First name : ");
                            fgets(acc.fname,30,stdin);
                            acc.fname[strlen(acc.fname)-1]='\0';
                            break;
                        case 3:
                            printf("Enter the new Last name : ");
                            fgets(acc.lname,30,stdin);
                            acc.lname[strlen(acc.lname)-1]='\0';
                            break;
                        case 4:
                            printf("Enter the new Id : ");
                            fgets(acc.Id,30,stdin);
                            acc.Id[strlen(acc.Id)-1]='\0';
                            break;
                        case 5:
                            printf("Enter the new Adress : ");
                            fgets(acc.adr,60,stdin);
                            acc.adr[strlen(acc.adr)-1]='\0';
                            break;
                        case 6:
                            acc.phone = llong_stdin("Enter the new Phone number : ");
                            break;
                        default:
                            printf("Choice invalid!\n");
                            break;
                    }
                }while(c!=0);
                fprintf(new,"%lld-%s-%s-%s-%s-%s-%f-%d-%d/%d/%d-%lld\n",acc.acc_no,acc.fname,acc.lname,acc.Id,acc.adr,acc.acc_type,acc.credits,acc.age,acc.birth.day,acc.birth.mth,acc.birth.yr,acc.phone);
            }else
                fprintf(new,"%lld-%s-%s-%s-%s-%s-%f-%d-%d/%d/%d-%lld\n",acc.acc_no,acc.fname,acc.lname,acc.Id,acc.adr,acc.acc_type,acc.credits,acc.age,acc.birth.day,acc.birth.mth,acc.birth.yr,acc.phone);
        }
    }else
        printf("Error during the procedure!\n");
    fclose(new);
    fclose(f);
    if(found){
        rmv = remove("data.txt");
        rnm = rename("file.txt","data.txt");
        if(rmv == 0 && rnm == 0)
            printf("Account number %lld has been updated successfully!\n",x);
        else{
            printf("Error during the procedure!\n");
        }
    }else{
        rmv = remove("file.txt");
        printf("There is no account registered with the number %lld !\n",x);
    }
}
int transactions(){
    FILE *f,*new;   long long x;     account acc;    int c,found=0,rmv,rnm;      float amt,max;      char ch[200];
    f = fopen("data.txt","r");
    new = fopen("temp.txt","w");
    if(f!= NULL && new!=NULL){
        x = llong_stdin("Enter the account number : ");
        while(fscanf(f,"%lld-%[^-]-%[^-]-%[^-]-%[^-]-%[^-]-%f-%d-%d/%d/%d-%lld%*c",&acc.acc_no,acc.fname,acc.lname,acc.Id,acc.adr,acc.acc_type,&acc.credits,&acc.age,&acc.birth.day,&acc.birth.mth,&acc.birth.yr,&acc.phone)!=EOF){ 
            if(acc.acc_no==x){
                found = 1;
                if(strcmp(acc.acc_type,"fixed")==0){
                    printf("Cannot Deposit or Withdraw on a fixed account!\n");
                    fclose(f);
                    fclose(new);
                    return 0;
                }else{
                    max = acc.credits;
                    do{
                        system("cls");
                        printf("\t\tAccount No %lld\n",x);
                        c = int_stdin("For deposit choose 1\nFor withdraw choose 2\n\tYour choice : ");
                        if(c==1){
                            system("cls");
                            printf("\t\tAccount No %lld\n",x);
                            printf("Enter the amount to deposit : ");
                            fgets(ch,100,stdin);
                            amt = strtol(ch,NULL,0);
                            acc.credits += amt;
                        }
                        if(c==2){
                            do{
                                acc.credits = max;
                                system("cls");
                                printf("The maximum ammount you can withdraw is %f\n",acc.credits);
                                printf("\t\tAccount No %lld\n",x);
                                printf("Enter the amount to withdraw : ");
                                fgets(ch,100,stdin);
                                amt = strtol(ch,NULL,0);
                                acc.credits -= amt;
                            }while(acc.credits<0);
                        }
                    }while(c!=1 && c!= 2);
                }
            }
            fprintf(new,"%lld-%s-%s-%s-%s-%s-%f-%d-%d/%d/%d-%lld\n",acc.acc_no,acc.fname,acc.lname,acc.Id,acc.adr,acc.acc_type,acc.credits,acc.age,acc.birth.day,acc.birth.mth,acc.birth.yr,acc.phone);
        }
    }else
        printf("Error during the procedure!\n");
    fclose(f);
    fclose(new);
    if(found){
        rmv = remove("data.txt");
        rnm = rename("temp.txt","data.txt");
        if(rmv == 0 && rnm == 0)
            printf("Transaction has been performed successfully!\n");
        else
            printf("Error during the procedure!\n");
    }else{
        rmv = remove("temp.txt");
        printf("There is no account registered with the number %lld !\n",x);
    }
}
int view_account(long long x){
    FILE *f = fopen("data.txt","r");    account acc;    int found=0;
    if(f!=NULL){
        while(fscanf(f,"%lld-%[^-]-%[^-]-%[^-]-%[^-]-%[^-]-%f-%d-%d/%d/%d-%lld%*c",&acc.acc_no,acc.fname,acc.lname,acc.Id,acc.adr,acc.acc_type,&acc.credits,&acc.age,&acc.birth.day,&acc.birth.mth,&acc.birth.yr,&acc.phone)!=EOF){
            if(x==acc.acc_no){
                printf("\tAccount No : %lld\n",acc.acc_no);
                printf("First name : %s\nLast name : %s\n",acc.fname,acc.lname);
                printf("ID : %s\nAccount type : %s\n",acc.Id,acc.acc_type);
                printf("Balance : %f\n",acc.credits);
                printf("Birthday : %d/%d/%d\nAge : %d\n",acc.birth.day,acc.birth.mth,acc.birth.yr,acc.age);
                printf("Adresse : %s\nPhone : %lld\n",acc.adr,acc.phone);
                fclose(f);
                return 1;
            }
        }
        fclose(f);
        return 0;
    }else   
        printf("Error during the procedure!\n");
    fclose(f);
}
void view_list(){
    FILE *f = fopen("data.txt","r");    account acc;
    if(f!=NULL){
        while(fscanf(f,"%lld-%[^-]-%[^-]-%[^-]-%[^-]-%[^-]-%f-%d-%d/%d/%d-%lld%*c",&acc.acc_no,acc.fname,acc.lname,acc.Id,acc.adr,acc.acc_type,&acc.credits,&acc.age,&acc.birth.day,&acc.birth.mth,&acc.birth.yr,&acc.phone)!=EOF){
            printf("\tAccount No : %lld\n",acc.acc_no);
            printf("First name : %s\nLast name : %s\n",acc.fname,acc.lname);
            printf("ID : %s\nAccount type : %s\n",acc.Id,acc.acc_type);
            printf("Balance : %f\n",acc.credits);
            printf("Birthday : %d/%d/%d\nAge : %d\n",acc.birth.day,acc.birth.mth,acc.birth.yr,acc.age);
            printf("Adresse : %s\nPhone : %lld\n\n",acc.adr,acc.phone);
        }    
    }else   
        printf("Error during the procedure!\n");
    fclose(f);
}
void dlt_acc(){
    FILE *f,*new;   account acc;    long long x;     char ch[200];   int found=0,rmv,rnm;
    f = fopen("data.txt","r");
    new=fopen("new.txt","w");
    if(f!=NULL && new!=NULL){
        x = llong_stdin("Enter the account number : ");
        while(fscanf(f,"%lld-%[^-]-%[^-]-%[^-]-%[^-]-%[^-]-%f-%d-%d/%d/%d-%lld%*c",&acc.acc_no,acc.fname,acc.lname,acc.Id,acc.adr,acc.acc_type,&acc.credits,&acc.age,&acc.birth.day,&acc.birth.mth,&acc.birth.yr,&acc.phone)!=EOF){
           if(acc.acc_no==x){
                found = 1;
            }else
                fprintf(new,"%lld-%s-%s-%s-%s-%s-%f-%d-%d/%d/%d-%lld\n",acc.acc_no,acc.fname,acc.lname,acc.Id,acc.adr,acc.acc_type,acc.credits,acc.age,acc.birth.day,acc.birth.mth,acc.birth.yr,acc.phone);
        }
    }else   
        printf("Error during the procedure!\n");
    fclose(f);
    fclose(new);
    if(found){
        rmv = remove("data.txt");
        rnm = rename("new.txt","data.txt");
        if(rmv == 0 && rnm == 0)
            printf("Account number %lld has been deleted successfully!\n",x);
        else
            printf("Error during the procedure!\n");
    }else{
        rmv = remove("new.txt");
        printf("There is no account registered with the number %lld !\n",x);
    }
}
long long llong_stdin(char *str){
    char ch[200],*endch;    long long x;    int OutRng,NoLlong;
    do{
        printf("%s",str);
        fgets(ch,200,stdin);
        x = strtoll(ch,&endch,0);
        if(endch!=ch){
            NoLlong = 0;
            if(x==LLONG_MAX || x<=0){
                printf("\t\tOut of range!!\n");
                OutRng = 1;
            }else
                OutRng = 0;
        }else
            NoLlong=1;    
    }while(NoLlong == 1 || OutRng == 1);
    return x;
}
int int_stdin(char *str){
    char ch[200],*endch;    int OutRng,NoLlong;     long x;
    do{
        printf("%s",str);
        fgets(ch,200,stdin);
        x = strtoll(ch,&endch,0);
        if(endch!=ch){
            NoLlong = 0;
            if(x>INT_MAX || x<INT_MIN){
                printf("\t\tOut of range!!\n");
                OutRng = 1;
            }else
                OutRng = 0;
        }else
            NoLlong=1;    
    }while(NoLlong == 1 || OutRng == 1);
    return x;
}
void date_stdin(account *acc){
    char ch[100];   int OutRng;
    do{
        OutRng=0;
        acc->birth.day = int_stdin("Enter day of birth : ");
        if(acc->birth.day >31 || acc->birth.day <= 0){
            OutRng = 1;
            printf("\t\tOut of range!!\n");
        }
    }while(OutRng);
    do{
        OutRng=0;
        acc->birth.mth = int_stdin("Enter mounth of birth (digits) : ");
        if(acc->birth.mth >12 || acc->birth.mth <= 0){
            OutRng = 1;
            printf("\t\tOut of range!!\n");
        }
    }while(OutRng);
    do{
        OutRng=0;
        acc->birth.yr = int_stdin("Enter year of birth : ");
        if(acc->birth.yr <= 0){
            OutRng = 1;
            printf("\t\tOut of range!!\n");
        }
    }while(OutRng);
}