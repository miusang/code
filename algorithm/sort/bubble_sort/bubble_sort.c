#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// C语言标准(C89)没有定义布尔类型。
typedef enum {true, false} bool;

struct Store {
    char *name; // 8 byte
    int id; // 4 byte
    int count; // 4 byte  total 8 byte
    int credit; // 8 byte
}; // total size 24 byte

struct List {
    struct Store *data;
    int len; // 统计数组实际长度
    int size; // 统计数组可用长度
};

void add(struct List *list, struct Store *item);
void store_copy(struct Store *src, struct Store *des);

/*
 * c不支持引用，只支持指针。
 */
void swap(int *a, int *b);
void swap_store(struct Store *a, struct Store *b);
void sort(int *nums, int len);
void test_for_time(int len, int max);
void test_for_stability();
void print_list(struct List *list);
void sort_with_count(struct List *list);
void sort_with_credit(struct List *list);


void array_print(int *nums, int len) {
    for (int i = 0; i < len; i++) {
        printf("%d ", nums[i]);
    }
    printf("\n");
}
long get_cur_time() {
    struct timespec times = {0, 0};
    clock_gettime(CLOCK_MONOTONIC, &times);
    return times.tv_sec * 1000 + times.tv_nsec / 1000000;
}

int main(int argc, const char*argv[]) {
    if (argc < 3) {
        return 0;
    }
    int max = atoi(argv[2]);
    int len = atoi(argv[1]);
    printf("nums len: %d, max: %d\n", len, max);
    //test_for_time(len, max);
    test_for_stability();
}

void sort(int *nums, int len) {
    for (int i = 0; i < len; i++) {
        bool flag = true;
        for (int j = 0; j < len - i - 1; j++) {
            if (nums[j] < nums[j+1]) {
                continue;
            }
            swap(&nums[j], &nums[j+1]);
            flag = false;
        }
        if (flag == true) {
            break;
        }
    }
}

void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void test_for_time(int len, int max) {
    int *nums = (int *) malloc (len * sizeof(int));
    for (int i = 0; i < len; i++) {
        nums[i] = rand() % max;
    }
    //array_print(nums, len);
    long start_time = get_cur_time();
    sort(nums, len);
    long end_time = get_cur_time();
    printf("sort time: %ld ms\n", end_time - start_time);
    //array_print(nums, len);
}

void test_for_stability() {
    const char* path = "../list.txt";
    FILE *fp = fopen(path, "r");
    if (fp == NULL) {
        return;
    }
    struct Store *stores = (struct Store*) malloc (16 * sizeof(struct Store));
    struct List list;
    list.data = stores;
    list.len = 0;
    list.size = 16;

    char line[255];
    fgets(line, sizeof(line), fp);
    while (fgets(line, sizeof(line), fp)) {
        char *name = (char *) malloc (16 * sizeof(char));
        struct Store store;
        store.name = name;
        sscanf(line, "%d %s %d %d",
                &store.id, store.name, &store.count, &store.credit);
        add(&list, &store);
    }
    fclose(fp);
    print_list(&list);
    printf("***********************************\n");
    sort_with_count(&list);
    print_list(&list);
    printf("***********************************\n");
    sort_with_credit(&list);
    print_list(&list);
}

void add(struct List *list, struct Store *item) {
    if (list->len >= list->size) {
        struct Store *tmps = list->data;
        struct Store *nums = (struct Store *) malloc(sizeof(struct Store) *
                list->size * 2);
        for (int i = 0; i < list->len; i++) {
            store_copy(&tmps[i], &nums[i]);
        }
        list->data = nums;
        free(tmps);
        list->size = list->size * 2;
    }
    list->data[list->len].name = item->name;
    item->name = NULL;
    list->data[list->len].id = item->id;
    list->data[list->len].count = item->count;
    list->data[list->len].credit = item->credit;
    list->len += 1;
}

void store_copy(struct Store *src, struct Store *des) {
    des->name = src->name;
    src->name = NULL;
    des->id = src->id;
    des->count = src->count;
    des->credit = src->credit;
}

void print_list(struct List *list) {
    for (int i = 0; i < list->len; i++) {
        printf("%d %s %d %d\n", list->data[i].id, list->data[i].name,
                list->data[i].count, list->data[i].credit);
    }
}

void swap_store(struct Store *a, struct Store *b) {
    char *tmp_name = a->name;
    int tmp_count = a->count;
    int tmp_credit = a->credit;
    int tmp_id = a->id;
    a->credit = b->credit;
    a->count = b->count;
    a->name = b->name;
    a->id = b->id;
    b->id = tmp_id;
    b->name = tmp_name;
    b->count = tmp_count;
    b->credit = tmp_credit;
}

void sort_with_count(struct List *list) {
    for (int i = 0; i < list->len; i++) {
        int sorted_flag = 1;
        for (int j = list->len - 1; j > i; j--) {
            if (list->data[j].count < list->data[j-1].count) {
                swap_store(&list->data[j], &list->data[j-1]);
                sorted_flag = 0;
            }
        }
        if (sorted_flag == 1) {
            return;
        }
    }
}

void sort_with_credit(struct List *list) {
    for (int i = 0; i < list->len; i++) {
        int sorted_flag = 1;
        for (int j = list->len - 1; j > i; j--) {
            if (list->data[j].credit < list->data[j-1].credit) {
                swap_store(&list->data[j], &list->data[j-1]);
                sorted_flag = 0;
            }
        }
        if (sorted_flag == 1) {
            return;
        }
    }
}
