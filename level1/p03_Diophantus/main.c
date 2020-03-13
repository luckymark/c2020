#include <stdlib.h>
#include <stdio.h>

int main() {
	system("title Diophantus");
	const float percent = .5 - 1. / 6 - 1. / 12 - 1. / 7;
	printf("%d\n", (int)((5. + 4.) / percent - 4. + .5));
	system("pause");
	return 0;
}
