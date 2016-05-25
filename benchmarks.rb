require 'benchmark/ips'
require './fast_sum'

`make`
n = 10_000_000
array = Array.new(n){ rand(0..10_000_000) }
fast = Fast.new

Benchmark.ips do |x|
  x.report('r reduce'){
    array.reduce{|a, b| a+b}
  }
  x.report('r classic'){
    result = 0
    array.each do |el|
      result += el
    end
  }
  x.report('r inject'){
    array.inject(:+)
  }
  x.report('c'){
    fast.sum(array)
  }

  x.compare!
end
