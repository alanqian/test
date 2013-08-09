# File:  simple_number_test.rb

require "test/unit"
require "./simple_number"

class SimpleNumberTest < Test::Unit::TestCase

  def test_simple
    assert_equal(4, SimpleNumber.new(2).add(2) )
    assert_equal(6, SimpleNumber.new(2).multiply(3) )
  end

end

__END__

# File: ts_allTheTests.rb
require 'test/unit'
require 'testOne'
require 'testTwo'
require 'testThree'

# Test::Unit Available Assertions

assert( boolean, [message] )

assert_equal( expected, actual, [message] )     True if expected == actual
assert_not_equal( expected, actual, [message] )
assert_in_delta( expected_float, actual_float, delta, [message] )       True if (actual_float - expected_float).abs <= delta
assert_same( expected, actual, [message])
assert_not_same( expected, actual, [message] )  True if actual.equal?( expected ).

assert_match( pattern, string, [message] )
assert_no_match( pattern, string, [message] )

assert_nil( object, [message] )
assert_not_nil( object, [message] )

assert_instance_of( class, object, [message] )  True if object.class == class
assert_kind_of( class, object, [message] )      True if object.kind_of?(class)

assert_raise( Exception,... ) {block}
assert_nothing_raised( Exception,...) {block}   True if the block raises (or doesn't) one of the listed exceptions.
assert_throws( expected_symbol, [message] ) {block}
assert_nothing_thrown( [message] ) {block}      True if the block throws (or doesn't) the expected_symbol.

assert_respond_to( object, method, [message] )  True if the object can respond to the given method.
assert_send( send_array, [message] )    True if the method sent to the object with the given arguments return true.
assert_operator( object1, operator, object2, [message] )        Compares the two objects with the given operator, passes if true

