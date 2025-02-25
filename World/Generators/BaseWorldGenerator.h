//
// Created by IDKTHIS on 17.02.2025.
//

#pragma once
#include "Engine/World/World.h"


class BaseWorldGenerator : public World {
public:
    virtual void GenerateWorld() = 0;
};
