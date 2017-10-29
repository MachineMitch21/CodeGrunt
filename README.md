
CODEGRUNT

A utility program for gathering statistics about a code -base.

FEATURES:

	1. Counts lines of all files in a directory

	2. Gathers search stats about the code-base (or any other types of 'text based' files)

COMMANDS:

	1. --exclude
		a. Is used to exclude files from being processed
			a.1 Excludes all files from processing (counting, searching, etc)
		b. Example usage (codegrunt [directory-to-process]  --exclude Mesh.h Mesh.cpp Matrix.h
			b.1 This will exclude the files "Mesh.h" "Mesh.cpp" and "Matrix.h" from being processed

	2. --search
		a. Is used to search files for any given word, phrase or character
		b. Example usage (codegrunt [directory-to-process]  --search "a phrase to search for" char* blah
			b.1 All phrases with spaces in them have to be entered between string quotes " "

FINAL THOUGHTS:

	Commands can be entered in any order and multiple times if you want (Ex. codegrunt [directory]  --search hi  --search thing --exclude somefile.txt) is a valid entry.
