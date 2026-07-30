// model/ExperienceFilter.cpp
#include "ExperienceFilter.h"

ExperienceFilter::ExperienceFilter(int years) : minYears(years) {}

bool ExperienceFilter::match(const CV& cv) const {
    return cv.experienceYears >= minYears;
}

