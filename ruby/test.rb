#!/usr/bin/ruby

def print_dec(i)
    puts i
    i = i - 1
    return i
end

def string_demo
    str1 = "double quoted string like many other languages"
    str2 = 'single quoted, no escape, can hold \t, \n, etc.'
    str3 = %q#this is another single quoted string#
    str4 = %Q/This is another double quoted string/
    str5 = <<__EOL
Here is document string with <<...
The second line here...
__EOL
    str = <<-FIN
           on the one-ton temple bell
           a moon-moth, folded into sleep
           sits still.

           --Taniguchi Buson, 18th century; translated by X. J. Kennedy
           FIN
    string = [<<-ONE, <<-TWO, <<-THREE]
        the first thing
        ONE
        the second thing
        TWO
        and the third thing
        THREE

    puts str
    #string.each { |s| puts ">>>" + s }
    string.each do |s|
        puts "[>do] " + s
    end
    return
    puts str1
    puts str2
    puts str3
    puts str4
    puts str5
    str = "raw"
    str += " + added"
    str << " another padding" << "!"
    puts str
    puts "last 8 chars: " + str[-8, 8]
    puts "first 3 chars: " + str[0, 3]
    puts "dupped:" + str * 2
    str = "str"
    n = 2
    s = "#{str} #{n}"
    puts "embeded variables: #{s}"

    puts "abcd" =~ /cd/
    puts "abcd" !~ /Cd/
    puts "abcd" !~ /d/
end
string_demo
exit

def io_demo
    afile = File.new("testfile", "r")
    afile.each_line("\n") do |line|
        puts line
    end
    afile.close

    File.open("testfile", "r") do |afile|
        puts afile.readlines
    end

    IO.foreach("testfile") { |line| puts line }

    arr = IO.readlines("testfile")
    arr.each { |line| puts line }
end
io_demo
exit

def show_closure(f)
    s = "demo"
    puts f.call("some thing")
    return proc { |str| str += s }
end
f = proc { |mesg| mesg *= 2 }
g = show_closure(f)
puts g.call("g ")


def hello(name)
    puts "hello #{name}"
end

def that_block
    for num in (1..3)
        yield(num)
        puts "puts in def"
        yield(num)
    end
end

#that_block do |num|
#    puts "puts in block #{num}"
#end

# add a foreach method for Array
class Array
    def foreach
        for i in 0..(size-1)
            yield(self[i])
        end
    end
end
arr = [1.1, 2, 3]
arr.foreach { |elem| print elem, ", " }
puts

def main
    puts 3/5
    puts 3/5.0
    i = 0
    puts "while"
    while i < 10
        puts i
        i = i + 1
    end
    puts "(...) while"
    (i = print_dec(i)) while i > 0
    puts "for"
    for i in 1..3
        puts i
    end

    puts "times/upto/downto"
    3.times { puts "hi!" }
    1.upto(5) { |i| puts "upto #{i}" if i < 3 }
    9.downto(7) { |i| puts "downto #{i}" }

    puts "each/step"
    (1..9).each { |i| puts "each ", i }
    0.step(11, 3) { |i| puts "step ", i }
end
#main()

def sum(*num)
    nSum = 0
    num.each { |n| nSum += n }
    return nSum
end

class Person
    def initialize(name, age=18)
        @name = name
        @age = age
        # undef :talk
    end
    def talk
        puts "name:" + @name + ", age:" + @age.to_s
        if @motherland == "China"
            puts "I'm a Chinese"
        end
    end
    attr_writer :motherland
    attr_reader :home
    attr_accessor :tel
end

class Student < Person
    def talk
        super
        puts "I'm a student"
    end
end

def test_person
    p1 = Person.new("Micheal", 20)
    p1.talk
    p1.motherland = "China"
    p1.talk
    p2 = Student.new("Sam", 14)
    p2.talk
    def p2.talk
        puts "this is p2"
    end
    p2.talk
end

class Point < Struct.new(:x, :y)
    def distance(point)
        Math.sqrt((point.x - self.x) ** 2 + (point.y - self.y) ** 2)
    end
end #=> nil

pt1 = Point.new(1, 2) #=> #<struct Point x=1, y=2>
pt2 = Point.new(3, 4) #=> #<struct Point x=3, y=4>
puts pt1.distance(pt2) #=> 2.8284271247461903

=begin comment

delimeters:
    ;
    ()
    ` '
    ,
    ::  scoped by package

keywords:
    module
    class
    def undef
    defined?
    if then else elsif case when unless
    for in while until break do redo retry yield
    not and or
    true false nil
    resure ensure
    super self
    begin end
    BEGIN END
    __FILE__ __LINE__
    return
    alias
    require include

operators:
    [] []=
    **
    ! ~ + -
    * / %
    + -
    >> <<
    &
    ^|
    <= < > >=
    <=> == === != =~ !~
    .. ...
    ?:
    = ...=
    defined?
    not
    or and
    if unless while until
    begin end

variable
    $xxx: global
    @xxx: instance variables, @# is illegal
    @@xxx: class variables;

class library:

    puts
    printf

variable types:
    number string array hash range re

    range: 1..5 --> [1, 2, 3, 4, 5]
    range: 1...5 --> [1, 2, 3, 4]

compares:
    value compares:
        == !=

    eql?    compares value & type
    equal?  compares reference (address)
    a = 1.0; b = 1.0;  a.equal?(b) #false
    a = 1.0; b = a;  a.equal?(b) #true

flow: if/unless/case
    if ...
        ...
    elsif ...
        ...
    elsif ...
        ...
    else
        ...
    end

    statement if/unless condition

    case object
    when ..
        ...
    when
        ...
    else
        ...
    end

loops:
    while ...
        ,,,
        break next
        redo:  redo this step
        retry: redo the whole loop, bad!
    end

    bad!: (...) while ...
          until ... end

    times:  3.times { print "hi!" }
    upto
    downto
    each
    step

exception:
    begin = try
    rescue = catch
    ensure = finally
    end
    raise

    catch/throw
    catch (:label) do
        throw :label
    end

class:
    initialize
    attr_writer :motherland
    attr_reader :home
    attr_accessor :tel
    super
    @member_var
    @@class_var
    $global_var
    def ClassName.static_method

    def ob.single_instance_method
    public/protected/private

module
    include Module
    load 'libfoo.rb'
    require 'libfoo'

    module Me

    aStudent = Student.new()
    aStudent.extend(Math)         # include Me for aStudent
    aStudent.sqrt(2)

    require "libfile"  # file name without .rb extension
    load "config.rb"

    require only load once for same file, load can load multiply times

    # In other file, ...
    # module Bar
    # ...

    class Foo
        include Bar     # include module Bar to class Foo
    end

    require 'math' # load only once in this file, does not include any module to a class
    load 'math.rb' # always load when call load method

array:
    arr = [1, 2, 3, "aa"]
    arr.first = arr[0]
    arr.last = arr[-1]
    arr[1..3] = [2, 3, "aa"]
    arr.join(",")
    arr[2] = "a"
    arr.delete_at(3)
    arr.push("last")
    arr.delete("a", 2, "last")
    arr.insert(1, "i3")
    arr.pop
    arr.shift
    arr.clear
    arr3 = arr1 + arr2
    arr4 = arr * 2;
    arr5 = arr3 - arr2
    arr1 | arr2
    arr1 & arr2
    arr.sort
    arr.reverse

string
    str1 = "double quoted string like many other languages"
    str2 = 'single quoted can hold \t, \n, etc.'
    str3 = %q/this is another single quoted string/
    str4 = %Q/This is another double quoted string/
    str5 = <<__EOL
Here is document string with <<...
The second line here...
__EOL
    str = <<-FIN
           on the one-ton temple bell
           a moon-moth, folded into sleep
           sits still.

           --Taniguchi Buson, 18th century; translated by X. J. Kennedy
          FIN

    s3 = s1 + s2
    double = s1 * 2
    last_3 = s[-3, 3]

regular expression
    almost everything in perl, but, ...
    ?(1.8): no named group
    ?(1.8): no unicode property
    string.sub(re, rep_string)
    string.gsub(re, rep_string)

IO
    afile = File.new("testfile", "r")
    afile.each_byte block
    afile.each_line("\n") block
    afile.close

    File.open("testfile", "r") do |afile|
    end

    IO.foreach("testfile") { |line| puts line }

    arr = IO.readlines("testfile")
    arr.each block

unit test:
    require "test/unit"
    http://en.wikibooks.org/wiki/Ruby_Programming/Unit_testing

=end

