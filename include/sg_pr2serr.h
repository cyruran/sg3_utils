#ifndef SG_PR2SERR_H
#define SG_PR2SERR_H

/*
 * Copyright (c) 2004-2018 Douglas Gilbert.
 * All rights reserved.
 * Use of this source code is governed by a BSD-style
 * license that can be found in the BSD_LICENSE file.
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

/* These are convenience functions that replace the somewhat long-winded
 * fprintf(stderr, ....). The second form (i.e. pr2ws() ) is for internal
 * library use and may place its output somewhere other than stderr; it
 * depends on the external variable sg_warnings_strm which can be set
 * with sg_set_warnings_strm(). By default it uses stderr. */

/* With regard to sg_scnpr():
 * Want safe, 'n += snprintf(b + n, blen - n, ...)' style sequence of
 * functions. Returns number of chars placed in cp excluding the
 * trailing null char. So for cp_max_len > 0 the return value is always
 * < cp_max_len; for cp_max_len <= 1 the return value is 0 and no chars are
 * written to cp. Note this means that when cp_max_len = 1, this function
 * assumes that cp[0] is the null character and does nothing (and returns
 * 0). Linux kernel has a similar function called  scnprintf().  */


#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

#if 0
enum sg_json_separator_t {
    SG_JSON_SEP_NONE = 0,
    SG_JSON_SEP_SPACE_1,
    SG_JSON_SEP_SPACE_2,
    SG_JSON_SEP_SPACE_3,
    SG_JSON_SEP_SPACE_4,
    SG_JSON_SEP_EQUAL_NO_SPACE,
    SG_JSON_SEP_EQUAL_1_SPACE,
    SG_JSON_SEP_COLON_NO_SPACE,
    SG_JSON_SEP_COLON_1_SPACE,
};
#endif


#if defined(__GNUC__) || defined(__clang__)
#ifdef SG_LIB_MINGW
/* MinGW uses Microsoft's printf */
int pr2serr(const char * fmt, ...);

int pr2ws(const char * fmt, ...);

int sg_scnpr(char * cp, int cp_max_len, const char * fmt, ...);

#else   /* GNU/clang other than MinGW */

int pr2serr(const char * fmt, ...)
        __attribute__ ((format (printf, 1, 2)));

int pr2ws(const char * fmt, ...)
        __attribute__ ((format (printf, 1, 2)));

int sg_scnpr(char * cp, int cp_max_len, const char * fmt, ...)
                 __attribute__ ((format (printf, 3, 4)));
#endif

#else   /* not GNU (and not clang) */

int pr2serr(const char * fmt, ...);

int pr2ws(const char * fmt, ...);

int sg_scnpr(char * cp, int cp_max_len, const char * fmt, ...);

#endif

#if 0
/* Print function for normal and/or json output. "hr" stands for human
 * readable (only); "j" for JSON (only). */
void pr_j_simple(int leadin_sp, const char * name,
                 enum sg_json_separator_t sep, const char * value);
void pr_j_hr_line(const char * hr_line, const char * jname,
                  const char * jvalue);
#endif


#ifdef __cplusplus
}
#endif

#endif
