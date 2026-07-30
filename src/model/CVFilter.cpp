// model/CVFilter.cpp
#include "CVFilter.h"

std::vector<CV*> CVFilter::filter(const std::vector<CV*>& cvs) const {
    std::vector<CV*> result;
    for (CV* cv : cvs) {
        if (cv != nullptr && match(*cv)) {
            result.push_back(cv);
        }
    }
    return result;
}
