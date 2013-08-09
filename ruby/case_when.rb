def test_case_when(t)
  case t
  when 1
    puts "case 1: t=#{t}"
    puts "need not break!"
  when 2
    puts "case 2: t=#{t}"
    t = 4
    puts "modified, t=#{t}"
    puts "still need not break!"
  else
    puts "other case: 1,2: t=#{t}"
    puts "need not break!"
  end
end

test_case_when(1)
test_case_when(2)
test_case_when(3)
