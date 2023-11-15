#ifndef LIST_H
#define LIST_H

/* Standard Library */
#include <iostream>

template <class TL>
class List {
  private:
    template <class TE>
    class Element {
      private:
        TE m_data;
        Element<TE>* m_next;

      public:
        Element();
        Element(TE data, Element<TE>* next);
        ~Element();
        void setData(TE data);
        void setNext(Element<TE>* next);
        TE getData() const;
        Element<TE>* getNext() const;
    };

  private:
    Element<TL>* m_head;
    Element<TL>* m_tail;

  public:
    class Iterator {
      private:
        Element<TL>* m_position;

      public:
        Iterator(Element<TL>* position = NULL);
        ~Iterator();
        TL operator*();
        Iterator operator+(int);
        Iterator operator++();
        Iterator operator++(int);
        bool operator!=(const Iterator& it);
    };

  public:
    List();
    ~List();
    void pushBack(TL element);
    Element<TL>* getHead() const;
    Element<TL>* getTail() const;
};

/* Element's Method Definition */

template <class TL>
template <class TE>
List<TL>::Element<TE>::Element()
  : m_data(NULL)
  , m_next(NULL)
{

}

template <class TL>
template <class TE>
List<TL>::Element<TE>::Element(TE data, Element<TE>* next)
  : m_data(data)
  , m_next(next)
{

}

template <class TL>
template <class TE>
List<TL>::Element<TE>::~Element() {
  delete m_data;
  m_next = NULL;
}

template <class TL>
template <class TE>
void List<TL>::Element<TE>::setData(TE data) {
  if (data != NULL)
    m_data = data;
}

template <class TL>
template <class TE>
void List<TL>::Element<TE>::setNext(Element<TE>* next) {
  if (next != NULL)
    m_next = next;
}

template <class TL>
template <class TE>
TE List<TL>::Element<TE>::getData() const {
  return m_data;
}

template <class TL>
template <class TE>
List<TL>::Element<TE>* List<TL>::Element<TE>::getNext() const {
  return m_next;
}

/* Iterator's Method Definition */

template <class TL>
List<TL>::Iterator::Iterator(List<TL>::Element<TL>* position)
  : m_position(position)
{

}

template <class TL>
List<TL>::Iterator::~Iterator() {
  m_position = NULL;
}

template <class TL>
TL List<TL>::Iterator::operator*() {
  return m_position->getData();
}

template <class TL>
typename List<TL>::Iterator List<TL>::Iterator::operator+(int num) {
  List<TL>::Iterator it = *this;
  for (int i = 0; i < num && it.m_position->getNext(); i++)
    it++;

  return it;
}

template <class TL>
typename List<TL>::Iterator List<TL>::Iterator::operator++() {
  m_position = m_position->getNext();
  return *this;
}

template <class TL>
typename List<TL>::Iterator List<TL>::Iterator::operator++(int) {
  m_position = m_position->getNext();
  return *this;
}

template <class TL>
bool List<TL>::Iterator::operator!=(const List<TL>::Iterator& it) {
  return this->m_position != it.m_position;
}

/* List's Method Definition */

template <class TL>
List<TL>::List()
  : m_head(NULL)
  , m_tail(NULL)
{

}

template <class TL>
List<TL>::~List() {
  Element<TL>* element = this->getHead(); 
  Element<TL>* tmp;

  while (element != NULL) {
    tmp = element;
    element = element->getNext();
    delete tmp;
  }
}

template <class TL>
void List<TL>::pushBack(TL element) {
  Element<TL>* tmp = new Element<TL>;

  if (tmp == NULL) {
    std::cout << "Error allocating element\n";
    return;
  }

  tmp->setData(element);
  tmp->setNext(NULL);

  if (m_head == NULL)
    m_head = tmp;
  else
    m_tail->setNext(tmp);

  m_tail = tmp;
}

template <class TL>
List<TL>::Element<TL>* List<TL>::getHead() const {
  return m_head;
}

template <class TL>
List<TL>::Element<TL>* List<TL>::getTail() const {
  return m_tail;
}

#endif
