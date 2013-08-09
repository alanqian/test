# encoding : utf-8
require 'nokogiri'
require 'open-uri'

#example：baidu encoding：GB2312

def method_1
  html=open("http://www.baidu.com/").read
  charset=Nokogiri::HTML(html).meta_encoding #！有些网页没有定义charset则不适用
  puts charset
  html.force_encoding(charset)
  html.encode!("utf-8", :undef => :replace, :replace => "?", :invalid => :replace)
  doc = Nokogiri::HTML.parse html
  puts doc
end

# method 2
require 'rchardet19'

def toUtf8(_string)
  cd = CharDet.detect(_string)      #用于检测编码格式  在gem rchardet9里
  if cd.confidence > 0.6
    _string.force_encoding(cd.encoding)
  end
  _string.encode!("utf-8", :undef => :replace, :replace => "?", :invalid => :replace)
  return _string
end

begin
  doc = Nokogiri::HTML(toUtf8(open("http://www.baidu.com/").read))
  puts doc
end


