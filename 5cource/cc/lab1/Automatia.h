#ifndef AUTOMATIA_H
#define AUTOMATIA_H
#include "State.h"
#include <graphviz/gvc.h>

class Automatia {
public:
    Automatia(StatePtr _startState);
    void visualize(const std::string& dot, const std::string& filename);
    std::vector<StatePtr> states() const;

    StatePtr getStartState() const;
    bool checkRegex(const std::string& regex);

private:
    StatePtr startState;
};

#endif // AUTOMATIA_H
