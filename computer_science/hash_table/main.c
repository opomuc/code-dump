#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

typedef int hash_t;

typedef struct Node
{
    char* name_key;
    hash_t password_hash;
    struct Node* next;
} Node;

Node* node_for_search;

typedef struct
{
  int ht_size;
  Node** head;
} Hash_table;

Hash_table*     HT_construct(int size_);
void            HT_destruct(Hash_table* ht);
Node*           Node_construct();
void            Node_destruct(Node* node);
unsigned int    Hash(const char*);
Node*           add_node_to_list(Node* head, Node* new_);
int             find_in_list(Node* head, const char* key_to_find);
int             delete_from_list(Node* head, const char* key_to_delete);
void            delete_list(Node* head);
int             add_to_hash(Hash_table* ht, const char* name, const char* password);
int             find_in_hash(Hash_table* ht, const char* key_to_find);
int             delete_from_hash(Hash_table* ht, const char* key_to_delete);

Node* Node_construct() {

    Node* new_elem = (Node*) malloc(sizeof(Node));
    new_elem->name_key = (char*) malloc(sizeof(char*));
    new_elem->password_hash = 0;
    new_elem->next = NULL;
//    printf("Node has been successfully created!\n");
    return new_elem;

}

void Node_destruct(Node* node) {

    if(!node)
        assert("--> Unable to destruct a NULL node <--");
    else {
        free(node->name_key);
        free(node);
    }
//    printf("Node has been successfully deleted!\n");
}

void delete_list(Node* head) {
    Node *p = head;
    Node* temp;
    while(p) {
        temp = p->next;
        Node_destruct(p);
        p = temp;
    }
}

Hash_table* HT_construct(int size_) {

    Hash_table* ht = (Hash_table*) calloc (1, sizeof(Hash_table));
    ht->ht_size = size_;
    ht->head = (Node**) calloc (ht->ht_size, sizeof(Node*));
    int i = 0;
    if(ht->head) {
        for (i = 0; i < ht->ht_size; i++) {
            ht->head[i] = NULL;
        }
    }
    else assert("--> Allocation error <--");
 //   printf("Hash table has been successfully created!\n");
    return ht;
}

void HT_destruct(Hash_table* ht) {

    Node* iterator_;
    Node* temp;
    int i = 0;
    if(!ht)
        assert("--> Unable to destruct a NULL hash table <--");

    for(i = 0; i < ht->ht_size; i++) {
        if(ht->head[i]) {
            delete_list(ht->head[i]);
        }
    }

    free(ht);           // freeing the hash table
 //   printf("Hash table has been successfully deleted!\n");
}

unsigned int Hash(const char * str) {

    unsigned int hash = 0;

    for(; *str; str++)
    {
        hash += (unsigned char)(*str);
        hash -= (hash << 13) | (hash >> 19);
    }

    return hash;

}

Node* add_node_to_list(Node* head, Node* new_) {

    if(head == NULL) {
        head = new_;
    }
    else {
        new_->next = head;
        head = new_;
    }
    return head;
}

int find_in_list(Node* head, const char* key_to_find) {
    Node* p = head;
    while(p) {
        if(!strcmp(key_to_find, p->name_key)) {
            node_for_search = p;
            return 1;
        }
        else {
            p = p->next;
        }
    }
    return 0;
}

int delete_from_list(Node* head, const char* key_to_delete) {
    Node* temp1 = head;
    Node* temp2;
    while(head) {
        if(!strcmp(key_to_delete, head->name_key)) {
            temp2 = head->next;
            Node_destruct(head);
            head = temp2;
            return 1;
        }
        else {
            head = head->next;
        }
    }
    head = temp1;
    return 0;
}

int add_to_hash(Hash_table* ht, const char* name, const char* password) {

    if(find_in_hash(ht, name)) {
        return 0;
    }

    Node* new_node = Node_construct();
    strcpy(new_node->name_key, name);
    new_node->password_hash = Hash(password);

    int pos = Hash(name) % ht->ht_size;
    ht->head[pos] = add_node_to_list(ht->head[pos], new_node);

    return 1;
}

int find_in_hash(Hash_table* ht, const char* key_to_find) {
    int pos = Hash(key_to_find) % ht->ht_size;
    if(find_in_list(ht->head[pos], key_to_find)) {
        return 1;
    }
    else return 0;
}

int delete_from_hash(Hash_table* ht, const char* key_to_delete) {
    int pos = Hash(key_to_delete) % ht->ht_size;
    if(delete_from_list(ht->head[pos], key_to_delete)) {
        return 1;
    }
    return 0;
}

int main()
{
    Hash_table* my_hash_table = HT_construct(100);
    add_to_hash(my_hash_table, "Roman", "12345");

    if(find_in_hash(my_hash_table, "Roman")) {
        printf("Found at node: %p\n", node_for_search);
        printf("Password_hash: %d\n", node_for_search->password_hash);
    }
    else
        printf("Username was not found\n");
    if(!delete_from_hash(my_hash_table, "Roman"))
        printf("Username was not found\n");
    if(find_in_hash(my_hash_table, "Roman")) {
        printf("Found at node: %p\n", node_for_search);
        printf("Password_hash: %d\n", node_for_search->password_hash);
    }
    else
        printf("Username was not found\n");

    HT_destruct(my_hash_table);
    printf("all done\n");
    return 0;
}
