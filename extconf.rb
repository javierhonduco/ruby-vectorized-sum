#!/usr/bin/env ruby
require 'mkmf'

# preparation for compilation goes here
$CFLAGS << '-Werror -Wall'
create_makefile 'fast_sum'
