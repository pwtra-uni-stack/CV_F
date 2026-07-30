
// model/SkillFilter.cpp
#include "SkillFilter.h"

SkillFilter::SkillFilter(std::vector<std::string> skills) 
    : required_skills(skills) {}

bool SkillFilter::match(const CV& cv) const {
    for (const std::string& keyword : required_skills) {
        bool found = false;
        for (const std::string& skill : cv.skills) {
            if (skill.find(keyword) != std::string::npos) {
                found = true;
                break;
            }
        }
        if (!found) return false;
    }
    return true;
}
