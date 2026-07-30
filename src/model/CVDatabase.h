
// model/CVDatabase.h
#ifndef CVDATABASE_H
#define CVDATABASE_H

#include <vector>
#include "CV.h"

class CVDatabase {
private:
    std::vector<CV*> list_cv;

public:
    CVDatabase() = default;
    ~CVDatabase();

    void addCV(CV* cv);
    void removeCV(int id);
    
    // Thêm const correctness giữ nguyên phong cách
    CV* getById(int id) const;
    std::vector<CV*> getAll() const;
    void clear();
};

#endif // CVDATABASE_H
