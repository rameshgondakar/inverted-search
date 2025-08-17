#include<stdio.h>
#include<string.h>
#include"main.h"

int file_validate(int argc, char *argv[])
{
    FILE *fptr;
	
    if(argc > 1)     //check arguments more than one 
    {
	for(int i=1;i<argc;i++)
	{
	    if(strstr(argv[i],".txt")==0)   //file is .txt file or not
	    {
		printf("[ %s ] => File is not a .txt file arg[%d]\n\n",argv[i],i);
		argv[i] = NULL;
	    }

	    if(argv[i] != NULL)
	    {
	        fptr=fopen(argv[i],"r"); 
	        if(fptr == NULL)
	        {
		    printf("[ %s ] => FILE NOT EXIST arg[%d]\n\n",argv[i],i);
		    argv[i] = NULL ;
	        }
	        else if(fptr != NULL)
	        {
	            fseek(fptr,0,SEEK_END);
	            if(ftell(fptr)==0)    //file empty or not
	            {
	 	        printf("[ %s ] => File is Empty file  arg[%d]\n\n",argv[i],i);
		        argv[i]= NULL;
	            } 
	        }
	    }
	}
	return SUCCESS;
    }
    else
        printf("Atleast one more argument is needed\n");
	return FAILURE;
}