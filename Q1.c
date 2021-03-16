#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

//taking +ve as 1 and -ve as 0
typedef enum{negative,positive} sign;


typedef struct int1024_t{
    char *data;
    int size;
    sign s;
}Big_int;



void string_to_big_int(char *num,Big_int **num_ptr)
{
    int i=0;//for iterating the given string
    int j;//for storing in the big_int
    //allocating memory
    (*num_ptr)=(Big_int*)malloc(sizeof(Big_int));
	
	//checking if the the given number is positive or negative
	//"-23566"
    if(num[i]=='-')
    {
        (*num_ptr)->s=negative;
        i++;
    }
    else
    {
        (*num_ptr)->s=positive;
        
    }
    //for numbers of type "00000002563"
    
    while(num[i] == '0')
    {
        i++;
    }
    (*num_ptr)->size=strlen(num)-i;
    
    //to crct user error in giving input
    if((*num_ptr)->size==0)
    {
        (*num_ptr)->data = (char*)malloc(sizeof(char)*2);
        (*num_ptr)->size++;
        (*num_ptr)->data[0]='0';
        (*num_ptr)->data[1]='\0';
    }
    else
    {
    	//creating with one extra size for NULL character to act as strings
        (*num_ptr)->data=(char*)malloc(sizeof(char)*((*num_ptr)->size+1));
       
        (*num_ptr)->data[(*num_ptr)->size]='\0';
        
        //
        for(j=0;j<(*num_ptr)->size;j++,i++)
        {
            (*num_ptr)->data[j]=num[i];
        }
    }
}

void add_big_int(Big_int **n1_ptr,Big_int **n2_ptr)
{
    //maximum number that can be obtained is length of bigger number+1 
    //creating with one extra size for NULL character to act as strings
    int max_size=((*n1_ptr)->size>(*n2_ptr)->size)?((*n1_ptr)->size+2):((*n2_ptr)->size+2);

    //allocating memory
    
    Big_int *ans=(Big_int*)malloc(sizeof(Big_int));
    
	ans->data=(char*)malloc(sizeof(char)*max_size);
	
    ans->s=(*n1_ptr)->s;//only taking sign of first number as sign of answer

    ans->size=max_size-1;

    ans->data[max_size-1]='\0';

    int i=(max_size-2);
    int j=(*n1_ptr)->size-1;
    int k=(*n2_ptr)->size-1;

    int temp1;
    int temp2;
    int sum=0;
    int carry=0;


    while( j>=0 || k>=0 )
    {
        temp1=0;
        temp2=0;
        if(j>=0)
        {
            temp1 = ( ((int)(*n1_ptr)->data[j--]) - 48) ;
        }
        if(k>=0)
        {
            temp2 = ( ((int)(*n2_ptr)->data[k--]) - 48) ;
        }

        sum = (temp1+temp2)+carry;

        ans->data[i]=(char)((sum%10)+48);
        carry=(sum/10!=0)?1:0;

        i--;

    }
	/*
	  carry(1) 95
	     	+ 356
		   --------
		      451
	*/
    ans->data[0]=(char)(carry+48);
    
    //checking if sign of answer is negative
    if(ans->s==negative)
    {
    	printf("-");
	}

	printf("%s",ans->data);
	
	//free the memory
    free(ans->data);
    free(ans);
}
void subtract_big_int(Big_int **n1_ptr,Big_int **n2_ptr)
{
    int max_size=((*n1_ptr)->size>(*n2_ptr)->size)?((*n1_ptr)->size+1):((*n2_ptr)->size+1);
    
    Big_int *ans=(Big_int*)malloc(sizeof(Big_int));
    
	ans->data=(char*)malloc(sizeof(char)*max_size);
	
    ans->size=max_size-1;


    ans->data[ans->size]='\0';

    int i=(max_size-2);
    int j=(*n1_ptr)->size-1;
    int k=(*n2_ptr)->size-1;

    int temp1;
    int temp2;
    int sum=0;
    int carry=0;

    while( j>=0 || k>=0 )
    {
        temp1=0;
        temp2=0;
        if(j>=0)
        {
            temp1 = ( ((int)(*n1_ptr)->data[j--]) - 48) ;
        }
        if(k>=0)
        {
            temp2 = 9-(((int)(*n2_ptr)->data[k--])-48);
        }

        sum = (temp1+temp2)+carry;

        carry=(sum/10!=0)?1:0;
        ans->data[i]=(char)((sum%10)+48);
        
        i--;
    }
	int temp_sum=0;
	int temp_carry=0;
	i=(max_size-2);
	
    if(carry==1)
    {
    	temp_sum = ((int)ans->data[i]-48)+temp_carry+1;//for base case
    	temp_carry=(temp_sum/10!=0)?1:0;
    	ans->data[i]=(char)((temp_sum%10)+48);
    	i--;
    	while(ans->data[i]>=0&&temp_carry)
    	{
    		temp_sum = ((int)ans->data[i]-48)+temp_carry;
			carry=(sum/10!=0)?1:0;
    		ans->data[i]=(char)((temp_sum%10)+48);
    		i--;
		}
        ans->s=positive;
    }
    else
    {
    	while(ans->data[i]>=0)
    	{
    		temp_sum = 9-((int)ans->data[i]-48);
    		ans->data[i]=(char)(temp_sum+48);
    		i--;
		}
    	ans->s=negative;
	}
	//checking if sign of answer is negative
	if(ans->s==negative)
    {
    	printf("-");
	}
	//printing the answer
	printf("%s",ans->data);
	
    
}
void multi_of_big_int(Big_int **n1_ptr,Big_int **n2_ptr)
{
	int max_size=((*n1_ptr)->size+(*n2_ptr)->size)+1;
	
    //allocating memory
    Big_int *ans=(Big_int*)malloc(sizeof(Big_int));
	ans->data=(char*)malloc(sizeof(char)*max_size);
    //To store in string 
    char *str=(char*)malloc(sizeof(char)*max_size);

    //if both numbers have same sign multiplication is +ve otherwise -ve
    ans->s=((*n1_ptr)->s==(*n2_ptr)->s)?positive:negative;
	
    ans->size=max_size-1;

	ans->data[ans->size]='\0';

	int i, j;

    //To store len of two strings 
	int len1=(*n1_ptr)->size;
    int len2=(*n2_ptr)->size;
    
    
    int temp1;
    int temp2;
    int carry=0;

    int m, n, sum;
    int str_len=0;
    int postion;

    //iterating from backside
    for(i = len1 - 1; i >= 0 ; i--) 
    {
        for(j = len2 - 1; j >= 0; j--) 
        {
            //converting string to numbers
            temp1 = ((int)(*n1_ptr)->data[i] - 48);
            temp2 = ((int)(*n2_ptr)->data[j] - 48);
            /* 
              (n2) 256 * 356 (n1)
                  ------------
                      1536
                     1280
                     768
                  ------------
                     91136   
            */                                  
            if(i == len1 - 1) 
            {
                str[str_len]=(char)(((temp1*temp2 + carry)%10)+48);
                carry = (temp1*temp2 +carry )/10;
                str_len++;
            } 
            else 
            {
                //for adding to the previous result
                postion = (len1 - 1 - i) + (len2 - 1 - j);
                if(postion < str_len) 
                {
                    sum = ((int)(str[postion])-48) + temp1*temp2 + carry;

                    str[postion]= (char)((sum%10)+48);

                    carry = sum/10;
                } 
                else 
                {
                    sum = temp1*temp2 + carry;

                    str[str_len]=(char)((sum%10)+48);

                    carry = sum/10;

                    str_len++;
                }
            }
        }
        if(carry) 
        {
            str[str_len]=(char)(carry+48);
            str_len++;
            carry = 0;
        }
    }
    
    for( i= str_len-1,j=0; i >= 0; i--,j++) 
    {
        ans->data[j]=str[i];
    }
    
    printf("\nProduct of two numbers is: ");
    //checking if sign of answer is negative
    if(ans->s==negative)
    {
    	printf("-");
	}
	
	printf("%s",ans->data);
	
    //free the memory
    free(str);
}

int main()
{
    //unsigned 1024 bits can maximum represent a decimal number maximum of 309 digits 
    
    char num1[310];
    char num2[310];
    
    printf("Enter first number:\n");
    scanf("%s", num1);

    printf("\nEnter second number:\n");
    scanf("%s", num2);

    Big_int *n1;
    Big_int *n2;
    
    string_to_big_int(num1,&n1);
    string_to_big_int(num2,&n2);
    
    //if both have same sign either +ve or -ve
    if(n1->s==n2->s)
    {
        printf("sum of two numbers:");
        add_big_int(&n1,&n2);
		
		//(-n1)-(-n2)=(-1)(n1-n2)<--->(n1->s)(n1-n2)
        printf("\nDifference of two numbers :");
        subtract_big_int(&n1,&n2);
    }
    else if(n1->s==positive)//if n1 is +ve and n2 is -ve
    {
        //n1+(-n2)==n1-n2;
        printf("Sum of two numbers is:");
        subtract_big_int(&n1,&n2);

        //n1-(-n2)==n1+n2;
        printf("\nDifference of two numbers :");  
        add_big_int(&n1,&n2);
    }
    else if(n2->s==positive)
    {
        //(-n1)+n2==n2-n1
        printf("Sum of two numbers is:");
        subtract_big_int(&n2,&n1);

        //(-n1)-(n2)==-(n1+n2)<---->(n1->s)(n1-n2)
        printf("\nDifference of two numbers :");  
        add_big_int(&n1,&n2);
    }

    //multipliaction of big int
    multi_of_big_int(&n1,&n2);
    
    return 0;
}
