
$fileName = "no_zealand.txt";

open FILE, "<", $fileName or die "Couldn't find file $fileName\n";

$hashLocation = {};

while (<FILE>) {

	chomp $_;
	@categories = split( '\t', $_ );

	$country = $categories[2];

	if ( $country ne "NZ" && $country ne "BE" ) {

		$region = $categories[3];

		if ( $region ne "HI" ) {

			$network  = $categories[0];
			$location = $country . "_" . $region . "_" . $categories[4];
			
			#print "Pushing $network\n";
			push( @{ $hashLocation{$location} }, $network );
		}

	}

}

@networks;	
for my $key ( keys %hashLocation ) {
	
	my $size=@{$hashLocation{$key}};
	if($size>10 && $size<100){
		
		foreach(@{$hashLocation{$key}}){
			push(@networks,$_);
		}
		
	}
	
}

my %seen;
$seen{$_}++ for @networks;
my @unique = keys %seen;

@sortedNetworks=sort @unique;

print "10,000th network is: $sortedNetworks[999]\n";
