//export manages variables to call them or write them to export them
// export with no args to export to for example another shell
// normally stdin stdout but can pipe to file
// uses builtin declare that we dont create but in bash there is
//declare -x A[="B"] -> can declare NULL / "\0" / abc
////
//
// export is sorted alphabetacly and has declare -x


#include <executer.h>

void	only_export(char **args)
{
	
}

void	export_bi(char **args)
{
	if (!args[1])
		only_export(args);
}
