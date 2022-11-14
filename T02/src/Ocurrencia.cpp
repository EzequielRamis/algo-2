#include "Ocurrencia.h"

bool esHorizontal(Ocurrencia &o) {
    set<Nat> colns;
    for (auto e: o)
        colns.insert(get<1>(e));
    return colns.size() == 1;
}

bool esVertical(Ocurrencia &o) {
    set<Nat> colns;
    for (auto e: o)
        colns.insert(get<0>(e));
    return colns.size() == 1;
}

bool haySuperpuestas(Ocurrencia &o) {
    for (auto oIt = o.begin(); oIt != o.end(); oIt++) {
        auto ficha = *oIt;
        for (auto oItSig = oIt; oItSig != o.end(); oItSig++) {
            auto fichaSig = *oItSig;
            if (get<0>(ficha) == get<0>(fichaSig) && get<1>(ficha) == get<1>(fichaSig))
                return true;
        }
    }
    return false;
}
