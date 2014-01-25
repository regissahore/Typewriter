Lab1 - Classes, Dynamic Memory and IOStreams
=====

See Lab1 materials folder for code, data file, and initialization files.  Modify Lab #1 code as follows:

* Convert all structures to C++ classes.  
* Keep the default access specifier ¡®private¡¯ for data and ¡®public¡¯ for member functions.
* Change the ¡®initializer¡¯ functions to C++ constructors. Note that when declaring dynamic arrays that the default constructor is used to initialize each array element.  The ¡®initializer¡¯ functions from the previous lab can be used after the array is constructed.
* Change the ¡®cleanup¡¯ functions to C++ destructors.  There should be no cleanup functions except for destructors after modifying lab #0.
* Replace C input/output/file operations with their C++ equivalent.  This means no ¡®printf¡¯, ¡®FILE*¡¯, etc.
* Replace C memory allocation (malloc) with C++ memory allocation (new).  Remember to make a distinction between scalar and vector versions of new.
* Replace C memory deallocation (free) with C++ memory deallocation (delete).  Remember to make a distinction between scalar and vector versions of delete.
* You may add additional functions as necessary to accomplish the conversion.
* Use MemTracker.h to track memory usage.
