
// model/Candidate.h
#ifndef CANDIDATE_H
#define CANDIDATE_H

#include <string>

class Candidate {
public:
    std::string candidate_id;
    std::string name;
    std::string email;
    std::string phone;

    Candidate();
    Candidate(std::string id, std::string name, std::string email, std::string phone);
};

#endif // CANDIDATE_H
