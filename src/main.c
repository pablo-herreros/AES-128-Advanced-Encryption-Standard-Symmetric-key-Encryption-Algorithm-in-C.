#include "Global.h"
#include "AES.h"

/*Test DATA
 *
SET 1:

PlainText
32 43 F6 A8 88 5A 30 8D 31 31 98 A2 E0 37 07 34
\x32\x43\xF6\xA8\x88\x5A\x30\x8D\x31\x31\x98\xA2\xE0\x37\x07\x34

Key
2B 7E 15 16 28 AE D2 A6 AB F7 15 88 09 CF 4F 3C

Cryptogram
3925841d02dc09fbdc118597196a0b32
\x39\x25\x84\x1d\x02\xdc\x09\xfb\xdc\x11\x85\x97\x19\x6a\x0b\x32
*
*/

int64_t diffTime(struct timespec *start, struct timespec *end)
{
      return (((end->tv_sec * 1000000000) + end->tv_nsec) - ((start->tv_sec * 1000000000) + start->tv_nsec));
}
int main(void) {

unsigned char CipherText[AES_KEY_BYTES] = {0};


struct timespec start, end;

clock_gettime(CLOCK_MONOTONIC, &start);

	AES128((unsigned char *)"\x39\x25\x84\x1d\x02\xdc\x09\xfb\xdc\x11\x85\x97\x19\x6a\x0b\x32",
			(unsigned char *)"\x2B\x7E\x15\x16\x28\xAE\xD2\xA6\xAB\xF7\x15\x88\x09\xCF\x4F\x3C",
			ENCRYPT_MODE, CipherText);

clock_gettime(CLOCK_MONOTONIC, &end);

	printf("Secuencia: %" PRId64 "\n" , diffTime(&start,&end));
	printf("%s\n", CipherText);

	return EXIT_SUCCESS;
}
