#pragma once

#include "npc.hpp"
#include "visitor.hpp"


class Bandit : public NPC {
public:
    Bandit(const std::string&, int, int);
    Bandit(std::istream&);

    virtual bool accept(const std::shared_ptr<NPC>&) const override;

    void save(std::ostream&) override;

    friend std::ostream& operator<<(std::ostream&, Bandit&);
};