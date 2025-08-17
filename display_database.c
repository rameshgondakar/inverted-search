#include<stdio.h>
#include"main.h"

int display_data(main_node *head,int index)
{
	main_node *m_temp = head;
    sub_node *s_temp;

    if (head == NULL) 
	{
        return 0;
    }

    while (m_temp != NULL) 
	{
        printf("%d\t %s\t %-12d\t", index, m_temp->word, m_temp->file_count);

        s_temp = m_temp->s_link;
        int f = 0;

        while (s_temp != NULL) 
		{
            if (f == 0) 
			{
                printf("%s\t %10d", s_temp->file_name, s_temp->word_count);
                f++;
            } else {
                printf("\n%38s\t %10d", s_temp->file_name, s_temp->word_count);
            }

            s_temp = s_temp->link;
        }

        m_temp = m_temp->m_link;
        printf("\n");
        index++;
    }

    return 1;
}