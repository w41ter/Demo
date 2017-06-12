void sort(int *a, int l, int r)
{
    if (l >= r) return;

    int lt = l, gt = r;
    int value = a[lt];
    while (true) {
        while (a[++lt] < value) if (lt >= r) break;
        while (a[--gt] > value) if (gt <= l) break;
        if (lt >= gt) break;
        swap(a, lt, gt);
    }
    swap(a, l, gt);
    sort(a, l, gt);
    sort(a, gt+1, r);
}

void sort(int *a, int l, int r) 
{
    int lt = l, gt = r, i = lt + 1;
    int value = a[lt];
    while (i < gt) {
        if (a[i] < value) swap(a, lt++, i++);
        else if (a[i] > value) swap(a, --gt, i);
        else i++;
    }
    sort(a, l, lt);
    sort(a, gt, r);
}