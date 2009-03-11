require 'test_base'
require 'dl/func'

module DL
  class TestFunc < TestBase
    def test_strcpy()
      f = Function.new(CFunc.new(@libc['strcpy'], TYPE_VOIDP, 'strcpy'),
                       [TYPE_VOIDP, TYPE_VOIDP])
      buff = "000"
      str = f.call(buff, "123")
      assert_equal("123", buff)
      assert_equal("123", str.to_s)
    end

    def test_isdigit()
      f = Function.new(CFunc.new(@libc['isdigit'], TYPE_INT, 'isdigit'),
                       [TYPE_INT])
      r1 = f.call(?1)
      r2 = f.call(?2)
      rr = f.call(?r)
      assert_positive(r1)
      assert_positive(r2)
      assert_zero(rr)
    end

    def test_atof()
      f = Function.new(CFunc.new(@libc['atof'], TYPE_FLOAT, 'atof'),
                       [TYPE_VOIDP])
      r = f.call("12.34")
      assert_match(12.00..13.00, r)
    end

    def test_strtod()
      f = Function.new(CFunc.new(@libc['strtod'], TYPE_DOUBLE, 'strtod'),
                       [TYPE_VOIDP, TYPE_VOIDP])
      buff1 = "12.34"
      buff2 = "     "
      r = f.call(buff1, buff2)
      assert_match(12.00..13.00, r)
    end

    def test_qsort1()
      cb = Function.new(CFunc.new(0, TYPE_INT, '<callback>qsort'),
                        [TYPE_VOIDP, TYPE_VOIDP]){|x,y| CPtr.new(x)[0] <=> CPtr.new(y)[0]}
      qsort = Function.new(CFunc.new(@libc['qsort'], TYPE_VOID, 'qsort'),
                           [TYPE_VOIDP, TYPE_INT, TYPE_INT, TYPE_VOIDP])
      buff = "9341"
      qsort.call(buff, buff.size, 1, cb)
      assert_equal("1349", buff)
    end

    def test_qsort2()
      cb = TempFunction.new(CFunc.new(0, TYPE_INT, '<callback>qsort'),
                               [TYPE_VOIDP, TYPE_VOIDP])
      qsort = Function.new(CFunc.new(@libc['qsort'], TYPE_VOID, 'qsort'),
                           [TYPE_VOIDP, TYPE_INT, TYPE_INT, TYPE_VOIDP])
      buff = "9341"
      qsort.call(buff, buff.size, 1, cb){|x,y| CPtr.new(x)[0] <=> CPtr.new(y)[0]}
      assert_equal("1349", buff)
    end
  end
end
