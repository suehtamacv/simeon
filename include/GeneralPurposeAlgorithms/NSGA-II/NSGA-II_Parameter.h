#ifndef NSGAII_PARAMETER_H
#define NSGAII_PARAMETER_H

#include <memory>
#include <vector>

class Parameter {
  public:
    enum class PossibleParameters : int;

    Parameter(PossibleParameters type);

    static std::shared_ptr<Parameter> create(std::vector<int> Gene, PossibleParameters);
    virtual double get_Value() = 0;
    bool operator < (const Parameter &other) const;

    PossibleParameters type;
    double value;
};

Parameter::Parameter(PossibleParameters type) : type(type) {}

bool Parameter::operator <(const Parameter &other) const {
    if (type == other.type) {
        return value < other.value;
    } else {
        return false;
    }
}

#endif // NSGAII_PARAMETER_H

