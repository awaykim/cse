def choosePivot(array, low, high):
        # array[low], array[mid], array[high] 값을 비교해 Median을 찾는다.
        # 찾은 Median이 array[high]에 가도록 Swap한다.
        mid = (low + high) // 2
        if array[low] > array[mid]:
            (array[low], array[mid]) = (array[mid], array[low])
        if array[mid] < array[high]:
            (array[mid], array[high]) = (array[high], array[mid])
        if array[low] > array[high]:
            (array[low], array[high]) = (array[mid], array[high])

def partition(array, low, high): 
    # 피봇을 찾는다.   
    choosePivot(array, low, high)
    pivot = array[high]
    i = low - 1
    # 배열의 각 요소를 pivot과 비교한다.
    for j in range(low, high):
        if array[j] <= pivot:
            i = i + 1
            (array[i], array[j]) = (array[j], array[i])
            print(i, j, array)
    (array[i + 1], array[high]) = (array[high], array[i + 1])    
    # partition이 끝난 위치(Pivot의 위치)를 반환한다.
    return i + 1

def quickSort(array, low, high):
    if low < high:
        # Pivot을 찾는다.
        c_pivot = partition(array, low, high)
        # low... c_pivot -1까지의 left array는 pivot보다 작다.
        # c_pivot + 1... high까지의 right array는 pivot보다 크다.
        #left array와 right array를 각각 quick sort 재귀 호출한다.
        quickSort(array, low, c_pivot - 1)
        quickSort(array, c_pivot + 1, high)
        
