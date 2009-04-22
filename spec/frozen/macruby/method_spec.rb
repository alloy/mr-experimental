require File.dirname(__FILE__) + '/../spec_helper'

describe "A MacRuby method" do
  it "uses argument-names + colon + variable syntax to form the method name" do
    o = Object.new
    def o.doSomething(x, withObject:y); x + y; end
    o.respond_to?(:'doSomething:withObject:').should == true
    o.respond_to?(:'doSomething').should == false
  end

  it "can have multiple arguments with the same name" do
    o = Object.new
    def o.doSomething(x, withObject:y, withObject:z); x + y + z; end
    o.respond_to?(:'doSomething:withObject:withObject:').should == true
    o.respond_to?(:'doSomething').should == false
  end

  it "can coexist with other selectors whose first part is similar" do
    o = Object.new
    def o.foo(x); x; end
    def o.foo(x, withObject:y); x + y; end
    def o.foo(x, withObject:y, andObject:z); x + y + z; end
    o.respond_to?(:'foo').should == true
    o.respond_to?(:'foo:withObject:').should == true
    o.respond_to?(:'foo:withObject:andObject:').should == true
  end

  it "must start by a regular argument variable then followed by argument-names" do
    lambda { eval("def foo(x:y); end") }.should raise_error(SyntaxError)
    lambda { eval("def foo(x, y, with:z); end") }.should raise_error(SyntaxError)
    lambda { eval("def foo(x, with:y, z); end") }.should raise_error(SyntaxError)
  end

  it "can be called using argument-names + colon + variable syntax" do
    o = Object.new
    def o.doSomething(x, withObject:y, withObject:z); x + y + z; end
    o.doSomething(30, withObject:10, withObject:2).should == 42
  end

  it "can be called using argument-name-as-symbols + => + variable syntax" do
    o = Object.new
    def o.doSomething(x, withObject:y, withObject:z); x + y + z; end
    o.doSomething(30, :withObject => 10, :withObject => 2).should == 42
  end

  it "can be called mixing both syntaxes" do
    o = Object.new
    def o.doSomething(x, withObject:y, withObject:z); x + y + z; end
    o.doSomething(30, withObject:10, :withObject => 2).should == 42
  end

  it "can be called using #send" do
    o = Object.new
    def o.doSomething(x, withObject:y, withObject:z); x + y + z; end
    o.send(:'doSomething:withObject:withObject:', 30, 10, 2).should == 42
  end

  it "can be called using -[NSObject performSelector:]" do
    o = Object.new
    def o.doSomething; 42; end
    o.performSelector(:'doSomething').should == 42
  end

  it "can be called using -[NSObject performSelector:withObject:]" do
    o = Object.new
    def o.doSomething(x); x; end
    o.performSelector(:'doSomething:', withObject:42).should == 42
  end

  it "can be called using -[NSObject performSelector:withObject:withObject:]" do
    o = Object.new
    def o.doSomething(x, withObject:y); x + y; end
    o.performSelector(:'doSomething:withObject:',
                      withObject:40, withObject:2).should == 42
  end

  it "named using the setFoo pattern cannot be called using #foo=" do
    o = Object.new
    def o.setFoo(x); end
    o.respond_to?(:'foo=').should == false
    lambda { o.foo = 42 }.should raise_error(NoMethodError)
  end

  it "named using the isFoo pattern cannot be called using #foo?" do
    o = Object.new
    def o.isFoo; end
    o.respond_to?(:'foo?').should == false
    lambda { o.foo? }.should raise_error(NoMethodError)
  end
end

framework 'Foundation'

fixture_source = File.dirname(__FILE__) + '/fixtures/method.m'
fixture_ext = '/tmp/method.bundle'
if !File.exist?(fixture_ext) or File.mtime(fixture_source) > File.mtime(fixture_ext)
=begin
  # #system is currently broken
  unless system("/usr/bin/gcc #{fixture_source} -o #{fixture_ext} -g -framework Foundation -dynamiclib -fobjc-gc -arch i386 -arch x86_64 -arch ppc")
    $stderr.puts "cannot compile fixture source file `#{fixture_source}' - aborting"
    exit 1
  end
=end
  `/usr/bin/gcc #{fixture_source} -o #{fixture_ext} -g -framework Foundation -dynamiclib -fobjc-gc -arch i386 -arch x86_64 -arch ppc`
end
require '/tmp/method'
load_bridge_support_file File.dirname(__FILE__) + '/fixtures/method.bridgesupport'

describe "An Objective-C method" do
  it "named using the setFoo pattern can be called using #foo=" do
    o = []
    o.respond_to?(:'setArray').should == true
    o.respond_to?(:'array=').should == true
    o.array = [1, 2, 3]
    o.should == [1, 2, 3]
  end

  it "named using the isFoo pattern can be called using #foo?" do
    o = NSBundle.mainBundle
    o.respond_to?(:'isLoaded').should == true
    o.respond_to?(:'loaded?').should == true
    o.loaded?.should == true
  end

  it "is only exposed in #methods if the second argument is true" do
    o = Object.new
    o.methods.include?(:'performSelector').should == false
    o.methods(true).include?(:'performSelector').should == false
    o.methods(false).include?(:'performSelector').should == false
    o.methods(true, true).include?(:'performSelector').should == true
    o.methods(false, true).include?(:'performSelector').should == true
  end

  it "can be called on an immediate object" do
    123.self.should == 123
    true.self.should == true
    false.self.should == false
    nil.self.should == nil
  end

  it "returning void returns nil in Ruby" do
    o = TestMethod.new
    o.methodReturningVoid.should == nil
  end

  it "returning nil returns nil in Ruby" do
    o = TestMethod.new
    o.methodReturningNil.should == nil
  end

  it "returning self returns the same receiver object" do
    o = TestMethod.new
    o.methodReturningSelf.should == o
    o.methodReturningSelf.object_id == o.object_id
  end

  it "returning kCFBooleanTrue returns true in Ruby" do
    o = TestMethod.new
    o.methodReturningCFTrue.should == true
    o.methodReturningCFTrue.class.should == TrueClass
  end

  it "returning kCFBooleanFalse returns false in Ruby" do
    o = TestMethod.new
    o.methodReturningCFFalse.should == false
    o.methodReturningCFFalse.class.should == FalseClass
  end

  it "returning kCFNull returns nil in Ruby" do
    o = TestMethod.new
    o.methodReturningCFNull.should == nil
    o.methodReturningCFNull.class.should == NilClass
  end

  it "returning YES returns true in Ruby" do
    o = TestMethod.new
    o.methodReturningYES.should == true
  end

  it "returning NO returns true in Ruby" do
    o = TestMethod.new
    o.methodReturningNO.should == false
  end

  it "returning 'char' or 'unsigned char' returns a Fixnum in Ruby" do
    o = TestMethod.new
    o.methodReturningChar.should == 42
    o.methodReturningChar2.should == -42
    o.methodReturningUnsignedChar.should == 42
  end
 
  it "returning 'short' or 'unsigned short' returns a Fixnum in Ruby" do
    o = TestMethod.new
    o.methodReturningShort.should == 42
    o.methodReturningShort2.should == -42
    o.methodReturningUnsignedShort.should == 42
  end

  it "returning 'int' or 'unsigned int' returns a Fixnum in Ruby" do
    o = TestMethod.new
    o.methodReturningInt.should == 42
    o.methodReturningInt2.should == -42
    o.methodReturningUnsignedInt.should == 42
  end

  it "returning 'long' or 'unsigned long' returns a Fixnum if possible in Ruby" do
    o = TestMethod.new
    o.methodReturningLong.should == 42
    o.methodReturningLong2.should == -42
    o.methodReturningUnsignedLong.should == 42
  end

  it "returning 'long' or 'unsigned long' returns a Bignum if it cannot fix in a Fixnum in Ruby" do
    o = TestMethod.new
    o.methodReturningLong3.should ==
      (RUBY_ARCH == 'x86_64' ? 4611686018427387904 : 1073741824)
    o.methodReturningLong3.class.should == Bignum
    o.methodReturningLong4.should ==
      (RUBY_ARCH == 'x86_64' ? -4611686018427387905 : -1073741825)
    o.methodReturningLong4.class.should == Bignum
    o.methodReturningUnsignedLong2.should ==
      (RUBY_ARCH == 'x86_64' ? 4611686018427387904 : 1073741824)
    o.methodReturningUnsignedLong2.class.should == Bignum
  end

  it "returning 'float' returns a Float in Ruby" do
    o = TestMethod.new
    o.methodReturningFloat.should be_close(3.1415, 0.0001)
    o.methodReturningFloat.class.should == Float
  end

  it "returning 'double' returns a Float in Ruby" do
    o = TestMethod.new
    o.methodReturningDouble.should be_close(3.1415, 0.0001)
    o.methodReturningDouble.class.should == Float
  end

  it "returning 'SEL' returns a Symbol or nil in Ruby" do
    o = TestMethod.new
    o.methodReturningSEL.class.should == Symbol
    o.methodReturningSEL.should == :'foo:with:with:'
    o.methodReturningSEL2.class.should == NilClass
    o.methodReturningSEL2.should == nil
  end

  it "returning 'NSPoint' returns an NSPoint boxed object in Ruby" do
    o = TestMethod.new
    b = o.methodReturningNSPoint
    b.class.should == NSPoint
    b.x.class.should == Float
    b.x.should == 1.0
    b.y.class.should == Float
    b.y.should == 2.0
  end

  it "returning 'NSSize' returns an NSSize boxed object in Ruby" do
    o = TestMethod.new
    b = o.methodReturningNSSize
    b.class.should == NSSize
    b.width.class.should == Float
    b.width.should == 3.0
    b.height.class.should == Float
    b.height.should == 4.0
  end

  it "returning 'NSRect' returns an NSRect boxed object in Ruby" do
    o = TestMethod.new
    b = o.methodReturningNSRect
    b.class.should == NSRect
    b.origin.class.should == NSPoint
    b.origin.x.should == 1.0
    b.origin.y.should == 2.0
    b.size.class.should == NSSize
    b.size.width.should == 3.0
    b.size.height.should == 4.0
  end

  it "returning 'NSRange' returns an NSRange boxed object in Ruby" do
    o = TestMethod.new
    b = o.methodReturningNSRange
    b.class.should == NSRange
    b.location.class.should == Fixnum
    b.location.should == 0
    b.length.class.should == Fixnum
    b.length.should == 42
  end

  it "accepting the receiver as 'id' should receive the exact same object" do
    o = TestMethod.new
    o.methodAcceptingSelf(o).should == 1
  end

  it "accepting the receiver's class as 'id' should receive the exact same object" do
    o = TestMethod.new
    o.methodAcceptingSelfClass(o.class).should == 1
  end

  it "accepting 'nil' as 'id' should receive Objective-C's nil" do
    o = TestMethod.new
    o.methodAcceptingNil(nil).should == 1
  end

  it "accepting 'true' as 'id; should receive CF's kCFBooleanTrue" do
    o = TestMethod.new
    o.methodAcceptingTrue(true).should == 1
  end

  it "accepting 'false' as 'id' should receive CF's kCFBooleanFalse" do
    o = TestMethod.new
    o.methodAcceptingFalse(false).should == 1
  end

  it "accepting a Fixnum as 'id' should receive a Fixnum boxed object" do
    o = TestMethod.new
    o.methodAcceptingFixnum(42).should == 1
  end

  it "accepting nil or false as 'BOOL' should receive NO, any other object should receive YES" do
    o = TestMethod.new
    o.methodAcceptingFalseBOOL(nil).should == 1
    o.methodAcceptingFalseBOOL(false).should == 1

    o.methodAcceptingTrueBOOL(true).should == 1
    o.methodAcceptingTrueBOOL(0).should == 1
    o.methodAcceptingTrueBOOL(123).should == 1
    o.methodAcceptingTrueBOOL('foo').should == 1
    o.methodAcceptingTrueBOOL(Object.new).should == 1
  end

  it "accepting a Fixnum-compatible object as 'char', 'unsigned char', 'short', 'unsigned short', 'int', 'unsigned int', 'long', 'unsigned long' should receive the converted data, or raise an exception" do
    o = TestMethod.new
    o.methodAcceptingChar(42).should == 1
    o.methodAcceptingUnsignedChar(42).should == 1
    o.methodAcceptingShort(42).should == 1
    o.methodAcceptingUnsignedShort(42).should == 1
    o.methodAcceptingInt(42).should == 1
    o.methodAcceptingUnsignedInt(42).should == 1
    o.methodAcceptingLong(42).should == 1
    o.methodAcceptingUnsignedLong(42).should == 1

    o.methodAcceptingChar(42.0).should == 1
    o.methodAcceptingUnsignedChar(42.0).should == 1
    o.methodAcceptingShort(42.0).should == 1
    o.methodAcceptingUnsignedShort(42.0).should == 1
    o.methodAcceptingInt(42.0).should == 1
    o.methodAcceptingUnsignedInt(42.0).should == 1
    o.methodAcceptingLong(42.0).should == 1
    o.methodAcceptingUnsignedLong(42.0).should == 1

    o2 = Object.new
    def o2.to_i; 42; end

    o.methodAcceptingChar(o2).should == 1
    o.methodAcceptingUnsignedChar(o2).should == 1
    o.methodAcceptingShort(o2).should == 1
    o.methodAcceptingUnsignedShort(o2).should == 1
    o.methodAcceptingInt(o2).should == 1
    o.methodAcceptingUnsignedInt(o2).should == 1
    o.methodAcceptingLong(o2).should == 1
    o.methodAcceptingUnsignedLong(o2).should == 1

    lambda { o.methodAcceptingChar(nil) }.should raise_error(TypeError)
    lambda { o.methodAcceptingUnsignedChar(nil) }.should raise_error(TypeError)
    lambda { o.methodAcceptingShort(nil) }.should raise_error(TypeError)
    lambda { o.methodAcceptingUnsignedShort(nil) }.should raise_error(TypeError)
    lambda { o.methodAcceptingInt(nil) }.should raise_error(TypeError)
    lambda { o.methodAcceptingUnsignedInt(nil) }.should raise_error(TypeError)
    lambda { o.methodAcceptingLong(nil) }.should raise_error(TypeError)
    lambda { o.methodAcceptingUnsignedLong(nil) }.should raise_error(TypeError)

    lambda { o.methodAcceptingChar(Object.new) }.should raise_error(TypeError)
    lambda { o.methodAcceptingUnsignedChar(Object.new) }.should raise_error(TypeError)
    lambda { o.methodAcceptingShort(Object.new) }.should raise_error(TypeError)
    lambda { o.methodAcceptingUnsignedShort(Object.new) }.should raise_error(TypeError)
    lambda { o.methodAcceptingInt(Object.new) }.should raise_error(TypeError)
    lambda { o.methodAcceptingUnsignedInt(Object.new) }.should raise_error(TypeError)
    lambda { o.methodAcceptingLong(Object.new) }.should raise_error(TypeError)
    lambda { o.methodAcceptingUnsignedLong(Object.new) }.should raise_error(TypeError)
  end

  it "accepting a one-character string as 'char' or 'unsigned char' should receive the first character" do
    o = TestMethod.new
    o.methodAcceptingChar('*').should == 1
    o.methodAcceptingUnsignedChar('*').should == 1
  end

  it "accepting a String, Symbol or nil as 'SEL' should receive the appropriate selector" do
    o = TestMethod.new
    o.methodAcceptingSEL(:'foo:with:with:').should == 1
    o.methodAcceptingSEL('foo:with:with:').should == 1
    o.methodAcceptingSEL2(nil).should == 1

    lambda { o.methodAcceptingSEL(123) }.should raise_error(TypeError)
    lambda { o.methodAcceptingSEL(Object.new) }.should raise_error(TypeError)
  end

  it "accepting a Float-compatible object as 'float' or 'double' should receive the appropriate data" do
    o = TestMethod.new
    o.methodAcceptingFloat(3.1415).should == 1 
    o.methodAcceptingDouble(3.1415).should == 1

    o2 = Object.new
    def o2.to_f; 3.1415; end

    o.methodAcceptingFloat(o2).should == 1 
    o.methodAcceptingDouble(o2).should == 1

    lambda { o.methodAcceptingFloat(nil) }.should raise_error(TypeError) 
    lambda { o.methodAcceptingDouble(nil) }.should raise_error(TypeError) 
    lambda { o.methodAcceptingFloat(Object.new) }.should raise_error(TypeError) 
    lambda { o.methodAcceptingDouble(Object.new) }.should raise_error(TypeError) 
  end

=begin
  it "accepting an NSPoint, NSSize, NSRange or NSRect object as 'NSPoint', 'NSSize', 'NSRange' or 'NSRect' should receive the C structure" do
    o = TestMethod.new
    p = o.methodReturningNSPoint
    o.methodAcceptingNSPoint(p).should == 1
    p = o.methodReturningNSSize
    o.methodAcceptingNSSize(p).should == 1
    p = o.methodReturningNSRect
    o.methodAcceptingNSRect(p).should == 1
    p = o.methodReturningNSRange
    o.methodAcceptingNSRange(p).should == 1

    lambda { o.methodAcceptingNSPoint(nil) }.should raise_error(TypeError)
    lambda { o.methodAcceptingNSPoint(123) }.should raise_error(TypeError)
    lambda { o.methodAcceptingNSPoint(Object.new) }.should raise_error(TypeError)
    lambda { o.methodAcceptingNSPoint(o.methodAcceptingNSSize) }.should raise_error(TypeError)
    lambda { o.methodAcceptingNSSize(nil) }.should raise_error(TypeError)
    lambda { o.methodAcceptingNSSize(123) }.should raise_error(TypeError)
    lambda { o.methodAcceptingNSSize(Object.new) }.should raise_error(TypeError)
    lambda { o.methodAcceptingNSSize(o.methodAcceptingNSPoint) }.should raise_error(TypeError)
    lambda { o.methodAcceptingNSRect(nil) }.should raise_error(TypeError)
    lambda { o.methodAcceptingNSRect(123) }.should raise_error(TypeError)
    lambda { o.methodAcceptingNSRect(Object.new) }.should raise_error(TypeError)
    lambda { o.methodAcceptingNSRect(o.methodAcceptingNSPoint) }.should raise_error(TypeError)
    lambda { o.methodAcceptingNSRange(nil) }.should raise_error(TypeError)
    lambda { o.methodAcceptingNSRange(123) }.should raise_error(TypeError)
    lambda { o.methodAcceptingNSRange(Object.new) }.should raise_error(TypeError)
    lambda { o.methodAcceptingNSRange(o.methodAcceptingNSPoint) }.should raise_error(TypeError)
  end
=end
end