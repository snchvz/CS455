#ifndef DLIST_H
#define DLIST_H

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
template<class T> class List;
template<class T> class Link;
template<class T> class List_iterator;
template<class T> class Dlink;
template<class T> class Dlist;
template<class T> class Dlist_iterator;

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
    virtual iterator begin() const;	//return iterator at fist link
    iterator end() const;	//return iterator at last link
    virtual void insert(const T & x); //insert given T value
    virtual void deleteNode(const T & x);//delete delete a link given T value,
    // calls search func to check is value is in the list first
    iterator search(const T & x); //search for value and returns an iterator position
    virtual void read(); //print out entire list from first to last link

private:
    Link<T> * first_link; //link at beginning of list
    Link<T> * last_link;	// link at end of list

protected:
    virtual void push_back(const T & x);
    unsigned int my_size;   

};
//_______________________________________________________


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
void List<T>::push_back(const T & x)
{
    Link<T> * new_link  = new Link<T>(x);
    //if empty, first link and last link equal new link @param T value
    if (empty()){
	first_link = last_link = new_link;
	my_size++;
    } else {	//last link pointer points to new link
	last_link->next_link = new_link;
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
    if (empty() or (last_link->value < x)){
	push_back(x);
	return;
    } else if (first_link->value >= x){	//add new link to beginning of list if first link > new link
	Link<T> * new_link = new Link<T>(x);
	new_link->next_link = first_link;
	first_link = new_link;
	my_size++;
	return;
    } else {
	Link<T> * new_link = new Link<T>(x);
	List_iterator<T> itr = begin();
	List_iterator<T> prev = begin();
 	while (itr.current_link->value < new_link->value){
	    ++itr;
    	    if (itr.current_link->value >= new_link->value)
		break;
	    ++prev;
	}
	prev.current_link->next_link = new_link;
	new_link->next_link = itr.current_link;	
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
    } else {	//delete link in middle of list
	List_iterator<T> prev = begin();
	while (prev.current_link != ditr.current_link){
	    if(prev.current_link->next_link == ditr.current_link)
		break;
	    ++prev;
	}
	if (ditr.current_link == last_link){
	    delete ditr.current_link;
	    last_link = prev.current_link;
	    my_size--;
	} else {
	    prev.current_link->next_link = ditr.current_link->next_link; 	
	    delete ditr.current_link;
	    my_size--;
	}
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
    else {
	Link<T> * rlink = first_link;
	while (rlink != last_link){
	    cout << rlink->value << endl;
	    rlink = rlink->next_link;
	}
	cout << last_link->value << endl;
    }
}

//____________________________________________________________________
//double linked list class
template<class T>
class Dlist: public List<T>
{
public:
    typedef Dlist_iterator<T> diterator;
    Dlist();
    ~Dlist();

    diterator dbegin() const;  
    void push_back(const T & x);
    diterator search(const T & x);
    void insert(const T & x);
    void deleteNode(const T & x);
    void read();

private:
    Dlink<T> * first_link;
    Dlink<T> * last_link;
    
};

template<class T>
Dlist<T>::Dlist()
{
    first_link = 0; 
    last_link = 0;
    this->my_size = 0;
}

template<class T>
Dlist<T>::~Dlist()
{
    Dlink<T> * first = first_link;
    while (first != 0){
	Dlink<T> * next = first -> next_link;
	delete first;
	first = next;
    }
}

template<class T>
typename Dlist<T>::diterator Dlist<T>::dbegin() const
{
    return diterator(first_link);
}

template<class T>
void Dlist<T>::push_back(const T & x)
{
	//insert link if list is empty or at end of list
	Dlink<T> * new_link = new Dlink<T>(x);
	if (this->empty()){
	    first_link = last_link = new_link;
	    this->my_size++;
	} else {
	    last_link->next_link = new_link;
	    new_link->prev_link = last_link;
	    last_link = new_link;
	    this->my_size++;
	}
}

template<class T>
typename Dlist<T>::diterator Dlist<T>::search(const T & x)
{  
    //uses seperate iterator for double link list
    Dlist_iterator<T> itr;
    if (this->empty()){
	cout << "list is empty" << endl;
        return itr;
    } else {
	itr = dbegin();
	while (itr.current_link != last_link->next_link){
	    if(itr.current_link->value == x){
		cout << x << " is in the list" << endl;
		return itr;
	    }
	    ++itr;
	}
	cout << x << " is not in the list" << endl;
	return itr;
    }
}

template<class T>
void Dlist<T>::insert(const T & x)
{
    //call push back if list is empty or insert is at end of list
    if (this->empty() or last_link->value <= x)
	this->push_back(x);
    //insert at beginning of list
    else if (first_link->value >= x){
	Dlink<T> * new_link = new Dlink<T>(x);
	new_link->next_link = first_link;
	first_link->prev_link = new_link;
	first_link = new_link;
	this->my_size++;
    //insert in middle of list
    } else {
	Dlink<T> * new_link = new Dlink<T>(x);
	Dlink<T> * pos = first_link;
	while (pos->value < new_link->value){
	    if (pos->next_link->value > new_link->value)
		break;
	    pos = pos->next_link;
	}
	new_link->next_link = pos->next_link;
	new_link->prev_link = pos;
	pos->next_link->prev_link = new_link;
	pos->next_link = new_link;
	this->my_size++;
    }
}


template<class T>
void Dlist<T>::deleteNode(const T & x)
{
    Dlist_iterator<T> ditr = search(x); //return iterator for searched position
    if (ditr.current_link == NULL)
	return; //return null is search returned null
    //delete if position at first link
    else if (ditr.current_link == first_link){
	first_link = first_link->next_link;
	delete ditr.current_link;
	this->my_size--;
    //delete if position at last link
    } else if (ditr.current_link == last_link){
	last_link = last_link->prev_link;
	delete ditr.current_link;
	this->my_size--;
    //delete if position in middle of list
    } else {
	ditr.current_link->prev_link->next_link = ditr.current_link->next_link;
	ditr.current_link->next_link->prev_link = ditr.current_link->prev_link;
	delete ditr.current_link;
	this->my_size--;
    }
    cout << x << " was deleted" << endl;
}


template<class T>
void Dlist<T>::read()
{
    if (this->empty())
	cout << "list is empty" << endl;
    else {
        Dlink<T> * rlink = first_link;
        while (rlink != last_link){
	    cout << rlink->value << endl;
	    rlink = rlink->next_link;
        }
        cout << last_link->value << endl;
    }
}


//_____________________________________________________________________


template<class T>
class Link
{
private:
    Link(const T & x): value(x), next_link(0){}
 
    T value;	
    Link<T> * next_link;
     
    friend class List<T>;
    friend class List_iterator<T>;
};

//_______________________________________________________________

template<class T>
class Dlink
{
private:
    Dlink(const T & x): value(x), next_link(0), prev_link(0){}

    T value;
    Dlink<T> * next_link;
    Dlink<T> * prev_link;

    friend class Dlist<T>;
    friend class Dlist_iterator<T>;
};

//_____________________________________________________________________
 
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

//_________________________________________________________________

template<class T>
class Dlist_iterator
{
public:
    typedef Dlist_iterator<T> diterator;

    Dlist_iterator(Dlink<T> * source_link): current_link(source_link){}
    Dlist_iterator(): current_link(0){}
    Dlist_iterator(Dlist_iterator<T> * source_iterator): current_link(source_iterator.current_link){}

    T & operator*();
    diterator & operator++();
protected:
    Dlink<T> * current_link;

    friend class Dlist<T>;
};

template<class T>
T & Dlist_iterator<T>::operator*()
{
    return current_link->value;
}

template<class T>
Dlist_iterator<T> & Dlist_iterator<T>::operator++()
{
    current_link = current_link->next_link;
    return *this;
}
    



#endif














