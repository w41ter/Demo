def bubble_sort(array):
    length = len(array)
    while length > 1:
        i = 0
        while i < length-1:
            if array[i] > array[i+1]:
                swap(array, i, i+1)
            i = i + 1

def swap(array, i, j):
    tmp = array[i]
    array[i] = array[j]
    array[j] = tmp
