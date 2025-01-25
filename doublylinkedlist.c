#include <stdio.h>
#include <stdlib.h>

struct node {
  int data;
  struct node* prev;
  struct node* next;
};

typedef struct node Node;

Node* createNode(int data){
  Node* n = (Node*) malloc(sizeof(Node));
  n->data = data;
  n->next = NULL;
  n->prev = NULL;
  return n;
}

void insertFront(Node* Header, int data){
  Node* n = createNode(data);
  n->next = Header->next;
  n->prev = Header;
  Header->next = n;
}

void insertLast(Node* Header, int data){
  Node* ptr = Header->next;
  Node* n = createNode(data);
  while(ptr != NULL && ptr->next != NULL){
    ptr = ptr->next;
  }
  if (ptr == NULL) {
    Header->next = n;
  } else {
    ptr->next = n;
  }
  n->prev = ptr;
}

void deleteFront(Node* Header){
  Node* ptr = Header->next;
  if(ptr != NULL){
    Node* nextNode = ptr->next;
    Header->next = nextNode;
    if (nextNode != NULL) {
      nextNode->prev = Header;
    }
    free(ptr);
  }
}

void deleteLast(Node* Header){
  Node* ptr = Header->next;
  if (ptr != NULL){
    while(ptr->next != NULL){
      ptr = ptr->next;
    }
    Node* prevNode = ptr->prev;
    if (prevNode != NULL) {
      prevNode->next = NULL;
    }
    free(ptr);
  }
}

void printList(Node* Header){
  Node* ptr = Header->next;
  printf("[ ");
  while(ptr != NULL){
    printf("%d ", ptr->data);
    ptr = ptr->next;
  }
  printf("]\n");
}

void freeList(Node* Header){
  Node* ptr = Header->next;
  while(ptr != NULL){
    Node* next = ptr->next;
    free(ptr);
    ptr = next;
  }
}

int main(){
  Node* Header = createNode(0);
  int choice, data;

  while(1) {
    printf("\nMenu:\n");
    printf("1. Insert at front\n");
    printf("2. Insert at last\n");
    printf("3. Delete from front\n");
    printf("4. Delete from last\n");
    printf("5. Print list\n");
    printf("6. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch(choice) {
      case 1:
        printf("Enter data to insert at front: ");
        scanf("%d", &data);
        insertFront(Header, data);
        break;
      case 2:
        printf("Enter data to insert at last: ");
        scanf("%d", &data);
        insertLast(Header, data);
        break;
      case 3:
        deleteFront(Header);
        break;
      case 4:
        deleteLast(Header);
        break;
      case 5:
        printList(Header);
        break;
      case 6:
        freeList(Header);
        free(Header);
        return 0;
      default:
        printf("Invalid choice. Please try again.\n");
    }
  }
}