#include<stdio.h>

void print_sth(char *str){
 printf("%s\n",str);
}

int main(){

 char *name = "Peter Munene";
 print_sth(name);

 printf("%p\n",name);

 printf("Hello World\n");
 return  0;
}
