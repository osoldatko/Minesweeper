#pragma once
#include "stdafx.h"

time_t now = time(0);
tm* ltm = localtime(&now);
int timegame1 = ltm->tm_sec + (ltm->tm_min) * 60 + (ltm->tm_hour) * 3600;