
#include<stdio.h>
#include<string.h>
#include"main.h"
int search_data(main_node *head,int index,char* word)
{
    main_node *m_temp = head;
    sub_node *s_temp;
    if(head == NULL)
    {
	return FAILURE;
    }
    while(m_temp != NULL)
    {
	if((strcmp(m_temp -> word, word)) == 0)      //comparing the word in hastable, if the word found it will display the details of the word
	{
	    printf("%d\t %s\t %-12d\t",index, m_temp -> word, m_temp -> file_count);        //printing main node data
	    s_temp = m_temp -> s_link;
		int f=0;
	    while(s_temp != NULL)
	    {
	        if (f == 0) 
			{
                printf("%s\t %10d", s_temp->file_name, s_temp->word_count);
                f++;
            } else {
                printf("\n%38s\t %10d", s_temp->file_name, s_temp->word_count);
            }
	        s_temp = s_temp -> link;
	    }
	    printf("\n");
	    return SUCCESS;
	}
	m_temp = m_temp -> m_link;
    }
    

    return 0;
}
