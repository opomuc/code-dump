#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#define FIND_ERROR 0xBAD
#define DELETE_SUCCESS 1
#define CHANGE_SUCCESS 1

using namespace std;

struct Node_t
{
    Node_t* next;

    char eng[40];
    char rus[40];

    public:
    Node_t();
    ~Node_t();
};

Node_t::Node_t():
    next (NULL)
{
//   printf("\nI'm a constructor. I made a node");
}

Node_t::~Node_t()
{
    next = NULL;

//    printf("\nI'm a destructor. I deleted a node");
}

class Dictionary_t
{
    Node_t* head;
    int flag;

    public:
    Dictionary_t();
    ~Dictionary_t();

    void add_word   (char* eng, char* rus);
    void print      ();
     int find_word  (char* key, const char* lang = "eng");
     int delete_word(char* key);
     int change_word(char* wrong, char* right, const char* lang);
    void translate  (char* key);
     int sorting    ();
};

Dictionary_t::Dictionary_t():
    head (new Node_t),
    flag (0)
{
    head->eng[0] = '\0';
    head->rus[0] = '\0';
//    printf("\nI'm a constructor. I made a dictionary");
}

Dictionary_t::~Dictionary_t()
{
    Node_t* temp;
    flag = 0;

    while (head)
    {
        temp = head->next;
        delete head;
        head = temp;
    }

//    printf("\nI'm a destructor. I deleted a dictionary");
}

void Dictionary_t::add_word(char* eng_, char* rus_)
{
    if (head->next == NULL && !flag)
    {
        strcpy(head->eng, eng_);
        strcpy(head->rus, rus_);
        flag = 1;
    }
    else
    {
        Node_t* new_list = new Node_t;
        Node_t* temp;

        temp = head->next;
        head->next = new_list;
        new_list->next = temp;

        strcpy(new_list->eng, eng_);
        strcpy(new_list->rus, rus_);
    }
}

void Dictionary_t::print()
{
    printf("\n\n# DICTIONARY #\n");

    Node_t* temp = head;

    while(head)
    {
        printf("\n# ");
        for (unsigned int i = 0; i < strlen(head->eng); i++)
        {
            printf("%c", head->eng[i]);
        }
        printf(" ");
        for (unsigned int i = 0; i < strlen(head->rus); i++)
        {
            printf("%c", head->rus[i]);
        }

        head = head->next;
    }
    printf("\n\n");

    head = temp;
}

int Dictionary_t::find_word(char* key, const char* lang)
{
    Node_t* temp = head;
    int num = 0;

    if (!(strcmp(lang, "eng")))
    {
        while (head)
        {
            if (strcmp(key, head->eng) == 0)
            {
                head = temp;
                return num;
            }
            else
            {
                head = head->next;
                num++;
            }
        }
    }
    else
    {
        while (head)
        {
            if (strcmp(key, head->rus) == 0)
            {
                head = temp;
                return num;
            }
            else
            {
                head = head->next;
                num++;
            }
        }
    }

    head = temp;
    return FIND_ERROR;
}

int Dictionary_t::delete_word(char* key)
{
    Node_t* temp1 = head;
    Node_t* temp2 = head->next;
    Node_t* temp3 = head;

    int num1 = find_word(key);

    if (num1 != FIND_ERROR)
    {
        for (int i = 0; i < num1; i++)
        {
            temp3 = head;
            head = head->next;
            if(head)
            {
                temp2 = head->next;
            }
            else
            {
                temp2 = NULL;
            }
        }
    }
    else
    {
        return FIND_ERROR;
    }

    delete head;

    if (num1 == 0)
    {
        head = temp2;
    }
    else
    {
        temp3->next = temp2;
        head = temp1;
    }

    return DELETE_SUCCESS;
}

void Dictionary_t::translate(char* key)
{
    Node_t* temp = head;

    int j = find_word(key);

    if (j != FIND_ERROR)
    {
        for (int i = 0; i < j; i++)
        {
            head = head->next;
        }
        for (unsigned int i = 0; i < strlen(head->rus); i++)
        {
            printf("%c", head->rus[i]);
        }
        printf(" ");
    }
    else
    {
        for (unsigned int i = 0; i < strlen(key); i++)
        {
            printf("%c", key[i]);
        }
        printf(" ");
    }

    head = temp;
}

int Dictionary_t::change_word(char* wrong, char* right, const char* lang)
{
    Node_t* temp = head;
    int num2 = find_word(wrong);

    if (num2 != FIND_ERROR)
    {
        for (int i = 0; i < num2; i++)
        {
            head = head->next;
        }
        if (!strcmp(lang, "eng"))
        {
            strcpy(head->eng, right);
        }
        else
        {
            strcpy(head->rus, right);
        }
    }
    else
    {
        return FIND_ERROR;
    }

    head = temp;
    return CHANGE_SUCCESS;
}

int Dictionary_t::sorting()
{
    Node_t* temp = head;
    int swap_num = 0;
    int list_size = 0;

    for (list_size = 1; head->next != NULL; list_size++)
    {
        head = head->next;
    }
    head = temp;

//    Node_t* arr[list_size];

    Node_t** arr = (Node_t**) calloc (list_size, sizeof(Node_t*));

    for (int i = 0; i < list_size; i++)
    {
        arr[i] = head;
        head = head->next;
    }
    head = temp;

    Node_t* temp2 = NULL;

    do
    {
        swap_num = 0;
        for (int i = 0; i < list_size - 1; i++)
        {
            if (strcmp(arr[i]->eng, arr[i+1]->eng) == 1)
            {
                temp2 = arr[i];
                arr[i] = arr[i+1];
                arr[i+1] = temp2;
                swap_num++;
            }
        }
    }
    while (swap_num);

    for (int i = 0; i < list_size - 1; i++)
    {
        arr[i]->next = arr[i+1];
    }

    head = arr[0];
    arr[list_size-1]->next = NULL;

    free(arr);

    return CHANGE_SUCCESS;
}


int main()
{
    FILE* in = fopen("input.txt", "r");
    char eng[40], rus[40];
    int cmd = 0, flag = 1;

    Dictionary_t dic;

    printf("\nHello! Glad to see you again");

    while (flag)
    {
        printf("\nWhat would you like me to do? (use commands): ");
        scanf("%10d", &cmd);
        switch(cmd)
        {
            case 1:
            {
                scanf("%39s %39s", eng, rus);
                dic.add_word(eng, rus);
                break;
            }
            case 2:
            {
                scanf("%39s %39s", eng, rus);
                dic.change_word(eng, rus, "eng");
                break;
            }
            case 3:
            {
                scanf("%39s %39s", eng, rus);
                dic.change_word(eng, rus, "rus");
                break;
            }
            case 4:
            {
                scanf("%39s", eng);
                dic.delete_word(eng);
                break;
            }
            case 5:
            {
                dic.sorting();
                break;
            }
            case 6:
            {
                int c, i, flag = 0;
                c = getchar();
                do
                {
                    do
                    {
                        if(i == 39)
                        {
                            printf("\nToo many characters!");
                            break;
                        }
                        c = getchar();
                        eng[i++] = (char) c;
                    }
                    while (c != ' ' && c != '\n');

                    eng[--i] = '\0';
                    dic.translate(eng);
                    i = 0;
                }
                while (c != '\n');
                break;
            }
            case 7:
            {
                dic.print();
                break;
            }
            case 9:
            {
                printf("\n\t# 1 - add a new word"
                       "\n\t# 2 - change the english word"
                       "\n\t# 3 - change the translation"
                       "\n\t# 4 - delete the word from the dictionary"
                       "\n\t# 5 - sorting by alphabet"
                       "\n\t# 6 - translate the sentence"
                       "\n\t# 7 - print the dictionary"
                       "\n\t# 0 - exit\n\n");
                break;
            }
            case 0:
            {
                flag = 0;
                break;
            }
            default:
            {
                printf("Wrong command! Use help (9)\n");
                break;
            }
        }
    }

    fclose(in);
    return 0;
}
