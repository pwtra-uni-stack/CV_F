
// model/EducationFilter.cpp
#include "EducationFilter.h"

EducationFilter::EducationFilter(std::string edu) : targetEducation(edu) {}

bool EducationFilter::match(const CV& cv) const {
    return cv.education.find(targetEducation) != std::string::npos;
}
