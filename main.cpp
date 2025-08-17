/*
 * GradeTracker++
 * Comprehensive grade management system.
*/

#include <iostream>
#include <string>
#include <vector>
#include <map>

class GradeComponent {
private:
    std::string name;
    double score;
    double total;

public:
    GradeComponent(const std::string& name, double score, double total);
};

class Course {
    std::string name;
    std::map<std::string, double> weights;
    std::map<std::string, std::vector<GradeComponent>> components;

    double calculateAverage() const;
};

class GradeBook {
private:
    std::vector<Course> courses;

public:
    void addCourse(const Course&);
    void removeCourse(const std::string&);
    void saveToFile(const std::string& filename);
    void loadFromFile(const std::string& filename);
};

int main() {
    std::cout << "Welcome to GradeTracker++!\n";

    return 0;
}