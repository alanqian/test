#!/usr/bin/perl 
#===============================================================================
#
#         FILE:  t.pl
#
#        USAGE:  ./t.pl  
#
#  DESCRIPTION:  G
#
#      OPTIONS:  ---
# REQUIREMENTS:  ---
#         BUGS:  ---
#        NOTES:  ---
#       AUTHOR:  YOUR NAME (), 
#      COMPANY:  
#      VERSION:  1.0
#      CREATED:  02/28/2011 03:21:40 PM
#     REVISION:  ---
#===============================================================================

use strict;
use HTML::ContentExtractor;
use LWP::UserAgent;

my $extractor = HTML::ContentExtractor->new();
my $agent=LWP::UserAgent->new;

my $url='http://sports.sina.com.cn/g/2007-03-23/16572821174.shtml';
$url = q(http://www.u148.net/article/27652.html);
$url = q(http://news.sina.com.cn/w/sd/2011-03-18/123022139452.shtml);
my $res=$agent->get($url);
my $HTML = $res->decoded_content();

$extractor->extract($url,$HTML);
#print $extractor->as_html();
my @paras = split("\n", $extractor->as_text());
print scalar(@paras);
my $ln = 1;
foreach (@paras)
{
    print "[$ln] $_\n";
    ++$ln;
}
__END__

use warnings;

use Gtk2 '-init';
 
my $window = Gtk2::Window->new('toplevel');
$window->set_title("Hello World!");
 
my $button = Gtk2::Button->new("Press me");
$button->signal_connect(clicked => sub { print "Hello again - the button was
pressed\n"; });
 
$window->add($button);
$window->show_all;
 
Gtk2->main;
 
0;

