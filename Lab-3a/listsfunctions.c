struct thelist
{
    int info;
    struct thelist *next;
};

struct thelist* create()
{
    struct thelist *tmp;
    tmp = (struct thelist*)malloc(sizeof(struct thelist));
    tmp->info = 0;
    tmp->next = NULL;
    return tmp;
}

void destroy(struct thelist *alist)
{
    int i = 0;
    struct thelist *tmp, *tmpn;
    tmp = alist;

    while (tmp->next != NULL)
    {
        printf("Removing: %i - %i\n", i++, tmp->info);
        tmpn = tmp->next;
        free(tmp);
        tmp = tmpn;
    }

    printf("Removing: %i - %i\n", i++, tmp->info);
    free(tmp);
}


struct thelist* getAddress(struct thelist *alist, int n)
{
    int i;
    struct thelist *tmp;
    tmp = alist;

    for (i = 0; i < n; i++)
        tmp = tmp->next;

    return tmp;
}

int getValue(struct thelist *alist, int n)
{
    int i;
    struct thelist *tmp;

    tmp = getAddress(alist, n);
    return tmp->info;
}

void print(struct thelist *alist)
{
    int i;
    int n = alist->info;
    
    if (!n)
    {
        printf("Список пуст!\n");
        return;
    }

    for (i = 1; i <= n; i++)
        printf("%i --> %p", getValue(alist, i), getAddress(alist, i));

    printf("\n");
}

