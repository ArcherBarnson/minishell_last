#include <signal.h>

int	main()
{
	raise(SIGPIPE);
}
