/*
 * GradeTracker++
 * Comprehensive grade management system.
*/

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <iomanip>

class GradeComponent {
private:
    std::string name;
    double score;
    double total;

public:
    // Constructor 
    GradeComponent(std::string n, double s, double t) {
        name = n;
        score = s;
        total = t;
    }

    // Getters
    std::string getName() { return name; }
    double getScore() { return score; }
    double getTotal() { return total; }

    // Setters
    void setName(std::string newName) { name = newName; }
    void setScore(double newScore) { score = newScore; }
    void setTotal(double newTotal) { total = newTotal; }
};

class Course {
private:
    std::string name;
    std::map<std::string, double> weights;
    std::map<std::string, std::vector<GradeComponent>> components;

public:
    // Constructor
    Course(std::string courseName, std::map<std::string, double> componentWeights) 
    : name(courseName), weights(componentWeights) {
        for(auto& pair : weights) {
            components[pair.first] = std::vector<GradeComponent>();
        }
    }
};

class GradeBook {
    std::vector<Course> courses;
};

int main() {
    std::cout << "Welcome to GradeTracker++!\n";

    return 0;
}
