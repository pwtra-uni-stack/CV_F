
// model/SkillFilter.h
#ifndef SKILLFILTER_H
#define SKILLFILTER_H

#include "CVFilter.h"
#include <vector>
#include <string>

class SkillFilter : public CVFilter {
private:
    std::vector<std::string> required_skills;

public:
    explicit SkillFilter(std::vector<std::string> skills);
    bool match(const CV& cv) const override;
};

#endif // SKILLFILTER_H
