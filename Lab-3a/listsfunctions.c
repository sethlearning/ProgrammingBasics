struct thelist
{
    int info;
    struct thelist *next;
};

struct thelist* create();
void destroy(struct thelist *);
void print(struct thelist *);
int getValue(struct thelist *, int);
struct thelist * getAddress(struct thelist *, int);
void append(struct thelist *, int);

struct thelist * create()
{
    struct thelist *tmp;
    tmp = (struct thelist *)malloc(sizeof(struct thelist));
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
        printf("Removing %i: %i\n", i++, tmp->info);
        tmpn = tmp->next;
        free(tmp);
        tmp = tmpn;
    }

    printf("Removing %i: %i\n", i++, tmp->info);
    free(tmp);
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
        printf("%i --> %p\n", getValue(alist, i), getAddress(alist, i)->next);

    printf("\n");
}

int getValue(struct thelist *alist, int n)
{
    int i;
    struct thelist *tmp;

    tmp = getAddress(alist, n);
    return tmp->info;
}

struct thelist * getAddress(struct thelist *alist, int n)
{
    int i;
    struct thelist *tmp;
    tmp = alist;

    for (i = 0; i < n; i++)
        tmp = tmp->next;

    return tmp;
}

void append(struct thelist *alist, int n)
{
    struct thelist *tmp, *new;

    tmp = getAddress(alist, alist->info);

    new = (struct thelist *)malloc(sizeof(struct thelist));
    tmp->next = new;
    alist->info++;

    new->info = n;
    new->next = NULL;
}
