use Devel::Depend::Cpp;

my ($success, $includ_levels, $included_files) = Devel::Depend::Cpp::Depend(
   undef, # use default 'cpp' command
   '/usr/include/stdio.h',
   '',  # switches to cpp
   0,  # include system includes
   0,  # dump 'cpp' output in terminal
  );

