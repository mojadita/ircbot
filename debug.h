#ifndef _DEBUG_H
#define _DEBUG_H

#ifndef DEBUG
#define DEBUG 0
#endif

#define D(x) __FILE__":%d:%s: " x, __LINE__, __func__

#endif /* _DEBUG_H */
