#include <stdio.h>
#include "Member.h"
#include "ChainHash.h"

typedef enum
{
  TERMINATE, ADD, DELETE, SEARCH, CLEAR, DUMP
} Menu;

Menu SelectMenu(void)
{
  int ch;
  do {
    printf("(1)Add (2)Delete (3)Search (4)Delete All (5)Dump (0)Exit\n");
    printf(": ");
    scanf("%d", &ch);
  } while(ch < TERMINATE || ch > DUMP);
  return(Menu)ch;
}

int main(void)
{
  Menu menu;
  ChainHash hash;
  Initialize(&hash, 13);
  do {
    int result;
    Member x;
    Node *temp;
    switch(menu = SelectMenu())
    {
      case ADD:
        x = ScanMember("Add", MEMBER_NO | MEMBER_NAME);
        result = Add(&hash, &x);
        if(result)
          printf("\aError: Add Failed(%s).\n", (result == 1) ? "Already Exist" : "Memory");
        break;
      
      case DELETE:
        x = ScanMember("Delete", MEMBER_NO);
        result = Remove(&hash, &x);
        if(result == 1)
          printf("\aError: Dont exist No.\n");
        break;
      
      case SEARCH:
        x = ScanMember("Search", MEMBER_NO);
        temp = Search(&hash, &x);
        if(temp == NULL)
          printf("\aSearch Failed.\n");
        else
        {
          printf("Search Success. : \n");
          PrintLnMember(&temp->data);
        }
        break;
      
      case CLEAR:
        Clear(&hash);
        break;
      
      case DUMP:
        Dump(&hash);
        break;
    }
  } while(menu != TERMINATE);
  Terminate(&hash); // Exit Hash Table

  return 0;
}