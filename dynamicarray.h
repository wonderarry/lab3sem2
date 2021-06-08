#include <cassert>
#include <string>
#include <fstream>
template <typename T>  class DynamicArray {
protected:
    T *data;
    int size;
public:

    int getSize(){
        return this->size;
    }

    int Get(int index){
        return this->data[index];
    }

    void Set(int index, T item){
        assert((index < 0 || index >= this->size) && "Index is out of range");
        this->data[index] = item;
    }

    void Resize(int newSize){
        assert(newSize < 0 && "Index is out of range");
        T *newArray = new T[newSize];
        if (newSize > this->size){
            for (int i = 0; i < this->size; ++i){
                newArray[i] = this->data[i];
            }
            for (int i = this->size; i < newSize; ++i){
                newArray[i] = 0;
            }

        }
        else{
            for (int i = 0; i < newSize; ++i){
                newArray[i] = this->data[i];
            }
        }
        delete[] this->data;
        this->size = newSize;
        this->data = newArray;
    }

    void InsertAt(int index, T item){
        assert((index < 0 || index > this->size) && "Index is out of range");
        this->Resize(this->size + 1);
        T tempContainer = this->data[index];
        T tempContainer2;
        this->data[index] = item;
        for (int i = index + 1; i < this->size; ++i){
            tempContainer2 = this->data[i];
            this->data[i] = tempContainer;
            tempContainer = tempContainer2;
        }
    }

    T PopAt(int index){
        assert(index < 0 && "Index is out of range");
        T returnContainer = this->data[index];
        for (int i = index; i < this->size - 1; ++i){
            this->data[i] = this->data[i+1];
        }
        this->Resize(this->size - 1);
        return returnContainer;
    }

    T LookFor(T item){
        int low = 0;
        int high = this->size - 1;
        int mid;
        while (low <= high){
            mid = (low + high) / 2;
            if (this->data[mid] < item){
                low = mid + 1;
            }
            else if (this->data[mid] > item){
                high = mid - 1;
            }
            else{
                return mid;
            }
        }
        return -1;
    }



    DynamicArray(){
        this->data = nullptr;
        this->size = 0;
    }
    DynamicArray(int givenSize){
        this->size = givenSize;
        this->data = new T[givenSize];
    }
    DynamicArray(T* items, int givenSize){
        this->size = givenSize;
        this->data = new T[givenSize];
        for (int i = 0; i < givenSize; ++i){
            this->data[i] = items[i];
        }
    }
    DynamicArray(DynamicArray<T> &item){
        this->size = item.getSize();
        this->data = new T[this->size];
        for (int i = 0; i < this->size; ++i){
            this->data[i] = item.Get(i);
        }
    }
    DynamicArray(DynamicArray &item, T (*lambdaFunction)(T)){ //а че так можно было что ли?
        this->data = new T[item.GetSize()];
        this->size = item.GetSize();
        for (int i = 0; i < this->size; ++i){
            this->data[i] = lambdaFunction(item.Get(i));
        }
    }
    DynamicArray(DynamicArray &item, bool (*discrFunction)(T)){
        this->data = new T[item.GetSize()];
        this->size = item.GetSize();
        int i = 0;
        for (int count = 0; count < this->size; ++count){
            if (discrFunction(item.Get(count))){
                this->data[i] = item.Get(count);
                ++i;
            }
        }
        this->Resize(i + 1);
    }
    DynamicArray<T> *Concat(DynamicArray &item){
        DynamicArray<T> *concatItem  = new DynamicArray<T>{this->data, this->size};
        concatItem->Resize(item.GetSize() + this->size);
        for (int i = 0; i < item.GetSize(); ++i){
            concatItem.Set(i + this->size, item.Get(i));
        }
        return concatItem;
    }

    ~DynamicArray(){
        delete[] this->data;
    }

    void SwapAt(int i1, int i2){
        T temp;
        temp = this->data[i1];
        this->data[i1] = this->data[i2];
        this->data[i2] = temp;
    }

    int MinIndexSearch(int i, int j){
        if (i == j){
            return i;
        }
        int k = MinIndexSearch(i + 1, j);
        return (this->data[i] < this->data[k]) ? 1 : k;
    }

    void SelectionSort(int n, int index = 0){
        if (index == n){
            return;
        }
        int k = MinIndexSearch(index, n - 1);
        if (k != index){
            SwapAt(k, index);
        }
        SelectionSort(a, n, index + 1);
    }

    void SortArray(){
        SelectionSort(this->size);
    }




};


template <typename T> class BinarySearchTree : public DynamicArray<T> {
private:
    std::string ordering; //1 - node, 2 - left, 3 - right
    int *visited;
    int lowerSubtreeBoundary;
    int upperSubtreeBoundary;
public:
    BinarySearchTree(){
        initDefValues();
        DynamicArray();
    }
    BinarySearchTree(int arraySize){
        initDefValues();
        DynamicArray(arraySize);
    }
    BinarySearchTree(T* items, int arraySize){
        initDefValues();
        DynamicArray(items, arraySize);
    }
    BinarySearchTree(BinarySearchTree &item){
        DynamicArray();
        initDefValues();
        this->size = item.getSize();
        this->data = new T[this->size];
        for (int i = 0; i < this->size; ++i){
            this->data[i] = item.Get(i);
        }
    }
    void AssessOrdering(std::string newOrderValue){
        this->ordering = newOrderValue;
    }

    void Order(int inputMode = 1, std::string fileName = "", int specificIndex == -1){
        this->visited = new int[this->size];
        for (int i = 0; i < this->size; ++i){
            this->visited[i] = 0;
        }
        printOrdered();
        delete[] this->visited;
        if (specificIndex != -1){
            this->lowerSubtreeBoundary = -1;
            this->upperSubtreeBoundary = -1;
        }
    }

    void preferredOutput(int index, int outputFlag = 1, std::string fileName = ""){ //1 - cout, 2 - file
        if (this->lowerSubtreeBoundary != -1){
            if (index < this->lowerSubtreeBoundary || index > this->upperSubtreeBoundary){
                return;
            }
        }
        if (outputFlag == 1){
            std::cout << this->data[index] << ' ';
        }
        else if (outputFlag == 2){
            ofstream fileObject(fileName);
            fileObject << this->data[index] << ' ';
            fileObject.close();
        }

    }
    void printOrdered(int currentIndex = this->size / 2, int leastIndex = 0, int mostIndex = this->size - 1, int inputMode = 1, std::string fileName = "", int specificIndex = -1){
        for (int i = 0; i < 2; ++i){
            if (this->ordering[i] == '1'){
                preferredOutput(this->data[currentIndex], inputMode, fileName);
            }
            else if (this->ordering[i] == '2' && ((leastIndex + currentIndex) / 2 != currentIndex) && this->visited[(leastIndex + currentIndex) / 2] != 1){
                this->visited[(leastIndex + currentIndex) / 2] = 1;
                if ((leastIndex + currentIndex) / 2 == specificIndex){
                    this->lowerSubtreeBoundary = leastIndex;
                    this->upperSubtreeBoundary = currentIndex;
                }
                printOrdered((leastIndex + currentIndex) / 2, leastIndex, currentIndex, inputMode, fileName, specificIndex);
            }
            else if (this->ordering[i] == '3' && ((mostIndex + currentIndex + 1) / 2 != currentIndex) && this->visited[(mostIndex + currentIndex + 1) / 2] != 1){
                this->visited[(mostIndex + currentIndex + 1) / 2] = 1;
                if ((mostIndex + currentIndex + 1) / 2 == specificIndex){
                    this->lowerSubtreeBoundary = currentIndex;
                    this->upperSubtreeBoundary = mostIndex;
                }
                printOrdered((mostIndex + currentIndex + 1) / 2, currentIndex, mostIndex, inputMode, fileName, specificIndex);
            }
        }
    }


    void initDefValues(){
        this->visited = nullptr;
        this->lowerSubtreeBoundary = -1;
        this->upperSubtreeBoundary = -1;
    }
    BinarySearchTree(BinarySearchTree &item, T (*lambdaFunction)(T)){


        this->data = new T[item.GetSize()];
        this->size = item.GetSize();
        for (int i = 0; i < this->size; ++i){
            this->data[i] = lambdaFunction(item.Get(i));
        }
    }
    BinarySearchTree(BinarySearchTree &item, bool (*discrFunction)(T)){
        initDefValues();
        this->data = new T[item.GetSize()];
        this->size = item.GetSize();
        int i = 0;
        for (int count = 0; count < this->size; ++count){
            if (discrFunction(item.Get(count))){
                this->data[i] = item.Get(count);
                ++i;
            }
        }
        this->Resize(i + 1);
    }
    template <typename U>
    U Reduce(U (*reduceFunction)(T, U), U starterValue = U()){
        U resultKeeper = reduceFunction(this->data[0], starterValue);
        for (int i = 1; i < this->size; ++i){
            resultKeeper = reduceFunction(this->data[i], resultKeeper);
        }
        return resultKeeper;
    }
    T PopFromTree(int index){
        return PopAt(index);
    }

    int findFirstBigger(T item){
        if (item < this->data[0]){
            return 0;
        }
        if (item > this->data[this->size - 1]){
            return this->size;
        }
        int low = 0;
        int high = this->size - 1;
        int mid;
        while (low <= high){
            mid = (low + high) / 2;
            if (this->data[mid] <= item && this->data[mid + 1] >= item){
                return mid + 1;
            }
            if (this->data[mid] >= item && this->data[mid - 1] <= item){
                return mid;
            }
            else if (this->data[mid] < item){
                low = mid + 1;
            }
            else if (this->data[mid] > item){
                high = mid - 1;
            }
            else{
                return mid;
            }
        }

    }
    InsertInTree(T item){
        InsertAt(findFirstBigger(item));
    }
    FindInTree(T item){
        LookFor(item);
    }

};


template <typename T> class BinaryHeap : public DynamicArray<T>{
private:
    DynamicArray<T> subheapKeeper;
public:
    BinaryHeap(){
        subheapKeeper = DynamicArray<T>();
        DynamicArray();
    }
    BinaryHeap(int size){
        subheapKeeper = DynamicArray<T>();
        DynamicArray(size);
    }
    BinaryHeap(T* items, int size){
        subheapKeeper = DynamicArray<T>();
        DynamicArray(items, size);
    }
    BinaryHeap(BinaryHeap &item){
        subheapKeeper = DynamicArray<T>();
        DynamicArray();
        this->size = item.getSize();
        this->data = new T[this->size];
        for (int i = 0; i < this->size; ++i){
            this->data[i] = item.Get(i);
        }
    }

    void Heapify(int i){
        int smallest =  i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        if (left < right && this->data[left] < this->data[smallest]){
            smallest = left;
        }
        if (right < left && this->data[right] < this->data[smallest]){
            smallest = right;
        }
        if (smallest != i){
            SwapAt(smallest, i);
        }
        Heapify(smallest);
    }

    void BuildHeap(){
        for (int i = n; i >= 0; --i){
            Heapify(i);
        }
    }

    void SubheapExtraction(int node, bool flagTracking = false){
        if (flagTracking){
            this->subheapKeeper.InsertAt(this->subheapKeeper->GetSize(), node);
        }
        std::cout << node;
        if (node * 2 + 1 < this->size){
            SubheapExtraction(node * 2 + 1);
        }
        if (node * 2 + 2 < this->size){
            SubheapExtraction(node * 2 + 2);
        }
    }

    bool isSubheapIncluded(){
        this->subheapKeeper.Resize(0);
        DynamicArray<T> obtainedSequence {};
        int length;
        std::cout << "Сколько элементов будет в последовательности?:";
        std::cin >> length;
        T temp;
        for (int i = 0; i < length; ++i){
            std::cin >> temp;
            obtainedSequence.InsertAt(obtainedSequence.GetSize(), temp);
        }
        SubheapExtraction(obtainedSequence.Get(0), true);
        for (int i = 0; i < length; ++i){
            if (obtainedSequence.Get(i) != this->subheapKeeper->Get(i)){
                return false;
            }
        }
        return true;
    }

}
