Collision did not conform to output specification
-------------------------------------------------

Edited the following submissions' `extra.c` files so that their
`collide_dumb()` and `collide_clever()` conform to the output specification.
Their original submissions may be found in `extra.orig.c`

+    /subs/leh2-695540
+    /subs/boyuanc1-708346
+    /subs/cdempsey1-759026
+    /subs/weizhix-752454
+    /subs/shiqingz1-752479
+    /subs/peiyuns-667816
+    /subs/yapq-732114
+    /subs/lajero-762095
+    /subs/nelsonc1-743322
+    /subs/glaw-759218
+    /subs/mlatifoglu-761770
+    /subs/mbabis-770881
+    /subs/yueminh-752563
+    /subs/r-700360
+    /subs/lan2-717178
+    /subs/dongweiw-728580
+    /subs/yuechenh-794731
+    /subs/jdewis-760858
+    /subs/mattiasw-683378
+    /subs/oavellan-743342
+    /subs/lputra-755379


Non-compiling submissions
-------------------------

13 submissions did not compile without math library.
Added `-lm` to the compiler flags

subs/ni-614472

Added `#include <stdint.h>` to `hash.c` and `extra.c`

subs/duteda-761312

- Changed the function prototypes of `str_eq` and `str_print` in `types.c`
- No function prototypes in `extra.c`

subs/liuk3-766486

- No function prototypes in `extra.c`
- Syntax errors, unclosed parentheses
- Did not include `<stdio.h>` and `<stdlib.h>`
- Redeclared `size` in `collide_dumb()`

subs/oavellan-743342

- No function prototypes in `extra.c`

subs/putraa-743206

- Didn't include `<assert.h>`

subs/stanner1-766434

- Removed `#include <stdbool.h>`
- No function prototypes in `extra.c`

subs/yapq-732114

- Included `<strings.h>` instead of `<string.h>`
- Did not include `<stdlib.h>`
- Did not include `<stdio.h>`

subs/yuchengz-743251

- Changed function prototype for `linear_probe()`
