#include <iostream>
template<typename T>
class Set
{
private:
    T* arr = nullptr; //integer pointer to store address of set
    int capacity = 0; //total storage capacity of set
    int current = 0; //number of current elements present
public:
    Set()   //default constructor
    {
        arr = new T[1];
        capacity = 1;
        current = 0;
    }

	~Set()
    {
        delete arr;
        capacity = 0;
        current = 0;
    }

    const T& operator[](int itrIndex) const
    {
        return arr[itrIndex];
    }
    //! Add an element to this set.
    void insert(T data)
    {
        if (current == capacity)
        {
            T* temp = new T[2 * capacity];
            for (int i = 0; i < capacity; i++) 
			{
                temp[i] = std::move(arr[i]);
            }
            delete[] arr;
            capacity *= 2;
            arr = std::move(temp);
        }
        arr[current] = std::move(data);
        current++;
        removeDuplicates(arr, current);
        quickSort(arr, 0, (current - 1));
    }

    void swapper(T* lhs, T* rhs)    //utility swapper function
    {
        T tempVal = std::move(*lhs);
        *lhs = std::move(*rhs);
        *rhs = std::move(tempVal);
    }

    int partition(T* arr, int low, int high) //takes last element as pivot and positions pivot at correct position in sorted array and places all elements smaller than the pivot to the left and all larger elements to the right. 
    {
        T pivot = std::move(arr[high]); //T pivot = arr[arrayHigh-1];
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

    //! Is a specified element already in the set?
    bool contains(const T& arrElement) const
    {
        bool found = false;
        int i = 0;
        while (i < current)
        {
            if (arrElement == arr[i])
            {
//          std::cout<<"true";
                found = true;
                return found;
            }
            i++;
        }
//      std::cout<<"false";
        return found;
    }

    void removeElement(T* arr, int index, int& sizeArr)
    {
        int i;
        for (i = index; i < sizeArr - 1; i++)
        {
            arr[i] = std::move(arr[i + 1]);
        }
        sizeArr--;
    }

    void removeDuplicates(T* arr, int& sizeArr) { //utility duplicate value removal function
        T element;
        int i;
        int j;
        for (i = 0; i < sizeArr; i++)
        {
            element = std::move(arr[i]);
            for (j = (i + 1); j < sizeArr; j++)
            {
                if (element == arr[j])
                {
                    removeElement(arr, j, sizeArr);
                    j--;
                }
            }
        }
    }

    //! How many values are in this set?
    size_t size() const {
        return current;
    }

	public:
    class Iterator {
    private:
        Set* ItrNode;
        int itrIndex;
    public:
        Iterator()
        {
            ItrNode = nullptr;
        }
        
        Iterator(Set<T>* SetP, int itrIndexer)
        {
            ItrNode = SetP;
            itrIndex = itrIndexer;

        }
        const T& operator*() const
        {
            return ItrNode->operator[](itrIndex);
        }
        Iterator& operator++()
        {
            ++itrIndex;
            return *this;
        }
        bool operator!= (const Iterator& other) const
        {
            return itrIndex != other.itrIndex;
        }
        bool operator== (const Iterator& other) const
        {
            return itrIndex == other.itrIndex;
        }
    };

    // Iterators over non-const sets:
    Iterator begin()
    {
        return Iterator{this,0};
    }
    Iterator end()
    {
		int newCurr = current-1;
        return Iterator{ this, newCurr };
    }
    Iterator find(const T& elemFind){
        bool found = contains(elemFind);
        if (found == true)
        {
            int i = 0;
            while(arr[i]!=elemFind)
            {
                i++;
            }
//            std::cout<<"set index is "<<i<<"\n";
            return Iterator{ this, i };
        }
        else
        {
//          std::cout<<"set index is "<<current-1<<"\n";
			int newCurr = current-1;
            return Iterator{ this, newCurr };
        }
    }

    class ConstIterator {
    private:
        const Set* ItrNode;
        int itrIndex;
    public:
        ConstIterator()
        {
            ItrNode = nullptr;
        }
        
        ConstIterator (const Set<T>* SetP, const int itrIndexer)
        {
            ItrNode = SetP;
            itrIndex = itrIndexer;

        }
        const T& operator*() const
        {
            return ItrNode->operator[](itrIndex);
        }
        ConstIterator& operator++()
        {
            itrIndex++;
            return *this;
        }
        bool operator!= (const ConstIterator& other) const
        {
            return itrIndex != other.itrIndex;
        }
        bool operator== (const ConstIterator& other) const
        {
            return itrIndex == other.itrIndex;
        }
    };

        // Iterators over non-const sets:
    ConstIterator begin() const
    {
        return ConstIterator{this,0};
    }
    ConstIterator end() const
    {
		int newCurr = current-1;
        return ConstIterator{ this, newCurr };
    }
    ConstIterator find(const T& elemFind) const{
        bool found = contains(elemFind);
        if (found == true)
        {
            int i = 0;
            while(arr[i]!=elemFind)
            {
                i++;
            }
//            std::cout<<"set index is "<<i<<"\n";
            return ConstIterator{ this, i };
        }
        else
        {
//          std::cout<<"set index is "<<current-1<<"\n";
			int newCurr = current-1;
            return ConstIterator{ this, newCurr };
        }
    }
    void outputSet()
    {
        for (int i = 0; i < current; i++) {
            std::cout << arr[i] << std::endl;
        }
    }
};

int main() {
    Set<double>set1;
    for (int n: {22,28,23,25,17,18}){
        set1.insert(n);
    }
    set1.outputSet();
    std::cout << set1.size() << " Size of set" << "\n";
    std::cout << *set1.end() << " Begin value" << std::endl;
    std::cout << *set1.end() << " End of set" << "\n";
    Set<char>set2;
    set2.insert('g');
    set2.insert('g');
    set2.insert('c');
    set2.insert('d');
    set2.insert('f');
    set2.insert('h');
    set2.insert('s');
    set2.insert('a');
    set2.insert('b');
    set2.insert('f');
    set2.size();
    set2.outputSet();
    std::cout << set2.size() << " Size of set" << "\n";
    std::cout << *set2.begin() << " Begin value" << std::endl;
    std::cout << *set2.end() << " End of set" << "\n";
    return 0;
}


