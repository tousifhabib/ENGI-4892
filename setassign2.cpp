#include<iostream>

template<typename T>
class Set
{
private:
    T* arr; //integer pointer to store address of set
    int capacity; //total storage capacity of set
    int current; //number of current elements present
public:
    Set()   //default constructor
    {
        arr = new T[1];
        capacity = 1;
        current = 0;
    }
    //! Add an element to this set.
    void insert(T data)
    {
        if (current == capacity)
        {
            T* temp = new T[2 * capacity];
            for (int i = 0; i < capacity; i++) {
                temp[i] = arr[i];
            }
            delete[] arr;
            capacity *= 2;
            arr = temp;
        }
        arr[current] = data;
        current++;
        removeDuplicates(arr, current);
        quickSort(arr, 0, (current - 1));
    }
    void swapper(T* lhs, T* rhs)    //utility swapper function
    {
        T tempVal = *lhs;
        *lhs = *rhs;
        *rhs = tempVal;
    }

    int partition(T* arr, int low, int high) //takes last element as pivot and positions pivot at correct position in sorted array and places all elements smaller than the pivot to the left and all larger elements to the right. 
    {
        T pivot = arr[high]; //T pivot = arr[arrayHigh-1];
        int i = (low - 1);
        for (int j = low; j <= (high - 1); j++) {
            if (arr[j] <= pivot) {
                i++;
                swapper(&arr[i], &arr[j]);
            }
        }
        swapper(&arr[i + 1], &arr[high]);
        return (i + 1);
    }

    void quickSort(T* arr, int low, int high) //sorting fucntion
    {
        if (low < high)
        {
            int pi = partition(arr, low, high); //partitioning index
            quickSort(arr, low, (pi - 1));
            quickSort(arr, (pi + 1), high);
        }

    }

    void outputSet() {
        for (int i = 0; i < current; i++) {
            std::cout << arr[i] << std::endl;
        }
        //      contains(9);
    }
    // //! Is a specified element already in the set?
    bool contains(const T& arrElement) const
    {
        bool found = false;
        int i = 0;
        while (i < current)
        {
            if (arrElement == arr[i])
            {
                //                std::cout<<"true";
                found = true;
                return found;
            }
            i++;
        }
        //        std::cout<<"false";
        return found;
    }

    void removeElement(T* arr, int index, int& sizeArr)
    {
        int i;
        for (i = index; i < sizeArr - 1; i++)
        {
            arr[i] == arr[i + 1];
        }
        sizeArr--;
    }

    void removeDuplicates(T* arr, int& sizeArr) {
        T element;
        int i;
        int j;
        for (i = 0; i < sizeArr; i++)
        {
            element = arr[i];
            for (int j = (i + 1); j < sizeArr; j++)
            {
                if (element == arr[j])
                {
                    removeElement(arr, j, sizeArr);
                    j--;
                }
            }
        }
    }

    // //! How many values are in this set?
    size_t size() const {
        return current;
    }

    // // Iterators over const and non-const sets:
    // Iterator begin();
    // ConstIterator begin() const;

    // Iterator end();
    // ConstIterator end() const;

    // /**
    //  * Look up a specific value within this set.
    //  *
    //  * This should return an iterator that is equal to end() if the value
    //  * is not found.
    //  */
    // Iterator find(const T&);
    // ConstIterator find(const T&) const;
};

int main() {
    Set<int>set1;
    set1.insert(3);
    set1.insert(4);
    set1.insert(4);
    set1.insert(4);
    set1.insert(4);
    set1.insert(5);
    set1.insert(1);
    set1.insert(20);
    set1.insert(6);
    set1.insert(8);
    set1.insert(8);
    set1.insert(20);
    set1.insert(21);
    set1.insert(15);
    set1.size();
    set1.outputSet();
    Set<char>set2;
    set2.insert('g');
    set2.insert('g');
    set2.insert('c');
    set2.insert('d');
    set2.insert('f');
    set2.insert('h');
    set2.insert('a');
    set2.insert('a');
    set2.insert('b');
    set2.insert('f');
    set2.size();
    set2.outputSet();
    // return 0;
}
