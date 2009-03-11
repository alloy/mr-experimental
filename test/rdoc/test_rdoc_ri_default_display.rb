require 'stringio'
require 'test/unit'
require 'rdoc/ri/formatter'
require 'rdoc/ri/display'
require 'rdoc/ri/driver'

class TestRDocRIDefaultDisplay < Test::Unit::TestCase

  def setup
    @output = StringIO.new
    @width = 78
    @indent = '  '

    @dd = RDoc::RI::DefaultDisplay.new RDoc::RI::Formatter, @width, true,
                                       @output

    @some_method = {
      'aliases' => [{'name' => 'some_method_alias'}],
      'block_params' => 'block_param',
      'comment' => [RDoc::Markup::Flow::P.new('some comment')],
      'full_name' => 'SomeClass#some_method',
      'is_singleton' => false,
      'name' => 'some_method',
      'params' => '(arg1, arg2) {|block_param| ...}',
      'source_path' => '/nonexistent',
      'visibility' => 'public',
    }
  end

  def test_display_class_info
    ri_reader = nil
    klass = {
      'attributes' => [
        { 'name' => 'attribute', 'rw' => 'RW',
          'comment' => [RDoc::Markup::Flow::P.new('attribute comment')] },
        { 'name' => 'attribute_no_comment', 'rw' => 'RW',
          'comment' => nil },
      ],
      'class_methods' => [
        { 'name' => 'class_method' },
      ],
      'class_method_extensions' => [
        { 'name' => 'class_method_extension' },
      ],
      'comment' => [RDoc::Markup::Flow::P.new('SomeClass comment')],
      'constants' => [
        { 'name' => 'CONSTANT', 'value' => '"value"',
          'comment' => [RDoc::Markup::Flow::P.new('CONSTANT value')] },
        { 'name' => 'CONSTANT_NOCOMMENT', 'value' => '"value"',
          'comment' => nil },
      ],
      'display_name' => 'Class',
      'full_name' => 'SomeClass',
      'includes' => [],
      'instance_methods' => [
        { 'name' => 'instance_method' },
      ],
      'instance_method_extensions' => [
        { 'name' => 'instance_method_extension' },
      ],
      'superclass_string' => 'Object',
    }

    @dd.display_class_info klass, ri_reader

    expected = <<-EOF
---------------------------------------------------- Class: SomeClass < Object
     SomeClass comment

------------------------------------------------------------------------------


Constants:
----------

     CONSTANT:
          CONSTANT value

     CONSTANT_NOCOMMENT


Class methods:
--------------

     class_method


Class method extensions:
------------------------

     class_method_extension


Instance methods:
-----------------

     instance_method


Instance method extensions:
---------------------------

     instance_method_extension


Attributes:
-----------

     attribute (RW):
          attribute comment

     attribute_no_comment (RW)
    EOF

    assert_equal expected, @output.string
  end

  def test_display_flow
    flow = [RDoc::Markup::Flow::P.new('flow')]

    @dd.display_flow flow

    assert_equal "     flow\n\n", @output.string
  end

  def test_display_flow_empty
    @dd.display_flow []

    assert_equal "     [no description]\n", @output.string
  end

  def test_display_flow_nil
    @dd.display_flow nil

    assert_equal "     [no description]\n", @output.string
  end

  def test_display_method_info
    @dd.display_method_info @some_method

    expected = <<-EOF
-------------------------------------------------------- SomeClass#some_method
     some_method(arg1, arg2) {|block_param| ...}

     Extension from /nonexistent
------------------------------------------------------------------------------
     some comment


     (also known as some_method_alias)
    EOF

    assert_equal expected, @output.string
  end

  def test_display_method_info_singleton
    method = {
      'aliases' => [],
      'block_params' => nil,
      'comment' => nil,
      'full_name' => 'SomeClass::some_method',
      'is_singleton' => true,
      'name' => 'some_method',
      'params' => '(arg1, arg2)',
      'visibility' => 'public',
    }

    @dd.display_method_info method

    expected = <<-EOF
------------------------------------------------------- SomeClass::some_method
     SomeClass::some_method(arg1, arg2)
------------------------------------------------------------------------------
     [no description]
    EOF

    assert_equal expected, @output.string
  end

  def test_display_method_list
    methods = [
      {
        "aliases" => [],
        "block_params" => nil,
        "comment" =>  nil,
        "full_name" => "SomeClass#some_method",
        "is_singleton" => false,
        "name" => "some_method",
        "params" => "()",
        "visibility" => "public",
      },
      {
        "aliases" => [],
        "block_params" => nil,
        "comment" => nil,
        "full_name" => "SomeClass#some_other_method",
        "is_singleton" => false,
        "name" => "some_other_method",
        "params" => "()",
        "visibility" => "public",
      },
    ]

    @dd.display_method_list methods

    expected = <<-EOF
     More than one method matched your request.  You can refine your search by
     asking for information on one of:

     SomeClass#some_method, SomeClass#some_other_method
    EOF

    assert_equal expected, @output.string
  end

  def test_display_params
    @dd.display_params @some_method

    expected = <<-EOF
     some_method(arg1, arg2) {|block_param| ...}

     Extension from /nonexistent
    EOF

    assert_equal expected, @output.string
  end

  def test_display_params_multiple
    @some_method['params'] = <<-EOF
some_method(index)
some_method(start, length)
    EOF

    @dd.display_params @some_method

    expected = <<-EOF
     some_method(index)
     some_method(start, length)

     Extension from /nonexistent
    EOF

    assert_equal expected, @output.string
  end

  def test_display_params_singleton
    @some_method['is_singleton'] = true
    @some_method['full_name'] = 'SomeClass::some_method'

    @dd.display_params @some_method

    expected = <<-EOF
     SomeClass::some_method(arg1, arg2) {|block_param| ...}

     Extension from /nonexistent
    EOF

    assert_equal expected, @output.string
  end

  def test_list_known_classes
    klasses = %w[SomeClass SomeModule]

    @dd.list_known_classes klasses

    expected = <<-EOF
---------------------------------------------------- Known classes and modules

     SomeClass, SomeModule
    EOF

    assert_equal expected, @output.string
  end

  def test_list_known_classes_empty
    @dd.list_known_classes []

    expected = <<-EOF
No ri data found

If you've installed Ruby yourself, you need to generate documentation using:

  make install-doc

from the same place you ran `make` to build ruby.

If you installed Ruby from a packaging system, then you may need to
install an additional package, or ask the packager to enable ri generation.
    EOF

    assert_equal expected, @output.string
  end

end

