#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SIZE_SOCIAL_NUMBER 10
#define SIZE_FULL_NAME 30
#define SIZE_ADDRESS 50
#define SIZE_TEL_NUMBER 11
#define SIZE_DATE 11


struct application_information{
    char* social_number;
    char* full_name;
    char* address;
    char* date;
    struct application_information *next;
};
typedef struct application_information Application_information ;

struct available_number_node{
    char* tel_number;
    struct available_number_node *next;
};
typedef struct available_number_node Available_number_node;

struct installed_number_node{
    char* tel_number;
    char* social_number;
    char* full_name;
    char* address;
    char* date;
    struct installed_number_node *next;
};
typedef struct installed_number_node Installed_number_node;

Installed_number_node *INSTALLED_NUMBER_STACK_TOP = NULL;
Available_number_node  *AVAILABLE_NUMBERS_STACK_TOP = NULL;
Application_information *APPLICATIONS_QUEUE_BEGINNING = NULL;

void enqueue_application(Application_information ** queue_beginning, char* social_number, char* full_name, char* address, char* date){
  /*reserve memory*/
  Application_information *new_node = (Application_information *)malloc(sizeof(Application_information));
  new_node->social_number = (char *)malloc(sizeof(char)*SIZE_SOCIAL_NUMBER);
  new_node->full_name = (char *)malloc(sizeof(char)*SIZE_FULL_NAME);
  new_node->address = (char *)malloc(sizeof(char)*SIZE_ADDRESS);
  new_node->date = (char *)malloc(sizeof(char)*SIZE_DATE);
  new_node->next = NULL;
  /*copy user values to new_node*/
  strcpy(new_node->social_number, social_number);
  strcpy(new_node->full_name, full_name);
  strcpy(new_node->address, address);
  strcpy(new_node->date, date);
  /*if queue is empty, we assign our new_node to queue_beginning*/
  if(*queue_beginning == NULL){
    *queue_beginning = new_node;
  }
  else{
    /*else we find last node and assign it to new_node */
    Application_information* last_node = *queue_beginning;
    while(last_node->next != NULL){
      last_node = last_node->next;
    }
    last_node->next = new_node;
  }
}

Application_information *dequeue_application(Application_information ** queue_beginning){
  /*if queue is empty, return NULL*/
  if(*queue_beginning == NULL) {
    return NULL;
  }else{
    Application_information *dequeued_node = *queue_beginning; //
    *queue_beginning = (*queue_beginning)->next;
    return dequeued_node;
  }
}

void display_waiting_application(){
  /*define temp variable and print till it reach NULL*/
  Application_information *temp = APPLICATIONS_QUEUE_BEGINNING;
  printf("Social Number - Full Name - Address - Date\n");
  while (temp != NULL){
    printf("%s - %s - %s - %s\n", temp->social_number, temp->full_name, temp->address, temp->date);
    temp = temp->next;
  }
  free(temp);
}

void push_available_number(Available_number_node ** stack_top, char* tel_number){
  Available_number_node *new_Node = (Available_number_node *)malloc(sizeof(Available_number_node));
  new_Node->tel_number = (char *)malloc(sizeof(char)*SIZE_TEL_NUMBER);
  new_Node->next = NULL;

  strcpy(new_Node->tel_number, tel_number);
  /*stack is empty just assign new_Node to stack_top */
  if(*stack_top == NULL){
    *stack_top = new_Node;
  }else{
    /*else keep next node as Top of stack each time we push*/
    new_Node->next = *stack_top;
    *stack_top = new_Node;
  }
}

Available_number_node *pop_available_number(Available_number_node ** stack_top){
  if(*stack_top == NULL){
    return NULL;
  }else{
    Available_number_node *popped_node = *stack_top;
    *stack_top = (*stack_top)->next;
    return popped_node;
  }
}

void display_available_number(){
  /*declare temp Available_number_node and print till its NULL*/
  Available_number_node *temp = AVAILABLE_NUMBERS_STACK_TOP;
  printf("Telephone Numbers\n");
  while (temp != NULL){
    printf("%s\n", temp->tel_number);
    temp = temp->next;
  }
}

void push_installed_number(Installed_number_node ** stack_top, char* tel_number, char* social_number, char* full_name, char* address, char* date){
  Installed_number_node *new_Node = (Installed_number_node *)malloc(sizeof(Installed_number_node));
  new_Node->tel_number = (char *)malloc(sizeof(char)*SIZE_TEL_NUMBER);
  new_Node->social_number = (char *)malloc(sizeof(char)*SIZE_SOCIAL_NUMBER);
  new_Node->full_name = (char *)malloc(sizeof(char)*SIZE_FULL_NAME);
  new_Node->address = (char *)malloc(sizeof(char)*SIZE_ADDRESS);
  new_Node->date = (char *)malloc(sizeof(char)*SIZE_DATE);
  new_Node->next = NULL;


  strcpy(new_Node->tel_number, tel_number);
  strcpy(new_Node->social_number, social_number);
  strcpy(new_Node->full_name, full_name);
  strcpy(new_Node->address, address);
  strcpy(new_Node->date, date);
  /*stack is empty just assign new_Node to stack_top*/
  if(*stack_top == NULL){
    *stack_top = new_Node;
  }else{
    /*else keep next node as Top of stack each time we push*/
    new_Node->next = *stack_top;
    *stack_top = new_Node;
  }
}

Installed_number_node *pop_installed_number(Installed_number_node ** stack_top){
  if(*stack_top == NULL){
    return NULL;
  }else{
    Installed_number_node *popped_node = *stack_top;
    *stack_top = (*stack_top)->next;
    return popped_node;
  }
}

void display_installed_number(){
  Installed_number_node *temp = INSTALLED_NUMBER_STACK_TOP;
  printf("Tel Number - Social Number - Full Name - Address - Date\n");
  while (temp != NULL){
    printf("%s %s %s %s %s\n",temp->tel_number,temp->social_number,temp->full_name,temp->address,temp->date);
    temp = temp->next;
  }
}

int accept_application(){
  /*0 means acceptance operation is not complete, if there is no numbers or applications waiting*/
  if(AVAILABLE_NUMBERS_STACK_TOP == NULL && APPLICATIONS_QUEUE_BEGINNING == NULL) return 0;
  /*declare popped_number and assign value of pop_available_number*/
  Available_number_node * popped_number = pop_available_number(&AVAILABLE_NUMBERS_STACK_TOP);
  if(popped_number != NULL) {
    /*if popped_number is not NULL, take dequeue_application and push it to push_installed_number*/
    Application_information * dequeued_information = dequeue_application(&APPLICATIONS_QUEUE_BEGINNING);
    push_installed_number(&INSTALLED_NUMBER_STACK_TOP, popped_number->tel_number, dequeued_information->social_number,
                          dequeued_information->full_name, dequeued_information->address, dequeued_information->date);
    free(dequeued_information);
    free(popped_number);
    return 1;
  }
  else{
    return 0;
  }
}

int remove_subscription(char* social_number, char* tel_number){
  int is_subscription_found = 0;

  Installed_number_node *temp_node = NULL;
  Installed_number_node *temp_stack_top = NULL;
  //find a subscription in INSTALLED_NUMBER_STACK_TOP using social_number and tel_number
  while(INSTALLED_NUMBER_STACK_TOP != NULL){
    temp_node = pop_installed_number(&INSTALLED_NUMBER_STACK_TOP);
    int comparision_result1 = strcmp(temp_node->social_number, social_number);
    int comparision_result2 = strcmp(temp_node->tel_number, tel_number);

    //subscription found, push its associated phone number to AVAILABLE_NUMBERS_STACK_TOP
    if(comparision_result1 == 0 && comparision_result2 == 0){
      is_subscription_found = 1;
      push_available_number(&AVAILABLE_NUMBERS_STACK_TOP, temp_node->tel_number);
      free(temp_node);
      break;
    }
    //add the nodes popped from INSTALLED_NUMBER_STACK_TOP into a temporary stack to return them to INSTALLED_NUMBER_STACK_TOP later
    push_installed_number(&temp_stack_top, temp_node->tel_number, temp_node->social_number, temp_node->full_name, temp_node->full_name, temp_node->date);
    //since push_installed_number allocates a new node in heap and copies all passed fields, free memory
    free(temp_node);
  }
  //return nodes from the temporary stack to INSTALLED_NUMBER_STACK_TOP
  while(temp_stack_top != NULL){
    temp_node = pop_installed_number(&temp_stack_top);
    push_installed_number(&INSTALLED_NUMBER_STACK_TOP, temp_node->tel_number, temp_node->social_number, temp_node->full_name, temp_node->address, temp_node->date);
    //since push_installed_number allocates a new node in heap and copies all passed fields, free memory
    free(temp_node);
  }

  return is_subscription_found;
}
int main() {
  int choice = 0; /*for switch case*/
  char social_number[SIZE_SOCIAL_NUMBER];
  char full_name[SIZE_FULL_NAME];
  char address[SIZE_ADDRESS];
  char date[SIZE_DATE];
  char telephone_number[SIZE_TEL_NUMBER];
  srand(time(0)); /*te get each time random numbers*/
  char numb[SIZE_TEL_NUMBER];
  /*to have first 4 digits as (0312) like ankara landline numbers
   * we initialized our array indexes with 0312 respectively*/
  numb[0] = '0'; numb[1] ='3'; numb[2] = '1'; numb[3] = '2'; numb[10] = '\0';
  /*we generate 50 random numbers and pushed to available numbers stack */
  for(int j = 0; j < 50; j++){
    for(int i = 4; i < 10; i++){
      numb[i] = (rand() % 9) + '0';
    }
    push_available_number(&AVAILABLE_NUMBERS_STACK_TOP, numb);
  }
  do
  {
    printf("Press number according to your choice");
    printf("\n1. Filling Application"
           "\n2. Display all possible Numbers"
           "\n3. Display all Waiting Applications"
           "\n4. Accept & Confirm Application from waiting list and assign a number"
           "\n5. Display all Accepted Applications "
           "\n6. Delete Subscription by providing both Social Number and Telephone Number"
           "\n0. Exit");
    printf("\nEnter Choice 0-6? :");
    scanf("%d", &choice);
    switch (choice)
    {
      case 1:
        printf("Enter your Social possible_number (9 digits):");
        getchar();
        scanf("%[^'\n']s", social_number );
        printf("Enter your Full Name:");
        getchar();
        scanf("%[^'\n']s", full_name );
        printf("Enter your Full Address:");
        getchar();
        scanf("%[^'\n']s", address );
        getchar();
        printf("Enter application date (DD.MM.YYYY):");
        getchar();
        scanf("%[^'\n']s", date);
        enqueue_application(&APPLICATIONS_QUEUE_BEGINNING,social_number,full_name,address,date);
        break;
      case 2:
        display_available_number();
        break;
      case 3:
        display_waiting_application();
        break;
      case 4:
        accept_application();
        break;
      case 5:
        display_installed_number();
        break;
      case 6:
        printf("You must provide both Social and Telephone numbers\n");
        printf("Enter your Social possible_number (9 digits):");
        getchar();
        scanf("%[^'\n']s", social_number );
        printf("Enter your Telephone Number:");
        getchar();
        scanf("%[^'\n']s", telephone_number );
        //remove_subscription(social_number,telephone_number);
        if(remove_subscription(social_number,telephone_number) == 1){
          printf("Subscription has been removed successfully!\n");
        }else{
          printf("Please check your given social number and Telephone number"
                 "we don't have subscriptions over the info you provided!\n");
        }

        break;
        case 0:
          printf("Program Ended!!\n");
          return 0;
        default:
        printf("Error. Unsupported input value");
    }
  }while (choice != 0);

  return 0;
}
