#include <stdio.h>
#include "config.h"

int main(){

#ifdef FLAG1_IS_DEFINED
	printf("flag 1 is set\n");
#endif
#ifdef FLAG2_IS_DEFINED
	printf("flag 2 is set\n");
#endif
#ifdef FLAG3_IS_DEFINED
	printf("flag 3 is set\n");
#endif
#ifdef FLAG_STR_IS_DEFINED
	printf("RAVEN is GOD\n");
#endif
#ifdef FLAG_SPACE_IS_DEFINED
	printf("space definition is pass\n");
#endif

	return 0;
}
