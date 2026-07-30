
// model/ExperienceFilter.h
#ifndef EXPERIENCEFILTER_H
#define EXPERIENCEFILTER_H

#include "CVFilter.h"

class ExperienceFilter : public CVFilter {
private:
    int minYears;

public:
    explicit ExperienceFilter(int years);
    bool match(const CV& cv) const override;
};

#endif // EXPERIENCEFILTER_H
