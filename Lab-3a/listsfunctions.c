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
void insert(struct thelist *, int, int);
void removeElement(struct thelist *, int);
void replace(struct thelist *, int, int);

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
        // printf("Removing %i: %i\n", i++, tmp->info);
        tmpn = tmp->next;
        free(tmp);
        tmp = tmpn;
    }

    // printf("Removing %i: %i\n\n", i++, tmp->info);
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

void append(struct thelist *alist, int value)
{
    struct thelist *last, *new;

    last = getAddress(alist, alist->info);

    new = (struct thelist *)malloc(sizeof(struct thelist));
    last->next = new;
    new->next = NULL;
    new->info = value;
    alist->info++;
}

void insert(struct thelist *alist, int n, int value)
{
    struct thelist *previous, *new, *next;

    if (n > alist->info)
    {
        append(alist, value);
        return;
    }

    previous = getAddress(alist, n-1);
    next = previous->next;

    new = (struct thelist *)malloc(sizeof(struct thelist));
    previous->next = new;
    new->next = next;
    new->info = value;
    alist->info++;
}

void removeElement(struct thelist *alist, int n)
{
    struct thelist *previous, *toremove, *next;

    previous = getAddress(alist, n-1);
    toremove = previous->next;
    next = toremove->next;

    previous->next = next;
    free(toremove);
    alist->info--;
}

void replace(struct thelist *alist, int n1, int n2)
{
    struct thelist *before1, *before2, *toreplace1, *toreplace2, *after1, *after2;

    if (n2 - n1 == 1 || n2 - n1 == -1)
    {
        if (n2 - n1 == 1)
            before1 = getAddress(alist, n1 - 1);

        else if (n2 - n1 == -1)
            before1 = getAddress(alist, n2 - 1);

        toreplace1 = before1->next;
        toreplace2 = toreplace1->next;
        after2 = toreplace2->next;

        before1->next = toreplace2;
        toreplace2->next = toreplace1;
        toreplace1->next = after2;
    }

    else
    {
        before1 = getAddress(alist, n1 - 1);
        before2 = getAddress(alist, n2 - 1);

        toreplace1 = before1->next;
        toreplace2 = before2->next;

        after1 = toreplace1->next;
        after2 = toreplace2->next;

        before2->next = toreplace1;
        before1->next = toreplace2;

        toreplace2->next = after1;
        toreplace1->next = after2;
    }
}
