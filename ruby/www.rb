require 'net/http'
require 'uri'
require 'rubygems'
require 'pp'

require 'nokogiri'
require 'open-uri'


def hp_version
    require 'hpricot'
    # Use Net::HTTP to fetch some html
    html = Net::HTTP.get(URI.parse('http://www.juretta.com/log/'))

    # use hpricot
    doc = Hpricot(html)

    # get all entries
    doc.search("//div[@class='entry']/h3/a").each do |a|
      print a.inner_html + "\n  -> " + a.attributes['href'] + "\n\n"
    end
end

def nokogiri_version
    # Get a Nokogiri::HTML:Document for the page we’re interested in...
    doc = Nokogiri::HTML(open('http://www.google.com/search?q=tenderlove'))

    # Do funky things with it using Nokogiri::XML::Node methods...

    puts "teared, search..."

    ####
    # Search for nodes by css
    #doc.css('h3.r a.l').each do |link|
        #puts link.content
    doc.css('a').each do |link|
        puts "===>" + link.content
        puts link.to_html
    end
end
nokogiri_version
