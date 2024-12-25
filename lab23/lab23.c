#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

typedef struct node {
    char task[256];
    struct node* next;
} node;

typedef struct linked_list {
    node* head;
} linked_list;

void init_list(linked_list* list);
void insert(linked_list* list, char* task);
void putslist(linked_list* list);
void delete(linked_list* list, char* task);
node* merge(node* first, node* second);
node* mergeSort(node* head);
void sort_list(linked_list* list);

int main() {
    system("chcp 1251");
    linked_list tasks;
    char input_task[256];
    int choice;
    init_list(&tasks);
    printf("Для выхода из трекера нажмите на '0'\n");
    do {
        printf("Трекер задач\n1)Добавить задачу\n2)Удалить задачу\n3)Показать задачи\n4)Сортировать задачи\n5)Выход\n");
        scanf("%d", &choice);
        getchar();
        switch (choice) {
        case 1:
            printf("Введите задачу, которую хотите добавить в список: ");
            fgets(input_task, sizeof(input_task), stdin);
            insert(&tasks, input_task);
            break;
        case 2:
            printf("Введите задачу, которую хотите убрать из списка: ");
            fgets(input_task, sizeof(input_task), stdin);
            delete(&tasks, input_task);
            break;
        case 3:
            putslist(&tasks);
            break;
        case 4:
            sort_list(&tasks);
            putslist(&tasks);
            break;
        case 5:
            break;
        default:
            printf("Выберите функцию 1-5\n");
        }
    } while (choice != 5);
    return 0;
}

void init_list(linked_list* list) {
    list->head = NULL;
}

void insert(linked_list* list, char* task) {
    node* newnode = (node*)malloc(sizeof(node));
    strcpy(newnode->task, task);
    newnode->next = NULL;
    if (!list->head) {
        list->head = newnode;
        return;
    }
    node* last = list->head;
    while (last->next) {
        last = last->next;
    }
    last->next = newnode;
}

void putslist(linked_list* list) {
    node* curr = list->head;
    if (curr == NULL) {
        printf("Список задач пуст.\n");
        return;
    }
    while (curr) {
        printf("- %s", curr->task);
        curr = curr->next;
    }
}

void delete(linked_list* list, char* task) {
    node* curr = list->head;
    node* prev = NULL;

    while (curr) {
        if (strcmp(curr->task, task) == 0) {
            if (prev) {
                prev->next = curr->next;
            }
            else {
                list->head = curr->next;
            }
            free(curr);
            printf("Задача '%s' удалена.\n", task);
            return;
        }
        prev = curr;
        curr = curr->next;
    }
    printf("Задача '%s' не найдена.\n", task);
}

node* mergeSort(node* head) {
    if (!head || !head->next) return head;

    node* middle = head;
    node* fast = head->next;

    while (fast && fast->next) {
        middle = middle->next;
        fast = fast->next->next;
    }

    node* left = head;
    node* right = middle->next;
    middle->next = NULL; 

    left = mergeSort(left);
    right = mergeSort(right);

    node* result = NULL;
    node* temp = NULL;
    if (strcmp(left->task, right->task) <= 0) {
        result = left;
        left = left->next;
    }
    else {
        result = right;
        right = right->next;
    }
    temp = result;

    while (left && right) {
        if (strcmp(left->task, right->task) <= 0) {
            temp->next = left;
            left = left->next;
        }
        else {
            temp->next = right;
            right = right->next;
        }
        temp = temp->next;
    }

    if (left) temp->next = left;
    else temp->next = right;

    return result;
}

void sort_list(linked_list* list) {
    list->head = mergeSort(list->head);
}