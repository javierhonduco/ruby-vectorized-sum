## ruby vectorized array sum

#### What it does?
It just adds up the numbers of an array using your CPU's vectorised instructions.

#### Why?
Just wanted to create a C extension for Ruby.
It's 100% to learn, not really to solve a problem and probably buggy even if the code is quite small.

#### Benchmarks
In order to run them you'll need to install the `benchmark-ips` gem.
```bash
▶ ruby benchmarks.rb
Warming up --------------------------------------
            r reduce     1.000  i/100ms
           r classic     1.000  i/100ms
            r inject     1.000  i/100ms
                   c     1.000  i/100ms
Calculating -------------------------------------
            r reduce      0.919  (± 0.0%) i/s -      5.000  in   5.440189s
           r classic      1.325  (± 0.0%) i/s -      7.000  in   5.283851s
            r inject      1.269  (± 0.0%) i/s -      7.000  in   5.519670s
                   c      5.580  (± 0.0%) i/s -     28.000  in   5.022475s

Comparison:
                   c:        5.6 i/s
           r classic:        1.3 i/s - 4.21x slower
            r inject:        1.3 i/s - 4.40x slower
            r reduce:        0.9 i/s - 6.07x slower
```
#### Misc
- In order to compile it: generate the Makefile with `ruby extconf.rb`, `make` to build and you can easily import it with `require './fast_sum'`
- Tests can be run with 
`ruby tests.rb`
