require 'minitest/autorun'
require './fast_sum'

class FastSumTest < Minitest::Test
  def setup
    `make`
    @fast = Fast.new
  end

  def test_one_integer
    assert_equal 2, @fast.sum([2])
  end

  def test_multiple_integers
    assert_equal 101, @fast.sum([25, 50, 25, 1])
  end

  def test_empty_array
    assert_equal 0, @fast.sum([])
  end

  def test_not_numeric_input
    assert_raises(ArgumentError){
      @fast.sum(:symbol)
    }
  end
end
