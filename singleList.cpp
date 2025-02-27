

#include <iostream>
#include "DictionaryList.hpp"


int main()
{
    DictionaryList<int> numbers;
    

    numbers.insert(133);
    numbers.insert(18);
    numbers.insert(120);
    numbers.insert(35);
    numbers.insert(1);
    numbers.insert(23423);
    numbers.insert(3);

    
    std::cout << "First dictionary: " << numbers << "\n";

    DictionaryList<int> orderedNumbers;
    orderedNumbers.insertInOrder(4);
    orderedNumbers.insertInOrder(8);
    orderedNumbers.insertInOrder(1);
    orderedNumbers.insertInOrder(35);
    orderedNumbers.insertInOrder(15);
    orderedNumbers.insertInOrder(55);

    orderedNumbers.insertInOrder(2);
    orderedNumbers.insertInOrder(16);
    orderedNumbers.insertInOrder(15);
    std::cout << "Second dictionary (ordered): " << orderedNumbers << "\n";

    std::cout << "search(84) for second dictionary: " << std::boolalpha << orderedNumbers.search(84) << "\n\n";
    orderedNumbers.remove(15);
    orderedNumbers.remove(8);
    std::cout << "After removing 8 and 15: " << orderedNumbers << "\n";

    orderedNumbers.merge(numbers);
    std::cout << "Merged (second dictionary): " << orderedNumbers << "\n";
    std::cout << "Merged (first dictionary): " << numbers << "\n";

    numbers.insert(133);
    numbers.insert(18);
    numbers.insert(120);
    std::cout << "First dictionary: " << numbers << "\n";
    orderedNumbers.deleteWords(numbers);
    std::cout << "Delete words (dict1) from dict2: " << orderedNumbers;

    orderedNumbers.insertInOrder(133);
    orderedNumbers.insertInOrder(120);
    orderedNumbers.insertInOrder(18);

    std::cout << "The intersection of 1st and 2nd dictionaries: " << getIntersection(orderedNumbers, numbers) << "\n";
    DictionaryList<int> listCopy = numbers;
    return 0;
}
