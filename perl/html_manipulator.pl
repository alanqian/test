use HTML::Manipulator;

my $html = <<HTML;
    <h1 id=title>Old news</h1>
    <a href='http://www.google.com' id=link>Google</a>....
HTML

# replace a tag content
my $new = HTML::Manipulator::replace($html, title => 'New news');


# replace a tag attribute and content
my $new = HTML::Manipulator::replace($html, link => {
        _content => 'Slashdot',
        href=>'http://www.slashdot.org/' }
);


# extract a tag content
my $content = HTML::Manipulator::extract_content($html, 'link');

print $content;

# extract a tag content and attributes
my $tag =  HTML::Manipulator::extract($html, 'link');
# returns a hash ref like
# { href => 'http://www.google.com', id => 'link', _content => 'Google' }

