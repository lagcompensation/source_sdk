#pragma once
#include "handle_entity.h"

#define NUM_ENT_ENTRY_BITS (11 + 2)
#define NUM_ENT_ENTRIES (1 << NUM_ENT_ENTRY_BITS)
#define INVALID_EHANDLE_INDEX 0xffffffff
#define NUM_SERIAL_NUM_BITS  16
#define NUM_SERIAL_NUM_SHIFT_BITS (32 - NUM_SERIAL_NUM_BITS)
#define ENT_ENTRY_MASK (( 1 << NUM_SERIAL_NUM_BITS) - 1)

class c_base_handle {
public:
	c_base_handle();
	c_base_handle(const c_base_handle& other);
	c_base_handle(unsigned long value);
	c_base_handle(int iEntry, int iSerialNumber);

	void init(int iEntry, int iSerialNumber);
	void term();

	bool is_valid();

	int get_entry_index();
	int get_serial_number();

	int to_int();
	bool operator !=(const c_base_handle& other);
	bool operator ==(const c_base_handle& other);
	bool operator ==(const i_handle_entity* ent);
	bool operator !=(const i_handle_entity* ent);
	bool operator <(const c_base_handle& other);

	const c_base_handle& operator=(const i_handle_entity* ent);
	const c_base_handle& set(const i_handle_entity* ent);

	i_handle_entity* get();
protected:
	unsigned long  m_index;
};

inline c_base_handle::c_base_handle() {
	m_index = INVALID_EHANDLE_INDEX;
}

inline c_base_handle::c_base_handle(const c_base_handle& other) {
	m_index = other.m_index;
}

inline c_base_handle::c_base_handle(unsigned long value) {
	m_index = value;
}

inline c_base_handle::c_base_handle(int iEntry, int iSerialNumber) {
	init(iEntry, iSerialNumber);
}

inline void c_base_handle::init(int iEntry, int iSerialNumber) {
	m_index = (unsigned long)(iEntry | (iSerialNumber << NUM_SERIAL_NUM_SHIFT_BITS));
}

inline void c_base_handle::term() {
	m_index = INVALID_EHANDLE_INDEX;
}

inline bool c_base_handle::is_valid() {
	return m_index != INVALID_EHANDLE_INDEX;
}

inline int c_base_handle::get_entry_index() {
	if (!is_valid())
		return NUM_ENT_ENTRIES - 1;

	return m_index & ENT_ENTRY_MASK;
}

inline int c_base_handle::get_serial_number() {
	return m_index >> NUM_SERIAL_NUM_SHIFT_BITS;
}

inline int c_base_handle::to_int() {
	return (int)m_index;
}

inline bool c_base_handle::operator !=(const c_base_handle& other) {
	return m_index != other.m_index;
}

inline bool c_base_handle::operator ==(const c_base_handle& other) {
	return m_index == other.m_index;
}

inline bool c_base_handle::operator ==(const i_handle_entity* ent) {
	return get() == ent;
}

inline bool c_base_handle::operator !=(const i_handle_entity* ent) {
	return get() != ent;
}

inline bool c_base_handle::operator <(const c_base_handle& other) {
	return m_index < other.m_index;
}

inline const c_base_handle& c_base_handle::operator=(const i_handle_entity* ent) {
	return set(ent);
}

inline const c_base_handle& c_base_handle::set(const i_handle_entity* ent) {
	if (ent)
		*this = ent->get_ref_ehandle();
	else
		m_index = INVALID_EHANDLE_INDEX;

	return *this;
}

template< class T >
class c_handle : public c_base_handle {
public:

	c_handle();
	c_handle(int iEntry, int iSerialNumber);
	c_handle(const c_base_handle& handle);
	c_handle(T* pVal);

	static c_handle<T> from_index(int index);

	T* get() const;
	void set(const T* pval);

	operator T* ();

	bool operator !();
	bool operator==(T* val);
	bool operator!=(T* val);
	const c_base_handle& operator=(const T* val);

	T* operator->();
};

template<class T>
c_handle<T>::c_handle() {
}

template<class T>
c_handle<T>::c_handle(int iEntry, int iSerialNumber) {
	init(iEntry, iSerialNumber);
}

template<class T>
c_handle<T>::c_handle(const c_base_handle& handle) : c_base_handle(handle) {
}

template<class T>
c_handle<T>::c_handle(T* pObj) {
	term();
	Set(pObj);
}

template<class T>
inline c_handle<T> c_handle<T>::from_index(int index) {
	c_handle<T> ret;
	ret.m_index = index;
	return ret;
}

template<class T>
inline T* c_handle<T>::get() const {
	return (T*)c_base_handle::get();
}

template<class T>
inline c_handle<T>::operator T* () {
	return get();
}

template<class T>
inline bool c_handle<T>::operator !() {
	return !get();
}

template<class T>
inline bool c_handle<T>::operator==(T* val) {
	return get() == val;
}

template<class T>
inline bool c_handle<T>::operator!=(T* val) {
	return get() != val;
}

template<class T>
void c_handle<T>::set(const T* pVal) {
	c_base_handle::set(reinterpret_cast<const i_handle_entity*>(pVal));
}

template<class T>
inline const c_base_handle& c_handle<T>::operator=(const T* val) {
	set(val);
	return *this;
}

template<class T>
T* c_handle<T>::operator -> () {
	return get();
}