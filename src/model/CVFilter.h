// model/CVFilter.h
#ifndef CVFILTER_H
#define CVFILTER_H

#include <vector>
#include "CV.h"

class CVFilter {
public:
    virtual ~CVFilter() = default;
    
    // Đã đổi từ (CV cv) thành (const CV& cv) để tránh copy lãng phí bộ nhớ
    virtual bool match(const CV& cv) const = 0;
    
    // Giữ nguyên phong cách nhận vector và lọc ra vector mới của bạn
    virtual std::vector<CV*> filter(const std::vector<CV*>& cvs) const;
};

#endif // CVFILTER_H
