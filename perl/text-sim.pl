use Text::Document;

my $t = Text::Document->new();

$t->AddContent( 'foo bar baz' );
$t->AddContent( 'foo barbaz; ' );

my @freqList = $t->KeywordFrequency();
my $u = Text::Document->new();
$u->AddContent( 'foo1 baz1' );

my $sj = $t->JaccardSimilarity( $u );
my $sc = $t->CosineSimilarity( $u );
#my $wsc = $t->WeightedCosineSimilarity( $u, \&MyWeight, $rock );

print $sc, "\n";

