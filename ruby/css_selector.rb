#!/usr/bin/env ruby
# encoding: utf-8

require 'fileutils'
require 'rubygems'
require 'nokogiri'
require 'open-uri'
require 'uri'

class css_select_demo
  def tag_selector
    sel = %q(h1 {font-family:Arial,sans-serif;color:#CCCCFF;})
    sel2 = %q(DIV,H1 {font-family:Arial,sans-serif;color:#CCCCFF;})
    sel = "h1"
    sel2 = "div,p"
  end

  def class_selector
    sel = ".class"
  end

  def id_selector
    sel = "#id"
  end

  def descendent_selector
    sel = "h1 strong"
  end

  def group_selector
    sel = ""
  end
end

=begin css selector

http://net.tutsplus.com/tutorials/html-css-techniques/the-30-css-selectors-you-must-memorize/

1. *
   target every single element on the page
   can also be used with child selectors

   * { margin:0; padding:0; }
   #container * { border:1px solid black;}

2. #X
   ID selector: target by ID

   #container { width: 960px; margin: auto; }

   >> do I absolutely need to apply an id to this element in order to target it?

3. .X
   class selector: target all elements with style class X

   .error { color: red; }

4. X Y
   descendant selector: target all elements with tag Y and with parent tag X

   li a { text-decoration: none; }

   >> If your selector looks like X Y Z A B.error, you’re doing it wrong. Always
   ask yourself if it’s absolutely necessary to apply all of that weight.

5. X
   tag selector: target elements with tag X

   a { color: red; }
   ul { margin-left: 0; }

6. X:visited and X:link
   pseudo-class selector

   a:link { color: red; }
   a:visted { color: purple; }

7. X + Y
   adjacent selector: target only the element that is IMMEDIATELY preceded
   by the former element;

   ul + p { color: red; }

8. X > Y
   target element Y which is the direct child of element X

   div#container > ul {  border: 1px solid black;  }

   <div id="container">
      <ul>
        <li> List Item
          <ul>
            <li> Child </li>
          </ul>
        </li>
        <li> List Item </li>
        <li> List Item </li>
        <li> List Item </li>
      </ul>
    </div>

9. X ~ Y
   sibling selector: similar to X + Y, but less strict; NO immediately need.

10. X[attr]
   attributes selector: target an element X with attribute attr;

   a[title] { color: green; }

11. X[attr="foo"]
   target element X with attribute attr with EXACT VALUE "foo";

   a[href="http://net.tutsplus.com"] {  color: #1f6053; /* nettuts green */  }

   >> Note that we’re wrapping the value in quotes. Remember to also do this
      when using a JavaScript CSS selector engine. When possible, always use
      CSS3 selectors over unofficial methods.

12. X[href*="nettuts"]

   The STAR designates that the proceeding value must APPEAR somewhere in the
   attribute’s value.

   a[href*="tuts"] {  color: #1f6053; /* nettuts green */  }

13. X[href^="http"]

   target all X tags that have a href which BEGINS WITH http,

   a[href^="http"] {
      background: url(path/to/external/icon.png) no-repeat;
      padding-left: 10px;
   }

14. X[href$=".jpg"]

   target all X tags that have a href which ENDS WITH .jpg,

15. X[data-*="foo"]

   target all X tags that have a custom attributes data-* with value foo;

16. X[foo~="bar"]

   The tilde (~) symbol allows us to target an attribute which has a
   SPACED-SEPARATED LIST of values.

    a[data-info~="external"] {
       color: red;
    }
    a[data-info~="image"] {
       border: 1px solid black;
    }

    <a href="path/to/image.jpg" data-info="external image"> Click Me, Fool </a>

17. X:checked
   pseudo-class selector: target checked element like a checkbox/radio button;

    X:after
    X:hover

20. X:not(selector)

   div:not(#container) { color: blue; }

21. X::pseudoElement

  p::first-line { font-weight: bold; font-size: 1.2em; }
  p::first-letter {
    float: left;
    font-size: 2em;
    font-weight: bold;
    font-family: cursive;
    padding-left: 2px;
  }

22. X:nth-child(n)
    X:nth-last-child(n)

  li:nth-child(3) { color: red; }
  the second list item: li:nth-class(2)

24. X:nth-of-type(n)
    X.nth-of-last-type(n)

  ul:nth-of-type(3) { border: 1px; }
  >> select the 3rd ul;

26. X::first-child
    X: last-child

    ul li:first-child { border-top: none; }

28. X:only-child

  div p:only-child { color: red; }

29. X:only-of-type

  li:only-of-type { font-weight: bold; }

  ul > li:only-of-type { font-weight: bold; }

3- X:first-of-type

    <div>
       <p> My paragraph here. </p>
       <ul>
          <li> List Item 1 </li>
          <li> List Item 2 </li>
       </ul>
       <ul>
          <li> List Item 3 </li>
          <li> List Item 4 </li>
       </ul>
    </div>
=end

=begin nokogiri
# Get a Nokogiri::HTML::Document for the page we’re interested in...

doc = Nokogiri::HTML(open('http://www.google.com/search?q=sparklemotion'))

# Do funky things with it using Nokogiri::XML::Node methods...

####
# Search for nodes by css
doc.css('h3.r a').each do |link|
  puts link.content
end


by class:
  doc.css("p.warning, p.note")
by ID
  doc.css("#main, #basic, #exclaimation")

by node tree parent/child
  doc.css("div.heat a")

####
# Search for nodes by xpath
doc.xpath('//h3/a').each do |link|
  puts link.content
end

####
# Or mix and match.
doc.search('h3.r a.l', '//h3/a').each do |link|
  puts link.content
end

=end
