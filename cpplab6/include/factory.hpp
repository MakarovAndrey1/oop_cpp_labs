#pragma once
#include "npc.hpp"
#include "elf.hpp"
#include "bandit.hpp"
#include "squirrel.hpp"
#include "observer.hpp"

class Factory {
public:
    static std::shared_ptr<NPC> CreateNPC(const NPCType& type, const std::string& name, int x, int y) {
        std::shared_ptr<NPC> result;
        switch (type) {
            case NPCType::ElfType:
                result = std::static_pointer_cast<NPC>(std::make_shared<Elf>(name, x, y));
                break;

            case NPCType::BanditType:
                result = std::static_pointer_cast<NPC>(std::make_shared<Bandit>(name, x, y));
                break;

            case NPCType::SquirrelType:
                result = std::static_pointer_cast<NPC>(std::make_shared<Squirrel>(name, x, y));
                break;
            default:
                break;
        }

        if (result) {
            result->subscribe(TextObserver::get());
            result->subscribe(FileObserver::get());
        }

        return result;
    }

    static std::shared_ptr<NPC> CreateNPC(std::istream& is) {
        std::shared_ptr<NPC> result;
        int type{0};
        if (is >> type) {
            switch (type) {
                case NPCType::ElfType:
                    result = std::static_pointer_cast<NPC>(std::make_shared<Elf>(is));
                    break;

                case NPCType::BanditType:
                    result = std::static_pointer_cast<NPC>(std::make_shared<Bandit>(is));
                    break;

                case NPCType::SquirrelType:
                    result = std::static_pointer_cast<NPC>(std::make_shared<Squirrel>(is));
                    break;
                default:
                    break;
            }
        } else {
            std::cerr << "unexpected NPC type:" << type << std::endl;
        }

        if (result) {
            result->subscribe(TextObserver::get());
            result->subscribe(FileObserver::get());
        }

        return result;
    }
};