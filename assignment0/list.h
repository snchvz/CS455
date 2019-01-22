/*usser defined list. List consists of single-linked ordered float numbers.
main functions:
- insert
- delete
- read
- search
*/

#include <iostream>

using namespace std;

//template class T for data types
template<class T> class Link;
template<class T> class List_iterator;

template<class T>
class List
{
public: 
    typedef List_iterator<T> iterator;

    List();	//constructor
    List(const List<T> & l);	//copy constructor
    ~List();	//deconstructor

    bool empty() const; 	
    unsigned int size() const;	
    void push_back(const T & x);	//insert link at end of list given T value
    T & front() const;	//return first link value
    T & back() const;	//return last link value
    iterator begin() const;	//return iterator at fist link
    iterator end() const;	//return iterator at last link
    void insert(const T & x); //insert given T value
    void deleteNode(const T & x);//delete delete a link given T value,
    // calls search func to check is value is in the list first
    iterator search(const T & x); //search for value and returns an iterator position
    void read(); //print out entire list from first to last link

protected:
    Link<T> * first_link; //link at beginning of list
    Link<T> * last_link;	// link at end of list
    unsigned int my_size;	
};

//definitions


template<class T>
List<T>::List()
{
    first_link = 0;
    last_link = 0;
    my_size = 0;
}

template<class T>
List<T>::List(const List & l)
{
    first_link = 0;
    last_link = 0;
    //uses push_back to insert incoming link of list to the end of target list
    for(Link<T> * current = l.first_link; current != 0; current = current->next_link)
	push_back(current->value);
}

template<class T>
List<T>::~List()
{
    Link<T> * first = first_link;
    while(first != 0){
	Link<T> * next = first->next_link;
	delete first;
	first = next;
    }
}

template<class T>
bool List<T>::empty() const
{
    if (size() == 0)
	return true;
    return false;
}

template<class T>
unsigned int List<T>::size() const
{
    return my_size;
}

template<class T>
T & List<T>::front() const
{
    return *(begin());
}

template<class T>
T & List<T>::back() const
{
    return *(end());
}

template<class T>
void List<T>::push_back(const T & x)
{
    Link<T> * new_link  = new Link<T>(x);
    //if empty, first link and last link equal new link @param T value
    if (empty()){
	first_link = last_link = new_link;
	my_size++;
    } else {	//last link pointer points to new link
	last_link->next_link = new_link;
	new_link->prev_link = last_link;
	last_link = new_link;
	my_size++;
    }
}

template<class T>
typename List<T>::iterator List<T>::begin() const
{
    return iterator(first_link);
}

template<class T>
typename List<T>::iterator List<T>::end() const
{
    return iterator(last_link);
}

template<class T>
void List<T>::insert(const T & x)
{
    //if empty only call push_back
    if (empty()){
	push_back(x);
	return;
    } else if (first_link->value > x){	//add new link to beginning of list if first link > new link
	Link<T> * new_link = new Link<T>(x);
	new_link->next_link = first_link;
	first_link->prev_link = new_link;
	first_link = new_link;
	my_size++;
	return;
    } else {
	List_iterator<T> itr = begin();
	while (itr.current_link->value < x){
	    if (itr.current_link == last_link){	//push_back if all links are less than new link
		push_back(x);
	    	return;
	    }
	    ++itr;
	}
	Link<T> * new_link = new Link<T>(x);	//add new link in middle of list
	new_link->next_link = itr.current_link;
	new_link->prev_link = itr.current_link->prev_link;
	itr.current_link->prev_link = new_link;
	itr.current_link = new_link->prev_link;
	itr.current_link->next_link = new_link;	
	my_size++;
	return;
    }	    
} 

template<class T>
void List<T>::deleteNode(const T & x)
{
    List_iterator<T> ditr = search(x);	//return Null if search returns Null
    if (ditr.current_link == NULL)
	return;
    else if (ditr.current_link == first_link){ //delete first link and make next link first link
	first_link = first_link->next_link;
	delete ditr.current_link;
	my_size--;
    }	
    else if (ditr.current_link == last_link){ //delete last link and make prev link last link
	last_link = last_link->prev_link;
	delete ditr.current_link;
	my_size--;

    }
    else{	//delete link in middle of list
	ditr.current_link->prev_link->next_link = ditr.current_link->next_link;
        ditr.current_link->next_link->prev_link = ditr.current_link->prev_link; 	
	delete ditr.current_link;
	my_size--;
    }
    cout << x << " was deleted" << endl;
}

template<class T>
typename List<T>::iterator List<T>::search(const T & x)
{
    List_iterator<T> itr;	//return null itr if list is empty
    if (empty()){
	cout << "list is empty" << endl;
        return itr;
    }
    else {
	itr = begin();
	while (itr.current_link != last_link->next_link){
	    if (itr.current_link->value == x){	
		cout << x << " is in the list" << endl;
	        return itr;
	    }
	    ++itr;
	}
	cout << x << " is not on the list" << endl;
	return itr;
    }
}

template<class T>
void List<T>::read()
{
    if (empty())
	cout << "list is empty" << endl;
    else if (my_size == 1)
	cout << first_link->value << endl;
    else {	//traverse the list with iterator at fist link
        List_iterator<T> itr = begin();
        while(itr.current_link != last_link){
            cout << *itr << endl;
            ++itr;
        }
	cout << last_link->value << endl;
    }
}
//_____________________________________________________________________


template<class T>
class Link
{
private:
    Link(const T & x): value(x), next_link(0), prev_link(0){}

    T value;	
    Link<T> * next_link;
    Link<T> * prev_link;

    friend class List<T>;
    friend class List_iterator<T>;
};

template<class T>
class List_iterator
{
public:
    typedef List_iterator<T> iterator;

    List_iterator(Link<T> * source_link): current_link(source_link){}
    List_iterator(): current_link(0){}
    List_iterator(List_iterator<T> * source_iterator): current_link(source_iterator.current_link){}

    T & operator*();	//return value at link
    iterator & operator++(); // pre-increment

protected:
    Link<T> * current_link;

    friend class List<T>;
};

template<class T>
T & List_iterator<T>::operator*()
{
    return current_link->value;
}

template<class T>
List_iterator<T> & List_iterator<T>::operator++()
{
    current_link = current_link->next_link;
    return *this;
}















