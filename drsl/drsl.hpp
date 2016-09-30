/**
*   \file   drsl.h
*   \author Dave Reid
*   \brief  Primary header file for DRSL.
*/
#ifndef DRSL
#define DRSL

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <errno.h>
#include <wchar.h>
#include <locale.h>
#include <assert.h>
#include <cctype>
#include <ostream>
#include <vector>

#include "setup.hpp"
#include "types.hpp"
#include "_private.hpp"
#include "reference_string.hpp"
#include "nextchar.hpp"
#include "getchar.hpp"
#include "length.hpp"
#include "charwidth.hpp"
#include "compare.hpp"
#include "findfirst.hpp"
#include "findfirstof.hpp"
#include "charcount.hpp"
#include "equal.hpp"
#include "writechar.hpp"
#include "copy.hpp"
#include "copysize.hpp"
#include "vformat.hpp"
#include "vformatsize.hpp"
#include "format.hpp"
#include "formatsize.hpp"
#include "parse.hpp"
#include "tostring.hpp"
#include "slow_string.hpp"
#include "string.hpp"
#include "getbom.hpp"
#include "skipbom.hpp"
#include "attachbom.hpp"
#include "removebom.hpp"
#include "append.hpp"
#include "appendsize.hpp"
#include "nextline.hpp"
#include "stream_output.hpp"
#include "erase.hpp"
#include "istype.hpp"
#include "replace.hpp"
#include "split.hpp"

#include "paths/_private.hpp"
#include "paths/getfileext.hpp"
#include "paths/getfileextsize.hpp"
#include "paths/isnetworkpath.hpp"
#include "paths/absolute.hpp"
#include "paths/absolutesize.hpp"
#include "paths/relative.hpp"
#include "paths/relativesize.hpp"
#include "paths/isabsolute.hpp"
#include "paths/isrelative.hpp"
#include "paths/splitpath.hpp"

#include "tokens/_private.hpp"
#include "tokens/nexttoken.hpp"
#include "tokens/extracttokens.hpp"

#include "search/containsprintablechar.hpp"
#include "search/containsnonprintablechar.hpp"

#include "misc/removequotes.hpp"

#endif // DRSL
