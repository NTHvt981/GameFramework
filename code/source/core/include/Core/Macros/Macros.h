#pragma once

#if defined DEBUG
#define DEBUG(x) x
#define RELEASE(x)
#else
#define DEBUG(x)
#define RELEASE(x) x
#endif
