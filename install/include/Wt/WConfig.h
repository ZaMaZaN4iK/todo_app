#ifndef WCONFIG_H
#define WCONFIG_H

// Version defines
#define WT_SERIES 4
#define WT_MAJOR  0
#define WT_MINOR  3

/*! \brief A constant that encodes the library version of %Wt
 *
 * You may use this constant to check for the version of %Wt at build-time.
 */
#define WT_VERSION (((WT_SERIES & 0xff) << 24) | ((WT_MAJOR & 0xff) << 16) | ((WT_MINOR & 0xff) << 8))
#define WT_VERSION_STR "4.0.3"
#define WT_CLASS       "Wt4_0_3"
#define WT_INCLUDED_VERSION Wt_4_0_3

#define RUNDIR "/home/zamazan4ik/OpenSource/wt-4.0.3/build/var/run/wt"
#define WT_CONFIG_XML "/home/zamazan4ik/OpenSource/wt-4.0.3/build/etc/wt/wt_config.xml"
#define WTHTTP_CONFIGURATION "/home/zamazan4ik/OpenSource/wt-4.0.3/build/etc/wt/wthttpd"

/* #undef WT_STATIC */
/* #undef WTDBO_STATIC */
/* #undef WTDBOPOSTGRES_STATIC */
/* #undef WTDBOSQLITE3_STATIC */
/* #undef WTDBOFIREBIRD_STATIC */
/* #undef WTDBOMYSQL_STATIC */
/* #undef WTDBOMSSQLSERVER_STATIC */
/* #undef WTHTTP_STATIC */

/* #undef WT_HAS_WRASTERIMAGE */
/* #undef WT_HAS_WPDFIMAGE */
#define WT_WITH_SSL

/* #undef WT_USE_OPENGL */
/* #undef WT_DEBUG_ENABLED */
#define WT_THREADED

#define WT_ANY_IS_THELINK2012_ANY
/* #undef WT_ANY_IS_EXPERIMENTAL_ANY */
/* #undef WT_ANY_IS_STD_ANY */

#define WT_ASIO_IS_BOOST_ASIO
/* #undef WT_ASIO_IS_STANDALONE_ASIO */

#define WT_WARN_HEADER_MISSING_H

// our win32: WIN32 (gcc) or _WIN32 (MSC)
#if defined(WIN32) || defined(_WIN32)
#define WT_WIN32 1
#endif

#endif
