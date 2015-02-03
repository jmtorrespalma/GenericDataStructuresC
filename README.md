Juan Manuel Torres Palma.

Lightweight and generic data structures library for small applications.

Written in C.

One of the benefits is the possibilty to use generic data structures,
and functions what implies using less space to store all the text code
that C++ uses because of templates. However, that makes it a bit less 
optimal and internally complex. 

Tasks to make it suitable for embedded.
	- Use static memory without resize.
	- Use power of 2 buffer sizes to avoid mod operations.
	- Add architecture dependent optimizations.

