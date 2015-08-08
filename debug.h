#ifndef _DEBUG_H
#define _DEBUG_H

#ifndef DEBUG
#define DEBUG 0
#endif

#if DEBUG
#define D(x) __FILE__":%d:%s: " x, __LINE__, __func__
#else
#define D(x) x
#endif

#define TR(fmt, type, X) do { \
	type ___ = (X); \
	if (config.cfg_flags & FLAG_DEBUG) \
		fprintf(stderr, \
			D("DEBUG:[%s](%s) => " fmt "\n"), \
			#X, \
			#type, \
			___); \
} while (0)

#define WARN(args...) do { \
	fprintf(stderr, args); \
} while (0)

#define ERR(args...) do { \
	fprintf(stderr, args);  \
	exit(EXIT_FAILURE); \
} while (0)

#endif /* _DEBUG_H */
