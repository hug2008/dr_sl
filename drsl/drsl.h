// Copyright (C) 2016 David Reid. See included LICENSE file.

#ifndef dr_sl_h
#define dr_sl_h

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <errno.h>
#include <wchar.h>
#include <locale.h>
#include <assert.h>
#include <ctype.h>
#include <ostream>
#include <vector>

#include "setup.hpp"
#include "_private.hpp"
#include "reference_string.hpp"
#include "nextchar.hpp"
#include "getchar.hpp"
#include "size.hpp"
#include "charwidth.hpp"
#include "compare.hpp"
#include "find.hpp"
#include "writechar.hpp"
#include "copy.hpp"
#include "format.hpp"
#include "parse.hpp"
#include "tostring.hpp"
#include "slow_string.hpp"
#include "string.hpp"
#include "bom.hpp"
#include "append.hpp"
#include "nextline.hpp"
#include "stream_output.hpp"
#include "erase.hpp"
#include "istype.hpp"
#include "replace.hpp"
#include "split.hpp"

#include "paths/_private.hpp"
#include "paths/getfileext.hpp"
#include "paths/isnetworkpath.hpp"
#include "paths/absolute.hpp"
#include "paths/relative.hpp"
#include "paths/isabsolute.hpp"
#include "paths/isrelative.hpp"
#include "paths/splitpath.hpp"

#include "tokens/_private.hpp"
#include "tokens/nexttoken.hpp"
#include "tokens/extracttokens.hpp"

#include "search/containsprintablechar.hpp"
#include "search/containsnonprintablechar.hpp"

#include "misc/removequotes.hpp"

#endif //dr_sl_h
