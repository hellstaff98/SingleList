#ifndef DICTIONARY_LIST_HPP
#define DICTIONARY_LIST_HPP
template <typename T>
class DictionaryList
{
private:
	template <typename U>
	struct Node
	{
		Node(const T& data) :
			data_(data)
		{}
		T data_;
		Node<T>* next_{ nullptr };
	};
public:
	~DictionaryList();
	DictionaryList() : head_(nullptr) {};
	DictionaryList(const DictionaryList<T>& other);
	bool insert(const T& data);
	bool insertToEnd(const T& data);
	bool insertUnique(const T& data);
	bool insertInOrder(const T& data);
	bool search(const T& data);
	bool remove(const T& data);
	
	void merge(DictionaryList<T>& list);
	void deleteWords(const DictionaryList<T>& list);
	template <typename U>
	friend DictionaryList<U> getIntersection( DictionaryList<U>& firstDict, DictionaryList<U>& secondDict);
	template <typename U>
	friend std::ostream& operator<< (std::ostream& out, const DictionaryList<U>& list);
private:
	Node<T>* head_{ nullptr };
};

template <typename T>
DictionaryList<T>::DictionaryList(const DictionaryList<T>& other)
{
	Node<T> *current = other.head_;
	while (current)
	{
		insert(current->data_);
		current = current->next_;
	}
	
}

template <typename T>
DictionaryList<T>::~DictionaryList()
{
	if (head_)
	{
		while (head_->next_)
		{
			Node<T>* current = head_;
			head_ = head_->next_;
			delete current;
		}
		delete head_;
	}
}
template <typename T>
bool DictionaryList<T>::insert(const T& data)
{
	bool isAdded = false;
	if (!head_)
	{
		Node<T>* node = new Node<T>(data);
		head_ = node;
		isAdded = true;
	}
	else
	{
		Node<T>* node = new Node<T>(data);
		node->next_ = head_;
		head_ = node;
		isAdded = true;
	}
	return isAdded;
}
template <typename T>
std::ostream& operator<< (std::ostream& out, const DictionaryList<T>& list)
{
	typename DictionaryList<T>::template Node<T> *current = list.head_;
	while (current)
	{
		if (current->next_)
		{
			out << current->data_ << ", ";
		}
		else
		{
			out << current->data_ << "\n";
		}
		current = current->next_;
	}
	return out;
}

template <typename T>
bool DictionaryList<T>::insertToEnd(const T& data)
{
	bool isAdded = false;
	if (!head_)
	{
		Node<T>* node = new Node<T>(data);
		head_ = node;
		isAdded = true;
	}
	else
	{
		Node<T>* current = head_;
		while (current->next_)
		{
			current = current->next_;
		}
		Node<T>* node = new Node<T>(data);
		current->next_ = node;
		isAdded = true;
	}
	return isAdded;
}

template <typename T>
bool DictionaryList<T>::insertUnique(const T& data)
{
	bool isAdded = false;
	if (!head_)
	{
		Node<T>* node = new Node<T>(data);
		head_ = node;
		isAdded = true;
	}
	else
	{
		bool isSameFound = false;
		Node<T>* current = head_;
		while (current)
		{
			if (current->data_ == data)
			{
				isSameFound = true;
				break;
			}
			current = current->next_;
		}
		if (!isSameFound)
		{
			Node<T>* node = new Node<T>(data);
			node->next_ = head_;
			head_ = node;
			isAdded = true;
		}
	}
	return isAdded;
}

template <typename T>
bool DictionaryList<T>::insertInOrder(const T& data)
{
	bool isAdded = false;
	if (!head_)
	{
		Node<T>* node = new Node<T>(data);
		head_ = node;
		isAdded = true;
	}
	else
	{
		Node<T>* current = head_;
		if (current->data_ > data)
		{
			Node<T>* node = new Node<T>(data);
			node->next_ = head_;
			head_ = node;
			isAdded = true;
		}
		while (current)
		{
			if (((current->data_ < data) && (!current->next_)) || ((current->data_ < data) && (current->next_->data_ > data)))
			{
				if (!isAdded)
				{
					Node<T>* node = new Node<T>(data);
					node->next_ = current->next_;
					current->next_ = node;
					isAdded = true;
				}
			}
			current = current->next_;
		}
	}
	return isAdded;
}

template <typename T>
bool DictionaryList<T>::search(const T& data)
{
	Node<T>* current = head_;
	while (current)
	{
		if (current->data_ == data)
		{
			return true;
		}
		current = current->next_;
	}
	return false;
}

template <typename T>
bool DictionaryList<T>::remove(const T& data)
{
	bool isDeleted = false;
	Node<T>* current = head_;
	Node<T>* temp = nullptr;
	if (current->data_ == data)
	{
		temp = head_;
		head_ = current->next_;
		current = head_;
		delete temp;
		isDeleted = true;
	}
	while (current->next_ && !isDeleted)
	{
		if (current->next_->data_ == data)
		{
			temp = current->next_;
			current->next_ = current->next_->next_;
			delete temp;
			isDeleted = true;
		}
		if (current->next_)
		{
			current = current->next_;
		}
	}
	return isDeleted;
}

template <typename T>
void DictionaryList<T>::merge(DictionaryList<T>& list)
{
	while (list.head_)
	{
		if (list.head_->data_ != head_->data_)
		{
			T data = list.head_->data_;
			Node<T>* currentFirst = head_;
			if (currentFirst->data_ > data)
			{
				Node<T>* node = list.head_;
				list.head_ = list.head_->next_;
				node->next_ = head_;
				head_ = node;
				
				currentFirst = currentFirst->next_;
			}
			while (currentFirst)
			{
				if (currentFirst->data_ == data)
				{
					Node<T>* forRemoving = list.head_;
					if (list.head_->next_)
					{
						list.head_ = list.head_->next_;
					}
					delete forRemoving;
					break;
				}
				else
				{
					if (((currentFirst->data_ < data) && (!currentFirst->next_)) || ((currentFirst->data_ < data) && (currentFirst->next_->data_ > data)))
					{
						Node<T>* node = list.head_;
						list.head_ = list.head_->next_;
						node->next_ = currentFirst->next_;
						currentFirst->next_ = node;
						currentFirst = currentFirst->next_;
					}
					currentFirst = currentFirst->next_;
				}
				
			}
		}
		else
		{
			Node<T>* forRemoving = list.head_;
			if (list.head_->next_)
			{
				list.head_ = list.head_->next_;
			}
			delete forRemoving;
		}
	}
	
}
template <typename T>
void DictionaryList<T>::deleteWords(const DictionaryList<T>& list)
{
	Node<T>* current = list.head_;
	while (current)
	{
		remove(current->data_);
		current = current->next_;
	}
}

template <typename T>
DictionaryList<T> getIntersection(DictionaryList<T>& firstDict, DictionaryList<T>& secondDict)
{
	typename DictionaryList<T>::template Node<T>* current = firstDict.head_;
	DictionaryList<T> result;
	secondDict.search(current->data_);
	while (current)
	{
		if (secondDict.search(current->data_))
		{
			result.insertInOrder(current->data_);
		}
		current = current->next_;
	}
	return result;
}
#endif // !DICTIONARY_LIST_HPP

