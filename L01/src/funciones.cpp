#include <vector>
#include "algobot.h"

using namespace std;

// Ejercicio 1
vector<int> quitar_repetidos(vector<int> s) {
    set<int> c;
    vector<int> res;
    for (int e: s) {
        c.insert(e);
    }
    for (int e: c) {
        res.push_back(e);
    }
    return res;
}

// Ejercicio 2
vector<int> quitar_repetidos_v2(vector<int> s) {
    set<int> c;
    vector<int> res;
    for (int e: s) {
        c.insert(e);
    }
    for (int e: c) {
        res.push_back(e);
    }
    return res;
}

// Ejercicio 3
bool mismos_elementos(vector<int> a, vector<int> b) {
    return quitar_repetidos_v2(a) == quitar_repetidos_v2(b);
}

// Ejercicio 4
bool mismos_elementos_v2(vector<int> a, vector<int> b) {
    return quitar_repetidos_v2(a) == quitar_repetidos_v2(b);
}

// Ejercicio 5
map<int, int> contar_apariciones(vector<int> s) {
    map<int, int> ap;
    for (int e: s) {
        ap[e]++;
    }
    return ap;
}

// Ejercicio 6
vector<int> filtrar_repetidos(vector<int> s) {
    map<int, int> ap = contar_apariciones(s);
    vector<int> res;
    for (pair<int, int> p: ap) {
        if (p.second == 1) {
            res.push_back(p.first);
        }
    }
    return res;
}

// Ejercicio 7
set<int> interseccion(set<int> a, set<int> b) {
    set<int> res;
    for (int e: a) {
        if (b.count(e) > 0) {
            res.insert(e);
        }
    }
    return res;
}

// Ejercicio 8
map<int, set<int>> agrupar_por_unidades(vector<int> s) {
    map<int, set<int>> res;
    for (int e: s) {
        int least = e % 10;
        res[least].insert(e);
    }
    return res;
}

// Ejercicio 9
vector<char> traducir(vector<pair<char, char>> tr, vector<char> str) {
    map<char, char> mtr;
    for (pair<char, char> t: tr) {
        mtr[t.first] = t.second;
    }
    vector<char> res = str;
    for (int i = 0; i < (int) str.size(); i++) {
        if (mtr.count(str[i]) > 0) {
            res[i] = mtr[str[i]];
        }
    }
    return res;
}

// Ejercicio 10
bool integrantes_repetidos(vector<Mail> s) {
    bool res = false;
    map<LU, int> alumnosXapariciones;
    set<set<LU>> ccl;
    for (Mail m: s) {
        ccl.insert(m.libretas());
    }
    for (set<LU> cl: ccl) {
        for (LU l: cl) {
            alumnosXapariciones[l]++;
        }
    }
    for (pair<LU, int> a: alumnosXapariciones) {
        if (a.second > 1) {
            res = true;
        }
    }
    return res;
}

// Ejercicio 11
map<set<LU>, Mail> entregas_finales(vector<Mail> s) {
    map<set<LU>, Mail> res;
    for (Mail m: s) {
        if (m.adjunto()) {
            res[m.libretas()] = m;
        }
    }
    return res;
}
