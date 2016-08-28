require 'minitest/autorun'
require './fast_sum'

`make`

class FastSumTest < Minitest::Test
  def test_one_integer
    assert_equal 2, Fast.sum([2])
  end

  def test_multiple_integers
    assert_equal 101, Fast.sum([25, 50, 25, 1])
  end

  def test_empty_array
    assert_equal 0, Fast.sum([])
  end

  def test_not_numeric_input
    assert_raises(ArgumentError){
      Fast.sum(:symbol)
    }
  end
end
