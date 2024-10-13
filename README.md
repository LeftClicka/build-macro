# build-macro
C++ Header that provides very basic functionality for building projects

# usage
Include this header in your c/c++ file and create a Project object in your main function. 
Set compiler and linker flags with the set_compiler_flags(...) and set_linker_flags(...) methods respectively. Then, add files via add_file(...).
You can optionally set the output directory with set_output_dir(...), otherwise the executable's directory will be used.
You can change the path of the compiler to use with set_compiler(...). This is expected to be some c/c++ compiler that is either in your path or specified by an absolute path. By default, compiler is "gcc".

This is only really suitable for small projects with a few files and maybe a linked in library that you want to write a quick and easy build recipe for instead of typing very long commands every time you rebuild.
