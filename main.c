#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<math.h>
#include<ctype.h>

typedef struct
{float data;
struct node *next;
}nodechar;
nodechar*newnodechar(float  x)
{nodechar*n=malloc(sizeof(nodechar));
n->data=x;
n->next=NULL;
return n;

}
typedef struct
{
    nodechar*top;

}stackchar;
stackchar *initchar()
{
    stackchar*s=malloc(sizeof(stackchar));
    s->top= NULL;
    return s;
}
void pushchar(stackchar*s,float x)
{nodechar*p=newnodechar(x);
p->next=s->top;
s->top=p;

}
float popchar(stackchar*s)
{nodechar*temp=s->top;
float data=s->top->data;
s->top=s->top->next;
free(temp);
return data;
}

float peekchar(stackchar*s)
{
   return s->top->data;

}
int isEmptychar(stackchar *s)
{
    if(s->top==NULL)
        return 1;
    return 0;
}
void display(stackchar*s) {
  nodechar*temp=s->top;
  printf("\nDisplay Stack :  \n");
  while (temp != NULL) {
    printf(" %f ", temp->data);
    temp = temp -> next;
  }
}
int order(char op)
{
    if(op=='^')
        return 3;
        if(op=='-'||op=='+'||op=='%')
            return 1;
          if(op=='*'||op=='/')
            return 2;
          return 0;

}
int isoperator(char e)

{

     if(e == '+' || e == '-' || e == '*' || e == '/' || e == '%'||e=='^')

          return 1;



          return 0;

}

char* infixToPostfix(char *in)
{
    char *result=malloc(strlen(in));


    stackchar*st=initchar();
    char* token = strtok(in," ");
    int i=0;
    int j=0;
    int k=0;
    char z;
   char w;
         while (token != NULL) {if(i==0&&strlen(token)>1||i==0&&isdigit(token[0]))
         {strcpy(result,token);
         strcat(result," ");
        j++;}
        else if(strlen(token)>1&&i!=0)
        {
            strcat(result,token);
             strcat(result," ");
        }
         else if(strlen(token)==1&&j!=0||strlen(token)==1&&j==0)
         {
             if( isdigit(token[0]))
             {
                 strncat(result, &token[0], 1);
                 strcat(result," ");
             }
             else if(isoperator(token[0]))
             {if(isEmptychar(st))
             pushchar(st,token[0]);
             else{if(order(peekchar(st))<order(token[0]))
                  pushchar(st,token[0]);
            else
                {
                    while(!isEmptychar(st)&&order(peekchar(st))>=order(token[0]))
                {
                    z=popchar(st);
                     strncat(result, &z, 1);
                    strcat(result," ");

                }
                 pushchar(st,token[0]);
            }
             }
             }
             else if(token[0]=='('&&i!=0||i==0&&token[0]=='(')
             {  if(j==0)
                {   pushchar(st,token[0]);
                    token = strtok(NULL," ");
                i=0;

                 continue;

                }

                 else
              pushchar(st,token[0]);

             }
            else if(token[0]==')'){
                while(!isEmptychar(st)&&peekchar(st)!='(')
                {
                    w=popchar(st);
                     strncat(result, &w, 1);
                      strcat(result," ");
                }
                popchar(st);
            }

         }



               i++;
                token = strtok(NULL," ");
}
while(!isEmptychar(st))
{z=popchar(st);

if(isEmptychar(st))
 strncat(result, &z, 1);
 else{strncat(result, &z, 1);
  strcat(result," ");}
}
return result;
}

float evaluatePostfix(char* postfix)
{ stackchar *s=initchar();
    int i;
 char *token=strtok(postfix," ");
    while(token!=NULL)
        {
       if(isdigit(*token))
         {pushchar(s,atof(token));
         }
         else if (strlen(token)>1)
         { float k =atof(token);
             pushchar(s,k);
         }
        else
        {
            float n=popchar(s);
            float  m=popchar(s);
           if(*token=='+')
                { float x=n+m;
                    pushchar(s,x);
                }
            else if(*token=='-')
                { float x=m-n;
                    pushchar(s,x);
                }
            else if(token=='*')
                { float x=n*m;
                    pushchar(s,x);
                }
            else if(*token=='/')
                {float x=m/n;
                    pushchar(s,x);
                }
               else if (*token=='^')
            {
                float x=pow(m,n);
                pushchar(s,x);
            }
        }
   token=strtok(NULL," ");
        }
 return popchar(s);
}

void replaceNewLineBySpace(char *s)
{
    char *s1 = s;
    while((s1 = strstr(s1, "\n")) != NULL)
        *s1 = ' ';
}

int main()
{
   char infixExpr[256] = "";

    printf("Enter an expression you want to evaluate or Ctrl+Z to exit: ");
    while(fgets(infixExpr, 255, stdin) != NULL)
    {
        replaceNewLineBySpace(infixExpr);
        char*postfix=infixToPostfix(infixExpr);
        printf("Postfix : %s\n", postfix);
        float result = evaluatePostfix(postfix);
        printf("Result: %f\n\n", result);
        printf("Enter an expression you want to evaluate or Ctrl+Z to exit: ");
    }
  return 0;

}
