
// model/EducationFilter.h
#ifndef EDUCATIONFILTER_H
#define EDUCATIONFILTER_H

#include "CVFilter.h"
#include <string>

class EducationFilter : public CVFilter {
private:
    std::string targetEducation;

public:
    explicit EducationFilter(std::string edu);
    bool match(const CV& cv) const override;
};

#endif // EDUCATIONFILTER_H
