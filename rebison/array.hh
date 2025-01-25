/*
** array.hh
** Dynamic array class
*/

#ifndef array_hh
#define array_hh

#include "rebison.h"

template<typename T>
struct Array {
  T *m_a = NULL;
  size_t m_n = 0, m_alloc = 0;

  ~Array (void) { destroy(); }
  /* methods */
  size_t count (void) const { return m_n; }
  /* set the allocation size of the array */
  void alloc (size_t newsize) {
    m_a = (T *)xrealloc(m_a, (m_alloc = newsize) * sizeof(T));
  }
  /* set allocation size and clear count */
  void init (size_t size = 4) {
    alloc(size);
    m_n = 0;
  }
  /* destructor */
  void destroy (void) {
    free(m_a);
    m_a = NULL;
    m_n = m_alloc = 0;
  }
  /* increment count by N */
  void inc (int n = 1) {
    while (m_n + n >= m_alloc)
      alloc(m_alloc ? m_alloc * 2 : 4);
    m_n += n;
  }
  /* push a value */
  void push (const T &val) { inc(); gettop() = val; }
  /* clear count */
  void clear (void) { m_n = 0; }
  /* pop N values */
  void pop (int n = 1) {
    assert((size_t)n >= 0 && (size_t)n <= count());
    m_n -= n;
  }
  /* get pointer to top element */
  T &gettop (void) { assert(count()); return m_a[count()-1]; }
  const T &gettop (void) const { assert(count()); return m_a[count()-1]; }
  /* array index overload */
  T &operator [] (int i)
    { assert(i >= 0 && (size_t)i < count()); return m_a[i]; }
  const T &operator [] (int i) const
    { assert(i >= 0 && (size_t)i < count()); return m_a[i]; }
  /* copying */
  void copyfrom (const Array<T> &src) {
    m_n = 0;
    alloc(src.count());
    memcpy(m_a, src.m_a, src.count() * sizeof(T));
  }
};

#endif /* array_hh */
