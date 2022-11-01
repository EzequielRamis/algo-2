template<typename T>
string_map<T>::string_map(): _size(0), raiz(nullptr) {}

template<typename T>
string_map<T>::string_map(const string_map<T> &aCopiar)
        : string_map() { *this = aCopiar; } // Provisto por la catedra: utiliza el operador asignacion para realizar la copia.

template<typename T>
string_map<T> &string_map<T>::operator=(const string_map<T> &d) {
    this->_size = d._size;
    if (d.raiz == nullptr)
        this->raiz = nullptr;
    else
        this->raiz = new Nodo(*d.raiz);
    return *this;
}

template<typename T>
string_map<T>::Nodo::Nodo():
        definicion(nullptr), siguientes(vector<Nodo *>(ASCII_SIZE, nullptr)) {}

template<typename T>
string_map<T>::Nodo::Nodo(const Nodo &aCopiar) : Nodo() { *this = aCopiar; }

template<typename T>
typename string_map<T>::Nodo &string_map<T>::Nodo::operator=(const Nodo &d) {
    delete definicion;
    for (auto l: siguientes)
        delete l;
    if (d.definicion != nullptr)
        definicion = new T(*d.definicion);
    for (int i = 0; i < (int) d.siguientes.size(); i++)
        if (d.siguientes[i] == nullptr)
            siguientes[i] = nullptr;
        else
            siguientes[i] = new Nodo(*d.siguientes[i]);
    return *this;
}

template<typename T>
bool string_map<T>::Nodo::hayPrefijos() {
    for (auto l: this->siguientes)
        if (l != nullptr)
            return true;
    return false;
}

template<typename T>
string_map<T>::~string_map() {
    borrarNodos(raiz);
}

template<typename T>
void string_map<T>::borrarNodos(string_map::Nodo *n) {
    if (n != nullptr) {
        for (auto pre: n->siguientes)
            borrarNodos(pre);
        delete n->definicion;
        delete n;
    }
}

template<typename T>
void string_map<T>::insert(const pair<string, T> &kv) {
    pair<int, Nodo *> rec = recorrer(kv.first);
    Nodo *pre;
    if (raiz == nullptr) {
        raiz = new Nodo();
        pre = raiz;
    } else
        pre = rec.second;
    for (int i = rec.first; i < (int) kv.first.size(); i++) {
        int letra = int(kv.first[i]);
        pre->siguientes[letra] = new Nodo();
        pre = pre->siguientes[letra];
    }
    if (pre->definicion == nullptr)
        _size++;
    else
        delete pre->definicion;
    pre->definicion = new T(kv.second);
}

template<typename T>
T &string_map<T>::operator[](const string &clave) {
    if (count(clave) == 0) {
        T *v = new T();
        insert(make_pair(clave, *v));
        delete v;
    }
    return at(clave);
}


template<typename T>
int string_map<T>::count(const string &clave) const {
    pair<int, Nodo *> rec = recorrer(clave);
    return rec.first == clave.size() && rec.second->definicion != nullptr ? 1 : 0;
}

template<typename T>
const T &string_map<T>::at(const string &clave) const {
    return *recorrer(clave).second->definicion;
}

template<typename T>
T &string_map<T>::at(const string &clave) {
    return *recorrer(clave).second->definicion;
}

template<typename T>
void string_map<T>::erase(const string &clave) {
    vector<Nodo *> recorrido;
    Nodo *m = raiz;
    recorrido.push_back(m);
    for (auto l: clave) {
        m = m->siguientes[int(l)];
        recorrido.push_back(m);
    }
    Nodo *ult = recorrido.back();
    delete ult->definicion;
    ult->definicion = nullptr;
    for (int i = ((int) recorrido.size()) - 2; i >= 0; i--) {
        Nodo *letra = recorrido[i];
        if (!letra->hayPrefijos() && letra->definicion == nullptr)
            letra->siguientes.clear();
    }
    _size--;
}

template<typename T>
int string_map<T>::size() const {
    return _size;
}

template<typename T>
bool string_map<T>::empty() const {
    return _size == 0;
}

template<typename T>
pair<int, typename string_map<T>::Nodo *> string_map<T>::recorrer(const std::string &key) const {
    return recorrerDesde(0, raiz, key);
}

template<typename T>
pair<int, typename string_map<T>::Nodo *> string_map<T>::recorrerDesde(int acc, Nodo *n, const std::string &key) const {
    Nodo *m = n;
    if (m != nullptr)
        while (m->siguientes[int(key[acc])] != nullptr && acc < (int) key.size()) {
            m = m->siguientes[int(key[acc])];
            acc++;
        }
    return make_pair(acc, m);
}
