#include <iostream>
#include <cstring>

using namespace std;

class BoolVector {
    private:
        int bitSize = 0;   
        int arraySize = 1; 
        char* array;       

        void createArray() {
            array = new char[arraySize];
            for (int i = 0; i < 8; i++) {
                array[0] = (0 << i) & array[0];
            }
        }

        bool getItem(const int& bitIndex,
            const int& arrayIndex) const {
            return ((1 << bitIndex) & array[arrayIndex]) != 0;
        }

        void changeElement(const int& bitIndex, const int& arrayIndex, const bool item) {
            array[arrayIndex] = (~(1 << bitIndex)) & array[arrayIndex] | (item << bitIndex);
        }

        void increaseSizeArray() {
            char* tempArray = array;
            array = new char[arraySize + 1];
            memcpy(array, tempArray, arraySize);
            delete[] tempArray;
            arraySize++;
        }

        void decreaseSizeArray() {
            arraySize--;
            char* tempArray = array;
            array = new char[arraySize];
            memcpy(array, tempArray, arraySize);
            delete[] tempArray;
        }

    public:
        BoolVector() {
            createArray();
        };

        ~BoolVector() {
            delete[] array;
        }

        int size() {
            return bitSize;
        }

        void changeElement(int index, bool value) { 
            int bitIndex = index % 8;
            int arrayIndex = index / 8;
            changeElement(bitIndex, arrayIndex, value);
        }

        bool operator[](int index) const {
            int arrayIndex = index / 8;
            int bitIndex = index % 8;
            return ((1 << bitIndex) & array[arrayIndex]) != 0;
        }

        void pushBack(bool item) {
            bitSize++;
            int index = (bitSize - 1) % 8;
            int arrayIndex = (bitSize - 1) / 8;
            if (((bitSize - 1) % 8 == 0) and (bitSize != 0))
                increaseSizeArray();
            changeElement(index, arrayIndex, item);
        }

        void insert(const int& position, const int& count, const bool& value) { 
            if ((bitSize + count) % 9 == 0)
                increaseSizeArray();
            for (int i = (bitSize - 1) + count; i > position; i--)
                changeElement(i % 8, i / 8, getItem((i - count) % 8, (i - count) / 8));
            for (int i = position; i < position + count; i++)
                changeElement(i % 8, i / 8, value);
            bitSize += count;
        }

        void erase(const int& position,
            const int& count) { 
            int index = position % 8;
            for (int j = position; j < bitSize - 1; j++)
                changeElement(j % 8, j / 8, getItem((j + count) % 8, (j + count) / 8));  
            bitSize -= count;
            if ((bitSize / 8) < (arraySize - 1)){
                decreaseSizeArray();  
            }
        }

        void outArray() const {
            for (int i = 0; i < bitSize; i++)
                cout << (bool)(*this)[i] << " ";
            cout << "| " << bitSize << endl;
        }
};





int main() {
    BoolVector boolVector;
    boolVector.pushBack(false); boolVector.outArray();
    boolVector.pushBack(true); boolVector.outArray();
    boolVector.pushBack(true); boolVector.outArray();
    boolVector.insert(2, 3, false); boolVector.outArray();
    boolVector.erase(2, 3); boolVector.outArray();
    boolVector.changeElement(0, true); boolVector.outArray();
    cout << boolVector[0] << endl;
    return 0;
}