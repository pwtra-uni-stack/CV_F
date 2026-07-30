// model/CVDatabase.cpp
#include "CVDatabase.h"
#include <algorithm>

CVDatabase::~CVDatabase() {
    clear();
}

void CVDatabase::addCV(CV* cv) {
    if (cv != nullptr) {
        list_cv.push_back(cv);
    }
}

void CVDatabase::removeCV(int id) {
    std::string targetId = "CV_" + std::to_string(id);
    
    // Sửa lỗi: Tìm kiếm vị trí trước rồi giải phóng vùng nhớ an toàn
    for (auto it = list_cv.begin(); it != list_cv.end(); ++it) {
        if (*it != nullptr && (*it)->id == targetId) {
            delete *it;          // Giải phóng bộ nhớ CV
            list_cv.erase(it);   // Xóa con trỏ khỏi vector
            break;
        }
    }
}

CV* CVDatabase::getById(int id) const {
    std::string targetId = "CV_" + std::to_string(id);
    for (CV* cv : list_cv) {
        if (cv != nullptr && cv->id == targetId) {
            return cv;
        }
    }
    return nullptr;
}

std::vector<CV*> CVDatabase::getAll() const {
    return list_cv;
}

void CVDatabase::clear() {
    for (CV* cv : list_cv) {
        if (cv != nullptr) {
            delete cv;
        }
    }
    list_cv.clear();
}

